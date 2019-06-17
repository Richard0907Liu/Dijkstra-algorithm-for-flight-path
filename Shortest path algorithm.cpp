#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
typedef unordered_map<string, const unordered_map<string, int>> verx;

verx graph;
vector<string> vertex;
vector<string> shortest_path;
unordered_map<string, int> dist;
unordered_map<string, string> find_path;
int path_len = 0;
auto comp = [&](string i, string j) { return dist[i] < dist[j]; };

void print_shortest_path(vector<string> shrotest_path);
void create_graph(string name, const unordered_map<string, int> & dist);
void set_defualt_value(string start, verx vx);
vector<string> Dijsktra_algo(string start, string end_vertex, verx vx);


int main() {

	create_graph("JFK", { {"CLT", 100}, {"ORD", 150}, {"DEN", 300} });
	create_graph("CLT", { {"JFK", 100}, {"ORD", 70}, {"DFW", 260},{"ATL", 350} });
	create_graph("ATL", { {"CLT", 350}, {"DFW", 60}, {"DEN", 120}, {"NYC", 60}, {"LAX", 120} });
	create_graph("ORD", { {"JFK", 150}, {"CLT", 70}, {"DEN", 70}, {"LAS", 310}, {"SFO", 200} });
	create_graph("DFW", { {"CLT", 260}, {"ATL", 60}, {"DEN", 40} });
	create_graph("DEN", { {"JFK", 300}, {"ATL", 120}, {"ORD", 70}, {"DFW", 40}, {"NYC", 300}, {"LAS", 40}, {"LAX ", 280} });
	create_graph("LAS", { {"ORD", 310}, {"DEN", 40}, {"SEA", 110} });
	create_graph("SEA", { {"LAS", 110}, {"SFO", 210}, {"LAX", 80} });
	create_graph("SFO", { {"ORD", 200}, {"SEA", 210}, {"LAX", 190} });
	create_graph("JFK", { {"CLT", 100}, {"ORD", 150}, {"DEN", 300} });
	create_graph("NYC", { {"ATL", 60}, {"DEN", 300}, {"LAX", 50} });
	create_graph("LAX", { {"ATL", 120}, {"DEN", 280}, {"SEA", 80}, {"SFO", 190}, {"NYC", 50} });

	// Dijsktra’s shortest path 
	// print out the shortest path
	print_shortest_path(Dijsktra_algo("JFK", "LAX", graph));

	return 0;
}

void print_shortest_path(vector<string> shrotest_path) {
	for (auto it = shrotest_path.rbegin(); it != shrotest_path.rend(); it++) {
		static int i = 1;
		if (i < shrotest_path.size())
			cout << *it << " => ";
		else
			cout << *it << endl;
		i++;
	}
}

void create_graph(string name, const unordered_map<string, int> & dist) {
	verx temp;
	temp.insert(verx::value_type(name, dist));

	graph.insert(temp.begin(), temp.end());
}

void set_defualt_value(string start, verx vx) {
	for (auto v : vx)
	{
		if (v.first == start) {
			dist[v.first] = 0;
		}
		else {
			dist[v.first] = INT_MAX;
		}

		vertex.push_back(v.first);
		push_heap(begin(vertex), end(vertex), comp);  // insert an element and rearrange
	}
}

vector<string> Dijsktra_algo(string start, string end_vertex, verx vx) {

	set_defualt_value(start, vx);

	while (vertex.empty() == false) {

		sort(begin(vertex), end(vertex), comp);   // Put the vertex with smallest dist at first
		pop_heap(begin(vertex), end(vertex), comp); // moves the element in the first position to the end
		string minimal = vertex.back();  // access the last element
		vertex.pop_back();  // really remove the last element

		if (minimal == end_vertex)
		{
			while (find_path.find(minimal) != find_path.end())	// ==  end(find_path))
			{
				shortest_path.push_back(minimal);
				minimal = find_path[minimal];
			}

			break;
		}

		for (auto next : vx[minimal])
		{

			path_len = dist[minimal] + next.second;  // dist[minimal], distance from JFK
			if (path_len < dist[next.first])  //
			{
				dist[next.first] = path_len;  // dist[next.first] => distance from JFK
				find_path[next.first] = minimal;  // Set the previous point where link to start is nearest
				sort(begin(vertex), end(vertex), comp);	// Put the vertex with smallest dist at first
			}
			cout << "Distance: " << path_len << endl;
		}

	}

	cout << "==============" << endl;
	cout << "The shortest distance from " << start << " to " << end_vertex << ": " << path_len << endl;
	shortest_path.push_back(start); // set the start vertex;

	return shortest_path;
}


