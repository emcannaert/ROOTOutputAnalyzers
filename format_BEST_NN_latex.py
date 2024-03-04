import sys,os



"""
Run this to create the text for the neural network stuff these plots are:
ROC plots, Probability of X classification, accuracy, loss, and normalized confusion matrices.

At some point another loop might need to be added for "low_mass" and "high_mass" if we continue to use this

"""


def year_converter(year):
	year_dict = {"2015":"2016preAPV", "2016":"2016postAPV","2017":"2017","2018":"2018"}
	return year_dict[year]
if __name__=="__main__":
	years = ["2015","2016","2017","2018"]
	output_file = open("BEST_NN_latex_text.txt",'w')
	sampleTypes = ["HT","ZT","WB", "QCD","Top"]
	plot_type = [""]
	captions  = [""]
	for year in years:

		### for plotting the ROC plots
		output_file.write(r"\begin{figure}[htp]"+ "\n")
		output_file.write(r"\centering"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/HT_ROCplot_%s.png"%year +r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/WB_ROCplot_%s.png"%year+ r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/ZT_ROCplot_%s.png}\n"%year)

		output_file.write(r"\medskip"+ "\n")

		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/QCD_ROCplot_%s.png"%year+ r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/op_ROCplot_%s.png}\n"%year)
		output_file.write(r"\caption{"+ "ROC plots for each NN category for %s.}\n"%year)
		output_file.write(r"\label{"+ "fig:ROC_%s}\n"%year)
		output_file.write(r"\end{figure}"+ "\n")
		output_file.write("\n")
		output_file.write("\n")

		### for plotting the decay classifications
		output_file.write(r"\begin{figure}[htp]"+ "\n")
		output_file.write(r"\centering"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/Probability_of_HT_Classification_for_%s.png"%year +r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/Probability_of_WB_Classification_for_%s.png"%year+ r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/Probability_of_ZT_Classification_for_%s.png}\n"%year)

		output_file.write(r"\medskip")

		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/Probability_of_QCD_Classification_for_%s.png"%year+ r"}\quad"+ "\n")
		output_file.write(r"\includegraphics[width=.3\textwidth]{"+ "plots/BEST_plots/Probability_of_Top_Classification_for_%s.png}\n"%year)
		output_file.write(r"\caption{"+ "The probability of decay classification for each training category for %s}\n"%year)
		output_file.write(r"\label{"+ "fig:decayClassification_%s}\n"%year)
		output_file.write(r"\end{figure}"+ "\n")
		output_file.write("\n")
		output_file.write("\n")

		## create plots of the HT distribution of the training events pre and post flattening
		output_file.write(r"\begin{figure" + "}"+ "\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/HTDistribution_%s.png"%(year) +r"}}"+"\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/HTDistribution_%s_train_flattened.png"%(year) +r"}} "+"\n")
		output_file.write(r"\caption{ " + "The number of training events (before splitting and shape-matching (a), and after splitting and shape-matching (b)) per HT bin for %s.}"%year+ "\n")
		output_file.write(r"\label{" + "fig:HT_training_%s}\n"%year ) 
		output_file.write(r"\end{figure}" + "\n")
		output_file.write("\n")
		output_file.write("\n")



	#### accuracy by year
	output_file.write(r"\begin{figure" + "}"+ "\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2015_acc.png" +r"}}"+"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2016_acc.png" +r"}}\ "+"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2017_acc.png" +r"}}"+"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2018_acc.png" +r"}}"+"\n")
	output_file.write(r"\caption{ " + "Training classification accuracy as a function of training epoch.}"+ "\n")
	output_file.write(r"\label{" + "fig:trainingAccuracy}\n" ) 
	output_file.write(r"\end{figure}" + "\n")
	output_file.write("\n")
	output_file.write("\n")

	#### accuracy by year
	output_file.write(r"\begin{figure" + "}"+ "\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2015_loss.png" +r"}}" +"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2016_loss.png" +r"}}\ "+"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2017_loss.png" +r"}}" +"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/2018_loss.png" +r"}}" +"\n")
	output_file.write(r"\caption{ " + "Training loss as a function of training epoch.}"+ "\n")
	output_file.write(r"\label{" + "fig:trainingLoss}\n" ) 
	output_file.write(r"\end{figure}" + "\n")
	output_file.write("\n")
	output_file.write("\n")


	#### confusion matrix by year
	output_file.write(r"\begin{figure" + "}\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/ConfusionMatrix_BES2015_normalized.png" +r"}}" +"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/ConfusionMatrix_BES2016_normalized.png" +r"}}\ "+"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/ConfusionMatrix_BES2017_normalized.png" +r"}}" +"\n")
	output_file.write(r"\subfloat[]{\includegraphics[width=.5\textwidth]" + "{plots/BEST_plots/ConfusionMatrix_BES2018_normalized.png" +r"}}" +"\n")
	output_file.write(r"\caption{ " + "The normalized confusion matrices for each training year. The truth labels are shown in the rows, and the assigned labels are shown in the columns.}"+ "\n")
	output_file.write(r"\label{" + "fig:confusionMatrices}\n" ) 
	output_file.write(r"\end{figure}" + "\n")
	output_file.write("\n")
	output_file.write("\n")


	# format - AK4_m1_2016.png
	input_features = ["AK41_E","AK41_FW1","AK41_FW2","AK41_FW3","AK41_FW4","AK41_aplanarity","AK41_isotropy","AK41_nDaughters","AK41_nsubjets","AK41_px","AK41_py","AK41_pz",
"AK41_sphericity","AK41_thrust","AK42_E","AK42_FW1","AK42_FW2","AK42_FW3","AK42_FW4","AK42_aplanarity","AK42_isotropy","AK42_nDaughters","AK42_nsubjets","AK42_px",
"AK42_py","AK42_pz","AK42_sphericity","AK42_thrust","AK43_E","AK43_FW1","AK43_FW2","AK43_FW3","AK43_FW4","AK43_aplanarity","AK43_isotropy","AK43_nDaughters",
"AK43_nsubjets","AK43_px","AK43_py","AK43_pz","AK43_sphericity","AK43_thrust","AK44_E","AK44_aplanarity","AK44_isotropy","AK44_nDaughters","AK44_nsubjets",
"AK44_px","AK44_py","AK44_pz","AK44_sphericity","AK44_thrust","AK4_m1","AK4_m12","AK4_m123","AK4_m1234","AK4_m124","AK4_m13","AK4_m134","AK4_m14","AK4_m2","AK4_m23",
"AK4_m234","AK4_m24","AK4_m3","AK4_m34","AK4_m4","AK4_theta12","AK4_theta13","AK4_theta14","AK4_theta23","AK4_theta24","AK4_theta34","SJ_FW1","SJ_FW2","SJ_FW3",
"SJ_FW4","SJ_aplanarity","SJ_asymmetry","SJ_isotropy","SJ_mass","SJ_mass_100","SJ_mass_1000","SJ_mass_150","SJ_mass_200","SJ_mass_25","SJ_mass_300","SJ_mass_400",
"SJ_mass_50","SJ_mass_500","SJ_mass_800","SJ_nAK4_100","SJ_nAK4_1000","SJ_nAK4_150","SJ_nAK4_200","SJ_nAK4_25","SJ_nAK4_300","SJ_nAK4_400","SJ_nAK4_50","SJ_nAK4_500",
"SJ_nAK4_800","SJ_sphericity"]

	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	output_file.write("\n")
	
	for input_feature in input_features:
		#### accuracy by year
		output_file.write(r"\begin{figure" + "}"+ "\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.35\textwidth]" + "{plots/BEST_plots/%s_2015.png"%(input_feature) +r"}}"+"\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.35\textwidth]" + "{plots/BEST_plots/%s_2016.png"%(input_feature) +r"}}\ "+"\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.35\textwidth]" + "{plots/BEST_plots/%s_2017.png"%(input_feature) +r"}}"+"\n")
		output_file.write(r"\subfloat[]{\includegraphics[width=.35\textwidth]" + "{plots/BEST_plots/%s_2018.png"%(input_feature) +r"}}"+"\n")
		output_file.write(r"\caption{ " + "Distributions of the of the %s input feature for each training category for 2016preAPV (a), 2016postAPV (b), 2017 (c), and 2018 (d).}"%(input_feature)+ "\n")
		output_file.write(r"\label{" + "fig:input_feature_%s}\n"%input_feature ) 
		output_file.write(r"\end{figure}" + "\n")
		output_file.write("\n")
		output_file.write("\n")
	
	output_file.close()
	print("Finished - output saved to BEST_NN_latex_text.txt")






