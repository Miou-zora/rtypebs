import queue
import struct
import socket
import sys
import os
import time
import threading

from binascii import hexlify

# a long 8 bytes, a long 8 bytes and an int 4 bytes, total should be 24 bytes
header_format = 'qqi'

# udp server that runs on port 12345
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 12345)
sock.bind(server_address)

players = {}
refreshes_per_second = 16

def server_thread():
    refresh_rate = 1.0 / float(refreshes_per_second)
    updates = 0
    start_update = time.time_ns()
    while True:
        start = time.time_ns()
        process_stuff()
        end = time.time_ns()
        elapsed = (end - start) / 1000000000.0
        if elapsed < refresh_rate:
            time.sleep(refresh_rate - elapsed)
        updates += 1
        if updates == refreshes_per_second:
            print(refreshes_per_second, "updates in", (time.time_ns() - start_update), "ns")
            updates = 0
            start_update = time.time_ns()

movement_speed = 120

def process_stuff():
    for address in players:
        player_moved = False
        while not players[address]["queue"].empty():
            action, data = players[address]["queue"].get()
            if action == "move" and not player_moved:
                # Calculate the new player position based on user input and elapsed time
                input_x, input_y = data
                elapsed_time = 1.0 / refreshes_per_second
                new_x = players[address]["position"][0] + input_x * movement_speed * elapsed_time
                new_y = players[address]["position"][1] + input_y * movement_speed * elapsed_time
                print("new_x", new_x, "new_y", new_y)
                # Update the player's position
                players[address]["position"] = [new_x, new_y]
                
                player_moved = True
    
    for address in players:
        message = struct.pack('ff', *players[address]["position"])
        header = struct.pack(header_format, 667, tim, 32)
        header = b"BTC\x01" + header + message
        #print("send struct", hex(1), hex(667), hex(tim), len(header), hexlify(header), header)

        # send the header to the client
        sock.sendto(header, address)

t = threading.Thread(target=server_thread)
t.daemon = True
t.start()


# while true, send the current time to the client
while True:
    # wait for the hello message from the client
    data, address = sock.recvfrom(4096)
    print("message from", address, len(data), hexlify(data))
    if data.startswith(b"BTC\x00") and address not in players:
        # create a message header
        print("welcome client", address, len(data), hexlify(data))
        tim = int(time.time())
        message = b""
        header = struct.pack(header_format, 667, tim, 32)
        header = b"BTC\x00" + header + message
        print("send struct", hex(0), hex(667), hex(tim), len(header), hexlify(header), header)

        # send the header to the client
        sock.sendto(header, address)

        players[address] = {"position": [20, 20], "queue": queue.Queue()}

    else:
        # move message
        tim = int(time.time())
        received_data = struct.unpack("ii", data[24:])
        print("received_data", received_data)
        if address in players:
            players[address]["queue"].put(("move", received_data))
        else:
            print("unknown client", address, len(data), hexlify(data))
        
