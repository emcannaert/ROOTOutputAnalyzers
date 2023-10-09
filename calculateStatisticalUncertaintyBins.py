import ROOT
import sys, os
from math import sqrt, exp
import random
from random import uniform, shuffle
import pdb
import time
from histInfo import histInfo

####  calculateStatisticalUncertaintyBins.py
####  written by Ethan Cannaert, 24 September 2023
####  opens up a TH2 (22x20 bins, avg superjet mass vs diSuperjet mass)
####  merges bins into "superbins" until superbin systematic uncertainties are below 25% ( or desired value)
####  histograms showing the bin mappings, final superbin counts, and superbin statistical uncertainties
####  the merging is automatically done upon defining a combineHistBins class object taking in a combined histogram, data year, and region


class combineHistBins:
	n_bins_x = 22
	n_bins_y = 20
	def __init__(self,TH2_hist,year,region):   #constructor will convert TH2 to a 2D array, do the optimized bin merging, and then return a TH2 with those associated bins
		self.TH2_hist = TH2_hist
		self.year = year
		self.region = region
		self.hist_values = self.convert_TH2() #histogram filled with counts in each bin (from alt datasets)     # self.fill_random_values() self.test_hist() self.test_hist2()   # 
		self.all_hist_values = histInfo.histInfo(year,region) ## everywhere there is originally a sqrt, will need to call get_bin_total_uncert and get 
		self.superbin_indices = self.init_superbin_indices()     
		
		print("Starting the process of merging bins.")
		self.do_bin_merging()
		print("Finished with bin merging.")
		#self.print_final_hist()
		self.fill_in_holes()

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
					hist_map[iii][jjj] = self.all_hist_values.get_bin_total_uncert(self.superbin_indices[self.get_superbin_number( (iii,jjj))] ) #  1.0/sqrt(self.counts_in_superbin(self.get_superbin_number( (iii,jjj ) ) ) ) 
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
				random.seed(54321)
				converted_hist[iii][jjj] = uniform(0.0,20.0)

		print("original histogram looks like: ")
		print('\n'.join(' '.join(str(x) for x in row) for row in converted_hist))
		return converted_hist
	def calculate_bin_weight(self, superbin_index, cand_superbin_index ):
		avg_xbin = 0
		avg_ybin = 0
		nBins = 0
		counts_in_cand_bin = self.counts_in_superbin(cand_superbin_index)
		for _tuple in self.superbin_indices[superbin_index]:
			avg_xbin+=_tuple[0]
			avg_ybin+= _tuple[1]
			nBins +=1
		avg_xbin/=nBins
		avg_ybin/=nBins
		cand_avg_xbin = 0
		cand_avg_ybin = 0
		cand_nbins = 0
		for _tuple in self.superbin_indices[cand_superbin_index]:
			cand_avg_xbin+=_tuple[0]
			cand_avg_ybin+= _tuple[1]
			cand_nbins+=1
		cand_avg_xbin/= cand_nbins
		cand_avg_ybin/= cand_nbins
		# distance should be distance between candidate superbin center and current superbin center
		distance = sqrt(pow(int(cand_avg_xbin- avg_xbin),2)+pow(int(cand_avg_ybin- avg_ybin),2))
		return (exp(5*distance/1.0) + 2.0*counts_in_cand_bin)
	def get_best_search_direction(self, superbin_index ):
		avg_xbin = 0
		avg_ybin = 0
		nBins = 0

		all_superbin_weight_x = 0
		all_superbin_weight_y = 0
		for _tuple in self.superbin_indices[superbin_index]:
			#get average x and y bin of this superbin
			avg_xbin+= _tuple[0]
			avg_ybin+= _tuple[1]
			nBins+=1
		avg_xbin = int(avg_xbin/nBins)
		avg_ybin = int(avg_ybin/nBins)

		avg_xbin_all = 0
		avg_ybin_all = 0
		nBins_all = 0
		for superbin in self.superbin_indices:
			for _tuple in superbin:
				counts_in_cand_bin = self.counts_in_superbin(self.get_superbin_number(_tuple))
				avg_xbin_all+= _tuple[0]
				avg_ybin_all+= _tuple[1]
				nBins_all+=1
				#nBins_all +=1
			#avg_xbin_all/=nBins_all
			#avg_ybin_all/=nBins_all
		avg_xbin_all/=nBins_all
		avg_ybin_all/=nBins_all
		all_superbin_weight_x= -(exp(-abs(avg_xbin-avg_xbin_all)/5.0)+ counts_in_cand_bin)*(avg_xbin-avg_xbin_all)
		all_superbin_weight_y= -(exp(-abs(avg_ybin-avg_ybin_all)/5.0)+ counts_in_cand_bin)*(avg_ybin-avg_ybin_all)

		return (all_superbin_weight_x,all_superbin_weight_y)
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
				if self.all_hist_values.get_bin_total_uncert(self.superbin_indices[iii])  > 0.25:    # 1.0/sqrt(self.counts_in_superbin( iii ) )
					return False
		return True
	def get_list_of_neighbors(self,_tuple):
		# need to get list of neighbor indices of all bins in this superbin   ######## am I checking here that the bins are not empty?
		list_of_neighbors = [] # will be full of the superbin #s  
		this_superbin_num = self.get_superbin_number( _tuple )
		for superbin_tuples in self.superbin_indices[this_superbin_num ]: # 

			# check to see if the hist_values neighbors of the superbin_tuples are already in this superbin
			# have to check up,down, right, left, have to check the indices are valid
			index_x = superbin_tuples[0] #_tuple[0]
			index_y = superbin_tuples[1] #_tuple[1]

			if ( ( index_x+1 ) < combineHistBins.n_bins_x ):
				if (index_x+1,index_y) not in self.superbin_indices[this_superbin_num ]:   
					if self.counts_in_superbin(self.get_superbin_number(  (index_x+1,index_y)  )) > 0:
						list_of_neighbors.append((index_x+1,index_y))
			if ( ( index_x-1 ) >= 0 ):
				if  (index_x-1,index_y) not in self.superbin_indices[this_superbin_num ]:
					if self.counts_in_superbin(self.get_superbin_number(  (index_x-1,index_y)  )) > 0:
						list_of_neighbors.append((index_x-1,index_y))
			if ( ( index_y+1 )< combineHistBins.n_bins_y ):
				if (index_x,index_y+1) not in self.superbin_indices[this_superbin_num ]:
					if self.counts_in_superbin(self.get_superbin_number(  (index_x,index_y+1)  )) > 0:
						list_of_neighbors.append((index_x,index_y+1))
			if ( ( index_y-1 ) >= 0 ):
				if (index_x,index_y-1) not in self.superbin_indices[this_superbin_num]:
					if self.counts_in_superbin(self.get_superbin_number(  (index_x,index_y-1)  )) > 0:
						list_of_neighbors.append((index_x,index_y-1))
		list_of_neighbor_superbins = []
		# then convert this to a list of superbin #s 
		for neighbor_tuple in list_of_neighbors:
			if self.counts_in_superbin(self.get_superbin_number(neighbor_tuple)) ==0:
				continue
			neighbor_superbin_number = self.get_superbin_number(neighbor_tuple)
			if neighbor_superbin_number not in list_of_neighbor_superbins:
				list_of_neighbor_superbins.append(neighbor_superbin_number)
		return list_of_neighbor_superbins
	def get_list_of_empty_neighbors(self,_tuple):
		start_time = time.time()
		# get only superbins in the direction of the nearest non-empty superbin

		list_of_neighbors = [] # will be full of the superbin #s  
		for superbin_tuples in self.superbin_indices[self.get_superbin_number( _tuple ) ]: # all superbin tuples in superbin 

			# check to see if the hist_values neighbors of the superbin_tuples are already in this superbin
			# have to check up,down, right, left, have to check the indices are valid
			index_x = superbin_tuples[0]
			index_y = superbin_tuples[1]
			search_direction = self.get_best_search_direction(self.get_superbin_number(_tuple))
			search_x = search_direction[0]
			search_y = search_direction[1]

			#print("search x/y: %s/%s"%(search_x,search_y))
			#### check adjacent bins
			if ( ( index_x+1 )< combineHistBins.n_bins_x ):
				if not (index_x+1,index_y) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x+1][index_y] == 0:		
						list_of_neighbors.append((index_x+1,index_y))
			if ( ( index_x-1 ) >= 0 ):
				if not (index_x-1,index_y) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x-1][index_y] == 0:
						list_of_neighbors.append((index_x-1,index_y))
			if ( ( index_y+1 )< combineHistBins.n_bins_y ):
				if not (index_x,index_y+1) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x][index_y+1] == 0:
						list_of_neighbors.append((index_x,index_y+1))
			if ( ( index_y-1 ) >= 0 ):
				if not (index_x,index_y-1) in self.superbin_indices[self.get_superbin_number( _tuple ) ]:
					if self.hist_values[index_x][index_y-1] == 0:
						list_of_neighbors.append((index_x,index_y-1))
		list_of_neighbor_superbins = []
		# then convert this to a list of superbin #s 
		for neighbor_tuple in list_of_neighbors:
			neighbor_superbin_number = self.get_superbin_number(neighbor_tuple)
			if self.counts_in_superbin(neighbor_superbin_number) > 0: # double checking these are empty
				continue
			if neighbor_superbin_number not in list_of_neighbor_superbins:
				list_of_neighbor_superbins.append(neighbor_superbin_number)
		#print("get_list_of_empty_neighbors took %s to run"%(time.time() - start_time))
		return list_of_neighbor_superbins
	def check_island_neighbors(self,superbin_number):
		start_time = time.time()
		#print("island superbin is %s"%self.superbin_indices[superbin_number])
		#print("island superbin is %s bins long"%len(self.superbin_indices[superbin_number]))
		for island_tuple in self.superbin_indices[superbin_number]:
			for adj_superbin in self.superbin_indices:
				if self.get_superbin_number(adj_superbin[0]) == superbin_number:
					continue # don't want this superbin to compare to itself.
				if self.counts_in_superbin(self.get_superbin_number(adj_superbin[0])) == 0:
					continue
				if (island_tuple[0]+1,island_tuple[1]) in adj_superbin:
					#print("check_island_neighbors took %s to run"%(time.time() - start_time))
					return False
				if (island_tuple[0]-1,island_tuple[1]) in adj_superbin:
					#print("check_island_neighbors took %s to run"%(time.time() - start_time))
					return False
				if (island_tuple[0],island_tuple[1]+1) in adj_superbin:
					#print("check_island_neighbors took %s to run"%(time.time() - start_time))
					return False
				if (island_tuple[0],island_tuple[1]-1) in adj_superbin:
					#print("check_island_neighbors took %s to run"%(time.time() - start_time))
					return False
		#print("check_island_neighbors took %s to run"%(time.time() - start_time))
		return True
	def find_empty_neighbors(self, superbin_tuple):
		start_time = time.time()
		list_of_empty_neighbors = []
		superbin = self.superbin_indices[self.get_superbin_number(superbin_tuple)]  ## the superbin of interest
		for tuple_ in superbin:
			if  (tuple_[0]+1,tuple_[1]) not in superbin:
				if (tuple_[0]+1) < combineHistBins.n_bins_x:
					counts = self.counts_in_superbin(self.get_superbin_number( (tuple_[0]+1,tuple_[1])  ))
					if (counts is not None) and (counts == 0) and (self.get_superbin_number( (tuple_[0]+1,tuple_[1])  ) not in list_of_empty_neighbors) :
						list_of_empty_neighbors.append( self.get_superbin_number( (tuple_[0]+1,tuple_[1])  ) )
			if (tuple_[0]-1,tuple_[1]) not in superbin:
				if (tuple_[0]-1) > 0:
					counts = self.counts_in_superbin(self.get_superbin_number( (tuple_[0]-1,tuple_[1])  ))
					if (counts is not None) and (counts == 0) and (self.get_superbin_number( (tuple_[0]-1,tuple_[1])  ) not in list_of_empty_neighbors) :
						list_of_empty_neighbors.append( self.get_superbin_number( (tuple_[0]-1,tuple_[1])  ) )
			if (tuple_[0],tuple_[1]+1) not in superbin:
				if (tuple_[1]+1) < combineHistBins.n_bins_y:
					counts = self.counts_in_superbin(self.get_superbin_number( (tuple_[0],tuple_[1]+1)  ))
					if (counts is not None) and (counts == 0) and (self.get_superbin_number( (tuple_[0],tuple_[1]+1)  ) not in list_of_empty_neighbors) :
						list_of_empty_neighbors.append( self.get_superbin_number( (tuple_[0],tuple_[1]+1)  ) )
			if (tuple_[0],tuple_[1]-1) not in superbin:
				if (tuple_[1]-1) >= 0:
					counts = self.counts_in_superbin(self.get_superbin_number( (tuple_[0],tuple_[1]-1)  ))
					if (counts is not None) and (counts == 0) and (self.get_superbin_number( (tuple_[0],tuple_[1]-1)  ) not in list_of_empty_neighbors) :
						list_of_empty_neighbors.append( self.get_superbin_number( (tuple_[0],tuple_[1]-1)  ) )
		#rint("find_empty_neighbors took %s to run"%(time.time() - start_time))
		return list_of_empty_neighbors   # return list of empty nearby superbins

	def fill_in_holes(self):



		### This won't completely work, best way to do this is to find the perimeter bin numbers and make sure everything within that in a row/column is filled


		## loop over all rows 

		# fill in holes within each superjet

		# how to find larger holes inside histogram'
		#for each row and column, store the max and min bin index 
		maxBin_row     = combineHistBins.n_bins_x*[-9999]  #index refers to the maximum row index for column with this index
		maxBin_column = combineHistBins.n_bins_y*[-9999]  #index refers to the maximum column index for row with this index 

		minBin_row     = combineHistBins.n_bins_x*[9999]  #index refers to the min row index for column with this index
		minBin_column = combineHistBins.n_bins_y*[9999]  #index refers to the min column index for 

		# go through all superbins, find these max indices for each row
		# go through the superbins, find any empty superbins with indices less than this and add them to adjacent non-empty superbins with fewest counts


		"""for iii in range(0, combineHistBins.n_bins_x):
			for jjj in range(0,combineHistBins.n_bins_y):
				if 
		"""

		## not working 

		for superbin_index,superbin in enumerate(self.superbin_indices):
			for _tuple in superbin:

				if self.counts_in_superbin(superbin_index) == 0:
					continue   # only want to use the bin values from superbins that are actually full    ### test to make sure we get the correct values
				#print("tuple: (%s/%s)"%(_tuple[0],_tuple[1]))

				### -9999/9999 value means whole row is empty (not uncommon for fringes)
				if _tuple[0] > maxBin_column[_tuple[1]]:
					maxBin_column[_tuple[1]] = _tuple[0]
				if _tuple[0] < minBin_column[_tuple[1]]:
					minBin_column[_tuple[1]] = _tuple[0]
				if _tuple[1] > maxBin_row[_tuple[0]]:
					maxBin_row[_tuple[0]]  = _tuple[1]
				if _tuple[1] < minBin_row[_tuple[0]]:
					minBin_row[_tuple[0]] = _tuple[1]

		### could test this by filling histogram bins between the min and max quantity for a rows

		boundary_test_hist = ROOT.TH2F("boundary_test_hist", "hist boundaries; diSuperjet mass (GeV); avg superjet mass (GeV)", 22,1250., 9500, 20, 500, 3500)  # 375 * 125


		for iii in range(0,combineHistBins.n_bins_x):
			for jjj in range(0,combineHistBins.n_bins_y):
				if maxBin_column[jjj] == -9999 or minBin_column[jjj] == 9999:
					continue
				if maxBin_row[iii] == -9999 or minBin_row[iii] == 9999:
					continue
				superbin_index = self.get_superbin_number((iii,jjj))
				if (iii <= maxBin_column[jjj]) and (iii >= minBin_column[jjj]) and self.counts_in_superbin(self.get_superbin_number((iii,jjj) )) == 0:
					list_of_neighbors = self.get_list_of_neighbors( (iii,jjj))
					neighbor_counts = [self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors]
					mergeIndex = list_of_neighbors[neighbor_counts.index(min(neighbor_counts))] # add to the neighbor with the fewest counts
					print("merged hole %s with %s"%(self.superbin_indices[superbin_index],self.superbin_indices[mergeIndex] ) )
					self.superbin_indices[mergeIndex].extend(self.superbin_indices[superbin_index])
					self.superbin_indices.remove(self.superbin_indices[superbin_index])
				elif (jjj < maxBin_row[iii]) and (jjj > minBin_row[iii]) and self.counts_in_superbin(self.get_superbin_number((iii,jjj) )) == 0:
					list_of_neighbors = self.get_list_of_neighbors( (iii,jjj))
					neighbor_counts = [self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors]
					mergeIndex = list_of_neighbors[neighbor_counts.index(min(neighbor_counts))] # add to the neighbor with the fewest counts
					print("merged hole %s with %s"%(self.superbin_indices[superbin_index],self.superbin_indices[mergeIndex] ) )
					self.superbin_indices[mergeIndex].extend(self.superbin_indices[superbin_index])
					self.superbin_indices.remove(self.superbin_indices[superbin_index])
		
		"""
		print("After running the entire algorithm, we find the following max column values for given rows 1-20: %s"%maxBin_column  )
		print("After running the entire algorithm, we find the following min column values for given rows 1-20: %s"%minBin_column  )
		print("After running the entire algorithm, we find the following max row values for given columns 1-22: %s"%maxBin_row  )
		print("After running the entire algorithm, we find the following min row values for given columns 1-22: %s"%minBin_row  )
		"""
		#with the max and min bins, need to scroll over all superbins and see which ones are within the boundaries for each row/column
		#if the superbin is empty and within he boundaries, merge the bin to neighbor
		return
		"""
		# fill in holes between superbin (possibly not working?)
		# loop over all empty superbins and see if all neighbors (not diagonals I suppose?) are in superbins (with counts >0), if so, add this bin to the surrounding superbin with the fewest counts 
		for superbin_index,superbin in enumerate(self.superbin_indices):
			if  self.counts_in_superbin(superbin_index) == 0 and len(superbin) == 1:   # single bin superbin with no counts
				#print ("finding stuff past here")
				#print("The bin is (%s,%s) and the shifted bin in question is (%s,%s) with counts %s"%(superbin[0][0],superbin[0][1], superbin[0][0],superbin[0][1]+1, ))
				if superbin[0][1]+1 < combineHistBins.n_bins_y and self.counts_in_superbin( self.get_superbin_number( (superbin[0][0],superbin[0][1]+1    ) ) ) > 0  :
					if superbin[0][1]-1 >= 0 and  self.counts_in_superbin( self.get_superbin_number( (superbin[0][0],superbin[0][1]-1    )) )  > 0:
						if superbin[0][0]+1 < combineHistBins.n_bins_x and self.counts_in_superbin( self.get_superbin_number( (superbin[0][0]+1,superbin[0][1]    )) )> 0:
							if superbin[0][1]-1 >= 0 and self.counts_in_superbin( self.get_superbin_number( (superbin[0][0]-1,superbin[0][1]    )) )> 0:
								#add superbin to adjacent superbin with fewest counts 

		"""
	def do_bin_merging(self):
		all_bins_good = False
		iteration_count = 0
		while not all_bins_good:

			print("Starting on run-through %i"%(iteration_count+1))

			if(iteration_count == 100): # don't want this going on forever
				test_counts = [ self.counts_in_superbin(superbin_number) for superbin_number in range(0,len(self.superbin_indices))]
				return
			# do a run-through of the bin merging
			for iii in reversed(range(0,combineHistBins.n_bins_x)):
				for jjj in reversed(range(0, combineHistBins.n_bins_y)):


					#print("superbin is %s"%self.superbin_indices[self.get_superbin_number((iii,jjj))])
					#print("total bin uncertainty %s (%s): %s"%(self.get_superbin_number((iii,jjj)),self.superbin_indices[self.get_superbin_number((iii,jjj))], self.all_hist_values.get_bin_total_uncert(self.superbin_indices[self.get_superbin_number((iii,jjj))])))
					#print("doing bin merging on (%s,%s) "%(iii,jjj))
					other_iii = combineHistBins.n_bins_x - (iii+1)
					other_jjj = combineHistBins.n_bins_y - (jjj+1)

					######################################
					#### starting at top-right corner ####
					######################################

					superbin_number   = self.get_superbin_number( (iii,jjj))
					superbin_counts = self.counts_in_superbin(superbin_number)
					if (superbin_counts == 0):  
						continue
					if ( ( self.all_hist_values.get_bin_total_uncert(self.superbin_indices[self.get_superbin_number( (iii,jjj))] )  )  < 0.25):  #     1.0/sqrt(self.counts_in_superbin(self.get_superbin_number( (iii,jjj ) ) ) )
						#print("This bin has low enough statistical uncertainty. Skipped.")
						continue

					#print("Looking at bin %s"%self.get_superbin_number( (iii,jjj)) )
					list_of_neighbors = self.get_list_of_neighbors( (iii,jjj) ) # all neighbors of this bin and all bins in its parent superbin 
					#neighbor_counts   = [ self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors]
					neighbor_weights   =  [ self.calculate_bin_weight(superbin_number, neighbor_index) for neighbor_index in list_of_neighbors]   #[ self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors]

					if len(list_of_neighbors) == 0:
						continue
					mergeIndex = list_of_neighbors[neighbor_weights.index(min(neighbor_weights))] # add to the neighbor with the fewest counts
					#print("Merging %s with %s"% ( self.superbin_indices[mergeIndex],self.superbin_indices[superbin_number]   ))
					self.superbin_indices[mergeIndex].extend(self.superbin_indices[superbin_number])
					self.superbin_indices.remove(self.superbin_indices[superbin_number])



					##########################################
					#### starting from bottom-left corner ####
					##########################################

					superbin_number   = self.get_superbin_number( (other_iii,other_jjj))
					superbin_counts = self.counts_in_superbin(superbin_number)
					if (superbin_counts == 0):
						continue

					if ( self.all_hist_values.get_bin_total_uncert(self.superbin_indices[self.get_superbin_number( (other_iii,other_jjj))] )   < 0.25     ):   #   # 1.0/sqrt(self.counts_in_superbin(self.get_superbin_number( (other_iii,other_jjj ) ) ) )
						continue

					list_of_neighbors = self.get_list_of_neighbors( (other_iii,other_jjj) ) # all neighbors of this bin and all bins in its parent superbin 
					neighbor_weights   = [ self.calculate_bin_weight(superbin_number, neighbor_index) for neighbor_index in list_of_neighbors] #[ self.counts_in_superbin(neighbor_index) for neighbor_index in list_of_neighbors] #   #
					if len(list_of_neighbors) == 0:
						continue
					mergeIndex = list_of_neighbors[neighbor_weights.index(min(neighbor_weights))] # add to the neighbor with the fewest counts
					#print("Merging %s with %s"% ( self.superbin_indices[mergeIndex],self.superbin_indices[superbin_number]   ))
					self.superbin_indices[mergeIndex].extend(self.superbin_indices[superbin_number])
					self.superbin_indices.remove(self.superbin_indices[superbin_number])

			# loop over all bins in a superbin and see if it's an island
			# if there are no neighbor bins that are not in the superbin, it's an island
			### do this in a random order
			range_x = list(range(0,combineHistBins.n_bins_x))
			range_y = list(range(0,combineHistBins.n_bins_y))
			random.seed(123456)
			shuffle(range_x)
			shuffle(range_y)
			for iii in range_x:
				for jjj in range_y:

					#print("checking islands (%s,%s)"%(iii,jjj))
					superbin_num = self.get_superbin_number((iii,jjj))
					superbin_counts = self.counts_in_superbin( superbin_num)
					superbin = self.superbin_indices[superbin_num]
					if ( (superbin_counts == 0) ):
						continue
					if (      (  self.all_hist_values.get_bin_total_uncert(self.superbin_indices[self.get_superbin_number( (iii,jjj))] )    < 0.25)   ):   #  1.0/sqrt(self.counts_in_superbin(self.get_superbin_number( (iii,jjj ) ) ) )
						continue
					if ( (iii > 0) and (jjj > 0) and (iii < (combineHistBins.n_bins_x)) and (jjj < (combineHistBins.n_bins_y)) ):
						#find superbin neighbors
						is_an_island = True

						#print("checking islands neighbors for (%s,%s)"%(iii,jjj))

						#### need to add something here to see if the island bin is touching any other superbin that has counts
						is_an_island = self.check_island_neighbors(superbin_num)
						#print("this is an island (%s,%s)"%(iii,jjj))

						if not (len(self.get_list_of_neighbors( (iii,jjj) )) ==0 ):   # are there any neighbors with counts greater than 0? if so, this is not an island
							is_an_island = False


						if is_an_island:
							#rint("superbin_indices: %s"%self.superbin_indices)
							#print("The island in question is ", (iii,jjj))


							### need each island to expand 
							empty_neighbor_indices = self.find_empty_neighbors((iii,jjj))
							#print("checking islands neighbors for (%s,%s)"%(iii,jjj))

							#print("The list of empty neighbor superbins is %s"%empty_neighbor_indices)
							#print("------ the neighbor indices are %s"%empty_neighbor_indices)
							empty_neighbor_superbins = [self.superbin_indices[empty_index] for empty_index in empty_neighbor_indices]
							#print("The empty neighbor superbins are %s"%empty_neighbor_superbins)
							for empty_neighbor_superbin in empty_neighbor_superbins:

								#print("empty_neighbor_superbin is %s"%empty_neighbor_superbin)
								empty_neighbor_index = self.get_superbin_number(empty_neighbor_superbin[0])
								island_index = self.get_superbin_number((iii,jjj))
								#print("island/empty_neighbor_indices: %s/%s"%(island_index,empty_neighbor_index))

								if empty_neighbor_index in self.superbin_indices[island_index]:
									continue

								#print("island superbin entry is %s, now adding %s"%(self.superbin_indices[island_index], self.superbin_indices[empty_neighbor_index]))
								self.superbin_indices[island_index].extend(self.superbin_indices[empty_neighbor_index])
								#print("removing %s from superbin "%self.superbin_indices[empty_neighbor_index])
								self.superbin_indices.remove(self.superbin_indices[empty_neighbor_index])
								#print("island superbin now looks like: %s "%self.superbin_indices[island_index])

			iteration_count+=1
			all_bins_good = self.all_bins_are_good()
		return
	
	
