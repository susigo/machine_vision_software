#include "mainwin.h"
#include "ui_mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    this->setWindowTitle("常见算子演示软件");
    ui->ori_label->setText("请选择一张图片！");
    ui->debug_win->insertPlainText("########\n软件启动!!!\n请先选择一张图片！\n否则算子功能无法选择\n########\n");
    this->set_conections();


}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::set_conections()
{
    connect(ui->S1_brigthness,&QSlider::valueChanged,[=](){
        this->show_message(11);
    });

    connect(ui->S2_contrace,&QSlider::valueChanged,[=](){
        this->show_message(12);
    });
    connect(ui->P_1,&QPushButton::clicked,[=](){
        this->show_message(1);
        buttonReset(1);
        ori_img = readImg(0);
    });
    connect(ui->P_2,&QPushButton::clicked,[=](){
        this->show_message(2);
        buttonReset(2);
        ori_img = readImg(1);
    });
    connect(ui->P_3,&QPushButton::clicked,[=](){
        this->show_message(3);
        buttonReset(3);
        ori_img = readImg(2);
    });
    connect(ui->P_4,&QPushButton::clicked,[=](){
        this->show_message(4);
        buttonReset(4);
        ori_img = readImg(3);
    });
    connect(ui->P_5,&QPushButton::clicked,[=](){
        this->show_message(5);
        buttonReset(5);
        ori_img = readImg(4);
    });
    connect(ui->P_6,&QPushButton::clicked,[=](){
        this->show_message(6);
        buttonReset(6);
        ori_img = readImg(5);
    });
    connect(ui->P_7,&QPushButton::clicked,[=](){
        this->show_message(7);
        buttonReset(7);
        ori_img = readImg(6);
    });
    connect(ui->P_8,&QPushButton::clicked,[=](){
        this->show_message(8);
        buttonReset(8);
        ori_img = readImg(7);
    });

    connect(ui->S1_brigthness,&QSlider::valueChanged,[=](){
        this->show_message(11);
    });
    if(start_flag!=0){
    connect(ui->S2_contrace,&QSlider::valueChanged,[=](){
        this->show_message(12);
    });
    connect(ui->B1_Sobel,&QPushButton::clicked,[=](){
        buttonReset(11);
        this->show_message(22);
        Mat abs,abs1,abs2;
        Sobel(ori_img, abs, CV_16S, 1, 0, 3, 1, 1, cv::BORDER_DEFAULT);
        convertScaleAbs(abs, abs1);
        imshow("Sobel", abs1);
    });
    connect(ui->B2_Kirsch,&QPushButton::clicked,[=](){
        buttonReset(12);
        this->show_message(23);
    });
    connect(ui->B3_Laplacian,&QPushButton::clicked,[=](){
        buttonReset(13);
        this->show_message(23);
        Mat gray, dst;
        Laplacian(ori_img, gray,CV_16S,3);
        convertScaleAbs(gray, gray);
        threshold(gray, gray, 0, 255, cv::THRESH_OTSU | cv::THRESH_BINARY);
        imshow("Laplacian", gray);
    });
    connect(ui->B4_SUSAN,&QPushButton::clicked,[=](){
        buttonReset(14);
        this->show_message(25);
        std::string sur_img_path_ = pics_path[cur_img_index].toStdString();
        char temp_cahr[20];
        strcpy(temp_cahr,sur_img_path_.c_str());

        src_img  = cvLoadImage(temp_cahr);
        AllocateImage(src_img);
        cvSplit( src_img, src_gray1, src_gray2, src_gray3, 0);
        //cvNamedWindow("my picture",CV_WINDOW_AUTOSIZE);
        //cvNamedWindow("my dst",CV_WINDOW_AUTOSIZE);

        SUSAN_check(src_gray1, dst_img, RADIUS) ;
        cvShowImage("Susan",src_img);

    });
    connect(ui->B5_Harris,&QPushButton::clicked,[=](){
        buttonReset(15);
        this->show_message(26);
    });
    connect(ui->B0_Canny,&QPushButton::clicked,[=](){
        buttonReset(16);
        this->show_message(21);
        cv::Canny( ori_img, ori_img, 150, 100,3 );
        imshow("Canny边缘检测", ori_img);
    });
    }
    connect(ui->debug_win,&QTextBrowser::textChanged,[=](){
        ui->debug_win->moveCursor(QTextCursor::End);
    });
}

