#include "list.h"
#include <cstdlib>

using namespace std;

List::List() {

  fileHead = NULL;

}

void List::insertFile(File* file) {

  FileNode* newFile = new FileNode;
  newFile->fileInfo = file;

  if (fileHead == NULL)
    fileHead = newFile;
  else {
    FileNode* tempPtr;
    tempPtr = fileHead;
    while (tempPtr->nextFile != NULL)
      tempPtr = tempPtr->nextFile;
    tempPtr->nextFile = newFile;
  }

}

List::FileNode* List::getFileHead() {

  return fileHead;

}
