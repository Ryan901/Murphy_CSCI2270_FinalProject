#include "Graph.h"
void startup(Graph &g);
int main()
{
	int choice = 0;
	int subchoice,trial;
	string name, input, data, group_name;
	Graph g;
	cout << "Enter 1 to load the trial data set. Enter 0 to continue to the main menu." << endl;
	cin >> trial;
	if (trial == 1)
	{
		startup(g);
	}
	while (choice != 10)
	{
		cout << "Main Menu" << endl
			<< "1. Add person." << endl
			<< "2. Add data to person." << endl
			<< "3. Add a group." << endl
			<< "4. Print a node. " << endl
			<< "5. Calculate group intersections." << endl
			<< "6. Write to file." << endl
			<< "7. Read from file." << endl
			<< "8. Print all nodes" << endl
			<< "9. Search for an employee"<<endl
			<< "10. Quit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Enter person's full name." << endl;
			cin.ignore();
			getline(cin, input);
			g.add_person(input);
			break;
		}
		case 2:
		{
			cin.ignore();
			cout << "Enter person's full name." << endl;
			getline(cin, name);
			cout << "Enter data name. Ex. Telephon, Email" << endl;
			getline(cin, input);
			cout << "Enter the " << input << " for " << name << endl;
			getline(cin, data);
			g.add_data(name, input, data);
			break;
		}
		case 3:
		{
			cin.ignore();
			cout << "Enter the group or person you wish to link from." << endl;
			getline(cin, group_name);
			int subchoice = 1;
			int counter = 1;
			vector<string> names;
			while (subchoice == 1)
			{
				cout << "Enter link to member #" << counter << ":" << endl;
				getline(cin, name);
				names.push_back(name);
				++counter;
				cout << "Would you like to enter another member to link to? 1. Yes, 2. No" << endl;
				cin >> subchoice;
				cin.ignore();
			}
			g.add_group(group_name, names);
			break;
		}
		case 4:
		{
			cout << "Entry name?" << endl;
			cin.ignore();
			getline(cin, name);
			g.print(name);
			break;
		case 5:
		{
			int subchoice = 1;
			vector<string> group_names;
			int count = 1;
			cin.ignore();
			while (subchoice == 1)
			{
				cout << "Enter group name # " << count << endl;
				getline(cin, group_name);
				group_names.push_back(group_name);
				cout << "Would you like to enter another group name? 1. Yes, 2. No" << endl;
				cin >> subchoice;
				cin.ignore();
				++count;
			}
			g.get_group_intersections(group_names);
			break;
		}
		case 6:
		{
			cin.ignore();
			cout << "Enter filename:" << endl;
			getline(cin, name);
			g.write_file(name);
			break;
		}
		case 7:
		{
			cin.ignore();
			cout << "Enter filename:" << endl;
			getline(cin, name);
			g.read_file(name);
			break;
		}
		case 8:
		{
			g.print_nodes();
			break;
		}
		case 9:
		{
			cin.ignore();
			stringstream ss;
			string search;
			vector<string>search_terms;
			cout << "Enter search phrase to search for employee" << endl;
			getline(cin, search);
			ss << search;
			while(ss.good())
			{
				getline(ss, search, ' ');
				search_terms.push_back(search);
			}
			cout << endl;
			g.search(search_terms);
			break;
		}
		}
		}
	}
}

void startup(Graph &g)
{
	g.add_person("John Smith");
	g.add_data("John Smith", "Telephone", "111-222-3333");
	g.add_data("John Smith", "Email", "john.smith@testers.run");
	g.add_person("David Dix");
	g.add_data("David Dix", "Telephone", "111-222-3333");
	g.add_data("David Dix", "Email", "david.dix@testers.run");
	g.add_person("Matt Strong");
	g.add_data("Matt Strong", "Telephone", "111-222-3333");
	g.add_data("Matt Strong", "Email", "matt.strong@testers.run");
	g.add_person("Nathan Toole");
	g.add_data("Nathan Toole", "Telephone", "111-222-3333");
	g.add_data("Nathan Toole", "Email", "nathan,toole@testers.run");
	g.add_person("Jennifer Crane");
	g.add_data("Jennifer Crane", "Telephone", "111-222-3333");
	g.add_data("Jennifer Crane", "Email", "jennifer.crane@testers.run");
	g.add_person("Kate Mathews");
	g.add_data("Kate Mathews", "Telephone", "111-222-3333");
	g.add_data("Kate Mathews", "Email", "kate.mathews@testers.run");
	g.add_person("Amanda Walters");
	g.add_data("Amanda Walters", "Telephone", "111-222-3333");
	g.add_data("Amanda Walters", "Email", "amanda.walters@testers.run");
	g.add_person("John Samuels");
	g.add_data("John Samuels", "Telephone", "123-456-789");
	g.add_data("John Samuels", "Email", "john.samuels@testers.run");
	g.add_group("Boulder Office", { "John Smith","David Dix","Jennifer Crane" });
	g.add_group("Summer Project", { "John Smith","Amanda Walters","Matt Strong","Nathan Toole" },"Working on the");
	g.add_group("Denver Office", { "Matt Strong","Nathan Toole","Amanda Walters","Kate Mathews","John Samuels" }, "Location: ");
	g.add_group("Kate Mathews", { "Matt Strong","Nathan Toole","Amanda Walters" }, "Supervisor of");
	g.add_relation("Matt Strong", "Kate Mathews", "Supervisor is");
	g.add_relation("Nathan Toole", "Kate Mathews", "Supervisor is");
	g.add_relation("Amanda Walters", "Kate Mathews", "Supervisor is");
}