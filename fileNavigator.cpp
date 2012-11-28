#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include "ICTCLAS50.h"

#define POS_TGGER_TEST
#ifdef POS_TAGGER_TEST
bool g_bPOSTagged=true;
#else
bool g_bPOSTagged=false;
#endif 

using namespace std;

class fileNavigator
{
public:
	fileNavigator(const string &dir);
	bool hasNext();
	const string &next();
private:
	stack<DIR*> s;
	string cur;
	string prefix;	
};

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

class NBayesModel
{
private:
	map<int, map<string, double> > freq;//<wordID,<documentClass,freq>>
}

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

fileNavigator::fileNavigator(const string &dir)
{
	DIR *d = opendir(dir.c_str());
	if(d != NULL)
		s.push(d);
	prefix = dir;
}
bool fileNavigator::hasNext()
{
	struct dirent *file;
	struct stat sb;
	while(!s.empty())
	{
		while( (file = readdir( s.top() )) != NULL )
		{
			if(strncmp(file->d_name, ".", 1) == 0)
				continue;
			string fullName = prefix + '/' + file->d_name; 
			if(stat(fullName.c_str(), &sb) >= 0 && S_ISDIR(sb.st_mode))
			{
				s.push(opendir(fullName.c_str()));
				prefix = fullName;
				continue;
			}
			cur = fullName;
			return true;	
		}
		closedir(s.top());
		s.pop();
		prefix.erase(prefix.rfind('/'));
	}	
	return false;
}
const string& fileNavigator::next()
{
	return cur;
}
int main()
{
	Tokenizer::startup();
	Tokenizer tk("abcdefgabc asfd  你好啊，美女。霍霍～");
	for(int i = 0; i < tk.getTokens().size(); i++)
		cout << tk.getTokens()[i] << endl;
	Tokenizer::shutdown();
/*
	fileNavigator fn("/home/lvlu/桌面/test");
	while(fn.hasNext())
	{
		cout << fn.next() << endl;		
	}
*/
}
