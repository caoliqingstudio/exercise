# -*- coding: utf-8 -*-
#!/usr/bin/python
import urllib
import urllib2
import re

#req = urllib2.Request('http://www.budejie.com/video')
#req.add_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 UBrowser/6.1.2107.204 Safari/537.36")
#html = urllib2.urlopen(req).read()
#reg = r'data-mp4="(.*?)"'
#result = re.findall(reg,html)
#print result

html1 = 'http://paper.people.com.cn/rmrb/html/'
data = '2017-03/27'
html2 = '/nbs.D110000renmrb_'
html3 = '.htm'
sixteen = ['01','02','03','04','05','06','07','08','09','10','11','12','13','14','15','16']
for pages in sixteen:
    req = urllib2.Request(html1+data+html2+pages+html3)#遍历十六个版面
    req.add_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 UBrowser/6.1.2107.204 Safari/537.36")
    html = urllib2.urlopen(req).read()
    reg = r'<a href=(.*?)><script>document.write'#使用正则表达式来寻找每条新闻的不同地址
    result = re.findall(reg,html)#找到正文中新闻的地址
    for html_num in result:#遍历每一个新闻地址
        news = urllib2.Request(html1+data+'/'+html_num)
        news.add_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 UBrowser/6.1.2107.204 Safari/537.36")
        content = urllib2.urlopen(news).read()
        artical = r'<!--enpcontent-->(.*?)<!--/enpcontent-->.*?<INPUT type=checkbox value=0 name=titlecheckbox sourceid="<Source>SourcePh</Source>" style="display:none">'#该正则表达式用于寻找正文内容，并且排除掉了重复的第二遍内容
        title_f = r'<title>(.*?)</title>'
        time_f = r'<div id="paperdatediv">(.*?)</div>'
        title = re.findall(title_f,content)#title成功的提取到了文章题目，但需要注意是list格式，无法当作字符串进行操作
        time  = re.findall(time_f,content,re.S)#title成功的提取到了文章题目，但需要注意是list格式，无法当作字符串进行操作
        mainbody = re.findall(artical,content,re.S)#mainbody成功的提取到了正文内容，但需要注意是list格式，无法当作字符串进行操作
        #mainbody.decode('utf-8')
        #mainbody.encode('utf-8')
        #mainbody.encode('utf-8')
        print (mainbody)