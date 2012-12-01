#include "NBayesModel.h"

using namespace std;
using namespace libstc;

vector<string> NBayesModel::split(const string& str)
{
	vector<string> words;
	string word;
	bool inWord = false;
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ')
		{
			if(inWord)
			{	
				words.push_back(word);
				word.clear();
				inWord = false;
			}
		}
		else
		{
			if(!inWord)
				inWord = true;
			word.push_back(str[i]);
		}
	}
	if(inWord)
		words.push_back(word);
	return words;
}

double NBayesModel::getFreq(int wordID, int docType)
{
	if(docType >= 0 && docType <= types.size())
	{
        	NBayesModel::FREQ_MAP_IT it1 = freqMap.find(wordID);
		if(it1 != freqMap.end())
       		{	    
                	map<int,double>::iterator it2 = it1->second.find(docType);
                	if(it2 != it1->second.end())
                        	return it2->second;
                	return 1.0 / freqMap.size();
        	}
		else
			return 1.0;//neglect this word.
	}
        return 0.0;
}

void NBayesModel::setFreq(int wordID, int docType, double freq)
{
	freqMap[wordID][docType] = freq;
}

void NBayesModel::clear()
{
	types.clear();
	freqMap.clear();
}

ostream& libstc::operator<<(ostream &os, const NBayesModel &model)
{
	int len = model.types.size();

	for(int i = 0; i < len; i++)
		os << model.types[i] << " ";
	os << endl;
	
        for(NBayesModel::FREQ_MAP_CON_IT it1 = model.freqMap.begin(); it1 != model.freqMap.end(); it1++)
        {
		for(int i = 0; i < len; i++)
		{
			map<int,double>::const_iterator it2 = it1->second.find(i);
			if(it2 != it1->second.end())
				os << it2->second << " ";
			else
				os << "0 ";
		}
                os << it1->first << endl;
        }
}

istream& libstc::operator>>(istream &is, NBayesModel &model)
{
        model.clear();

	string line;
	getline(is, line);
	model.setTypes(NBayesModel::split(line));
	
	int len = model.types.size();
	vector<string> v;
        while(getline(is, line))
        {
		v = NBayesModel::split(line);
		if(v.size() == len + 1)
		{
			int wordID = atoi(v[len].c_str());
			if(wordID > 0)
			{
				map<int,double> m;
				for(int i = 0; i < len; i++)
				{
					double freq = atof(v[i].c_str());
					if(freq > 0.0)
						m[i] = freq;
				}
				model.freqMap[wordID] = m;
			}
		}
        }

}