void MainWin::show_message(int mes_index)
{
    QString pic_message[50] = {"x","选择图片一！","选择图片二！","选择图片三！","选择图片四！",
                                   "选择图片五！","选择图片六！","选择图片七！","选择图片八！"
                               };
    QString fun_message[50] = {"x","Canny ！\n","Sobel\n","Kirsch！\n","Laplacian！\n",
                                   "SUSAN！\n","Harris！\n","reset！\n","save！\n"
                               };
    QString slider_message[6] = {"x","亮度值变至：","对比度变至："};
    if(mes_index<10){
        if(start_flag==0){
            start_flag = 1;
            this->set_conections();
            ui->debug_win->insertPlainText("*********\n图片已选择\n算子功能已激活\n********\n");
        }
        ui->statusBar->showMessage(pic_message[mes_index],600);
        ui->debug_win->insertPlainText(pic_message[mes_index]);
        ui->debug_win->insertPlainText("\n");
        qDebug()<<pic_message[mes_index];
    }
    else if(mes_index>10 && mes_index <=20){
        if(mes_index==11){
            slider_message[4]=QString::number(ui->S1_brigthness->value())+="%";
            ui->S1_value->setText(slider_message[4]);
            slider_message[4] = "";
            qDebug()<<slider_message[mes_index-10]<<ui->S1_brigthness->value()<<"%";
        }
        else {

        slider_message[5]=QString::number(ui->S2_contrace->value())+="%";
        ui->S2_value->setText(slider_message[5]);
        //slider_messagcur_pixmape[5] = "";
        qDebug()<<slider_message[mes_index-10]<<ui->S2_contrace->value()<<"%";
        }
    }
    else if (mes_index>20) {
        ui->statusBar->showMessage(fun_message[mes_index-20],600);
        ui->debug_win->insertPlainText(fun_message[mes_index-20]);
        //ui->debug_win->insertPlainText("\n");
        qDebug()<<pic_message[mes_index-20];
    }
}

void MainWin::buttonReset(int set_index)
{
    QString selected_green = "QPushButton{background-color: rgb(115, 210, 22)}";
    QString unselected_wihte= "QPushButton{background-color: rgb(243, 243, 243)}";
    QString selected_red= "QPushButton{background-color: rgb(239, 41, 41);}";
    if(set_index<10){
        if(set_index==1){ui->P_1->setStyleSheet(selected_green);}
        else {ui->P_1->setStyleSheet(unselected_wihte);}
        if(set_index==2){ui->P_2->setStyleSheet(selected_green);}
        else {ui->P_2->setStyleSheet(unselected_wihte);}
        if(set_index==3){ui->P_3->setStyleSheet(selected_green);}
        else {ui->P_3->setStyleSheet(unselected_wihte);}
        if(set_index==4){ui->P_4->setStyleSheet(selected_green);}
        else {ui->P_4->setStyleSheet(unselected_wihte);}
        if(set_index==5){ui->P_5->setStyleSheet(selected_green);}
        else {ui->P_5->setStyleSheet(unselected_wihte);}
        if(set_index==6){ui->P_6->setStyleSheet(selected_green);}
        else {ui->P_6->setStyleSheet(unselected_wihte);}
        if(set_index==7){ui->P_7->setStyleSheet(selected_green);}
        else {ui->P_7->setStyleSheet(unselected_wihte);}
        if(set_index==8){ui->P_8->setStyleSheet(selected_green);}
        else {ui->P_8->setStyleSheet(unselected_wihte);}
    }
    else if (set_index>10 && set_index<20) {
        if(set_index==11){ui->B1_Sobel->setStyleSheet(selected_red);}
        else {ui->B1_Sobel->setStyleSheet(unselected_wihte);}
        if(set_index==12){ui->B2_Kirsch->setStyleSheet(selected_red);}
        else {ui->B2_Kirsch->setStyleSheet(unselected_wihte);}
        if(set_index==13){ui->B3_Laplacian->setStyleSheet(selected_red);}
        else {ui->B3_Laplacian->setStyleSheet(unselected_wihte);}
        if(set_index==14){ui->B4_SUSAN->setStyleSheet(selected_red);}
        else {ui->B4_SUSAN->setStyleSheet(unselected_wihte);}
        if(set_index==15){ui->B5_Harris->setStyleSheet(selected_red);}
        else {ui->B5_Harris->setStyleSheet(unselected_wihte);}
        if(set_index==16){ui->B0_Canny->setStyleSheet(selected_red);}
        else {ui->B0_Canny->setStyleSheet(unselected_wihte);}
    }
}

