#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class SEMAFORO:public Adafruit_NeoPixel{
  private:

    int estado_semaforo;
    uint8_t dir_Verde;
    uint8_t dir_Amarillo;
    uint8_t dir_Rojo;
    uint16_t time_Verde;
    uint16_t time_Amarillo;
    uint16_t time_Rojo;
    unsigned long tiempoInicio_1;
    unsigned long tiempoActual;
    Adafruit_NeoPixel pixels;
    

  public:
    
    SEMAFORO(uint8_t dir_Verde,uint8_t dir_Amarillo,uint8_t dir_Rojo, uint16_t time_Verde, uint16_t time_Amarillo, uint16_t time_Rojo);
    void sem(unsigned long tiempoActual);
    int estado_r();
    unsigned long tiempo();
};

class SEMAFORO_DOBLE:public Adafruit_NeoPixel{
  private:

    int estado_semaforo_2;
    uint8_t dir_Verde_1;
    uint8_t dir_Verde_2;
    uint8_t dir_Amarillo_1;
    uint8_t dir_Amarillo_2;
    uint8_t dir_Rojo_1;
    uint8_t dir_Rojo_2;
    uint16_t time_Verde_1;
    uint16_t time_Verde_2;
    uint16_t time_Amarillo_1;
    uint16_t time_Amarillo_2;
    unsigned long tiempoInicio_2;
    unsigned long tiempoActual;
    Adafruit_NeoPixel pixels;
    

  public:
    
    SEMAFORO_DOBLE(uint8_t dir_Verde_1,uint8_t dir_Verde_2, uint8_t dir_Amarillo_1, uint8_t dir_Amarillo_2, uint8_t dir_Rojo_1, uint8_t dir_Rojo_2, uint16_t time_Verde_1, uint16_t time_Verde_2, uint16_t time_Amarillo_1, uint16_t time_Amarillo_2);
    void semaforo_doble(unsigned long tiempoActual);
    
};
#endif