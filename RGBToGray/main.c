/**
 * Author:KingTreeS
 * 2018-10-19
 * �����ͼ��תΪ�Ҷ�ͼ
 */

#include <stdio.h>
#include <stdlib.h>

 /*
  * BMP�ļ���ʽ��
  * bmp�ļ�ͷ(bmp file header)���ṩ�ļ��ĸ�ʽ����С����Ϣ
  * λͼ��Ϣͷ(bitmap information)���ṩͼ�����ݵĳߴ硢λƽ������ѹ����ʽ����ɫ��������Ϣ
  * ��ɫ��(color palette)����ѡ����ʹ����������ʾͼ�񣬵�ɫ��������������Ӧ����ɫ��ӳ���
  * λͼ����(bitmap data)
  *
  * �ֱ����Ӧ�Ľṹ��
  */

  /*
   * bmp�ļ�ͷ
   */
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER {
	unsigned char bfType[2];        //�ļ���ʽ
	unsigned long bfSize;           //�ļ���С
	unsigned short bfReserved1;     //����
	unsigned short bfReserved2;
	unsigned long bfOffBits;        //�������ļ��е�ƫ����
} fileHeader;
#pragma pack()

/*
 * λͼ��Ϣͷ
 */
#pragma pack(1)
typedef struct tagBITMAPINFOHEADER {
	unsigned long biSize;           //�ṹ���С
	long biWidth;                   //�ļ����
	long biHeight;                  //�ļ��߶�
	unsigned short biPlanes;        //ƽ����
	unsigned short biBitCount;      //��ɫλ��
	unsigned long biCompression;    //ѹ������
	unsigned long biSizeImage;      //��������С
	long biXPixPerMeter;
	long biYPixPerMeter;
	unsigned long biClrUsed;        //��ɫ����������
	unsigned long biClrImportant;   //��Ҫ��ɫ����
} fileInfo;
#pragma pack()

/*
 * ��ɫ��ṹ
 */
#pragma pack(1)
typedef struct tagRGBQUAD {
	unsigned char rgbBlue;          //��ɫ��������
	unsigned char rgbGreen;         //��ɫ��������
	unsigned char rgbRed;           //��ɫ��������
	unsigned char rgbReserved;
} rgbq;
#pragma pack()

int main() {
	// ��ȡ��д���ļ���Ϣ
	// ����A��ͼƬ��1733*1083
	unsigned char bmpRGBPath[] = "D:/VSProject/RGBToGray/DLAM.bmp";
	unsigned char bmpGrayPath[] = "D:/VSProject/RGBToGray/grayDLAM.bmp";
	/*
	// lenaͼƬ��200*200
	unsigned char bmpRGBPath[] = "D:/VSProject/RGBToGray/lena.bmp";
	unsigned char bmpGrayPath[] = "D:/VSProject/RGBToGray/gray.bmp";
	*/
	FILE *fpBMP, *fpGray;
	// �洢RGBͼ�����ص�
	unsigned char rgbImgData[3];
	// �洢ת����ĻҶ�ͼ�����ص�
	unsigned int grayImgData;
	// ���ڴ洢��ɫͼ��ÿ��ɨ���ж�����ֽ���
	unsigned char rgbAnthor;
	// ����Ĺ���BMP�ļ��Ľṹ������
	fileHeader *fh;
	fileInfo *fi;
	rgbq *fq;


	if ((fpBMP = fopen(bmpRGBPath, "rb")) == NULL) {
		puts("�򿪲�ɫͼ��ʧ��");
		exit(0);
	}
	else {
		if ((fpGray = fopen(bmpGrayPath, "wb")) == NULL) {
			puts("�򿪻�ɫͼ��ʧ��");
			exit(0);
		}
		else {
			fh = (fileHeader *)malloc(sizeof(fileHeader));
			fi = (fileInfo *)malloc(sizeof(fileInfo));

			// ��ȡBMP�ļ�ͷ��λͼ��Ϣͷ�ṹ
			fread(fh, sizeof(fileHeader), 1, fpBMP);
			fread(fi, sizeof(fileInfo), 1, fpBMP);
			// long oldBiWidth = fi->biWidth;
			// ����ԭ���Ĳ�ɫͼ��ÿ��ɨ������ռ���ֽ���
			long oldBiWidth = (fi->biWidth * fi->biBitCount / 8 + 3) / 4 * 4;
			
			// �޸�BMP�ļ�ͷ
			fi->biBitCount = 8;
			// ����ת����ĻҶ�ͼ��ÿ��ɨ������ռ�ֽ���
			long newBiWidth = (fi->biWidth * fi->biBitCount / 8 + 3) / 4 * 4;
			fi->biSizeImage = newBiWidth * fi->biHeight;
			// �޸�ͼƬ���ؿ�ȣ��ޱ�Ҫ��
			// fi->biWidth = newBiWidth;

			// �޸�λͼ��Ϣͷ
			fh->bfOffBits = sizeof(fileHeader) + sizeof(fileInfo) + 256 * sizeof(rgbq);
			fh->bfSize = fh->bfOffBits + fi->biSizeImage;

			// ������ɫ��
			fq = (rgbq *)malloc(256 * sizeof(rgbq));
			for (int i = 0; i < 256; i++) {
				fq[i].rgbBlue = fq[i].rgbGreen = fq[i].rgbRed = i;
			}

			// ��BMP�ļ�ͷ��λͼ��Ϣͷ�͵�ɫ��д��Ҷ�ͼ���ļ�
			fwrite(fh, sizeof(fileHeader), 1, fpGray);
			fwrite(fi, sizeof(fileInfo), 1, fpGray);
			fwrite(fq, sizeof(rgbq), 256, fpGray);

			// ��ȡRGBͼ�����ز�ת��Ϊ�Ҷ�ֵ
			for (int i = 0; i < fi->biHeight; i++) {
				for (int j = 0; j < newBiWidth; j++) {
					if (j < fi->biWidth)
					{
						for (int k = 0; k < 3; k++) {
							fread(&rgbImgData[k], 1, 1, fpBMP);
						}
						//��ÿһ�����ض�����ʽy=B*0.299+G*0.587+R*0.114����ת��
						grayImgData = (int)((float)rgbImgData[0] * 0.299 + (float)rgbImgData[1] * 0.587 + (float)rgbImgData[2] * 0.114);
					}
					else {
						grayImgData = 0;
					}
					// ���Ҷ�ͼ����Ϣд���ļ�
					fwrite(&grayImgData, 1, 1, fpGray);
				}
				// ע�⣬��ͼ��ɨ������ռ�ֽ������ǵ����� ���*3 ��Ҫ���д���
				for (int i = (fi->biWidth * 3); i < oldBiWidth; i++) {
					fread(&rgbAnthor, 1, 1, fpBMP);
				}
			}
			free(fh);
			free(fi);
			free(fq);
			fclose(fpGray);
			fclose(fpBMP);
			puts("�Ѿ��ɹ��Ľ���ɫͼƬתΪ�Ҷ�ͼ��");
			return 0;
		}
	}
}