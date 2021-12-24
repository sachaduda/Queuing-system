#ifndef BUFFER_H
#define BUFFER_H

#include "application.h"
#include "step.h"

#include <vector>
#include <algorithm>
#include <iterator>

class Buffer
{
public:
  Buffer(int sizeBuff_);

  void addApp(const appPointer newApp_, step_t& step_);
  appPointer getApp(step_t& step_);
  void removeApp(const appPointer newApp_, step_t &step_);
  bool static compare(const appPointer& a_, const appPointer& b_);

  bool isEmpty();
  bool isFull();
  void minusFreePlace();

  int getSizeBuff();
  int getFreePlace();
  appPointer getRemovedApp();

private:
  std::vector<appPointer> appVector;
  int sizeBuff;
  int freePlace;

  appPointer removedApp;
};

#endif // BUFFER_H
