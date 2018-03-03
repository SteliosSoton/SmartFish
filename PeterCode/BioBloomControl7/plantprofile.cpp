#include "plantprofile.h"

PlantProfile::PlantProfile(QString inputName, int inputTemp, int inputLight, int inputMoisture, int inputHumidity) : plantTypeName(inputName),
                                                                                                                     idealTemp(inputTemp),
                                                                                                                     idealLight(inputLight),
                                                                                                                     idealMoisture(inputMoisture),
                                                                                                                     idealHumidity(inputHumidity)
                                                                                                                     {}
