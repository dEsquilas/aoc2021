#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
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

char **addWrapper(char **map, int h, int w){
	
	char **newMap = (char **) malloc(sizeof(char *) * h);
	
	for(int i = 0; i < h; i++){
		
		newMap[i] = (char *) malloc(sizeof(char) * w);
		
		for(int j = 0; j < w; j++){
			
			
			if(i == 0 || i == h - 1 || j == 0 || j == w - 1){
				newMap[i][j] = '-';
			}
			else{
				newMap[i][j] = map[i-1][j-1];
			}
			
		}
		
	}
	
	return newMap;
	
}

char calculate(char **map, int currentCol, int currentRow, string code, int current){
	
	int values[9];
	int iter = 0;
	
	//cout << "Current " << current << " " << (current % 2 == 0) << endl;
	
	for(int i = currentCol - 1; i <= currentCol + 1; i++){
		for(int j = currentRow -1; j <= currentRow + 1; j++){
			if(map[i][j] == '.')
				values[iter++] = 0;
			else if(map[i][j] == '#')
				values[iter++] = 1;
			else {
				
				if(code.at(0) == '#'){
					
					if(current % 2 != 0)
						values[iter++] = 1;
					else
						values[iter++] = 0;
					
				}else{
					values[iter++] = 0;
				}
				
			}
		}
	}
	
	int v = 0;
	
	for(int i = 0; i < 9; i++){
		if(values[i])
			v += pow(2, 8 - i);
	}
	
	return code.at(v);
	
	
}

char **applyConversion(char **map, int h, int w, string code, int current){
	
	
	char **oldMap = (char **) malloc(sizeof(char *) * h);
	
	for(int i = 0; i < h; i++) {
		oldMap[i] = (char *) malloc(sizeof(char) * w);
		for (int j = 0; j < w; j++) {
			oldMap[i][j] = map[i][j];
		}
	}
	
	for(int i = 1; i < h -1; i++){
		for(int j = 1; j < w -1; j++){
			map[i][j] = calculate(oldMap, i, j, code, current);
		}
	}
	
	return map;
	
}

void debugMap(char **map, int h, int w){
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			cout << map[i][j];
		}
		cout << endl;
	}

}


int main() {
	
	vector<string> input = getInput();
	
	string code = input[0];
	
	char **map;
	map = (char **) malloc(sizeof(char *) * (input.size() - 2));
	
	int h = input.size() - 2;
	int w = input[2].size();
	
	for(int i = 2; i < input.size(); i++){
		map[i-2] = (char *) malloc(sizeof(char) * input[i].size());
		for(int j = 0; j < input[i].size(); j++){
			map[i-2][j] = input[i].at(j);
		}
	}
	
	for(int i = 0; i < 2; i++) {
		
		h += 2;
		w += 2;
		
		map = addWrapper(map, h, w);
		h += 2;
		w += 2;
		
		map = addWrapper(map, h, w);
		map = applyConversion(map, h, w, code, i);
		
		//debugMap(map, h, w);
		
	}
	
	int count1 = 0;
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(map[i][j] == '#')
				count1++;
		}
	}
	
	for(int i = 0; i < 48; i++) {
		
		h += 2;
		w += 2;
		
		map = addWrapper(map, h, w);
		h += 2;
		w += 2;
		
		map = addWrapper(map, h, w);
		map = applyConversion(map, h, w, code, i);
		
		//debugMap(map, h, w);
		
	}
	
	int count2 = 0;
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(map[i][j] == '#')
				count2++;
		}
	}
	
	cout << "Part 1 " << count1 << endl;
	cout << "Part 2 " << count2 << endl;
	
	return 0;
	
}