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
    req = urllib2.Request(html1+data+html2+pages+html3)#����ʮ��������
    req.add_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 UBrowser/6.1.2107.204 Safari/537.36")
    html = urllib2.urlopen(req).read()
    reg = r'<a href=(.*?)><script>document.write'#ʹ��������ʽ��Ѱ��ÿ�����ŵĲ�ͬ��ַ
    result = re.findall(reg,html)#�ҵ����������ŵĵ�ַ
    for html_num in result:#����ÿһ�����ŵ�ַ
        news = urllib2.Request(html1+data+'/'+html_num)
        news.add_header("User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 UBrowser/6.1.2107.204 Safari/537.36")
        content = urllib2.urlopen(news).read()
        artical = r'<!--enpcontent-->(.*?)<!--/enpcontent-->.*?<INPUT type=checkbox value=0 name=titlecheckbox sourceid="<Source>SourcePh</Source>" style="display:none">'#��������ʽ����Ѱ���������ݣ������ų������ظ��ĵڶ�������
        title_f = r'<title>(.*?)</title>'
        time_f = r'<div id="paperdatediv">(.*?)</div>'
        title = re.findall(title_f,content)#title�ɹ�����ȡ����������Ŀ������Ҫע����list��ʽ���޷������ַ������в���
        time  = re.findall(time_f,content,re.S)#title�ɹ�����ȡ����������Ŀ������Ҫע����list��ʽ���޷������ַ������в���
        mainbody = re.findall(artical,content,re.S)#mainbody�ɹ�����ȡ�����������ݣ�����Ҫע����list��ʽ���޷������ַ������в���
        #mainbody.decode('utf-8')
        #mainbody.encode('utf-8')
        #mainbody.encode('utf-8')
        print (mainbody)