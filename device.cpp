#include "device.h"

Device::Device(int deviceNumber_, double a_, double b_) : deviceNumber(deviceNumber_), a(a_), b(b_) {}

void Device::getApp(const appPointer currentApp_, step_t & step_)
{
    currentPointer = currentApp_;

    step_.deviceVector[deviceNumber] = currentApp_;

    if ((startTimeTask == 0) || (startTimeTask < currentApp_->getStartTime()))
    {
        startTimeTask = currentApp_->getStartTime();
    }
    endTimeTask = startTimeTask + (((double)qrand()/(double)RAND_MAX) * (b - a) + a);

    step_.time = startTimeTask;
    step_.deviceVector[deviceNumber] = currentApp_;
    step_.action = "Application " + std::to_string(currentPointer->getSourceNumber() + 1)
            + "." + std::to_string(currentPointer->getAppNumber())
            + " is on device " + std::to_string(getDeviceNumber() + 1);
}

void Device::addToStatistic(Statistic &statistic_, step_t & step_)
{
    step_.time = endTimeTask;
    step_.deviceVector[deviceNumber] = nullptr;
    step_.action = "Application " + std::to_string(currentPointer->getSourceNumber() + 1)+ "."
            + std::to_string(currentPointer->getAppNumber())
            + " processed. Device " + std::to_string(getDeviceNumber() + 1) + " is free.";

    statistic_.addStep(step_);
    statistic_.processed(currentPointer->getSourceNumber());
    statistic_.funTimeInSystem(currentPointer->getSourceNumber(), endTimeTask - currentPointer->getStartTime());
    statistic_.funDeviceWorkingTime(deviceNumber, endTimeTask - startTimeTask);
    statistic_.funWaitingTime(currentPointer->getSourceNumber(), startTimeTask - currentPointer->getStartTime());
    statistic_.funServiceTime(currentPointer->getSourceNumber(), endTimeTask - startTimeTask);
    statistic_.funSystemTime(endTimeTask);
}

bool Device::isFree(Statistic &statistic_, step_t & step_)
{
    if (currentPointer == nullptr)
    {
        return true;
    }
    else
    {
        addToStatistic(statistic_, step_);
        currentPointer = nullptr;
        startTimeTask = endTimeTask;
        return true;
    }
}

bool Device::isFree(double lastAppTime_, Statistic &statistic_, step_t & step_)
{
    if (currentPointer == nullptr)
    {
        return true;
    }

    if (endTimeTask < lastAppTime_)
    {
        addToStatistic(statistic_, step_);
        currentPointer = nullptr;
        startTimeTask = endTimeTask;
        return true;
    }
    return false;
}


bool Device::compareNumber(Device &a, Device &b)
{
    return a.getDeviceNumber() < b.getDeviceNumber();
}

bool Device::compareTime(Device &a, Device &b)
{
  return a.getTaskEndTime() < b.getTaskEndTime();
}

int Device::getDeviceNumber()
{
    return deviceNumber;
}

double Device::getTaskStartTime()
{
    return startTimeTask;
}

double Device::getTaskEndTime()
{
    return endTimeTask;
}
