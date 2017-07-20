#------coding=utf-8--*---

from urllib import request
import re
import os
import sys
import zipfile
import json
with open("alleky.json","r") as fileKEY:
    allkeyfile=json.load(fileKEY)
#allkeyfile={"backdoor":0,"horse":0}
url0="http://www.offensivecomputing.net/search.cgi?search="
url1="http://www.offensivecomputing.net/"
print("when you close this py:")
print(" please delete the rest file \n and share the json file\n")
print("password = infected\n\n")
allkeylist=[]
allCodeFile=[]
with open("allFileName.json","r") as filename:
    allCodeFile=json.load(filename)
number = 0
for bbb in allkeyfile.keys():
    allkeylist.append(bbb)
for keyword in allkeylist:
    print("*"*20)
    if not allkeyfile[keyword]:
        url=url0+keyword
        Request =request.urlopen(url)
        result00 = Request.read()
        mainhtml=keyword+".html"
        result = result00.decode('utf-8')
        reg=r'<a href="(.*?)">Download Sample'
        pattern = re.compile(reg)
        infoList=pattern.findall(result)
        regKey=r'<b>Original Filename:</b>\s+</td>\s+<td id="checksum">\s+(.*?)\s+</td>'
        pattKey=re.compile(regKey)
        keyList = pattKey.findall(result)
        if len(keyList)> 1:
            with open(mainhtml,"wb") as fmain:
                fmain.write(result00)
            for keyword12 in keyList:
                keyList0=keyword12.split(".")
                print(keyList0)
                for aaa in keyList0[0:3]:
                    if not aaa in allkeyfile:
                        allkeylist.append(aaa)
                        allkeyfile[aaa]=0
            for info in infoList:
                number=number + 1
                NowUrl=url1+info
                exefile=request.urlopen(NowUrl).read()
                regNow=r'id=(.*?)&auth'
                patternNow = re.compile(regNow)
                nameList = patternNow.findall(info)
                name0 = keyword+"_"+nameList[0]
                name = name0 + ".zip"
                allCodeFile.append(name0)
                with open(name,"wb") as f:
                    f.write(exefile)
                    print(name+" download")
        allkeyfile[keyword]=1 
    print(keyword+" is ok!")
    with open("alleky.json","w") as fw:
        json.dump(allkeyfile,fw)
        print("json update with ",keyword)
        print("*"*20,"\n")
    with open("allFileName.json","w")as fall:
        json.dump(allCodeFile,fall)
print("OK")
print("include all file")
print(number)
