#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cmath>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

vector<string> getInput(){
	
	ifstream input("input");
	vector<string> list;
	
	if (input.is_open()) {
		string tmp;
		
		while(getline(input, tmp)){
			
			trim(tmp);
			list.push_back(tmp);
			
		}
		input.close();
	}
	
	return list;
	
}

class Tile{
	
	public:
		int value;
		bool visited = false;
		
};

int countNeighbors(map<string, Tile *> tiles, int x, int y){
	
	string id = to_string(y) + "|" + to_string(x);
	int rg[] = {-1, 0, 1};
	
	
	if(tiles.count(id) == 0 || tiles[id]->visited)
		return 0;
	
	tiles[id]->visited = true;
	
	if(tiles[id]->value == 9)
		return 0;
	
	int count = 1;
	
	for(auto ny: rg) {
		for (auto nx: rg) {
			if ((nx == 0 && ny != 0) || (nx != 0 && ny == 0)) {
				string ci = to_string(ny + y) + "|" + to_string(nx + x);
				if (tiles.count(ci) > 0) {
					count += countNeighbors(tiles, x+nx, y+ny);
				}
			}
		}
	}
	
	return count;
	
}

int main() {
	
	vector<string> input = getInput();
	
	map<string, int> m;
	map<string, Tile *> tiles;
	
	int line = 0;
	
	for(auto l: input){
		for(int i = 0; i < l.length(); i++) {
			char tmp = l.at(i);
			m[to_string(line) + "|" + to_string(i)] = atoi(&tmp);
			Tile *tile = new Tile();
			tile->value = atoi(&tmp);
			tiles[to_string(line) + "|" + to_string(i)] = tile;
		}
		line++;
	}
	
	int p = 0;
	int rg[] = {-1, 0, 1};
	
	// Part 1
	
	for(auto [index, mv]: m) {
		
		bool lower = true;
		vector<string> tmp;
		split(tmp, index, is_any_of("|"));
		int currentX = stoi(tmp[1]),
			currentY = stoi(tmp[0]);
		
		for(auto y: rg){
			for(auto x: rg){
				if((x == 0 && y != 0) || (x != 0 && y == 0)) {
					string ci = to_string(currentY + y) + "|" + to_string(currentX + x);
					if (m.count(ci) > 0) {
						if (m[ci] <= mv)
							lower = false;
					}
				}
			
			}
		}
		if(lower){
			p += mv + 1;
		}
		
	}
	
	// Part 2
	
	vector<int> biggest;
	
	for(auto [index, t]: tiles) {
		vector<string> tmp;
		split(tmp, index, is_any_of("|"));
		int currentX = stoi(tmp[1]),
			currentY = stoi(tmp[0]);
		if(!t->visited) {
			int count = countNeighbors(tiles, currentX, currentY);
			biggest.push_back(count);
		}
	}
	
	sort(biggest.begin(), biggest.end());
	
	int multiply = 1;
	for(int i = biggest.size() - 3; i < biggest.size(); i++)
		multiply *= biggest[i];
	
	int totalP1 = p;
	int totalP2 = multiply;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}