using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <map>

#include "odadata.h"
//Data structures included now make variables for odasynatx
int a=0;

#include "odalib.h"
#include "odasyntax.h"

void execute(char filen[]){
	vector<string> filec;//Stores file context
	ifstream org (filen);
	string tmp;
	while(true){
		if(org.eof())break;
		getline(org,tmp);
		filec.push_back(tmp);
	}
	org.close();
	//Read file into a vector

	//prepare labels and clear whitespace
	int i,main,tjump;//Stores main() line
	bool tmain, iscomment = false;//True if is comment
	for(i=0;i<filec.size();++i){

		filec[i] = cws(filec[i]);

		//Start multiline comment handling
		if(iscomment){
			if(filec[i].find("*/")!=filec[i].npos){
				filec[i] = filec[i].substr(filec[i].find("*/")+2,filec[i].length());
				iscomment = false;
			}else{
				filec.erase(filec.begin()+i);
				--i;
				continue;
			}
		}

		if(filec[i].find("/*")!=filec[i].npos){
			iscomment = true;
			filec[i] = filec[i].substr(0,filec[i].find("/*"));
		}
		//End multiline comment handling

		/*Fixes "bug" that only allowed //coemmetns to start at str[0]*/
		if(filec[i].find("//")!=filec[i].npos){//Handle comments
			filec[i].erase(filec[i].find("//"),filec[i].length());
			--i;
			continue;
		}

		/*Rease empty lines*/
		if(filec[i].length()==0){
			filec.erase(filec.begin()+i);
			--i;
			continue;
		}

		/*Detect laebls*/
		if(filec[i][ filec[i].length()-1 ] == ':'){
			tmain = newlabel(filec[i],i);
			if(tmain)//If it's main
				main = i;
		}
	}

	//cout << main << endl;

	for(i=0;i<filec.size();++i){
		cout << filec[i] << endl;
	}
	return;
	//cout << endl;//Debuging to print out filec

	for(i=main;i<filec.size();++i){
		cerr << '[' << filec[i] << "] " << i << endl;
		if(filec[i].find("echo")== 0){
			echo(filec[i]);
		}else if(filec[i].find("halt")== 0){
			halt(filec[i]);
		}else if(filec[i].find("jump")== 0){
			jumps.push_back(i);//Important leave alone
			show(jumps);
			i = jump(filec[i])-1;
			cout << "Jumping to line "<<i+1<<endl;
		}else if(filec[i]=="prev"){
			i = jumps[jumps.size()-1];
			jumps.pop_back();
			show(jumps);
		}else if(filec[i].find("shell")==0){
			shell(filec[i]);
		}else if(filec[i].find("when")==0){
			tjump = when(filec[i]);
			/*Fix variable label assigment prev error*/
			if(tjump!=-1){
				jumps.push_back(i);//Fixed there
				show(jumps);
				i = tjump-1;
			}
		}else if(filec[i].find("var")==0){
			var(filec[i]);
		}
	}

}

int main(int argc, char *argv[]){
	if(argc>1)
		execute(argv[1]);
		//Begin execution
	return 0;
}