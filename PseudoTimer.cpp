#include "PseudoTimer.h"


PseudoTimer::PseudoTimer(unsigned long  period, typefunzione funzione){
	
	_period = period;
	_funzione = funzione;
	_last_execution = 0;
	
}
PseudoTimer::PseudoTimer(unsigned long  period){
  
  _period = period;
  _funzione = 0x0;
  _last_execution = 0;
}

PseudoTimer::PseudoTimer(){
	_last_execution = 0;
}

void PseudoTimer::start(){
	_last_execution = millis();
}

bool PseudoTimer::testAndExecute(){
	if ((millis() - _last_execution)  > _period) {
		_last_execution = millis();
		if (_funzione != 0x0) (*_funzione)();
		return true;
	} else return false;
	
}

bool PseudoTimer::test(){
  if ((millis() - _last_execution) > _period) 
  {
	_last_execution = millis();
	return true;
  } 
  else return false;
  
}

bool PseudoTimer::testNoReset(){
if ((millis() - _last_execution) > _period)
{
		return true;
}
else return false;

}


unsigned long PseudoTimer::getPeriod(){
    return _period;
  }

void PseudoTimer::setPeriod(unsigned long period){
  _period = period;
  }  

void PseudoTimer::setFunction(void(*funzione)()){
  _funzione = funzione;}

