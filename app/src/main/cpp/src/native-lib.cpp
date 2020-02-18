#include <jni.h>
#include <string>
#include "LogUtils.h"
#include "TimeUtils.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int playVideo(const string &filename) {
    __TIC1__(VideoCapture_Constructor);
    VideoCapture capture(filename);
    __TOC1__(VideoCapture_Constructor);
    __TIC1__(isOpened);
    if (!capture.isOpened()) {
        LOGE("Error : video loaded failed");
        return -1;
    }
    __TOC1__(isOpened);
    __TIC1__(get_CV_CAP_PROP_FPS);
    double rate = capture.get(CV_CAP_PROP_FPS); //获取帧率
    __TOC1__(get_CV_CAP_PROP_FPS);
    LOGD("rate: %f", rate);
    Mat frame;
    char output_path[32];
    int index = 0;
    __TIC1__(total_read);
    while (capture.read(frame)) {
        sprintf(output_path, "/sdcard/sensetime/frame/%d.png", index);
        LOGD("output_path: %s", output_path);
        index++;
        __TIC1__(imwrite);
        bool ret = imwrite(output_path, frame);
        LOGD("imwrite ret: %d", ret);
        __TOC1__(imwrite);
    }
    __TOC1__(total_read);
    __TIC1__(release);
    capture.release();
    __TOC1__(release);
    return 0;
}

extern "C" JNIEXPORT jstring
JNICALL
Java_com_afei_opencvdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    string filepath = "/sdcard/test.mp4";
    LOGD("filepath: %s", filepath.c_str());
    int ret = playVideo(filepath);
    LOGD("ret: %d", ret);
    return env->NewStringUTF("Hello from C++");
}
