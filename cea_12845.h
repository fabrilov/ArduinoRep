#ifndef CEA_12845_H
#define CEA_12845_H


#include "c_12845.h"
#define TOTAL_N_OF_REG_CEA 100
#define DELAY_BETWEEN_READS 2500 


//#define CEA_12845_DEBUG true

#ifdef CEA_12845_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif



class CEA_12845 :
	public EvoClass
{
public:
	CEA_12845();
	virtual void begin(uint8_t, ModbusMaster*);	//void begin(uint8_t _slave_id, ModbusMaster *Nodo);
	virtual bool  aggiornaStato();						// legge tutti i registri definiti dallo slave
//	String processCommand(String message); 
	~CEA_12845();                     // distruttore


private:
	void condizionamentoDati();
	int	regs[TOTAL_N_OF_REG_CEA];							//  array con i dati letti
	int old_regs[TOTAL_N_OF_REG_CEA];						//  array con i vecchi valori letti dal modbus
	int _delay_between_reads;
	const String  label_for_cs[TOTAL_N_OF_REG_CEA] PROGMEM = {
		"WorkHours","V1Rms","V2Rms","V3Rms", "I1Rms", "I2Rms", "I3Rms", "CosPhi1", "CosPhi2", "CosPhi3", "FrequenzaRete","PotenzaApparente", "PotenzaAttiva", "PotenzaReattiva","","","","","",
		"V12Concatenata","V23Concatenata","V31Concatenata","WorkMinutes","","ParzialeMinutiPompa",
		"","","PartialHours","PartialMinutes" };

	const int Mreg_for_cs[TOTAL_N_OF_REG_CEA] = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24
	};



	//  registri modbus da leggere, sono tutti contigui, quindi basta dare id partenza, quanti sono e dove metterli
	//  Nel Pack 2 sono presenti solo 11 pacchetti da leggere, questo vale per lo small.
	//  Nella struttura dati ne sono stati previsti 17 perchè ci saranno altri parametri aggiuntivi
	//	per i dati sul detaT	
	ModBusRegistri
		pack_1 = { 1, 24, &regs[0],&old_regs[0] },
		pack_2 = { 32, 47 , &regs[25],&old_regs[25] },
		pack_3 = { 201, 3, &regs[27],&old_regs[27] },
		pack_4 = { 211, 17, &regs[30],&old_regs[30] },
		pack_5 = { 231, 15, &regs[47],&old_regs[47] },
		pack_6 = { 251, 9, &regs[62],&old_regs[62] };


};


#endif /* CEA_12485_ */