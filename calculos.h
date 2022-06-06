#include <math.h>

#ifndef NAMESPACE_CALCULOS
#define NAMESPACE_CALCULOS

#define foreach(COUNTER_INDEX, COUNTER_END) for(int COUNTER_INDEX = 0; COUNTER_INDEX < COUNTER_END; COUNTER_INDEX++)


namespace calculos {

const int N_MAX_LECS = 200, N = N_MAX_LECS;

class Magnitud {
  protected:
  byte t;
  double escala;
  int lecturas[N];
  
  public:
  /*
    @param escala el valor maximo en rms para los datos
  */
  Magnitud(int escala = 5) {
    t = 0;
    this->escala = escala * M_SQRT2;
  }
  
  // transforma un valor en bits al valor medido como magnitud fisica
  double magnitud(int bits) {
    return escala * bits / 1024.0;
  }
  
  // guarda un valor en el array
  void leer(int bits) {
    lecturas[t++] = bits;
    
    if(t == N) t = 0;
  }
  
  double valorRMS() {
    double ms = 0;
    
    foreach(i, N)
      ms += pow(lecturas[i], 2) / N;
    
    return magnitud(sqrt(ms));
  }
  
  int operator [] (int i) {
    return magnitud(lecturas[i]);
  }
  
  /*
    cambia la escala máxima de medición (evite su uso)
    @param escala el valor maximo en rms para los datos
  */
  void setEscala(int escala) {
    this->escala = escala * M_SQRT2;
  }
};

}

#endif
