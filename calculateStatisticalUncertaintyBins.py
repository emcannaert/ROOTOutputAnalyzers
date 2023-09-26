import ROOT
import sys, os
from math import sqrt
from random import uniform
import pdb


"""

	histograms are 22 x 20
at end: in a TH2: fill grouped bins with a certain color to see how the groupings ended 
"""


#idea: if a bin has no neighbors, then check check diagonals, then create a cube around it

class combineHistBins:
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self, TH2_hist):   #constructor will convert TH2 to a 2D array, do the optimized bin merging, and then return a TH2 with those associated bins
		self.TH2_hist = TH2_hist
		self.hist_values = self.convert_TH2() # self.fill_random_values() self.test_hist() self.test_hist2()   # 
		self.superbin_indices = self.init_superbin_indices()
		print("Starting the process of merging bins.")
		self.do_bin_merging()
		print("Finished with bin merging.")
		self.print_final_hist()

	def test_hist(self):
		test_hist = [
		[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.2,0,0,0,0],
		[0,0,0,0,0,0,0,0,0,0.2,0,0,0,0,0,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0,0.2,0,0,0,0,0,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0,0,0.2,0,0,0,0,0.2,0,0.2,0,0,0,0],
		[0,0,0,0,0,0,0,0,0,0,0.2,0.2,0.2,0,0.2,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0.2,0,0,0,0.2,0.2,0.2,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0,0,0,0,0,0,0,0,0],
		[0,0,0,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0,0,0,0,0,0,0,0,0,0],
		[0,1,1,1,1,1,1,1,1,0.2,0.2,0.2,0.2,0.2,0.2,0,0,0,0,0,0,0],
		[0,2,2,2,2,5,5,5,2,5,2,2,2,1,1,0.2,0.2,0.2,0.2,0,0,0],
		[0,5,5,5,5,5,5,10,10,5,10,10,5,5,5,1,1,0.2,0.2,0.2,0,0],
		[0,10,10,10,10,10,10,10,10,10,10,5,5,5,5,1,1,0.2,0.2,0,0,0],
		[0,10,10,10,10,10,10,10,10,10,10,5,5,5,5,5,1,1,0,0,0,0],
		[0,20,20,20,20,20,20,20,20,10,10,10,10,10,10,0.2,0.2,0,0,0,0,0],
		[0,20,20,20,20,20,20,20,20,10,10,10,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,20,10,10,10,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,20,10,10,10,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,20,10,10,10,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,10,10,10,5,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,10,10,10,5,5,5,1,1,0.2,0.2,0,0,0,0],
		[0,20,20,20,20,20,20,20,10,10,10,5,5,5,1,1,0.2,0.2,0,0,0,0]]
		return test_hist
	def test_hist2(self):
		test_hist = [
		[0,0,0,0,0],
		[0,0,0.5,0,0],
		[0,0,0,0,0],
		[0,1,2,3,0],
		[0,1,2,3,0]]
		return test_hist
	def print_final_hist(self):
		hist_map = [ [-999]*combineHistBins.n_bins_y for i in range(combineHistBins.n_bins_x)]
		print("Histogram bin map:")
		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0, combineHistBins.n_bins_y):
				hist_map[iii][jjj] = self.get_superbin_number( (iii,jjj))

		print('\n'.join(' '.join(str(x) for x in row) for row in hist_map))

		print("Histogram bin statistical uncertainties")
		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0, combineHistBins.n_bins_y):
				if(  self.counts_in_superbin(self.get_superbin_number( (iii,jjj))) > 0  ):
					hist_map[iii][jjj] = 1.0/sqrt(self.counts_in_superbin(self.get_superbin_number( (iii,jjj))))
				else:
					hist_map[iii][jjj] = 0.0

		print('\n'.join(' '.join(str(x) for x in row) for row in hist_map))

		return
	def convert_TH2(self):

		converted_hist = [ [0]*combineHistBins.n_bins_y for i in range(combineHistBins.n_bins_x)]
		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0,combineHistBins.n_bins_y):
				converted_hist[iii][jjj] = self.TH2_hist.GetBinContent(iii,jjj) 
		return converted_hist

	def fill_random_values(self):

		converted_hist = [ [0]*combineHistBins.n_bins_y for i in range(combineHistBins.n_bins_x)]
		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0,combineHistBins.n_bins_y):
				converted_hist[iii][jjj] = uniform(0.0,20.0)

		print("original histogram looks like: ")
		print('\n'.join(' '.join(str(x) for x in row) for row in converted_hist))
		return converted_hist



	def init_superbin_indices(self):
		_superbin_indices = []    # format [ [(x1,x2),(x2,x3),....], [(xi,yi), (xi+1,yi+1),.....], ...., [(xn-1,yn-1),(xn,yn)] ]     _superbin_indices[<superbin #>][<order bin was added>][<coordinate>]
		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0, combineHistBins.n_bins_y):
				_superbin_indices.append([(iii,jjj)])    # superbin # and add # don't matter
		return _superbin_indices
	def get_superbin_number(self, index_tuple): # given a tuple of coordinate indices (relative to the original TH2), return the superbin number this coordinate is a part of
		for iii, superbin in enumerate(self.superbin_indices):
			if index_tuple in superbin:
				return iii
	def counts_in_superbin(self, superbin_number):
		_sum = 0
		for _tuple in self.superbin_indices[superbin_number]:
			_sum+= self.hist_values[_tuple[0]][_tuple[1]]
		return _sum
	def all_bins_are_good(self):
		for iii, superbin in enumerate(self.superbin_indices):
			n_counts = self.counts_in_superbin(iii)
			if n_counts > 0: # don't want to divide by 0
				#print("Number of counts in superbin: ", n_counts)
				if (1.0/sqrt(self.counts_in_superbin(iii)) ) > 0.25:
					return False
		return True
	def get_list_of_neighbors(self,_tuple):
		# need to get list of neighbor indices of all bins in this superbin
		list_of_neighbors = [] # will be full of the superbin #s  
		for superbin_tuples in self.superbin_indices[self.get_superbin_number( _tuple ) ]: # get_list_of_neighbors

			# check to see if the hist_values neighbors of the superbin_tuples are already in this superbin
			# have to check up,down, right, left, have to check the indices are valid
			index_x = _tuple[0]
			index_y = _tuple[1]

			if ( ( index_x+1 )< combineHistBins.n_bins_x ):
				if not (index_x+1,index_y) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x+1][index_y] > 0:
						list_of_neighbors.append((index_x+1,index_y))
			if ( ( index_x-1 ) >= 0 ):
				if not (index_x-1,index_y) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x-1][index_y] > 0:
						list_of_neighbors.append((index_x-1,index_y))
			if ( ( index_y+1 )< combineHistBins.n_bins_y ):
				if not (index_x,index_y+1) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x][index_y+1] > 0:
						list_of_neighbors.append((index_x,index_y+1))
			if ( ( index_y-1 ) >= 0 ):
				if not (index_x,index_y-1) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x][index_y-1] > 0:
						list_of_neighbors.append((index_x,index_y-1))
		list_of_neighbor_superbins = []
		# then convert this to a list of superbin #s 
		for neighbor_tuple in list_of_neighbors:
			neighbor_superbin_number = self.get_superbin_number(neighbor_tuple)
			if neighbor_superbin_number not in list_of_neighbor_superbins:
				list_of_neighbor_superbins.append(neighbor_superbin_number)
		return list_of_neighbor_superbins
		
	#maybe should loop over superbins instead
	def do_bin_merging(self):
		all_bins_good = False
		iteration_count = 0
		while not all_bins_good:
			print("Starting on run-through %i"%(iteration_count+1))


			if(iteration_count == 1000): # don't want this going on foreer
				test_counts = [ self.counts_in_superbin(superbin_number) for superbin_number in range(0,len(self.superbin_indices))]
				#for iii in range(0, len(test_counts)):
				#	print("indices: %s                counts: %s"%(self.superbin_indices[iii], test_counts[iii]))
				return
			# do a run-through of the bin merging
			for iii in reversed(range(0,combineHistBins.n_bins_x)):
				for jjj in reversed(range(0, combineHistBins.n_bins_y)):


					#print(self.hist_values)
					#print(self.superbin_indices)
					#print("bins iii/jjj: %s/%s"%(iii,jjj))
					superbin_number   = self.get_superbin_number( (iii,jjj))
					superbin_counts = self.counts_in_superbin(superbin_number)
					if (superbin_counts == 0):
						#print("No events - bin skipped.")
						continue

					if ( (1.0/sqrt(superbin_counts)) < 0.25):
						#print("This bin has low enough statistical uncertainty. Skipped.")
						continue

					#add the surrounding bins to the
					list_of_neighbors = self.get_list_of_neighbors( (iii,jjj) ) # all neighbors of this bin and all bins in its parent superbin 
					neighbor_counts   = [ self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors]
					#print("Found %i neighbors:"%len(list_of_neighbors) ,list_of_neighbors )

					if len(list_of_neighbors) == 0:
						continue
					# problem: there are no neighbors ...
					mergeIndex = list_of_neighbors[neighbor_counts.index(min(neighbor_counts))] # add to the neighbor with the fewest counts
					#print("Merging %s with %s"% ( self.superbin_indices[mergeIndex],self.superbin_indices[superbin_number]   ))
					self.superbin_indices[mergeIndex].extend(self.superbin_indices[superbin_number])
					self.superbin_indices.remove(self.superbin_indices[superbin_number])
					#print("New superbin_indices looks like %s"%self.superbin_indices)

			## check all bins to see if they are islands
			    # if bin has stat uncertainty that is too high, check if adjacent bins are all empty
			    # check to see if adjacent bins are already in a superbin (they shouldn't be), if they are, don't add these 
			    # if adjacent bin is empty, add these bins to the superbin_indices island entry and remove the adjacent bin entry
			
			for iii in reversed(range(0,combineHistBins.n_bins_x)):
				for jjj in reversed(range(0, combineHistBins.n_bins_y)):
					superbin_num = self.get_superbin_number((iii,jjj))
					superbin_counts = self.counts_in_superbin( superbin_num)
					superbin = self.superbin_indices[superbin_num]
					if ( (superbin_counts > 0) and   ((1.0/sqrt(superbin_counts)) < 0.25)):
						continue
					if ( (iii > 0) and (jjj > 0) and (iii < (combineHistBins.n_bins_x - 1)) and (jjj < (combineHistBins.n_bins_y -1  )) ):
						
						is_an_island = True
						island_index = self.get_superbin_number((iii,jjj))
						for xshift in range(-1,2):
							for yshift in range(-1,2):
								if (xshift == yshift) or (xshift == -yshift):  # we don't want the diagonals ...
									continue
								if (self.hist_values[iii+xshift][jjj+yshift] > 0):
									is_an_island = False
								# if adjacent bin is already in another superbin, this is not an island, diagonal bins can be in superbins
								for superbin_compare in self.superbin_indices: 
									if (len(superbin_compare) > 1) and ( (iii+xshift,jjj+yshift) in superbin_compare):
										is_an_island = False
						if is_an_island:
							#print("Found that (%s,%s) (or superbin index %s) is an island"%(iii,jjj, island_index ) )
							#print("superbin indices look like ", self.superbin_indices)

							for xshift in range(-1,2):
								for yshift in range(-1,2):
									if (xshift == yshift) or (xshift == -yshift):  # we don't want the diagonals ...
										continue
									adjacent_index = self.get_superbin_number((iii+xshift,jjj+yshift))
									#print("iii/jjj are %s/%s"%(iii,jjj))
									#print("xshift/yshift are: %s/%s"%(xshift,yshift))
									#print("checking adjacent index (%s,%s) (superbin index %s)"%( iii+xshift,jjj+yshift,adjacent_index) )
									#print("island superbin entry is %s, now adding %s"%(self.superbin_indices[island_index], self.superbin_indices[adjacent_index]))
									self.superbin_indices[island_index].extend(self.superbin_indices[adjacent_index])
									#print("removing %s from superbin "%self.superbin_indices[adjacent_index])
									self.superbin_indices.remove(self.superbin_indices[adjacent_index])
									island_index = self.get_superbin_number((iii,jjj))
									#print("the current island index is ", island_index)
									#print("island superbin index now looks like: %s "%self.superbin_indices[island_index])
							#print("----------- finished with island -----------")

			iteration_count+=1
			all_bins_good = self.all_bins_are_good()
		return

