using std::cout, std::endl,std::string;
using namespace RooFit;
void examplews(){
    gSystem->Load("libHiggsAnalysisCombinedLimit.so");

    string start_ws = "/uscms/home/cannaert/nobackup/Combine/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/SuuToChiChi_FullyHadronic/input_wspace/";
    string input_root_path = "linearized_root/";

    string systematic = "nom";
    string year = "2018";
    string signal_label = "SuuToChiChi_MSuu8TeV_MChi3TeV"; // use this format here for outputting the linearized signal models


    /*
    TFile *fInputRoot = new TFile((input_root_path+"linear_"+ year+ ".root").c_str());  // get SR/CR BR/data histograms
    TFile *fInputRoot_sig = new TFile((input_root_path+"signal/linear_"+signal_label+"_"+ year+ ".root").c_str());  // get SR/CR signal histograms
    */
    TFile *fOut = new TFile( ("param_"+signal_label +"_ws.root").c_str(),"RECREATE");  // create output file where workspace will be
    RooWorkspace wspace("wspace","wspace");

    // maximum and minium of the MdiSJ_MSJ_uw (= unwrapped M_diSJ-M_SJ ) hist, these are simply bin numbers, not an observable


    const int nbins = 4;    // this is only 4 now for testing purposes
    double xmin = 200.;     
    double xmax = 1000.;
    double xbins[5] = {200.,400.,600.,800.,1000.};
    // Output file and workspace

    /*
    TH1F *h_input_QCD_SR   =  (TH1F*)fInputRoot->Get( "SR/QCD");
    TH1F *h_input_QCD_CR   =  (TH1F*)fInputRoot->Get( "CR/QCD");

    TH1F *h_input_TTbar_SR =  (TH1F*)fInputRoot->Get( "SR/TTbar");
    TH1F *h_input_TTbar_CR =  (TH1F*)fInputRoot->Get( "CR/TTbar" );

    TH1F *h_input_data_CR =  (TH1F*)fInputRoot->Get( "CR/data"  );
    TH1F *h_input_data_SR =  (TH1F*)fInputRoot->Get( "SR/data");

    TH1F *h_input_sig_CR =  (TH1F*)fInputRoot_sig->Get( "CR/sig"  );
    TH1F *h_input_sig_SR =  (TH1F*)fInputRoot_sig->Get( "SR/sig");
    */
    // need to make each of these histograms into new ones with one 4 bins for testing purposes

    RooRealVar MdiSJ_MSJ_uw("MdiSJ_MSJ_uw","Unwrapped M_{diSJ} vs avg M_{SJ}", 200., xmin,xmax);
    RooArgList vars(MdiSJ_MSJ_uw);   
    std::cout << "created RooRealVar" << std::endl;

    // define the bin parameter here - the unwrapped SJ vs diSJ bin number (0-440)
    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// Signal Region ////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    //// IMPORTANT: 'true' QCD means the corrected background prediction we're trying to make, this is NOT the QCD MC, it is the floating parameter

    ///  get the unwrapped 2D histograms 
    TH1F data_obs_SR("data_obs_SR_","Data observed in signal region",nbins,xbins);  //set this manually for just 4 bins 
    TH1F signal_SR("signal_SR_","Signal expected in signal region",nbins,xbins);
    TH1F QCD_MC_SR("QCD_MC_SR_","QCD expected in signal region",nbins,xbins);
    TH1F TTbar_MC_SR("TTbar_MC_SR_","TTbar expected in signal region",nbins,xbins);

    std::cout << "Initialized SR Histograms" << std::endl;

    RooArgList true_QCD_SR_bins; // these will be freely floating, need to create rateparamters for each 
    //these are all constant and to be used for the RooFormulaVar in the CR
    RooArgList QCD_MC_SR_bins;
    RooArgList TTbar_MC_SR_bins;
    std::vector<std::string> names = {"true_QCD_SR_bin1","true_QCD_SR_bin2","true_QCD_SR_bin3","true_QCD_SR_bin4"};
    double signal_SR_test[4] = {0,2,7,2};
    double QCD_MC_SR_test[4]  =  {12,20,46,22};
    double TTbar_MC_SR_test[4] = {2,2,3,1};
    double data_obs_SR_test[4] = {15,25,51,26}; 
    for(int iii=0; iii<nbins; iii++)
    {
        /*
        data_obs_SR.SetBinContent(iii, h_input_data_SR->GetBinContent(iii)); 
        signal_SR.SetBinContent(iii, h_input_sig_SR->GetBinContent(iii));
        QCD_MC_SR.SetBinContent(iii, h_input_QCD_SR->GetBinContent(iii));
        TTbar_MC_SR.SetBinContent(iii, h_input_TTbar_SR->GetBinContent(iii));

        true_QCD_SR_bins.add(RooRealVar(  ("true_QCD_SR_bins"+std::to_string(iii)).c_str(), ("'True' QCD yield in signal region, bin "+std::to_string(iii)).c_str(),h_input_data_SR->GetBinContent(iii),0,500)); //allowed to float between 0 and 500
        QCD_MC_SR_bins.add(RooRealVar(  ("QCD_MC_SR_bin"+std::to_string(iii)).c_str(), ("QCD MC yield in signal region, bin "+std::to_string(iii)).c_str(),QCD_MC_SR->GetBinContent(iii)));    // fixed value
        */
        data_obs_SR.SetBinContent(iii+1,data_obs_SR_test[iii] ); 
        signal_SR.SetBinContent(iii+1, signal_SR_test[iii]);
        QCD_MC_SR.SetBinContent(iii+1, QCD_MC_SR_test[iii]);
        TTbar_MC_SR.SetBinContent(iii+1, TTbar_MC_SR_test[iii]);

        RooRealVar * true_QCD_bin_ = new RooRealVar(  ("true_QCD_SR_bin"+ std::to_string(iii+1)).c_str(), ("True Number of QCD Events in the SR, bin "+std::to_string(iii+1)).c_str(),QCD_MC_SR_test[iii],0,500);
 
        true_QCD_SR_bins.add(*true_QCD_bin_); //allowed to float between 0 and 500
        RooRealVar * QCD_MC_SR_bin_ = new RooRealVar(  ("QCD_MC_SR_bin"+std::to_string(iii+1)).c_str(), ("QCD MC yield in signal region, bin "+std::to_string(iii+1)).c_str(),QCD_MC_SR.GetBinContent(iii+1));
        QCD_MC_SR_bins.add(*QCD_MC_SR_bin_); //allowed to float between 0 and 500

        //std::cout << " GetBinContent gives " <<  data_obs_SR.GetBinContent(iii+1) << std::endl;
    }


    RooDataHist data_hist_SR("data_obs_SR","Data observed",vars,&data_obs_SR);   //associating the histogram data here with the variables in RooArgList, how does this manifest itself??
    RooDataHist signal_hist_SR("signal_SR","signal (data observed)",vars,&signal_SR);
    RooDataHist TTbar_MC_hist_SR("TTbar_MC_SR","TTbar",vars,&TTbar_MC_SR);
    
    RooParametricHist p_QCD_SR("true_QCD_SR", "'True' QCD PDF in signal region",MdiSJ_MSJ_uw,true_QCD_SR_bins,data_obs_SR);
    RooAddition p_QCD_SR_norm("true_QCD_SR_norm","Total 'true' events from QCD in signal region",true_QCD_SR_bins);//      SEG FAULT
    //////// SR imported parameters ////////
    
    wspace.import(data_hist_SR);       // obs data SR
    wspace.import(signal_hist_SR);     // signal MC SR
    wspace.import(TTbar_MC_hist_SR);    // TTbar MC SR

    wspace.import(p_QCD_SR);           // "true" SR QCD pdf, floating RooRealVar    // SEG FAULT 
    wspace.import(p_QCD_SR_norm,RooFit::RecycleConflictNodes());                    // SEG FAULT

    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////// Control Region ///////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    
    // initialize and set input unwarpped 2D histograms 
    TH1F data_obs_CR("data_obs_CR_","Data observed in control region",nbins,xbins);
    TH1F signal_CR("signal_CR_","Signal expected in control region",nbins,xbins);
    TH1F QCD_MC_CR("QCD_MC_CR_","QCD expected in control region",nbins,xbins);
    TH1F TTbar_MC_CR("TTbar_MC_CR_","TTbar expected in control region",nbins,xbins);

    double signal_CR_test[4] = {1,1,2,0};
    double QCD_MC_CR_test[4]  =  {22,36,61,35};
    double TTbar_MC_CR_test[4] = {1,1,0,0};
    double data_obs_CR_test[4] = {25,35,65,36};

    RooArgList QCD_MC_CR_bins;
    RooArgList TTbar_MC_CR_bins;
    for(int iii=0; iii<nbins; ++iii)
    {
        /*
        data_obs_CR->SetBinContent(iii,h_input_data_CR->GetBinContent(iii));
        signal_CR.SetBinContent(iii, h_input_sig_CR->GetBinContent(iii));
        QCD_MC_CR.SetBinContent(iii, h_input_QCD_CR->GetBinContent(iii));
        TTbar_MC_CR.SetBinContent(iii, h_input_TTbar_CR->GetBinContent(iii));

        QCD_MC_CR_bins.add(RooRealVar(  ("QCD_MC_CR_bin"+std::to_string(iii).c_str(), ("QCD MC yield in control region, bin "+std::to_string(iii).c_str(),QCD_MC_CR->GetBinContent(iii)));    // fixed value
        */
        data_obs_CR.SetBinContent(iii+1,data_obs_CR_test[iii]);
        signal_CR.SetBinContent(iii+1,signal_CR_test[iii] );
        QCD_MC_CR.SetBinContent(iii+1,QCD_MC_CR_test[iii] );
        TTbar_MC_CR.SetBinContent(iii+1,TTbar_MC_CR_test[iii] );
        
        RooRealVar * bin_ = new RooRealVar(("QCD_MC_CR_bin"+std::to_string(iii+1)).c_str(), ("QCD MC yield in control region, bin "+std::to_string(iii+1)).c_str(),QCD_MC_CR.GetBinContent(iii+1) );
        QCD_MC_CR_bins.add(*bin_);  
    }


    // create a RooDataHists out of the CR observed events, CR signal MC, and CR TTbar MC
    RooDataHist data_hist_CR("data_obs_CR","Data observed CR",vars,&data_obs_CR);
    RooDataHist signal_hist_CR("signal_hist_CR","signal MC in CR",vars,&signal_CR);
    RooDataHist TTbar_MC_hist_CR("TTbar_MC_hist_CR","TTbar MC in CR",vars,&TTbar_MC_CR);

    std::cout << std::endl;
    // these are the formulae that represent the total number of observed events in each control region bin
    RooArgList true_QCD_CR_bins;
    for(int iii=0; iii<nbins; ++iii)
    {
        RooFormulaVar *true_QCD_CR_form_ = new RooFormulaVar( ("true_QCD_CR_bin"+std::to_string(iii+1)).c_str(),("true number of events in control region, bin "+std::to_string(iii+1)).c_str(),
        "@0*(@1/@2)",RooArgList(true_QCD_SR_bins[iii],QCD_MC_CR_bins[iii], QCD_MC_SR_bins[iii]  ));
        true_QCD_CR_bins.add(*true_QCD_CR_form_);

        // question here - is this the correct way to implement something like this? If the QCD MC SR/CR histograms are varied
        // that will not be reflected here because these parameters are not given to the data card
    }
    RooParametricHist p_QCD_CR("true_QCD_CR", "True QCD PDF in control region",MdiSJ_MSJ_uw,true_QCD_CR_bins,data_obs_CR);
    RooAddition p_QCD_CR_norm("true_QCD_CR_norm","Total number of observed events in control region",true_QCD_CR_bins); //  SEG FAULT


    //////// CR imported parameters ////////
    wspace.import(data_hist_CR);       //observed events
    wspace.import(signal_hist_CR);     //signal events
    wspace.import(TTbar_MC_hist_CR);   //TTbar events

    wspace.import(p_QCD_CR);            // "true" CR QCD pdf, RooFormulaVar     SEG FAULT
    wspace.import(p_QCD_CR_norm,RooFit::RecycleConflictNodes());            //    SEG FAULT


    //////////////////////////////////////////////////////////////
    fOut->cd();
    wspace.Write();
    /*
    fInputRoot->Close();
    fInputRoot_sig->Close();
    */
    return;
}
