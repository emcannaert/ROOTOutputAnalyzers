// Macro to add PDF weights to nanoAODtrees
// calcAlphas, calcRenomrmWeight, and calcFacorizeWeight lightly modified from versions sent by Carlos at https://cms-pub-talk.web.cern.ch/t/comments-on-anv7/6774/3

// Compilation instuctions:
/*
  This macro requires both ROOT and the LHAPDF library so must be compiled against both.
  To compile using ROOT on LPC:
  - Set up a CMS env (>= CMSSW_10_6_X )
  - run:  lhapdf-config --cflags --ldflags     to get the paths necessary for compilation
      and linking against LHAPDF
  - start root:    root
  - in root, run :  gSystem->AddIncludePath(" -I/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/lhapdf/6.2.1-pafccj3/include ")     where the path matches the include path from the lhapdf-config
  - in root, run : gSystem->AddLinkedLibs("-L/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/lhapdf/6.2.1-pafccj3/lib -lLHAPDF")   where the path matches the include path from the lhapdf-config
  - in root, compile this script:    .L pdfWeightAdder.C+
  - The functions below can now be run

*/

#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#include <cmath>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

using namespace LHAPDF;
//using namespace std;

//TString FILEPATH_BASE = "root://cmsxrootd.fnal.gov//store/user/fojensen/excitedTau_01112022/"; //The path to the directory containing files to be used
TString FILEPATH_BASE = "../Data/PdfWeights/ExcitedTau_06032023/";
const int N_FILES = 17; //Number of files to be read, if this is changed, fillFileList() must also be updated - 41 for all samples, 17 for just taustar signal MC

const int LHAPDF_NOM = 303600; // nominal PDF used to generate the sample. This should also be used for e.g. the muF uncertainty below
// Nominal pdf is NNPDF31_nnlo_as_0118 => lhapdfnumber_base = 303600
const int LHAPDF_VAR_LOW = 303601; //The LHAPDF number of the first variation
const int LHAPDF_VAR_HIGH = 303700; //The LHAPDF number of the last variation
int nVars = 100; //The number of variations (MC Replicas // WARNING /// this is assumed to be 100 in the branch defs below
int nVarsUD = 2 * nVars; //doubled to include up and down   ///// WARNING //// this is assumed to be 200 in the branch defs below

void setFilepathBase(TString newFilepath);
void fillFileList(TString filenames[], int nQCDs[], TString year);
void addPDFWeights(TString filename, int nQCD, PDF* nomPDF, PDF* varPDFs[]);
double calcAlphas(double q2);
double calcRenormWeight(double q2, int up_or_dn, int nQCD);
double calcFactorizWeight(LHAPDF::PDF* pdf, double id1, double id2, double x1, double x2, double q2, int up_or_dn);

//Add PDF weights to the files retrieved by fillFileList for the given year
// TString year : the year to fill files for
void pdfWeightAdder(TString year)
{   
    //Get the PDFs
    PDF* nomPDF = LHAPDF::mkPDF(LHAPDF_NOM); //Nominal PDF
    PDF* varPDFs[nVars];
    for (int i = 0; i< nVars; i++)
      {
	    varPDFs[i] = LHAPDF::mkPDF(LHAPDF_VAR_LOW + i);
      }
    
    //Add the weights to each file
    cout << "\nBeginning " << year << "..." << endl;
    TString filenames[N_FILES];
    int nQCDs[N_FILES];

    fillFileList(filenames, nQCDs, year);

    for (int fN = 0; fN < N_FILES; fN++)
    {
        cout << "\tAdding weights to file:  " << filenames[fN] << endl;
        addPDFWeights(filenames[fN], nQCDs[fN], nomPDF, varPDFs);
    }
}

//Set a new path to the directory containing the files listed in fillFileList()
void setFilepathBase(TString newFilepath)
{
    FILEPATH_BASE = newFilepath;
}


