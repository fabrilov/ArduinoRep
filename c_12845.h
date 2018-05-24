/*
  LBA
*/
// 

#ifndef C_12845_H
#define C_12845_H


#include "evo.h"


// #define C_12845_DEBUG true

#ifdef C_12845_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif



#define WIDGET_DISABLED "\"d\""
#define WIDGET_HIDDEN "\"h\""

// definizione grandezza del buffer dove sono memomorizzati i dati estratti letti da modBus
#define TOTAL_N_OF_REG_C 100 
  
// definizione del numero massimo di parametri 
#define MAX_PARAMETERS_FROM_CS 10  



// valore non letto da modbus, questo valore viene anche letto quando il dato modbus non ï¿½ valido
#define NOT_READ_VALUE   0x7FFF
#define NOT_READ_VALUE_1 0xFFFF


// valore che si mette sul buffer per invalidare una lettura da modbus
// Il sistema puï¿½ essere migliorato, non memorizzando il vecchio valore, ma memorizzando solo se ï¿½ cambiato.
#define NOT_VALID_VALUE INFINITY

// stringa che si invia nel caso il valore letto non sia valido
#define STRING_NOT_VALID_VALUE "null"

// delay tra 2 burst di letture.
// se velocita superiore a 9600
#define DELAY_BETWEEN_READS 2000

// se velocitÃ  Ã¨ 4800
// #define DELAY_BETWEEN_READS 4000
// definizione separatore fr
#define SEPARATORE "/"

class C_12845 : public EvoClass {
  public:

  C_12845();
// funzioni virtuali redifinite
  virtual void begin(uint8_t, ModbusMaster*);	// void begin(uint8_t _slave_id, ModbusMaster *Nodo);
  virtual bool aggiornaStato();					// legge tutti i registri definiti dallo slave
  virtual String processCommand(String);		// elabora e risponde ad un comando del DAB CS o del sito web
  ~C_12845();									// distruttore

private:
  void condizionamentoDati();								//Condizionamento dati leddi dal modbus e memorizzari in _parametri
  int	  regs[TOTAL_N_OF_REG_C];						//  array con i dati letti
  // int old_regs[TOTAL_N_OF_REG_C];			  //  array con i vecchi valori letti dal modbus
  int _delay_between_reads;	
  const String  label_for_cs[TOTAL_N_OF_REG_C] PROGMEM = {				
	"WorkMinutes","WorkHours","BatteryVoltageA","BatteryVoltageB","BatteryCurrentA","BatteryCurrentB","RPM","OilPressure","WaterT","DieselLevel",
     "","","OilTemperature","PartialHours","PartialMinutes"};
     
	const int Mreg_for_cs[TOTAL_N_OF_REG_C] = {				
	   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	};
  
	
	
	//  registri modbus da leggere, sono tutti contigui, quindi basta dare id partenza, quanti sono e dove metterli
	//  Nel Pack 2 sono presenti solo 11 pacchetti da leggere, questo vale per lo small.
    //  Nella struttura dati ne sono stati previsti 17 perchï¿½ ci saranno altri parametri aggiuntivi
    //	per i dati sul detaT	
    ModBusRegistri 
		    pack_1 = {1, 15, &regs[0],&regs[0]},
            pack_2 = {64, 64 , &regs[25],&regs[25]},
            pack_3 = {201, 3, &regs[27],&regs[27]},
            pack_4 = {211, 17, &regs[30],&regs[30]},
            pack_5 = {231, 15, &regs[47],&regs[47]},
			pack_6 = {251, 9, &regs[62],&regs[62]};
  

};



#endif /* C_12485_ */

