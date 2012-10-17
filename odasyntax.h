#include "odavar.h"  //Import vars first as 'when' statment uses them
#include "odacalc.h"
#include "odawhat.h"

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
	if(firstfind!=lab.npos){
		//Handle strings
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
	}else{
		cout << getValue(  lab.substr(lab.find(' ',0)+1,lab.length()-1)  );
	}
}

void halt(string lab){
	if(lab.find(' ')==lab.npos)
		exit(0);
	else{
		lab = lab.substr(lab.find(' ')+1,lab.length());
		exit(getValue(lab));
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

int mgoto(string lab){
	lab = lab.substr(5,lab.length());
	return getValue(lab);
}

void aski(string lab){
	lab = lab.substr(5,lab.length()-5);
	int ret;
	cin >> ret;
	assignValue(lab,ret);
}

void mrand(string lab){
	//Borrowd from odacalc.h calc() function
	int po1, po2;
	int val1, val2;
	string ass;
	lab = lab.substr(5,lab.length());//Now we only have args left

	po1 = lab.find(' ');
	po2 = lab.find(' ',po1+1);
	val1 = getValue(lab.substr(0,po1));
	val2 = getValue(lab.substr(po1+1,po2-po1-1));
	ass = lab.substr(po2+1,lab.length()-po2);

	int tmp = 0;
	tmp = (rand()%(val2-val1))+val1;
	assignValue(ass, tmp);
}