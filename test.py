import  sys, string
import httplib
import time

domain = "localhost"
emoncmspath = "emoncms"
apikey = "bcd4ee9fce950386b355705373f71ddf"
nodeid = 1

httpServ = httplib.HTTPConnection(domain)

while 1:
    httpServ.connect()
    csv="100,150,200"
    print(csv)
    time.sleep(10)
    # Send to emoncms
    httpServ.request("GET", "/"+emoncmspath+"/input/post.json?apikey="+apikey+"&node="+str(nodeid)+"&csv="+csv)
    print("GET", "/"+emoncmspath+"/input/post.json?apikey="+apikey+"&node="+str(nodeid)+"&csv="+csv)
    response = httpServ.getresponse()
    print response.read()
    time.sleep(10)
    httpServ.close()
