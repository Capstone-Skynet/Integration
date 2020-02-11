import socketio
import base64
import time

client = socketio.Client()
img_prefix = "Images/"
png = ".jpg"
data = 1;

connection = 'http://localhost:80'

client.connect(connection)
print ('my sid is ', client.sid)
client.emit('pytest', 'pytest sent')

@client.event
def connect():
    print('Connected to ', connection)

@client.event
def connect_error():
    print('Error, could not connect to ', connection)

@client.event
def disconnect():
    print('Disconnected from ', connection)

while 1:
    filepath = img_prefix + str(data) + png
    with open(filepath, 'rb') as imageFile:
        image_data = base64.b64encode(imageFile.read())
        img_string = str(image_data)
        length = len(img_string)
        client.emit('py_img_receive', img_string[2:length-1] )
    time.sleep(0.4)
    #print('Image sent') 
    if (data == 10):
        data = 1
    else:
        data += 1
    


