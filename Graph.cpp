#include "Graph.h"
#include<algorithm>

bool compare(Vertex left, Vertex right)
{
	return(left.label < right.label);
}

bool search_compare(SearchResult left, SearchResult right)
{
	return left.score > right.score;
}

Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::add_person(string name)
{
	Vertex *to_add = new Vertex;
	to_add->label = name;
	nodes.push_back(*to_add);
}

int Graph::find_node(string name)
{
	for (auto i = nodes.begin(); i<nodes.end(); ++i)
	{
		if (i->label == name)
		{
			return i - nodes.begin();
		}
	}
	return -1;
}

void Graph::add_data(string name, string data_tag, string value)
{
	int index = find_node(name);
	if (index != -1)
	{
		data_terms.push_back(data_tag);
		nodes[index].data.set(data_tag, value);
	}
	else
	{
		cout << "There is no entry for " << name << " data entry failed." << endl;
	}
}

void Graph::add_group(string label, vector<string> people, string type)
{
	if (type == "n/a")
		type = "Group";
	int index = find_node(label);
	if (index == -1)
	{
		Vertex to_add;
		to_add.isGroup = true;
		to_add.label = label;
		nodes.push_back(to_add);
		for (auto i = people.begin(); i != people.end(); ++i)
		{
			add_relation(label, *i, *i);
			add_relation(*i, label, label);
		}
	}
	else
	{

		for (auto j = people.begin(); j != people.end(); ++j)
		{
			bool exists = false;
			for (auto i = nodes[index].edges.begin(); i != nodes[index].edges.end(); ++i)
			{
				if (i->label == *j)
					exists = true;
			}
			if (!exists)
			{
				add_relation(label, *j, type);
			}
		}
	}

}

void Graph::add_relation(string name1, string name2, string label)
{
	int index1, index2;
	index1 = find_node(name1);
	index2 = find_node(name2);
	Edge to_add1, to_add2;
	if (index1 != -1)
	{
		to_add1.v = index2;
		to_add1.label = label;
		nodes[index1].edges.push_back(to_add1);
	}
	else if (index1 == -1)
	{
		cout << "Error: There is no entry for " << name1 << "." << endl
			<< "The relationship between " << name1 << " and " << name2 << " was not created." << endl;
	}
}


void Graph::print(string name, string data_tag)
{
	int to_print = find_node(name);
	print(to_print, data_tag);
}

void Graph::print(int index, string data_tag = "all")
{
	if (index != -1)
	{
		Vertex *to_print = &nodes[index];
		if (to_print->isGroup)
		{
			cout << "Group Name: " << to_print->label << endl;
			if (data_tag != "none")
			{
				cout << "Members:" << endl;
				for (auto i = to_print->edges.begin(); i != to_print->edges.end(); ++i)
				{
					cout << nodes[i->v].label << endl;
					nodes[i->v].data.print(data_tag);
				}
			}
		}
		else
		{
			cout << "Name: " << to_print->label << endl;
			if (!to_print->edges.empty() && (data_tag == "group" || data_tag == "all"))
			{
				cout << "Connections: " << endl;

				for (auto i = to_print->edges.begin(); i != to_print->edges.end(); ++i)
				{
					if (i->label == nodes[i->v].label)
						cout << i->label << endl;
					else
						cout << i->label << " " << nodes[i->v].label << endl;
				}
			}
			to_print->data.print(data_tag);
		}
	}
}

void Graph::print_groups(string data_tag)
{
	cout << "Groups:" << endl;
	for (auto i = nodes.begin(); i != nodes.end(); ++i)
	{
		if (i->isGroup)
		{
			print(i - nodes.begin(), data_tag);
		}
	}

}

vector<Vertex> Graph::get_group_intersections(vector<string> labels)
{
	vector<Vertex> group_nodes;
	vector<Vertex> members;
	for (auto i = labels.begin(); i != labels.end(); ++i)
	{

		int index = find_node(*i);
		if (index != -1)
		{
			Vertex * temp = &nodes[index];
			group_nodes.push_back(*temp);
		}
	}
	if (!group_nodes.empty())
	{

		Vertex temp = group_nodes[0];
		/*int size = temp->edges.size();
		for(auto j=group_nodes.begin();j!=group_nodes.end();++j)
		{
		if(j->edges.size()<size)
		{
		temp = j;
		size = j->edges.size();
		}
		}*/
		for (auto i = temp.edges.begin(); i != temp.edges.end(); ++i)
		{
			members.push_back((nodes[i->v]));
		}
		int goal = labels.size();
		for (vector<Vertex>::iterator m = members.begin(); m != members.end();)
		{
			int found = 0;
			for (auto g = labels.begin(); g != labels.end(); ++g)
			{

				for (auto l = m->edges.begin(); l != m->edges.end(); ++l)
				{
					if (l->label == *g)
					{
						++found;
					}
				}

			}
			if (found != goal)
			{
				m = members.erase(m);
			}
			else
			{
				++m;
			}
		}

		if (!members.empty())
		{
			cout << "These groups share the following members:" << endl;
			for (auto m = members.begin(); m != members.end(); ++m)
			{
				cout << m->label << endl;
			}
		}
		return members;
	}
}

