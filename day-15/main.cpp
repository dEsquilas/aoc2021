#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#define DEBUG 1

using namespace std;
using namespace boost;

using VertexPropertyType = property<vertex_name_t, std::string>;
using EdgePropertyType = property<edge_weight_t, int>;
using DirectedGraphType = adjacency_list<vecS, vecS, directedS, VertexPropertyType, EdgePropertyType>;
using VertexDescriptor = graph_traits<DirectedGraphType>::vertex_descriptor;


vector<string> getInput() {
	
	ifstream input("input");
	vector<string> list;
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			
			trim(tmp);
			list.push_back(tmp);
			
		}
		input.close();
	}
	
	return list;
	
}

void debug(string s) {
	
	if (DEBUG)
		cout << s << endl;
	
}

std::vector<VertexDescriptor> getPath(
		const DirectedGraphType& graph,
		const std::vector<VertexDescriptor>& pMap,
		const VertexDescriptor& source,
		const VertexDescriptor& destination
) {
	
	std::vector<VertexDescriptor> path;
	VertexDescriptor current = destination;
	
	auto n = get(vertex_name, graph);
	
	while (current != source)
	{
		path.push_back(current);
		current = pMap[current];
	}
	
	//path.push_back(source);

	return path;
}

std::vector<VertexDescriptor> djikstra(
		const DirectedGraphType graph,
		const VertexDescriptor source,
		const VertexDescriptor destination
) {
	const int numVertices = num_vertices(graph);
	std::vector<int> distances(numVertices);
	vector<VertexDescriptor> pMap(numVertices);
	
	auto distanceMap = predecessor_map(
			make_iterator_property_map(pMap.begin(), get(vertex_index, graph))).distance_map(
			make_iterator_property_map(distances.begin(), get(vertex_index, graph)));
	
	dijkstra_shortest_paths(graph, source, distanceMap);
	
	return getPath(graph, pMap, source, destination);
}

int dijkstra(int **tiles, int h, int w){
	
	int vertexDirection[4][2] = {
			{0, -1},
			{0, 1},
			{1, 0},
			{-1, 0}
	};
	
	DirectedGraphType g;
	map<string, VertexDescriptor> vertexs;
	map<string, int> vertexsValues;
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			string idX = to_string(j);
			string idY = to_string(i);
			
			
			string id = idY + "|" + idX;
			
			VertexDescriptor current = add_vertex(VertexPropertyType(id), g);
			vertexs[id] = current;
			vertexsValues[id] = tiles[i][j];
			
		}
	}
	
	auto names = get(vertex_name, g);
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			string idX = to_string(j);
			string idY = to_string(i);
			
			string id = idY + "|" + idX;
			
			for(auto v: vertexDirection){
				
				if(0 <= v[0] + i && v[0] + i < h
				   && 0 <= v[1] + j && v[1] + j < w){
					
					string aidX = to_string(v[1] + j);
					string aidY = to_string(v[0] + i);
					string nextId = aidY + "|" + aidX;
					
					add_edge(vertexs[id], vertexs[nextId], vertexsValues[nextId], g);
					
				}
			}
		}
	}
	
	vector<VertexDescriptor> tmp = djikstra(g, vertexs["0|0"], vertexs[to_string(h-1) + "|" + to_string(w-1)]);
	auto n = get(vertex_name, g);
	
	
	int sum = 0;
	
	for(auto t: tmp){
		sum += vertexsValues[n[t]];
	}
	
	return sum;
	
}


int **fillBoard1(vector<string> input, int h, int w){
	
	int **tiles = (int **) malloc(sizeof(int *) * h);
	for(int i = 0; i < h; i++)
		tiles[i] = (int *) malloc(sizeof(int) * w);
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			char tmp = input[i].at(j);
			tiles[i][j] = atoi(&tmp);
		}
	}
	
	return tiles;
	
}

int **fillBoard2(vector<string> input, int h, int w){
	
	int **board;
	
	board = (int **) malloc(sizeof(int *) * h * 5);
	for(int i = 0; i < h * 5; i++) {
		board[i] = (int *) malloc(sizeof(int) * w * 5);
		memset(board[i], 0, w * 5 * sizeof(int));
	}
	
	// Fill the main boards
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			char tmp = input[i].at(j);
			board[i][j] = atoi(&tmp);
			
			for(int t = 1; t < 5; t++){
				
				if(t + board[i][j] > 9){
					board[i + (t*w)][j] = t + board[i][j] - 9;
					board[i][j + (t*w)] = t + board[i][j] - 9;
				}
				else{
					board[i + (t*w)][j] = board[i][j] + t;
					board[i][j + (t*w)] = board[i][j] + t;
				}
			}
		}
	}
	
	//Fill the rest
	
	for(int k = 1; k < 5; k++){
		for(int i = 0; i < w; i++){
			for(int j = 0; j < w; j++){
				
				for(int t = 1; t < 5; t++){
					
					if(t + board[i+(w*k)][j] > 9){
						board[i+(w*k)][j + (t*w)] = t + board[i+(w*k)][j] - 9;
					}
					else{
						board[i+(w*k)][j + (t*w)] = board[i+(w*k)][j] + t;
					}
				}
			}
		}
	}
	
	return board;
	
}


int main() {
	
	vector<string> input = getInput();
	
	int h = input.size();
	int w = input[0].size();
	
	int **tiles = fillBoard1(input, h, w);
	int **board = fillBoard2(input, h, w);
	
	auto started = std::chrono::high_resolution_clock::now();
	unsigned long int part1 = dijkstra(tiles, h, w);
	auto done = std::chrono::high_resolution_clock::now();
	
	auto p1time = std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count();
	
	started = std::chrono::high_resolution_clock::now();
	unsigned long int part2 = dijkstra(board, h*5, w*5);
	done = std::chrono::high_resolution_clock::now();
	
	auto p2time = std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count();
	
	cout << "Part 1: " << part1 << " on " << p1time << "ms" << endl;
	cout << "Part 2: " << part2 << " on " << p2time << "ms" << endl;
	
	
	return 0;
	
}