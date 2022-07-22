#include "CVirus.h"
#include <exception>


Virus::Virus():Death_rate(-1),Nerkh_shoyu(-1)
{

	cout << "Please Enter Death Rate of the virus : [0-100] "<<endl;
	do
	{
		cout << "Death rate = ";
		try
		{
			cin >> Death_rate;
		}
		catch(...)
		{
			cout << "Please enter a number between 0 and 100 " << endl;
		}
	} while (Death_rate < 0 || Death_rate > 100);
	
	cout << "Please Enter nerkh Shoyu virus : [0-100] "<< endl;
	do
	{
		cout << "Nerkh shoyu bimary = ";
		try
		{
			cin >> Nerkh_shoyu;
		}
		catch(...)
		{
			cout << "Please enter a number between 0 and 100 " << endl;
		}
	} while (Nerkh_shoyu < 0 || Nerkh_shoyu > 100 );
	
}


Virus::~Virus()
{

}





