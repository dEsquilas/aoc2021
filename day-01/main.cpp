#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;


int main() {
	
	ifstream input("input");
	
	
	bool isRules = true;
	
	
	int last = -1;
	int current = -1;
	
	int incrementP1 = 0;
	
	int measure0 = -1;
	int measure1 = -1;
	int measure2 = -1;
	
	int lastWindow = -1;
	
	int incrementP2 = 0;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			// Part 1
			
			if(last != -1){
				current = stoi(tmp);
				if(current > last)
					incrementP1++;
			}
			last = stoi(tmp);
			
			// Part 2
			if(measure0 == -1)
				measure0 = stoi(tmp);
			
			else if(measure1 == -1 && measure0 != -1)
				measure1 = stoi(tmp);
			
			else if(measure0 != -1 && measure1 != -1){
				
				measure2 = stoi(tmp);
				int currentWindow = measure0 + measure1 + measure2;
	
				if(lastWindow != -1 && currentWindow > lastWindow) {
					incrementP2++;
				}
				
				
				lastWindow = currentWindow;
				
				measure0 = measure1;
				measure1 = measure2;
				
			}
			
		}
		input.close();
	}
	
	cout << "Part 1 - Increments: " << to_string(incrementP1) << endl;
	cout << "Part 2 - Increments: " << to_string(incrementP2) << endl;
	
	
	return 0;
	
}