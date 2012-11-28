#include "fileNavigator.h"

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

