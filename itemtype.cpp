#include "itemtype.h"

using namespace std;

File::File(string name) {

  fileName = name;
  wordCount = 0;

}

string File::getFileName() {

  return fileName;

}

int File::getWordCount() {

  return wordCount;

}

void File::incrementWordCount() {

  wordCount++;

}
