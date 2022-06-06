// #include <math.h>
// #include <avdweb_AnalogReadFast.h>
#include "Varmetro.h"
// #include "Reloj.h"

const float 
  frecuencia = 60, 
  fase = 30,
  // automaticos
  periodo = 1 / frecuencia,
  omega = M_2_PI * frecuencia,
  faseRd = fase * DEG_TO_RAD;

varmetro::Varmetro v(250, 15);
double t = 0;

void setup() {
  Serial.begin(115200);
  
  // títulos de la gráfica
  Serial.println("Voltaje, Corriente");
  
  // reloj::begin();
}

void loop() {
  v.leer(
    (int) 1024 * sin(omega * t),
    (int) 1024 * sin(omega * t + faseRd)
  );
  
  if (t > 0.2) {
    varmetro_foreach(i) {
      v.estado(i);
    }
    
    v.estado();    
    delay(10000);
  }
  Serial.println(t);
  t += 0.001;
}


  
