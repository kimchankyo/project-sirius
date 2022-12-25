#include <iostream>
#include <cstring>
#include "strarray.h"

using namespace std;

StringArray::StringArray() {
  length = 0;
}

StringArray::~StringArray() {
  if(length) {
    for(unsigned int i = 0; i < length; i++) {
      free(arr[i]);
    }
    free(arr);
  }
}

void StringArray::append(string str) {
  // copy string to buffer
  const char *cstr = str.c_str();
  char *strmem = (char *)malloc((strlen(cstr)+1)*sizeof(char));
  memcpy(strmem, cstr, strlen(cstr)+1);

  // create new array of char *
  if(length) {
    arr = (char **)realloc(arr, sizeof(char *)*(length+1));
  } else {
    arr = (char **)malloc(sizeof(char *));
  }
  arr[length] = strmem;
  length++;
}

string StringArray::get(unsigned int idx) {
  if(idx < length) { return string(arr[idx]); }
  throw invalid_argument("Index value is greater than or equal to length");
}

void StringArray::remove(unsigned int idx) {
  if(idx >= length) { 
    throw invalid_argument("Index value is greater than or equal to length");
  }
  free(arr[idx]);

  char **temp = (char **)malloc(sizeof(char *)*(length-1));
  for(unsigned int i = 0; i < length; i++) {
    if(i != idx) {
      if(i < idx) {
        temp[i] = arr[i];
      } else {
        temp[i-1] = arr[i];
      }
    }
  }
  free(arr);
  arr = temp;
  length--;
}

StringArray string_split(string str, char delim) {
  unsigned int start = 0;
  StringArray arr;
  for(unsigned int i = 0; i <= strlen(str.c_str()); i++) {
    if(str[i] == delim || str[i] == '\0') {
      string substr = str.substr(start, i-start);
      arr.append(substr);
      start = i+1;
    }
  }
  return arr;
}