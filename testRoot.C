#include<TRandom3.h>
#include <iostream>
#include <string>
#include "TLorentzVector.h"

using namespace std;
void testRoot()
{
	TRandom3 *randomNum = new TRandom3(); // for JERs

	//randomNum->SetSeed(7880);
	//double value = randomNum->Gaus(0.,1);
	//std::cout << value<< std::endl;
	for(int iii = 0; iii < 10000; iii++)
	{
		double sigma = 1.0*iii/10.;
		randomNum->SetSeed(iii);
		std::cout << randomNum->GetSeed() << std::endl;
		double gausVar = randomNum->Gaus(0,sigma);
		std::cout << "index/gausVar: " << iii << "/"<<  gausVar << std::endl;
	}

}