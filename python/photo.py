#------coding=utf-8--*---

from urllib import request

url="http://www.huitu.com/design/show/20160501/124844807400.html"
Request =request.urlopen(url)
result = Request.read()
with open("1.html","wb") as f:
    f.write(result)