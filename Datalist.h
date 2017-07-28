#pragma once
#include<string>
#include <iostream>
#include <fstream>

using namespace std;

struct Datapoint
{
	string data_tag;
	string value;
	Datapoint* next = nullptr;
};

class Datalist
{
public:
	Datalist();
	~Datalist();
	void set(string name, string value);
	string get(string name);
	void print(string name);//Enter name of data to print, enter 'all' to print all the data
	bool has(string name);
	void delete_all();
	Datapoint *head, *tail;
};

