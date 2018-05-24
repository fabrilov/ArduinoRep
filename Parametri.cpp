#include "Parametri.h"


Parametri::Parametri(){
  _label_for_cs = NULL;
  _value_for_cs = NULL;
  _nParametri=0;

};

Parametri::~Parametri(){
//delete _label_for_cs;
delete _value_for_cs;
}; 

void Parametri::begin(const  String *label_for_cs, int nParametri){

  _nParametri = nParametri;
  _label_for_cs = label_for_cs;
  if (_value_for_cs == NULL)  _value_for_cs = new String[_nParametri];
  if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
      for(int i=0; i< _nParametri; i++)  {
      //_label_for_cs[i] =label_for_cs[i];
		  if (_label_for_cs[i].length() > 0) { 
			  			  _value_for_cs[i] = ""; 
		  }
		  else _value_for_cs[i].reserve(0);
     }
  }
}

int Parametri::setValue(String parametro,String valore){
 if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
  for(int i=0; i< _nParametri; i++) {
    if (_label_for_cs[i] == parametro){
      _value_for_cs[i] = valore;
      return i;
      } 
  }
 }
  return NAN;
}

int Parametri::setValue(String parametro, long valore) {
	if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
		for (int i = 0; i< _nParametri; i++) {
			if (_label_for_cs[i] == parametro) {
				_value_for_cs[i] = String(valore);
				return i;
			}
		}
	}
	return NAN;
}

String Parametri::getValue(String parametro){

if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
    for(int i=0; i< _nParametri; i++) {
      if (_label_for_cs[i] == parametro){ return  _value_for_cs[i]; } 
    }
  }  
  return "";
}

String Parametri::getValueIJson(int i){
	String data= "";
	if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
		if (((i >= 0) && (i < _nParametri)) && ( _label_for_cs[i] != "") && (_value_for_cs[i] != ""))
			data = "\"" + _label_for_cs[i] + "\":" + _value_for_cs[i];
  	   }
	return data;
}  
  

int Parametri::getOrdinaleParametro(String parametro){

if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
  for( int i=0; i< _nParametri; i++) {
    if (_label_for_cs[i] == parametro)
	   { return i; } 
   }
  }  
 return NAN;
}



int Parametri::setValueWithDoubleQuote(String parametro, String valore) {

return  setValue(parametro, '"' + valore + '"');
}

int Parametri::setValueAutoQuote(String parametro, String valore)
{
	String valoreTrimmato = valore;
	valoreTrimmato.trim();

	if (String(valoreTrimmato.toDouble())==valoreTrimmato) return setValue(parametro,valoreTrimmato);
	else return setValueWithDoubleQuote(parametro, valoreTrimmato);

}


void Parametri::resetData() {
	if ((_label_for_cs != NULL) && (_value_for_cs != NULL)) {
		for (int i = 0; i< _nParametri; i++) {
			if (_label_for_cs[i].length() > 0) {
				_value_for_cs[i] = "";
			}
		}
		
	}

}
