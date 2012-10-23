map<string,int> labels;
vector<int> jumps;
map<string,int> vars;


struct ifdata{//Stores data to be processed by wehn statment
	string newlab;
	int one;
	int two;
};

struct arraydata{
	int size;
	vector<int> index;
	vector<int> data;
};

map<string,arraydata> arrays;