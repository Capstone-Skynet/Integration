import argparse
import base64
import cv2
import numpy as np
import socketio
import sys
import time
import threading
import random

# SETUP: Argument Setup
arg_parser = argparse.ArgumentParser(description="Camera test program to connect to Skynet Webapp via socket.io")
arg_parser.add_argument('--reconnect', help='Keep trying to reconnect to socket server even when connection refuses', action='store_true')
arg_parser.add_argument('--reconnect-freq', help='The frequency to attempt reconnecting to socket IO server', default=3)
arg_parser.add_argument('--cam-res-scale', help='Magnitude of the scale of the camera input images (default 0.1)', default=0.1)
arg_parser.add_argument('--frame-delay', help='Number of seconds to delay betweek each frame capture (unlimited/default -1)', default=-1)
args = arg_parser.parse_args()

# SETUP: Socket IO connections
CONNECTION_URL = 'http://localhost:80'
SIGNAL_SEND_DATA = 'PY_IMG_DATA'

# SETUP: Camera
CAMERA_RESOLUTION_WIDTH = 1280
CAMERA_RESOLUTION_HEIGHT = 1024
CAMERA_RESOLUTION_SCALE = float(args.cam_res_scale)

args.frame_delay = float(args.frame_delay)
CAMERA_FRAME_DELAY = args.frame_delay if args.frame_delay > 0 else 0

def setup_socket():
    client = socketio.Client()

    while not client.connected:
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

def main():
    client = setup_socket()
    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, int(CAMERA_RESOLUTION_SCALE * CAMERA_RESOLUTION_WIDTH))
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, int(CAMERA_RESOLUTION_SCALE * CAMERA_RESOLUTION_HEIGHT))
    print(f'Setting camera resolution to {cap.get(cv2.CAP_PROP_FRAME_WIDTH)}, {cap.get(cv2.CAP_PROP_FRAME_HEIGHT)}')

    client.emit('PY_ML_CLEAR', 0)

    i = 0
    while True:
        # Capture frame-by-frame
        _, frame = cap.read()

        # Display the resulting frame
        _, buffer = cv2.imencode('.jpg', frame)
        frame_data = str(base64.b64encode(buffer))
        client.emit(SIGNAL_SEND_DATA, frame_data[2:len(frame_data) - 1])
        
        # Test BBox
        i += 1
        client.emit('PY_ML_RESULT', f'Type: person, Width: 50, Height: 60, X: {random.randint(0, 600)}, Y: {random.randint(0, 400)}')
        if (i % 30 == 0):
            client.emit('PY_ML_CLEAR', 0);

        if CAMERA_FRAME_DELAY > 0:
            time.sleep(CAMERA_FRAME_DELAY)

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Program Terminated.')