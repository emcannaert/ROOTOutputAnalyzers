using std::cout, std::endl,std::string;
void interpolateRootFile(){
    // As usual, load the combine library to get access to the RooParametricHist

    string input_root_path = "/Users/ethan/Documents/rootFiles/fInputRootalCombineFiles/";
    string year = "2018";
    string region = "SR";

    
    // Output file and workspace
    TFile *fInputRoot = new TFile((input_root_path+"combine_"+ year+ "_"+ region + ".root").c_str());
    RooWorkspace wspace("wspace","wspace");

    // need to import CR and SR histograms
    TH1F *h_fInputRootal_combine_hist=  (TH1F*)fInputRoot->Get("QCD_SR/QCD");
    int NFilledBins = 0;
    for(int iii = 0; iii<h_fInputRootal_combine_hist->GetNbinsX(); ++iii)
    {
        double nCounts = h_fInputRootal_combine_hist->GetBinContent(iii);
        if((nCounts > 0) && (NFilledBins < 4))
        {   
            cout << iii << endl;
            NFilledBins++;
        }
    }
    const int nbins = 4;  // start with just 4 bins for testing purposes, choose first four fInputRoots of the linear plot

    fInputRoot->Close();
    //fInputRoot->Delete();


    return;
}
