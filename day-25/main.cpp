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

void freeMap(char **map, int h){

	for(int i = 0; i < h; i++)
		free(map[i]);

	free(map);

}

void debugMap(char **map, int h, int w){

	for(int i = 0; i < h; i++){
		for(int j = 0;  j < w; j++)
			cout << map[i][j];
		cout << endl;
	}

}

int getNextPositionEastFacing(int w, int currentW){

	int nextPosition = currentW + 1;

	if(currentW == w-1)
		nextPosition = 0;

	return nextPosition;

}

int getNextPositionSouthFacing(int h, int currentH){

	int nextPosition = currentH + 1;

	if(currentH == h-1)
		nextPosition = 0;

	return nextPosition;

}

bool checkNextEastFacing(char **map, int h, int w, int currentH, int currentW){

	int checkPosition = getNextPositionEastFacing(w, currentW);

	if(map[currentH][checkPosition] == '.')
		return true;
	else
		return false;

}


bool checkNextSouthFacing(char **map, int h, int w, int currentH, int currentW){

	int checkPosition = getNextPositionSouthFacing(h, currentH);

	if(map[checkPosition][currentW] == '.')
		return true;
	else
		return false;

}


char **copyMap(char **map, int h, int w){

	char **newMap = (char **) malloc(sizeof(char *) * h);

	if(!newMap)
		exit(1);

	for(int i = 0; i < h; i++) {
		newMap[i] = (char *) malloc(sizeof(char) * w);
		if(!newMap[i])
			exit(1);
	}

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			newMap[i][j] = map[i][j];


	return newMap;

}



int executeTurn(char **map, int h, int w, bool turn){

	int count = 0;

	char **newMap = copyMap(map, h, w);

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(!turn){// moves right
				if(checkNextEastFacing(map, h, w, i, j) && map[i][j] == '>'){

					newMap[i][getNextPositionEastFacing(w, j)] = '>';
					newMap[i][j] = '.';

					count++;
				}
			}
			else{ // moves down
				if(checkNextSouthFacing(map, h, w, i, j) && map[i][j] == 'v'){

					newMap[getNextPositionSouthFacing(h, i)][j] = 'v';
					newMap[i][j] = '.';
					count++;
				}
			}
		}
	}

	freeMap(map, h);
	map = copyMap(newMap, h, w);
	freeMap(newMap, h);

	return count;

}


int main() {
	
	vector<string> input = getInput();

	char **map;
	int w = input[0].size();
	int h = input.size();

	map = (char **) malloc(sizeof(char *) * h);
	if(!map)
		exit(1);

	for(int i = 0; i < h; i++) {
		map[i] = (char *) malloc(sizeof(char) * w);
		if(!map[i])
			exit(1);
	}

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			map[i][j] = input[i].at(j);
		}
	}

	int turn = 0;

	int moves = 0;

	do{

		moves = 0;

		moves += executeTurn(map, h, w, false);
		moves += executeTurn(map, h, w, true);

		turn++;


	}while(moves);



	cout << "Part 1 " << turn << endl;
	cout << "Part 2 " << 0 << endl;
	
	return 0;
	
}