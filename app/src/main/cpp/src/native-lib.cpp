#include <jni.h>
#include <string>
#include <vector>

#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;


extern "C" JNIEXPORT jstring
JNICALL
Java_com_afei_opencvdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {


    return env->NewStringUTF("Hello from C++");
}
