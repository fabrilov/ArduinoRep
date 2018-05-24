/*
  LBA
*/
// 

#ifndef Evo_H
#define Evo_H

#include <Arduino.h>
#include "ModbusMaster.h"
#include "Parametri.h"
#include "Dum.h"


//#define EVO_DEBUG true

#ifdef EVO_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif



#define WIDGET_DISABLED "\"d\""
#define WIDGET_HIDDEN "\"h\""

// definizione grandezza del buffer dove sono memomorizzati i dati estratti letti da modBus
#define TOTAL_N_OF_REG_EVO 72  
  
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

class EvoClass : public Dum {
  public:
	EvoClass();
// funzioni virtuali redifinite

	virtual void begin(uint8_t,ModbusMaster*);
	virtual bool aggiornaStato();							// legge tutti i registri definiti dallo slave
	String processCommand(String);                  // elabora e risponde ad un comando del DAB CS o del sito web

// funzione pubbliche della classe

	void change_slave_id(uint8_t);
	int write(uint16_t,uint16_t); 
	int read_slave_id();
	int read_data_to_slave(uint16_t);
	~EvoClass(); 											// distruttore
  protected:

	bool dato_ok = false;									// variabile per indicare se il dato ï¿½ ok 
	ModbusMaster *Modbus;									//  puntatore alla classe ModbusMaster che gestisce il modbus
	//struct name_Mreg {
	//			String name;
	//			int Mreg;
	//};
  
	uint8_t slave_id;										//  Variabile con l'indirizzo dello slave   
	
	struct ModBusRegistri {
		const unsigned int base;
		const unsigned int n_dati;
		int *regs;
		int *old_regs;
     };
    

private:
	void condizionamentoDati();								//Condizionamento dati leddi dal modbus e memorizzari in _parametri
	int _delay_between_reads;
	const String label_for_cs[TOTAL_N_OF_REG_EVO] PROGMEM = {				
	"Slave Minimum Reply delay","Modbus address","Modbus baud rate","Modbus Parity Bit","Modbus Stop Bit","",
	   "","","Regulation mode","Regulation Setpoint","Regulation T Max","Economy","Economy Setpoint Reduction","Ext signal type","Twin type","Setpoint RPM",
	   "Enable","","","","","","","","","","",
	   "","Pump Status","Fault Status",
	   "Board Temperature","Heatsink Temperature","Line Voltage","Current","","RPM","Power","Run time Pump","","Read Head","Estimated Flow","Liquid Temperature",
	"Liquid Temperature 2","","","","",
	"Last Error","Error - 1","Error - 2","Error - 3","Error - 4","Error - 5","Error - 6","Error - 7","Error - 8","Error - 9","Error - 10","Error - 11","Error - 12","Error - 13","Error - 14",
	"Low Voltage Software version","","High Voltage Software version","","Kernel Version","","Unit Family","Unit type","Unit Version"};
	
	const int Mreg_for_cs[TOTAL_N_OF_REG_EVO] = {				
	   1,2,3,4,5,0,
	   0,0,103,104,105,106,107,108,109,110,111,0,0,0,0,0,0,0,0,0,0,
	   0,202,203,
	   211,212,213,214,0,216,217,218,0,220,221,222,223,0,0,0,0,
	   231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,
	   251,0,253,0,255,0,257,258,259};
	

  int regs[TOTAL_N_OF_REG_EVO];               //  array con i dati letti
  int old_regs[TOTAL_N_OF_REG_EVO];           //  array con i vecchi valori letti dal modbus

	//  registri modbus da leggere, sono tutti contigui, quindi basta dare id partenza, quanti sono e dove metterli
	//  Nel Pack 2 sono presenti solo 11 pacchetti da leggere, questo vale per lo small.
    //  Nella struttura dati ne sono stati previsti 17 perchï¿½ ci saranno altri parametri aggiuntivi
    //	per i dati sul detaT	
    ModBusRegistri 
		        pack_1 = {1, 6, &regs[0],&old_regs[0]},
                pack_2 = {101, 11, &regs[6],&old_regs[6]},
                pack_3 = {201, 3, &regs[27],&old_regs[27]},
                pack_4 = {211, 17, &regs[30],&old_regs[30]},
                pack_5 = {231, 15, &regs[47],&old_regs[47]},
				pack_6 = {251, 9, &regs[62],&old_regs[62]};
  

	// funzioni private

};



#endif /* evo_1_H_ */

