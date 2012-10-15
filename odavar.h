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
	//cout << "'" << lab << "'" << endl;
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
	cout << "assignValue called\n";
	cout << lab << " " << newv << endl;
	if(lab[0]=='$'){
		lab.erase(0,1);
		vars[lab] = newv;
	}else{
		cout << lab << " " << labels[lab] << " " << newv << endl;
		labels[lab] = newv;
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
		cout <<  lab.substr( lab.find(' ')+1, lab.size()-1) << endl;
		assign = getValue(     lab.substr( lab.find(' ')+1, lab.size()-1)    );
	}

	lab = lab.substr(0,lab.find(' '));

	assignValue(lab,assign);
}