#include <Arduino.h>

#ifndef PSEUDOTIMER_H
#define PSEUDOTIMER_H
extern "C" {
  typedef void (*typefunzione)(void);
  }


class PseudoTimer {
public:
  PseudoTimer();
  PseudoTimer(unsigned long period, typefunzione funzione);
  PseudoTimer(unsigned long period);
  void start();
  void setPeriod(unsigned long  period);
  void setFunction(void(*funzione)());
  unsigned long getPeriod();
  bool test();
  bool testNoReset();
  bool testAndExecute();
	
private:
  unsigned long _last_execution;
  unsigned long _period;
  typefunzione _funzione;
	
	
};



#endif

