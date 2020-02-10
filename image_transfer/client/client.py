import socket
from PIL import Image
import numpy as np

port = 8001
host = 'localhost'

s = socket.socket()
s.connect((host,port))

imageFolder = "./images/"
imageFormat = ".png"
imageIndex = 0

n = 0

while True:

    imagebytes = s.recv(307200*4)
    
    if imagebytes:
        print(n)
        n += 1
        print ("received data")
        print (len(imagebytes))
        if (len(imagebytes) == 307200*3):
            print("saving image")       
            data = np.frombuffer(imagebytes, dtype=np.uint8)
            data.shape = (480,640,3)
         
            filename = imageFolder + str(imageIndex) + imageFormat
            imageIndex += 1
            
            if (imageIndex == 20):
                imageIndex = 0
        
            img = Image.fromarray(data, 'RGB')
            img.show()
            img.save(filename)