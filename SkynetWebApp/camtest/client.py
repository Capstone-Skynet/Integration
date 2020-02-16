import argparse
import base64
import cv2
import numpy as np
import socketio
import sys
import time
import threading

# SETUP: Argument Setup
arg_parser = argparse.ArgumentParser(description="Camera test program to connect to Skynet Webapp via socket.io")
arg_parser.add_argument('--reconnect', help='Keep trying to reconnect to socket server even when connection refuses', action='store_true')
arg_parser.add_argument('--reconnect-freq', help='The frequency to attempt reconnecting to socket IO server', default=3)
args = arg_parser.parse_args()

# SETUP: Socket IO connections
CONNECTION_URL = 'http://localhost:80'

def setup_socket():
    client = socketio.Client()

    while client.connected:
        try:
            client.connect(CONNECTION_URL)
        except socketio.exceptions.ConnectionError as e:
            if args.reconnect:
                print(f'Connection to {CONNECTION_URL} refused; attempting to reconnect (Control+C to quit).')
                time.sleep(1 / args.reconnect_freq)
            else:
                print(f'Connection to {CONNECTION_URL} refused.')
                print(e)
                sys.exit(1)

    return client

# @client.event
# def connect():
#     print('Connected to ', CONNECTION_URL)

# @client.event
# def connect_error():
#     print('Error, could not connect to ', CONNECTION_URL)

# @client.event
# def disconnect():
#     print('Disconnected from ', CONNECTION_URL)

# print ('my sid is ', client.sid)
# client.emit('pytest', 'pytest sent')

def main():
    client = setup_socket()

    cap = cv2.VideoCapture(0)

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Display the resulting frame
        cv2.imshow('frame',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Program Terminated.')

# while 1:
#     filepath = img_prefix + str(data) + png
#     with open(filepath, 'rb') as imageFile:
#         image_data = base64.b64encode(imageFile.read())
#         img_string = str(image_data)
#         length = len(img_string)
#         client.emit('py_img_receive', img_string[2:length-1] )
#     time.sleep(0.4)
#     #print('Image sent') 
#     if (data == 10):
#         data = 1 
#     else:
#         data += 1