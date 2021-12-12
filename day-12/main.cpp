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

class Node{

	public:
		string name;
		bool visited;
		vector<string> neighbors;
		
		bool canBeVisitedMultiplesTimes(){
			
			
			if(name.compare("start") == 0 || name.compare("end") == 0)
				return false;
			
			return isupper(name.at(0));
			
		}

};

int countOcurrences(string input, string substring){
	
	int position = input.find(substring);
	
	if(position == string::npos){
		return 0;
	}
	
	return 1 + countOcurrences(input.substr(position + 1), substring);
	
}

bool hasSmallMultipleTimes(map<string, Node> nodes, string currentRoute){

	vector<string> smallNodes;
	
	for(auto [name, n]: nodes)
		if(!n.canBeVisitedMultiplesTimes())
			smallNodes.push_back(name);
		
		
	for(auto n: smallNodes)
		if(countOcurrences(currentRoute, n) > 1)
			return true;
		
	return false;

}

vector<string> visitAllNodes(map<string, Node> nodes, string currentRoute, string currentNode, int maxOcurrences){

	vector<string> results;
	
	if(currentNode.compare("end") == 0){
		results.push_back("end");
		return results;
	}
	
	if(!nodes[currentNode].canBeVisitedMultiplesTimes()){
		
		
		int currentMaxOcurrences = maxOcurrences;
		
		if(currentNode.compare("start") == 0 || hasSmallMultipleTimes(nodes, currentRoute))
			currentMaxOcurrences = 1;
		
		if(countOcurrences(currentRoute, currentNode) >= currentMaxOcurrences)
			return results;
		
	}
	
	for(auto neighbor: nodes[currentNode].neighbors){
		
		vector<string> routes = visitAllNodes(nodes, currentRoute + currentNode, neighbor, maxOcurrences);
		
		if(routes.size() != 0)
			for(auto route: routes){
				results.push_back(currentNode + "," + route);
			}
		
	}
	
	
	return results;

}

int main() {
	
	vector<string> input = getInput();
	map<string, Node> nodes;
	
	for(auto l: input){
		vector<string> tmp;
		split(tmp, l, is_any_of("-"));
		
		for(auto node: tmp){
		
			if(node.compare("-") != 0){
				
				if(nodes.count(node) == 0){
				
					Node *n = new Node();
					n->name = node;
					nodes[node] = *n;
				
				}
				
			}
		
		}
		
		nodes[tmp[0]].neighbors.push_back(tmp[1]);
		nodes[tmp[1]].neighbors.push_back(tmp[0]);
		
	}
	
	vector<string> resultsP1  = visitAllNodes(nodes, "", "start", 1);
	vector<string> resultsP2  = visitAllNodes(nodes, "", "start", 2);
	
	unsigned long int totalP1 = resultsP1.size();
	unsigned long int totalP2 = resultsP2.size();;
	
	cout << "Part 1: " << totalP1 << endl;
	cout << "Part 2: " << totalP2 << endl;
	
	return 0;
	
}