#ifndef STATISTIC_H
#define STATISTIC_H

#include "step.h"

#include <numeric>
#include <cmath>
#include <vector>


class Statistic
{
public:
    Statistic(int sizeBuff_, int appsQantity_, int sourcesQantity_,
              int devicesQuantity_, double lambda_, double a_, double b_);

    void processed(int sourceNumber_);
    void rejected(int sourceNumber_);
    void funTimeInSystem(int sourceNumber_, double time_);
    void funSystemTime(double time_);
    void funWaitingTime(int sourceNumber_, double time_);
    void funServiceTime(int sourceNumber_, double time_);
    void funDeviceWorkingTime(int sourceNumber_, double time_);
    void addStep(step_t step_);

    int getProcessed();
    int getProcessed(int sourceNumber_);
    int getRejected();
    int getRejected(int sourceNumber_);
    double getTimeInSystem(int sourceNumber_);
    double getSystemTime();
    double getWaitingTime(int sourceNumber_);
    double getServiceTime(int sourceNumber_);
    double getDeviceWorkingTime(int deviceNumber_);
    double getTotalTime(std::vector<double> time_);
    std::vector<step_t> getSteps();
    void stepsForm();
    int getAppsQantity();
    int getSizeBuff();
    int getSourcesQantity();
    int getDevicesQuantity();
    double getDevicesTimeAverage();
    double getTimeInSysAverage();
    double getLambda();
    double getA();
    double getB();

private:
    std::vector<int> processedApps;
    std::vector<int> rejectedApps;
    std::vector<double> timeInSystem;
    std::vector<std::vector<double>> waitingTime;
    std::vector<std::vector<double>> serviceTime;
    std::vector<double> deviceWorkingTime;
    std::vector<step_t> steps;
    double systemTime;
    int sizeBuff;
    int appsQantity;
    int sourcesQantity;
    int devicesQuantity;
    double lambda;
    double a;
    double b;
};

#endif // STATISTIC_H
