# this is test 

require "socket"

# 127.0.0.1:9999 ポートへ接続
sock = TCPSocket.open("127.0.0.1:9999")

sock.write("test.c");

sock.close

