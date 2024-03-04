import sys, os
import ROOT


def main():

	hist_list = []
	hist_list.append(ROOT.TH1F("h_PDFWeights_factWeightsRMS_up","PDFWeights_factWeightsRMS_up",50,0.4,1.5,))  	#0 
	hist_list.append(ROOT.TH1F("h_PDFWeights_factWeightsRMS_down","PDFWeights_factWeightsRMS_down",50,0.5,2.0)) #1
	hist_list.append(ROOT.TH1F("h_PDFWeights_alphas","PDFWeights_alphas",50,0.12,0.16,))							#2
	hist_list.append(ROOT.TH1F("h_PDFWeights_varWeightsRMS","PDFWeights_varWeightsRMS",50,0.9,1.1,))			#3
	hist_list.append(ROOT.TH1F("h_PDFWeights_varWeightsErr","PDFWeights_varWeightsErr",50,0.0,0.25,))			#4
	c = ROOT.TCanvas("c","", 1000,1000)

	"""
		vars to plot
		PDFWeights_factWeightsRMS_up
		PDFWeights_factWeightsRMS_down
		PDFWeights_alphas
		PDFWeights_varWeightsRMS
		PDFWeights_varWeightsErr
	"""

	input_root = "/Users/ethan/Documents/rootFiles/clusteringAnalyzer_QCDMC2000toInf_2016_nom_output.root"
	f = ROOT.TFile.Open(input_root)
	tree = f.Get("clusteringAnalyzerAll_nom/tree_nom")
	for event in tree:
		hist_list[0].Fill(event.PDFWeights_factWeightsRMS_up)
		hist_list[1].Fill(event.PDFWeights_factWeightsRMS_down)
		hist_list[2].Fill(event.PDFWeights_alphas)
		hist_list[3].Fill(event.PDFWeights_varWeightsRMS)
		hist_list[4].Fill(event.PDFWeights_varWeightsErr)
	for hist in hist_list:
		hist.Draw("HIST")

		c.SaveAs(hist.GetName() + ".png")
if __name__=="__main__":
	main()