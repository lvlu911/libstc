libstc.so : fileNavigator.o Tokenizer.o NBayesModel.o Classifier.o ../libICTCLAS50.so
	g++ fileNavigator.o Tokenizer.o NBayesModel.o Classifier.o ../lib/libICTCLAS50.so -fPIC -shared -o ../bin/libstc.so
fileNavigator.o: fileNavigator.cpp fileNavigator.h
	g++ fileNavigator.cpp -c -o fileNavigator.o
Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ Tokenizer.cpp -c -o Tokenizer.o
NBayesModel.o: NBayesModel.cpp NBayesModel.h
	g++ NBayesModel.cpp -c -o NBayesModel.o
Classifier.o: Classifier.cpp Classifier.h
	g++ Classifier.cpp -c -o Classifier.o
test: test.cpp fileNavigator.o Tokenizer.o NBayesModel.o Classifier.o ../libICTCLAS50.so
	g++ test.cpp ../lib/libICTCLAS50.so fileNavigator.o Tokenizer.o NBayesModel.o Classifier.o -o ../bin/test
