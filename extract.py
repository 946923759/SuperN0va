#!/usr/bin/env python3
import sys
import shutil

for i in range(1,len(sys.argv)):
    infName = sys.argv[i]
    with open(infName,'rb') as inf:
        outName = infName.split(".",1)[0]

        header = inf.read(2)
        if header==b'\x00\x00': #mp4 with 2 extra header bytes
            outName+=".mp4"
            with open(outName,'wb') as outf:
                outf.write(inf.read())
        elif header==b'\x89\x50': #PNG (No changes to output, just a normal PNG)
            outName+=".png"
            shutil.copyfile(infName,outName)
        else: #Usually XML or other junk data
            print("Unknown file type for "+infName)
            continue
        print("Wrote "+outName)
