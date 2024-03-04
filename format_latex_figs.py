import os,sys

def format_string(sample, caption, plot_name):
	sample_use = sample
	if sample == "ST_MC_All":
		sample_use = "combined, inclusive Single Top Quark"
	elif sample == "TTbarMC_All":
		sample_use = r"inclusive $t\bar{t}$"
	elif sample == "QCDMC_All":
		sample_use = "combined QCD multijet"


	print(r"\begin{figure}")
	print(r"\centering")
	print(r"\subfloat[]{\includegraphics[width = 3in]" + r"{plots/cutflow_plots/" + "%s_%s_2015"%(plot_name,sample) + r".png}} ")
	print(r"\subfloat[]{\includegraphics[width = 3in]" + r"{plots/cutflow_plots/" + "%s_%s_2016"%(plot_name,sample) + r".png}}\\")
	print(r"\subfloat[]{\includegraphics[width = 3in]" + r"{plots/cutflow_plots/" + "%s_%s_2017"%(plot_name,sample) + r".png}}")
	print(r"\subfloat[]{\includegraphics[width = 3in]" + r"{plots/cutflow_plots/" + "%s_%s_2018"%(plot_name,sample) + r".png}} ")
	print(r"\caption{" + " %s in the %s dataset for 2016preAPV (a), 2016postAPV (b), 2017 (c), and 2018 (d). "%(caption,sample_use) + r"}")
	print(r"\label{" + "fig:%s_%s"%(plot_name,sample) + r"}")
	print(r"\end{figure}"%())
	return

def format_cutflow():


	#samples = ["QCDMC1000to1500","QCDMC1500to2000","QCDMC2000toInf", "TTToHadronic", "TTToSemiLeptonic", "TTToLeptonic"]
	samples = ["QCDMC_All","TTbarMC_All","ST_MC_All"]
	captions_= ["The total event $H_{T}$ ", "The number of AK8 jets per event","The number of heavy AK8 jets","The AK4 dijet mass",
	"The number of dijet pairs per event with $M_{dijet}$ $>$ 1.5 TeV","The number of b-tagged AK4 jets (tight WP, deepjet/deepFlavour)",
	"The number of reclustered CA4 jets in the superjet COM frame with E $>$ 300 GeV"]
	captions = [caption + " (before its respective cut is put in place)" for caption in captions_]
	plot_names = ["h_tot_HT_semiRAW","h_nfatjets_semiRAW","h_nfatjets_pre_semiRAW","h_dijet_mass_semiRAW",
	"h_nDijet_pairs_semiRAW",
	"h_nTight_b_jets_semiRAW",
	"h_SJ_nAK4_300_semiRAW"]


	for sample in samples:
			for iii, plot_name in enumerate(plot_names):
				format_string(sample, captions[iii], plot_name)
	return
def format_JME_plots():
	samples = ["QCDMC_All","TTbarMC_All","ST_MC_All"]
	captions= [r"The $\eta$ of selected AK8 jets", r"The $\phi$ of selected AK8 jets", r"The $p_{T}$ of selected AK8 jets",
				r"The $\eta$ of selected AK4 jets", r"The $\phi$ of selected AK4 jets", r"The $p_{T}$ of selected AK4 jets"]
	plot_names = ["h_AK8_eta","h_AK8_phi","h_AK8_pt" ,"h_AK4_eta","h_AK4_phi","h_AK4_pt"]


	for sample in samples:
			for iii, plot_name in enumerate(plot_names):
				format_string(sample, captions[iii], plot_name)

	return
if __name__=="__main__":
	format_cutflow()
	format_JME_plots()
