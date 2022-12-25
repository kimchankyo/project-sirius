/*
Linux Distributions Only
*/

#include <iostream>
#include <filesystem>
#include <stack>
#include <math.h>
#include <mntent.h>
#include <cstring>

#include <chrono>

using namespace std::chrono;

#include "strarray.h"

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

const string MOUNT_FILE_LOCATION = "/proc/self/mounts";
const string READ_WRITE_FLAG = "rw";
const string REMOUNT_FLAG = "errors=remount-ro";

bool is_drive(const mntent *ent) {
  // init criteria
  bool is_write = false, is_remount = false;

  // copy ent->mnt_opts
  StringArray opts = string_split(string(ent->mnt_opts), ',');

  // return false if number of options is 1
  if(opts.length == 1) { return false; }

  // check if READ_WRITE_FLAG and REMOUNT_FLAG options are enabled
  for(unsigned int i = 0; i < opts.length; i++) {
    string opt = opts.get(i);
    if(!strcmp(opt.c_str(), READ_WRITE_FLAG.c_str())) { is_write = true; }
    if(!strcmp(opt.c_str(), REMOUNT_FLAG.c_str())) {is_remount = true; }
  }
  if(is_write && is_remount) { return true; }
  return false;
}

void find_mounted_drives() {
  struct mntent ent;
  FILE *mountFile;
  char buf[256];

  mountFile = setmntent(MOUNT_FILE_LOCATION.c_str(), "r");
  if(mountFile == NULL) {
    perror("Failed to open mount information file.");
    exit(1);
  }
  
  while(NULL != getmntent_r(mountFile, &ent, buf, sizeof(buf))) {
    if(is_drive(&ent)) {
      cout << ent.mnt_fsname << " " << ent.mnt_dir << endl;
    }
  }
  endmntent(mountFile);
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
