#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(void)
{
    int cam_id = 0;
    cv::VideoCapture cap(cam_id);

    if (!cap.isOpened())
    {
        puts("cv::VideoCapture");
        return -1;
    }

    int width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = 30;

    //int fourcc = -1; // choose
    int fourcc = 0x7634706d; // mp4v
    //int fourcc = 0x3447504D; // MPEG-4
    //int fourcc = 0x34363248; // H.264/MPEG-4 AVC
    //int fourcc = 0x34363248; // H.264 H264

    //cv::VideoWriter writer("movie.mp4", fourcc, fps, cv::Size(width, height));
    cv::VideoWriter writer("img_%02d.jpg", 0, 0, cv::Size(width, height));

    cv::namedWindow("CameraCapture2", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);

    cv::Mat frame;
    for (;;)
    {
        cap >> frame;
        cv::imshow("CameraCapture2", frame);
        writer << frame;

        if (cv::waitKey(1000 / 30) > 0)
            break;
    }

    return 0;
}
