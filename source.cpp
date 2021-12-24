#include "source.h"

Source::Source(int sourceNumber_, double sourceSpeed_)  : sourceNumber(sourceNumber_), sourceSpeed(sourceSpeed_) {}

appPointer Source::generationApp()
{
    generatedApps++;
    newGenerationTime += (-1 / sourceSpeed * log(static_cast<double>(qrand()) / static_cast<double>(RAND_MAX)));
    return Application::getNewApplication(newGenerationTime, sourceNumber, generatedApps);
}

bool Source::compare(Source &a, Source &b)
{
    return a.getNewGenerationTime() < b.getNewGenerationTime();
}

int Source::getSourceNumber()
{
    return sourceNumber;
}
double Source::getSourceSpeed()
{
    return sourceSpeed;
}
double Source::getNewGenerationTime()
{
    return newGenerationTime;
}
int Source::getGeneratedApps()
{
    return generatedApps;
}
