#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <stdio.h>

#include <boost/algorithm/string.hpp>

#define DEBUG 1
#define H -999999

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

int shoot(int speedX, int speedY, int minX, int maxX, int minY, int maxY){
	
	
	int x = 0,
		y = 0;
	
	int highestY = H;
	
	int lastX = -1;
	bool yPassed = false;
	
	do{
		
		x += speedX;
		y += speedY;
		
		if(lastX == x && yPassed){
			break;
		}
		
		lastX = x;
		
		if(y > highestY)
			highestY = y;
		
		if(speedX > 0)
			speedX--;
		if(speedX < 0)
			speedX++;
		
		speedY--;
		
		if(minX <= x && x <= maxX && minY <= y && y <= maxY){
			return highestY;
		}
		
		if(y < minY){
			yPassed = true;
		}
		
	
	}while(x <= maxX);
	
	return H;
	

}


int main() {
	
	vector<string> input = getInput();
	int minX,
		minY,
		maxX,
		maxY;
	
	sscanf(input[0].c_str(), "target area: x=%d..%d, y=%d..%d", &minX, &maxX, &minY, &maxY);
	
	int highestY = 0;
	int count = 0;
	
	for(int i = 1; i <= maxX; i++){
		for(int j = minY; j <= -minY; j++){
			int ret = shoot(i, j, minX, maxX, minY, maxY);
			if(ret != H)
				count++;
			if(highestY < ret)
				highestY = ret;
		}
	}
	
	
	
	cout << "Part 1: " << highestY << endl;
	cout << "Part 2: " << count << endl;
	
	
	return 0;
	
}