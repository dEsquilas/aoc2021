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

void debugBoard(int **board, int boardSize) {
	
	if (DEBUG)
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	
}

int incrementNeighbor(int **board, int boardSize){
	
	int neighbors[8][2] = {
			{-1, -1},
			{-1, 0},
			{-1, 1},
			{0,  -1},
			{0,  1},
			{1,  -1},
			{1,  0},
			{1,  1}
	};
	
	int updatedNeighbors = 0;
	
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] > 9) {
				board[i][j] = -1;
				for (auto neighbor: neighbors) {
					int currentY = i + neighbor[0];
					int currentX = j + neighbor[1];
					if (0 <= currentY && currentY < boardSize && 0 <= currentX && currentX < boardSize) {
						if(board[currentY][currentX] != -1) {
							board[currentY][currentX]++;
							updatedNeighbors++;
						}
					}
				}
			}
		}
	}
	
	
	return updatedNeighbors;
	
}

int getFlashes(int **board, int boardSize) {
	
	int count = 0;
	
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			board[i][j]++;
		
		
	while(incrementNeighbor(board, boardSize));
	
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == -1) {
				board[i][j] = 0;
				count++;
			}
		}
	
	return count;
	
}


int main() {
	
	vector<string> input = getInput();
	
	int **board;
	int boardSize = input.size();
	
	board = (int **) malloc(boardSize * sizeof(int *));
	for (int i = 0; i < input.size(); i++)
		board[i] = (int *) malloc(boardSize * sizeof(int));
	
	
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++) {
			char &c = input[i].at(j);
			board[i][j] = (int) c - 48;
		}
	
	int totalFlashes = 0;
	
	int i = 1;
	
	// Part 1
	
	for (; i <= 100; i++) {
		int countFlashes = getFlashes(board, boardSize);
		totalFlashes += countFlashes;
		if(countFlashes == 100)
			break;
	}
	
	// Part 2
	
	if(i >= 100)
		for (; ; i++) {
			int countFlashes = getFlashes(board, boardSize);
			if(countFlashes == 100)
				break;
		}
	
	unsigned long int totalP1 = totalFlashes;
	unsigned long int totalP2 = i;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}