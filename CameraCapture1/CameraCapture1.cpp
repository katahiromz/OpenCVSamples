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
    double fps = cap.get(cv::CAP_PROP_FPS);

    cv::namedWindow("CameraCapture1", cv::WINDOW_AUTOSIZE | cv::WINDOW_FREERATIO);

    cv::Mat frame;
    for (;;)
    {
        cap >> frame;
        cv::imshow("CameraCapture1", frame);

        if (cv::waitKey(1) > 0)
            break;
    }

    return 0;
}
