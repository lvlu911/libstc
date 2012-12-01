#include "Tokenizer.h"

#define POS_TGGER_TEST
#ifdef POS_TAGGER_TEST
bool g_bPOSTagged=true;
#else
bool g_bPOSTagged=false;
#endif


using namespace std;
using namespace libstc;

bool Tokenizer::startup()
{
        if(!ICTCLAS_Init())
                return false;
        ICTCLAS_SetPOSmap(2);
}

void Tokenizer::shutdown()
{
        ICTCLAS_Exit();
}

void Tokenizer::construct(const string & s) 
{
	int rstCount = 0;
        LPICTCLAS_RESULT rstVec = ICTCLAS_ParagraphProcessA(s.c_str(), 
                                s.size(), rstCount, CODE_TYPE_UTF8, g_bPOSTagged);
        for(int i = 0; i < rstCount; i++)
        {   
        	if(rstVec[i].iWordID > 0 && !stopWords.count(rstVec[i].iWordID))
        		tokens.push_back(rstVec[i].iWordID);
	}   
        free(rstVec);
	
}

