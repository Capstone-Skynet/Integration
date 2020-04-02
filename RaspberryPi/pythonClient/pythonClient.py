import base64
import numpy as np
import socketio
import sys
import time
import picamera
from PIL import Image
import io
import socket

# SETUP: Socket IO connections

# MODIFY THIS
GROUND_STATION_URL = 'http://192.168.137.2:80'

CPP_SERVER_HOST = 'localhost'
CPP_SERVER_PORT = 8000

SIGNAL_SEND_DATA = 'PY_IMG_DATA'
SIGNAL_SEND_RESULT = 'PY_ML_RESULT'

SIGNAL_RECEIVE_THRESHOLD = 'gs_threshold'
SIGNAL_RECEIVE_MODE = 'gs_mode'

IMAGE_LENGTH = 640 * 480 * 3

socketio_client = socketio.Client()

THRESHOLD = 0.5
PEDESTRIAN_ONLY = False

def socketio_client_start():

    while not socketio_client.connected:
        try:
            socketio_client.connect(GROUND_STATION_URL)
        except socketio.exceptions.ConnectionError as e:
            print(f'Connection to {GROUND_STATION_URL} refused.')
            print(e)
            sys.exit(1)
    
def get_tcp_socket():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((CPP_SERVER_HOST,CPP_SERVER_PORT))
    return s

def receive_str(socket):
    byteArr = socket.recv(100)
    if len(byteArr) > 0:
        return byteArr.decode()

def receive_image(socket):
    data = bytearray()
    while len(data) < IMAGE_LENGTH:
        packet = socket.recv(IMAGE_LENGTH - len(data))
        if not packet:
            return None
        data.extend(packet)
    return data


def sendImg(receiveBytes):
    
    print("sending image")
    
    # formatting array
    data = np.frombuffer(receiveBytes, dtype=np.uint8)
    data.shape= (480,640,3)
    
    image = Image.fromarray(data, 'RGB')
    
    imgByteArr = io.BytesIO()
    image.save(imgByteArr, format='JPEG')

    imgByteArr = imgByteArr.getvalue()
    
    frame_data = str(base64.b64encode(imgByteArr))
    
    socketio_client.emit(SIGNAL_SEND_DATA, frame_data[2:len(frame_data) - 1])

def sendResult(result):
    print("sending result")
    socketio_client.emit(SIGNAL_SEND_RESULT, result)

@socketio_client.on(SIGNAL_RECEIVE_THRESHOLD)
def on_message(data):
    global THRESHOLD
    THRESHOLD = float(data)
    print('new threshold received: ' + data)
    
@socketio_client.on(SIGNAL_RECEIVE_MODE)
def on_message(data):
    global PEDESTRIAN_ONLY
    if data[0] == 'Pedestrian Only':
        PEDESTRIAN_ONLY = True
        print('pedestrian only')
    elif data[0] == 'All Classes':
        PEDESTRIAN_ONLY = False
        print('all enabled')
    else:
        print(data)

def send_parameters(socket):
    global THRESHOLD, PEDESTRIAN_ONLY
    
    if (PEDESTRIAN_ONLY):
        parameters = "{0:5.4f};{1}".format(THRESHOLD, "T")
    else:
        parameters = "{0:5.4f};{1}".format(THRESHOLD, "F")
    print(parameters)
    socket.send(parameters.encode())


if __name__ == '__main__':
    socketio_client_start()
    tcp_socket = get_tcp_socket()
        
    
    while(True):
        try:
            print("LOOP")
            cmd = receive_str(tcp_socket)
            print("CMDRECV")

            if cmd == 'IMAGE':
                frameData = receive_image(tcp_socket)
            
                print(len(frameData))
            
                if frameData != None:
                    sendImg(bytes(frameData))
            
            elif cmd == 'RESULT':
                result = receive_str(tcp_socket)
            
                sendResult(result)
            
                send_parameters(tcp_socket)

        except KeyboardInterrupt:
            print('Program Terminated.')
            sys.exit(0)
            
        except UnicodeDecodeError:
            print('Unicode decode error.')
