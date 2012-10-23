ifdata getVals(string lab){
	/*Handels the '2 $var label'
	pert of the when statment*/

	ifdata toret;//to retrun

	string one,two, newlab;
	int i,j;

	i = lab.find(' ');
	j = lab.find(' ',i+1)-i;//Less previous index

	one = lab.substr(0,i);
	two = lab.substr(i+1,j-1);
	toret.newlab = lab.substr(j+i+1,lab.length()-1);

	/*Rewriten to take advantage of new 
	Odavar.h functions*/
	toret.one = getValue(one);
	toret.two = getValue(two);

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
	return -1;
}