void Graph::print_nodes()
{

	vector<Vertex> temp(nodes);
	sort(temp.begin(), temp.end(), compare);
	for (auto i = temp.begin(); i != temp.end(); ++i)
	{
		cout << i->label << endl;
	}
}

void Graph::read_file(string filename)
{
	ifstream fin;
	string temp, name;
	bool new_node = false;
	bool edges = false;
	fin.open(filename);
	stringstream ss;
	getline(fin, temp);
	getline(fin, temp);
	while (fin.good() && temp != "data")
	{
		ss << temp;
		getline(ss, temp);
		add_person(temp);
		getline(fin, temp);
	}
	string node_name, data_tag, value;
	getline(fin, temp);
	while (fin.good() && temp != "edges")
	{
		ss << temp;
		while (ss.good())
		{

			getline(ss, node_name, ',');
			getline(ss, data_tag, ',');
			getline(ss, value);
			add_data(node_name, data_tag, value);
		}
		ss.clear();
		getline(fin, temp);

	}
	while (fin.good() && temp != "end file")
	{
		string edge_start, edge_end, label;
		ss << temp;
		getline(ss, edge_start, ',');
		getline(ss, label, ',');
		getline(ss, edge_end);
		add_relation(edge_start, edge_end, label);
		getline(fin, temp);
	}
	fin.close();
}

void Graph::write_file(string filename)
{
	ofstream fout;
	fout.open(filename, 'w');
	fout << "nodes" << endl;
	for (auto i = nodes.begin(); i != nodes.end(); ++i)
	{
		fout << i->label << endl;

	}
	fout << "data" << endl;
	for (auto i = nodes.begin(); i != nodes.end(); ++i)
	{

		Datapoint *current = i->data.head;
		while (current)
		{
			fout << i->label << "," << current->data_tag << "," << current->value << endl;
			current = current->next;
		}
	}
	fout << "edges" << endl;
	for (auto i = nodes.begin(); i != nodes.end(); ++i)
	{
		for (auto j = i->edges.begin(); j != i->edges.end(); ++j)
		{
			fout << i->label << "," << j->label << "," << nodes[j->v].label << endl;
		}
	}
	fout.close();
}

void Graph::search(vector<string> reqs)
{
	vector<SearchResult> results;
	vector<string> data_tags;
	for (auto j = nodes.begin(); j != nodes.end(); ++j)
	{
		int temp_score = 0;
		for(auto i =reqs.begin();i!=reqs.end();++i)
		{
			if(j->data.has(*i))
			{
				++temp_score;
			}
			if(find(data_terms.begin(),data_terms.end(),*i)!=data_terms.end())
			{
				data_tags.push_back(*i);
			}
			if(j->label.find(*i)!=string::npos)
			{
				temp_score=temp_score+3;
			}
			for (auto k = j->edges.begin(); k != j->edges.end(); ++k)
			{
				if (k->label.find(*i)!=string::npos)
				{
					++temp_score;
				}
				if(nodes[k->v].label.find(*i)!=string::npos)
				{
					++temp_score;
				}
			}
		}
		if(temp_score>0)
		{
			SearchResult r;
			r.index = j - nodes.begin();
			r.score = temp_score;
			results.push_back(r);
		}
	
	}
	if (!results.empty())
	{
		sort(results.begin(), results.end(), search_compare);
		cout << "Search results (most likely first):" << endl;
		int i = 0;
		while(i<results.size()&&i<3)
		{
			if (!data_tags.empty())
			{
				if (nodes[results[i].index].isGroup)
					print(results[i].index, data_tags[0]);
				else
					print(results[i].index, data_tags[0]);
				cout << endl;
			}
			else
			{
				if (nodes[results[i].index].isGroup)
					print(results[i].index, "names");
				else
					print(results[i].index);
				cout << endl;
			}
			++i;
		}
	}
}
