#include "TTree.h"
#include "PixelCalibrations/include/PixelPowerLVStatus.h"

//#define NDEBUG

#include "CalibFormats/SiPixelObjects/interface/PixelCalibConfiguration.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDACNames.h"
#include "CalibFormats/SiPixelObjects/interface/PixelDACSettings.h"
#include "PixelConfigDBInterface/include/PixelConfigInterface.h"
#include "PixelUtilities/PixelTestStandUtilities/include/PixelTimer.h"
#include "PixelUtilities/PixeluTCAUtilities/include/PixelAMC13Interface.h"
#include "PixelUtilities/PixelDCSUtilities/include/PixelDCSSOAPCommander.h"
#include "PixelUtilities/PixelDCSUtilities/include/PixelDCSPVSSCommander.h"
//#include "PixelUtilities/PixelDCSUtilities/include/PixelDCSPVSSDpe.h"
// #include "pixel/utils/PSXReply.h"
#include "utils/include/pixel/utils/LogMacros.h"
#include "log4cplus/logger.h"
//#include "log4cplus/loggingmacros.h"
//#include "xdaq/Application.h"
//#include <glob.h>
//#include <pthread.h>
#include <sys/socket.h>
#include <stdlib.h>     /* getenv */
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace pos;
using namespace std;
typedef vector<pos::PixelROCName> roclist_t;


// for possible future use , please leave comment section
//map<string, string> controlPowerFSMinterpret = {{"ON","LV_ON"},{"OFF","LV_OFF"},{"OVERCURRENT","LV_OFF"},
//{"UNDERVOLTAGE","LV_OFF"},{"MAXVOLTAGE","LV_OFF"},{"INTERNALTRIP","LV_OFF"},{"CALIBRATIONERROR","LV_OFF"},
//{"UNPLUGGED","LV_OFF"},{"MAXVCONN","LV_OFF"},{"NO_COMMUNICATION","LV_OFF"},{"DISABLED","LV_OFF"},
//{"MAXDROP","LV_OFF"},{"INTERLOCKED","LV_OFF"},{"INTERNALFAIL","LV_OFF"},{"POWERFAIL","LV_OFF"},{"DEAD","UNDEFINED"}};
//map<string, string> modulePowerFSMinterpret = {{"OFF","LV_OFF"},{"ON_LV","LV_ON"},{"ON","LV_ON"},
//{"HVMIXED","LV_ON"},{"HVRAMPINGUP","LV_ON"},{"HVRAMPINGDOWN","LV_ON"},
//{"HVON_LVOFF","LV_ON"},{"DIGITAL_ON_RED","LV_ON_REDUCED"},{"ANALOG_ON_RED","LV_ON_REDUCED"},
//{"ANALOG_ON","LV_OFF"},{"ERROR","LV_OFF"},{"UNPLUGGED","LV_OFF"},
//{"INTERLOCKED","LV_OFF"},{"NO_COMMUNICATION","LV_OFF"},{"DEAD","UNDEFINED"}};

