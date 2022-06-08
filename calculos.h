#include <math.h>

#ifndef NAMESPACE_CALCULOS
#define NAMESPACE_CALCULOS

#define foreach(COUNTER_INDEX, COUNTER_END) for(byte COUNTER_INDEX = 0; COUNTER_INDEX < COUNTER_END; COUNTER_INDEX++)

namespace calculos {

const int N_MAX_LECS = 105, N = N_MAX_LECS;

// Guarda 200 muestrasy hace cálculos con ellas
class Magnitud {
  protected:
  byte i;
  double escala, tiempoInicio, tiempoFin;
  int muestras[N];
  
  public:
  /* @param escala el valor maximo en rms para los datos */
  Magnitud(const int escala = 1) {
    i = 0;
    this->escala = escala * M_SQRT2;
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
      tiempoFin = tiempoMuestra;Serial.println(tiempoFin);
    }
  }
  
  /* calcula el indice proximo en el que las funciones cruzan por 0
    esta funcion encontrara x0 entre 2 indices, el primero es menor a 0 y el segundo mayor.
    el método interpolar permitirá obtener el valor en tiempo.
    @param i0 inidice inicial desde el cual empezar a contar
    @returns el valor del indice con el valor ANTES del cruce */
  byte indiceCrucePorCero(const byte i0 = 0) {
    for(byte i = i0; i < N - 1; i++)
      //Serial.println(muestras[i]);
      if(muestras[i] <= 512 && muestras[i + 1] > 512)
        return i;
        
    return 100;
  }
  
  /* devuelve el valor decimal estimado para obtener la raiz del seno que cruza */
  double interpolar(const byte i) {
    double x0 = magnitud(muestras[i]), x1 = magnitud(muestras[i + 1]);
    
    return i - x1 / (x1 - x0);
  }
  
  double posicionATiempo(const double i) {
    return getTiempoMuestreo() * i / N;
  }
  
  // calcula el valor en rms de las muestras
  double valorRMS() {
    double ms = 0;
    
    foreach(i, N)
      ms += pow(muestras[i], 2) / N;
    
    return magnitud(sqrt(ms));
  }
  
  // calcula el promedio en un array
  double promedio(double arr[], byte lim) {
    double res = 0;
    
    foreach(i, lim)
      res += arr[i] / lim;
      
    return res;
  }
  
  // @returns el valor leído como magnitud fisica
  int operator [] (byte i) {
    return magnitud(muestras[i]);
  }
  
  /* cambia la escala máxima de medición (evite su uso)
    @param escala el valor maximo en rms para los datos */
  void setEscala(int escala) {
    this->escala = escala * M_SQRT2;
  }

  /* @returns el tiempo de inicio de muestreo en segundos */
  double getTiempoInicio() {
    return tiempoInicio;
  }
  
  /* @returns el tiempo final de muestreo en segundos */
  double getTiempoFin() {
    return tiempoFin;
  }

  /* @returns el tiempo de muestreo en segundos */
  double getTiempoMuestreo() {
    return tiempoFin - tiempoInicio;
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
    
    Serial.print(magnitud(muestras[i]), 7);
    Serial.println(unidad);
  }
  
  /* muestra el resumen de las mediciones */
  void estado(const char* nombre, const char* unidad = "") {
    Serial.println(nombre);
    
    estado("Valor RMS", valorRMS(), unidad);
    estado("Tiempo inicial", tiempoInicio, "seg");
    estado("Tiempo final", tiempoFin, "seg");
    estado("Transcurrido", getTiempoMuestreo(), "seg");
    
    auto i0 = estadoCrucePorCero("Primer", 0, unidad);
    estadoCrucePorCero("Segundo", i0 + 1, unidad);
    
    Serial.println("");
  }
  
  byte estadoCrucePorCero(const char* valorCardinal, const byte i0 = 0, const char* unidad = "") {
    const byte i = indiceCrucePorCero(i0);
    const double t = posicionATiempo(interpolar(i));
    
    Serial.print(valorCardinal);
    Serial.print(" cruce por cero: ");
    printCorchetes(i, true);
    
    estado("aprox. inferior", magnitud(muestras[i]), unidad);
    estado("aprox. superior", magnitud(muestras[i + 1]), unidad);
    estado("tiempo aproximado para cruce positivo", t, "seg");
    
    return i;
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
