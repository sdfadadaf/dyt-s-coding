#include"ImgProdCons.h"
#include"iostream"
#include<opencv2/opencv.hpp>
#include<thread>

using namespace std;
using namespace cv;

namespace rm
{
void ImgProdCons::init()
{
    //prevent usb port from being blocked
    init_signals();

    //Initialize camera
    _videoCapturePtr->open(0,2);
    _videoCapturePtr->setVideoFormat(1280, 720, true);
    _videoCapturePtr->setExposureTime(100);
    _videoCapturePtr->setFPS(60);
    _videoCapturePtr->startStream();
    _videoCapturePtr->info();
}

void ImgProdCons::sense()
{

}

void ImgProdCons::consume()
{
    auto t1 = chrono::high_resolution_clock::now();

    Frame frame;
    for(;;)
    {
        if(!_buffer.getLatest(frame)) continue;

        //for(int i = 0; i < 100; i++)
        //{
            resize(frame.img,frame.img,Size(),0.5,0.5);
            imshow("capture", frame.img);
            if(waitKey(1) == 'q')
            {
                return;
            }
        //}

        auto t2 = chrono::high_resolution_clock::now();
        cout << "process: " << (static_cast<chrono::duration<double, std::milli>>(t2 - t1)).count() << " ms" << endl;
        t1 = t2;
    }
}
}



