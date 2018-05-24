#include "Arduino.h"


/* Versione rev 10, si parte dalla versione DB4 installata su bientina

Cose da migliorare:
implementare che in caso di dato tutto a -1 scriva dato non valido.


*/


#define SIMULEBOX_DEBUG true


#ifdef SIMULEBOX_DEBUG_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif


// include
#include "PseudoTimer.h"
#include "PWMCOM_SimulEbox.h"

// librerie


// Fine degli include

#define INVIO_TUTTO_AL_CS 10                                  // definizione di quando si mandano comunque tutti i dati al Centro Servizi

#define MAX_PARAMETERS_FROM_MAILBOX 2                         // numero di parametri che arrivano dal bridge e vengono analizzati localmente

#define MAX_PARAMETERS_FROM_CS_TO_PWMCOM 6                    // Numero massimo di parametri che possono arrivare dal Bridge

#define T_INVIO_DATI_CS  10000                                // intervallo di tempo per l'invio dati al centro servizi in millisecondi
#define T_INVIO_DATI_SITO 3000                                // intervallo di tempo per l'invio dati al sito locale
#define T_RICEVI_MESSAGGI 500                                 // intervallo di tempo la ricezione dei messaggi dal sito /tempo non strettamente necessario
#define WATCH_DOG_TIME  17000                                 // Watch dog time 16s


// dichiarazione dei prototipi di funzione per evitare gli errori di compilazione.

PWMCOM_SimulEbox  SimulEbox;

void sendDataToCs() {
	SerialUSB.print("ingresso SendDataToCS ---");
	SimulEbox.sendDataToCs();
	SerialUSB.println(" SendDataToCS UScita");
	};

void aggionrnaSito() { SimulEbox.aggionrnaSito(); };
void riceviMessaggi() {
	SerialUSB.print("ingresso riceviMessaggi ---");
	SimulEbox.riceviMessaggi();
	SerialUSB.println(" riceviMessaggi UScita");
};
void watchdogSetup(void) {}; // funzione necessaria per l'aggiornaemnto Watchdog


PseudoTimer timerInvioDatiCs(T_INVIO_DATI_CS, sendDataToCs);
//PseudoTimer timerInvioDatiSito(T_INVIO_DATI_SITO, aggionrnaSito);
PseudoTimer timerRicezioneMessaggi(T_RICEVI_MESSAGGI, riceviMessaggi);







// struttira che contiene quello necessario ad usare e gestire un evoplus.


//int debug=10;

// nomi dei percorsi dove memorizzare i file




void setup()
{

	//  Setup del  2
	uint8_t j, result;

	// inizalizazione del watchdog
	watchdogEnable(WATCH_DOG_TIME);
	delay(3000);
	watchdogReset();
	SerialUSB.begin(250000);

	SerialUSB.println("-----------------------------------AVVIO--------------------------------------");
	//inizializzazione della seriale per debug



	// accensione e spegimento led su pin 13
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delay(100);

	//  SerialUSB.println("avvio node");

	// node.SlaveAddress(slave_id);
	_DEB_PRINTLN("avvio node");


	digitalWrite(13, LOW);
	// dopo la partenza del bridge si spegne il led su pin 13


	// inizializzazione client modbus Attivi



	//watchdogReset();
	SimulEbox.begin();
	watchdogReset();
	timerInvioDatiCs.start();
	sendDataToCs();
	//timerInvioDatiSito.start();
	timerRicezioneMessaggi.start();

}

void loop()
{
	watchdogReset();
	timerInvioDatiCs.testAndExecute();
	//watchdogReset();
	//timerInvioDatiSito.testAndExecute();
	watchdogReset();
	timerRicezioneMessaggi.testAndExecute();
	watchdogReset();
	//timerInvioDatiCs.setPeriod(SimulEbox.getSampleRate());
	//watchdogReset();
}








