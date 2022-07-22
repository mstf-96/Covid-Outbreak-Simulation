#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "CVirus.h"
#include "CPerson.h"
#include "CSociety.h"

using namespace std;

int choose_output_format();                                 // tabe nahve namayesh khoroji 

enum output_format { afrad = 1, har_rooz = 2, rooz_va_afrad = 3 };

int main()
{
	int tedad_afrad = -1, simulation_duration = -1, out_format = 0;

	srand(time(0));							// baraye fargh kardan adaade random dar har ejra barname

	cout << ".:: WELCOME ::." << endl << endl;
	cout << "Project COVID 19" << endl << endl;
	cout << "lotfan tedad afrade jamee ra vared konid : " << endl;
	do
	{
		cout << "tedad = ";
		try
		{
			cin >> tedad_afrad;
			if (tedad_afrad <= 0)
				throw("ERROR");
		}
		catch (...)
		{
			cerr << "[ERROR] : Yek adade bozorgtar az 0 vared konid." << endl;
		}

	} while (tedad_afrad <= 0);


	ifstream fin("in.txt");                        //jaryan khondan az file 
	if (!fin)
	{
		cerr << "\n[ERROR] : open file failed , probably file (in.txt) doesn't exist.\n" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		cout << "\nFile in.txt opened succesfully.\n" << endl;
	}

	ofstream fout("out.txt", ios::trunc);
	if (!fout)
	{
		cerr << "\n[ERROR] : open file failed , could not open file (out.txt).\n" << endl;
		system("pause");
		exit(1);
	}
	else
	{
		cout << "\nFile out.txt opened succesfully.\n" << endl;
	}

	Virus corona;
	Society jamee(tedad_afrad, fin, &corona);

	jamee.print_Contacts_For_Each_Person();

	cout << "\nLotfan modate shabih sazi ra vared konid (duration > 0) : " << endl;

	do
	{
		cout << "Duration = ";
		try
		{
			cin >> simulation_duration; ;
			if (simulation_duration <= 0)
				throw("ERROR");
		}
		catch (...)
		{
			cerr << "[ERROR] : Yek adade bozorgtar az 0 vared konid." << endl;
		}

	} while (simulation_duration <= 0);


	out_format = choose_output_format();

	for (int i = 1; i <= simulation_duration; i++)						//anjame shabih sazi
	{
		jamee.simulate_A_Day_For_Society(i);

		if (out_format == har_rooz || out_format == rooz_va_afrad)
		{
			if (i == 1)
			{
				jamee.print_Result_Of_Day(0, fout);                   //print roz 0
			}
			jamee.print_Result_Of_Day(i, fout);                       //print baghie roza 
		}

	}

	if (out_format == afrad || out_format == rooz_va_afrad)
		jamee.print_result_of_each_person(fout);

	cout << "\n\n------------------------------------------------------------------" << endl;
	cout << "\nShabih sazi ba movafaghiat anjam shod." << endl;
	cout << "\nKhoruji dar file (out.txt) ba movafaghiat print shod." << endl;
	cout << "\n\n------------------------------------------------------------------" << endl;
	cout << "\nA work by : " << endl;
	cout << "\t\tMostafa Nakhaei nezhad" << endl;
	cout << "\t\tArian Asgar nezhad" << endl;
	cout << "\t\tAli Hosseinian" << endl << endl << endl;

	fin.close();
	fout.close();

	system("pause");
	return 0;
}


int choose_output_format()
{
	int opt = 0;

	cout << "\nNahve namayesh khoruji ra entekhab konid :" << endl << endl;
	cout << "1. Namayesh natije har fard pas az etmame shabih sazi" << endl;
	cout << "2. Namayesh natije pas az payane har rooz" << endl;
	cout << "3. Har do" << endl;

	do
	{
		cout << "Option = ";
		try
		{
			cin >> opt;
		}
		catch (...)
		{
			cerr << "adade 1 ya 2 ra vared konid." << endl;
		}
	} while (opt != 1 && opt != 2 && opt != 3);

	return opt;
}
