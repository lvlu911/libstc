#include "NBayesModel.h"

double NBayesModel::getFreq(int wordID, const string& docType)
{
        T_FREQ_MAP::iterator it1 = freq.find(wordID);
        if(it1 != freq.end())
        {    
                T_SD_MAP::iterator it2 = it1->second.find(docType);
                if(it2 != it1->second.end())
                        return *it2;
                return 1.0 / freqMap.size();
        }
        return 0.0;
}

ostream& operator<<(ostream &os, const NBayesModel &model)
{
        for(T_FREQ_MAP::iterator it1 = model.begin(); it1 != model.end(); it1++)
        {
                for(T_SD_MAP::iterator it2 = it1->second.beign();
                        it2 != it1->second.end(); it2++)
                        os << it2->first <<" " << it2->second << " ";
                os << it1->first << endl;
        }
}

istream& operator>>(istream &is, NBayesModel &model)
{
        string line;
        while(getline(is, line))
        {
                line.find
        }

}

