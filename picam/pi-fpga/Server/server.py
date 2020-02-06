import socket
import time
from picamera import PiCamera
import numpy as np

host = "localhost"
port = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind((host, port))
s.listen(5)

print("waiting for connections")

(conn, addr) = s.accept()

print("connected")

camera = Picamera()
camera.resolution = (640,480)
time.sleep(2)
img = np.empty((480, 640, 3), dtype=np.uint8)

while True:
    camera.capture(img, "rgb")
    bytearray = img.tobytes()
    conn.send(bytearray)
    time.sleep(1)