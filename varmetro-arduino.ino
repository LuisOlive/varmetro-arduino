#include "Varmetro.h"

/************** configuraciones ***************/ const float 
  frecuencia = 60, 
  fase = 48, 
  frecuenciaMuestreo = 2400, // 50 - 100 Hz legibles
  voltaje = 250, // RMS
  corriente = 5 // RMS
/*********************************************/;

// automaticos
const float 
  periodo = 1 / frecuencia, 
  omega = 2 * PI * frecuencia,
  faseRd = fase * DEG_TO_RAD,
  tiempoEspera = 1 / frecuenciaMuestreo;

varmetro::Varmetro v(voltaje, corriente);
double t = 0;
int i = 0;

void setup() {
  Serial.begin(115200);
  
  // títulos de la gráfica
  Serial.println("Voltaje, Corriente");
}

void loop() {
  v.tomarMuestras(
    t,
    (int) 512 + 512 * sin(omega * t),
    (int) 512 + 512 * sin(omega * t + faseRd)
  );
  
  if (++i == calculos::N_MAX_LECS) 
    trasLecturasTomadas();
  
  t += tiempoEspera;
}

void trasLecturasTomadas() {
  varmetro_foreach(i) { // es un for xD
    v.estado(i);
  }
  
  v.estado();    
  delay(5000);
  i = 0;
}
  
