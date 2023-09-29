import struct
import socket
import sys
import os
import time

from binascii import hexlify

# a long 8 bytes, a long 8 bytes and an int 4 bytes, total should be 24 bytes
header_format = 'qqi'

# udp server that runs on port 12345
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 12345)
sock.bind(server_address)

# while true, send the current time to the client
while True:
    # wait for the hello message from the client
    data, address = sock.recvfrom(4096)

    print("received", len(data), hexlify(data))

    # create a message header
    tim = int(time.time())
    message = b""
    header = struct.pack(header_format, 667, tim, 24)
    header = b"BTC\x00" + header + message
    print("send struct", hex(0), hex(667), hex(tim), len(header), hexlify(header), header)

    # send the header to the client
    sock.sendto(header, address)
    
    data, address = sock.recvfrom(4096)
    print("received", len(data), hexlify(data))
    # move message

    message = struct.pack('qq', 20, 20)
    header = struct.pack(header_format, 667, tim, 40)
    header = b"BTC\x01" + header + message
    print("send struct", hex(1), hex(667), hex(tim), len(header), hexlify(header), header)

    # send the header to the client
    sock.sendto(header, address)