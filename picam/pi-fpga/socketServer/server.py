import socket

if __name__ == '__main__':
    port = 8080
    s = socket.socket()
    host = socket.gethostname()
    s.bind((host, port))
    s.listen(5)

    imageFolder = "./images/"
    imageFormat = ".png"
    imageIndex = 0

    print('Server listening....')
    conn, addr = s.accept()
    print('Got connection from', addr)

    while True:
        filename = imageFolder + str(imageIndex) + imageFormat
        imageIndex += 1

        imagebytes = conn.recv(307200)
        myfile = open(filename, 'wb')
        myfile.write(imagebytes)
        myfile.close()

    print('Done receiving')
    conn.close()