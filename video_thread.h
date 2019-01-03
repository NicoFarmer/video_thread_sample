#ifndef VIDEO_THREAD_H
#define VIDEO_THREAD_H

#include <QObject>
#include <QThread>
// AJOUTE PAR LAGUICHE --------------------------
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
// ----------------------------------------------

typedef enum {
    VIDEO_PROCESS_ALGO1 = 0,
    VIDEO_PROCESS_ALGO2,
    VIDEO_PROCESS_DUMMY
}tVideoProcessAlgoType;

typedef struct
{
    tVideoProcessAlgoType video_process_algo;
    float data1;
    float data2;
    float data3;

}tVideoInput;

typedef struct
{
    float result1;
    float result2;
    std::vector <int>markers_detected;
}tVideoResult;

Q_DECLARE_METATYPE(tVideoInput)
Q_DECLARE_METATYPE(tVideoResult)

// ======================================================
// ======================================================
class VideoWorker : public QObject
{
    Q_OBJECT
public :
    void init(QString video_name);

private :
    QString m_video_name;
    bool m_stop_work_request;

// AJOUTE PAR LAGUICHE --------------------------
    cv::VideoCapture * capture;
// ----------------------------------------------
    cv::Mat m_frame; //image du buffer video
    cv::Mat m_frameCloned;



public slots:
    void doWork(tVideoInput parameter);
    void stopWork();

signals:
    void resultReady(tVideoResult result);
    void workStarted();
    void workFinished();


private:
    void _video_process_algo1(tVideoInput parameter);
    void _video_process_dummy(tVideoInput parameter);
};



#endif // VIDEO_THREAD_H
