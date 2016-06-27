#!/usr/bin/python

"""
        File      : count.py
        Author    : Cheng WANG
"""
import sys,os

extens = [".cpp",".h", ".pro", ".qrc"]
linesCount = 0
filesCount = 0

def funCount(dirName):
    global extens,linesCount,filesCount
    for root,dirs,fileNames in os.walk(dirName):
        for f in fileNames:
            fname = os.path.join(root,f)
            if '.' not in f:
                continue
            try :
                ext = f[f.rindex('.'):]
                if extens.count(ext) > 0:
                    filesCount += 1 
                    print fname
                    if not fname.__contains__("qcustomplot"):
                        l_count = len(open(fname).readlines())
                        linesCount += l_count
            except:
                print "Error occur!"
                pass


if len(sys.argv) > 1 :
    for m_dir in sys.argv[1:]:        
        print m_dir
        funCount(m_dir)
else :
    funCount(".")        

print "files count : ", filesCount
print "lines count : ", linesCount