/*
Linux Distributions Only
*/

#include <iostream>
#include <filesystem>
#include <stack>
#include <math.h>

#include <chrono>

using namespace std::chrono;

#include "strarray.h"
#include "drive.h"

using namespace std;
namespace fs = filesystem;

unsigned long int exploreTree(string path) {
  stack<string> searchPath;
  searchPath.push(path);
  unsigned long int totalLength = 0;

  while(!searchPath.empty()) {
    string curPath = searchPath.top();
    searchPath.pop();
    for(const auto& entry: fs::directory_iterator(curPath)) {
      if(entry.is_directory() && !entry.is_symlink()) { 
        searchPath.push(entry.path().string()); 
      } else if (entry.is_regular_file() && !entry.is_symlink()) {
        totalLength += entry.file_size();
      }
    }
  }
  cout << totalLength / pow(1024, 3) << " GB of data starting at " << path << endl;
  return totalLength;
}

unsigned long int exploreTreeRecurse(string path) {
  unsigned long int total = 0;
  for(const auto& entry: fs::directory_iterator(path)) {
    if(entry.is_directory() && !entry.is_symlink()) {
      total += exploreTreeRecurse(entry.path().string());
    } else if (entry.is_regular_file() && !entry.is_symlink()) {
      total += entry.file_size();
    }
  }
  return total;
}


int main() {
  // string roots[4] = {"/home", "/usr", "/opt", "/var"};

  auto start = high_resolution_clock::now();
  
  // unsigned long int total = 0;
  // for(string root: roots) {
  //   total += exploreTree(root);
  // }
  // cout << total / pow(1024, 3) << " GB found." << endl;
  
  // step 2
  find_mounted_drives();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << duration.count() / 1000000.00 << endl;
  return 0;
}
