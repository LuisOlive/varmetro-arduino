#include "calculos.h"

#ifndef NAMESPACE_VARMETRO
#define NAMESPACE_VARMETRO

namespace varmetro {

#define varmetro_foreach(VARMETRO_COUNTER_INDEX) for(int VARMETRO_COUNTER_INDEX=0; VARMETRO_COUNTER_INDEX < calculos::N_MAX_LECS; VARMETRO_COUNTER_INDEX++)

class Varmetro {
  protected:
  
  bool estaAnalizando;
  int t;
  calculos::Magnitud voltajes, corrientes;
  double escalaVoltaje, escalaCorriente;
  
  double
    anguloFase,
    corriente,
    factorPotencia,
    frecuencia,
    potenciaActiva,
    potenciaAparente,
    potenciaReactiva,
    tiempoFase,
    voltaje;
    
  public:
  
  Varmetro(const int escalaVoltaje = 5, const int escalaCorriente = 5) {
    voltajes.setEscala(escalaVoltaje);
    corrientes.setEscala(escalaCorriente);
    estaAnalizando = false;
  }
  
  // Guarda valores de tensión y corriente en bits (0 - 1023)
  void tomarMuestras(const double tiempoMuestra, const int bitsVoltaje, const int bitsCorriente) {
    if(estaAnalizando) return;
    
    voltajes.tomarMuestra(tiempoMuestra, bitsVoltaje);
    corrientes.tomarMuestra(tiempoMuestra, bitsCorriente);
  }
  
  void analizar() {
    estaAnalizando = true;
    
    voltajes.analizar();
    corrientes.analizar();
    
    voltaje = voltajes.getValorRMS();
    corriente = corrientes.getValorRMS();
    
    frecuencia = (voltajes.getFrecuencia() + corrientes.getFrecuencia()) / 2;
    
    tiempoFase = voltajes.getTiempoInicioCiclo() - corrientes.getTiempoInicioCiclo();    
    anguloFase = 2 * PI * tiempoFase; // radianes
    
    potenciaAparente = voltaje * corriente;
    factorPotencia = cos(anguloFase);
    potenciaActiva = potenciaAparente * factorPotencia;
    potenciaReactiva = potenciaAparente * sin(anguloFase);
  }
  
  void estado(const byte i) {
    voltajes.estado(i, "Voltaje", "V");
    corrientes.estado(i, "Corriente", "A");
    Serial.println("");
  }
  
  void estado() {
    voltajes.estado("Voltaje", "V");
    corrientes.estado("Corriente", "A");
    
    estado("Voltaje", voltaje, "V");
    estado("Corriente", corriente, "A");
    estado("Frecuencia", frecuencia, "Hz");
    
    estado("Angulo de fase", anguloFase * RAD_TO_DEG, "deg");
    estado("Factor de potencia", factorPotencia);
    
    estado("Potencia aparente", potenciaAparente, "VA");
    estado("Potencia activa", potenciaActiva, "W");
    estado("Potencia reactiva", potenciaReactiva, "VAr");
  }
  
  void estado(char* magnitud, double valor, char* unidad = "") {
    Serial.print(magnitud);
    Serial.print(": ");
    Serial.print(valor, 7);
    Serial.print(" ");
    Serial.println(unidad);
  }
};

}

#endif
