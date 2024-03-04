## no inputs returns the whole dictionary
def return_BR_SF():
	scale_factor = 1.0
	scale_factors = {
	"QCDMC1000to1500":{"2015":1.578683216,"2016":1.482632755,"2017":3.126481451,"2018":4.407417122},
	"QCDMC1500to2000":{"2015":0.2119142341,"2016":0.195224041,"2017":0.3197450474,"2018":0.5425809983},
	"QCDMC2000toInf":{"2015":0.08568186031,"2016":0.07572795371,"2017":0.14306915,"2018":0.2277769275},
	"TTToHadronicMC":{"2015":0.075592,"2016":0.05808655696,"2017":0.06651018525,"2018":0.06588049107},
	"TTToSemiLeptonicMC":{"2015":0.05395328118,"2016":0.05808655696,"2017":0.04264829286,"2018":0.04563489275},
	"TTToLeptonicMC":{"2015":0.0459517611,"2016":0.03401684391,"2017":0.03431532926,"2018":0.03617828025},

	"TTJetsMCHT1200to2500":{"2015":0.002722324842,"2016":0.002255554525,"2017":0.00267594799,"2018":0.003918532089},
	"TTJetsMCHT2500toInf" :{"2015":0.000056798633,"2016":0.000050253843,"2017":0.00005947217,"2018":0.000084089656},

	"ST_t_channel_top_inclMC":{"2015":0.0409963154,"2016":0.03607115071,"2017":0.03494669125,"2018":0.03859114659},
	"ST_t_channel_antitop_incMC":{"2015":0.05673857623,"2016":0.04102705994,"2017":0.04238814865,"2018":0.03606630944},
	"ST_s_channel_hadronsMC":{"2015":0.04668187234,"2016":0.03564988679,"2017":0.03985938616,"2018":0.04102795437},
	"ST_s_channel_leptonsMC":{"2015":0.01323030083,"2016":0.01149139097,"2017":0.01117527734,"2018":0.01155448784},
	"ST_tW_antiTop_inclMC":{"2015":0.2967888696,"2016":0.2301666797,"2017":0.2556495594,"2018":0.2700032391},
	"ST_tW_top_inclMC":{"2015":0.2962796522,"2016":0.2355829386,"2017":0.2563403788,"2018":0.2625270613}}
	return scale_factor

def return_BR_SF(year,sample):
	scale_factor = 1.0
	scale_factors = {
	"QCDMC1000to1500":{"2015":1.578683216,"2016":1.482632755,"2017":3.126481451,"2018":4.407417122},
	"QCDMC1500to2000":{"2015":0.2119142341,"2016":0.195224041,"2017":0.3197450474,"2018":0.5425809983},
	"QCDMC2000toInf":{"2015":0.08568186031,"2016":0.07572795371,"2017":0.14306915,"2018":0.2277769275},
	"TTToHadronicMC":{"2015":0.075592,"2016":0.05808655696,"2017":0.06651018525,"2018":0.06588049107},
	"TTToSemiLeptonicMC":{"2015":0.05395328118,"2016":0.05808655696,"2017":0.04264829286,"2018":0.04563489275},
	"TTToLeptonicMC":{"2015":0.0459517611,"2016":0.03401684391,"2017":0.03431532926,"2018":0.03617828025},

	"TTJetsMCHT1200to2500":{"2015":0.002722324842,"2016":0.002255554525,"2017":0.00267594799,"2018":0.003918532089},
	"TTJetsMCHT2500toInf" :{"2015":0.000056798633,"2016":0.000050253843,"2017":0.00005947217,"2018":0.000084089656},

	"ST_t_channel_top_inclMC":{"2015":0.0409963154,"2016":0.03607115071,"2017":0.03494669125,"2018":0.03859114659},
	"ST_t_channel_antitop_incMC":{"2015":0.05673857623,"2016":0.04102705994,"2017":0.04238814865,"2018":0.03606630944},
	"ST_s_channel_hadronsMC":{"2015":0.04668187234,"2016":0.03564988679,"2017":0.03985938616,"2018":0.04102795437},
	"ST_s_channel_leptonsMC":{"2015":0.01323030083,"2016":0.01149139097,"2017":0.01117527734,"2018":0.01155448784},
	"ST_tW_antiTop_inclMC":{"2015":0.2967888696,"2016":0.2301666797,"2017":0.2556495594,"2018":0.2700032391},
	"ST_tW_top_inclMC":{"2015":0.2962796522,"2016":0.2355829386,"2017":0.2563403788,"2018":0.2625270613}}

	if "QCD" in sample:
		if "1000to1500" in sample:
			scale_factor = scale_factors["QCDMC1000to1500"][year]
		elif "1500to2000" in sample:
			scale_factor = scale_factors["QCDMC1500to2000"][year]
		elif "2000toInf" in sample:
			scale_factor = scale_factors["QCDMC2000toInf"][year]
		else:
			print("ERROR: Sample name not found: %s"%sample)
			return
	elif "TTTo" in sample:
		if "Hadronic" in sample:
			scale_factor = scale_factors["TTToHadronicMC"][year]
		elif "SemiLeptonic" in sample:
			scale_factor = scale_factors["TTToSemiLeptonicMC"][year]
		elif "TTToLeptonic" in sample:
			scale_factor = scale_factors["TTToLeptonicMC"][year]
		else: 
			print("ERROR: Sample name not found: %s"%sample)
	elif "ST_" in sample:
		if "t_channel_top_incl" in sample:
			scale_factor = scale_factors["ST_t_channel_top_inclMC"][year]
		elif "t_channel_antitop_inc":
			scale_factor = scale_factors["ST_t_channel_antitop_incMC"][year]
		elif "s_channel_hadrons":
			scale_factor = scale_factors["ST_s_channel_hadronsMC"][year]
		elif "s_channel_leptons":
			scale_factor = scale_factors["ST_s_channel_leptonsMC"][year]
		elif "tW_antiTop_incl":
			scale_factor = scale_factors["ST_tW_antiTop_inclMC"][year]
		elif "tW_top_incl":
			scale_factor = scale_factors["ST_tW_top_inclMC"][year]
		else:
			print("ERROR: Sample name not found: %s"%sample)
	else:
		print("MC sample type not found: %s"%sample, " - assumed to be data.")
	return scale_factor