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

class Result{
	
	public:
		int gammaVal;
		int epsilonVal;
		string gamma;
		string epsilon;
};

int *calculateGamma(vector<string> list) {
	
	int allocated = 0;
	int *count;
	
	for (auto tmp: list) {
		
		if (!allocated) {
			allocated = sizeof(int) * tmp.length();
			count = (int *) malloc(allocated);
			for (int i = 0; i < tmp.length(); i++)
				count[i] = 0;
		}
		
		for (int i = 0; i < tmp.length(); i++) {
			if (tmp.at(i) == 49)
				count[i]++;
		}
		
	}
	
	return count;
	
}

Result convertCount(int *count, int inputLength, int lines){
	
	Result *r = new Result();
	
	for(int i = 0; i < inputLength; i++){
		
		if(count[i] > (lines-1) / 2) {
			r->gamma += "1";
			r->epsilon += "0";
			r->gammaVal += pow(2, (inputLength - i -1));
		}else {
			r->gamma += "0";
			r->epsilon += "1";
			r->epsilonVal += pow(2, (inputLength - i -1));
		}
	}
	
	return *r;
	
}

int binaryStringToInt(string s){
	
	int val = 0;
	
	for(int i = 0; i < s.length(); i++)
		if(s.at(i) == '1')
			val += pow(2, (s.length() - i -1));
	
	return val;
	
}

int filterListByMask(vector<string> list, int inputLength, bool onGamma = true){
	
	int pointer = 0;
	
	do{
		
		vector<string> aux;
		
		int *count = calculateGamma(list);
		Result rtmp = convertCount(count, inputLength, list.size());
		
		for(auto current: list){
			if(rtmp.gamma.at(pointer) == current.at(pointer) && onGamma) {
				aux.push_back(current);
			}
			if(rtmp.epsilon.at(pointer) == current.at(pointer) && !onGamma) {
				aux.push_back(current);
			}
		}
		
		pointer++;
		list = aux;
		
		
	}while(list.size() > 1);
	
	return binaryStringToInt(list[0]);
	
}

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
	
	vector<string> initialList = getInput();
	int lines = initialList.size();
	int inputLength = initialList[0].length();
	
	// Part 1
	
	int *count = calculateGamma(initialList);
	Result r1 = convertCount(count, inputLength, lines);
	
	// Part 2
	
	int oxygen = filterListByMask(initialList, inputLength);
	int co2 = filterListByMask(initialList, inputLength, false);
	
	
	int totalP1 = r1.gammaVal * r1.epsilonVal;
	int totalP2 = co2 * oxygen;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}