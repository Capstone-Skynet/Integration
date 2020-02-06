import socket

port = 1234
host = '192.168.137.199'

s = socket.socket()
s.connect((host,port))

imageFolder = "./images/"
imageFormat = ".png"
imageIndex = 0

#print('Server listening....')
#conn, addr = s.accept()
#print('Got connection from', addr)

while True:
    filename = imageFolder + str(imageIndex) + imageFormat
    imageIndex += 1

    imagebytes = s.recv(307200)
    myfile = open(filename, 'wb')
    myfile.write(imagebytes)
    myfile.close()

print('Done receiving')
conn.close()