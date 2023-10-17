using std::cout, std::endl,std::string;
void interpolateRootFile(){
    // As usual, load the combine library to get access to the RooParametricHist

    string input_root_path = "/Users/ethan/Documents/rootFiles/finalCombineFiles/";
    string year = "2018";
    string region = "SR";
    // Output file and workspace
    TFile *fIn = new TFile((input_root_path+"combine_"+ year+ "_"+ region + ".root").c_str(),"RECREATE");
    std::cout << "Opened root file" << endl;
    RooWorkspace wspace("wspace","wspace");

    // need to import CR and SR histograms
    TH1F *h_final_combine_hist=  (TH1F*)fIn->Get("QCD_SR/QCD");

    cout << "Trying to print the histogram" << endl;
    for(int iii = 0; iii<h_final_combine_hist->GetNbinsX(); ++iii)
    {
        std::cout << "In loop" << std::endl;
        cout << iii << " " << h_final_combine_hist->GetBinContent(iii) <<endl;
    }
    const int nbins = 4;  // start with just 4 bins for testing purposes, choose first four fins of the linear plot

    fIn->Close();
    fIn->Delete();

    int d = 3;
    int e = d;
    cout << d << " " << e << endl;
    e = 4;
    cout << d << " " << e << endl;
    d = 6;
    cout << d << " " << e << endl;
    return;
}
