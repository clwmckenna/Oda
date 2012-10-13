#include "odawhat.h"
//#include "odavar.h"

bool newlabel(string lab, int line){
	//Returns is it main function
	//Add label da
	int i;

	for(i=0;i<lab.size();++i){//Remove spaces
		if(lab[i]==' '){
			lab.erase(i,1);
			i--;
		}
	}
		
	labels[lab.substr(0,lab.find(':',0))] = line;

	if(lab.substr(0,lab.find(':',0))=="main")
		return true;
	return false;
}

void echo(string lab){
	//Handles priting variable sto be implementd
	int firstfind = lab.find('"',0);
	lab = lab.substr(firstfind+1,lab.length());
	lab = lab.substr(0,lab.find('"'));

	for(int i=0;i<lab.size();++i){
		if(i<lab.size()-1)
			if(lab[i]=='\\' and lab[i+1]=='n'){
				cout << endl;
				++i;
				continue;
			}

		cout << lab[i];
	}
}

void halt(string lab){
	if(lab.find(' ')==lab.npos)
		exit(0);
	else{
		int stat;//Exit status
		lab = lab.substr(lab.find(' ')+1,lab.length());
		stat = stoi(lab);
		exit(stat);
	}
}

int jump(string lab){
	//Returns line to which to jump
	lab = lab.substr(lab.find(' ')+1,lab.length());
	return labels[lab];
}

void shell(string lab){
	//Execute system call
	lab = lab.substr(lab.find(' ')+1,lab.length());
	int firstfind = lab.find('"',0);
	lab = lab.substr(firstfind+1,lab.length());
	lab = lab.substr(0,lab.find('"'));
	system(lab.c_str());
}

void var(string lab,int i){
	//Set a new var
	cout << "Var called: ";
	int a = lab.find(" ");
	lab = lab.substr(a+1,lab.size()-a-1);

	//Handle labels separate to variables
	if(lab[0]='$'){

	}else{
		
	}
}