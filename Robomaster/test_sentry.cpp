#include<unistd.h>
#include"iostream"
#include<opencv2/opencv.hpp>
#include<thread>
#include<list>

#include"ImgProdCons.h"
#include"./Armor/ArmorDetector.h"
#include"./Pose/AngleSolver.hpp"
#include"./KCF/kcftracker.hpp"

using namespace std;
using namespace cv;

//#define _DEBUG
//#define GET_VIDEO

namespace rm
{

void ImgProdCons::init()
{
    //prevent usb port from being blocked
    init_signals();

    //Initialize camera
    _videoCapturePtr->open(0,2); // 0 works fine for small panel , if you meet problem opening the camera, try change this
    _videoCapturePtr->setVideoFormat(1280, 720, true);
    _videoCapturePtr->setExposureTime(100);
    _videoCapturePtr->setFPS(60);
//    _videoCapturePtr->setBalanceRatio(1.6, 1.3, 2.0);
//    _videoCapturePtr->setGain(1);
//    _videoCapturePtr->setGamma(1);

//    _videoCapturePtr->startStream();
//    _videoCapturePtr->closeStream();
    _videoCapturePtr->startStream();
    _videoCapturePtr->info();

    //Initilize serial
    _serialPtr->openPort();
    _serialPtr->setDebug(false);
    int self_color;
    while(_serialPtr->setup(self_color) != Serial::OJBK)
    {
        sleep(1);
    }
    self_color =rm::RED;
//    self_color =rm::BLUE;
    cout << "I am " << (self_color == rm::BLUE ? "blue" : "red") << "." << endl;

    //Initialize angle solver
    AngleSolverParam angleParam;
    angleParam.readFile(9);//camera number sentry = 9
    _solverPtr->init(angleParam);
    _solverPtr->setResolution(_videoCapturePtr->getResolution());

    //Initialize armor detectorp
    ArmorParam armorParam;
    _armorDetectorPtr->init(armorParam);
    _armorDetectorPtr->setEnemyColor(self_color == rm::BLUE ? rm::RED : rm::BLUE);
    _sentryStrategiesPtr->initPara();
}

//void updateFeeling(list<double>& feeling, const double duration)
//{
//    for(auto it = feeling.begin(); it != feeling.end(); it++)
//    {
//        if(*it < 10)
//        {
//            feeling.erase(it);
//        }
//        else
//        {
//            *it *= exp(0.1*duration);
//        }
//    }
//}

void ImgProdCons::sense()
{
    //	chrono::time_point<chrono::steady_clock> lastTime;
    //	list<double> worrys0, worrys1, pains;
    //	double totalWorry0, totalWorry1, totalPain;
    //	const double TAU = 0.1;
    //	const double M = 10;
    //	int remainHp = 3000;
    /* Loop for sensing */
    for(;;)
    {
        FeedBackData feedBackData;
//        auto t1 = chrono::high_resolution_clock::now();
        /* TODO: Handel exceptions when socket suddenly being plugged out. */
        if(_serialPtr->tryFeedBack(feedBackData, chrono::milliseconds(2)) == Serial::OJBK)
        {
//            auto t2 = chrono::high_resolution_clock::now();
//            cout << "Capture period: " << (static_cast<chrono::duration<double, std::milli>>(t2 - t1)).count() << " ms" << endl;
            //			const auto nowTime = chrono::high_resolution_clock::now();
            //			const auto duration = (static_cast<chrono::duration<double, std::milli>>(nowTime - lastTime)).count();

            //			/*	Update historic worrys and pain */
            //			updateFeeling(worrys0, duration);
            //			updateFeeling(worrys1, duration);
            //			updateFeeling(pains, duration);

            //TODO: add other states
            //_task = feedBackData.task_mode;

            //			auto pain = remainHp - feedBackData.remain_hp;
            //			remainHp = feedBackData.remain_hp;
            //			if(feedBackData.shot_armor == 0)
            //			{
            //				worrys0.push_back(pain);
            //				pains.push_back(pain);
            //			}
            //			else if(feedBackData.shot_armor == 1)
            //			{
            //				worrys1.push_back(pain);
            //				pains.push_back(pain);
            //			}

            //			totalWorry0 = accumulate()


            //			lastTime = nowTime;
            //cout<<"sense"<<endl;
            this_thread::sleep_for(chrono::milliseconds(80));
        }
        else
        {
            //cout<<"??sense"<<endl;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
}

void ImgProdCons::consume()
{
#ifdef GET_VIDEO
    /*
     * Variables for recording camera
     */
    VideoWriter writer;
    bool isRecording = false;
    time_t t;
    time(&t);
    const string fileName = "/home/nvidia/Robomaster/Robomaster2019/" + to_string(t) + ".avi";
    writer.open(fileName, CV_FOURCC('M', 'J', 'P', 'G'), 25, Size(1280, 720));
#endif


    /* Variables for serial communication*/
    ControlData controlData;
    controlData.gimbal_mode = Serial::PATROL_AROUND;

    /* Variables for angle solve module */
    int angleFlag;
    Vec2f targetAngle;

    /* Variables for armor detector modeule */
    int armorFlag;
    int armorType;
    std::vector<cv::Point2f> armorVertex;


    /* The main loop for armor detection */
    Frame frame;
	//CFrame frame;

    for(;;)
    {
        auto t1 = chrono::high_resolution_clock::now();

        if(_serialPtr->getErrorCode() == Serial::SYSTEM_ERROR || !_videoCapturePtr->isOpened())
        {
            this_thread::sleep_for(chrono::seconds(3));
        }


        if(!_buffer.getLatest(frame)) continue;
//        imshow("emm",frame.img);
        waitKey(1);
        _armorDetectorPtr->loadImg(frame.img);

        /* detect lightbar */
        if(controlData.gimbal_mode == Serial::PATROL_AROUND)
        {
            if(_sentryStrategiesPtr->sentryStatus == Strategies::PATROL)
            {
                if(_armorDetectorPtr->detect_lightbar())
                {
                    controlData.gimbal_mode = Serial::SERVO_MODE;
                    _sentryStrategiesPtr->sentryStatus = Strategies::SEARCH;
                    _sentryStrategiesPtr->_num_search = 10;
                }
                else
                {
                    controlData.gimbal_mode = Serial::PATROL_AROUND;
                }
                    controlData.frame_seq   = frame.seq;
                    controlData.shoot_mode  = Serial::NO_FIRE | Serial::HIGH_SPEED;
                    controlData.pitch_dev   = 0;
                    controlData.yaw_dev     = 0;
                    if(_serialPtr->tryControl(controlData, chrono::milliseconds(1)) != Serial::OJBK)
                    {
                        cout<<"not sent"<< endl;
                    }
                    cout<<"detect lightbar"<<endl;

                continue;
            }
            else if(_sentryStrategiesPtr->sentryStatus == Strategies::WAIT)
            {
                controlData.gimbal_mode = Serial::PATROL_AROUND;
                controlData.frame_seq   = frame.seq;
                controlData.shoot_mode  = Serial::NO_FIRE | Serial::HIGH_SPEED;
                controlData.pitch_dev   = 0;
                controlData.yaw_dev     = 0;
                if(_serialPtr->tryControl(controlData, chrono::milliseconds(1)) != Serial::OJBK)
                {
                    cout<<"not sent"<< endl;
                }
                _sentryStrategiesPtr->count();
                cout<<"wait"<<endl;
                this_thread::sleep_for(chrono::milliseconds(50));
                continue;
            }
            cout<<"liangtoule"<<endl;
        }


        /* detect armor */
        armorFlag = _armorDetectorPtr->detect();
        if(armorFlag == ArmorDetector::ARMOR_LOCAL || armorFlag == ArmorDetector::ARMOR_GLOBAL || armorFlag == ArmorDetector::TRACKING)//
        {
            armorVertex = _armorDetectorPtr->getArmorVertex();
            armorType = _armorDetectorPtr->getArmorType();
//            cout<<armorType<<endl;
            if(armorFlag == ArmorDetector::TRACKING)
            {
                if(_armorDetectorPtr->_para._losting)
                {
                    cout<<"taget is losting..."<<endl;
                    //_sentryStrategiesPtr->popFrontAngle();
                    continue;
                }
                _solverPtr->setTarget(_armorDetectorPtr->getKCFTarget(), 0);//armorType
            }
            else
            {
                _solverPtr->setTarget(armorVertex,armorType);
                _solverPtr->solve();
                float t_x=0,t_y=0;
                cv::Point2f t_point;
                t_x=(armorVertex[0].x+armorVertex[1].x+armorVertex[2].x+armorVertex[3].x)/4;
                t_y=(armorVertex[0].y+armorVertex[1].y+armorVertex[2].y+armorVertex[3].y)/4;
                t_point.x=t_x;
                t_point.y=t_y;
                _solverPtr->setTarget(t_point, 0);//armorType
            }

            _solverPtr->setCurrentPose(frame.PoseEuler.gimbal_pitch, 0);
            angleFlag = _solverPtr->solve();

            if(angleFlag != rm::AngleSolver::ANGLE_ERROR)
            {
                targetAngle = _solverPtr->getCompensateAngle();//getAngle();//
                _sentryStrategiesPtr->pushBackAngle(targetAngle);

                controlData.frame_seq = frame.seq;
                if(_sentryStrategiesPtr->ifHitTarget())
                {
                    controlData.shoot_mode  = Serial::BURST_FIRE | Serial::HIGH_SPEED;
                    cout<<"hit"<<endl;
                }
                else
                {
                    controlData.shoot_mode  = Serial::NO_FIRE | Serial::HIGH_SPEED;
                    cout<<"emmm"<<endl;
                }
                //controlData.shoot_mode  = Serial::BURST_FIRE | Serial::HIGH_SPEED;
                controlData.pitch_dev   = targetAngle[1];
                controlData.yaw_dev     = targetAngle[0];
//--------testKF-------------------------------------------------//
//                _predictorPtr->predict_yaw(controlData.yaw_dev);

//                controlData.yaw_dev     = _predictorPtr->get_predict_yaw();
//                for(int t=0;t<3*(20-_predictorPtr->get_predict_yaw());t++)
//                {
//                    cout<<"0";
//                }
//                cout<<_predictorPtr->get_predict_yaw()<<endl;


//--------testKF-------------------------------------------------//
                //controlData.speed_on_rail = 0;

                controlData.gimbal_mode = Serial::SERVO_MODE;
                _sentryStrategiesPtr->sentryStatus = Strategies::SERVO;
                _sentryStrategiesPtr->_num_search = 15;

                if(_serialPtr->tryControl(controlData, chrono::milliseconds(2)) != Serial::OJBK)
                {
                    cout<<"not sent"<< endl;
                }
                cout << "Deviation: " << targetAngle <<endl;

//                for(int t=0;t<2*(20-targetAngle[0]);t++)
//                {
//                    cout<<"1";
//                }
//                cout<<targetAngle[0]<<endl;
//                cout<<endl;
                //continue;
            }

        }
        else
        {


            if(Strategies::SERVO)
                _sentryStrategiesPtr->popFrontAngle();

            _sentryStrategiesPtr->count();

            if(_sentryStrategiesPtr->_num_search == 0)
            {
                controlData.gimbal_mode = Serial::PATROL_AROUND;
                cout<<"e"<<endl;
            }
            else
            {
                controlData.gimbal_mode = Serial::SERVO_MODE;
                cout<<"emmm"<<endl;
            }
            //controlData.gimbal_mode = Serial::PATROL_AROUND;
            controlData.frame_seq   = frame.seq;
            controlData.shoot_mode  = Serial::NO_FIRE | Serial::HIGH_SPEED;
            controlData.pitch_dev   = 0;
            controlData.yaw_dev     = 0;
            if(_serialPtr->tryControl(controlData, chrono::milliseconds(1)) != Serial::OJBK)
            {
                cout<<"not sent"<< endl;
            }

        }
//        cout << "Deviation: " << targetAngle <<endl;





#ifdef _DEBUG
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Total period: " << (static_cast<chrono::duration<double, std::milli>>(t2 - t1)).count() << " ms" << endl;
        cout << endl;
        t1 = t2;
#endif

#ifdef GET_VIDEO
        if(isRecording)
        {
            writer << frame.img;
        }
        if(!writer.isOpened())
        {
            cout << "Capture failed." << endl;
            continue;
        }
        isRecording = true;
        //cout << "Start capture. " + fileName +" created." << endl;
        if(waitKey(1) == 'q')
        {
            return;
        }
#endif

    }
}





}
