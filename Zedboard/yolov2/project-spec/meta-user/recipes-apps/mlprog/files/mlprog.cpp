#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "yolov2.h"
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#define PORT 8080 

void fetchImage(int socket, image img)
{
    int bytesRead = 0;
    int result;

    int imageLength = 2076672;

    bytesRead = 0;
    while (bytesRead < imageLength) {
        //printf("%d bytes fetched!\n", bytesRead);
        result = read(socket, ((char *) img.data) + bytesRead, imageLength - bytesRead);

        if(result < 1) {
            printf("ERROR %d!\n", errno);
            exit(-1);
        }

        bytesRead += result;
    }
}
    

int main( int argc, char *argv[])
{
   
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "192.168.1.11", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    image sized = make_empty_image(416,416,3);
    sized.data = (float *)calloc(416*416*3, sizeof(float));

    unsigned int WEIGHT_BASE = 0x10000000;
    unsigned int BETA_BASE = 0x1C25F000;
    unsigned int MEM_BASE  = 0x1C26A000;// 49770*1024*4 = 203857920 = C26A000

    printf("YOLOv2 TEST Begin\n");
    char **names = get_labels("coco.names");
	int x;
	for(x=0;x<80;x++)//80 class labels
	{
		printf("[%d]%s\n",x,names[x]);
	}
    image **alphabet = load_alphabet();
    network *net = load_network("yolov2.cfg", "yolov2.weights", 0);
    set_batch_network(net, 1);

    int firstRun = 1;

    while(1) {
        fetchImage(sock, sized);

        double time;
        layer l = net->layers[net->n-1];
        float *X = sized.data;

        int i;
        float nms=.2;
        float thresh = .2;
        float hier_thresh = .2;
        int nboxes = 0;

        detection *dets;

        time = what_time_is_it_now();
        yolov2_hls_ps(firstRun, net, X,WEIGHT_BASE,BETA_BASE,MEM_BASE);
        firstRun = 0;

        dets = get_network_boxes(net, sized.w, sized.h, thresh, hier_thresh, 0, 1, &nboxes);
        if (nms) do_nms_sort(dets, nboxes, l.classes, nms);

        int sizeofSendData = 4 + 48*nboxes;
        int * sendData = (int *) calloc(sizeofSendData, sizeof(char));

        extract_detections(sendData, sized, dets, nboxes, thresh, names, l.classes);

        send(sock, sendData, 4 + 48*sendData[0], 0);

        free_detections(dets, nboxes);
        free(sendData);
    }

    free_image(sized);
    return 0;
}
