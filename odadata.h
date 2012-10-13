map<string,int> labels;
map<string,int> vars;
vector<int> jumps;

struct ifdata{//Stores data to be processed by wehn statment
	string newlab;
	int one;
	int two;
};