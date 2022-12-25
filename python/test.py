import os


def getDirSize(dirPath: str) -> float:
  total = 0.0
  for d, _, objs in os.walk(dirPath):
    if d.split(os.sep)[1] == "proc":
        continue
    for obj in objs:
      try:
        file = os.path.join(d, obj)
        total += os.lstat(file).st_size
      except:
        print(d.split(os.sep))
        raise Exception
  total /= 1024**3
  print("Directory Starting At {} Contains {} GB".format(dirPath, total))
  return total



if __name__ == "__main__":
  import shutil
  import time
  # print(shutil.disk_usage('/').used / 1024**3)

  # getDirSize("/home")
  # # Files can be directories as well
  start = time.time()
  s1 = getDirSize("/home")
  s2 = getDirSize("/usr")
  s3 = getDirSize("/opt")
  s4 = getDirSize("/var")
  print("Total: {} GB".format(s1 + s2 + s3 + s4))
  print(time.time() - start)
  # getDirSize("/home/chankyo/snap/slack/common/.cache/gio-modules")
  # f = '/home/chankyo/snap/slack/common/.cache/gio-modules'
