#include "statistic.h"

Statistic::Statistic(int sizeBuff_, int appsQantity_, int sourcesQantity_, int devicesQuantity_, double lambda_, double a_, double b_) :
         sizeBuff(sizeBuff_), appsQantity(appsQantity_),sourcesQantity(sourcesQantity_), devicesQuantity(devicesQuantity_),
         lambda(lambda_), a(a_), b(b_)
{
    rejectedApps = std::vector<int>(sourcesQantity_, 0);
    processedApps= std::vector<int>(sourcesQantity_, 0);
    timeInSystem = std::vector<double>(sourcesQantity_, 0.0);
    deviceWorkingTime = std::vector<double>(devicesQuantity_, 0.0);
    waitingTime = std::vector<std::vector<double>>(sourcesQantity_);
    serviceTime = std::vector<std::vector<double>>(sourcesQantity_);
}

void Statistic::processed(int sourceNumber_)
{
    processedApps.at(sourceNumber_)++;
}

void Statistic::rejected(int sourceNumber_)
{
    rejectedApps.at(sourceNumber_)++;
}

void Statistic::funTimeInSystem(int sourceNumber_, double time_)
{
     timeInSystem.at(sourceNumber_) += time_;
}

void Statistic::funSystemTime(double time_)
{
    systemTime = time_;
}

void Statistic::funWaitingTime(int sourceNumber_, double time_)
{
    waitingTime.at(sourceNumber_).push_back(time_);
}

void Statistic::funServiceTime(int sourceNumber_, double time_)
{
    serviceTime[sourceNumber_].push_back(time_);
}

void Statistic::funDeviceWorkingTime(int sourceNumber_, double time_)
{
    deviceWorkingTime.at(sourceNumber_) += time_;
}

void Statistic::addStep(step_t step_)
{
    steps.push_back(step_);
}

int Statistic::getProcessed()
{
    int processed = 0;
    for (int i = 0; i < processedApps.size(); i++)
    {
        processed += processedApps.at(i);
    }
    return processed;
}

int Statistic::getProcessed(int sourceNumber_)
{
    return processedApps.at(sourceNumber_);
}

int Statistic::getRejected()
{
    int rejected = 0;
    for (int i = 0; i < rejectedApps.size(); i++)
    {
        rejected += rejectedApps.at(i);
    }
    return rejected;
}

double Statistic::getDevicesTimeAverage()
{
    double time = 0;
    for (int i = 0; i < getDevicesQuantity(); i++)
    {
        time += getDeviceWorkingTime(i) / getSystemTime();
    }
    return time;
}

double Statistic::getTimeInSysAverage()
{
    double time = 0;
    for (int i = 0; i < getSourcesQantity(); i++)
    {
        time += getTimeInSystem(i) / (getProcessed(i) + getRejected(i));
    }
    return time;
}

int Statistic::getRejected(int sourceNumber_)
{
    return rejectedApps.at(sourceNumber_);
}

double Statistic::getTimeInSystem(int sourceNumber_)
{
    return timeInSystem.at(sourceNumber_);
}

double Statistic::getSystemTime()
{
    return systemTime;
}

double Statistic::getWaitingTime(int sourceNumber_)
{
    double sum = 0.0;
    int tempAppsQuantity = processedApps.at(sourceNumber_) + rejectedApps.at(sourceNumber_);
    double averageWaitTime = getTotalTime(waitingTime.at(sourceNumber_)) / tempAppsQuantity;

    for (int i = 0; i < waitingTime.at(sourceNumber_).size(); i++)
    {
        sum += pow(waitingTime.at(sourceNumber_).at(i) - averageWaitTime, 2);
    }
    return sum / tempAppsQuantity;
}

double Statistic::getServiceTime(int sourceNumber_)
{
    double sum = 0.0;
    double averageServiceTime = getTotalTime(serviceTime.at(sourceNumber_)) / processedApps.at(sourceNumber_);

    for (int i = 0; i < serviceTime.at(sourceNumber_).size(); i++)
    {
        sum += pow(serviceTime.at(sourceNumber_).at(i) - averageServiceTime, 2);
    }
    return sum / processedApps.at(sourceNumber_);
}

double Statistic::getDeviceWorkingTime(int deviceNumber_)
{
    return deviceWorkingTime.at(deviceNumber_);
}

double Statistic::getTotalTime(std::vector<double> time_)
{
    return std::accumulate(time_.begin(), time_.end(), 0);
}

std::vector<step_t> Statistic::getSteps()
{ 
    return steps;
}

int Statistic::getAppsQantity()
{
    return appsQantity;
}

int Statistic::getSizeBuff()
{
    return sizeBuff;
}

int Statistic::getSourcesQantity()
{
    return sourcesQantity;
}

int Statistic::getDevicesQuantity()
{
    return devicesQuantity;
}

double Statistic::getLambda()
{
    return lambda;
}

double Statistic::getA()
{
    return a;
}

double Statistic::getB()
{
    return b;
}

void Statistic::stepsForm()
{
    for(int i = 1; i < steps.size(); ++i)
    {
        for(int r = 0; r < steps.size()-i; r++)
        {
            if(steps[r].time > steps[r + 1].time)
            {
                double temp = steps[r].time;
                steps[r].time = steps[r + 1].time;
                steps[r + 1].time = temp;
            }
        }
    }
}
