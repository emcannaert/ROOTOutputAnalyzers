using std::cout, std::endl, std::string;
void examplews(){
    // As usual, load the combine library to get access to the RooParametricHist
    gSystem->Load("libHiggsAnalysisCombinedLimit.so");


    string ws_path = "/Users/ethan/Documents/rootFiles/finalCombineFiles/combine_ws";

    // Output file and workspace
    TFile *fOut = new TFile("/Users/ethan/Documents/rootFiles/finalCombineFiles/combine_ws/param_ws.root","RECREATE");
    RooWorkspace wspace("wspace","wspace");

    const int nbins = 4;  // start with just 4 bins for testing purposes


}