Mat MainWin::readImg(int temp_falg){
    Mat ori_img = imread(pics_path[temp_falg].toStdString(),cv::IMREAD_GRAYSCALE);
    QPixmap pixmap(pics_path[temp_falg]);
    pixmap.scaled(QSize(ui->ori_label->width(),ui->ori_label->height()),Qt::IgnoreAspectRatio);
    ui->ori_label->setPixmap(pixmap);
    ui->ori_label->show();
    cur_img_index = temp_falg;
    return ori_img;
}


void MainWin::AllocateImage(IplImage* I)   //给图像分配大小
{
    CvSize sz   = cvGetSize(I);

    dst_img   = cvCreateImage( sz, IPL_DEPTH_8U, 1);
    cvSetZero(dst_img);
    src_gray1 = cvCreateImage( sz, IPL_DEPTH_8U, 1);    //原图的三个通道
    src_gray2 = cvCreateImage( sz, IPL_DEPTH_8U, 1);
    src_gray3 = cvCreateImage( sz, IPL_DEPTH_8U, 1);
    NumR0     = cvCreateMat(sz.height,sz.width,CV_16SC1);
    Rr0       = cvCreateMat(sz.height,sz.width,CV_16SC1);
    cvSetZero(NumR0);
    cvSetZero(Rr0);

}

void MainWin::DeallocateImage()
{
    cvReleaseImage(&src_img);
    cvReleaseImage(&dst_img);
    cvReleaseImage(&src_gray1);
    cvReleaseImage(&src_gray2);
    cvReleaseImage(&src_gray3);
    cvReleaseMat(&NumR0);

}

void MainWin::SUSAN_check(IplImage* I, IplImage* dst, int r)                    //SUSAN角点检测函数
{
    int i,j,x,y;
    int num,MaxNum=0,g,CValue;
    int R0Value,temp;

    for( i=r; i<(I->height-r); i++ )               //计算n(r0),模板内图像USAN的像元数量
    {
        for( j=r; j<(I->width-r); j++ )
        {

            R0Value=cvGetReal2D(I,i,j);
            num=0;
            for( y=i-r; (y-i<=r)&&(y-i>=-r);y++ )
            {
                for( x=j-r;(x-j<=r)&&(x-j>=-r);x++ )
                {
                    if(((x-j)*(x-j)+(y-i)*(y-i))<=r*r&&(x!=j||y!=i))                //中心点圆形邻域内
                    {
                        temp=cvGetReal2D(I,y,x);
                        if( abs(R0Value-temp) <= THRESHOLD  )
                        num++;
                    }
                }
            }
            cvSetReal2D(NumR0,i,j,num);
            if(num>MaxNum)  MaxNum = num;
        }
    }
    g=3*MaxNum/4;
    for( i=r; i<(I->height-r); i++ )               //计算R(r0),USAN特征图像
    {
        for( j=r; j<(I->width-r); j++ )
        {
            temp = cvGetReal2D(NumR0,i,j);
            if( temp<g )
                cvSetReal2D(Rr0,i,j,(g-temp));
        }
    }

    for( i=r; i<(I->height-r); i++ )             //非极大抑制
    {
        for( j=r; j<(I->width-r); j++ )
        {
            CValue = cvGetReal2D(Rr0,i,j);       //USAN特征图像中心点值
            num=0;
            if(CValue!=0)
            {
            for( y=i-r; (y-i<=r)&&(y-i>=-r);y++ )         //查看周围半径r圆形邻域是否为极大值
            {
                for( x=j-r;(x-j<=r)&&(x-j>=-r);x++ )
                {
                    if(((x-j)*(x-j)+(y-i)*(y-i))<=r*r&&(x!=j||y!=i))                //中心点圆形邻域内
                    {
                    temp = cvGetReal2D(Rr0,y,x);
                    if(j==27&&i==129)
                    {
                        MaxNum=MaxNum;
                    }
                    if(CValue>temp)
                        num++;
                    }
                }
            }
            if(num==MaxNum)
            {
            cvCircle(src_img,cvPoint(j,i),3,cvScalar(0,0,255),1,8,0);
            //cvSet2D(src_img,i,j,cvScalar(0,0,255));
            *(dst->imageData+i*dst->widthStep+j) =255;
            }
            }

        }
    }

}
