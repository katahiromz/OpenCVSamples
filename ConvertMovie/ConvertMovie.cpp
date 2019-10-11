#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        puts("Usage: ConvertMovie input.avi output.avi");
        return 0;
    }

    const char *input = argv[1];
    const char *output = argv[2];

    cv::VideoCapture cap(input);
    if (!cap.isOpened())
    {
        puts("cv::VideoCapture");
        return -1;
    }

    int width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(cv::CAP_PROP_FPS);

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

    cv::Mat frame;
    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;

        writer << frame;
    }

    return 0;
}
