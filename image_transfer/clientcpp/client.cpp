// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define PORT 8080
#define HOST "192.168.0.101"

#define IMAGE_SIZE 480 * 640 * 3

int main(int argc, char const *argv[])
{
    int sock = 0, valread = 0;
    struct sockaddr_in serv_addr;

    char buffer[IMAGE_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //struct timeval tv;
    //gettimeofday(&tv, NULL);
    //unsigned long start = 1000000 * tv.tv_sec + tv.tv_usec;

    while (true)
    {
        int n = 0;
        valread = 0;
        while (valread < IMAGE_SIZE)
        {
            n++;
            valread += read(sock, buffer + valread, IMAGE_SIZE - valread);
        }

        printf("Image received, bytes: %d\n", valread);
        printf("%d loops\n", n);
    }

    // gettimeofday(&tv, NULL);
    // unsigned long end = 1000000 * tv.tv_sec + tv.tv_usec;

    // printf("%ld\n", start);
    // printf("%ld\n", end);

    return 0;
}
//send(sock, hello, strlen(hello), 0);
