ifdata getVals(string lab){
	ifdata toret;//to retrun

	string one,two, newlab;
	int i,j;

	i = lab.find(' ');
	j = lab.find(' ',i+1)-i;//Less previous index

	one = lab.substr(0,i);
	two = lab.substr(i+1,j-1);
	toret.newlab = lab.substr(j+i+1,lab.length()-1);

	if(isvalue(one)){
		toret.one = stoi(one);
	}else{
		toret.one = vars[one];
	}

	if(isvalue(two)){
		toret.two = stoi(two);
	}else{
		toret.two = vars[two];
	}

	return toret;
}

int when(string lab){
	lab.erase(0,4);//Erase 'when'

	ifdata tmpdata;

	if(lab[0]=='>' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one>=tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}

	}else if(lab[0]=='<' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one<=tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}

	}else if(lab[0]=='='){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one==tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}
	}else if(lab[0]=='>'){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one>tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}
	}else if(lab[0]=='<'){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one<tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}

	}else if(lab[0]=='!' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		if(tmpdata.one!=tmpdata.two){
			return labels[tmpdata.newlab];
		}else{
			return -1;
		}
	}
}