#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        puts("Usage: BuildMovie img_%03d.jpg output.avi fps");
        return 0;
    }

    const char *input = argv[1];
    const char *output = argv[2];
    double fps = atof(argv[3]);

    char image_name[300];
    int i = 0;
    cv::Mat frame;

    sprintf(image_name, input, i);
    frame = cv::imread(image_name);
    if (!frame.data)
    {
        puts("unable to load frame");
        return -1;
    }

    int width = frame.cols;
    int height = frame.rows;

    //int fourcc = -1; // choose
    int fourcc = 0x7634706d; // mp4v
    //int fourcc = 0x3447504D; // MPEG-4
    //int fourcc = 0x34363248; // H.264/MPEG-4 AVC
    //int fourcc = 0x34363248; // H.264 H264

    cv::VideoWriter writer(output, fourcc, fps, cv::Size(width, height));
    if (!writer.isOpened())
    {
        puts("cv::VideoWriter");
        return -2;
    }

    for (;;)
    {
        sprintf(image_name, input, i);
        frame = cv::imread(image_name);
        if (!frame.data)
        {
            break;
        }

        writer << frame;
        ++i;
    }

    return 0;
}
