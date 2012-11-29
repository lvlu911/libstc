#include "Tokenizer.h"

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

Tokenizer::Tokenizer(const char *s)
{
        int rstCount = 0;
        LPICTCLAS_RESULT rstVec = ICTCLAS_ParagraphProcessA(s, strlen(s), rstCount, CODE_TYPE_UTF8, g_bPOSTagged);
        for(int i = 0; i < rstCount; i++)
                tokens.push_back(rstVec[i].iWordID);
        free(rstVec);
}

