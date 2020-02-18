#ifndef _TIME_UTILS_H
#define _TIME_UTILS_H

#include "LogUtils.h"

#ifdef _MSC_VER // 兼容微软平台
#include <windows.h>
#include <WinSock.h>
static int gettimeofday(struct timeval *tp, void *tzp) {
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#else
#include <sys/time.h>
#endif // _MSC_VER

static unsigned long long currentTimeMillis(void) {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000000ULL + tv.tv_usec;
}

#ifdef DEBUG // 在 LogUtils.h 中定义了，也可以单独使用另一个宏开控制开关
#define __TIC1__(tag) unsigned long long time_##tag##_start = currentTimeMillis();
#define __TOC1__(tag) unsigned long long time_##tag##_end = currentTimeMillis();\
        LOGD(#tag " time: %.3f ms", ((time_##tag##_end - time_##tag##_start) / 1000.0))
#else
#define __TIC1__(tag)
#define __TOC1__(tag)
#endif // DEBUG

#endif //_TIME_UTILS_H
