void calc(string lab){
	int po1, po2;
	int val1, val2;
	string ass;
	char op;
	op = lab[0];
	lab = lab.substr(2,lab.length());//Now we only have args left

	po1 = lab.find(' ');
	po2 = lab.find(' ',po1+1);
	val1 = getValue(lab.substr(0,po1));
	val2 = getValue(lab.substr(po1+1,po2-po1-1));
	ass = lab.substr(po2+1,lab.length()-po2);

	switch(op){
		case '+':
			assignValue(ass,val1+val2);
			break;
		case '-':
			assignValue(ass,val1-val2);
			break;
		case '/':
			assignValue(ass,val1/val2);
			break;
		case '*':
			assignValue(ass,val1*val2);
			break;
		case '%':
			assignValue(ass,val1%val2);
			break;
		case '^':
			assignValue(ass,pow(val1,val2));
			break;
		case '$':
			/*Get 2nd arg again*/
			assignValue(  lab.substr(po1+1,po2-po1-1) ,sqrt(val1));
			break;
	}
}