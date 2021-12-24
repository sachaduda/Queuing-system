#include "buffer.h"

Buffer::Buffer(int sizeBuff_) : sizeBuff(sizeBuff_), freePlace(sizeBuff_)
{
  appVector = std::vector<appPointer>(sizeBuff);
  appVector.reserve(sizeBuff);
}

void Buffer::addApp(const appPointer newApp_, step_t& step_)
{
  for (int i = 0; i != sizeBuff; i++)
  {
    if (appVector.at(i) == nullptr)
    {
        appVector.at(i) = newApp_;
        step_.time = newApp_->getStartTime();
        step_.bufferVector.at(i) = newApp_;
        step_.action = "Application " + std::to_string(newApp_->getSourceNumber() + 1)
                + "." + std::to_string(newApp_->getAppNumber()) +" generated and added to buffer.";
        minusFreePlace();
        break;
    }
  }
}


appPointer Buffer::getApp(step_t& step_)
{
    int index = 0;
    double maxTime = 0.0;
    for (int i = 0; i < sizeBuff; i++)
    {
        if (appVector.at(i) != nullptr)
        {
            if (appVector.at(i)->getStartTime() > maxTime)
            {
                maxTime = appVector.at(i)->getStartTime();
                index = i;
            }
        }
    }
    for (int i = 0; i < step_.bufferVector.size(); i++)
    {
        if (step_.bufferVector.at(i) == appVector.at(index))
            {
               step_.bufferVector.at(i) = nullptr;
            }
    }
    appPointer tempPointer =  appVector.at(index);
    appVector.at(index) = nullptr;
    freePlace++;
    return tempPointer;
}

bool Buffer::compare(const appPointer& a_, const appPointer& b_)
{
  if (b_ == nullptr || a_ == nullptr)
  {
    return false;
  }
  return a_->getStartTime() < b_->getStartTime();
}


void Buffer::removeApp(const appPointer newApp_, step_t &step_)
{
  auto min = std::min_element(appVector.begin(), appVector.end(), Buffer::compare);
  removedApp = *min;
  *min = newApp_;
  for (int i = 0; i < step_.bufferVector.size(); i++)
  {
     if (step_.bufferVector.at(i) == removedApp)
     {
         step_.bufferVector.at(i) = newApp_;
     }
  }
}

bool Buffer::isEmpty()
{
  return freePlace == sizeBuff;
}

bool Buffer::isFull()
{
  return freePlace == 0;
}

void Buffer::minusFreePlace()
{
  freePlace--;
}

int Buffer::getSizeBuff()
{
  return sizeBuff;
}

int Buffer::getFreePlace()
{
  return freePlace;
}

appPointer Buffer::getRemovedApp()
{
  return removedApp;
}
