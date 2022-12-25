#include <mntent.h>
#include <iostream>
#include <cstring>

#include "strarray.h"
#include "drive.h"


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