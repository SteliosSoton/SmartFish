#ifndef PLANTPROFILE_H
#define PLANTPROFILE_H

#include <QString>

class PlantProfile
{

public:
    PlantProfile(QString inputName, int inputTemp, int inputLight, int inputMoisture, int inputHumidity);

 //   QString getPlantTypeName();

 //   int getIdealTemp();
 //   int getIdealLight();
 //   int getIdealMoisture();
 //   int getIdealHumidity();

 //   void setPlantTypeName(QString inputName);

 //   void setIdealTemp(int inputTemp);
 //   void setIdealLight(int inputLight);
 //   void setIdealMoisture(int inputMoisture);
 //   void setIdealHumidity(int inputHumidity);

private:
    QString plantTypeName;

    int idealTemp;
    int idealLight;
    int idealMoisture;
    int idealHumidity;

};

#endif // PLANTPROFILE_H
