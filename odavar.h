bool isvalue(string lab){
	//Checks for lab is a numerical constant
	for(int i=lab.size()-1;i>=0;--i){
		if(not isdigit( lab[i] )){
			return false;
		}
	}
	return true;
}

int getValue(string);

vector<int> getIndex(string lab, int *size=NULL){
	vector<int> index;
	int t;

	unsigned int tpos,tpos1;
	tpos = lab.find("]");
	while(tpos!=lab.npos){
		lab.erase(tpos--,1);
		tpos1 = lab.find("[");
		lab.erase(tpos1,1);
		t = getValue(lab.substr(0,tpos));
		index.push_back(t);


		if(size!=NULL){
			*size *= t;
		}


		lab.erase(0,tpos);


		tpos = lab.find("]");
	}

	return index;

}

int getPos(vector<int> ni, string name){
	int up,low;
	unsigned int i;

	low = arrays[name].size / arrays[name].index[0] * ni[0];
	up = arrays[name].size / arrays[name].index[0] * (ni[0]+1);
	
	for(i=1;i<ni.size();++i){

		low += (up-low) / arrays[name].index[i] * ni[i];
		up += (up-low) / arrays[name].index[i] * (ni[i]+1);
	}

	return low;
}

void assignValue(string lab, int newv){
	//Assign value
	if(lab[0]=='$'){
		lab.erase(0,1);

		unsigned int bracepos = lab.find("[");
		if(bracepos==lab.npos){
			arrays[lab].index.clear();
			arrays[lab].data.clear();
			arrays[lab].index.push_back(1);
			arrays[lab].data.push_back(newv);
		}else{

			/*Serious array stuff*/
			string name = lab.substr(0,bracepos);
			lab.erase(0,bracepos);
			arrays[name].data[getPos(getIndex(lab),name)] = newv;
		}

	}else{
		labels[lab] = newv;
	}
}

int getValue(string lab){
	//gets value of constant or var or label
	if(lab[0]=='$'){
		lab.erase(0,1);

		unsigned int bracepos = lab.find("[");
		if(bracepos==lab.npos){
			return arrays[lab].data[0];
		}else{

			/*Serious array stuff*/
			string name = lab.substr(0,bracepos);
			lab.erase(0,bracepos);
			return arrays[name].data[getPos(getIndex(lab),name)];
		}
		/*Updated for arrays*/


	}else if(isvalue(lab)){
		return stoi(lab);
	}else{
		return labels[lab];
	}
}


void var(string lab){
	int assign = 0;

	//Set a new var
	lab = lab.substr(4,lab.size()-4);

	//Handle assigment
	if(lab.find(' ')!=lab.npos){
		string tmp =  lab.substr( lab.find(' ')+1, lab.size()-1);
		assign = getValue(     lab.substr( lab.find(' ')+1, lab.size()-1)    );
	}

	lab = lab.substr(1,lab.find(' ')-1);
	unsigned int bracepos = lab.find("[");

	switch(bracepos==lab.npos){
		case true:
			arrays[lab].index.clear();
			arrays[lab].data.clear();
			arrays[lab].index.push_back(1);
			arrays[lab].size = 1;
			arrays[lab].data.push_back(assign);

			break;
		case false:

			int size = 1;
			string name = lab.substr(0,bracepos);
			lab.erase(0,bracepos);
			
			/*lab =    array indexes
			  size =   Size in vector
			  name =   Actual name
			  assign = Value to assign*/

			/*Get size and index from lab*/
			arrays[name].index.clear();
			arrays[name].data.clear();

			arrays[name].index = getIndex(lab,&size);
			arrays[name].size = size;

			for(int i=0;i<size;++i){
				arrays[name].data.push_back(assign);
			}
			break;
	}
}