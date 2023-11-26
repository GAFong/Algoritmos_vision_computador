#include "SEMAFORO.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


SEMAFORO::SEMAFORO(uint8_t dir_Verde,uint8_t dir_Amarillo,uint8_t dir_Rojo, uint16_t time_Verde, uint16_t time_Amarillo, uint16_t time_Rojo){
  this->dir_Verde = dir_Verde;
  this->dir_Amarillo = dir_Amarillo;
  this->dir_Rojo = dir_Rojo;
  this-> time_Verde = time_Verde;
  this-> time_Amarillo = time_Amarillo;
  this-> time_Rojo = time_Rojo;
  pixels = Adafruit_NeoPixel(99, 6, NEO_GRB + NEO_KHZ800);
  pixels.begin();
}

void SEMAFORO::sem(unsigned long tiempoActual){
  

  switch (estado_semaforo) {
    case 0: // Verde
      pixels.setPixelColor(dir_Verde, 0, 255, 0);       //Luz verde encendida
      pixels.setPixelColor(dir_Amarillo, 0, 0, 0);    //Luz amarilla apagada
      pixels.setPixelColor(dir_Rojo, 0, 0, 0);    //Luz roja apagada
      pixels.show();
      if ((tiempoActual - tiempoInicio_1) > time_Verde) {
        estado_semaforo = 1; // Cambiar a amarillo
        tiempoInicio_1 = tiempoActual;
      }
      break;

    case 1: // Amarillo
      pixels.setPixelColor(dir_Verde, 0, 0, 0);       //Luz verde apagada
      pixels.setPixelColor(dir_Amarillo, 15, 15, 0);    //Luz amarilla encendida
      pixels.setPixelColor(dir_Rojo, 0, 0, 0);    //Luz roja apagada
      pixels.show();
      if ((tiempoActual - tiempoInicio_1) > time_Amarillo) {
        tiempoInicio_1 = tiempoActual;
        estado_semaforo = 2; // Cambiar a rojo
      }
      break;
      
    case 2: // Rojo
      pixels.setPixelColor(dir_Verde, 0, 0, 0);       //Luz verde apagada
      pixels.setPixelColor(dir_Amarillo, 0, 0, 0);    //Luz amarilla apagada
      pixels.setPixelColor(dir_Rojo, 15, 0, 0);    //Luz roja encendida
      pixels.show();
      if (tiempoActual - tiempoInicio_1 >= time_Rojo) {
        tiempoInicio_1 = tiempoActual;
        estado_semaforo = 0; // Cambiar a verde
      }
      break;
  }

}


SEMAFORO_DOBLE::SEMAFORO_DOBLE(uint8_t dir_Verde_1,uint8_t dir_Verde_2, uint8_t dir_Amarillo_1, uint8_t dir_Amarillo_2, uint8_t dir_Rojo_1, uint8_t dir_Rojo_2, uint16_t time_Verde_1, uint16_t time_Verde_2, uint16_t time_Amarillo_1,uint16_t time_Amarillo_2){
  this->dir_Verde_1 = dir_Verde_1;
  this->dir_Verde_2 = dir_Verde_2;
  this->dir_Amarillo_1 = dir_Amarillo_1;
  this->dir_Amarillo_2 = dir_Amarillo_2;
  this->dir_Rojo_1 = dir_Rojo_1;
  this->dir_Rojo_2 = dir_Rojo_2;
  this-> time_Verde_1 = time_Verde_1;
  this-> time_Verde_2 = time_Verde_2;
  this-> time_Amarillo_1 = time_Amarillo_1;
  this-> time_Amarillo_2 = time_Amarillo_2;
  pixels = Adafruit_NeoPixel(99, 6, NEO_GRB + NEO_KHZ800);
  pixels.begin();
}



