#include <Arduino.h>

#ifndef Parametri_H
#define Parametri_H

//#define PARAMETRI_DEBUG true

#ifdef PARAMETRI_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif



class Parametri {
public:
   Parametri();
   ~Parametri();

   int setValue(String parametro,String valore);
   int setValue(String parametro, long valore);
   int setValueWithDoubleQuote(String parametro, String valore);
   int setValueAutoQuote(String parametro, String valore);
   String getValue(String parametro);
   String getValueIJson(int i);
   int getOrdinaleParametro(String parametro);
   void resetData();
   void begin(const String* label_for_cs, int nParametri);

private:
   int _nParametri;
   const String * _label_for_cs;
   String * _value_for_cs;
};


#endif