PixelPowerLVStatus::PixelPowerLVStatus(const PixelSupervisorConfiguration &tempConfiguration, SOAPCommander *mySOAPCmdr)
    : PixelCalibrationBase(tempConfiguration, *mySOAPCmdr), logger_(app_->getApplicationLogger()) {
      //const xdaq::ApplicationDescriptor *psxDescriptor = 0;
      _mySOAPCommander=mySOAPCmdr;
      pvssCommander_ = 0;
      if (psxServers_.size() > 0){
        pvssCommander_ = new PixelDCSPVSSCommander(app_, psxServers_.begin()->second);
      }
}//end constructor

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PixelPowerLVStatus::beginCalibration(){

    //PixelCalibConfiguration *tempCalibObject = dynamic_cast<PixelCalibConfiguration *>(theCalibObject_);
    //assert(tempCalibObject != 0);
    // PixelSupervisorConfiguration *pixSupConfPtr = dynamic_cast<PixelSupervisorConfiguration *>(this);
    // SOAPCommander *soapCmdrPtr = dynamic_cast<SOAPCommander *>(this);
    // PixelDCSSOAPCommander dcsSoapCommander(this);
    // PixelDCSPVSSCommander pvssCommander(this, psxServers_.begin()->second); //xdaq::Application *xdaqApplication

    //ccu maps
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi1", {"+1N", 3, "0x7e"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi2", {"+2N", 3, "0x7d"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi3", {"+3N", 3, "0x7c"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi4", {"+4N", 3, "0x7b"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi5", {"+5N", 3, "0x7a"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi6", {"+6N", 3, "0x79"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi7", {"+7N", 3, "0x78"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmi8", {"+8N", 3, "0x77"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo1", {"-1N", 2, "0x77"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo2", {"-2N", 2, "0x78"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo3", {"-3N", 2, "0x79"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo4", {"-4N", 2, "0x7a"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo5", {"-5N", 2, "0x7b"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo6", {"-6N", 2, "0x7c"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo7", {"-7N", 2, "0x7d"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bmo8", {"-8N", 2, "0x7e"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi1", {"+1P", 3, "0x77"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi2", {"+2P", 3, "0x78"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi3", {"+3P", 3, "0x79"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi4", {"+4P", 3, "0x7a"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi5", {"+5P", 3, "0x7b"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi6", {"+6P", 3, "0x7c"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi7", {"+7P", 3, "0x7d"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpi8", {"+8P", 3, "0x7e"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo1", {"-1P", 2, "0x7e"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo2", {"-2P", 2, "0x7d"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo3", {"-3P", 2, "0x7c"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo4", {"-4P", 2, "0x7b"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo5", {"-5P", 2, "0x7a"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo6", {"-6P", 2, "0x79"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo7", {"-7P", 2, "0x78"}));
    ns_bpix_sectors_.insert (std::pair<std::string, bpixVector> ("bpo8", {"-8P", 2, "0x77"}));

    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC1_PRT1", { "0x7e", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC1_PRT2", { "0x7e", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC2_PRT1", { "0x7d", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC2_PRT2", { "0x7d", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC3_PRT1", { "0x7c", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC3_PRT2", { "0x7c", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC4_PRT1", { "0x7b", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC4_PRT2", { "0x7b", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC5_PRT1", { "0x7a", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC5_PRT2", { "0x7a", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC6_PRT1", { "0x79", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC6_PRT2", { "0x79", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC7_PRT1", { "0x78", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC7_PRT2", { "0x78", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC8_PRT1", { "0x77", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmI_SEC8_PRT2", { "0x77", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC1_PRT1", { "0x77", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC1_PRT2", { "0x77", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC2_PRT1", { "0x78", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC2_PRT2", { "0x78", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC3_PRT1", { "0x79", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC3_PRT2", { "0x79", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC4_PRT1", { "0x7a", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC4_PRT2", { "0x7a", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC5_PRT1", { "0x7b", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC5_PRT2", { "0x7b", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC6_PRT1", { "0x7c", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC6_PRT2", { "0x7c", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC7_PRT1", { "0x7d", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC7_PRT2", { "0x7d", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC8_PRT1", { "0x7e", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BmO_SEC8_PRT2", { "0x7e", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC1_PRT1", { "0x77", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC1_PRT2", { "0x77", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC2_PRT1", { "0x78", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC2_PRT2", { "0x78", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC3_PRT1", { "0x79", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC3_PRT2", { "0x79", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC4_PRT1", { "0x7a", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC4_PRT2", { "0x7a", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC5_PRT1", { "0x7b", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC5_PRT2", { "0x7b", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC6_PRT1", { "0x7c", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC6_PRT2", { "0x7c", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC7_PRT1", { "0x7d", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC7_PRT2", { "0x7d", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC8_PRT1", { "0x7e", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpI_SEC8_PRT2", { "0x7e", 3, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC1_PRT1", { "0x7e", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC1_PRT2", { "0x7e", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC2_PRT1", { "0x7d", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC2_PRT2", { "0x7d", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC3_PRT1", { "0x7c", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC3_PRT2", { "0x7c", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC4_PRT1", { "0x7b", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC4_PRT2", { "0x7b", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC5_PRT1", { "0x7a", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC5_PRT2", { "0x7a", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC6_PRT1", { "0x79", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC6_PRT2", { "0x79", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC7_PRT1", { "0x78", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC7_PRT2", { "0x78", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC8_PRT1", { "0x77", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("BPix_BpO_SEC8_PRT2", { "0x77", 2, "0x13"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D1_PRT1", {"0x7b", 1, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D1_PRT2", {"0x7c", 1, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D1_PRT3", {"0x7e", 1, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D1_PRT4", {"0x7d", 1, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D2_PRT1", {"0x7b", 1, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D2_PRT2", {"0x7c", 1, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D2_PRT3", {"0x7e", 1, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D2_PRT4", {"0x7d", 1, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D3_PRT1", {"0x7b", 1, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D3_PRT2", {"0x7c", 1, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D3_PRT3", {"0x7e", 1, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmI_D3_PRT4", {"0x7d", 1, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D1_PRT1", {"0x7b", 0, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D1_PRT2", {"0x7c", 0, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D1_PRT3", {"0x7e", 0, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D1_PRT4", {"0x7d", 0, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D2_PRT1", {"0x7b", 0, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D2_PRT2", {"0x7c", 0, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D2_PRT3", {"0x7e", 0, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D2_PRT4", {"0x7d", 0, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D3_PRT1", {"0x7b", 0, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D3_PRT2", {"0x7c", 0, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D3_PRT3", {"0x7e", 0, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BmO_D3_PRT4", {"0x7d", 0, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D1_PRT1", {"0x7b", 3, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D1_PRT2", {"0x7c", 3, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D1_PRT3", {"0x7e", 3, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D1_PRT4", {"0x7d", 3, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D2_PRT1", {"0x7b", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D2_PRT2", {"0x7c", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D2_PRT3", {"0x7e", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D2_PRT4", {"0x7d", 3, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D3_PRT1", {"0x7b", 3, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D3_PRT2", {"0x7c", 3, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D3_PRT3", {"0x7e", 3, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpI_D3_PRT4", {"0x7d", 3, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D1_PRT1", {"0x7b", 2, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D1_PRT2", {"0x7c", 2, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D1_PRT3", {"0x7e", 2, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D1_PRT4", {"0x7d", 2, "0x10"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D2_PRT1", {"0x7b", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D2_PRT2", {"0x7c", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D2_PRT3", {"0x7e", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D2_PRT4", {"0x7d", 2, "0x11"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D3_PRT1", {"0x7b", 2, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D3_PRT2", {"0x7c", 2, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D3_PRT3", {"0x7e", 2, "0x12"}));
    ns_portcard_addresses_.insert (std::pair<std::string, portcardVect> ("FPix_BpO_D3_PRT4", {"0x7d", 2, "0x12"}));
//    ns_portcard_addresses_cp_ = ns_portcard_addresses_;


    ns_fpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("d1", {1,2}));
    ns_fpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("d2", {3,4}));
    ns_fpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("d3", {5,6}));


    ns_bpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("l1", {1,2,3}));
    ns_bpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("l2", {8,9,10}));
    ns_bpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("l3", {11,12,13}));
    ns_bpix_dcdcs_.insert (std::pair<std::string, std::vector<int>> ("l4", {4,5,6,7}));

    ccu_ports_.insert (std::pair< std::string, int > ("bpix_bm", 2005));
    ccu_ports_.insert (std::pair< std::string, int > ("bpix_bp", 2006));
    ccu_ports_.insert (std::pair< std::string, int > ("fpix", 2007));
    ccu_ports_.insert (std::pair< std::string, int > ("fpix_testsetup", 2008));
    ccu_ports_.insert (std::pair< std::string, int > ("bpixtestsetup", 2009));
    ccu_ports_.insert (std::pair< std::string, int > ("bpixcommissionig", 2006));
    ccu_ports_.insert (std::pair< std::string, int > ("fpix_commissioning", 2007));


    /*
    *  Fills Maps from .dat files
    */
    PixelConfigInterface::get(theLowVoltageMap_, "pixel/lowvoltagemap/", *theGlobalKey_);
    if (theLowVoltageMap_ == 0) {
        cout << "Could not find the LowVoltageMap in the configuration"
             << "\n";
        assert(0);
    }

    PixelConfigInterface::get(thePowerMap_, "pixel/powermap/", *theGlobalKey_);
    if (thePowerMap_ == 0) {
        cout << "Could not find the PowerMap in the configuration"
             << "\n";
        assert(0);
    }//

    string action = "BeginCalibration";

    //ScanVana = tempCalibObject->parameterValue("ScanVana") == "yes";
    //ReadDCU = tempCalibObject->parameterValue("ReadDCU") == "yes"; // all-inclusive DCU snapshot with all portcards

}

bool PixelPowerLVStatus::execute() {
    //print ccu info
    cout << "\n sector -> { pxfecaddress, ccu, ring }" << endl;
    for (map<string , bpixVector >::iterator it=ns_bpix_sectors_.begin(); it!=ns_bpix_sectors_.end(); it++){
        cout << it->first << " -> { " << ns_bpix_sectors_[it->first].pxfecaddress << ", " << ns_bpix_sectors_[it->first].ccu << ", " << ns_bpix_sectors_[it->first].ring << " }" << endl;
    }
    cout << "\n sector -> { channel, ccu, ring }" << endl;
    for (map<string , portcardVect >::iterator it=ns_portcard_addresses_.begin(); it!=ns_portcard_addresses_.end(); it++){
        cout << it->first << " -> { "  << ns_portcard_addresses_[it->first].channel << ", " << ns_portcard_addresses_[it->first].ccu << ", " << ns_portcard_addresses_[it->first].ring << " }" << endl;
    }
    cout << "\n fpix dcdcs" << endl;
    for (map< string , vector<int> >::iterator it=ns_fpix_dcdcs_.begin(); it!=ns_fpix_dcdcs_.end(); it++){
        cout << it->first << " -> { " << ns_fpix_dcdcs_[it->first][0] << " , " <<ns_fpix_dcdcs_[it->first][1] << " } "<< endl;
    }
    cout << "\n bpix dcdcs" << endl;
    for (map< string , vector<int> >::iterator it=ns_bpix_dcdcs_.begin(); it!=ns_bpix_dcdcs_.end(); it++){
        cout << it->first << " -> { " ;
        for (int d_num : it->second){
            cout << d_num << "  " ;
        }
        cout << " } \n" ;

    }
    cout << "\n ccu ports" << endl;
    for (map< string, int >::iterator it=ccu_ports_.begin(); it!=ccu_ports_.end(); it++){
        cout << it->first << " -> " << it->second << endl;
    }

    // debugging
    set<pos::PixelModuleName> modulesToLoop; // add temporarily here to test
    for (vector<pos::PixelModuleName>::const_iterator module = theDetectorConfiguration_->getModuleList().begin(), end = theDetectorConfiguration_->getModuleList().end(); module != end; ++module) {
        modulesToLoop.insert(*module);
        PixelDACSettings *dacs = 0;
        PixelConfigInterface::get(dacs, "pixel/dac/" + module->modulename(), *theGlobalKey_);
        assert(dacs != 0);
        // dacsettings_[*module] = dacs;
    }
    cout << " \n\n Getting Module LV Status ..." << endl;
    getLVstatusForModules(modulesToLoop);
    cout << "\nPrint LVstatusMap below: " << endl;
    for (map<string, string>::iterator it=nodeLVstatusMap_.begin(); it!=nodeLVstatusMap_.end(); ++it){
      cout << it->first << " => "<< it->second << endl;
    }

    cout << " \n Getting Module DCDC Status ..." << endl;
//    std::map<std::string,std::string> getDCDCStatusMdNd=getDCDCstatusForModules(modulesToLoop);
//    cout << "\nPrint DCDC Map below: " << endl;
//    for (map<string, string>::iterator it=getDCDCStatusMdNd.begin(); it!=getDCDCStatusMdNd.end(); ++it){
//      cout  << it->first << " => "<< it->second << endl;
//    }


    cout << " \n Executed PixelPowerLVStatus" << endl;
    return false;
}

void PixelPowerLVStatus::endCalibration() {
  // does nothing really at the moment
  cout << "\n End of Calibration. Will Provide necessary details here later" << endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*                                    Section1.1: Get LV status of modules
*                                Create structures:  map/list<module,PowerSupply>
----------------------------------------------------------------------------------------------------------------------*/
bool PixelPowerLVStatus::getLVstatusForModules(set<pos::PixelModuleName> &moduleList) {
  string return_Node = "UNKNOWN";
  string return_string = "None";
  pair<string,string> return_Pair (return_Node,return_string);
  list<PixelDCSPVSSDpe> dpes; // PVSS data-point name
  list<string> list_return_Node;

  INFO("Will get the power status for " + itoa(moduleList.size()) + " modules:");
  set<string> nodesToBeQuerried;
  for (set<pos::PixelModuleName>::iterator it_module = moduleList.begin();it_module != moduleList.end(); it_module++) {
    string dpName = theLowVoltageMap_->dpName(*it_module);  // module name to string
    if (dpName != "") {
      nodesToBeQuerried.insert(dpName);
      // INFO("   dpName:" + dpName);
    }
  }
  INFO("Will get the power status for " + itoa(nodesToBeQuerried.size()) + " notes");
  for (set<string>::iterator it_note = nodesToBeQuerried.begin();it_note != nodesToBeQuerried.end(); it_note++) {
    //go from this format CAEN/CMS_TRACKER_SY1527_5/branchController05/easyCrate0/easyBoard01
    //to this cms_trk_dcs_1:tkPg_CAEN\CMS_TRACKER_SY1527_5\branchController05\easyCrate0\easyBoard00.readyLv.bits.9
    // INFO("    note:"+ (*it_note));
    string note_complete = "cms_trk_dcs_1:tkPg_" + (*it_note) + ".getState";
    replace(note_complete.begin(), note_complete.end(), '/', '\\');
    list_return_Node.push_back(note_complete);
    // PixelDCSPVSSDpe dpe(note_complete,desired_value);
    dpes.push_back(PixelDCSPVSSDpe(note_complete, ""));
    return_Node = note_complete;
    pair<string,string> return_Pair (return_Node,return_string);
    nodeLVstatusMap_.insert(return_Pair);
  }

  if (pvssCommander_ != 0 && dpes.size() > 0) {
    INFO("Will send the soap to PVSS");
    cout<< "Pvsss commander == "<<pvssCommander_ <<endl;
    list<PixelDCSPVSSDpe> returndpes; // list of the values of a PVSS data-point
    try {
        returndpes = pvssCommander_->getDpeValues(dpes);
    }
    catch (xdaq::exception::Exception &e) {
        string const msg_error_hmy = "Failure to get the status from the PSX server. Exception: " + string(e.what());
        ERROR(msg_error_hmy);
        return_string = "STATE_MIXED";
        pair<string,string> return_Pair (return_Node,return_string);
        return false;
    }
    for (list<PixelDCSPVSSDpe>::iterator it_dpe = returndpes.begin(); it_dpe != returndpes.end(); it_dpe++) {
      string msg_status = "status " + it_dpe->getName() + " is " + it_dpe->getValue();
      INFO(msg_status);
      if (return_string == "None") {
	       return_string = it_dpe->getValue();
      }
      else if (return_string != it_dpe->getValue()) {
	       return_string = "STATE_MIXED";
      }
      return_Node = it_dpe->getName();
      return_Pair.first = return_Node;
      return_Pair.second = return_string;
      nodeLVstatusMap_.insert(return_Pair);
    }
  }

  // cout << "\n nodeLVstatusMap_ : " << endl;
  INFO("nodeLVstatusMap_ : ");
  for (std::map<std::string, std::string>::iterator it=nodeLVstatusMap_.begin(); it!=nodeLVstatusMap_.end(); ++it){
    // cout << "    " << it->first << " => " << it->second << endl;
    INFO("    " << it->first << " => " << it->second);
  }
  INFO("Moment Before the return at line:"+to_string(__LINE__));
  return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*                                    Section1.2: Get DCDC status of modules
*                                   Create structures:  map/list<module, DCDC>
----------------------------------------------------------------------------------------------------------------------*/
map<string,string> PixelPowerLVStatus::getDCDCstatusForModules(set<pos::PixelModuleName> &moduleList) {
  pair<string, string> dcdcpgname;
  string dcdcname;
  string pgname;
  pos::PixelModuleName modulname;
  string modname;
  pair<string,string> return_Pair ;

  INFO("Will get the DCDC status for " + itoa(moduleList.size()) + " modules:");
  set<string> nodesToBeQuerried;
  for (set<pos::PixelModuleName>::iterator it_module = moduleList.begin();it_module != moduleList.end(); it_module++) {
    dcdcpgname = thePowerMap_->dcdcAndPowergroup(*it_module);  // module name to pair
    dcdcname = dcdcpgname.first;
    pgname = dcdcpgname.second;
    if (dcdcname != "") {
      INFO("   dcdcname:" + dcdcname);
    }
    if (pgname != "") {
      INFO("   pgname:" + pgname);
    }
    modulname = *it_module;
    modname = modulname.modulename();
    INFO("   modulename:" + modname);
    INFO("Filling module to DCDC map...");
    return_Pair = make_pair(modname, dcdcname);
    modDCDCstatusMap_.insert(return_Pair);
  }
  return modDCDCstatusMap_;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*  Set status:
 *    a) set LV off per power supply in parallel                b) disable DCDCs per power supply in parallel
 *    c) set LV on per power supply in parallel                 d) enable DCDCs per power supply in parallel
----------------------------------------------------------------------------------------------------------------------*/
bool PixelPowerLVStatus::setONpower(set<string> compList){
    // string lvon = "ON";
    if (compList.size() == 0){return false;}
    list<PixelDCSPVSSDpe> set_dpes;
    for (set<string>::iterator it = compList.begin(); it != compList.end(); it++) {
      set_dpes.push_back(PixelDCSPVSSDpe((*it) , "1"));
    }
    if (pvssCommander_ != 0) {
      for (map<string, string>::iterator it=nodeLVstatusMap_.begin(); it!=nodeLVstatusMap_.end(); ++it){
          cout << it->first << " => "<< it->second << endl;
          std::size_t foundLVON = (it->second).find("ON");
          if (foundLVON!=std::string::npos){
              std::cout << "LV is at status " << it->second << '\n';
              std::cout << " Which means we need to turn off ! ";
              try {
                  pvssCommander_->setDpeValue(it->first, "LV_OFF");
              }
              catch (xoap::exception::Exception &e) {
                  string const msg_error_hmy = "Failure to print the status: " + string(e.what());
                  ERROR(msg_error_hmy);
              }
          }
          else{
              std::cout << "LV is at status " << it->second << '\n';
              std::cout << " Leave as is , check enable DCDC ? ";
          }
          //disable DCDCs first here?

          try {
              pvssCommander_->setDpeValue(it->first, "LV_ON");
          }
          catch (xoap::exception::Exception &e) {
              string const msg_error_hmy = "Failure to print the status: " + string(e.what());
              ERROR(msg_error_hmy);
          }

          //disable DCDCs first here?

      }
    }
    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                       CCU - DCDC functions
//----------------------------------------------------------------------------------------------------------------------
bool PixelPowerLVStatus::checkKillOpenProcess(std::string systemStr){
    std::string systemLower = systemStr;
    std::transform(systemLower.begin(), systemLower.end(), systemLower.begin(), ::tolower);
    int port = ccu_ports_[systemLower];

    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    inet_aton("127.0.0.1", &address.sin_addr); // .s_addr
    address.sin_port = htons(port);
    bool port_free = true;

    try{
        bind(s, (struct sockaddr *) &address, addrlen);
        if (errno==EADDRINUSE){ //98
            throw errno;
        }
    }
    catch (int e){
        port_free = false;
        if (e == EADDRINUSE){
            std::cout << "Port is already in use" << std::endl;
            std::string kill;
            std::cout << "Do you want to kill running ccu processes (Yes/No) ? ";
            std::cin >> kill;
            if (kill !="Yes"){
                return port_free;
            }
            const char * killcommand;
            killcommand = "for p in $(pgrep ccu); do kill -s KILL $p; done";
            std::cout << "Issuing command:" << std::endl;
            std::cout << killcommand << std::endl;
            FILE * killedF = popen(killcommand, "r"); //.readlines();
            char line[200];
            std::cout << "Result: "<< std::endl;
            while (fgets(line, sizeof(line), killedF) != NULL) {
                std::cout <<"  " <<  line << std::endl;
            }
            sleep(2);
            // std::cout <<"Result:" <<  killed << std::endl;
            std::cout << std::strerror(e) << std::endl;
            port_free = true;
        }
        else{
            // something else raised the socket.error exception
            std::cout << "Port error" << std::endl;
            std::cout << "[Error}:" << e << " : " << std::strerror(e) << std::endl;
        }
     }

    return port_free;
}

#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string PixelPowerLVStatus::exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");

    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe))
    {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }
    auto rc = pclose(pipe);
    if (rc == EXIT_SUCCESS)
    {
        std::cout << "SUCCESS\n";
    }
    else
    {
        std::cout << "FAILED\n";
    }

    return result;
}

std::pair<std::string, std::string> PixelPowerLVStatus::sendToCcu(std::string systemStr, std::string ns_command){
        std::string ns_stdout;
        std::string ns_stderr;
        bool continue_ccu = checkKillOpenProcess(systemStr);
        if (!continue_ccu){
         std::pair<std::string, std::string> outPair ("Exit due to already open process","");
         return outPair;
        }

        std::string systemLower = systemStr;
        std::transform(systemLower.begin(), systemLower.end(), systemLower.begin(), ::tolower);
        if (systemLower.find("bpix_") != std::string::npos){
            while( systemLower.find("bpix") != string::npos) {
                systemLower.replace(systemLower.find("bpix"), 0, "");
            }
        }

        char * opstoolspathTemp;
        std::string opstoolspath;
        opstoolspathTemp=getenv("BPIXELTOOLS");
        if (opstoolspathTemp!=NULL){
            cout << "The current path is: %s" << opstoolspath << std::endl;
            std::string opstoolspath(opstoolspathTemp);
         }
         else{
            std::string opstoolspath = "~/opstools";
         }

//         res =
//        std::string cmdLineCommandTemp = "cd " + opstoolspath + "/ccu; ./run_" + systemLower + ".sh<< EOF \n " + ns_command + " \n exit  2>&1"; // \n EOF
//        const char* cmdLineCommand = cmdLineCommandTemp.c_str();
//        const char* testCMDL = "ls";
//        system(testCMDL);
//        system(cmdLineCommand);

        if (ns_stdout.empty()){
            ns_stdout="";
        }
        if (ns_stderr.empty()){
            ns_stderr="";
        }
        std::pair<std::string, std::string> outPair2 (ns_stdout,ns_stderr);
        return outPair2;
    }

std::string PixelPowerLVStatus::join(const vector<string> &vec_dummy, std::string &cseparator) {
    std::string s_dummy;
    s_dummy="";
    for (std::vector<std::string>::const_iterator p = vec_dummy.begin(); p != vec_dummy.end(); ++p) {
      s_dummy += *p;
      if (p != vec_dummy.end() - 1)
        s_dummy += cseparator;
    }
    return s_dummy;
}

std::vector<std::string> PixelPowerLVStatus::enableDisableDcdcs(std::string systemStr, std::string action, std::vector<std::string> portcards, std::vector<std::string> layer= {}, std::vector<std::string> disc={}, std::string dcdc_number="", bool sequential=true, bool fast=false){
    std::vector<std::string> ccus;
    std::vector<int> rings;
    std::vector<std::string> names;
    std::string portcard_lower;
    std::string actionLower;
    std::string specific_dcdc;
    std::string layLower;
    std::string dLower;
    std::string _ccu;
    int _ring;
    std::string this_command;
    std::vector<std::string> discAll={"D1","D2","D3"};
    std::vector<std::string> layerAll={"L1","L2","L3","L4"};

    for (std::string portcard : portcards){
        portcard_lower = portcard;
        std::transform(portcard_lower.begin(), portcard_lower.end(), portcard_lower.begin(), ::tolower);
        for (map<string,portcardVect>::iterator it=ns_portcard_addresses_.begin(); it!=ns_portcard_addresses_.end(); it++){
            std::string portcard_address = it->first;
            std::string portcard_address_lower = portcard_address;
            std::transform(portcard_address_lower.begin(), portcard_address_lower.end(), portcard_address_lower.begin(), ::tolower);
            //if (std::count(portcard_address_lower.begin(), portcard_address_lower.end(), portcard_lower)){ // //error!
            if (portcard_address_lower.find(portcard_lower) != std::string::npos){
                _ccu=ns_portcard_addresses_[portcard_address].ccu;
                _ring=ns_portcard_addresses_[portcard_address].ring;
                ccus.push_back(_ccu);
                rings.push_back(_ring);
                names.push_back(portcard_address_lower);
            }
        }
    }


    std::vector<std::string> ns_command;
    std::string ns_stdout = "";
    std::string ns_stderr = "";
    std::string fout_command = "";
    std::string foutSeparator = "";
    std::vector<std::string> ns_inOutErr;
    std::pair<std::string, std::string> stdOutErr;
    for (long unsigned int i =0; i < rings.size(); i++){
        this_command="";
        this_command = this_command + "ring " +  to_string(rings[i]) + " \n";
        this_command = this_command +"ccu " + ccus[i]  + " \n";

        actionLower = action;
        std::transform(actionLower.begin(), actionLower.end(), actionLower.begin(), ::tolower);
        if (!(actionLower=="on" || actionLower=="off")){
            ns_inOutErr.push_back(fout_command);
            ns_inOutErr.push_back(ns_stdout);
            ns_inOutErr.push_back(ns_stderr);
            return ns_inOutErr;
        }
        specific_dcdc="";

        if (!dcdc_number.empty()){
            specific_dcdc=dcdc_number;
            this_command= this_command + "power " +specific_dcdc + actionLower+ " \n";
            this_command = this_command + "sleep \n";
         }

        //else if ((std::count(names[i].begin(), names[i].end(), "bpix")) && (std::count(names[i].begin(), names[i].end(), "prt1")) && layer.empty()){
        else if ((names[i].find("bpix") != std::string::npos) && (names[i].find("prt1")!=std::string::npos) && (layer.empty())){
            if (sequential){
                for (int n_dcdc : ns_bpix_dcdcs_["l1"]) {
                    this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                    this_command = this_command + "sleep \n";
                }
                for (int n_dcdc : ns_bpix_dcdcs_["l2"]){
                    this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                    this_command = this_command + "sleep \n";
                 }
            }
            else{
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][0]) + to_string(ns_bpix_dcdcs_["l2"][0]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][1]) + to_string(ns_bpix_dcdcs_["l2"][1]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][2]) + to_string(ns_bpix_dcdcs_["l2"][2]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
             }
        }
        //else if ((std::count(names[i].begin(), names[i].end(), "bpix")) && (std::count(names[i].begin(), names[i].end(), "prt2")) && layer.empty()){
        else if ((names[i].find("bpix") != std::string::npos) && (names[i].find("prt2")!=std::string::npos) && (layer.empty())){
            if (sequential){
                for (int n_dcdc : ns_bpix_dcdcs_["l3"]){
                    this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                    this_command = this_command + "sleep \n";
                }
                for (int n_dcdc : ns_bpix_dcdcs_["l4"]){
                    this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                    this_command = this_command + "sleep \n";
                }
            }
            else{
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][0]) + to_string(ns_bpix_dcdcs_["l4"][0]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][1]) + to_string(ns_bpix_dcdcs_["l4"][1]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][2]) + to_string(ns_bpix_dcdcs_["l4"][2]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l4"][3]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
             }
        }
        //else if ((std::count(names[i].begin(), names[i].end(), "bpix")) && !layer.empty()){
        else if ((names[i].find("bpix") != std::string::npos) && (!layer.empty())){
            if (layer==layerAll && fast){
                this_command = this_command +"power "+ actionLower +" \n";
                this_command = this_command + "sleep \n";
            }
            else if (layer==layerAll && !sequential){
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][0]) + to_string(ns_bpix_dcdcs_["l2"][0]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][1]) + to_string(ns_bpix_dcdcs_["l2"][1]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l1"][2]) + to_string(ns_bpix_dcdcs_["l2"][2]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][0]) + to_string(ns_bpix_dcdcs_["l4"][0]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][1]) + to_string(ns_bpix_dcdcs_["l4"][1]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l3"][2]) + to_string(ns_bpix_dcdcs_["l4"][2]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_bpix_dcdcs_["l4"][3]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
            }
            else{
                for (std::string lay : layer){
                layLower = lay;
                std::transform(layLower.begin(), layLower.end(), layLower.begin(), ::tolower);
                    for (int n_dcdc : ns_bpix_dcdcs_[layLower]){
                        this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                        this_command = this_command + "sleep \n";
                     }
                 }
             }
        }

        //else if ((std::count(names[i].begin(), names[i].end(), "fpix")) && (std::count(names[i].begin(), names[i].end(), "d1")) && disc.empty()){
        else if ((names[i].find("fpix") != std::string::npos) && (names[i].find("d1")!=std::string::npos) && (disc.empty())){
            for (int n_dcdc : ns_fpix_dcdcs_["d1"]){
                this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                this_command = this_command + "sleep \n";
             }
        }
        //else if ((std::count(names[i].begin(), names[i].end(), "fpix")) && (std::count(names[i].begin(), names[i].end(), "d2")) && disc.empty()){
        else if ((names[i].find("fpix") != std::string::npos) && (names[i].find("d2")!=std::string::npos) && (disc.empty())){
            for (int n_dcdc : ns_fpix_dcdcs_["d2"]){
                this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                this_command = this_command + "sleep \n";
             }
        }
        //else if ((std::count(names[i].begin(), names[i].end(), "fpix")) && (std::count(names[i].begin(), names[i].end(), "d3")) && disc.empty()){
        else if ((names[i].find("fpix") != std::string::npos) && (names[i].find("d3")!=std::string::npos) && (disc.empty())){
            for (int n_dcdc : ns_fpix_dcdcs_["d3"]){
                this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                this_command = this_command + "sleep \n";
             }
         }
        //else if ((std::count(names[i].begin(), names[i].end(), "fpix"))  && !disc.empty()){
        else if ((names[i].find("fpix") != std::string::npos) &&  (!disc.empty())){
            if (disc==discAll && fast){
                this_command = this_command + "power " + actionLower +" \n";
                this_command = this_command + "sleep \n";
            }
            else if (disc==discAll && !sequential){
                this_command = this_command +"power " + to_string(ns_fpix_dcdcs_["d1"][0]) + to_string(ns_fpix_dcdcs_["d2"][0]) + to_string(ns_fpix_dcdcs_["d3"][0]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
                this_command = this_command +"power " + to_string(ns_fpix_dcdcs_["d1"][1]) + to_string(ns_fpix_dcdcs_["d2"][1]) + to_string(ns_fpix_dcdcs_["d3"][1]) + actionLower + " \n";
                this_command = this_command + "sleep \n";
            }
            else{
                for (std::string d : disc){
                    dLower = d;
                    std::transform(dLower.begin(), dLower.end(), dLower.begin(), ::tolower);
                    for (int n_dcdc : ns_fpix_dcdcs_[dLower]){
                        this_command = this_command + "power " + to_string(n_dcdc) + actionLower +" \n";
                        this_command = this_command + "sleep \n";
                     }
                 }
             }
         }


        if (std::count(ns_command.begin(), ns_command.end(), this_command)){
            ns_command.push_back(this_command);
        }

     }

   if (ns_command.empty()){
        ns_inOutErr.push_back(fout_command);
        ns_inOutErr.push_back(ns_stdout);
        ns_inOutErr.push_back(ns_stderr);
        return ns_inOutErr;
    }
    fout_command = join(ns_command, foutSeparator);
    stdOutErr=sendToCcu(systemStr,fout_command);
    ns_stdout = stdOutErr.first;
    ns_stderr = stdOutErr.second;

    ns_inOutErr.push_back(fout_command);
    ns_inOutErr.push_back(ns_stdout);
    ns_inOutErr.push_back(ns_stderr);
    return ns_inOutErr;

}

std::vector<std::string> PixelPowerLVStatus::writePiaRegEnable(std::string systemStr,std::vector<std::string> portcards={}){
    std::vector<std::string> ccus;
    std::vector<int> rings;
    std::vector<std::string> ns_command;
    std::string ns_stdout = "";
    std::string ns_stderr = "";
    std::string fout_command = "";
    std::string foutSeparator = "";
    std::vector<std::string> ns_inOutErr;
    std::pair<std::string, std::string> stdOutErr;

    std::string systemLower = systemStr;
    std::transform(systemLower.begin(), systemLower.end(), systemLower.begin(), ::tolower);
    if (portcards.empty()){
        std::vector<std::string> setUpIdStr={"fpix_testsetup", "bpixtestsetup", "fpix_commissioning", "bpixcommissioning"};
        if (std::find(setUpIdStr.begin(), setUpIdStr.end(), systemLower) != setUpIdStr.end()){
            string const msg_error_portcard = "Portcard must be provided for the testsetups and commissioning setups";
            ERROR(msg_error_portcard);
        }
        // std::vector<std::string> portcards;
        portcards.push_back(systemStr);
     }

    std::map<std::string,  std::map<std::string, std::string>> pia_data;
    std::map<std::string,std::string> pia_sub_data;
    pia_sub_data["fpix"] = "3f";
    pia_sub_data["bpix"] = "3f";
    pia_data["30"] = pia_sub_data;
    pia_sub_data["fpix"] = "0";
    pia_sub_data["bpix"] = "0";
    pia_data["31"] = pia_sub_data;
    pia_data["32"] = pia_sub_data;
    pia_data["33"] = pia_sub_data;

    std::string _ccu;
    int _ring;
    for (std::string portcard : portcards){
        std::string portcard_lower = portcard;
        std::transform(portcard_lower.begin(), portcard_lower.end(), portcard_lower.begin(), ::tolower);
        for (map<string,portcardVect>::iterator it=ns_portcard_addresses_.begin(); it!=ns_portcard_addresses_.end(); it++){
            std::string portcard_address = it->first;
            std::string portcard_address_lower = portcard_address;
            std::transform(portcard_address_lower.begin(), portcard_address_lower.end(), portcard_address_lower.begin(), ::tolower);
            if (portcard_address_lower.find(portcard_lower) != std::string::npos){
                _ccu=ns_portcard_addresses_[portcard_address].ccu;
                _ring=ns_portcard_addresses_[portcard_address].ring;
                ccus.push_back(_ccu);
                rings.push_back(_ring);
            }
        }
    }

    std::string this_command;
    for (long unsigned int i =0; i < rings.size(); i++){
        this_command="";
        this_command = this_command + "ring " +  to_string(rings[i]) + " \n";
        this_command = this_command +"ccu " + ccus[i]  + " \n";
        for (map<string,std::map<std::string, std::string>>::iterator it=pia_data.begin(); it!=pia_data.end(); it++){
            std::string pia = it->first;
            this_command = this_command + "piaChannel " + pia + " \n";
            this_command = this_command + "pia get ddr \n";
            this_command = this_command + "pia get data \n";
            if (systemLower.find("fpix") != std::string::npos){
                this_command = this_command + "pia set data " + pia_data[pia][""] + " \n";
            }
            else if (systemLower.find("bpix") != std::string::npos){
                this_command = this_command + "pia set data " + pia_data[pia][""] + " \n";
            }
            this_command = this_command + "pia get data \n";
            this_command = this_command + "pia set ddr 0 \n";
            this_command = this_command + "pia get ddr \n";
            this_command = this_command + "pia get data \n";
        }
        if (std::count(ns_command.begin(), ns_command.end(), this_command)){
            ns_command.push_back(this_command);
        }
     }

    if (ns_command.empty()){
        ns_inOutErr.push_back(fout_command);
        ns_inOutErr.push_back(ns_stdout);
        ns_inOutErr.push_back(ns_stderr);
        return ns_inOutErr;
    }
    fout_command = join(ns_command, foutSeparator);
    stdOutErr=sendToCcu(systemStr,fout_command);
    ns_stdout = stdOutErr.first;
    ns_stderr = stdOutErr.second;

    ns_inOutErr.push_back(fout_command);
    ns_inOutErr.push_back(ns_stdout);
    ns_inOutErr.push_back(ns_stderr);
    return ns_inOutErr;
}