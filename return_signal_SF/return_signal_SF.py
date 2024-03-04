def return_signal_SF(year,mass_point):
	## input signal mass point in the format Suu$Mass_chi$mass
	## can be imported into other modules when needed
	SFs = {'Suu4_chi1': {'2015':1.26E+00 ,'2016':1.09E+00,'2017':2.68E+00,'2018':3.87E+00}, 
	'Suu4_chi1p5': {'2015':9.43E-01 ,'2016':8.12E-01,'2017':2.00E+00,'2018':2.89E+00}, 
	'Suu5_chi1': {'2015':4.46E-01 ,'2016':3.84E-01,'2017':9.49E-01,'2018':1.37E+00}, 
	'Suu5_chi1p5': {'2015':3.87E-01 ,'2016':3.33E-01,'2017':8.22E-01,'2018':1.19E+00}, 
	'Suu5_chi2': {'2015':2.83E-01 ,'2016':2.44E-01,'2017':6.01E-01,'2018':8.67E-01}, 
	'Suu6_chi1': {'2015':9.19E-02 ,'2016':7.92E-02,'2017':1.95E-01,'2018':2.82E-01}, 
	'Suu6_chi1p5': {'2015':8.42E-02 ,'2016':7.25E-02,'2017':1.79E-01,'2018':2.58E-01}, 
	'Suu6_chi2': {'2015':7.16E-02 ,'2016':6.17E-02,'2017':1.52E-01,'2018':2.20E-01}, 
	'Suu7_chi1': {'2015': 6.54E-02,'2016':5.64E-02,'2017':1.39E-01,'2018':2.01E-01}, 
	'Suu7_chip5': {'2015':6.16E-02 ,'2016':5.30E-02,'2017':1.31E-01,'2018':1.89E-01}, 
	'Suu7_chi2': {'2015':5.56E-02 ,'2016':4.79E-02,'2017':1.18E-01,'2018':1.71E-01}, 
	'Suu7_chi3': {'2015':4.28E-02 ,'2016':3.69E-02,'2017':9.10E-02,'2018':1.31E-01}, 
	'Suu8_chi1': {'2015': 7.09E-03,'2016':6.10E-03,'2017':1.51E-02,'2018':2.17E-02}, 
	'Suu8_chi1p5': {'2015':6.78E-03 ,'2016':5.84E-03,'2017':1.44E-02,'2018':2.08E-02}, 
	'Suu8_chi2': {'2015': 6.31E-03,'2016':5.44E-03,'2017':1.34E-02,'2018':1.74E-02}, 
	'Suu8_chi3': {'2015': 5.68E-03,'2016':4.89E-03,'2017':1.21E-02,'2018':1.93E-02}}


	return SFs[mass_point][year]



# overloaded version to work for the individual decays 
def return_signal_SF(year,mass_point,decay):
	## input signal mass point in the format Suu$Mass_chi$Mass
	## can be imported into other modules when needed
	SFs = {'Suu4_chi1': {'2015':1.26E+00 ,'2016':1.09E+00,'2017':2.68E+00,'2018':3.87E+00}, 
	'Suu4_chi1p5': {'2015':9.43E-01 ,'2016':8.12E-01,'2017':2.00E+00,'2018':2.89E+00}, 
	'Suu5_chi1': {'2015':4.46E-01 ,'2016':3.84E-01,'2017':9.49E-01,'2018':1.37E+00}, 
	'Suu5_chi1p5': {'2015':3.87E-01 ,'2016':3.33E-01,'2017':8.22E-01,'2018':1.19E+00}, 
	'Suu5_chi2': {'2015':2.83E-01 ,'2016':2.44E-01,'2017':6.01E-01,'2018':8.67E-01}, 
	'Suu6_chi1': {'2015':9.19E-02 ,'2016':7.92E-02,'2017':1.95E-01,'2018':2.82E-01}, 
	'Suu6_chi1p5': {'2015':8.42E-02 ,'2016':7.25E-02,'2017':1.79E-01,'2018':2.58E-01}, 
	'Suu6_chi2': {'2015':7.16E-02 ,'2016':6.17E-02,'2017':1.52E-01,'2018':2.20E-01}, 
	'Suu7_chi1': {'2015': 6.54E-02,'2016':5.64E-02,'2017':1.39E-01,'2018':2.01E-01}, 
	'Suu7_chip5': {'2015':6.16E-02 ,'2016':5.30E-02,'2017':1.31E-01,'2018':1.89E-01}, 
	'Suu7_chi2': {'2015':5.56E-02 ,'2016':4.79E-02,'2017':1.18E-01,'2018':1.71E-01}, 
	'Suu7_chi3': {'2015':4.28E-02 ,'2016':3.69E-02,'2017':9.10E-02,'2018':1.31E-01}, 
	'Suu8_chi1': {'2015': 7.09E-03,'2016':6.10E-03,'2017':1.51E-02,'2018':2.17E-02}, 
	'Suu8_chi1p5': {'2015':6.78E-03 ,'2016':5.84E-03,'2017':1.44E-02,'2018':2.08E-02}, 
	'Suu8_chi2': {'2015': 6.31E-03,'2016':5.44E-03,'2017':1.34E-02,'2018':1.74E-02}, 
	'Suu8_chi3': {'2015': 5.68E-03,'2016':4.89E-03,'2017':1.21E-02,'2018':1.93E-02}}

	WB_BR = 0.50
	ZT_BR = 0.25
	HT_BR = 0.25

	Z_had_BR = 0.6991
	W_had_BR = 0.6741
	H_had_BR = 0.58
	t_had_BR = 0.6741

	WBWB_had_BR = (WB_BR*WB_BR)*(W_had_BR)*(W_had_BR)   # the Suu -> chi chi -> WBWB -> all had branching fraction
	HTHT_had_BR = (HT_BR*HT_BR)*(H_had_BR*t_had_BR)*(H_had_BR*t_had_BR)
	ZTZT_had_BR = (ZT_BR*ZT_BR)*(Z_had_BR*t_had_BR)*(Z_had_BR*t_had_BR)
	WBHT_had_BR = (WB_BR*HT_BR)*(W_had_BR)*(H_had_BR*t_had_BR)
	WBZT_had_BR = (WB_BR*ZT_BR)*(W_had_BR)*(Z_had_BR*t_had_BR)
	HTZT_had_BR = (HT_BR*ZT_BR)*(H_had_BR*t_had_BR)*(Z_had_BR*t_had_BR)
	if decay == "WBWB":
		return SFs[mass_point][year]*WBWB_had_BR
	elif decay == "HTHT":
		return SFs[mass_point][year]*HTHT_had_BR
	elif decay == "ZTZT":
		return SFs[mass_point][year]*ZTZT_had_BR
	elif decay == "WBHT":
		return SFs[mass_point][year]*WBHT_had_BR
	elif decay == "WBZT":
		return SFs[mass_point][year]*WBZT_had_BR
	elif decay == "HTZT":
		return SFs[mass_point][year]*HTZT_had_BR
	else:
		print("ERROR: decay %s did not match any of the accepted SuuToChiChi decays (WBWB,HTHT,ZTZT,WBHT,WBZT,HTZT)."%decay)
		return None






