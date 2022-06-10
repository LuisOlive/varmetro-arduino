#include <math.h>

#ifndef NAMESPACE_CALCULOS
#define NAMESPACE_CALCULOS

#define foreach(COUNTER_INDEX, COUNTER_END) for(byte COUNTER_INDEX = 0; COUNTER_INDEX < COUNTER_END; COUNTER_INDEX++)

namespace calculos {

const int N_MAX_LECS = 105, N = N_MAX_LECS;

// Guarda 200 muestrasy hace cálculos con ellas
class Magnitud {
  protected:
  byte i, i0, i1;
  int muestras[N];
  double 
    escala, 
    tiempoInicio, tiempoFin, 
    tiempoInicioCiclo, tiempoFinCiclo, 
    tiempoMuestreo,
    periodo, frecuencia,
    valorRMS
  ;  
  
  public:
  /* @param escalaRMS el valor maximo en rms para los datos */
  Magnitud(const int escalaRMS = 1) {
    i = 0;
    this->escala = escalaRMS * M_SQRT2;
  }
  
  // transforma un valor en bits al valor medido como magnitud fisica
  double magnitud(const int bits) {
    return escala * (bits - 512) / 512.0;
  }
  
  // guarda un valor en el array
  void tomarMuestra(const double tiempoMuestra, const int bits) {
    if(!i) tiempoInicio = tiempoMuestra;
    
    muestras[i++] = bits;
    
    if(i == N) {
      i = 0;
      tiempoFin = tiempoMuestra;//Serial.println(tiempoFin);
    }
  }
  
  // calcula los valores y los alamacena para liberar
  void analizar() {
    calcularTiempos();
    calcularValorRMS();
  }
  
  /* calcula el indice proximo en el que las funciones cruzan por 0
    esta funcion encontrara x0 entre 2 indices, el primero es menor a 0 y el segundo mayor.
    el método interpolar permitirá obtener el valor en tiempo.
    @param i0 inidice inicial desde el cual empezar a contar
    @returns el valor del indice con el valor ANTES del cruce */
  byte buscarIndiceCrucePorCero(byte i = 0) {
    for(; i < N - 1; i++)
      //Serial.println(muestras[i]);
      if(muestras[i] <= 512 && muestras[i + 1] > 512)
        return i;
  }
  
  /* devuelve el valor decimal estimado para obtener la raiz del seno que cruza */
  double interpolar(const byte i) {
    double x0 = getValor(i), x1 = getValor(i + 1);
    
    return i - x1 / (x1 - x0);
  }
  
  double getTiempoAPosicion(const double i) {
    return tiempoMuestreo * i / N;
  }
  
  double getValorRMS() { return valorRMS; }
  double getFrecuencia() { return frecuencia; }
  double getPeriodo() { return periodo; }
  double getTiempoInicio() { return tiempoInicio; }
  double getTiempoFin() { return tiempoFin; }
  double getTiempoInicioCiclo() { return tiempoInicioCiclo; }
  double getTiempoFinCiclo() { return tiempoFinCiclo; }
  double getTiempoMuestreo() { return tiempoMuestreo; }
  
  // recalcula el valor RMS de las muestras de la onda
  void calcularValorRMS() {
    double ms = 0;
    
    for(int i = i0; i < i1; i++)
      ms += pow(getValor(i), 2) / N;
    
    valorRMS = sqrt(ms);
  }
  
  void calcularTiempos() {
    tiempoMuestreo = tiempoFin - tiempoInicio;
    
    i0 = buscarIndiceCrucePorCero();
    i1 = buscarIndiceCrucePorCero(i0 + 1);
      
    tiempoInicioCiclo = getTiempoAPosicion(i0);
    tiempoFinCiclo = getTiempoAPosicion(i1);
    
    periodo = tiempoFinCiclo - tiempoInicioCiclo;
    frecuencia = 1 / periodo;
  }
    
  // @returns el valor leído como magnitud fisica
  double getValor(byte i) {
    return magnitud(muestras[i]);
  }
  
  // @returns el valor leído como magnitud fisica
  double operator [] (byte i) {
    return getValor(i);
  }
  
  /* cambia la escala máxima de medición (evite su uso)
    @param escala el valor maximo en rms para los datos */
  void setEscala(int escala) {
    this->escala = escala * M_SQRT2;
  }

  /* plantilla para imprimir datos */
  void estado(const char* magnitud, const double valor, const char* unidad = "") {
    Serial.print(magnitud);
    Serial.print(": ");
    Serial.print(valor, 7);
    Serial.print(" ");
    Serial.println(unidad);
  }
  
  /* muestra el valor de cada variable por índice */
  void estado(const byte i, const char* nombre, const char* unidad) {
    Serial.print(nombre);
    
    Serial.print(" [");
    Serial.print(i);
    Serial.print("]: ");
    
    Serial.print(getValor(i), 7);
    Serial.println(unidad);
  }
  
  /* muestra el resumen de las mediciones */
  void estado(const char* nombre, const char* unidad = "") {
    Serial.println(nombre);
    
    estado("Valor RMS", valorRMS, unidad);
    estado("Tiempo inicial", tiempoInicio * 1000, "mseg");
    estado("Tiempo final", tiempoFin * 1000, "mseg");
    estado("Transcurrido", tiempoMuestreo * 1000, "mseg");
    
    Serial.println(i0);
    Serial.println(i1);
    estado("inicio del ciclo", tiempoInicioCiclo * 1000, "mseg");
    estado("final del ciclo", tiempoFinCiclo * 1000, "mseg");
    
    estadoCrucePorCero("Primer", i0, unidad);
    estadoCrucePorCero("Segundo", i1, unidad);
    
    estado("Periodo", periodo * 1000, "mseg");
    estado("Frecuencia", frecuencia, "Hz");
    Serial.println("");
  }
  
  void estadoCrucePorCero(const char* valorCardinal, const byte i, const char* unidad = "") {
    Serial.print(valorCardinal);
    Serial.print(" cruce por cero: ");
    printCorchetes(i, true);
    
    estado("aprox. inferior", getValor(i), unidad);
    estado("aprox. superior", getValor(i + 1), unidad);
    estado("tiempo aproximado para cruce positivo", getTiempoAPosicion(i) * 1000, "mseg");
  }
  
  void printCorchetes(const byte i, const bool saltarLinea = false) {
    Serial.print("[");
    Serial.print(i);
    Serial.print("]");
    
    if(saltarLinea) Serial.println("");
  }
};

}

#endif
