using std::cout, std::endl,std::string;
using namespace RooFit;
void makeTestROOT(){
    gSystem->Load("libHiggsAnalysisCombinedLimit.so");

    string systematic = "nom";
    string year = "2018";
    string signal_label = "SuuToChiChi_MSuu8TeV_MChi3TeV"; // use this format here for outputting the linearized signal models

    TFile *fOut = new TFile( ("inputHists_"+signal_label + "_" + year+ "_ws.root").c_str(),"RECREATE");  // create output file where workspace will be
    RooWorkspace wspace("wspace","wspace");

    const int nbins = 4;    // this is only 4 now for testing purposes
    double xmin = 200.;     
    double xmax = 1000.;
    double xbins[5] = {200.,400.,600.,800.,1000.};
    // Output file and workspace

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// Signal Region ////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    //// IMPORTANT: 'true' QCD means the corrected background prediction we're trying to make, this is NOT the QCD MC, it is the floating parameter

    ///  get the unwrapped 2D histograms 
    TH1F data_obs_SR("data_obs_SR","Data observed in the signal region",nbins,xbins);  //set this manually for just 4 bins 
    TH1F signal_SR("signal_SR","Signal expected in the signal region",nbins,xbins);
    TH1F QCD_MC_SR("QCD_MC_SR","QCD expected in the signal region",nbins,xbins);
    TH1F TTbar_MC_SR("TTbar_MC_SR","TTbar expected in the signal region",nbins,xbins);

    double signal_SR_test[4] = {0,2,7,2};
    double QCD_MC_SR_test[4]  =  {12,20,46,22};
    double TTbar_MC_SR_test[4] = {2,2,3,1};
    double data_obs_SR_test[4] = {15,25,51,26}; 
    for(int iii=0; iii<nbins; iii++)
    {
        data_obs_SR.SetBinContent(iii+1,data_obs_SR_test[iii] ); 
        signal_SR.SetBinContent(iii+1, signal_SR_test[iii]);
        QCD_MC_SR.SetBinContent(iii+1, QCD_MC_SR_test[iii]);
        TTbar_MC_SR.SetBinContent(iii+1, TTbar_MC_SR_test[iii]);

        RooRealVar * true_QCD_bin_ = new RooRealVar(  ("true_QCD_SR_bin"+ std::to_string(iii+1)).c_str(), ("True Number of QCD Events in the SR, bin "+std::to_string(iii+1)).c_str(),QCD_MC_SR_test[iii],0,500);
 
        true_QCD_SR_bins.add(*true_QCD_bin_); //allowed to float between 0 and 500
        RooRealVar * QCD_MC_SR_bin_ = new RooRealVar(  ("QCD_MC_SR_bin"+std::to_string(iii+1)).c_str(), ("QCD MC yield in signal region, bin "+std::to_string(iii+1)).c_str(),QCD_MC_SR.GetBinContent(iii+1));
        QCD_MC_SR_bins.add(*QCD_MC_SR_bin_); //allowed to float between 0 and 500
    }

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// Control Region ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    
    // initialize and set input unwarpped 2D histograms 
    TH1F data_obs_CR("data_obs_CR","Data observed in the control region",nbins,xbins);
    TH1F signal_CR("signal_CR","Signal expected in the control region",nbins,xbins);
    TH1F QCD_MC_CR("QCD_MC_CR","QCD expected in the control region",nbins,xbins);
    TH1F TTbar_MC_CR("TTbar_MC_CR","TTbar expected in the control region",nbins,xbins);

    double signal_CR_test[4] = {1,1,2,0};
    double QCD_MC_CR_test[4]  =  {22,36,61,35};
    double TTbar_MC_CR_test[4] = {1,1,0,0};
    double data_obs_CR_test[4] = {25,35,65,36};

    RooArgList QCD_MC_CR_bins;
    RooArgList TTbar_MC_CR_bins;
    for(int iii=0; iii<nbins; ++iii)
    {
        data_obs_CR.SetBinContent(iii+1,data_obs_CR_test[iii]);
        signal_CR.SetBinContent(iii+1,signal_CR_test[iii] );
        QCD_MC_CR.SetBinContent(iii+1,QCD_MC_CR_test[iii] );
        TTbar_MC_CR.SetBinContent(iii+1,TTbar_MC_CR_test[iii] );
    }

    fOut.Write();
    fOut.CLose();
    /*
    fInputRoot->Close();
    fInputRoot_sig->Close();
    */
    return;
}
