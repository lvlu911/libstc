#ifndef __LIBSTC_CLASSIFIER_H__
#define __LIBSTC_CLASSIFIER_H__

#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "NBayesModel.h"
#include "Tokenizer.h"
#include "fileNavigator.h"

using namespace std;
using namespace libstc;

namespace libstc
{

class Classifier
{
public:
        Classifier();
        void setModelFile(const string &modelFile);
        void train(const string& folderPath);
        string test(const string& filePath);
        void save();
        void save(const string& filePath);
        ~Classifier();
private:
        const static double smallDouble = -1.0;
	const static double bigDouble = 0.0 + 0x7fffffff;
	const static double reasonableDouble = 1.0 / 1024;
        string modelFile;
        void getDefaultModelFile();
        NBayesModel *model;
	set<int> stop;
};


}

#endif
