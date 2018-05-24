/*
  LBA

  Classe per la gestione de Dum
*/
//

#ifndef DUM_H
#define DUM_H
//#include <malloc.h>

#include <Arduino.h>
#include "NewBridge.h"
#include "PseudoTimer.h"
#include "Parametri.h"

//#define DUM_DEBUG true

#ifdef DUM_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif


#define DUM_DHTPIN 11
#define DUM_DHTTYPE DHT22
#define DUM_SENSOREDISTANZATRIGGERPORT 57
#define DUM_SENSOREDISTANZAECHOPORT    58
#define DUM_INVIODATIFAST 120000

#define DUM_TOTAL_N_OF_REG_OF_DUM 1         // definizione grandezza del buffer dove sono memomorizzati i dati
#define DUM_MAX_PARAMETERS_FROM_CS 10       // numero massimo di parametri che possono arrivare dal centro servizi                                
#define DUM_NOT_READ_VALUE   "null"         // valore non letto - Preset con un valore che non si leggerÃ  mail
#define DUM_NOT_VALID_VALUE "null"          // valore letto ma che non ha senso
#define DUM_STRING_NOT_VALID_VALUE "null"   // stringa che si invia nel caso il valore letto non sia valido
#define DUM_SEPARATORE "/"                  // definizione separatore fra parametri in arrivo e mandati verso il centro servizi
#define DUM_FILESTORAGEPARAMETRI			"/evoplus/storageConfiguration.txt"
#define DUM_CATEGREPSCRIPS					"/evoplus/scripts/catgrep.sh "


class Dum {
  public:
    Dum();
	~Dum(); 									// distruttore da impplentare

// funzioni Virtuale da implementare in ogni singolo DUM   

	virtual void begin();
	virtual bool aggiornaStato();
	virtual String processCommand(String);				// elabora e risponde ad un comando del DAB CS o del sito web

// funzioni generiche per tutti i DUM

	String dataToCS(String seriale);					//Genera il json con tutti i dati del dum
	String dataToCS();									//Genera il json con tutti i dati del sum, usa il codice seriale mem in _seriale
														// legge tutti i registri definiti dallo slave
    											// prepara una stringa da inviare al centro servizi

	String getSerial();
	void setSerial(String);
	void setNameConf(String);
	void resetData();
	void setSampleRate(int sampleRate);
	void setParameter(String parametro, String valore);				// salva su _parametri(parametri,valore) serve per accedere a parametri
	int  stringToInt(String parametro);

//	Funzioni generiche per leggere dati dal file system linux. Potenti ma lente 
    String catgrepString(String dovecercare, String cosacercare = "");	// fa il cat & grep
    String catgrepInt(String dovecercare, String cosacercare = "");		// fa il cat & grep
	void salvaParametroSuFile(String parametro, String valore, String nomefile= DUM_FILESTORAGEPARAMETRI);     //Funzione per il salvataggio parametri su file system linux in fileStorageParametri.


// funzione ottimizzata pe la velocità tratta una intera stringa
	String getValueFromKey(String stringaDoveCercare, String chiave);   // cerca sulla stringaDoveCercare la chiave e restituisce il valore associato																					 
														 																					 
// funzioni per la determinazione della memoria Ram Libera
	String dynamicRamUsed();
	String staticRamUsed();
	String stackRamUsed();
	String myGuessAtFreeMem();

	int unsignet_to_int(uint16_t);										// funzione che trasforma un uint a 16 bit in long
 
protected:
    String _seriale;												//	Stringa con il seriale del dispositivo
	Parametri _parametri;
	int _numParametri;
	String _fileStorageParametri;
	PseudoTimer _invioDatiFast;
	String _nomeConfigurazione;

private:

	String label_for_cs[DUM_TOTAL_N_OF_REG_OF_DUM] PROGMEM = { "UpTime" };           // definizione grandezza del buffer dove sono memomorizzati i dati
};





#endif /* Dum_H */

