// usage:: change the "hists" vector below with the name of the histograms to include
// this creates data/MC (combined) stack plots for each year for a given histogram name
// this uses processed root files
// WARNING: not debugged 



template <typename T> std::vector<T> get_histograms(std::vector<std::string> fnames, std::string hist_name)
{


    std::vector<T> return_hists;
    std::cout <<fnames.size() << " files found. " << std::endl;

    for(auto iii = fnames.begin();iii<fnames.end();iii++)
    {
      TFile * f1 = new TFile((*iii).c_str(), "READ" ); // open TFile for each fname
      return_hists.push_back( (T) f1->Get(  (hist_name).c_str() )  );
      //std::cout << "File: " << typeid((T)(*iii)->Get( ("nom_/" + hist_name).c_str() )).name() << " " << std::endl;
    }
    std::cout << std::endl;
    return return_hists;  // returns list of histograms 
}

template <typename T> T combine_histograms(std::vector<T> _hists, double weights[])
{

  T first_hist_scaled = T(_hists[0]);
  double original_events = first_hist_scaled->Integral();

  first_hist_scaled->Scale(weights[0]);

  T comb_hist = T(first_hist_scaled);
  int counter = 0;
  for(auto iii = _hists.begin() + 1;iii<_hists.end();iii++)
  {

    original_events = (*iii)->Integral();
    T dummy_hist = T(*iii);
    dummy_hist->Scale(weights[counter+1]);
    //(*iii)->Scale(weights[counter+1]);
    comb_hist->Add(dummy_hist);
    counter++;
  }
  return comb_hist;
}

