import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys, os
def main(args):
	### 2015,2016,2017,2018
	years = np.array(["2016preAPV","2016postAPV","2017","2018"])
	n_qcd_1000to1500 = np.array([5,5,5,6])
	n_qcd_1500to2000 = np.array([269,270,443,362])
	n_qcd_2000toInf  = np.array([2830,2639,3741,3251])
	n_TTbar          = np.array([388,439,1076,1560])

	xs_1000to1500 = np.array([1.578683216 , 1.482632755 , 3.126481451 , 4.289571744  ])
	xs_1500to2000 = np.array([ 0.2119142341, 0.195224041 , 0.3197450474 , 0.4947703875 ])
	xs_2000toInf  = np.array([0.08568186031 , 0.07572795371 ,  0.14306915, 0.2132134533  ])
	xs_TTbar      = np.array([0.075592 , 0.05808655696 , 0.06651018525 ,  0.06588049107])

	n_qcd_1000to1500_scaled = np.multiply(n_qcd_1000to1500,xs_1000to1500)
	n_qcd_1500to2000_scaled = np.multiply(n_qcd_1500to2000,xs_1500to2000)
	n_qcd_2000toInf_scaled  = np.multiply(n_qcd_2000toInf,xs_2000toInf)
	n_TTbar_scaled          = np.multiply(n_TTbar,xs_TTbar)

	x_ = range(0,4)
	frac_QCD = (n_qcd_1000to1500_scaled+n_qcd_1500to2000_scaled+n_qcd_2000toInf_scaled) / (n_qcd_1000to1500_scaled+n_qcd_1500to2000_scaled+n_qcd_2000toInf_scaled+n_TTbar_scaled)
	frac_TTbar = (n_TTbar_scaled ) / (n_qcd_1000to1500_scaled+n_qcd_1500to2000_scaled+n_qcd_2000toInf_scaled+n_TTbar_scaled)

	print("QCD/TTbar fractions or each year are ", frac_QCD,frac_TTbar)
	plt.plot(x_,frac_QCD, label='QCD Fraction')
	plt.plot(x_,frac_TTbar, label='TTbar Fraction')
	plt.title("Signal Region Background Proportion")
	plt.xlabel("Data Year")
	plt.ylabel("Background Fraction of Whole")
	plt.legend()
	plt.ylim((0,1.0))
	plt.xticks(range(len(years)), years, size='small')
	#plt.show()
	plt.savefig('/Users/ethan/Documents/plots/randomPlots/SR_BR_proportions.png')


	return


if __name__=="__main__":
	main(sys.argv)