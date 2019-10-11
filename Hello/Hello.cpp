#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        puts("Usage: hello hello.png");
        return -1;
    }

    cv::Mat img;
    img = cv::imread(argv[1]);
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    cv::waitKey(0);
    return 0;
}
