#ifndef MAINWIN_H
#define MAINWIN_H

#include<QMainWindow>
#include<QString>
#include<QDebug>
#include<QSlider>
#include<QImage>
#include<QPixmap>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv/cv.h>
//#include "opencv2/nonfree/nonfree.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/legacy/legacy.hpp"
#include<iostream>
#include "opencv2/features2d.hpp"
#include <math.h>
#define THRESHOLD  20
#define RADIUS  3
using cv::Mat;
using cv::imread;
using cv::imshow;
namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();
    void set_conections();
    void show_message(int mes_index);
    void buttonReset(int set_index);
    //void  MySusan(Mat imageGray, std::vector<cv::Point2f>& corners);
    void SUSAN_check(IplImage* I, IplImage* dst, int r);
    void AllocateImage(IplImage* I);
    void DeallocateImage();
    Mat readImg(int temp_flag);

    Mat ori_img;
    int start_flag = 0;//如果启动标志为0则说明没有选择图片
    typedef  unsigned long uint32;
    typedef  unsigned int  uint16;
    typedef  unsigned char uint8;
    IplImage *src_gray1, *src_gray2, *src_gray3;
    IplImage* src_img, *dst_img;
    CvMat  *NumR0,*Rr0;
    int MaxNumR0=0;
    int cur_img_index;
    QString pics_path[9] = {"./imgs/pic_01.jpg","./imgs/pic_02.jpg","./imgs/pic_03.jpg","./imgs/pic_04.jpg"
                            ,"./imgs/pic_05.jpg","./imgs/pic_06.png","./imgs/pic_07.jpg","./imgs/pic_08.jpg"};

private:
    Ui::MainWin *ui;
};

#endif // MAINWIN_H
