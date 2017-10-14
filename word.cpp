#include "word.h"

using namespace std;

Word::Word(string word) {

  wordString = word;
  fileList = new List;

}

void Word::insertWord(string word, WordNode*& wordHead) {

  Word* newWord = new Word(word);
  WordNode* newWordNode = new WordNode;
  newWordNode->wordInfo = newWord;

  if (wordHead == NULL)
    wordHead = newWordNode;
  else {
    WordNode* tempPtr;
    tempPtr = wordHead;
    while (tempPtr->nextWord != NULL)
      tempPtr = tempPtr->nextWord;
    tempPtr->nextWord = newWordNode;
  }

}

string Word::getWord() {

  return wordString;

}

List* Word::getFileList() {

  return fileList;

}
