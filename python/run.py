# coding:utf-8
import json
import MySQLdb
from BaseHTTPServer import HTTPServer,BaseHTTPRequestHandler
def insertuser(user,password):
    conn= MySQLdb.connect(
        host='localhost',
        port = 3306,
        user='root',
        passwd='2015huster',
        db ='test',
        )
    b=1
    cur = conn.cursor()
    a=cur.execute("select * from user where userid=%s and password=%s",(user,password))
    ##if a == 0:
    ##a=cur.execute("select * from user where userid = %s and true",user)
    ##    print "wrong\n\n\n"
    ##    print b
    ##    print "\n\n\nhahahahah\n\n\n"
    ##print a
    if a == 0 and b == 0:
        a=1
        print "\n\n\n    "+user+password
        cur.execute("insert into user values(%s,%s)",(user,password))
    elif a==0 and b > 0:
        a=0
        print "wrong password \n\n\n\n\n\n"
    cur.close()
    conn.commit()
    conn.close()
    return a
def setinfor(userid,aimuserid,pinci,time,content,contentType):
    conn= MySQLdb.connect(
        host='localhost',
        port = 3306,
        user='root',
        passwd='2015huster',
        db ='test',
        )
    cur = conn.cursor()
    a=cur.execute("insert into setinfor values(%s,%s,%s,%s,%s,%s,%s)",(userid,aimuserid,pinci,time,content,contentType,"false"))
    cur.close()
    conn.commit()
    conn.close()
    return b

def search(userid,aimuserid,time):
    conn= MySQLdb.connect(
        host='localhost',
        port = 3306,
        user='root',
        passwd='2015huster',
        db ='test',
        )
    cur = conn.cursor()
    b=()
    a=cur.execute("select * from myinfor where aimuserid=%s and userid=%s and time=%s",(aimuserid,userid,time))
    if a>0:
        b=cur.fetchone()
    cur.close()
    conn.commit()
    conn.close()
    return b
def findset(aimuser):
    conn= MySQLdb.connect(
        host='localhost',
        port = 3306,
        user='root',
        passwd='2015huster',
        db ='test',
        )
    cur = conn.cursor()
    b=()
    a=cur.execute("select * from setinfor where aimuserid=%s and state=%s",(aimuser,"false"))
    if a>0:
        b=cur.fetchone()
        cur.execute("update setinfor set state='true' where aimuserid=%s and state=%s",(aimuser,"true"))
    cur.close()
    conn.commit()
    conn.close()
    return b
class RequestHandler(BaseHTTPRequestHandler):
  def _writeheaders(self):
    ### print self.path
    self.send_response(200);
    self.send_header('Content-type','text/html');
    self.end_headers()
  def do_Head(self):
    self._writeheaders()
  def do_GET(self):
    getinput = self.path
    self._writeheaders()
    ### getinput = '/type=call&userid=15927187851&password=14564'
    getinfor={"type":"type","userid":"type","password":"type","aimuserid":"type","time":"type","pinci":"type","content":"type","contentType":"type",}
    temp = getinput.strip('/')
    temp = temp.strip('?')
    inputList=temp.split('&')
    input ={}
    for x in inputList:
        x0 =x.split('=')
        getinfor[x0[0]]=x0[1]
    if getinfor['type'] == 'call':
        input = {"type" : "set","userid" :"x","aimuserid" : "x","pinci": "x","time":"x","content" :"x","contentType" : "x"}
        aimuserid = getinfor["aimuserid"]
        b=findset(aimuserid)
        if len(b) > 4:
            input["userid"]=b[0]
            input["aimuserid"]=b[1]
            input["pinci"]=b[2]
            input["time"]=b[3]
            input["content"]=b[4]
            input["contentType"]=b[5]
        else:
            input["type"]="unset"
    elif getinfor['type'] == 'login':
        userid = getinfor["userid"]
        password = getinfor["password"]
        state = insertuser(userid,password)
        input = {"type" : "login","state":"false"}
        print state
        print "state\n\n\n\n\n\n\n\n\n"
        if state >= 1:
            input["state"]="true"
    elif getinfor['type'] == 'search':
        aimuserid = getinfor["aimuserid"]
        userid=getinfor["userid"]
        time=getinfor["time"]
        bbb=search(userid,aimuserid,time)
        input = {"type" : "search",	"userid" :"xx","aimuserid" :"xx","xuetang":"xx","xueya":"xx","xinlv":"xx","time":"xx"}
        if len(bbb)>0:
            input["userid"]=bbb[0]
            input["aimuserid"]=bbb[1]
            input["xuetang"]=bbb[2]
            input["xueya"]=bbb[3]
            input["xinlv"]=bbb[4]
            input["time"]=bbb[5]
    elif getinfor['type'] == 'set':
        aimuserid = getinfor["aimuserid"]
        userid=getinfor["userid"]
        time=getinfor["time"]
        pinci = getinfor["pinci"]
        content=getinfor["content"]
        contentType=getinfor["contentType"]
        input={}
        setinfor(userid,aimuserid,pinci,time,content,contentType)
    else:
        input = {"type":"wrong"}
    result = json.dumps(input)
    self.wfile.write(result)
  def do_POST(self):
    self._writeheaders()
    length = self.headers.getheader('content-length');
    nbytes = int(length)
    data = self.rfile.read(nbytes)
    self.wfile.write("stupid")
addr = ('',8080)
server = HTTPServer(addr,RequestHandler)
server.serve_forever()
