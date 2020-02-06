import socket
import time
import numpy as np

print(socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = socket.gethostbyname("10.2.0.15")

print(host)

port = 8080