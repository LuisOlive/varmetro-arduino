#include "calculos.h"

#ifndef NAMESPACE_VARMETRO
#define NAMESPACE_VARMETRO

namespace varmetro {

#define varmetro_foreach(VARMETRO_COUNTER_INDEX) for(int VARMETRO_COUNTER_INDEX=0; VARMETRO_COUNTER_INDEX < calculos::N_MAX_LECS; VARMETRO_COUNTER_INDEX++)

class Varmetro {
  protected:
  
  int t;
  calculos::Magnitud voltajes, corrientes;
  double escalaVoltaje, escalaCorriente;
    
  public:
  
  Varmetro(const int escalaVoltaje = 5, const int escalaCorriente = 5) {
    voltajes.setEscala(escalaVoltaje);
    corrientes.setEscala(escalaCorriente);
  }
  
  // Guarda valores de tensión y corriente en bits (0 - 1023)
  void tomarMuestras(const double tiempoMuestra, const int bitsVoltaje, const int bitsCorriente) {
    // Serial.println(tiempoMuestra, 8); // bien
    voltajes.tomarMuestra(tiempoMuestra, bitsVoltaje);
    corrientes.tomarMuestra(tiempoMuestra, bitsCorriente);
  }
  
  void estado(const byte i) {
    voltajes.estado(i, "Voltaje", "V");
    corrientes.estado(i, "Corriente", "A");
    Serial.println("");
  }
  
  void estado() {
    voltajes.estado("Voltaje", "V");
    corrientes.estado("Corriente", "A");
  }
  
  void estado(double valor, char* magnitud, char* unidad) {
    Serial.print(magnitud);
    Serial.print(": ");
    Serial.print(valor, 7);
    Serial.print(" ");
    Serial.println(unidad);
  }
};

}

#endif
