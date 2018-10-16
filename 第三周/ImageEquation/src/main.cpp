#include <iostream>
#include <opencv/cv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat image = imread("/Volumes/D/CLionProject/ImageEquation/image/lena.jpg", 1);
    if (image.empty())
    {
        std::cout << "打开图片失败,请检查" << std::endl;
        return -1;
    }

    Mat imageRGB[3];
    split(image, imageRGB);
    for (int i = 0; i < 3; i++)
    {
        equalizeHist(imageRGB[i], imageRGB[i]);
    }
    merge(imageRGB, 3, image);
    //imshow("直方图均衡化图像增强效果", image);
    imwrite("/Volumes/D/CLionProject/ImageEquation/image/lenaEquation.jpg",image);
    waitKey();
    return 0;
}

