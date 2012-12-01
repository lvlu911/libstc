#ifndef __LIBSTC_TOKENIZER_H__
#define __LIBSTC_TOKENIZER_H__

#include <vector>
#include <stack>
#include <set>
#include <cstring>
#include <cstdlib>
#include <string>
#include "ICTCLAS50.h"

using namespace std;

namespace libstc
{

class Tokenizer
{
public:
        static bool startup();
        static void shutdown();
        Tokenizer(const string & s);
	Tokenizer(const string & s, const set<int> & stop); 
        vector<int> & getTokens();
private:
	void construct(const string & s);
        vector<int> tokens;
	set<int> stopWords;
};


inline vector<int>& Tokenizer::getTokens()
{
	return tokens;
}

inline Tokenizer::Tokenizer(const string & s)
{
	construct(s);
}

inline Tokenizer::Tokenizer(const string & s, const set<int> & stop)
{
	stopWords = stop;
	construct(s);
}

}

#endif
