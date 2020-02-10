#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "yolov2.h"

int main( int argc, char *argv[])
{
	unsigned int WEIGHT_BASE = 0x10000000;
    unsigned int BETA_BASE = 0x1C25F000;
    unsigned int MEM_BASE  = 0x1C26A000;// 49770*1024*4 = 203857920 = C26A000

    printf("YOLOv2 TEST Begin\n");
    char **names = get_labels("coco.names");
	int x;
	for(x=0;x<80;x++)//80 classe labels
	{
		printf("[%d]%s\n",x,names[x]);
	}
    image **alphabet = load_alphabet();
    network *net = load_network("yolov2.cfg", "yolov2.weights", 0);
    set_batch_network(net, 1);

////////////////////load img resize img begin
    char buff[256];
    char *input_imgfn = buff;
    if(argc==1)
    {
    	strncpy(input_imgfn, "person.jpg", 256);
    }
    else
    {
    	strncpy(input_imgfn, argv[1], 256);
    }
	printf("Input img:%s\n",input_imgfn);
	image im = load_image_stb(input_imgfn, 3);//3 channel img
	printf("img w=%d,h=%d,c=%d\n",im.w,im.h,im.c);
	image sized = letterbox_image(im, 416, 416);
	save_image_png(sized, "sized");// convert to yolov3 net input size 416x416x3
////////////////////load img resize img end

//	time_t first, second;
	double time;
	layer l = net->layers[net->n-1];
        float *X = sized.data;

        int i;
        float nms=.2;
        float thresh = .6;
        float hier_thresh = .6;
        int nboxes = 0;

        detection *dets;

        for (i = 0; i < 1; i++) {
            time = what_time_is_it_now();
            yolov2_hls_ps(net, X,WEIGHT_BASE,BETA_BASE,MEM_BASE);
            printf("Predicted in %f seconds.!\n",what_time_is_it_now()-time);

            dets = get_network_boxes(net, im.w, im.h, thresh, hier_thresh, 0, 1, &nboxes);
            printf("%d\n", nboxes);
            if (nms) do_nms_sort(dets, nboxes, l.classes, nms);
        }

    printf("DONE3!");
    draw_detections(im, dets, nboxes, thresh, names, alphabet, l.classes);

    free_detections(dets, nboxes);
	
///////////////////write predictions img
	save_image_png(im, "predictions");// output

	free_image(im);
    free_image(sized);

	printf("YOLOv2 TEST1 End\n");

    return 0;
}
