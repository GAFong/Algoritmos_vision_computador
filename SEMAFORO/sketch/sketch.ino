#include <Arduino.h>
#include "SEMAFORO.h"
#include <Adafruit_NeoPixel.h>



unsigned long tiempoInicio_1 = 0;
unsigned long tiempoInicio_2 = 0;

const int16_t timeVerde_sem1 = 1000;
const int16_t timeAmarillo_sem1 = 5000;
const int16_t timeRojo_sem1 = 1000;

int16_t dirVerde_sem1 = 0;
int16_t dirAmarillo_sem1 = 1;
int16_t dirRojo_sem1 = 2;

int timeVerde_sem2 = 6000;
int timeAmarillo_sem2 = 1000;
int timeRojo_sem2 = 4000;

int16_t dirVerde_sem2 = 3;
int16_t dirAmarillo_sem2 = 4;
int16_t dirRojo_sem2 = 5;

int timeVerde_sem3 = 10000;
int timeAmarillo_sem3 = 2000;
int timeRojo_sem3 = 5000;

int16_t dirVerde_sem3 = 6;
int16_t dirAmarillo_sem3 = 7;
int16_t dirRojo_sem3 = 8;

int estadoSemaforo1 = 0;
int estadoSemaforo2 = 0;

unsigned long tiempoActual_1= 0;
unsigned long tiempoActual_2= 0;

SEMAFORO semaforo1(dirVerde_sem1,dirAmarillo_sem1,dirRojo_sem1,timeVerde_sem1, timeAmarillo_sem1,timeRojo_sem1);
//SEMAFORO semaforo2(3,4,5,6000, 3000,7000);
SEMAFORO_DOBLE semaforo_2(3,6,4,7,5,8,5000,4000,2000,1000);
void setup() {
  
  
}

void loop() {
  tiempoActual_1 = millis();
  //tiempoActual_2 = millis();
  semaforo1.sem(tiempoActual_1);
  semaforo_2.semaforo_doble(tiempoActual_1);
  //semaforo2.sem(tiempoActual_1);


}
