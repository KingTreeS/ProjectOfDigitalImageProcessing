#include <iostream>
#include <opencv/cv.hpp>

using namespace cv;

int main()
{
    //读入图像
    Mat srcImage=imread("/Volumes/D/CLionProject/ImageZoom/image/lena.jpg");
    Mat temImage,dstImage1,dstImage2;
    temImage=srcImage;

    //尺寸调整
    resize(temImage,dstImage1,Size(temImage.cols/2,temImage.rows/2),0,0,INTER_LINEAR);
    resize(temImage,dstImage2,Size(temImage.cols*2,temImage.rows*2),0,0,INTER_LINEAR);

    imwrite("/Volumes/D/CLionProject/ImageZoom/image/amplification.jpg",dstImage1);
    imwrite("/Volumes/D/CLionProject/ImageZoom/image/narrow.jpg",dstImage2);

    waitKey();
    return 0;

}