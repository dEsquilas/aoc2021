#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cmath>

#include <boost/algorithm/string.hpp>

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

string getRemovedPairsSubstring(string s) {
	
	vector<string> pairs = {"[]", "{}", "<>", "()"};
	
	while (true) {
		
		bool foundPair = false;
		
		//debug(s);
		
		for (auto p: pairs) {
			replace_all(s, p, "");
		}
		
		for (auto p: pairs) {
			if (s.find(p) != string::npos) {
				foundPair = true;
				break;
			}
		}
		
		if (!foundPair)
			break;
		
	}
	
	return s;
	
}

char getCloser(string s) {
	
	switch (s.at(s.size() - 1)) {
		case '[':
			return ']';
		case '(':
			return ')';
		case '<':
			return '>';
		case '{':
			return '}';
	}
	
	return 0;
	
}


int removePairs(string s) {
	
	vector<char> closeTags = {']', '}', '>', ')'};
	s = getRemovedPairsSubstring(s);
	
	char unexpectedChar = 0;
	
	for (int i = 0; i < s.size(); i++) {
		char current = s.at(i);
		for (auto ct: closeTags) {
			if (current == ct) {
				unexpectedChar = current;
				break;
			}
		}
		
		if (unexpectedChar != 0)
			break;
	}
	
	if (unexpectedChar == 0)
		return 0;
	else {
		switch (unexpectedChar) {
			case ')':
				return 3;
			case ']':
				return 57;
			case '}':
				return 1197;
			case '>':
				return 25137;
		}
	}
	
}

int main() {
	
	vector<string> input = getInput();
	
	int points = 0;
	
	vector<unsigned long int> scores;
	
	for (auto l: input) {
		points += removePairs(l);
		if (!removePairs(l)) {
			
			l = getRemovedPairsSubstring(l);
			
			unsigned long int score = 0;
			
			while (l.size() > 0) {
				char matching = getCloser(l);
				score *= 5;
				switch (matching) {
					case ')':
						score += 1;
						break;
					case ']':
						score += 2;
						break;
					case '}':
						score += 3;
						break;
					case '>':
						score += 4;
						break;
				}
				
				l = getRemovedPairsSubstring(l + matching);
				
			}
			
			scores.push_back(score);
			
		}
	}
	
	sort(scores.begin(), scores.end());
	
	int totalP1 = points;
	unsigned long int totalP2 = scores[scores.size() / 2];
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}