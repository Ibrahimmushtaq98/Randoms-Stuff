#include <dirent.h> 
#include <iostream> 
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/tokenizer.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::string;

void readFile(string *fileN, int size, string argu);
void readFileT(string file, string argu);
void makeIndex(string *fileN, int size);
void Indexed(string *words, int size, string file, int line);


int main(int argc, char** argv)
{
	bool inde = false;
	string tmp = "";
    int count = 0;
    string *files = new string[count];

    DIR *pdir = NULL; 
    pdir = opendir (".");
    struct dirent *pent = NULL;
 
	//Using current directory, this will find .txt files
    while (pent = readdir (pdir))
    {
        if (pent == NULL) 
        { 
            return -1;
        }else{
			tmp = pent->d_name;
			if(tmp == "index.log"){
				inde = true;
			}
			if(tmp.size() > 4 && tmp.substr(tmp.size()-4,tmp.size()) == ".txt"){
				string *tmp = new string[count+1];

				for(int i = 0; i < count; i++){
					tmp[i] = files[i];
				}
				delete [] files;
				files = tmp;

				files[count] = pent->d_name;
				count++;
			}

		}
    }
    closedir (pdir);
	string cmd = argv[1];
	if(cmd == "--make-index"){
		makeIndex(files,count);
	}else{
		if(inde == true){
			for(int i = 1; i < argc; i++ ){
				cout << "Keyword[" << i << "]" << endl;
				readFileT("index.log",argv[i]);
			}

		}else{
			for(int i = 1; i < argc; i++ ){
				cout << "Keyword[" << i << "]" << endl;
				readFile(files,count,argv[i]);
			}

		}
	}

	delete [] files;
    return 0;
}

void makeIndex(string *fileN, int size){
	string line = "";
	int lineC = 0;
	int count = 0;
	string *wordS = new string[count];
	for(int i = 0; i < size; i++){
		ifstream myfile(fileN[i]);
		while(getline(myfile,line)){
			lineC++;
			string *wordS = new string[count]; 
			boost::tokenizer<> tokens(line);

			for(string word : tokens){
				string* tmp = new string[count + 1];
				for(int x = 0; x < count; x++){
					tmp[x] = wordS[x];
				}
				delete [] wordS;
				wordS = tmp;
				wordS[count] = word;
				count++;
			}

			Indexed(wordS,count, fileN[i], lineC);
			delete [] wordS;
			count = 0;

		}
		myfile.close();
	}

}

void Indexed(string *word,int size, string file, int line){

	sort(word, word +size);
	int count = 1;


	ofstream outFile("index.log", std::ios::app);
	for(int i = 0; i < size; i++){
		if(word[i] == word[i+1]){
			count++;
		}else{
			outFile << word[i] << ",Found in file " 
					<< file << " in line " 
					<< line << " (" << count << " time)\n";
			count = 1;
		}
	}

	outFile.close();
}

void readFile(string *fileN, int size, string argu){
	string line = "";
	int wordC = 0;
	int lineC = 0;
	int buf = 0;

	for(int i = 0; i < size; i++){
		ifstream myfile(fileN[i]);
		wordC = 0; 
		lineC = 0;
		while(getline(myfile,line)){
			wordC = 0;
			lineC++;
			boost::tokenizer<> tokens(line);
			for(string word: tokens){
				if(word == argu){
					wordC++;
				}else{
					buf++;
				}
			}
			if(wordC > 0){
				cout << "\tfound in file "<< fileN[i] 
					<< " in line " << lineC 
					<< " (" << wordC <<" time)" << endl;
			}
		}
		myfile.close();
	}
	if(buf == size){
		cout<< "\tNot found\n";
	}
}

void readFileT(string file, string argu){
	int count = 0;
	string line = "";
	ifstream myfile(file);
	while(getline(myfile, line)){
		boost::tokenizer<>tokens(line);
		for(string word : tokens){
			if(word == argu){
				cout << "\t";
				for(string wordT : tokens){
					if(count > 1){
						cout << wordT << " "; 
					}else{
						count++;
					}
				}
				cout << endl;
			}
			count = 0;
			break;
		}
	}
}
