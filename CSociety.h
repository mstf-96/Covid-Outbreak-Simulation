#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "CVirus.h"
#include "CPerson.h"
using namespace std;

class Society
{
public:
	Society();
	Society(int tedad, ifstream& fin ,Virus*);
	~Society();
	void print_Contacts_For_Each_Person();                            //chap kardan shomare id mokhatab hai har fard
	void simulate_A_Day_For_Society(int );                            //shabih sazi yek roz barai jamee 
	void print_Result_Of_Day(int day , ofstream& fout);              //natije roz x ra print mikonad
	void print_result_of_each_person(ofstream& fout);                //natije nahaii ba asas har fard
private:
	int First_Sick_Id;                                               //nafar avali ke mariz mishavad
	vector<Person> Persons;                                          //afrad jamee - jamee araye ii az afrade
	vector<vector<int>> matris_mojaverat;
	Virus* virus;                                                     // * : neshan dahande rabete shenakhtan                         
	
	void find_Contacts_For_Each_Person();                              //kamel kardan ertebatat har fard 
	void set_First_sick_Person(int);                                  //neshan dar kardan avalin fard bimar
};
