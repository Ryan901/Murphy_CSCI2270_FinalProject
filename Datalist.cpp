#include "Datalist.h"



Datalist::Datalist()
{
	head = nullptr;
}


Datalist::~Datalist()
{
	//delete_all();
}

void Datalist::set(string name, string value)
{
	Datapoint *current = new Datapoint;
	current->data_tag = name;
	current->value = value;
	if (!head)
	{
		head = current;
		tail = current;
	}
	else
	{
		tail->next = current;
		tail = current;
	}
	current = nullptr;
	delete current;
}

string Datalist::get(string name)
{
	Datapoint *current = head;
	string result;
	while (current&&current->data_tag != name)
	{
		current = current->next;
	}
	if (current)
	{
		result = current->value;
	}
	else
	{
		result = "null";
	}
	current = nullptr;
	return result;
}

void Datalist::print(string name)
{
	Datapoint *current = head;
	while (current)
	{
		if (name == "all" || current->data_tag == name)
		{
			cout << current->data_tag << ": " << current->value << endl;
		}
		current = current->next;
	}
}

bool Datalist::has(string name)
{
	Datapoint * current = head;
	while(current&&current->data_tag!=name)
	{
		current = current->next;
	}
	if(current)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Datalist::delete_all()
{

	while (head)
	{
		Datapoint *temp = head;
		head = head->next;
		delete temp;
	}
}

/*ostream& operator<<(ostream& os, const Datalist& data)
{
Datapoint * current = data.head;
string temp;
while(current)
{
temp= temp+current->data_tag + "," + current->value+",";
current = current->next;
}
os << temp;
return os;
}*/