#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

class Application
{
public:
  Application(double startTime_, int sourceNumber_, int appNumber_);

  static std::shared_ptr<Application> getNewApplication(double startTime_, int sourceNumber_, int appNumber_);

  double getStartTime();
  int getSourceNumber();
  int getAppNumber();

private:
  double startTime = 0.0;
  int sourceNumber = 0;
  int appNumber = 0;
};

typedef  std::shared_ptr<Application> appPointer;
#endif // APPLICATION_H
