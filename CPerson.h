#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CVirus.h"
using namespace std;

class Person
{
public:
	Person();
	~Person();

	void add_Contact(Person*);
	void print_Contacts()const;

	bool is_Alive()const { return Alive; }
	bool is_Sick()const { return Sick; }
	bool get_Was_Sick()const { return Was_Sick; }

	int get_Sickness_Level()const { return Sickness_level; }
	int get_Sick_Day()const { return Sick_day; }
	int get_Death_Day()const { return Death_day; }
	int get_Id()const { return Id; }
	

	void simulate_A_Day_For_Sick_Person(Virus*,int);				//shabih sazi yek roz bara har fard:agar taraf mariz bashe mire az dakhel contact hash afrad ro mariz mikone
	void set_Sick(int date);										//mariz kardan yek fard dar yek tarikh
	void set_Id(int);												//be har nafar yek id moshakhas dadn
	void print_Sick_Day(int, ofstream&);                            
	void print_Death_Day(int, ofstream&);
	void print_Cured_Day(int, ofstream&);
	void print_The_Result_Of_Person(ofstream& fout);                    //khoroji natije koli har fard
	
	
private:
	int Id;
	bool Was_Sick;
	bool Alive;
	bool Sick;
	int Sickness_level;
	int Sick_day;
	int Death_day;
	int Cured_day;
	vector<Person*> Contacts;

	void kill(int);
};