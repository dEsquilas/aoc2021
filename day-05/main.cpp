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

class Board{
	public:
		map<string, int> m;
};

class Order{
	public:
		int fromX;
		int fromY;
		int toX;
		int toY;
		Order(string s){
			
			vector<string> tmp;
			split(tmp, s, is_any_of(" -> "));
			
			trim(tmp[0]);
			trim(tmp[1]);
			
			string from = tmp[0];
			string to = tmp[4];
			
			split(tmp, from, is_any_of(","));
			fromX = std::stoi(tmp[0]);
			fromY = stoi(tmp[1]);
			split(tmp, to, is_any_of(","));
			toX = stoi(tmp[0]);
			toY = stoi(tmp[1]);
			
		}
		
		void debug(){
			
			cout << fromX << "," << fromY << "|" << toX << "," << toY << endl;
			
		}
		
};


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



int main() {
	
	vector<string> input = getInput();
	vector<Order *> orders;
	Board *b = new Board();
	
	// Part 1
	
	for(auto l: input){
		Order *o = new Order(l);
		orders.push_back(o);
		
		if(o->fromX == o->toX){
			
			int o1 = o->fromY;
			int t1 = o->toY;
			
			if(o->fromY > o->toY){
				o1 = o->toY;
				t1 = o->fromY;
			}
			
			for(int i = o1; i <= t1; i++){
				string id = to_string(i) + "|" + to_string(o->fromX);
				if(b->m.count(id) > 0)
					b->m[id]++;
				else
					b->m[id] = 1;
			}
		}
		
		if(o->fromY == o->toY){
			
			int o1 = o->fromX;
			int t1 = o->toX;
			
			if(o->fromX > o->toX){
				o1 = o->toX;
				t1 = o->fromX;
			}
			
			for(int i = o1; i <= t1; i++){
				string id = to_string(o->fromY) + "|" + to_string(i);
				if(b->m.count(id) > 0)
					b->m[id]++;
				else
					b->m[id] = 1;
			}
		}
		
	}
	
	int largerThan2p1 = 0;
	
	for(auto [index, i]: b->m){
		if(i > 1)
			largerThan2p1++;
	}
	
	// Part 2
	
	for(auto o: orders){
		
		int vdx = abs(o->fromX - o->toX);
		int vdy = abs(o->fromY - o->toY);
		
		if(vdx == vdy){
			
			int fromX = o->fromX,
				fromY = o->fromY,
				toX = o->toX,
				toY = o->toY;
			
			for(
				int x = fromX, y = fromY, i = 0;
				i <= vdx ;
				fromX > toX ? x-- : x++, fromY > toY ? y-- : y++, i++
				) {
				
				string id = to_string(y) + "|" + to_string(x);
				if(b->m.count(id) > 0)
					b->m[id]++;
				else
					b->m[id] = 1;
			}
			
		}
	
	}
	
	int largerThan2p2 = 0;
	
	for(auto [index, i]: b->m){
		if(i > 1)
			largerThan2p2++;
	}
	
	int totalP1 = largerThan2p1;
	int totalP2 = largerThan2p2;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}