import socket
import time
from picamera import PiCamera
import numpy as np

print(socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostname()
print(host)

port = 8080

s.connect((host, port))

camera = Picamera()
camera.resolution = (640,480)
time.sleep(2)
img = np.empty((480, 640, 3), dtype=np.uint8)

while True:
    camera.capture(img, "rgb")
    bytearray = img.tobytes()
    s.send(bytearray)
    time.sleep(1)