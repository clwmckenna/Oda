string cws(string org){
	int i;

	replace(org.begin(),org.end(),'\t',' ');
	replace(org.begin(),org.end(),'\r',' ');
	replace(org.begin(),org.end(),'\n',' ');
	//Remove tabs

	//Remove extra spaces
	if(org.length()>2){
		for(i=0;i<org.length()-2;++i){
			if(org[i+1]==' ' and org[i]==' '){
				org.erase(i,1);
				--i;
			}
		}
	}

	if(org.length()>0)
		if(org[0]==' ')
			org.erase(0,1);

	if(org.length()>0)
		if(org[ org.length()-1 ]==' ')
			org.erase(org.length()-1,1);


	return org;
}

//Stoi taken from cfoldlib.h (Credit myself :))
int stoi(string toConv){
	//Converts std::string to int
	int result = 0;
	int tmp = 1;//What to multiply separate numbers by

	for(int i=toConv.length()-1 ;i>=0; --i){
		result += tmp*((int)toConv[i]-48); //Get ansii value and - 48 for char->int
		tmp *= 10;
	}
	return result;
}

template <class T>
void quote(T a){
	cerr << "'" << a << "'\n";
}