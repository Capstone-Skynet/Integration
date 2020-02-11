import socket
import time
import picamera
import numpy as np

host = "192.168.0.102"
port = 8080

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#camera = picamera.Picamera()
#camera.resolution = (640,480)
#time.sleep(2)
#img = np.empty((480, 640, 3), dtype=np.uint8)

buffer_size = 100
n = 1

with picamera.PiCamera() as camera:
    camera.resolution = (640,480)
    time.sleep(2)
    img = np.empty((480, 640, 3), dtype=np.uint8)
    
    s.bind((host, port))
    s.listen(5)

    print("waiting for connections")

    (conn, addr) = s.accept()

    print("connected")

    while True:
        print("waiting for new request")
        
        data = conn.recv(buffer_size)
        while(len(data) == 0):
            data = conn.recv(buffer_size)
        
        camera.capture(img, "rgb")
        bytearray = img.tobytes()
        conn.send(bytearray)
        print("image sent")
        
        print("waiting for results")
        
        data = conn.recv(buffer_size)
        while(len(data) == 0):
            data = conn.recv(buffer_size)
        
        print("results received\n")
        
        print(str(n) + " images sent\n")
        n += 1