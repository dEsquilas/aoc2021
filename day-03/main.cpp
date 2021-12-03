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

int main() {
	
	ifstream input("input");

	int lines = 0;
	int inputLength = 0;
	
	vector<string> initialList;
	
	if (input.is_open()) {
		string tmp;
		
		while(getline(input, tmp)){
			
			trim(tmp);
			
			if(!inputLength)
				inputLength = tmp.length();
				
			initialList.push_back(tmp);
			lines++;
			
		}
		input.close();
	}
	
	// Part 1
	
	int *count = calculateGamma(initialList);
	Result r1 = convertCount(count, inputLength, lines);
	
	
	// Part 2
	
	int oxygenPointer = 0;
	vector<string> oxygenList = initialList;
	
	do{
		
		vector<string> aux;
		
		int *count = calculateGamma(oxygenList);
		Result rtmp = convertCount(count, inputLength, oxygenList.size());
		
		for(auto current: oxygenList){
			if(rtmp.gamma.at(oxygenPointer) == current.at(oxygenPointer)) {
				aux.push_back(current);
			}
		}
		
		oxygenPointer++;
		oxygenList = aux;
		
		
	}while(oxygenList.size() > 1);
	
	vector<string> co2List = initialList;
	int co2Pointer = 0;
	
	do{
		
		vector<string> aux;
		
		int *count = calculateGamma(co2List);
		Result rtmp = convertCount(count, inputLength, co2List.size());
		
		for(auto current: co2List){
			if(rtmp.epsilon.at(co2Pointer) == current.at(co2Pointer)) {
				aux.push_back(current);
			}
		}
		
		co2Pointer++;
		co2List = aux;
		
		
	}while(co2List.size() > 1);
	
	int oxygen = binaryStringToInt(oxygenList[0]);
	int co2 = binaryStringToInt(co2List[0]);
	
	
	int totalP1 = r1.gammaVal * r1.epsilonVal;
	int totalP2 = co2 * oxygen;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}