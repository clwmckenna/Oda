bool isvalue(string lab){
	//Checks for lab is a numerical constant
	for(int i=lab.size()-1;i>=0;--i){
		if(not isdigit( lab[i] )){
			return false;
		}
	}
	return true;
}

int getValue(string lab){
	//gets value of constant or var or label
	if(lab[0]=='$'){
		lab.erase(0,1);
		return vars[lab];
	}else if(isvalue(lab)){
		return stoi(lab);
	}else{
		return labels[lab];
	}
}

void assignValue(string lab,int newv){
	//Assign value
	if(lab[0]=='$'){
		lab.erase(0,1);
		vars[lab] = newv;
	}else{
		return labels[lab] = newv;
	}
}


void var(string lab){
	int assign = 0;

	//Set a new var
	int a = lab.find(" ");
	lab = lab.substr(a+1,lab.size()-a-1);

	//Handle assigment
	if(lab.find(' ')!=lab.npos){
		string tmp =  lab.substr( lab.find(' ')+1, lab.size()-1);
		assign = stoi(     lab.substr( lab.find(' ')+1, lab.size()-1)    );
	}

	lab = lab.substr(0,lab.find(' '));

	//Handle labels separate to variables
	if(lab[0]=='$'){
		lab.erase(0,1);//Remove $
		vars[lab] = assign;
	}else{
		labels[lab] = assign;
	}
}