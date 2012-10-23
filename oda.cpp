/*Version 0.1.0rc
TODO:
  - Make basic errors
  - Arrays
*/
using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <map>
#include <cmath>

#include "odadata.h"
//Data structures included now make variables for odasynatx
int a=0;

#include "odalib.h"
#include "odasyntax.h"

#define is_type_signed(my_type) (((my_type)-1) < 0)

void execute(char filen[]){
	srand(time(NULL));
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
	unsigned int i,main;
	int tjump;
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
			/*Fix for a that allows multiline comment to be single line
			before it the scanner never detected the closing *\/ when it was
			on the same line*/
			if(filec[i].find("*/")!=filec[i].npos){
				filec[i] = filec[i].substr(0,filec[i].find("/*")) + filec[i].substr(filec[i].find("*/")+2,filec[i].length());
			}else{
				iscomment = true;
				filec[i] = filec[i].substr(0,filec[i].find("/*"));
			}
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

		if(filec[i][ filec[i].length()-1 ] == ';'){
			filec[i].erase(filec[i].length()-1,1);
		}

		/*Detect laebls*/
		if(filec[i][ filec[i].length()-1 ] == ':'){
			tmain = newlabel(filec[i],i);
			if(tmain)//If it's main
				main = i;
		}
	}


	for(i=main;i<filec.size();++i){
		if(filec[i].find("echo")== 0){
			echo(filec[i]);
		}else if(filec[i].find("halt")== 0){
			halt(filec[i]);
		}else if(filec[i].find("jump")== 0){
			jumps.push_back(i);//Important leave alone
			i = jump(filec[i])-1;
		}else if(filec[i]=="prev"){
			i = jumps[jumps.size()-1];
			jumps.pop_back();
		}else if(filec[i].find("shell")==0){
			shell(filec[i]);
		}else if(filec[i].find("when")==0){
			tjump = when(filec[i]);
			/*Fix variable label assigment prev error*/
			if(tjump!=-1){
				jumps.push_back(i);//Fixed there
				i = tjump-1;
			}
		}else if(filec[i].find("var")==0){
			var(filec[i]);
		}else if(filec[i].find("goto")==0){
			i = mgoto(filec[i])-1;

		}else if(filec[i][0]=='+' or filec[i][0]=='*' or filec[i][0]=='-' or filec[i][0]=='/' or filec[i][0]=='^' or filec[i][0]=='%' or filec[i][0]=='$'){
			//Maths :)
			calc(filec[i]);
		}else if(filec[i].find("aski")==0){
			aski(filec[i]);
		}else if(filec[i].find("rand")==0){
			mrand(filec[i]);
		}
	}

}

int main(int argc, char *argv[]){
	if(argc>1)
		execute(argv[1]);
		//Begin execution
	return 0;
}