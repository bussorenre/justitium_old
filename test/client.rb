# this is test 

require "socket"

# 127.0.0.1:9999 ポートへ接続
TCPSocket.open("127.0.0.1", 9999) do |s|
    s.write("./test/test.c");
    while line = s.gets
        puts line.chop
    end
end