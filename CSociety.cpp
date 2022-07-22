#include "CSociety.h"
#include <exception>

using namespace std;


Society::Society() : First_Sick_Id(0)
{

}
Society::Society(int tedad, ifstream& fin, Virus* vp) : virus(vp) , First_Sick_Id(0)
{
	vector<Person> p(tedad);

	Persons = p;                                           //ghar dadan vector afrad dar in vector

	for (int i = 0; i < tedad; i++)                        //khondan matris mijaverat
	{
		vector<int> v;
		for (int j = 0; j < tedad; j++)
		{
			int x = -1;
			try
			{
				fin >> x;
				if (x != 0 && x != 1)
					throw ("In file (in.txt) Just 0 and 1 is valid.");

				v.push_back(x);
			}
			catch (...)
			{
				cerr << "\n[ERROR] : File (in.txt) should consist of a 2D array ("<<tedad<<"*"<<tedad<<") filled only with 0 or 1." << endl;
				cerr << "Please fix file (in.txt) and try again." << endl << endl;
				system("pause");
				exit(1);
			}
		}
		matris_mojaverat.push_back(v);
	}

	try
	{
		for (int i = 0; i < tedad; i++)
		{
			for (size_t j = 0; j < tedad; j++)
			{
				if (matris_mojaverat[i][j] != matris_mojaverat[j][i])
				{
					throw("[ERROR]");
				}
			}
		}
	}
	catch (...)
	{
		cerr << "[ERROR] : File (out.txt) marboot be matris mojaverat bayad motagharen bashad." << endl;
		cerr << "lotfan file ra tashih karde va mojadad talash konid." << endl;

		system("pause");
		exit(1);
	}
	
	find_Contacts_For_Each_Person();                                        //peyda kardan contact hai har fard

	for (size_t i = 0; i < Persons.size(); i++)								//  dorost kardan Id har fard  
	{
		Persons[i].set_Id(i + 1);
	}

	set_First_sick_Person(tedad);
}


Society::~Society()
{

}

void Society::find_Contacts_For_Each_Person()
{
	for (size_t i = 0; i < matris_mojaverat.size(); i++)
	{
		for (size_t j = 0; j < matris_mojaverat[i].size(); j++)
		{
			if (matris_mojaverat[i][j] == 1)
				Persons[i].add_Contact(&Persons[j]);                          //addres nafar j mizare to contact hai fard i
		}
	}
}

void Society::set_First_sick_Person(int tedad)
{
	string opt;
	cout << "\nPlease choose an option and enter it's number :" << endl << endl;
	cout << "1. I want to specify the first person with the virus" << endl;
	cout << "2. Choose a random person" << endl << endl;
	do
	{
		cout << "Option = ";
		cin >> opt;
		if (opt != "1" && opt != "2")
			cout << "please enter 1 or 2 :" << endl;

	} while (opt != "1" && opt != "2");

	if (opt == "1")
	{
		cout << "Please Enter First sick person's ID (1," << tedad << ") : " << endl;
		do
		{
			cout << "Id = ";
			try
			{
				cin >> First_Sick_Id;
				if (First_Sick_Id<1 && First_Sick_Id>tedad)
					throw("ERROR");
			}
			catch(...)
			{
				cerr << "[ERROR] : Id must be a number between 1 and "<<tedad<<" ." << endl;
			}
			
		}while (First_Sick_Id<1 && First_Sick_Id>tedad);
		
	}
	else if (opt == "2")
	{
		First_Sick_Id = (rand() % tedad) + 1;
	}

	Persons[First_Sick_Id - 1].set_Sick(0);                  //nafar id bedast amde dar roz 0 mariz shode ast
}


void Society::print_Contacts_For_Each_Person()				// for debugging 
{
	cout << "\nContacts for each person of society :" << endl;
	for (size_t i = 0; i < Persons.size(); i++)
	{
		cout << "Person [" << i + 1 << "] : ";
		Persons[i].print_Contacts();
		cout << endl;
	}
}

void Society::simulate_A_Day_For_Society(int date)                       // mariz kardan contact hai fard bimar 
{
	for (size_t i = 0; i < Persons.size(); i++)
	{
		if(Persons[i].is_Alive() && Persons[i].is_Sick())				// bayd fard zende v mariz bashad ta betone contact hasho mariz kone
		{
			Persons[i].simulate_A_Day_For_Sick_Person(virus,date);
		}
		else
		{
			continue;
		}
	}
}

void Society::print_Result_Of_Day(int day, ofstream& fout)
{
	
	fout << "Day " << day << " :" << endl;
	fout << "Got sick today :";
	for (size_t i = 0; i < Persons.size(); i++)
	{
		Persons[i].print_Sick_Day(day, fout);
	}
	fout << "\nDied today :";
	for (size_t i = 0; i < Persons.size(); i++)
	{
		Persons[i].print_Death_Day(day, fout);
	}
	fout << "\nGot cured today :";
	for (size_t i = 0; i < Persons.size(); i++)
	{
		Persons[i].print_Cured_Day(day, fout);
	}
	fout << "\n-----------------------------------------------------------" << endl;
}


void Society::print_result_of_each_person(ofstream& fout)                          // khoroji natije bar asas har fard
{

	for (size_t i = 0; i < Persons.size(); i++)
	{
		Persons[i].print_The_Result_Of_Person(fout);
	}
}
