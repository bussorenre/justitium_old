# this is test 

require "socket"

hostname = "127.0.0.1"

if ARGV[0]
    hostname = ARGV[0]
end

# 127.0.0.1:9999 ポートへ接続
TCPSocket.open(hostname, 9999) do |s|
    s.write("./test/test.c");
    while line = s.gets
        puts line.chop
    end
end
