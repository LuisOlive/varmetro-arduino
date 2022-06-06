#include "calculos.h"

#ifndef NAMESPACE_VARMETRO
#define NAMESPACE_VARMETRO

namespace varmetro {
/*
  máxima cantidad de lecturas
*/
const int N_MAX_LECS = 200, N = N_MAX_LECS;

#define varmetro_foreach(VARMETRO_COUNTER_INDEX) for(int VARMETRO_COUNTER_INDEX=0; VARMETRO_COUNTER_INDEX < varmetro::N_MAX_LECS; VARMETRO_COUNTER_INDEX++)

class Varmetro {
  protected:
  
  int t;
  calculos::Magnitud voltajes, corrientes;
  double escalaVoltaje, escalaCorriente;
    
  public:
  
  Varmetro(int escalaVoltaje = 5, int escalaCorriente = 5) {
    voltajes.setEscala(escalaVoltaje);
    corrientes.setEscala(escalaCorriente);
  }
  
  // Guarda valores de tensión y corriente en bits (0 - 1023)
  void leer(const int V, const int I) {
    voltajes.leer(V);
    corrientes.leer(I);
  }
  
  void estado(int t) {
    estado(voltajes[t], "Voltaje", 'V');
    estado(corrientes[t], "Corriente", 'A');
    
    Serial.println("");
  }
  
  void estado() {
    estado(voltajes.valorRMS(), "Voltaje RMS", 'V');
    estado(corrientes.valorRMS(), "Corriente RMS", 'A');
    
    Serial.println("");
  }
  
  void estado(double valor, char* magnitud, char unidad) {
    Serial.print(magnitud);
    Serial.print(": ");
    Serial.print(valor, 7);
    Serial.print(" ");
    Serial.println(unidad);
  }
};

}

#endif