void createDataToMCRatioStack(std::string year, std::string hist_name){

    
    std::string infilePaths = "/Users/ethan/Documents/plots/ANPlots/";
    TCanvas *can       = new TCanvas("","",1150,1000);


    std::vector<std::string> QCDFiles = { ("QCDMC1000to1500_"+year + "_processed.root"  ).c_str(),
      ("QCDMC1000to1500_"+year + "_processed.root"  ).c_str(),
      ("QCDMC1500to2000_"+year + "_processed.root"  ).c_str()};

    std::vector<std::string> TTbarFiles =  {("TTToHadronicMC_"+year + "_processed.root"  ).c_str(),
      ("TTToSemiLeptonicMC_"+year + "_processed.root"  ).c_str(),
      ("TTToLeptonicMC_"+year + "_processed.root"  ).c_str()};
    std::vector<std::string> STFiles = {("ST_t-channel-top_inclMC_"+year + "_processed.root"  ).c_str(),
      ("ST_t-channel-antitop_inclMC_"+year + "_processed.root"  ).c_str(),
      ("ST_s-channel-hadronsMC_"+year + "_processed.root"  ).c_str(),
      ("ST_s-channel-leptonsMC_"+year + "_processed.root"  ).c_str(),
      ("ST_tW-antiTop_inclMC_"+year + "_processed.root"  ).c_str(),
      ("ST_tW-top_inclMC_"+year + "_processed.root"  ).c_str()  };

    double QCD_weights[3];
    double TTbar_weights[3];
    double ST_weights[6];

    std::vector<std::string> dataFiles;
    if (year == "2015")
    {
      dataFiles = {"dataB-ver2_","dataC-HIPM_","dataD-HIPM_","dataE-HIPM_","dataF-HIPM_"};
      QCD_weights = {1.578683216,0.2119142341,0.08568186031};
      TTbar_weights = {0.075592,0.05395328118,0.0459517611};
      ST_weights = {0.0409963154,0.05673857623,0.04668187234,0.01323030083,0.2967888696,0.2962796522};
    }
    else if(year == "2016")
    {
      dataFiles = {"dataF_", "dataG_", "dataH_"};
      QCD_weights = {1.482632755,0.195224041,0.07572795371};
      TTbar_weights = {0.05808655696,0.05808655696,0.03401684391};
      ST_weights = {0.03607115071,0.04102705994,0.03564988679,0.01149139097,0.2301666797,0.2355829386};
    }
    else if(year == "2017")
    { 
      dataFiles = {"dataB_","dataC_","dataD_","dataE_", "dataF_"};
      QCD_weights = {3.126481451,0.3197450474,0.14306915};
      TTbar_weights = {0.06651018525,0.04264829286,0.03431532926};
      ST_weights = {0.03494669125,0.04238814865,0.03985938616,0.01117527734,0.2556495594,0.2563403788};
    }
    else if(year == "2018")
    {
      dataFiles = {"dataA_","dataB_","dataC_","dataD_"};
      QCD_weights = {4.407417122,0.5425809983,0.2277769275};
      TTbar_weights = {0.06588049107,0.04563489275,0.03617828025};
      ST_weights = {0.03859114659,0.03606630944,0.04102795437,0.01155448784,0.2700032391,0.2625270613};
    }
    else{std::cout << "ERROR: incorrect year." << std::endl;}


    std::vector<TH1F*> QCD_hists   = get_histograms(QCDFiles,  hist_name);
    std::vector<TH1F*> TTbar_hists = get_histograms(TTbarFiles, hist_name);
    std::vector<TH1F*> ST_hists    = get_histograms(STFiles, hist_name);

    TH1F * h1 = combine_histograms(QCD_hists,QCD_weights);
    TH1F * h2 = combine_histograms(TTbar_hists,TTbar_weights);
    TH1F * h3 = combine_histograms(ST_hists, ST_weights);

    double weights_data[20];
    std::fill_n(weights_data, 20, 1.0); //dummy weights for data
    std::vector<TH1F*> allDataHists = get_histograms(dataFiles, weights_data )
    TH1F * data = combine_histograms(allDataHists); /// merged data

    gStyle->SetOptStat(0);
    gPad->SetLeftMargin(0.18);
    can->SetTickx(1);
    can->SetTicky(1);
    
    TPad *pad1 = new TPad("pad1", "pad1", 0.00, 0.33, 1.00, 1.00);
    TPad *pad2 = new TPad("pad2", "pad2", 0.00, 0.00, 1.00, 0.33);

    THStack *hs = new THStack("hs","");
    THStack *hs1 = new THStack("hs1","");
    
    pad1->SetBottomMargin(0.00001);
    pad1->SetBorderMode(0);
    pad1->SetLeftMargin(0.14);
    pad1->SetTickx(1);
    pad1->SetTicky(1);
    pad2->SetTopMargin(0.00001);
    pad2->SetBottomMargin(0.4);
    pad2->SetBorderMode(0);
    pad2->SetLeftMargin(0.14);
    pad2->SetTickx(1);
    pad2->SetTicky(1);
    gStyle->SetOptTitle(kFALSE);
    pad1->Draw();
    pad2->Draw();
    pad1->cd();

   THStack *hstack = new THStack("hstack","Scaling hstack");
   //TH1F *data = new TH1F("data","",30,0,3);

   //contributions are h1-h4
   /*
   TH1F *h1   = new TH1F("h1","",30,0,3);
   TH1F *h2   = new TH1F("h2","",30,0,3);
   TH1F *h3   = new TH1F("h3","",30,0,3);
   TH1F *h4   = new TH1F("h4","",30,0,3);
    */
   //data->FillRandom("gaus",22500);
   data->Draw("e");
   data->SetMarkerStyle(20);
   data->SetMarkerSize(1.2);
   data->SetLineColor(kBlack);
   data->GetYaxis()->SetTitle("Events ");
   //data->GetYaxis()->SetTitleOffset(1.5);
   data->GetXaxis()->SetTitleFont(42);
   data->GetXaxis()->SetTitleSize(0.04);
   data->GetYaxis()->SetLabelSize(0.04);
   data->GetYaxis()->SetTitleFont(42);
   data->GetYaxis()->SetTitleSize(0.04);


   //h1->FillRandom("gaus",20000);
   h1->SetFillColor(kRed);
   h1->SetMarkerStyle(21);
   h1->SetMarkerColor(kRed);

   //h2->FillRandom("gaus",1500);
   h2->SetFillColor(kBlue);
   h2->SetMarkerStyle(21);
   h2->SetMarkerColor(kBlue);

   //h3->FillRandom("gaus",1000);
   h3->SetFillColor(kGreen);
   h3->SetMarkerStyle(21);
   h3->SetMarkerColor(kGreen);

   hstack->Add(h3);
   hstack->Add(h2);
   hstack->Add(h1);
   hstack->Add(h4);

   //double stack_total = h1->Integral() +h2->Integral()+ h3->Integral()+ h4->Integral();
   //hstack->Scale(1./stack_total);
   //hstack->Scale(stack_total);

  hstack->Draw(); // this is the stack
  data->Draw("e, same");

  TH1F *h = new TH1F(*((TH1F *)(hstack->GetStack()->Last()))); // last item of the stack?

  double N_of_bkg   = h->Integral(7, 30);
  double N_of_data = data->Integral(7, 30);

    //std::cout<<" N of bkg "<<N_of_bkg<<", and "<<"N of data: "<<N_of_data<<". "<<"Ratio Data/SM: "<<N_of_data/N_of_bkg<<std::endl;

    //h->Scale(N_of_data/N_of_bkg);


    TLegend *leg = new TLegend(0.62,0.62,0.76,0.84,NULL,"brNDC");
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);
    leg->SetTextFont(42);
    leg->SetTextSize(0.03230543);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);
    leg->AddEntry(data,"Data","P");
    leg->AddEntry(h1 ,"QCD","f");
    leg->AddEntry(h2,"TTbar","f");
    leg->AddEntry(h3,"ST","f");
    leg->Draw();

    can->Update();


  pad2->cd();
    // Calculating the sum manuly and then get the ratio plot.
    //TH1F* total1=(TH1F*) ttbar->Clone("total1");    
    //total1->Add(Wt);
    //TH1F* total2=(TH1F*) Zjet->Clone("total2");
    //total2->Add(Diboson);
    //TH1F* total3=(TH1F*) Mis_ID_lepton->Clone("total3");
    //total3->Add(total2);
    //TH1F* totalMc=(TH1F*) total1->Clone("totalMc");
    //totalMc->Add(total3);


    for(int l = 0; l< data->GetNbinsX(); l++) 
    {
      h4->SetBinContent(l+1, data->GetBinContent(l+1)/h->GetBinContent(l+1));
    }


    h4->SetLineColor(kPink+9);
    h4->GetXaxis()->SetTitle("m_{somthing} [GeV] ");
    h4->GetXaxis()->SetLabelSize(0.09);
    h4->GetXaxis()->SetTitleSize(0.12);
    h4->GetXaxis()->SetTickLength(0.08);
    h4->GetXaxis()->SetTitleOffset(1.163);

    h4->GetXaxis()->SetTitleFont(42);
    h4->GetYaxis()->SetTitle("Data/Mc");
    h4->GetYaxis()->SetLabelSize(0.09);
    h4->GetYaxis()->SetTitleSize(0.09);
    h4->GetYaxis()->SetTitleOffset(0.7);
    h4->GetYaxis()->SetNdivisions(404,kTRUE);
    h4->SetStats(false);
    h4->SetMaximum(1.3);
    h4->SetMinimum(0.7);
    h4->Draw("histo");

    TLine *line = new TLine();
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->SetLineColor(kBlack);
    line->DrawLine(h4->GetXaxis()->GetXmin(), 1  , h4->GetXaxis()->GetXmax(), 1  );
    can->SaveAs( (infilePaths + hist_name+ "_dataMC_RatioStack_" + region + "_"+ year + ".png").c_str()   );
}

void create_stack_ratio()
{
  std::vector<std::string> years = {"2015","2016","2017","2018"};
  std::vector<std::string> hists  = {"h_SJ_mass", "h_disuperjet_mass"};  // IMPORTANT: this is the hist name without the region on the end 
  std::vector<std::string> systematics = {"bTagSF","nom", "PUSF", "JEC", "JER", "topPt", "L1Prefiring", "pdf", "scale"};
  std::vector<std::string> regions = {"AT1b", "AT0b"}
  //std::vector<std::string> samples = {"QCDMC_","TTbarMC_","STMC_","data"};
  for(auto year = years.begin(); year != years.end();year++)
  {
    for(auto hist_name = hists.begin(); hist_name != hists.end();hist_name++)
    {
      for(auto region = regions.begin(); region!=regions.end();region++)
      {
        createDataToMCRatioStack(year,hist_name, region);
      }
      
    }
  }


}


