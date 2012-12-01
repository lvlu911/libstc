#ifndef __LIBSTC_FILENAVIGATOR_H__
#define __LIBSTC_FILENAVIGATOR_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stack>

using namespace std;

namespace libstc
{

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

}

#endif
