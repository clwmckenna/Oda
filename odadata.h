vector<int> jumps;


struct ifdata{//Stores data to be processed by wehn statment
	string newlab;
	int one;
	int two;
};

struct arraydata{
	int size;
	vector<int> index;
	vector<int> data;
	bool islabel;
};

map<string,arraydata> arrays;