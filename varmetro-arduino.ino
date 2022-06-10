#include "Varmetro.h"

/************** configuraciones ***************/ const float 
  frecuencia = 60, 
  fase = 48, 
  frecuenciaMuestreo = 3000, // 50 - 100 Hz legibles
  voltaje = 250, // RMS
  corriente = 5 // RMS
/*********************************************/;

// automaticos
const float 
  periodo = 1 / frecuencia, 
  omega = 2 * PI * frecuencia,
  faseRd = fase * DEG_TO_RAD,
  tiempoEspera = 1 / frecuenciaMuestreo;


double t = 0;
int i = 0;

varmetro::Varmetro v(voltaje, corriente);

void setup() {
  Serial.begin(115200);
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
  
  v.analizar();
  
  v.estado();  
    
  delay(3000);
  i = 0;
}
  
