# SkynetWebApp

A js server-client webapp for the base station.

## Requirements

This server runs on Node.js. Please ensure Node.js version 13 is installed. Note that newer versions of Node.js should work but is not tested.

## Packages

The `server.js` requires express and socket.io.

    npm install express
    npm install --save socket.io

## Camera Test

This is a set up to test the functionality of the web-app without hooking up to a working payload (Zedboard and Raspberry Pi). It uses a Python script to capture images from the webcam and sends it to the server IP. The script first ensures that it has a connection to the Node.js server before turning on the camera.

The related files are located under `camtest/`.


### Requirements

The Python script runs in Python 3.6+. We need *cv2* library for image capture and socket.io client library for communication. 

We highly recommend running Python-related
code inside a virtual enviornment to avoid tampering with system Python modules. In this document, I shall
use *Pipenv* but *Virtualenv* also works.

#### Virutal Environemnt

Download `pipenv` using your `pip` package manager (run `pip3` if your system has both Python 2 and Python 3)

```
pip install --user pipenv
```

There is a *Pipfile* located under *camtest/*. This file is a manifest of the packages and their required versions to make the program work. From here, we install all the needed packages inside our virutal environment:

```
pipenv install
```

### Running Camera Test

First start the server as instructed above:

```
node server
```

Then run the Python script through *pipenv* in a separate shell.

```
pipenv run python client.py
```

Open the browser and go to address `localhost:80`.
