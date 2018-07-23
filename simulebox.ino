#include "Arduino.h"
#include "PseudoTimer.h"
#include "MysticDum.h"


#define MysticBox_DEBUG true

#ifdef MysticBox_DEBUG_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif


#define T_INVIO_DATI_CS  10000                                // intervallo di tempo per l'invio dati al centro servizi in millisecondi
#define T_RICEVI_MESSAGGI 500                                 // intervallo di tempo la ricezione dei messaggi dal sito /tempo non strettamente necessario
#define WATCH_DOG_TIME  17000                                 // Watch dog time 16s


MysticDum  MysticBox;



void sendDataToCs() {
	SerialUSB.print("ingresso SendDataToCS ---");
	MysticBox.sendDataToCs();
	SerialUSB.println(" SendDataToCS UScita");
	};

/*
void riceviMessaggi() {
	SerialUSB.print("ingresso riceviMessaggi ---");
	MysticBox.riceviMessaggi();
	SerialUSB.println(" riceviMessaggi UScita");
};
*/

void watchdogSetup(void) {}; // funzione necessaria per l'aggiornaemnto Watchdog


PseudoTimer timerInvioDatiCs(T_INVIO_DATI_CS, sendDataToCs);
//PseudoTimer timerRicezioneMessaggi(T_RICEVI_MESSAGGI, riceviMessaggi);



void setup()
{

	//  Setup dell'Arduino Due
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

	_DEB_PRINTLN("avvio node");

	// dopo la partenza del bridge si spegne il led su pin 13
	digitalWrite(13, LOW);

	//watchdogReset();
	MysticBox.begin();
	watchdogReset();
	timerInvioDatiCs.start();
	sendDataToCs();
	//timerInvioDatiSito.start();
	//timerRicezioneMessaggi.start();
}

void loop()
{
	watchdogReset();
	timerInvioDatiCs.testAndExecute();
	watchdogReset();
	//timerRicezioneMessaggi.testAndExecute();
	watchdogReset();
}
