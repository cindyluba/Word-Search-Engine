// word.h
// declares class Word
// stores a word and pointer to the beginning of a linked list

#ifndef WORD_H
#define WORD_H

#include "list.h"
#include "itemtype.h"
#include <string>

using namespace std;

class Word {

 public:

  //structure for word node
  struct WordNode {
    Word* wordInfo = NULL;
    WordNode* nextWord = NULL;
  };

  //constructor for Word: initialize word
  Word(string word);

  //insert word to the word linked list 
  void insertWord(string word, WordNode*& wordHead);

  //returns the word 
  string getWord();

  //returns the pointer that points to the file list
  List* getFileList();

 private:
  string wordString;
  List* fileList;

};


#endif
