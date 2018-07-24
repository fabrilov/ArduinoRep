
#include <Arduino.h>
#include "NewBridge.h"
#include "PseudoTimer.h"
#include "Parametri.h"
#include "Dum.h"

#include <Wire.h> //per sensore I2C es. giroscopio/accelerometro
#include "DHT.h" // sensore temp. umidità DHT 21  (AM2301)

#define SIMUL_MAX_PARAMETERS_FROM_CS 10       // numero massimo di parametri che possono arrivare dal centro servizi                                
#define SIMUL_HIDDEN		"h"					// valore che nasconde il widget
#define SIMUL_DISABLE		"d"					// valore disabilita il widget
#define SIMUL_NONVALIDO     "-1"
#define SIMUL_STRING_NOT_VALID_VALUE "null"	// stringa che si invia nel caso il valore letto non sia valido

//TODO: ridefinire richiesta seriale se non già presente in eeprom al dabmgr, utilizzare come modello qst parte di codice

 #if 0
int DumMaster::exec(String* command)
{
	String parameters[2];
	String tmpCommand;

	DBG_PRINTF("Comando ricevuto dal lato linux (dentro DumMaster::exec: %s)\n", command->c_str());

	/* Formato richiesta da CS:

                ID_richiesta/ID_device/Command/parametro_1/parametro_2/../parametro_n

                La risposta verso il centro servizi e:
                ID_richiesta/ID_device/risposa/parametro_1/parametro_2/../parametro_n

                risposta contiene:
                1) Il comando ricevuto se si è riusciti ad elaborare il comando
                2) una stringa per il tipo di errore generato.
                parametro_1.. paramentro_n
                i dati ricevuti per questo parametro.
	 */

	// fino a 2 per separare ID_richiesta/ID_device/
	parameters[0] = command->substring(0, command->indexOf('/'));
	tmpCommand = command->substring(command->indexOf('/') + 1);
	parameters[1] = tmpCommand.substring(0, tmpCommand.indexOf('/'));
	tmpCommand = tmpCommand.substring(tmpCommand.indexOf('/') + 1);

	char ser[128];
	if (parameters[1] == "Inventory") {
		if (!get_serial(ser, 0)) {
			String risposta = "";
			getInventory(risposta);
			risposta = parameters[0] + risposta;
			DBG_PRINTF("Risposta ad Inventory:  %s\n", risposta.c_str());
			Mailbox.writeMessage(risposta);
			inventory_resp = 1;
		} else {
			// if (id_inventory)
			// delete id_inventory;
			// id_inventory = new String(parameters[0]);
			//  Bridge.put("NewSerial", "ebox_ser");
			printf("get(NewSerial)\n");
			int len;
			S32 getTimer = K_TIMER_SetTimer(0);
			while(1) {
				long_wait = 15000 * 10;
				if (K_TIMER_TestTimer(getTimer)) {
					printf(".");
					getTimer = K_TIMER_SetTimer(50);
					if (Bridge.get("NewSerial", ser, sizeof(ser) - 1)!=0xFFFF) {
						if ((len=strlen(ser))>4) {
							if (strcmp(ser, "Overflow")!=0) {
								get_serial(ser, len+1);
								Mailbox.writeMessage(parameters[0] + "/" + ser);
								DBG_PRINTF("Risposta ad inventory:  %s\n", (parameters[0] + "/" + ser).c_str());
								inventory_resp = 1;
							}
							break;
						} else if (len!=0)
							break;
					} else
						break;
				}
				K_WD_ForeGroundCheck();
			}
		}
		return 0;
	}

	if (parameters[1] == *serial) {
		if (tmpCommand == "UpdateReady") {
			Mailbox.writeMessage(parameters[0] + "/" + parameters[1] + "/" + tmpCommand);
			update_DUM = UPDATE_PRESENT;
			return 0;
		}
		// GlobalRequests.insert_request(parameters[0].c_str());
		::doCmd(parameters[0], tmpCommand);
	} else
		Mailbox.writeMessage(parameters[0] + "/" + tmpCommand + String("/INVALID COMMAND"));
	return -1;
}
#endif



// TODO: valutare se necessari qst file di configurazione di appoggio
#define DUM_FILESTORAGEPARAMETRI				"/evoplus/storageConfiguration.txt"
//TODO correggere define
#define SIMUL_SENDDATATICS						"to_cs_usb.sh"							// Script per l'invio dati su CS. gli script sono relativi e si trovano in /evolpus/scripts 
#define SIMUL_NOME_FILE_CS_TXT					"data_to_cs.txt"						// File che contiene i dati da inviare al CS
#define SIMUL_MAX_CAR_TO_BRIDGE 250	 // numero massimo di caratteri verso il Bridge
#define SIMUL_TOTAL_N_OF_REG	 10  // numero parametri da trattare
#define SIMUL_NOMECONFIGURAZIONE	   "MysticDum" //deve tornare con l configurazione inserita nel CS


//inserire define dei pin da usare
//sensore DHT
#define DHTPIN 23
#define DHTTYPE DHT22
//sensore LDR
#define LDRPIN A0
//RELAY
#define RELAYPIN 22


#ifndef MysticDum_h
#define MysticDum_h


//#define MysticDum_h_DEBUG true

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



class MysticDum : public Dum
{

private:

	String label_for_cs[SIMUL_TOTAL_N_OF_REG]  = 
	{"Switch1","SwitchMode","Luminosity","Temperature","PerceivedTemperature","Humidity","LuminosityThreshold",
	 "UpTime", "SampleRate","Reboot"};



public:
	MysticDum();
	virtual ~MysticDum();

	virtual void begin();
	virtual bool aggiornaStato(); 						// legge tutti i registri definiti dallo slave
	virtual String processCommand(String);				// elabora e risponde ad un comando dal dabmgr

	//TODO: di base, a riposo, ha un sample rate di 30sec, quando interagisco con il DUM passa a 5 sec per un tempo di 2 min
	unsigned long int getSampleRate();					// funzione per prelevare il sample rate in miilisecondi
	String leggiParametroStringSuFile(String Parametro);   // Funzione per leggere il parametro Stringa sul file system linux
	void sendDataToCs();								// prepara i dati e li invia al centro servizi

	// Serve per la DConnect BOX, NON necessario se non ci sono altri dum collegati
	void riceviMessaggi();								// riceve i messaggi dal centro servizi li passa a processMessage
	String processMessage(String message);				// Risponde alle richieste base: inventory, setparam, se riguardano un altro dum smista la richiesta al dum corretto

protected:
	String _fileStorageParametri = DUM_FILESTORAGEPARAMETRI;


private:
	int getRandomIntValue(int min, int max);						// Stato Casuale
	float getRandomFloatValue(int min, int max);
	void inviaStati();
	float getTemperature();
	float getTemperaturePerceived();
	float getHumidity();
	int getLuminosity();
	int getSwitchStatus();
	void setSwitch(int, boolean ); //per attivare il relay

	//variabili corrispondenti alle etichette dei parametri del dum
	boolean _switch1;
	float _humidity;  //Stores humidity value
	float _temperature; //Stores temperature value
	float _temperaturePerceived;
	int _luminosity; //Stores ldr luminosity value
	int _luminosityThreshold; //soglia di luminosità impostabile che sarà scritta su FS
	boolean _relayMode;
	boolean _connectedToBridge;
};

#endif
