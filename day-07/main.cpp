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

class CrabBlock{
	
	public:
		int count;
		int startPosition;
		
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
	vector<string> tmp;
	split(tmp, input[0], is_any_of(","));
	
	vector<int> list;
	
	for(auto t: tmp)
		list.push_back(stoi(t));
	
	
	sort(list.begin(), list.end());
	
	int min = list[0];
	int max = list[list.size()-1];
	
	vector<CrabBlock *> crabs;
	
	for(int i = 0; i < list.size(); ){
		int count = 1;
		int current = list[i];
		if(list[i+count] == current) {
			do {
				if (i + count >= list.size())
					break;
				count++;
			} while (list[i + count] == current);
		}
		CrabBlock *c = new CrabBlock();
		c->count = count;
		c->startPosition = current;
		crabs.push_back(c);
		
		i += count;
		
	}
	
	// Part 1
	
	int minFuelUsedP1 = 99999999;
	
	for(int i = min; i <= max; i++){
		int fuelUsed = 0;
		for(auto c: crabs){
			fuelUsed += abs(c->startPosition - i) * c->count;
		}
		if(fuelUsed < minFuelUsedP1)
			minFuelUsedP1 = fuelUsed;
	}
	
	// Part 2
	
	unsigned long int minFuelUsedP2 = 99999999999999;
	
	for(int i = min; i <= max; i++){
		
		unsigned long int fuelUsed = 0;
		for(auto c: crabs){
			int currentUnit = abs(c->startPosition - i);
			unsigned long int fuelUsedCurrentCrab = 0;
			for(int i = 0; i < currentUnit; i++){
				fuelUsedCurrentCrab += (i+1) * c->count;
			}
			fuelUsed += fuelUsedCurrentCrab;
		}
		if(fuelUsed < minFuelUsedP2)
			minFuelUsedP2 = fuelUsed;
	}
	
	
	
	int totalP1 = minFuelUsedP1;
	unsigned long int totalP2 = minFuelUsedP2;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}