/* Fills the passed arrays with the list of filenames to read and the corresponding num of QCD vertices in the involved diagrams
   TString filenames[] : an empty TString array of length N_FILES to fill with filenames
   TString nQCDs[] : an empty int array of length N_FILES to fill with the num of QCD vertices (i.e. gg/gq/qq -> gluino gluino or stop stop) in the involved diagram
   TString year : the desired year
*/ 
void fillFileList(TString filenames[], int nQCDs[], TString year)
{
    filenames[0] = "Taustar_m1750_" + year + ".root";
    nQCDs[0] = 0;
    filenames[0] = "Taustar_m1000_" + year + ".root";
    nQCDs[0] = 0;
    filenames[1] = "Taustar_m1250_" + year + ".root";
    nQCDs[1] = 0;
    filenames[2] = "Taustar_m1500_" + year + ".root";
    nQCDs[2] = 0;
    filenames[3] = "Taustar_m1750_" + year + ".root";
    nQCDs[3] = 0;
    filenames[4] = "Taustar_m175_" + year + ".root";
    nQCDs[4] = 0;
    filenames[5] = "Taustar_m2000_" + year + ".root";
    nQCDs[5] = 0;
    filenames[6] = "Taustar_m2500_" + year + ".root";
    nQCDs[6] = 0;
    filenames[7] = "Taustar_m250_" + year + ".root";
    nQCDs[7] = 0;
    filenames[8] = "Taustar_m3000_" + year + ".root";
    nQCDs[8] = 0;
    filenames[9] = "Taustar_m3500_" + year + ".root";
    nQCDs[9] = 0;
    filenames[10] = "Taustar_m375_" + year + ".root";
    nQCDs[10] = 0;
    filenames[11] = "Taustar_m4000_" + year + ".root";
    nQCDs[11] = 0;
    filenames[12] = "Taustar_m4500_" + year + ".root";
    nQCDs[12] = 0;
    filenames[13] = "Taustar_m5000_" + year + ".root";
    nQCDs[13] = 0;
    filenames[14] = "Taustar_m500_" + year + ".root";
    nQCDs[14] = 0;
    filenames[15] = "Taustar_m625_" + year + ".root";
    nQCDs[15] = 0;
    filenames[16] = "Taustar_m750_" + year + ".root";
    nQCDs[16] = 0;
}


/* Reads in nominal weighting information from the Events tree in filename and calculates and stores new weights in the tree
    TString filename : the name of the root file to be read, relative to FILEPATH_BASE. This file will be updated in place
    int nQCD : the number of QCD vertices (i.e. ggq, qqgg, etc) in the diagram
*/
void addPDFWeights(TString filename, int nQCD, PDF* nomPDF, PDF* varPDFs[])
{
    TFile* file = TFile::Open(FILEPATH_BASE + filename, "UPDATE");
    TTree* tree = (TTree*) file->Get("Events");
    if (tree == NULL)
        {
            cout << "File " << filename << " could not be read or does not contain a readable tree" << endl;
            exit(-1);
        }

    //Set up storage of new weights
    double alphas;
    double renormWeights[2]; //Up, down
    double factorizWeights[nVarsUD];
    double weightsForVar[nVars]; 
    double factWeightsRMSs[2]; // Up, down
    double varWeightsRMS;
    double varWeightsErr;
    TBranch *b_alphas = tree->Branch("PDFWeights_alphas", &alphas, "PDFWeights_alphas/D");
    TBranch *b_renormWeights = tree->Branch("PDFWeights_renormWeights", renormWeights, "PDFWeights_renormWeights[2]/D");
    //TBranch *b_nVarsUD = tree->Branch("PDFWeights_nVarsUD", &nVarsUD, "PDFWeights_nVarsUD/i");
    TBranch *b_nVars = tree->Branch("PDFWeights_nVars", &nVars, "PDFWeights_nVars/i");
    //TBranch *b_factorizeWeights = tree->Branch("PDFWeights_factorizeWeights", factorizWeights, "PDFWeights_factorizeWeights[200]/D");
    //TBranch *b_weightsForVar = tree->Branch("PDFWeights_weightsForVar", weightsForVar, "PDFWeights_weightsForVar[100]/D");
    TBranch *b_factWeightsRMSs = tree->Branch("PDFWeights_factWeightsRMSs", factWeightsRMSs, "PDFWeights_factWeightsRMSs[2]/D");
    TBranch *b_varWeightsRMS = tree->Branch("PDFWeights_varWeightsRMS", &varWeightsRMS, "PDFWeights_varWeightsRMS/D");
    TBranch *b_varWeightsErr = tree->Branch("PDFWeights_varWeightsErr", &varWeightsErr, "PDFWeights_varWeightsErr/D");

    const int VAR_UP = 1;
    const int VAR_DOWN = -1;
    float scalePDF, x1, x2; //The existing variables in the tree that we'll need to calc the new weights
    int id1, id2;
    
    tree->SetBranchAddress("Generator_id1", &id1);
    tree->SetBranchAddress("Generator_id2", &id2);
    tree->SetBranchAddress("Generator_scalePDF", &scalePDF);
    tree->SetBranchAddress("Generator_x1", &x1);
    tree->SetBranchAddress("Generator_x2", &x2);
    int nEntries = tree->GetEntries();

    for (int entryN = 0; entryN < nEntries; entryN++)
    {
        //Get the existing values from the tree
        tree->GetEntry(entryN);
      
        //Calc the new weights
        alphas = calcAlphas(scalePDF);
        renormWeights[0] = calcRenormWeight(scalePDF, VAR_UP, nQCD); 
        renormWeights[1] = calcRenormWeight(scalePDF, VAR_DOWN, nQCD); 
	
       
	for (int varN = 0; varN < nVars; varN++) 
        {
            factorizWeights[varN] = calcFactorizWeight(varPDFs[varN], id1, id2, x1, x2, scalePDF, VAR_UP); 
            factorizWeights[varN+1] = calcFactorizWeight(varPDFs[varN], id1, id2, x1, x2, scalePDF, VAR_DOWN); 

            factWeightsRMSs[0] += (factorizWeights[varN] * factorizWeights[varN]);
            factWeightsRMSs[1] += (factorizWeights[varN+1] * factorizWeights[varN+1]);

            // weight using https://lhapdf.hepforge.org/group__reweight__double.html, one per replica.
            weightsForVar[varN] = LHAPDF::weightxxQ(id1, id2, x1, x2, scalePDF, nomPDF, varPDFs[varN]); 
            varWeightsRMS += (weightsForVar[varN] * weightsForVar[varN]);
        }

        //Calculate the RMS's
        factWeightsRMSs[0] /= nVars;
        factWeightsRMSs[1] /= nVars; 
        factWeightsRMSs[0] = sqrt(factWeightsRMSs[0]);
        factWeightsRMSs[1] = sqrt(factWeightsRMSs[1]);
        varWeightsRMS /= nVars;
        varWeightsRMS = sqrt(varWeightsRMS);


        //Calculated the error on the varWeightsRMS according to eqn 6.4 from https://arxiv.org/pdf/2203.05506.pdf
        //Need the values in sorted order
        int arrSize = sizeof(weightsForVar) / sizeof(weightsForVar[0]);
        sort(weightsForVar, weightsForVar + arrSize);
        double weight16 = weightsForVar[15];
        double weight84 = weightsForVar[83];
        varWeightsErr = (weight84 - weight16) / 2.0;
        if (varWeightsErr < 0)
            varWeightsErr = 0;


        //Fill the tree
        b_alphas->Fill();
        b_renormWeights->Fill();
        //b_factorizeWeights->Fill();
        //b_weightsForVar->Fill();
        //b_nVarsUD->Fill();
        b_nVars->Fill();
        b_factWeightsRMSs->Fill();
        b_varWeightsRMS->Fill();
        b_varWeightsErr->Fill();
    }
    
    tree->Write("", TObject::kOverwrite); // save only the new version of the tree
	
}

