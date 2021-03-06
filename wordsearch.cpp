#include "wordsearch.h"
#include "word.h"
#include "list.h"
#include "itemtype.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {

  string dir;
  vector<string> files = vector<string>();

  if (argc < 2)
    {
      cout << "No Directory specified; Exiting ..." << endl;
      return(-1);
    }
  dir = string(argv[1]);
  if (getDir(dir, files) != 0)
    {
      cout << "Error opening " << dir << "; Exiting ..." << endl;
      return(-2);
    }

  // THIS PART OF THE CODE SETS UP THE INVERTED INDEX

  File *currentFile = NULL;
  File *file = NULL;
  Word* words = NULL;
  Word::WordNode* firstWord = NULL;
  Word::WordNode* wordCursor = NULL;
  List::FileNode* fileCursor = NULL;
  string word, input;
  int wordIndex, fileIndex;

  string slash("/");
  for (unsigned int i = 0; i < files.size(); i++) {
    if (files[i][0] == '.')
      continue; //skip hidden files
    cout << "OPEN " << files[i] << endl;
    ifstream fin((string(argv[1]) + slash + files[i]).c_str()); //open using absolute path
    // ...read the file..

    currentFile = new File(files[i]);

    while (!fin.eof()) {
      fin >> word;
      for (int i = 0; i < word.size(); i++) {
	word[i] = tolower(word[i]);
	if (!isalpha(word[i])) {
	  word.erase(i, 1);
	  i--;
	}
      }
      if (firstWord == NULL) {
	words->insertWord(word, firstWord);
	wordCursor = firstWord;
	file = new File(currentFile->getFileName());
	wordCursor->wordInfo->getFileList()->insertFile(file);
	fileCursor = wordCursor->wordInfo->getFileList()->getFileHead();
	fileCursor->fileInfo->incrementWordCount();
      }
      else if (wordIndex = wordIsPresent(word, firstWord)) {
	Word::WordNode* tempWordCursor;
	tempWordCursor = firstWord;
	for (int i = 1; i < wordIndex; i++)
	  tempWordCursor = tempWordCursor->nextWord;
	fileCursor = tempWordCursor->wordInfo->getFileList()->getFileHead();
	if (fileIndex = fileIsPresent(currentFile->getFileName(), fileCursor)) {
	  for (int i = 1; i < fileIndex; i++)
	    fileCursor = fileCursor->nextFile;
	}
	else {
	  file = new File(currentFile->getFileName());
	  tempWordCursor->wordInfo->getFileList()->insertFile(file);
	  while (fileCursor->fileInfo->getFileName() != currentFile->getFileName())
	    fileCursor = fileCursor->nextFile;
	}
	fileCursor->fileInfo->incrementWordCount();
      }
      else {
	words->insertWord(word, firstWord);
	wordCursor = wordCursor->nextWord;
	file = new File(currentFile->getFileName());
	wordCursor->wordInfo->getFileList()->insertFile(file);
	fileCursor = wordCursor->wordInfo->getFileList()->getFileHead();
	fileCursor->fileInfo->incrementWordCount();
      }
    }

    fin.close();
  }

  cout << "Input word (or \"exit\" to quit): ";
  cin >> input;
  while (input.compare("exit")) {
    for (int i = 0; i < input.size(); i++)
      input[i] = tolower(input[i]);
    cout << "File Name" << setw(15) << "Count" << endl;
    if (wordIndex = wordIsPresent(input, firstWord)) {
      wordCursor = firstWord;
      for (int i = 1; i < wordIndex; i++)
	wordCursor = wordCursor->nextWord;
      fileCursor = wordCursor->wordInfo->getFileList()->getFileHead();
      for (fileCursor; fileCursor != NULL; fileCursor = fileCursor->nextFile) {
	cout << fileCursor->fileInfo->getFileName();
	cout << setw(15) << fileCursor->fileInfo->getWordCount() << endl;
      }
    }
    cout << "Input word (or \"exit\" to quit): ";
    cin >> input;
  }

  return 0;

}

int getDir(string dir, vector<string> &files) {

  DIR *dp;
  struct dirent *dirp;

  if ((dp = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    files.push_back(string(dirp->d_name));
  }

  closedir(dp);

  return 0;

}

int wordIsPresent(string word, Word::WordNode* start) {

  Word::WordNode* tempPtr;
  tempPtr = start;
  int index = 1;

  while (tempPtr != NULL) {
    if (tempPtr->wordInfo->getWord() == word) {
      return (index);
    }
    tempPtr = tempPtr->nextWord;
    index++;
  }

  return 0;

}

int fileIsPresent(string fileName, List::FileNode* start) {

  List::FileNode* tempPtr;
  tempPtr = start;
  int index = 1;

  while (tempPtr != NULL) {
    if (tempPtr->fileInfo->getFileName() == fileName) {
      return (index);
    }
    tempPtr = tempPtr->nextFile;
    index++;
  }

  return 0;

}
