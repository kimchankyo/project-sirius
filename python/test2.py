import psutil




parts = psutil.disk_partitions()

for part in parts:
  print(part)
  # print("Device: {}\tFS: {}\tMountPoint: {}".format(part.device, part.fstype, part.mountpoint))