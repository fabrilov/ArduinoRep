#pragma once
/*
LBA

Classe per la gestione di un cronotemporizzatore
Funzionamento della classe:
	1) il tempo all'interno della libreria è definito come distanza in secondi dal 1970...
	2) la programmazione è settimanale
	3) Il tempo viene preso dalla parte linux e qunado disponibile si memorizza in un rtc
	4) le schedulazioni vengono scritte e lette nella parte retentiva linux
	5) il controllo delle schedulazioni viene richiesto alla classe, che restituisce con l'ora corrente lo stato

Si basa su una programmazione settimanale.
*/
//

#ifndef Crono_H
#define Crono_H


#include <Arduino.h>
#include "TimeLib.h"
#include "NewBridge.h"
#include "Dum.h"



//#define CRONO_DEBUG true

#ifdef CRONO_DEBUG
#define _DEB_PRINT(x)   SerialUSB.print(x);
#define _DEB_PRINTLN(x) SerialUSB.println(x);
#else
#define _DEB_PRINT(x)
#define _DEB_PRINTLN(x)
#endif

#define TEMPOAGGIURNAMENTOORA   3600 * 1000										// 1 h in millisecondi
#define MAXPROGRAMMIGIORNALIERI 3
#define NUMEROPROGRAMMI  (8*MAXPROGRAMMIGIORNALIERI)

//TODO: adesso si usa il getNTPTime perchè fornito dal dabmgr >9.3 non uo script fatto ad hoc
#define SCRIPTORARIO "raspyNtp.py"										// programma che prende il tempo, se tempo non valido restituisce -1
#define CHIAVETEMPO "NtpTime"


class Crono
{
public:
	Crono();
	~Crono();
	void begin(boolean settimanale = false);									// inizializza la classe
	boolean setTimeCrono();
	void setTimeCrono(int year, int mont, int day, int hour, int sec);
	String getTime();
	//TODO: vedi nuovo modello GetTime implementato nel dabmgr
	#if 0
	static boolean getNTPTime(String &_fileDati) {
//    unsigned long UTC = 0, fuso = 0;;
//    long time;

    _fileDati = "";
    File dataFile = FileSystem.open("@GetTime", FILE_READ);

    if (!dataFile)
        return false;

    int k;
    for (k = 0; (k < 7) && (dataFile.size() == 0); k++) {
        delay(200);
    }

    char c;

    while (dataFile.available()) {
        c = dataFile.read();
        _fileDati += c;
    }

    dataFile.close();

    return true;

#if 0
    String StringDataFromBridge;
    StringDataFromBridge = _fileDati;

    printf("NTP %s\n", _fileDati.c_str());

    int indice = StringDataFromBridge.indexOf('+');
    if (indice > 0) {
        time = StringDataFromBridge.substring(0, indice).toInt();
        if (time != -1)
            UTC = StringDataFromBridge.substring(0, indice).toInt();
        else
            UTC = 0;
        fuso = StringDataFromBridge.substring(indice + 1, StringDataFromBridge.length()).toInt();
    }
    else {
        time = StringDataFromBridge.toInt();
        if (time != -1)
            UTC = StringDataFromBridge.substring(0, indice - 1).toInt();
        else
            UTC = 0;
    }

    tfp_printf("UTC %u\n", UTC);
    if (UTC > (10 * 365 * 24 * 60 * 60)) {
        _offSet = millis() / 1000;
        _standardTimeTo1970 = UTC;
        _fusoOrario = fuso;
        setTime(_standardTimeTo1970 + fuso);
        _sincronizzato = true;
        return true;
    }
    else {
        return false;
    }
#endif
}

	#endif

																// prende il tempo
	bool setProgramTimeSlot(byte day, byte ordinale, int start, int endurance);	// programmazione settimanale
	boolean runNow();															// verifica il programma
	void setFusoOrario(int fuso);												// imposta il fuso orario
	struct programmaGiornaliero {
		boolean attivo;
		byte giorno;
		int partenza; // in minuti
		int durata;
		int temperatura;

	};

private:
	 String mesi[12] = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno","luglio", "agosto", "settembre", "ottobre", "novembre", "dicembre"};
	 String giorni[8] = { "", "domenica","lunedi","martedi","mercoledi","giovedi","venerdi","sabato" };
	 String Data;								// SRINGA CHE CONTIENE LA DATA NEL FORMATO LINUX
	 long	offsetMills;			// tempo trascorso dal 1970... il time corretto è time = offsetmills + mills();
	 unsigned long _standardTimeTo1970;
	 long _offSet;
	 int _fusoOrario;
	 String printDigits(int digits);
	 programmaGiornaliero programma[NUMEROPROGRAMMI];
	 Dum d;
	 String _fileStorageProgramma;
	 boolean _sincronizzato;
	 boolean _settimanale;
	 PseudoTimer _aggiornaOra;
};


#endif
