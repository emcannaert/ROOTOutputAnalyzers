#include <iostream>
#include <string>
#include "TLorentzVector.h"
#include "TRatioPlot.h"
#include "THStack.h"
#include "TRatioPlot.h"
using namespace std;

  // make ratio plots between XXXX and MC for 2018

  double SuuToChiChi_MSuu8TeV_Mchi3TeV_SF = 1.93E-02;
  double SuuToChiChi_MSuu5TeV_Mchi2TeV_SF = 8.67E-01;

  double QCD1000to1500_SF[4] = {1.578683216,1.482632755,3.126481451,4.407417122}; //TODO, 
  double QCD1500to2000_SF[4] = {0.2119142341,0.195224041,0.3197450474,0.5425809983}; //TODO
  double QCD2000toInf_SF[4] = {0.08568186031,0.07572795371,0.14306915,0.2277769275}; //TODO
  double h_TTToHadronic_SF[4] = {0.075592,0.05808655696,0.06651018525,0.06588049107}; //TODO
  double h_TTToSemiLeptonic_SF[4] = {0.05395328118,0.05808655696,0.04264829286,0.04563489275}; //TODO
  double h_TTTo2l2nu_SF[4] = {0.0459517611,0.03401684391,0.03431532926,0.03617828025}; //TODO

  double ST_t_channel_top_5f_SF[4] = {0.0409963154,0.03607115071,0.03494669125,0.03859114659}; //TODO
  double ST_t_channel_antitop_5f_SF[4] = {0.05673857623,0.04102705994,0.04238814865,0.03606630944}; //TODO
  double ST_s_channel_4f_hadrons_SF[4] = {0.04668187234,0.03564988679,0.03985938616,0.04102795437}; //TODO
  double ST_s_channel_4f_leptons_SF[4] = {0.01323030083,0.01149139097,0.01117527734,0.01155448784}; //TODO
  double ST_tW_antitop_5f_SF[4] = {0.2967888696,0.2301666797,0.2556495594,0.2700032391}; //TODO
  double ST_tW_top_5f_SF[4] = {0.2962796522,0.2355829386,0.2563403788,0.2625270613}; //TODO

template <typename T> std::vector<T> get_histograms(std::vector<std::string> fnames, std::string hist_name)
{


    std::vector<T> return_files;
    std::cout <<fnames.size() << " files found. " << std::endl;

    for(auto iii = fnames.begin();iii<fnames.end();iii++)
    {
      TFile * f1 = new TFile((*iii).c_str(), "READ" ); // open TFile for each fname
      return_files.push_back( (T) f1->Get(  (hist_name).c_str() )  );
      //std::cout << "File: " << typeid((T)(*iii)->Get( ("nom_/" + hist_name).c_str() )).name() << " " << std::endl;
    }
    std::cout << std::endl;
    return return_files;
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


// compare data and MC for a variable (histName) given data and MC files 
template <typename T> void create_ratio(std::vector<std::string> dataFiles, std::vector<std::string> MCFiles, std::string histName, std::string year, double weights[], std::string ratioName = "data/MC",std::string plotName = ""  )
{

  //double h_TTJets2500toInf_SF  = 0.00008408965681;
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);

  std::string plot_home = "/Users/ethan/Documents/plots/ANPlots/";
  if(plotName == "") plotName = histName;

  std::string getName = histName;

  double weights_data[20];
  std::fill_n(weights_data, 20, 1.0); //dummy weights for data

  std::cout << "Loading data files." << std::endl;
  std::vector<T>  h_data_hists  = get_histograms<T>(dataFiles, getName.c_str());
  std::cout << "Loading MC files." << std::endl;
  std::vector<T>  h_MC_hists    = get_histograms<T>(MCFiles, getName.c_str());

  T  h_all_data    = combine_histograms<T>(h_data_hists,weights_data);
  std::cout << "Data integral is " << h_all_data->Integral() << std::endl;
  T  h_all_MC      = combine_histograms<T>(h_MC_hists,weights);
  std::cout << "MC integral is " << h_all_MC->Integral() << std::endl;

  h_all_data->SetTitle((plotName + ", data vs MC").c_str());

  auto ratioPlot = new TRatioPlot(h_all_data,h_all_MC);
  //h_BR_combined->Draw("HIST");
  ratioPlot->Draw("HIST,EP");
  ratioPlot->GetLowerRefYaxis()->SetTitle( ratioName.c_str() );
  ratioPlot->GetLowerRefGraph()->SetMaximum(2.);
  ratioPlot->GetUpperRefYaxis()->SetTitle("Events");
  std::cout << "Ratio plot saved to " <<  (plot_home + plotName +"_RatioPlot_"+ year+".png").c_str() <<std::endl;

  c1->SaveAs( (plot_home + plotName +"_"+ year+".png").c_str()); 

}

