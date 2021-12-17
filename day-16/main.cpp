#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <chrono>
#include <boost/algorithm/string.hpp>

#define DEBUG 1

using namespace std;
using namespace boost;

int sumVersions = 0;

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

string toBinary(char to)
{
	
	switch (to) {
		case '0':
			return "0000";
			break;
		case '1':
			return "0001";
			break;
		case '2':
			return "0010";
			break;
		case '3':
			return "0011";
			break;
		case '4':
			return "0100";
			break;
		case '5':
			return "0101";
			break;
		case '6':
			return "0110";
			break;
		case '7':
			return "0111";
			break;
		case '8':
			return "1000";
			break;
		case '9':
			return "1001";
			break;
		case 'A':
		case 'a':
			return "1010";
			break;
		case 'B':
		case 'b':
			return "1011";
			break;
		case 'C':
		case 'c':
			return "1100";
			break;
		case 'D':
		case 'd':
			return "1101";
			break;
		case 'E':
		case 'e':
			return "1110";
			break;
		case 'F':
		case 'f':
			return "1111";
			break;
		default:
			exit(-1);
	}
}


class Packet{
	
	public:
		string block;
		int version;
		int typeId;
		int subpacketsType;
		
		unsigned long int currentValue;
		unsigned long int offset;
		int subpacketLength;
		
		vector<Packet *> subpackets;
		
		Packet(string data){
			
			block = data;
			
			offset = 0;
			version = binaryToDecimal(block.substr(offset, 3));
			offset = 3;
			typeId  = binaryToDecimal(block.substr(offset, 3));
			offset = 6;
			
			sumVersions += version;
			
			if(typeId == 4){
				currentValue = readType4();
			}
			else{
				
				subpacketsType = binaryToDecimal(block.substr(offset, 1));
				offset++;
				
				if(!subpacketsType)
					readSomeBits();
				else
					readSomeNumbers();
				
				operate();
				
			}
			
		}
		
		void readSomeBits(){
			
			int subpacketLength = binaryToDecimal(block.substr(offset, 15));
			offset += 15;
			
			int subpacketOffset = 0;
			
			string subpacketString = block.substr(offset, subpacketLength);
			
			do{
				
				Packet *p = new Packet(subpacketString.substr(subpacketOffset));
				subpacketOffset += p->offset;
				
				subpackets.push_back(p);
				
			}while(subpacketOffset < subpacketLength);
			
			
			offset += subpacketLength;
			
		}
		
		void readSomeNumbers(){
			
			int subpacketsToRead = binaryToDecimal(block.substr(offset, 11));
			offset += 11;
			
			int subpacketOffset = offset;
			
			for(int i = 0; i < subpacketsToRead; i++){
				
				Packet *p = new Packet(block.substr(subpacketOffset));
				subpacketOffset += p->offset;
				subpackets.push_back(p);
				
			}
			
			offset = subpacketOffset;
			
		}
		
		unsigned long int readType4(){
			
			int nextBlock;
			string current = "";
			
			do{
				
				nextBlock = binaryToDecimal(block.substr(offset, 1));
				offset++;
				current += block.substr(offset, 4);
				offset += 4;
				
			}while(nextBlock && offset < block.size());
			
			return binaryToDecimal(current);
			
		}
		
		void operate(){
			
			vector<int> collectedNumbers;
			
			switch(typeId){
				case 0:
					currentValue = 0;
					for(auto sp: subpackets)
						currentValue += sp->currentValue;
					break;
				case 1:
					currentValue = 1;
					for(auto sp: subpackets)
						currentValue *= sp->currentValue;
					break;
				case 2:
					
					for(auto sp: subpackets)
						collectedNumbers.push_back(sp->currentValue);
					
					sort(collectedNumbers.begin(), collectedNumbers.end());
					currentValue = collectedNumbers[0];
					break;
				case 3:
					
					for(auto sp: subpackets)
						collectedNumbers.push_back(sp->currentValue);
					
					sort(collectedNumbers.begin(), collectedNumbers.end());
					currentValue = collectedNumbers.back();
					break;
				case 5:
					if(subpackets[0]->currentValue > subpackets[1]->currentValue)
						currentValue = 1;
					else
						currentValue = 0;
					break;
				case 6:
					if(subpackets[0]->currentValue < subpackets[1]->currentValue)
						currentValue = 1;
					else
						currentValue = 0;
					break;
				case 7:
					if(subpackets[0]->currentValue == subpackets[1]->currentValue)
						currentValue = 1;
					else
						currentValue = 0;
					break;
				default:
					cout << "Critical Issue" << endl;
					exit(1);
			}
			
		}
		
		unsigned long int binaryToDecimal(string input){
			
			unsigned long int value = 0;
			
			for(int i = 0; i < input.size(); i++){
				char a = input.at(i);
				int v = atoi(&a);
				value += pow(2, input.size() - i - 1) * v;
			}
			
			return value;
			
		}
		
		
		
};


int main() {
	
	vector<string> input = getInput();
	
	string output = "";
	
	for(int i = 0; i < input[0].size(); i++)
		output += toBinary(input[0].at(i));
	
	
	Packet *p = new Packet(output);
	
	unsigned long int offset = 0;
	unsigned long int total = p->currentValue;
	
	cout << "Part 1: " << sumVersions << endl;
	cout << "Part 2: " << total << endl;
	
	
	return 0;
	
}