if __name__=="__main__":
	print("Calculating bin groupings for best statistical uncertainties")
	out_txt_file = open("/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/txtfiles/superbin_indices.txt","w")
	years = {"2015","2016","2017","2018"}
	regions = {"SR","CR"}
	c = ROOT.TCanvas("c", "canvas", 1000, 1050)
	for region in regions:
		for year in years:



			hist_path = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/allBR_expectedCounts_%s_%s.root"%(region,year)
			hist_name = "h_MSJ_mass_vs_MdSJ_" +region
			TH2_file = ROOT.TFile.Open(hist_path,"READ")
			TH2_hist = TH2_file.Get(hist_name)
			TH2_hist_merged_name = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudyAlt/mergedBinFiles/allBR_statUncert_%s_%s_MERGED_BINS.root"%(region,year)
			TH2_hist_new_bins_name = "/Users/ethan/Documents/rootFiles/statisticalUncertaintyStudy/mergedBinFiles/allBR_statUncert_%s_%s_NEW_BINS.root"%(region,year)
			out_file = ROOT.TFile.Open(TH2_hist_new_bins_name,"RECREATE")

			# give histogram to constructor
			testCase = combineHistBins(TH2_hist,year, region)
			#create a dummy histogram with dimensions 20x22
			merged_bins = testCase.superbin_indices
			bin_map_hist = ROOT.TH2F("bin_map_hist", ("Map of how bins were merged in %s for %s; diSuperjet mass (GeV); avg superjet mass (GeV)"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
			stat_uncert_hist = ROOT.TH2F("stat_uncert_hist", ("Statistical Uncertainty (post bin merging) in the %s for %s; diSuperjet mass (GeV); avg superjet mass (GeV)"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
			merged_hist_count = ROOT.TH2F("merged_hist_count", ("Bin Counts (post bin merging) in the %s for %s; diSuperjet mass (GeV); avg superjet mass (GeV)"%(region, year)), 22,1250., 9500, 20, 500, 3500)  # 375 * 125
			R = ROOT.TRandom3()
			for superbin_index, superbin in enumerate(merged_bins):
				random.seed(12345)
				rndm = R.Uniform(0,10000)
				for smallbin in superbin:
					if testCase.counts_in_superbin(superbin_index) == 0:   # don't show indices for empty bins
						continue					
					bin_map_hist.SetBinContent(smallbin[0],smallbin[1],rndm)
					stat_uncert_hist.SetBinContent(smallbin[0],smallbin[1], testCase.all_hist_values.get_bin_total_uncert(testCase.superbin_indices[superbin_index]))    #   1.0/sqrt(testCase.counts_in_superbin(superbin_index))   
					merged_hist_count.SetBinContent(smallbin[0],smallbin[1], testCase.counts_in_superbin(superbin_index))


			out_txt_file.write("%s/%s/%s\n"%(year,region, testCase.superbin_indices))

			c = ROOT.TCanvas("c", "canvas", 1000, 1050)

			ROOT.gStyle.SetOptStat(0)
			bin_map_hist.GetZaxis().SetRangeUser(0,10000)
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


