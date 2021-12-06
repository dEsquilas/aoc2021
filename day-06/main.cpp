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

class SyncFish{

	public:
		unsigned long int count;
		int currentDay;
		
		SyncFish(int _currentDay){
			currentDay = _currentDay;
			count = 0;
		}
		
		unsigned long int decrease(){
			
		
			if(currentDay == 0) {
				currentDay == 6;
				return count;
			}else{
				currentDay--;
				return 0;
			}
		
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
	vector<SyncFish *> fish;
	
	vector<string> inputNumbers;
	split(inputNumbers, input[0], is_any_of(","));
	
	for(int i = 0; i <= 8; i++){
		SyncFish *sf = new SyncFish(i);
		fish.push_back(sf);
		for(auto number: inputNumbers){
			if(stoi(number) == i){
				//cout << i << endl;
				sf->count++;
			}
		}
	}

	int cycles = 256;
	unsigned long int t1 = 0;
	unsigned long int t2 = 0;
	
	for(int i = 0; i < cycles; i++){
		
		unsigned long int toAdd = 0;
		for(auto f: fish){
			toAdd += f->decrease();
		}
		
		fish[7]->count += toAdd;
		
		SyncFish *sf = new SyncFish(8);
		sf->currentDay = 8;
		sf->count = toAdd;
		fish.push_back(sf);
		fish.erase(fish.begin());
		
		
		if(i == 79){
			for(auto f: fish)
				t1 += f->count;
		}
		
		
	}
	
	for(auto f: fish)
		t2 += f->count;
	
	
	unsigned long int totalP1 = t1;
	unsigned long int totalP2 = t2;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}