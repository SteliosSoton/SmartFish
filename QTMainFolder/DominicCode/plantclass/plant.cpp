#include "plant.h"

plant::plant()
{




}

void plant::setIdealTemp(int newT)
{
    idealTemp=newT;
}
void plant::setIdealLight(int newL)
{
    idealTemp=newL;
}
void plant::setIdealSoilMoisture(int newM)
{
    idealTemp=newM;
}
void plant::setIdealAirHum(int newH)
{
    idealTemp=newH;
}
int plant::getIdealTemp()
{
    return idealTemp;
}
int plant::getIdealLight()
{
    return idealLight;
}
int plant::getIdealSoilMoisture()
{
    return idealSoilMoisture;
}
int plant::getIdealAirHum()
{
    return idealAirHum;
}
