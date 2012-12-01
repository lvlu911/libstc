#ifndef __LIBSTC_NBYESMODEL_H__
#define __LIBSTC_NBYESMODEL_H__

#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

namespace libstc
{

class NBayesModel
{
public:
        const vector<string> & getTypes();
        void setTypes(const vector<string>& types);
	
	const map<int, map<int,double> > & getFreqMap() const; 
     	
	double getFreq(int wordID, int docType);
	void setFreq(int wordID, int docType, double freq);
	
	void clear();
	static vector<string> split(const string& str);
private:
        typedef map<int, map<int, double> >::iterator FREQ_MAP_IT;
        typedef map<int, map<int, double> >::const_iterator FREQ_MAP_CON_IT;
 
        map<int, map<int,double> > freqMap;//<wordID,<docType,freq>>
        vector<string> types;

        friend ostream& operator<<(ostream &os, const NBayesModel &model);
        friend istream& operator>>(istream &is, NBayesModel &model);
};

ostream& operator<<(ostream &os, const NBayesModel &model);
istream& operator>>(istream &is, NBayesModel &model);

inline const vector<string> & NBayesModel::getTypes()
{
	return types;
}

inline void NBayesModel::setTypes(const vector<string> & types)
{
        this->types = types;
}

inline const map<int, map<int,double> > & NBayesModel::getFreqMap() const
{
	return freqMap;
}

}

#endif
