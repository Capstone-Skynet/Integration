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
#include <fcntl.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "imagesupport.h"
#include <cstdio>
#include <ctime>
#define PORT 8080
#define PYTHON_CLIENT_PORT 8000

#define NUM_VIDEOFRAMES 320

#define USE_TAPEDELAY 0
#define LATENCY_OFFSET 30

float charArrToFloat(const char *fc)
{
  std::string fs(fc);
  float f = std::stof(fs);
  return f;
}

#define ENABLE_ML 1

using namespace std;
using namespace cv;

unsigned char * videoData;
int currFrame = 0;

float ml_threshold = 0.25;

/* Grabs the next frame from the (pre-loaded) video */
void updateFrame(VideoCapture capture, unsigned char *data)
{
  currFrame = (currFrame+1)%NUM_VIDEOFRAMES;
  printf("Current Frame: %d\n", currFrame);

  memcpy(data, videoData + 640*480*3*sizeof(uint8_t)*currFrame, 640*480*sizeof(uint8_t)*3);
}

/* Loads the video into memory (converting to the same format as webcam footage) */
void loadVideo(VideoCapture capture)
{
  videoData = (unsigned char *) malloc(640*480*3*sizeof(uint8_t)*NUM_VIDEOFRAMES);

  Mat frame;
  
  capture.set(1, 0);
 
  for (int i = 0; i < NUM_VIDEOFRAMES; i++) {
    capture >> frame;

    cv::cvtColor(frame, frame, CV_BGR2RGB);

    memcpy(videoData + frame.cols*frame.rows*sizeof(uint8_t)*3*i, frame.ptr(0), frame.cols*frame.rows*sizeof(uint8_t)*3);
  }
}

int main(int argc, char const *argv[])
{
 
  // Initialize socket communication to Python helper 
  int gs_sock = 0, gs_client;
  struct sockaddr_in gs_addr;

  int opt = 1;

  const char image_transfer[100] = "IMAGE";
  const char result_transfer[100] = "RESULT";

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

  // Initialize socket to PLB
  int server_fd, new_socket, valread;
  struct sockaddr_in address;

  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  char buff[256];
  char *input_imgfn = buff;

  printf("Opening ML socket...\n");

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


  //Setup Camera
  raspicam::RaspiCam Camera;

  Camera.setFormat(raspicam::RASPICAM_FORMAT_BGR);
  Camera.setExposure(raspicam::RASPICAM_EXPOSURE_AUTO);
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

  unsigned char *data = (unsigned char *)malloc(640 * 480 * 3 * LATENCY_OFFSET);
  unsigned char *ml_data = (unsigned char *)malloc(640 * 480 * 3);

  int currOffset = 0;

  image im = make_image(640, 480, 3);

  char *parameters = (char *)malloc(10);

  /* Setup video acquisition, if desired */
  int useVideo = 0;
  char videoName[100];
  VideoCapture capture;
  if (argc > 1) {
    useVideo = 1;
    VideoCapture capture(videoName);    
    loadVideo(capture);
  } 

  while (1)
  {
    if(!useVideo) {
      Camera.grab();
      Camera.retrieve(ml_data, raspicam::RASPICAM_FORMAT_IGNORE);
    }
    else {
      updateFrame(capture, ml_data);
    }

    for (int k = 0; k < 3; ++k)
    {
      for (int j = 0; j < 480; ++j)
      {
        for (int i = 0; i < 640; ++i)
        {
          int dst_index = i + 640 * j + 640 * 480 * k;
          int src_index = k + 3 * i + 3 * 640 * j;
          im.data[dst_index] = (float)ml_data[src_index] / 255.;
        }
      }
    }

    image sized = letterbox_image(im, 416, 416);

    if (ENABLE_ML)
    {
      send(new_socket, &ml_threshold, 4, 0);
      send(new_socket, sized.data, (sized.h * sized.w * sized.c) * 4, 0);
    }

    int bytesRead = 0;
    
    char result[100];

    //Initially read 4 bytes (Depending on the value recieved here, we might
    //have to read more if we've classified something!

    if (ENABLE_ML)
    {
      int numClassified = 0;

      int results = 0;

      do { /* While we're waiting for results... */
        send(gs_client, image_transfer, 100, 0);
        send(gs_client, data + (currOffset*640*480*3), 640 * 480 * 3, 0); 

        if(!useVideo) {
          Camera.grab();
          Camera.retrieve(data + (currOffset*640*480*3), raspicam::RASPICAM_FORMAT_IGNORE);
        }
        else {
          updateFrame(capture, data + (currOffset*640*480*3));
          usleep(50000);
        }
        
        if(USE_TAPEDELAY) {
          currOffset = (currOffset + 1) % LATENCY_OFFSET;
        }
      
        results = recv(new_socket, &numClassified, 4, MSG_DONTWAIT);
      } while (results <= 0);

      // We've gotten results!
      int *detection = (int *)malloc(48 * sizeof(char));
      
      printf("Num Results: %d\n", numClassified);
      
      send(gs_client, result_transfer, 100, 0);
      sprintf(result, "%d", numClassified);  
      send(gs_client, result, 100, 0);

      /* For each classified result */
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
        sprintf(result, "Type: %.*s, Width: %d, Height: %d, X: %d, Y: %d", 32, ((char *)detection), detection[8], detection[9], detection[10], detection[11]);
        send(gs_client, result, 100, 0);
      }
    }
    else /* Dummy data for testing */
    {
      // Manually add some delay to simulation ml delay
      usleep(500000);
      send(gs_client, result_transfer, 100, 0);
      char *type = "person";
      int height = rand() % 100;
      int width = rand() % 100;
      int x = rand() % 100;
      int y = rand() % 100;
      sprintf(result, "Type: %.*s, Width: %d, Height: %d, X: %d, Y: %d", 32, type, height, width, x, y);
      send(gs_client, result, 100, 0);
    }

    /* Read paramaters to pass onto PLB */
    int parameter_bytes = read(gs_client, parameters, 10);
    if (parameter_bytes == 8)
    {
      printf("Threshold: %f\n", charArrToFloat(parameters));
      ml_threshold = charArrToFloat(parameters);
      if (parameters[7] == 'T')
      {
        //printf("Pedestrian only\n");
      }
      else if (parameters[7] == 'F')
      {
        //printf("All classes\n");
      }
    }
    // GSC - END
  }
  return 0;
}
