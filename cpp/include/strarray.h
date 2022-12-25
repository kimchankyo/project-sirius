#pragma once

using namespace std;

class StringArray {
  private:
    char **arr;
  public:
    unsigned int length;
    StringArray();
    ~StringArray();
    void append(string str);
    string get(unsigned int idx);
    void remove(unsigned int idx);
};

StringArray string_split(string str, char delim);