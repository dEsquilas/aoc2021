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

class Cell{
	public:
		int row;
		int col;
		int val;
		bool marked = false;
		
		void debug(){
			cout << "(" << row << "," << col << ")" << val << " " << "<" << marked << ">";
		}
};

class Board{
	public:
		unordered_map<int, Cell*> cells;
		vector<int> cols = {0, 0, 0, 0, 0};
		vector<int> rows = {0, 0, 0, 0, 0};
		bool disabled = false;
		
		void addCell(int row, int col, int val){
			
			Cell *c = new Cell();
			c->row = row;
			c->col = col;
			c->val = val;
			
			cells[val] = c;
			
		}
		
		void reset(){
			
			cols = {0, 0, 0, 0, 0};
			rows = {0, 0, 0, 0, 0};
			
		}
		
		void mark(int current){
			
			cells[current]->marked = true;
			cols[cells[current]->col]++;
			rows[cells[current]->row]++;
			
		}
		
		bool check(){
			
			for(auto c: cols)
				if(c == 5)
					return true;
			
			for(auto r: rows)
				if(r == 5)
					return true;
				
			return false;
			
		}
		
		void debug(){
			
			for(auto [key, current]: cells){
				current->debug();
			}
			
		}
		
		int sumUnmarked(){
			
			int t = 0;
			
			for(auto [index, c]: cells){
				if(!c->marked)
					t += c->val;
			}
			
			return t;
			
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
	
	vector<int> numbers;
	vector<string> numbersToParse;
	split(numbersToParse, input[0], is_any_of(","));
	for(auto current: numbersToParse)
		numbers.push_back(stoi(current));
	
	vector<Board *> boards;
	
	for(int i = 2; i < input.size(); i++){
		Board *b = new Board();
		
		for(int j = 0; j < 5; j++){
			
			string tmp = input[i+j];
			replace_all(tmp, "  ", " ");
			vector<string> output;
			split(output, tmp, is_any_of(" "));
			
			for(int v = 0; v < output.size(); v++)
				b->addCell(j, v, stoi(output[v]));
			
		}
		
		boards.push_back(b);
		
		i+= 5;
		
	}
	
	// Part 1
	
	int r = 0;
	
	for(auto current: numbers){
	
		for(auto b: boards){
			if(b->cells.count(current) > 0) {
				b->mark(current);
				if(b->check()){
					r = current * b->sumUnmarked();
					break;
				}
			}
		}
		
		if(r)
			break;
		
	}
	
	// Part 2
	
	int last = 0;
	
	for(auto b: boards) {
		for (auto[index, c]: b->cells)
			c->marked = false;
		b->reset();
	}
	
	for(auto current: numbers){
		
		for(auto b: boards){
			if(b->cells.count(current) > 0) {
				b->mark(current);
				if(boards.size() > 1 && b->check()){
					b->disabled = true;
				}
			}
		}
		
		vector<Board *> out;
		
		if(boards.size() > 1) {
			for (auto b: boards)
				if (!b->disabled)
					out.push_back(b);
			boards = out;
		}
		
		if(boards.size() == 1 && boards[0]->check()) {
			last = current;
			break;
		}
		
	}
	
	int totalP1 = r;
	int totalP2 = last * boards[0]->sumUnmarked();
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}