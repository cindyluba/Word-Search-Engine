// itemtype.h
// declares class File
// stores file-name and number of times a word occured in the file

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <string>

using namespace std;

class File {

 public:

  //constructor for File
  File(string name);

  //returns the file name
  string getFileName();

  //returns the word count in that file
  int getWordCount();

  //increment the word count of that file 
  void incrementWordCount();

 private:
  string fileName;
  int wordCount;

};

#endif
