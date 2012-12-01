#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "fileNavigator.h"
#include "Tokenizer.h"
#include "NBayesModel.h"
#include "Classifier.h"

using namespace std;
using namespace libstc;

void test_fileNavigator(char *arg)
{
	string folderPath(arg);
	fileNavigator fn(folderPath);
        while(fn.hasNext())
        	cout << fn.next() << endl;
}

void test_Tokenizer(char *arg)
{
	Tokenizer::startup();
        Tokenizer tk(arg);
        for(int i = 0; i < tk.getTokens().size(); i++)
        	cout << tk.getTokens()[i] << endl;
        Tokenizer::shutdown();
}

void test_NBayesModel_split(char *arg)
{
	string sentence(arg);
	vector<string> v = NBayesModel::split(sentence);	
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
}

void test_NBayesModel_io(char *arg1, char *arg2)
{
	ifstream is(arg1);
	ofstream os(arg2);
	if(is && os)
	{
		NBayesModel m;
		is >> m;
		
		for(int i = 0; i < m.getTypes().size(); i++)
			cout << m.getTypes()[i] << " ";
		cout << endl;
		
		for(map<int, map<int,double> >::const_iterator it1 = m.getFreqMap().begin();
			it1 != m.getFreqMap().end(); it1++)
		{
			cout << it1->first << " : ";
			for(map<int, double>::const_iterator it2 = it1->second.begin();
				it2 != it1->second.end(); it2++)
				cout << "(" << it2->first << "," << it2->second <<") ";
			cout << endl;
		}
		
		os << m;	
	}
	else
		cout << arg1 << "or" << arg2 << " doesn't exists." << endl;
}

void test_Classifier_rs(char *arg1, char *arg2)
{
	string file1(arg1), file2(arg2);
	Classifier c;
	c.setModelFile(file1);
	c.save(file2);
}

void test_Classifier_ts(char *arg1, char *arg2)
{
	Tokenizer::startup();

	string folder(arg1), file(arg2);
	Classifier c;
	c.train(folder);
	c.save(file);
	
	Tokenizer::shutdown();
}

void test_Classifier_test(char *arg1, char *arg2)
{
	Tokenizer::startup();

	string file1(arg1), file2(arg2);
	Classifier c;
	c.setModelFile(file1);
	cout << c.test(file2) << endl;
	
	Tokenizer::shutdown();
}

int main(int argc, char** argv)
{
        if(argc == 3)
        {   
		string option = string(argv[1]);
		if(option == "-f")
                	test_fileNavigator(argv[2]);
		else if(option == "-t")
			test_Tokenizer(argv[2]);
		else if(option == "-ns")
		{
			test_NBayesModel_split(argv[2]);
		}
        }
	else if(argc == 4)
	{
		string option = string(argv[1]);
		if(option == "-nio")
			test_NBayesModel_io(argv[2], argv[3]);
		if(option == "-crs")
			test_Classifier_rs(argv[2], argv[3]);
		if(option == "-cts")
			test_Classifier_ts(argv[2], argv[3]);
		if(option == "-ct")
			test_Classifier_test(argv[2], argv[3]);
	}   
}

