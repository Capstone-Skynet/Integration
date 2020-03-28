// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <raspicam/raspicam.h>
#include "imagesupport.h"
#define PORT 8080
#define PYTHON_CLIENT_PORT 8000

#define ENABLE_ML 0

using namespace std;

int main(int argc, char const *argv[])
{
  //GSC - START
  int gs_sock = 0, gs_client;
  struct sockaddr_in gs_addr;

  int opt = 1;

  const char *image_transfer = "IMAGE";
  const char *result_transfer = "RESULT";

  if ((gs_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  if (setsockopt(gs_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  gs_addr.sin_family = AF_INET;
  gs_addr.sin_addr.s_addr = INADDR_ANY;
  gs_addr.sin_port = htons(PYTHON_CLIENT_PORT);

  if (bind(gs_sock, (struct sockaddr *)&gs_addr,
           sizeof(gs_addr)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(gs_sock, 3) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  int addrlen1 = sizeof(gs_addr);
  if ((gs_client = accept(gs_sock, (struct sockaddr *)&gs_addr,
                          (socklen_t *)&addrlen1)) < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  //GSC - END

  int server_fd, new_socket, valread;
  struct sockaddr_in address;

  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  char *hello = "Hello from server";
  char buff[256];
  char *input_imgfn = buff;

  if (ENABLE_ML)
  {
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
      perror("socket failed");
      exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
      perror("listen");
      exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }
  }

  raspicam::RaspiCam Camera;

  //Setup Camera
  Camera.setFormat(raspicam::RASPICAM_FORMAT_RGB);
  Camera.setCaptureSize(640, 480);

  printf("Opening Camera...\n");
  if (!Camera.open())
  {
    printf("Error opening camera!");
    return -1;
  }

  printf("Sleeping to stabilize camera\n");
  usleep(3000000);

  //Begin Transactional Communications
  //  while(1) {

  //strncpy(input_imgfn,"input_image.jpg", 256);

  unsigned char *data = (unsigned char *)malloc(640 * 480 * 3);

  image im = make_image(640, 480, 3);

  while (1)
  {

    // GSC - START
    send(gs_client, image_transfer, strlen(image_transfer), 0);
    // GSC - END

    Camera.grab();
    Camera.retrieve(data, raspicam::RASPICAM_FORMAT_IGNORE);

    // GSC - START
    send(gs_client, data, 640 * 480 * 3, 0);
    // GSC - END

    for (int k = 0; k < 3; ++k)
    {
      for (int j = 0; j < 480; ++j)
      {
        for (int i = 0; i < 640; ++i)
        {
          int dst_index = i + 640 * j + 640 * 480 * k;
          int src_index = k + 3 * i + 3 * 640 * j;
          im.data[dst_index] = (float)data[src_index] / 255.;
        }
      }
    }

    //image im = load_image_stb(input_imgfn,3);
    image sized = letterbox_image(im, 416, 416);

    if (ENABLE_ML)
    {
      save_image_png(sized, "test.png");
      send(new_socket, sized.data, (sized.h * sized.w * sized.c) * 4, 0);
    }

    // GSC - START
    send(gs_client, result_transfer, strlen(result_transfer), 0);
    // GSC - END

    //Read Results:

    int bytesRead = 0;

    //Initially read 4 bytes (Depending on the value recieved here, we might
    //have to read more if we've classified something!

	
    if (ENABLE_ML)
    {
      int numClassified;

      int results;
      results = read(new_socket, &numClassified, 4);
      
      int *detection = (int *)malloc(48 * sizeof(char));

      printf("Num Results: %d\n", numClassified);

      for (int i = 0; i < numClassified; i++)
      {
        bytesRead = 0;
        while (bytesRead < 48)
        {
          results = read(new_socket, ((char *)detection) + bytesRead, 48 - bytesRead);

          if (results < 0)
          {
            printf("ERROR!\n");
            exit(-1);
          }

          bytesRead += results;
        }
        printf("Type: %.*s, Width: %d, Height: %d, X: %d, Y: %d\n", 32, ((char *)detection), detection[8], detection[9], detection[10], detection[11]);
      }
    }
    
    // GSC - START
  char result[100];
  char *type = "person";
  int height = rand() % 100;
  int width = rand() % 100;
  int x = rand() % 100;
  int y = rand() % 100;
 
  sprintf(result, "Type: %.*s, Width: %d, Height: %d, X: %d, Y: %d", 32, type, height, width, x, y);
  send(gs_client, result, strlen(result), 0);
  usleep(100);
  // GSC - END
  }
  return 0;
}
