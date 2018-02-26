#ifndef PLANT_H
#define PLANT_H


class plant
{
public:
    plant(idealTemp, idealLight,idealSoilMoisture, idealAirHum);
    void setIdealTemp(int newT);
    void setIdealLight(int newL);
    void setIdealSoilMoisture(int newM);
    void setIdealAirHum(int newH);
    int getIdealTemp();
    int getIdealLight();
    int getIdealSoilMoisture();
    int getIdealAirHum();


private:
    int idealTemp;
    int idealLight;
    int idealSoilMoisture;
    int idealAirHum;

};

#endif // PLANT_H
