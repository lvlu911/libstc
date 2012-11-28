#ifndef __LIBSTC_FILENAVIGATOR_H__
#define __LIBSTC_FILENAVIGATOR_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <cstdlib>
#include <stack>

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

#endif
