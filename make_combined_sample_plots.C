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

  double h_TTJetsMCHT1200to2500_SF[4] = {0.002722324842,0.002255554525,0.002675947994,0.003918532089};
  double h_TTJetsMCHT2500toInf_SF[4]  = {0.00005679863673,0.00005025384367,0.00005947217017,0.00008408965681};
  double ST_t_channel_top_5f_SF[4] = {0.0409963154,0.03607115071,0.03494669125,0.03859114659}; //TODO
  double ST_t_channel_antitop_5f_SF[4] = {0.05673857623,0.04102705994,0.04238814865,0.03606630944}; //TODO
  double ST_s_channel_4f_hadrons_SF[4] = {0.04668187234,0.03564988679,0.03985938616,0.04102795437}; //TODO
  double ST_s_channel_4f_leptons_SF[4] = {0.01323030083,0.01149139097,0.01117527734,0.01155448784}; //TODO
  double ST_tW_antitop_5f_SF[4] = {0.2967888696,0.2301666797,0.2556495594,0.2700032391}; //TODO
  double ST_tW_top_5f_SF[4] = {0.2962796522,0.2355829386,0.2563403788,0.2625270613}; //TODO

template <typename T> std::vector<T> get_histograms(std::vector<std::string> fnames, std::string hist_name, std::string folderName)
{

    std::string folder_str = "";
    if folderName != "":
      folder_str = folderName;
    std::vector<T> return_files;
    std::cout <<fnames.size() << " files found. " << std::endl;

    for(auto iii = fnames.begin();iii<fnames.end();iii++)
    {
      TFile * f1 = new TFile((*iii).c_str(), "READ" ); // open TFile for each fname
      return_files.push_back( (T) f1->Get(  (folderName+hist_name).c_str() )  );
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


template <typename T> void create_plots(std::vector<std::string> dataFiles, std::vector<std::string> QCDFiles, std::vector<std::string> TTbarFiles, std::vector<std::string> STFiles, double QCD_weights[], double TTbar_weights[], double ST_weights[], std::string histName, std::string year,std::string plotName = "", std::string folderName = ""  )
{

  //double h_TTJets2500toInf_SF  = 0.00008408965681;
  TCanvas *c1 = new TCanvas("c1","",400,20, 2000,1500);

  std::string plot_home = "/Users/ethan/Documents/plots/ANPlots/";
  if(plotName == "") plotName = histName;

  std::string getName = histName;

  double weights_data[20];
  std::fill_n(weights_data, 20, 1.0); //dummy weights for data



  std::vector<T>  h_TTbar_hists    = get_histograms<T>(TTbarFiles, getName.c_str(), folderName);
  T  h_all_TTbar_MC    = combine_histograms<T>(h_TTbar_hists,TTBar_weights);
  h_all_TTbar_MC->SetTitle((plotName + " (" +*year+  "combined TTbar)").c_str());
  h_all_TTbar_MC->Draw("HIST");
  c1->SaveAs( (plot_home + plotName +"_TTbar_combined_"+ year+".png").c_str());
  if(plotName == "top_pt_weight")continue; // these are only saved for top datasets
  //std::cout << "Loading data files." << std::endl;
  //std::vector<T>  h_data_hists  = get_histograms<T>(dataFiles, getName.c_str());
  //std::cout << "Loading MC files." << std::endl;
  std::vector<T>  h_QCD_hists    = get_histograms<T>(QCDFiles, getName.c_str()), folderName;
  std::vector<T>  h_ST_hists    = get_histograms<T>(STFiles, getName.c_str(), folderName);


  //T  h_all_data    = combine_histograms<T>(h_data_hists,weights_data);
  //std::cout << "Data integral is " << h_all_data->Integral() << std::endl;
  T  h_all_QCD_MC      = combine_histograms<T>(h_QCD_hists,QCD_weights);
  T  h_all_ST_MC       = combine_histograms<T>(h_ST_hists,ST_weights);

  //std::cout << "MC integral is " << h_all_MC->Integral() << std::endl;

  //h_all_data->SetTitle((plotName + " (" +*year+  "data)").c_str());
  h_all_QCD_MC->SetTitle((plotName + " (" +*year+  "combined QCD)").c_str());
  h_all_ST_MC->SetTitle((plotName + " (" +*year+  "combined ST)").c_str());

  h_all_QCD_MC->Draw("HIST");
  c1->SaveAs( (plot_home + plotName +"_QCD_combined_"+ year+".png").c_str()); 
 
  h_all_ST_MC->Draw("HIST");
  c1->SaveAs( (plot_home + plotName +"_ST_combined_"+ year+".png").c_str()); 


  // create combined BR plot
  T h_allBR = (T)h_all_QCD_MC->Clone();
  h_allBR->Add(h_all_TTbar_MC);
  h_allBR->Add(h_all_ST_MC);
  h_allBR->SetTitle((plotName + " (" +*year+  "combined BRs)").c_str());
  h_allBR->Draw("HIST");
  c1->SaveAs( (plot_home + plotName +"_allBR_"+ year+".png").c_str()); 

  return;
}


void make_combined_sample_plots()
{

  std::vector<std::string> years = {"2015","2016","2017","2018"};


  


  //double weights[20];
  //std::fill_n(weights, 20, 1.0);


  // histograms to make from skimmed files
  std::vector<std::string> histNames = 
  {
    "bTag_eventWeight_nom",
    "PU_eventWeight_nom",
    "prefiringWeight_nom",
    "top_pt_weight",
    "AK8_JER",
    "h_tot_HT_semiRAW"
  };



  ///// histograms to make from processed files
  std::vector<std::string> histNames_2D = 
  {
    "h_MSJ_mass_vs_MdSJ_SR",
    "h_MSJ_mass_vs_MdSJ_CR",
    "h_MSJ_mass_vs_MdSJ_AT1b",
    "h_MSJ_mass_vs_MdSJ_AT0b"
  };
  std::vector<std::string> histNames_proc = 
  {
    "h_SJ_mass_SR",
    "h_disuperjet_mass_SR",
     "h_SJ_mass_CR",
    "h_disuperjet_mass_CR",
     "h_SJ_mass_AT1b",
    "h_disuperjet_mass_AT1b",
     "h_SJ_mass_AT0b",
    "h_disuperjet_mass_AT0b"
  };
  //std:;string plotName = "";  // get from histName
  std::string year = "2018";
  int iii = 0;
  for(auto year = years.begin();year!= years.end();year++)
  {

    std::vector<std::string> dataFiles;

/*
         if(*dataYear == "2015")
         {
            dataBlocks = {"dataB-ver2_","dataC-HIPM_","dataD-HIPM_","dataE-HIPM_","dataF-HIPM_"}; // dataB-ver1 not present
         }
         else if(*dataYear == "2016")
         {
            dataBlocks = {"dataF_", "dataG_", "dataH_"};
         }
         else if(*dataYear == "2017")
         {
            dataBlocks = {"dataB_","dataC_","dataD_","dataE_", "dataF_"};
         }
         else if(*dataYear == "2018")
         {
            dataBlocks = {"dataA_","dataB_","dataC_","dataD_"};
         }


*/
    double QCD_weights[] = {QCD1000to1500_SF[iii],QCD1500to2000_SF[iii],QCD2000toInf_SF[iii]};
    double TTbar_weights[] = {h_TTJetsMCHT1200to2500_SF[iii],h_TTJetsMCHT2500toInf_SF[iii]};
    double ST_weights[] = {ST_s_channel_4f_hadrons_SF[iii], ST_s_channel_4f_leptons_SF[iii], ST_t_channel_antitop_5f_SF[iii], ST_t_channel_top_5f_SF[iii], ST_tW_antitop_5f_SF[iii],ST_tW_top_5f_SF[iii]};

    if (year == "2015")
    {
      dataFiles  = {"/Users/ethan/Documents/rootFiles/cutflowPlots/dataB-ver2_2015_nom_CUTFLOW.root",
                    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataC-HIPM_2015_nom_CUTFLOW.root",
                    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataD-HIPM_2015_nom_CUTFLOW.root",
                    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataE-HIPM_2015_nom_CUTFLOW.root",
                    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataF-HIPM_2015_nom_CUTFLOW.root"};
    }
    else if (year == "2016")
    {
        dataFiles = {"/Users/ethan/Documents/rootFiles/cutflowPlots/dataF_2016_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataG_2016_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataH_2016_nom_CUTFLOW.root"};
    }
    else if (year == "2017")
    {
        dataFiles = {"/Users/ethan/Documents/rootFiles/cutflowPlots/dataB_2017_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataC_2017_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataD_2017_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataE_2017_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataF_2017_nom_CUTFLOW.root"};
    }
    else if (year == "2018")
    {
        dataFiles = {"/Users/ethan/Documents/rootFiles/cutflowPlots/dataA_2018_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataB_2018_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataC_2018_nom_CUTFLOW.root",
    "/Users/ethan/Documents/rootFiles/cutflowPlots/dataD_2018_nom_CUTFLOW.root"};
    }
    else
    {
      std::cout << "ERROR: incorrect year" << std::endl;
      return;
    }

  std::vector<std::string> QCDFiles   = { ("/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC1000to1500_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC1500to2000_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/QCDMC2000toInf_"+*year+"_nom_CUTFLOW.root").c_str()}

  std:;vector<std::string> TTbarFiles = {("/Users/ethan/Documents/rootFiles/cutflowPlots/TTToHadronicMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/TTToLeptonicMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/TTToSemiLeptonicMC_"+*year+"_nom_CUTFLOW.root").c_str()};

  std:;vector<std::string> STFiles = {("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_s-channel-hadronsMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_s-channel-leptonsMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_t-channel-antitop_inclMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_t-channel-top_inclMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_tW-antiTop_inclMC_"+*year+"_nom_CUTFLOW.root").c_str(),
("/Users/ethan/Documents/rootFiles/cutflowPlots/ST_tW-top_inclMC_"+*year+"_nom_CUTFLOW.root").c_str()};




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

  

    // make combined/partially combined plots from cutflow files
    for(auto histName = histNames.begin(); histName < histNames.end(); histName++)
    {
      create_plots<TH1F*>(dataFiles, QCDFiles, TTbarFiles, STFiles, QCD_weights, TTbar_weights, ST_weights, *histName, *year, *histName, "");
    }





    // make combined/partially combined plots from processed files 
    std::string nomFolderName = "nom/"
    // I think the processed files will be within systematic folders, so plot names will have to have folder strings attached

    for(auto histName = histNames_proc .begin(); histName < histNames_proc.end(); histName++)
    {
      create_plots<TH2F*>(dataFiles, QCDFiles_processed, TTbarFiles_processed, STFiles_processed, QCD_weights, TTbar_weights, ST_weights, *histName, *year, *histName, nomFolderName);
    }

    for(auto histName = histNames_2D .begin(); histName < histNames_2D.end(); histName++)
    {
      create_plots<TH2F*>(dataFiles, QCDFiles_processed, TTbarFiles_processed, STFiles_processed, QCD_weights, TTbar_weights, ST_weights, *histName, *year, *histName, nomFolderName);
    }

    iii++;

  }



}
