#include <cmath>
#include <iostream>
#include "TLorentzVector.h"
#include <string>

using namespace std;
#include <iostream>

class sortJets()
{	
	public:
		sortJets(std::vector<TLorentzVector>,std::vector<TLorentzVector>,std::vector<TLorentzVector>);
		void findBestJetComb();

		std::vector<TLorentzVector> superJet1;
		std::vector<TLorentzVector> superJet2;
		std::vector<TLorentzVector> miscJets;
		int nJets;

		std::vector<TLorentzVector> finalSuperJet1;
		std::vector<TLorentzVector> finalSuperJet2;

}	

sortJets::sortJets(std::vector<TLorentzVector> SJ1, std::vector<TLorentzVector> SJ2, std::vector<TLorentzVector> _miscJets )
{
	superJet1 = SJ1;
	superJet2 = SJ2;
	miscJets = _miscJets;
	nJets = superJet1.size() + superJet2.size() + miscJets.size();
	findBestJetComb();
}

void sortJets::findBestJetComb()
{


	TLorentzVector bestSuperJet1;
	TLorentzVector bestSuperJet2;
	double minMassDiff = 9999999999.;
	//nfatjets will be 3+
	if(nJets == 3)
	{
		int useArray[3];
		for(int aaa=0;aaa<2;aaa++)
		{
			for(int bbb=0;bbb<2;bbb++)
			{
				for(int ccc=0;ccc<2;ccc++)
				{
					if( (aaa==bbb) && (aaa==ccc))continue;
					useArray[0]=aaa;useArray[1]=bbb;useArray[2]=ccc;
					TLorentzVector useSuperJet1 = superJet1;
					TLorentzVector useSuperJet2 = superJet2;
					for(int iii = 0;iii<nJets;iii++)
					{	
						if(useArray[iii] == 0)useSuperJet1+=miscJets[iii];
						else{ useSuperJet2+=miscJets[iii];}
					}
					if( abs(useSuperJet1.M() - useSuperJet2.M()) < minMassDiff )
						{
							minMassDiff = abs(useSuperJet1.M() - useSuperJet2.M());
							bestSuperJet1 = useSuperJet1;
							bestSuperJet2 = useSuperJet2;
						} 
				}
			}
		}

	}

	/*
	else if(nJets == 4)
	{
		
	}
	else if(nJets == 5)
	{
		
	}
	else if(nJets == 6)
	{
		
	}
	else if(nJets == 7)
	{
		
	}
	else if(nJets == 8)
	{
		
	}
	else if(nJets == 9)
	{
		
	}
	else{ std::cout << "Event has more than 9 AK8 jets, don't have a case for this" << std::endl;}
	*/
	finalSuperJet1 = bestSuperJet1;
	finalSuperJet2 = bestSuperJet2;
	return;
}

