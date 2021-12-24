#include "application.h"

Application::Application(double startTime_, int sourceNumber_, int appNumber_)
  : startTime(startTime_), sourceNumber(sourceNumber_), appNumber(appNumber_) {}

std::shared_ptr<Application> Application::getNewApplication(double startTime_, int sourceNumber_, int appNumber_)
{
  return std::shared_ptr<Application>(new Application(startTime_, sourceNumber_, appNumber_));
}

double Application::getStartTime()
{
  return startTime;
}

int Application::getSourceNumber()
{
  return sourceNumber;
}

int Application::getAppNumber()
{
  return appNumber;
}
