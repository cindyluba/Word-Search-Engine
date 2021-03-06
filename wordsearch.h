#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include "list.h"
#include "word.h"
#include <vector>

using namespace std;

//main program
int main(int argc, char* argv[]);

int getDir(string dir, vector<string> &files);

//check if the word already exists in the word list, returns 0 if not, returns the index of the word node in the list if it exists
int wordIsPresent(string word, Word::WordNode* start);

//check if the file already exists in the file list, returns 0 if not, returns the indexof the file node in the list if it exists
int fileIsPresent(string fileName, List::FileNode* start);

#endif