// q2 == Generator_scalePDF in NanoAOD
double calcAlphas(double q2) 
{ 
    double mZ = 91.2; //Z boson mass in the NNPDF31_nnlo_as_0118 docs (http://lhapdfsets.web.cern.ch/lhapdfsets/current/NNPDF31_nnlo_as_0118/NNPDF31_nnlo_as_0118.info )
    double alphas_mZ = 0.118; //alpha_s evaluated at Z boson mass, based on the NNPDF31_nnlo_as_0118 docs (http://lhapdfsets.web.cern.ch/lhapdfsets/current/NNPDF31_nnlo_as_0118/NNPDF31_nnlo_as_0118.info )
    int nFlavors = 5; //effective number of flavors
    double b0 = (33 - 2.0 * nFlavors) / (12 * M_PI); 
    return alphas_mZ / (1 + alphas_mZ * b0 * std::log(q2 / std::pow(mZ,2))); // alphas evolution
}

// Will always be 1 for electroweak processes at LO
// number of QCD vertices (including both cubic and quartic e.g. qqg, ggqq, etc) 
double calcRenormWeight(double q2, int up_or_dn, int nQCD) 
{ 
    if (nQCD == 0) //Time saving check since we will exponentiate by nQCD as the last step
        return 1;

    double k2;
    if ( up_or_dn ==  1 )
        k2 = 4; // 2*q ==> 4*q2
    else if ( up_or_dn == -1 )
        k2 = 0.25; // 0.5*q ==> 0.25*q2
    else {
      throw std::invalid_argument("up_or_dn must be -1 or 1");
    }
    
    double alphas_old = calcAlphas(q2);
    double alphas_new = calcAlphas(k2*q2);
 
    return std::pow(alphas_new / alphas_old, nQCD);
}


double calcFactorizWeight(LHAPDF::PDF* pdf, double id1, double id2, double x1, double x2, double q2, int up_or_dn) 
{
    double k2;
    if ( up_or_dn ==  1 )
        k2 = 4; // 2*q ==> 4*q2
    else if ( up_or_dn == -1 )
        k2 = 0.25; // 0.5*q ==> 0.25*q2
    else {
        throw std::invalid_argument("up_or_dn must be -1 or 1");
    }

    double pdf1old = pdf->xfxQ2(id1,x1,q2);
    double pdf2old = pdf->xfxQ2(id2,x2,q2);
    double pdf1new = pdf->xfxQ2(id1,x1,k2*q2);
    double pdf2new = pdf->xfxQ2(id2,x2,k2*q2);
    double weight = (pdf1new * pdf2new) / (pdf1old * pdf2old);

    return weight;
}