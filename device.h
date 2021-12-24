#ifndef DEVICE_H
#define DEVICE_H

#include "application.h"
#include "statistic.h"
#include "step.h"
#include <QtGlobal>

class Device
{
public:
    Device(int deviceNumber_, double a_, double b_);

    void getApp(const appPointer currentApp_, step_t & step_);
    void addToStatistic(Statistic &statistic_, step_t & step_);

    bool isFree(Statistic &statistic_, step_t & step_);
    bool isFree(double lastAppTime_, Statistic &statistic_, step_t & step_);
    bool static compareNumber(Device &a, Device &b);
    bool static compareTime(Device &a, Device &b);

    int getDeviceNumber();
    double getTaskStartTime();
    double getTaskEndTime();

private:
    int deviceNumber;
    double a;
    double b;
    double startTimeTask = 0.0;
    double endTimeTask = 0.0;
    appPointer currentPointer;
};

#endif // DEVICE_H
