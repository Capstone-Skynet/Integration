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
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 300);
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 200);

    while True:
        # Capture frame-by-frame
        _, frame = cap.read()

        # Display the resulting frame
        _, buffer = cv2.imencode('.jpg', frame)
        frame_data = str(base64.b64encode(buffer))
        client.emit('py_img_receive', frame_data[2:len(frame_data) - 1])

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Program Terminated.')