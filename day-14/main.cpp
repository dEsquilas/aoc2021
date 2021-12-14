#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <stdio.h>

#include <boost/algorithm/string.hpp>
#include <algorithm>

#define DEBUG 1

using namespace std;
using namespace boost;

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


map<char, unsigned long int> getResults(map<string, unsigned long int> occurrences, string initial){
	
	map<char, unsigned long int> results;
	
	for(auto [index, v]: occurrences){
		
		if(results.count(index.at(0)) == 0)
			results[index.at(0)] = 0;
		if(results.count(index.at(1)) == 0)
			results[index.at(1)] = 0;
		
		results[index.at(0)] += v;
		
	}
	
	results[initial.at(initial.size() - 1)]++;
	
	return results;
	
}



int main() {
	
	vector<string> input = getInput();
	
	
	map<string, string[2]> rules;
	string initial;
	
	for(int i = 0; i < input.size(); i++){
		auto l = input[i];
		
		if(i == 0)
			initial = l;
		
		if(i > 1){
			
			vector<string> tmp;
			split(tmp, l, is_any_of(" -> "));
			rules[tmp[0]][0] = tmp[0].at(0) + tmp[4];
			rules[tmp[0]][1] = tmp[4] + tmp[0].at(1);
			
		}
		
	}
	
	map<string, unsigned long int> occurrences;
	map<string, unsigned long int> newOccurrences;
	
	for(auto [index, groups]: rules){
		occurrences[index] = 0;
	}
	
	unsigned long int highest = 0;
	unsigned long int lowest = 9999999999999999;
	
	unsigned long int part1 = 0;
	
	
	// Get the initial groups
	
	for(int i = 0; i < initial.size() - 1; i++){
		occurrences[initial.substr(i, 2)]++;
	}
	
	
	for(int i = 0; i < 40; i++){
		// Reset ocurrences
		for(auto [index, groups]: rules){
			newOccurrences[index] = 0;
		}
		
		for(auto [index, v]: occurrences){
			newOccurrences[rules[index][0]] += v;
			newOccurrences[rules[index][1]] += v;
		}
		
		occurrences = newOccurrences;
		
		// For Part 1 stop here and calculate
		
		if(i == 9) {
			
			map<char, unsigned long int> results = getResults(occurrences, initial);
			
			for (auto[index, v]: results) {
				if (highest < v)
					highest = v;
				if (lowest > v)
					lowest = v;
			}
			part1 = highest - lowest;
		}
		
	}
	
	map<char, unsigned long int> results = getResults(occurrences, initial);
	highest = 0;
	lowest = 9999999999999999;
	
	for(auto [index, v]: results){
		if(highest < v)
			highest = v;
		if(lowest > v)
			lowest = v;
	}
	
	
	unsigned long int part2 = highest - lowest;
	
	cout << "Part 1: " << part1 << endl;
	cout << "Part 2: " << part2 << endl;
	
	
	
	return 0;
	
}