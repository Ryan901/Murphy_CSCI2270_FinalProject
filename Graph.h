#pragma once
#include"Datalist.h"
#include<vector>
#include<iostream>
#include <fstream>
#include<sstream>

struct Edge;
struct Vertex
{
	bool isGroup = false;
	string label;
	Datalist data;
	vector<Edge> edges;
};

struct Edge
{
	string type = "group";
	string label;
	int v;
};
struct SearchResult
{
	int index;
	int score;
};
class Graph
{
public:
	Graph();
	~Graph();
	void add_person(string name);
	void add_data(string name, string data_tag, string value);
	void add_group(string label, vector<string> people, string type = "n/a");
	void add_relation(string name1, string name2, string label);
	void print(string name, string data_tag = "all");
	void print(int to_print, string data_tag);
	void print_groups(string data_tag = "none");
	vector<Vertex> get_group_intersections(vector<string> labels);
	void print_nodes();
	void read_file(string filename);
	void write_file(string filename);
	void search(vector<string> reqs);

private:
	vector<string> data_terms;
	vector<Vertex> nodes;
	int find_node(string name);
};

