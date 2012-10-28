int finwhen(string lab, bool to){
	/*Assigns value if it's a variableand return -1
	otherwise return new lable pos*/
	if(islabel(lab)){
		/*Make sure we dont' assign value:
		if it's false just return -1*/
		if(to)
			return getValue(lab);
		return -1;
	}
	
	assignValue(lab,to);
	return -1;
}

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
	lab.erase(0,2);//Erase 'if'

	ifdata tmpdata;

	if(lab[0]=='>' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab, tmpdata.one>=tmpdata.two );

	}else if(lab[0]=='<' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab, tmpdata.one<=tmpdata.two );

	}else if(lab[0]=='='){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab, tmpdata.one==tmpdata.two );

	}else if(lab[0]=='>'){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab,tmpdata.one>tmpdata.two);

	}else if(lab[0]=='<'){
		lab = lab.substr(2,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab,tmpdata.one<tmpdata.two);

	}else if(lab[0]=='!' and lab[1]=='='){
		lab = lab.substr(3,lab.length());

		tmpdata = getVals(lab);

		return finwhen(tmpdata.newlab,tmpdata.one!=tmpdata.two);
	}
	return -1;
}