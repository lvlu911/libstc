#ifndef __LIBSTC_TOKENIZER_H__
#define __LIBSTC_TOKENIZER_H__

#include <vector>
#include <stack>
#include <cstring>
#include <cstdlib>
#include "ICTCLAS50.h"

#define POS_TGGER_TEST
#ifdef POS_TAGGER_TEST
bool g_bPOSTagged=true;
#else
bool g_bPOSTagged=false;
#endif

using namespace std;

class Tokenizer
{
public:
        static bool startup();
        static void shutdown();
        Tokenizer(const char* s); 
        vector<int> getTokens(){return tokens;}
private:
        vector<int> tokens;
};

#endif