// create SR shape vs CR shape plots for a variable (histName) given a list of MC files
template <typename T> void compareSRCR(std::vector<std::string> MCFiles, std::string histName, std::string year, double weights[], std::string ratioName = "data/MC",std::string plotName = "", std::string region1="SR", std::string region2="CR"  )
{

  //double h_TTJets2500toInf_SF  = 0.00008408965681;
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);

  std::string plot_home = "/Users/ethan/Documents/plots/ANPlots/";
  if(plotName == "") plotName = histName;

  std::string getName1 = histName + "_"+ region1;
  std::string getName2 = histName + "_"+ region2;

  double weights_data[20];
  std::fill_n(weights_data, 20, 1.0); //dummy weights for data


  // get region1 hists
  std::vector<T>  h_region1_hists    = get_histograms<T>(MCFiles, getName1.c_str());

  // get region2 hists
  std::vector<T>  h_region2_hists    = get_histograms<T>(MCFiles, getName2.c_str());

  T  h_all_region1      = combine_histograms<T>(h_region1_hists,weights);
  T  h_all_region2      = combine_histograms<T>(h_region2_hists,weights);

  h_all_region1->SetTitle( (region1 + " " histName + " vs " + region2 + " " + histName + "(combined BR MC, "+ year+")").c_str()  );

  auto ratioPlot = new TRatioPlot(h_all_region1,h_all_region2);
  //h_BR_combined->Draw("HIST");
  ratioPlot->Draw("HIST,EP");
  ratioPlot->GetLowerRefYaxis()->SetTitle( ratioName.c_str() );
  ratioPlot->GetLowerRefGraph()->SetMaximum(2.);
  ratioPlot->GetUpperRefYaxis()->SetTitle("Events");
  std::cout << "Ratio plot saved to " <<  (plot_home + plotName +"_RatioPlot_"+ year+".png").c_str() <<std::endl;

  c1->SaveAs( (plot_home + plotName +"_"+ year+".png").c_str()); 

}






void make_cutflow_ratio_plots()
{



  std::vector<std::string> years = {"2015","2016","2017","2018"};

  for(auto year= years.begin();years!=years.end();years++)
  {

      // need to change this for different years
      std::vector<std::string> dataFiles = {"/Users/ethan/Documents/rootFiles/cutflowPlots/dataA_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/dataB_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/dataC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/dataD_"+ *year+ "_nom_CUTFLOW.root"};
      std::vector<std::string> MCFiles   = {"/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC1000to1500_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC1500to2000_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC2000toInf_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/TTToHadronicMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/TTToLeptonicMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/TTToSemiLeptonicMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_s-channel-hadronsMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_s-channel-leptonsMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_t-channel-antitop_inclMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_t-channel-top_inclMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_tW-antiTop_inclMC_"+ *year+ "_nom_CUTFLOW.root",
      "/Users/ethan/Documents/rootFiles/cutflowPlots/ST_tW-top_inclMC_"+ *year+ "_nom_CUTFLOW.root"};
      double weights[] = {QCD1000to1500_SF[3],QCD1500to2000_SF[3],QCD2000toInf_SF[3],h_TTToHadronic_SF[3],h_TTTo2l2nu_SF[3],h_TTToSemiLeptonic_SF[3],ST_s_channel_4f_hadrons_SF[3],
      ST_s_channel_4f_leptons_SF[3], ST_t_channel_antitop_5f_SF[3], ST_t_channel_top_5f_SF[3], ST_tW_antitop_5f_SF[3],ST_tW_top_5f_SF[3]};
      //double weights[20];
      //std::fill_n(weights, 20, 1.0);
      std::vector<std::string> histNames = {"h_nfatjets_semiRAW",
        "h_tot_HT_semiRAW",
        "h_nfatjets_semiRAW",
        "h_nfatjets_pre_semiRAW",
        "h_dijet_mass_semiRAW",
        "h_nDijet_pairs_semiRAW",
        "h_nTight_b_jets_semiRAW",
        "h_SJ_nAK4_300_semiRAW",
        "h_m_SJ1_AT1b",
        "h_m_SJ1_AT0b",
        "h_m_SJ1_SR",
        "h_m_SJ1_CR",
        "h_m_diSJ_SR",
        "h_m_diSJ_CR"
      };
      //std::string year = "2018";


      for(auto histName = histNames.begin(); histName < histNames.end(); histName++)
      {
        create_ratio<TH1F*>(dataFiles, MCFiles, *histName, *year, weights, "data/MC", *histName);
      }

      // regions to compare shapes
      std::string region1 = "SR";
      std::string region2 = "CR";


      std::vector<std::string> QCDFiles_processed   = { ("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC1000to1500_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC1500to2000_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/QCDMC2000toInf_"+*year+"_processed.root").c_str()}

      std:;vector<std::string> TTbarFiles_processed = {("/Users/ethan/Documents/rootFiles/processedRootFiles/TTJetsMCHT1200to2500_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/TTJetsMCHT2500toInf_"+*year+"_processed.root").c_str()};

      std:;vector<std::string> STFiles_processed = {("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_s-channel-hadronsMC_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_s-channel-leptonsMC_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_t-channel-antitop_inclMC_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_t-channel-top_inclMC_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_tW-antiTop_inclMC_"+*year+"_processed.root").c_str(),
        ("/Users/ethan/Documents/rootFiles/processedRootFiles/ST_tW-top_inclMC_"+*year+"_processed.root").c_str()};

  
      // want to make these with processed root files
      // VERY IMPORTANT: this must be the name of the histogram you want to compare without the region suffix (e.g. SJ_mass)
      std::string histNames_minus_region =
      {
        "h_SJ_mass",
        "h_disuperjet_mass"
      };

      for(auto histName_minus_region = histNames_minus_region.begin(); histName_minus_region < histNames_minus_region.end(); histName_minus_region++)
      {
        compareSRCR<TH1F*>(MCFiles, *histName, *year, weights, "SR MC shape/CR MC shape", *histName_minus_region ,"",region1, region2 );
      }


  }
   



}
