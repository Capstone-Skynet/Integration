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
GROUND_STATION_URL = 'http://192.168.0.107:80'

CPP_SERVER_HOST = 'localhost'
CPP_SERVER_PORT = 8000

SIGNAL_SEND_DATA = 'PY_IMG_DATA'
SIGNAL_SEND_RESULT = 'PY_ML_RESULT'

IMAGE_LENGTH = 640 * 480 * 3

def get_socketio_client():
    client = socketio.Client()

    while not client.connected:
        try:
            client.connect(GROUND_STATION_URL)
        except socketio.exceptions.ConnectionError as e:
            print(f'Connection to {GROUND_STATION_URL} refused.')
            print(e)
            sys.exit(1)
    return client
    
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


def sendImg(client, receiveBytes):
    print("sending image")
    
    # formatting array
    data = np.frombuffer(receiveBytes, dtype=np.uint8)
    data.shape= (480,640,3)
    
    image = Image.fromarray(data, 'RGB')
    
    imgByteArr = io.BytesIO()
    image.save(imgByteArr, format='JPEG')

    imgByteArr = imgByteArr.getvalue()
    
    frame_data = str(base64.b64encode(imgByteArr))
    
    client.emit(SIGNAL_SEND_DATA, frame_data[2:len(frame_data) - 1])

def sendResult(client, result):
    print("sending result")
    client.emit(SIGNAL_SEND_RESULT, result)

if __name__ == '__main__':
    try:
        client = get_socketio_client()
        tcp_socket = get_tcp_socket()

        while(True):
            cmd = receive_str(tcp_socket)

            if cmd == 'IMAGE':
                frameData = receive_image(tcp_socket)
                print(len(frameData))
                if frameData != None:
                    sendImg(client, bytes(frameData))
                
            elif cmd == 'RESULT':
                result = receive_str(tcp_socket)
                sendResult(client, result)


    except KeyboardInterrupt:
        print('Program Terminated.')