if __name__=="__main__":
	print("Calculating bin groupings for best statistical uncertainties")

	years = {"2015","2016","2017","2018"}
	regions = {"SR","CR"}
	c = ROOT.TCanvas("c", "canvas", 800, 800)
	for region in regions:
		for year in years:


			hist_path = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudy/allBR_statUncert_%s_%s.root"%(region,year)
			hist_name = "h_MSJ_mass_vs_MdSJ_" +region
			TH2_file = ROOT.TFile.Open(hist_path,"READ")
			TH2_hist = TH2_file.Get(hist_name)
			TH2_hist_merged_name = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/mergedBinFiles/allBR_statUncert_%s_%s_MERGED_BINS.root"%(region,year)
			TH2_hist_new_bins_name = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudy/mergedBinFiles/allBR_statUncert_%s_%s_NEW_BINS.root"%(region,year)
			out_file = ROOT.TFile.Open(TH2_hist_new_bins_name,"RECREATE")

			# give histogram to constructor
			testCase = combineHistBins(TH2_hist)

			#create a dummy histogram with dimensions 20x22
			merged_bins = testCase.superbin_indices
			bin_map_hist = ROOT.TH2F("bin_map_hist", ("Map of how bins were merged in %s for %s"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
			stat_uncert_hist = ROOT.TH2F("stat_uncert_hist", ("Statistical Uncertainty (post bin merging) in the %s for %s"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
			merged_hist_count = ROOT.TH2F("merged_hist_count", ("Bin Counts (post bin merging) in the %s for %s"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125

			for superbin_index, superbin in enumerate(merged_bins):
				for smallbin in superbin:
					if testCase.counts_in_superbin(superbin_index) == 0:   # don't show indices for empty bins
						continue
					#print("Filling bins [%s, %s] for region %s and year %s with value %i"%(smallbin[0],smallbin[1],region,year,superbin_index))
					bin_map_hist.SetBinContent(smallbin[0],smallbin[1],superbin_index)
					stat_uncert_hist.SetBinContent(smallbin[0],smallbin[1], 1/sqrt(testCase.counts_in_superbin(superbin_index)))
					merged_hist_count.SetBinContent(smallbin[0],smallbin[1], testCase.counts_in_superbin(superbin_index))


			ROOT.gStyle.SetOptStat(0)
			bin_map_hist.Write()
			bin_map_hist.Draw("colz")
			#bin_map_hist.Print()
			c.SaveAs("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/mergedBinPlots/bin_map_%s_%s.png"%(region,year)) 
			

			stat_uncert_hist.Write()
			stat_uncert_hist.Draw("colz")
			#bin_map_hist.Print()
			c.SaveAs("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/mergedBinPlots/stat_uncert_%s_%s.png"%(region,year)) 
			
			merged_hist_count.Write()
			merged_hist_count.Draw("colz")
			#bin_map_hist.Print()
			c.SaveAs("/Users/ethan/Documents/plots/statUncertaintyPlotsAlt/mergedBinPlots/bin_counts_%s_%s.png"%(region,year)) 


