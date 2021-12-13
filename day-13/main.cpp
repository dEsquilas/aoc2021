#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <stdio.h>

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

int **fold(int **oldSheet, int oldWidth, int oldHeight, bool direction, int position){

	int **sheet;
	int width;
	int height;
	
	if(direction){
		width = oldWidth;
		height = position;
	}
	else{
		width = position;
		height = oldHeight;
	}
	
	sheet = (int **) malloc(sizeof(int *) * height);
	for(int i = 0; i < height; i++) {
		sheet[i] = (int *) malloc(sizeof(int) * width);
		memset(sheet[i], 0, width * sizeof(int));
	}
	
	// Fill the sheet
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			sheet[i][j] = oldSheet[i][j];
		}
	}
	
	// Mirror
	
	int max = (direction) ? width : height;
	
	
	for(int i = 1; i <= position; i++){
		for(int j = 0; j < max; j++){
			
			if(direction){
				sheet[position - i][j] += oldSheet[position + i][j];
			}
			else{
				sheet[j][position - i] += oldSheet[j][position + i];
			}
			
		
		}
	}
	
	return sheet;
	
}


int main() {
	
	vector<string> input = getInput();
	
	int **sheet;
	int sheetWidth = 0;
	int sheetHeight = 0;

	vector<int> coordsX;
	vector<int> coordsY;
	
	for(auto l: input){
		if(l.size() == 0)
			break;
		vector<string> tmp;
		split(tmp, l, is_any_of(","));
		
		if(stoi(tmp[0]) > sheetWidth)
			sheetWidth = stoi(tmp[0]);
		if(stoi(tmp[1]) > sheetHeight)
			sheetHeight = stoi(tmp[1]);
		
		coordsX.push_back(stoi(tmp[0]));
		coordsY.push_back(stoi(tmp[1]));
		
	}
	
	sheetWidth++;
	sheetHeight++;
	
	sheet = (int **) malloc(sizeof(int *) * sheetHeight);
	for(int i = 0; i < sheetHeight; i++) {
		sheet[i] = (int *) malloc(sizeof(int) * sheetWidth);
		memset(sheet[i], 0, sheetWidth * sizeof(int));
	}
	
	for(int i = 0; i < coordsX.size(); i++){
		sheet[coordsY[i]][coordsX[i]] = 1;
	}
	
	vector<bool> directions;
	vector<int> positions;
	
	for(auto l: input){
		if(l.find("fold along y=") != string::npos){
			int tmp;
			sscanf(l.c_str(), "fold along y=%d", &tmp);
			directions.push_back(true);
			positions.push_back(tmp);
		}
		if(l.find("fold along x=") != string::npos){
			int tmp;
			sscanf(l.c_str(), "fold along x=%d", &tmp);
			directions.push_back(false);
			positions.push_back(tmp);
		}
	}
	
	// End read input and prepare
	
	// Part 1
	
	int countP1 = 0;
	
	sheet = fold(sheet, sheetWidth, sheetHeight, directions[0], positions[0]);
	if(directions[0]){
		sheetHeight = positions[0];
	}
	else{
		sheetWidth = positions[0];
	}
	
	for(int i = 0; i < sheetHeight; i++)
		for(int j = 0; j < sheetWidth; j++)
			if(sheet[i][j])
				countP1++;
	
	cout << "Part 1: " << countP1 << endl;
	
	
	// Part 2
	
	for(int i = 1; i < directions.size(); i++){
		sheet = fold(sheet, sheetWidth, sheetHeight, directions[i], positions[i]);
		if(directions[i]){
			sheetHeight = positions[i];
		}
		else{
			sheetWidth = positions[i];
		}
	}
	
	cout << "Part 2: " << endl;
	
	for(int i = 0; i < sheetHeight; i++){
		for(int j = 0; j < sheetWidth; j++){
			if(sheet[i][j])
				cout << "#";
			else
				cout << " ";
		}
		cout << endl;
	}
	
	
	
	return 0;
	
}