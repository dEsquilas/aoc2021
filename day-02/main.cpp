#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

int main() {
	
	ifstream input("input");
	
	int stackH = 0;
	int stackD = 0;
	
	int aim = 0;
	int stackH2 = 0;
	int stackD2 = 0;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			vector <string> order;
			split(order, tmp, is_any_of(" "));
			
			cout << "|" << order[0] << "|" << order[1] << endl;
			
			string command = order[0];
			
			// Part 1
			
			if(command.compare("forward") == 0)
				stackH += stoi(order[1]);
			if(command.compare("down") == 0)
				stackD += stoi(order[1]);
			if(command.compare("up") == 0)
				stackD -= stoi(order[1]);
			
			// Part 2
			
			if(command.compare("forward") == 0) {
				stackH2 += stoi(order[1]);
				stackD2 += aim * stoi(order[1]);
			}
			if(command.compare("down") == 0) {
				aim += stoi(order[1]);
			}
			if(command.compare("up") == 0) {
				aim -= stoi(order[1]);
			}
			
			
			
		}
		input.close();
	}
	
	
	int totalP1 = stackH * stackD;
	int totalP2 = stackH2 * stackD2;
	
	cout << "Part 1: " << to_string(totalP1) << endl;
	cout << "Part 2: " << to_string(totalP2) << endl;
	
	return 0;
	
}