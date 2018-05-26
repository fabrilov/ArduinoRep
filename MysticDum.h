
#include <Arduino.h>
#include "NewBridge.h"
#include "PseudoTimer.h"
#include "Parametri.h"
#include "Dum.h"

#include <Wire.h> //per sensore 12c es. giroscopio/accelerometro
#include "DHT.h" // sensore temp. umidità DHT 22  (AM2302)

//#define SIMUL_INVIODATIFAST 120000
#define SIMUL_MAX_PARAMETERS_FROM_CS 10       // numero massimo di parametri che possono arrivare dal centro servizi                                
#define SIMUL_HIDDEN		"h"					// valore che nasconde il widget
#define SIMUL_DISABLE		"d"					// valore disabilita il widget
#define SIMUL_NONVALIDO   "-1"
#define SIMUL_STRING_NOT_VALID_VALUE "null"	// stringa che si invia nel caso il valore letto non sia valido


#define SIMUL_FILESTORAGEPARAMETRI				"/evoplus/storageConfiguration.txt"
#define SIMUL_FILESTORAGEPARAMETRIRETE			"/var/tmp/dboxInfo.txt"
//#define SIMUL_IPSCRIPT							"/evoplus/scripts/copyInfo.sh"          // non usato
#define SIMUL_PERCORSOCONFIGURAZIONE			"/evoplus/configurazione/pwmCom_1_0"
#define SIMUL_SENDLOGSH							"/evoplus/scripts/sendlog.sh"
#define SIMUL_SENDDATATICS						"to_cs_usb.sh"							// Script per l'invio dati su CS. gli script sono relativi e si trovano in /evolpus/scripts 
#define SIMUL_NOME_FILE_CS_TXT					"data_to_cs.txt"						// File che contiene i dati da inviare al CS
//#define SIMUL_NOME_FILE_TMP						"dati.tmp"								// File temporaneo che memorizza i dati per il sito locale
//#define SIMUL_NOME_FILE_DATI_TO_WEB				"data_to_cs.json"						// File definitivo dove sono memoriazzati i dati per il sito locale
#define SIMUL_MAX_CAR_TO_BRIDGE 250											// numero massimo di caratteri che possono arrivare dal Bridge
#define SIMUL_TOTAL_N_OF_REG	 8  // definizione grandezza del buffer dove sono memomorizzati i dati,  numero parametri da trattare
#define SIMUL_NOMECONFIGURAZIONE	   "MysticBox"


//inserire define dei pin da usare
//sensore DHT
#define DHTPIN 7
#define DHTTYPE DHT22



#ifndef MysticDum_h
#define MysticDum_h


//#define PWMCOM_Macchinetta_Caffe_DEBUG true

#ifdef MysticDum_h_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif

//#define MysticDum_h_DEBUG_1 true

#ifdef MysticDum_h_DEBUG_1
#define _DEB_1_PRINT(x)   SerialUSB.print(x);
#define _DEB_1_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_1_PRINT(x)
#define _DEB_1_PRINTLN(x)
#endif

//#define MysticDum_h_INOUT
#ifdef MysticDum_h_INOUT
#define M_CAFFE_INOUT_PRINT(x)   SerialUSB.print(x);
#define M_CAFFE_INOUT_PRINTLN(x) SerialUSB.println(x);
#else
#define M_CAFFE_INOUT_PRINT(x)
#define M_CAFFE_INOUT_PRINTLN(x)
#endif




class MysticDum : public Dum
{

private:
	/* i dati di label for_cs sono organizzati in questo modo
		all'inizio i dati prelevati dalla parte linux
		Alla fine i dati prelevati dalla parte embedded.

		In questo modo l'aggiornamento dei dati si fa con un semplice for, 
		Aggiungere parametri non richiede conosceli.
	*/
	String label_for_cs[SIMUL_TOTAL_N_OF_REG] PROGMEM = 
	{"Switch1","Switch2","LDR","Temperature","Humidity",
	 "UpTime", "SampleRate","Reboot"};



public:

	MysticDum();
	virtual ~MysticDum();

	virtual void begin();
	virtual bool aggiornaStato(); 						// legge tutti i registri definiti dallo slave
	virtual String processCommand(String);				// elabora e risponde ad un comando del DAB CS o del sito web
	unsigned long int getSampleRate();					// funzione per prelevare il sample rate in miilisecondi
	String leggiParametroStringSuFile(String Parametro);            // Funzione per leggere il parametro Stringa sul file system linux
	void sendDataToCs();								// prepara i dati e li invia al centro servizi
	void riceviMessaggi();								// riceve i messaggi dal centro servizzi li passa a processMessage
	String processMessage(String message);				// Risponde alle richieste base: inventory, setparam, se riguardano un altro dum smista la richiesta al dum corretto

protected:
	String _fileStorageParametri = SIMUL_FILESTORAGEPARAMETRI;
	String _fileStorageParametriRete = SIMUL_FILESTORAGEPARAMETRIRETE;
	String _fileConfigurazionePwmCom = SIMUL_PERCORSOCONFIGURAZIONE;

private:
	void generazioneStati();						// Stato Casuale
	void statoStop();
	void inviaStati();
	void leggiCorrenti();

	/*int _pinA, _pinB, _pinC, _pinR, _pinN, _pinOutI1, _pinOutI2, _pinCorrentePompaA, _pinCorrentePompaB;
	int _pinTastoPompaA, _pinTastoPompaB;*/
	float _humidity;  //Stores humidity value
	float _temperature; //Stores temperature value


	int _pinA = 3;
	int _pinB = 4;
	int _pinC = 5;
	int _pinR = 6;
	int _pinN = 7;
	int _pinOutI1 = 10;
	int _pinOutI2 = 11;
	int _pinCorrentePompaA = 0;
	int _pinCorrentePompaB = 1;
	int _pinTastoPompaA = 44;
	int _pinTastoPompaB = 45;



	boolean _connectedToBridge;
	//definizione delle variabili corrispondent alle etichette dei dum
	byte A, B, C, R, N, Iout1, Iout2, TastoPompaA, TastoPompaB;
	unsigned long UpTime, _correnteA, _correnteB, _TriggerCorrentePompaA, _TriggerCorrentePompaB;
	unsigned long cicli, stato;
	boolean _errorePompaA, _errorePompaB;

};

#endif  //pwmcom_ver_1.0_H
