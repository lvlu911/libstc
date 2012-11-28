#ifndef __LIBSTC_NBYESMODEL_H__
#define __LIBSTC_NBYESMODEL_H__

#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>

using namespace std;

class NBayesModel
{
public:
        const vector<string> & getTypes();
        double getFreq(int wordID, const string& docType); 
        static vector<string> split(const string& str);
private:
        typedef map<int, map<int, double> >::iterator FREQ_MAP_IT;
        typedef map<int, map<int, double> >::const_iterator FREQ_MAP_CON_IT;
 
        map<int, map<int,double> > freqMap;//<wordID,<docType,freq>>
        vector<string> types;
        map<string, int> typeToIndex;    

        friend ostream& operator<<(ostream &os, const NBayesModel &model);
        friend istream& operator>>(istream &is, NBayesModel &model);
};

#endif
