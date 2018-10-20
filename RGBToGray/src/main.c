/**
 * Author:KingTreeS
 * 2018-10-19
 * 将真彩图像转为灰度图
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * BMP文件格式：
 * bmp文件头(bmp file header)：提供文件的格式、大小等信息
 * 位图信息头(bitmap information)：提供图像数据的尺寸、位平面数、压缩方式、颜色索引等信息
 * 调色板(color palette)：可选，如使用索引来表示图像，调色板就是索引与其对应的颜色的映射表
 * 位图数据(bitmap data)
 *
 * 分别定义对应的结构体
 */

/*
 * bmp文件头
 */
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER{
    unsigned char bfType[2];        //文件格式
    unsigned long bfSize;           //文件大小
    unsigned short bfReserved1;     //保留
    unsigned short bfReserved2;
    unsigned long bfOffBits;        //数据在文件中的偏移量
} fileHeader;
#pragma pack()

/*
 * 位图信息头
 */
#pragma pack(1)
typedef struct tagBITMAPINFOHEADER{
    unsigned long biSize;           //结构体大小
    long biWidth;                   //文件宽度
    long biHeight;                  //文件高度
    unsigned short biPlanes;        //平面数
    unsigned short biBitCount;      //颜色位数
    unsigned long biCompression;    //压缩类型
    unsigned long biSizeImage;      //数据区大小
    long biXPixPerMeter;
    long biYPixPerMeter;
    unsigned long biClrUsed;        //颜色索引表数量
    unsigned long biClrImportant;   //重要颜色数量
} fileInfo;
#pragma pack()

/*
 * 调色板结构
 */
#pragma pack(1)
typedef struct tagRGBQUAD{
    unsigned char rgbBlue;          //蓝色分量亮度
    unsigned char rgbGreen;         //绿色分量亮度
    unsigned char rgbRed;           //红色分量亮度
    unsigned char rgbReserved;
} rgbq;
#pragma pack()

int main() {
    // 读取和写入文件信息
    unsigned char bmpRGBPath[] = "/Volumes/D/CLionProject/CPractice/RGBToGray/img/lena.bmp";
    unsigned char bmpGrayPath[] = "/Volumes/D/CLionProject/CPractice/RGBToGray/img/gray.bmp";
    FILE *fpBMP, *fpGray;
    // 存储RGB图像像素点
    unsigned char rgbImgData[3];
    // 存储转换后的灰度图像像素点
    unsigned int grayImgData;
    // 定义的关于BMP文件的结构体声明
    fileHeader *fh;
    fileInfo *fi;
    rgbq *fq;


    if ((fpBMP = fopen(bmpRGBPath, "rb")) == NULL){
        puts("打开彩色图像失败");
        exit(0);
    } else{
        if ((fpGray = fopen(bmpGrayPath, "wb")) == NULL){
            puts("打开灰色图像失败");
            exit(0);
        } else{

            printf("%d\n", sizeof(fileHeader));
            printf("%d\n", sizeof(fileInfo));
            printf("%d\n", sizeof(rgbq));
            fh = (fileHeader *)malloc(sizeof(fileHeader));
            fi = (fileInfo *)malloc(sizeof(fileInfo));

            // 读取BMP文件头和位图信息头结构
            fread(fh, sizeof(fileHeader), 1, fpBMP);
            fread(fi, sizeof(fileInfo), 1, fpBMP);
            // 定义新宽度
            long newBiWidth = ((fi->biWidth + 3) / 4) * 4;
            // 修改BMP文件头和位图信息头
            fi->biBitCount = 8;
            // fi->biSizeImage = newBiWidth * fi->biHeight;
            fi->biSizeImage = fi->biHeight * newBiWidth;

            fh->bfOffBits = sizeof(fileHeader) + sizeof(fileInfo) + 256 * sizeof(rgbq);
            fh->bfSize = fh->bfOffBits + fi->biSizeImage;

            // 创建调色板
            fq = (rgbq *)malloc(256 * sizeof(rgbq));
            for (int i = 0; i < 256; i++) {
                fq[i].rgbBlue = fq[i].rgbGreen = fq[i].rgbRed = i;
            }

            // 将BMP文件头、位图信息头和调色板写入灰度图像文件
            fwrite(fh, sizeof(fileHeader), 1, fpGray);
            fwrite(fi, sizeof(fileInfo), 1, fpGray);
            fwrite(fq, sizeof(rgbq), 256, fpGray);

            // 读取RGB图像像素并转化为灰度值

            /*rgbImgData = (char *)malloc(fi->biSizeImage);
            grayImgData = (char *)malloc(fi->biSizeImage);*/
            for (int i = 0; i < fi->biHeight; i++) {
                for (int j = 0; j < fi->biWidth; j++) {
                    for (int k = 0; k < 3; k++) {
                        fread(&rgbImgData[k], 1, 1, fpBMP);
                    }
                    //将每一个像素都按公式y=B*0.299+G*0.587+R*0.114进行转化
                    grayImgData = (int)((float)rgbImgData[0] * 0.299 + (float)rgbImgData[1] * 0.587 + (float)rgbImgData[2] * 0.114);
                    // 将灰度图像信息写入文件
                    fwrite(&grayImgData, 1, 1, fpGray);
                }
            }
            free(fh);
            free(fi);
            free(fq);
            fclose(fpGray);
            fclose(fpBMP);
            puts("已经成功的将彩色图片转为灰度图！");
            return 0;
        }
    }
}