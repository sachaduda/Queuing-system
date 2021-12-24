#ifndef STEP_H
#define STEP_H

#include "application.h"

#include <vector>
#include <string>

struct step_t
{
    double time;
    std::string action;
    std::vector<appPointer> bufferVector;
    std::vector<appPointer> deviceVector;
};

#endif // STEP_H
