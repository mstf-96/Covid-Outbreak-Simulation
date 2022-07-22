#include "CPerson.h"
#include "CVirus.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>

using namespace std;

Person::Person()                                 // constructor
{                                            
	Id = 0;
	Was_Sick = false;							//ghablan bimar bodan ya nabodn
	Cured_day = -1;								//rozi ke khob mishe
	Alive = true;								//zende bodan ya nabodn
	Sick = false;								//bimar bodan ya nabodan
	Sickness_level = 0;							//daraje bimari har fard
	Sick_day = -1;								//  -1 : mariz nashode 
	Death_day = -1;								//  -1 : fot nashode	
}

Person::~Person()                               //chon chizi ro new nakrdim distructor khalie
{
	                                            //vector khodesh yek distructor dare
}

void Person::add_Contact(Person* p)
{
	if (find(Contacts.begin(), Contacts.end(), p) == Contacts.end())            //check kardan nabod contact tekrari dar vector har fard
	{
		Contacts.push_back(p);
	}
}

void Person::print_Contacts()const                                             //chap kardan id afradi ke ba an ertebat darim
{
	for (size_t i = 0; i < Contacts.size(); i++)
	{
		cout <<"["<< Contacts[i]->get_Id() << "] ";
	}
}

void Person::set_Sick(int day)                                             //ijad taghirat dar method afrad mariz shode
{
	Sickness_level = 10;
	Sick = true;
	Sick_day = day;
	Was_Sick = true;
}

void Person::kill(int day)                                          //ijad taghirat dar method afradi ke mimirand 
{
	Alive = false;
	Death_day = day;
}

void Person::simulate_A_Day_For_Sick_Person(Virus* v, int day)               // 1:mariz kardan contacts   2:mordan ya namordan fard mariz
{
	int ehtemal;
	for (size_t i = 0; i < Contacts.size() && Sick_day!=day; i++)
	{
		if (Contacts[i]->is_Alive() && !Contacts[i]->is_Sick() && !Contacts[i]->get_Was_Sick())
		{
			ehtemal = v->get_Nerkh_Shoyu() * Sickness_level / 10;
			int random = (rand() % 100) + 1;	// 1 - 100
			if (random <= ehtemal)
				Contacts[i]->set_Sick(day);
		}
	}

	if (Sick_day != day)
	{
		ehtemal = v->get_Death_Rate() * Sickness_level / 10;
		int random = rand() % 100 + 1;  //1 - 100
		if (random <= ehtemal)
			this->kill(day);
	}
	
	if (Sick_day != day && Sickness_level > 0)                                     //kam kardan darje bimari fard mariz
	{
		--Sickness_level;
		if (Sickness_level <= 0)                                                   //payan dore bimari -khob shodan fard
		{
			Sick = false;
			Cured_day = day;
		}
	}
}

void Person::set_Id(int x)
{
	Id = x;
}


void Person::print_Sick_Day(int day,ofstream& fout)                                      //khoroji bar asas har roz
{
	if (Sick_day == day)
		fout << " [" << Id << "]";
}

void Person::print_Death_Day(int day, ofstream& fout)                                    //khoroji bar asas har roz
{
	if (Death_day == day)
		fout << " [" << Id << "]";
}

void Person::print_Cured_Day(int day, ofstream& fout)                                    //khoroji bar asas har roz
{
	if (Cured_day == day)
		fout << " [" << Id<<"]";
}

void Person::print_The_Result_Of_Person(ofstream& fout)                                 ////khoroji bar asas har fard
{
	fout << "[" << Id << "] : ";

	if (!Was_Sick)																		//mariz nmishavad 
		fout << "Alive : This peson did Not get sick." << endl;
	else if (Was_Sick && Cured_day != -1 && Alive)										//mariz shode va khoob shode
		fout << "Alive : Sick day = " << Sick_day << " , Cure day = " << Cured_day << endl;
	else if(Was_Sick && !Alive && Death_day!=-1)										// mariz shode va morde 
		fout<< "Dead : Sick day = " << Sick_day << " , Death day = " << Death_day << endl;
	else if(Was_Sick && Cured_day == -1 && Alive && Death_day==-1)						//mariz shode  khob nashode va zende ast
		fout<< "Alive and Sick : Sick day = " << Sick_day << " , Sickness level = " << Sickness_level << endl;

}
