#include "Classifier.h"

using namespace std;
using namespace libstc;


Classifier::Classifier() : model(NULL)
{
	int stopArr[] = {23161,56,74123,63889,31816,64337,50214,55282,13,14,49,45,46,52622,2133,65243,48415,52622,42865,40459,16498,16755,85616,29495,51842,17242,48477,13185,55924,15345,-1};
	for(int i = 0; stopArr[i] != -1; i++)
	{
		stop.insert(stopArr[i]);
	}
}

Classifier::~Classifier()
{
	delete model;
}

void Classifier::setModelFile(const string &modelFile)
{
	this->modelFile = modelFile;
	ifstream is(modelFile.c_str());
	if(is)
	{
		model = new NBayesModel;
		is >> *model;
	}
	is.close();
}

void Classifier::getDefaultModelFile()
{	
	char buf[1000] = {'\0'};
	readlink("/proc/self/exe", buf, BUFSIZ);
	string exeFile = string(buf);
	modelFile = exeFile.substr(0, exeFile.rfind('/')) + "/.NBayesModel";
}

void Classifier::train(const string& folderPath)
{
	ifstream cis((folderPath + "/ClassList.txt").c_str());
	if(cis)
	{
		map<string, string> classList;
		string line;
		while(getline(cis, line))
		{
			int pos = line.find(' ');	
			classList[line.substr(pos + 1, line.size()-pos-2)] = line.substr(0, pos);
		}
		cis.close();
		
		//count the number of all words
		map<int, map<int,int> > NumMap;//<wordID,<docType,num>>
		set<int> NumSet[classList.size()];//<wordID>[docType]
		vector<string> types;
		int docType = 0;
		int j = 0;	
		for(map<string, string>::iterator it = classList.begin();
			it != classList.end(); it++,j++)
		{
			types.push_back(it->first);
			fileNavigator fn(folderPath + '/' + it->second);
			
			while(fn.hasNext())
			{
				ifstream eis(fn.next().c_str());
				if(eis)
				{
					string line;
					while(getline(eis, line))
					{
						Tokenizer tk(line, stop);
						for(int i = 0; i < tk.getTokens().size(); i++)
						{
							int wordID = tk.getTokens()[i];
							NumMap[wordID][j]++;	
							NumSet[j].insert(wordID);
						}
					}
				}
				eis.close();
			}
		}
			
		if(model == NULL)
			model = new NBayesModel;	
		model->clear();	
		model->setTypes(types);
		for(map<int, map<int, int> >::iterator it1 = NumMap.begin();
			it1 != NumMap.end(); it1++)
		{
			j = 0;
			for(map<int, int>::iterator it2 = it1->second.begin();
				it2 != it1->second.end(); it2++, j++)
			{
				model->setFreq(it1->first,it2->first,
						(it2->second + 1.0) / (NumMap.size() + NumSet[j].size()));
								
			}			
		} 
			
	}
}

string Classifier::test(const string& filePath)
{
	if(model == NULL)
	{
		model = new NBayesModel;	
		if(modelFile.size() == 0)
			getDefaultModelFile();
		
		ifstream mis(modelFile.c_str());//model ifstream
		if(!mis)
			return "Cannot Find the model. Please train first."; 		
		mis >> *model;
		mis.close();	
	}

	ifstream dis(filePath.c_str());//document ifstream
	if(!dis)
		return "The file path is wrong.";

	string line;
	int num = model->getTypes().size();
	double freq[num];
	for(int i = 0; i < num; i++)
		freq[i] = 1.0;
	while(getline(dis, line))
	{
		Tokenizer tk(line, stop);
		
		for(int j = 0; j < tk.getTokens().size(); j++)
		{
			double minFreq = bigDouble;
			int target = -1;
			
			for(int i = 0; i < num; i++)
			{
				freq[i] *= model->getFreq(tk.getTokens()[j], i);	
				
				if(freq[i] < minFreq)
				{   
					minFreq = freq[i];
					target = i;
				}
			}
		
			//cout << minFreq << endl;
			
			if(minFreq < reasonableDouble)
			{   
				for(int i = 0; i < num; i++)
				{           
					freq[i] /= minFreq; 
                        	}
			}   

		}
	
	}
	dis.close();	

	double maxFreq = smallDouble;
	int target = -1;
	for(int i = 0; i < num; i++)
	{
		cout << model->getTypes()[i] << " " << freq[i] << endl;
		if(freq[i] > maxFreq)
		{
			maxFreq = freq[i];
			target = i;
		}
	}
	return model->getTypes()[target];			
}

void Classifier::save()
{
	if(modelFile.size() == 0)
		getDefaultModelFile();
	save(modelFile);
}

void Classifier::save(const string& modelFile)
{
	ofstream mos(modelFile.c_str());
	if(mos)
		mos << *model;
	mos.close();		
}

