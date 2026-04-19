#include "time.h"
string get_time() {//获取当前时间
    time_t now = time(0);
    struct tm* t = localtime(&now);
    return to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday) + "_" + to_string(t->tm_hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec);
}