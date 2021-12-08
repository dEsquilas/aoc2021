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

vector<string> findByLength(vector<string> words, int length){
	
	vector<string> out;
	
	for(auto w: words)
		if(w.length() == length)
			out.push_back(w);
	
	return out;
	
}

string findByNotHave(vector<string> words, int charCount, string thisOrThat){
	
	vector<string> fiveCharWords = findByLength(words, charCount);
	
	for(auto w: fiveCharWords){
		if(w.find(thisOrThat.at(0)) != string::npos ^ w.find(thisOrThat.at(1)) != string::npos)
			return w;
	}
	
	return "";
	
}

string findByNotHaveOne(vector<string> words, int charCount, string that){
	
	vector<string> fiveCharWords = findByLength(words, charCount);
	
	for(auto w: fiveCharWords){
		if(w.find(that.at(0)) != string::npos )
			return w;
	}
	
	return "";
	
}

string findNotIn(string find, string needle){
	
	string out = "";
	
	for(int i = 0; i < find.length(); i++)
		if(needle.find(find.at(i)) == string::npos)
			out += find.at(i);
	
	return out;
	
}

string findNine(vector<string> words, string zero, string six){
	
	for(auto w: words)
		if(w.length() == 6 && zero.compare(w) != 0 && six.compare(w) != 0)
			return w;
	
	return "";
}

string findByHasBothOf(vector<string> words, string one){
	
	for(auto w: words)
		if(w.length() == 5 && w.find(one.at(0)) != string::npos && w.find(one.at(1)) != string::npos){
			return w;
		}
	
	return "";
	
}

string findByHas(vector<string> words, string s){
	
	for(auto w: words)
		if(w.length() == 5 && w.find(s.at(0)) != string::npos){
			return w;
		}
	
	return "";
	
}


map<int, string> getNumbers(string l){
	
	map<int, string> numbers;
	
	
	vector<string> parser;
	split(parser, l, is_any_of(" "));
	
	vector<string> inputList;
	for(int i = 0; i <= 9; i++){
		inputList.push_back(parser[i]);
	}
	
	numbers[1] = findByLength(inputList, 2)[0];
	numbers[4] = findByLength(inputList, 4)[0];
	numbers[7] = findByLength(inputList, 3)[0];
	numbers[8] = findByLength(inputList, 7)[0];
	
	numbers[6] = findByNotHave(inputList, 6, numbers[1]);
	
	string notIncludedOn4 = findNotIn(numbers[4], numbers[1]);
	
	numbers[0] = findByNotHave(inputList, 6, notIncludedOn4);
	numbers[9] = findNine(inputList, numbers[0], numbers[6]);
	
	string notIncludedOn0 = findNotIn(numbers[8], numbers[0]);
	string notIncludedOn4_2 = findNotIn(numbers[4], numbers[1] + notIncludedOn0);
	
	numbers[3] = findByHasBothOf(inputList, numbers[1]);
	numbers[2] = findByHas(inputList, notIncludedOn4_2);
	
	string tmp = numbers[1] + notIncludedOn0;
	string aux;
	for(int i = 0; i < numbers[4].length(); i++)
		if(tmp.find(numbers[4].at(i)) == string::npos)
			aux = numbers[4].at(i);
	
	numbers[5] = findByNotHaveOne(inputList, 5, aux);
	
	for(auto w: inputList) {
		
		
		bool found = false;
		
		for(auto[i, n]: numbers) {
			if(n.compare(w) == 0)
				found = true;
		}
		if(!found){
			numbers[2] = w;
			break;
		}
		
	}
	
	
	return numbers;
	
}

vector<string> getElements(string l){
	
	vector<string> parser;
	split(parser, l, is_any_of(" "));
	vector<string> out;
	
	vector<string> inputList;
	for(int i = 11; i < 15; i++){
		out.push_back(parser[i]);
	}
	
	return out;
	
}

int getCurrent(string l){
	
	map<int, string> numbers = getNumbers(l);
	vector<string> digits = getElements(l);
	
	int total = 0;
	
	for(auto [i, n]: numbers)
		sort(numbers[i].begin(), numbers[i].end());
	
	for(int i = 0; i < 4; i++){
		sort(digits[i].begin(), digits[i].end());
		for(auto [index, w]: numbers){
			if(w.compare(digits[i]) == 0){
				total += index * pow(10, 3 - i);
				break;
			}
		}
	}
	
	return total;
	
}



int main() {
	
	vector<string> input = getInput();
	
	int countRelevant = 0;
	
	// Part 1
	
	for(auto l: input){
		vector<string> parser;
		split(parser, l, is_any_of(" "));
		for(int i = 11; i < 15; i++)
			if(
					parser[i].length() == 2
					||
					parser[i].length() == 3
					||
					parser[i].length() == 4
					||
					parser[i].length() == 7
					) {
				countRelevant++;
			}
		
	}
	
	// Part 2
	
	unsigned long int count = 0;
	
	for(auto l: input)
		count += getCurrent(l);
	
	
	
	int totalP1 = countRelevant;
	unsigned long int totalP2 = count;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}