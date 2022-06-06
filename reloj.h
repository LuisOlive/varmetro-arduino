#ifndef NAMESPACE_RELOJ
#define NAMESPACE_RELOJ

namespace reloj {
// const byte adcPin = 0;  // A0

// const int MAX_RESULTS = 64*5;

// volatile int results[MAX_RESULTS];

// volatile int resultNumber;

// // ADC complete ISR
// ISR(ADC_vect) {
//   if (resultNumber >= MAX_RESULTS) {
//     resultNumber = 0;
//     //ADCSRA = 0;  // turn off ADC
//   } else {
//     results[resultNumber++] = ADC;
//   }
// }
  
EMPTY_INTERRUPT(TIMER1_COMPB_vect);

void begin() {
  Serial.println("Reloj initialized");
  //  // reset Timer 1
  // TCCR1A = 0;
  // TCCR1B = 0;
  // TCNT1 = 0;
  // TCCR1B = bit(CS11) | bit(WGM12);  // CTC, prescaler of 8
  // TIMSK1 = bit(OCIE1B);
  // OCR1A = 520;    
  // OCR1B = 520;   // 20 uS - sampling frequency 50 kHz [1 / (62.5e-9 * 8 * OCR1B+1) = 50000 Hz]

  // ADCSRA =  bit(ADEN) | bit(ADIE) | bit(ADIF);   // turn ADC on, want interrupt on completion
  // //ADCSRA |= bit(ADPS2);  // Prescaler of 16
  // //ADCSRA |= bit(ADPS2) | bit(ADPS0); //Prescaler of 32
  // //ADCSRA |= bit(ADPS0) | bit(ADPS1) | bit(ADPS2);   // 128
  // ADMUX = bit(REFS0) | (adcPin & 7);
  // ADCSRB = bit(ADTS0) | bit(ADTS2);  // Timer/Counter1 Compare Match B
  // ADCSRA |= bit(ADATE);   // turn on automatic triggering
}

}

#endif
