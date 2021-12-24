#ifndef SOURCE_H
#define SOURCE_H

#include "application.h"
#include <QtMath>
#include <QtGlobal>

class Source
{
public:
    Source(int sourceNumber_, double sourceSpeed_);

    appPointer generationApp();

    bool static compare(Source &a, Source &b);

    int getSourceNumber();
    double getSourceSpeed();
    double getNewGenerationTime();
    int getGeneratedApps();


private:
    int sourceNumber;
    double sourceSpeed = 0.0;
    double newGenerationTime = 0.0;
    int generatedApps = 0;
};

#endif // SOURCE_H
