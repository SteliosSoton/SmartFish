#ifndef PLANTPROFILE_H
#define PLANTPROFILE_H

#include <QString>

class PlantProfile
{

public:
    PlantProfile(QString inputName, int inputTemp, int inputLight, int inputMoisture, int inputHumidity);

    QString plantTypeName;

    int idealTemp;
    int idealLight;
    int idealMoisture;
    int idealHumidity;

};

#endif // PLANTPROFILE_H
