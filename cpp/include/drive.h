#pragma once

#include <mntent.h>

bool is_drive(const mntent *ent);
void find_mounted_drives();