void SEMAFORO_DOBLE::semaforo_doble(unsigned long tiempoActual){
  int estadoSemaforo2;
  // Verificar si ha pasado el intervalo de 5 segundos
  switch (estado_semaforo_2) {
    case 0: // Verde semaforo 1
      pixels.setPixelColor(dir_Verde_1, 0, 255, 0);       //Luz verde encendida sem 1
      pixels.setPixelColor(dir_Amarillo_1, 0, 0, 0);    //Luz amarilla apagada sem 1
      pixels.setPixelColor(dir_Rojo_1, 0, 0, 0);        //Luz roja apagada sem 1
      pixels.setPixelColor(dir_Verde_2, 0, 0, 0);       //Luz verde apagada sem 2
      pixels.setPixelColor(dir_Amarillo_2, 0, 0, 0);    //Luz amarilla apagada sem 2
      pixels.setPixelColor(dir_Rojo_2, 15, 0, 0);       //Luz roja encendida sem 2
      pixels.show();
      if (tiempoActual - tiempoInicio_2 >= time_Verde_1) {
        tiempoInicio_2 = tiempoActual;
        estado_semaforo_2 = 1; // Cambiar a amarillo
      }
      break;

    case 1: // Amarillo semaforo 1
      pixels.setPixelColor(dir_Verde_1, 0, 0, 0);        //Luz verde apagada sem 1
      pixels.setPixelColor(dir_Amarillo_1, 15, 15, 0);   //Luz amarilla encendida sem 1
      pixels.setPixelColor(dir_Rojo_1, 0, 0, 0);         //Luz roja apagada sem 1
      pixels.setPixelColor(dir_Verde_2, 0, 0, 0);       //Luz verde apagada sem 2
      pixels.setPixelColor(dir_Amarillo_2, 0, 0, 0);    //Luz amarilla apagada sem 2
      pixels.setPixelColor(dir_Rojo_2, 15, 0, 0);       //Luz roja encendida sem 2
      pixels.show();
      if (tiempoActual - tiempoInicio_2 >= time_Amarillo_1) {
        tiempoInicio_2 = tiempoActual;
        estado_semaforo_2 = 2; // Cambiar a rojo
      }
      break;

    case 2: // Verde semaforo 2
      pixels.setPixelColor(dir_Verde_1, 0, 0, 0);       //Luz verde apagada
      pixels.setPixelColor(dir_Amarillo_1, 0, 0, 0);    //Luz amarilla apagada
      pixels.setPixelColor(dir_Rojo_1, 15, 0, 0);     //Luz roja encendida
      pixels.setPixelColor(dir_Verde_2, 0, 15, 0);       //Luz verde encendida sem 2
      pixels.setPixelColor(dir_Amarillo_2, 0, 0, 0);    //Luz amarilla apagada sem 2
      pixels.setPixelColor(dir_Rojo_2, 0, 0, 0);       //Luz roja apagada sem 2
      pixels.show();
      if (tiempoActual - tiempoInicio_2 >= time_Verde_2) {
        tiempoInicio_2 = tiempoActual;
        estado_semaforo_2 = 3; // Cambiar a amarillo semaforo 2
      }
      break;

    case 3: // Amarillo semaforo 2
      pixels.setPixelColor(dir_Verde_1, 0, 0, 0);       //Luz verde apagada
      pixels.setPixelColor(dir_Amarillo_1, 0, 0, 0);    //Luz amarilla apagada
      pixels.setPixelColor(dir_Rojo_1, 15, 0, 0);      //Luz roja encendida
      pixels.setPixelColor(dir_Verde_2, 0, 0, 0);       //Luz verde encendida sem 2
      pixels.setPixelColor(dir_Amarillo_2, 15, 15, 0);  //Luz amarilla apagada sem 2
      pixels.setPixelColor(dir_Rojo_2, 0, 0, 0);       //Luz roja apagada sem 2
      pixels.show();
      if (tiempoActual - tiempoInicio_2 >= time_Amarillo_2) {
        tiempoInicio_2 = tiempoActual;
        estado_semaforo_2 = 0; // Cambiar a verde semaforo 1
      }
      break;
  }
}

