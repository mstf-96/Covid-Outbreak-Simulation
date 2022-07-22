
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

class Virus
{
public:
	Virus();
	~Virus();

	void set_Death_Rate(unsigned d_rate) { Death_rate = d_rate; }
	void set_Nerkh_Shoyu(unsigned shoyo) { Nerkh_shoyu = shoyo; }

	unsigned get_Death_Rate() { return Death_rate; }
	unsigned get_Nerkh_Shoyu() { return Nerkh_shoyu; }
				

private:
	unsigned Death_rate;						// nerkh koshande boodan bimary
	unsigned Nerkh_shoyu;                       
	
};







