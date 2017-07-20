#------coding=utf-8--*---

from urllib import request
import re
import os
import sys
import zipfile
keyword=sys.argv[1]
print(keyword)
url0="http://www.offensivecomputing.net/search.cgi?search="
url=url0+keyword
url1="http://www.offensivecomputing.net/"
print("password = infected")
Request =request.urlopen(url)
result = Request.read()
mainhtml=keyword+".html"
with open(mainhtml,"wb") as fmain:
    fmain.write(result)
result = result.decode('utf-8')
reg=r'<a href="(.*?)">Download Sample'
pattern = re.compile(reg)
infoList=pattern.findall(result)
for info in infoList:
    print(info)
    NowUrl=url1+info
    exefile=request.urlopen(NowUrl).read()
    regNow=r'id=(.*?)&auth'
    patternNow = re.compile(regNow)
    nameList = patternNow.findall(info)
    name = keyword+"_"+nameList[0] + ".zip"
    with open(name,"wb") as f:
        f.write(exefile)
print("OK")
