#ifndef LIST_H
#define LIST_H

#include "itemtype.h"

class List {

 public:

  //structure for file node 
  struct FileNode {
    File* fileInfo = NULL;
    FileNode* nextFile = NULL;
  };

  //constructor for List 
  List();

  //insert a file node to the file linked list
  void insertFile(File* file);

  //returns the file head in the linked list
  FileNode* getFileHead();

 private:
  FileNode* fileHead;

};

#endif
