#include "ImgProdCons.h"
#include<unistd.h>
#include <signal.h>

#include<opencv2/opencv.hpp>
#include<chrono>
#include<iostream>
#include<thread>
#include<memory>

using namespace std;
using namespace cv;

namespace rm
{

FrameBuffer::FrameBuffer(size_t size):
    _frames(size),
    _mutexs(size),
    _tailIdx(0),
    _headIdx(0),
    _lastGetTimeStamp(0.0)
{

}

bool FrameBuffer::push(const Frame& frame)
{
    const size_t newHeadIdx = (_headIdx + 1) % _frames.size();

    //try for 1ms to lock
    unique_lock<timed_mutex> lock(_mutexs[newHeadIdx],chrono::milliseconds(2));
    if(!lock.owns_lock())
    {
        return false;
    }

    _frames[newHeadIdx] = frame;
    if(newHeadIdx == _tailIdx)
    {
        _tailIdx = (_tailIdx + 1) % _frames.size();
    }
    _headIdx = newHeadIdx;

    return true;
}

bool FrameBuffer::getLatest(Frame& frame)
{
    volatile const size_t headIdx = _headIdx;

    //try for 1ms to lock

    unique_lock<timed_mutex> lock(_mutexs[headIdx],chrono::milliseconds(2));
    if(!lock.owns_lock() ||
       _frames[headIdx].img.empty() ||
       _frames[headIdx].timeStamp == _lastGetTimeStamp)
    {
        return false;
    }

    frame = _frames[headIdx];
    _lastGetTimeStamp = _frames[headIdx].timeStamp;

    return true;
}



ImgProdCons::ImgProdCons():
    _videoCapturePtr(make_unique<RMVideoCapture>()),
    _buffer(6),
    _serialPtr(make_unique<Serial>()),
    _solverPtr(make_unique<AngleSolver>()),
    _predictorPtr(make_unique<Predictor>()),
    _armorDetectorPtr(make_unique<ArmorDetector>()),
    //_runeDetectorPtr(make_unique<RuneDetector>()),
    //_windmillPtr(make_unique<Windmill>()),
    _sentryStrategiesPtr(make_unique<Strategies>()),
    _task(Serial::NO_TASK)
{}

void ImgProdCons::signal_handler(int)
{
    _quit_flag = true;
}

void ImgProdCons::init_signals(void)
{
    _quit_flag = false;
    struct sigaction sigact;
    sigact.sa_handler = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGINT,&sigact,(struct sigaction*)NULL);
}

void ImgProdCons::produce()
{
    auto startTime = chrono::high_resolution_clock::now();

    auto t1 = chrono::high_resolution_clock::now();
    for(;;)
    {
        /*
         * Can prevent the camera usb port from being blocked as possible.
         */
        if (_quit_flag) return;

//        CFrame frame;
        /*
         * Decoding costs lots of time, so let the STM record after grab,
         * and then decode by calling 'retrieve'.
         */

//        if(!_videoCapturePtr->grab(frame)) continue;
        if(!_videoCapturePtr->grab()) continue;

        /*
         * Every new Mat has a new address.
         * Let the sequence number of image frame and serial frame be the same.
         */
        Mat newImg;
        uint8_t seq;
        double timeStamp = (static_cast<chrono::duration<double,std::milli>>(chrono::high_resolution_clock::now() - startTime)).count();
        GyroData poseEuler;
        /*
         * Tell the STM to record.
         */
//        auto t3 = chrono::high_resolution_clock::now();
        if(_serialPtr->tryRecord(seq, poseEuler, chrono::milliseconds(1)) != Serial::OJBK)
        {
            cout<<"!"<<endl;
            cout<<"trying reopen port"<<endl;
            _serialPtr->closePort();
            _serialPtr->openPort();
            _serialPtr->setDebug(false);
            int self_color;
            while(_serialPtr->setup(self_color) != Serial::OJBK)
            {
                sleep(1);
            }
            cout << "I am " << (self_color == rm::BLUE ? "blue" : "red") << "." << endl;
            continue;
        }
//        auto t4 = chrono::high_resolution_clock::now();
//        cout << "Capture period: " << (static_cast<chrono::duration<double, std::milli>>(t4 - t3)).count() << " ms" << endl;
//        t3=t4;

        /*
         * Decode image
         */
//        if(!_videoCapturePtr->retrieve(newImg, frame)) continue;
        if(!_videoCapturePtr->retrieve(newImg)) continue;


        /*
         * push the new image into the circular buffer
         */
        _buffer.push(Frame{newImg, poseEuler, seq, timeStamp});

//        auto t2 = chrono::high_resolution_clock::now();
//        cout << "Capture period: " << (static_cast<chrono::duration<double, std::milli>>(t2 - t1)).count() << " ms" << endl;
//        cout << endl;
//        t1 = t2;
    }
}

}
