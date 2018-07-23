#include "Crono.h"




Crono::Crono()
{

}


Crono::~Crono()
{
}

void Crono::begin(boolean settimanale)
{
	_sincronizzato = false;
	 _standardTimeTo1970 = 0;
	_aggiornaOra.setPeriod(TEMPOAGGIURNAMENTOORA);
	_aggiornaOra.start();
	for (size_t i = 0; i < NUMEROPROGRAMMI; i++)
	{
		programma[i].attivo = false;
	}
	// inizializzazione delle variabili
	_settimanale = settimanale;
	String _fileDati;
	_fusoOrario = 3600;
	setTimeCrono();



}

boolean Crono::setTimeCrono(){


//	SerialUSB.println("--------------------------------- ingresso SetTimeCrono--------------------------");
	unsigned long orario = 0;
//	watchdogReset();
	Process p;
	String data="";
	p.begin(SCRIPTORARIO);
	//p.setTimeout(2000);
	if (p.run()) {
		// errore
	}
	else {
		for (int i = 0; i < 20; i++) {
			if (p.running()) { delay(400); }
			else {
				while (p.available()) {
					data += (char)p.read();
				}
				break;
			}
		}
	}
	//while (p.available()) {
	//	data += (char)p.read();
	//}

	if (data != "") {
		data = d.getValueFromKey(data, CHIAVETEMPO);
		if (data != "-1" && data !="")
			orario = data.toInt();
		else orario = 0;

	}



	if (orario > (10*365*24*60*60)) {
		_offSet = millis() / 1000;
		_standardTimeTo1970 = orario;
		setTime(_standardTimeTo1970 +_fusoOrario);

		_sincronizzato = true;
		return true;

	}
	else return false;
	//watchdogReset();

}
//TODO: vedi modello nel'header
String Crono::getTime()
{

	if (!_sincronizzato || _aggiornaOra.test()) {
		if	(setTimeCrono())  _aggiornaOra.start();
	};
	if (_sincronizzato) {
		time_t tempo_attuale;
		tempo_attuale = _standardTimeTo1970 + millis() / 1000 - _offSet;
		//ctime(&tempo_attuale);
		//setTime(_standardTimeTo1970 + millis()/1000 - _offSet);

		String Data = printDigits(hour()) + ":" + printDigits(minute()) + "." + printDigits(second()) + " del "
					 + String(day()) + " " + mesi[month()-1] + " " + String(year()) + " " + giorni[weekday()];

		return Data;
	}
	return "Orario non definito";
}

bool Crono::setProgramTimeSlot(byte day, byte ordinale, int start, int endurance)
{
	ordinale -= 1;
	int ordinaleProgramma = (day - 1) * MAXPROGRAMMIGIORNALIERI + ordinale;


	// validazione della programmazione;
	if ((day <= 0) ||(day > 7) || (ordinale < 0) || (ordinale >= MAXPROGRAMMIGIORNALIERI)) return false;
	if ((endurance == 0) || (start < 0) || (start > 60 * 24)) {
		programma[ordinaleProgramma].attivo = false;
		if (day==7)	programma[ordinale].attivo = false;
		_DEB_PRINT("Abilitato in falso: "); _DEB_PRINTLN(programma[ordinaleProgramma].attivo);
		return false;
	}
// dati corretti
	boolean attivo;
	_DEB_PRINT("day: "); _DEB_PRINTLN(day);
	_DEB_PRINT("ordinale: "); _DEB_PRINTLN(ordinale);
	_DEB_PRINT("Start: "); _DEB_PRINTLN(start);
	_DEB_PRINT("endurance: "); _DEB_PRINTLN(endurance);
	_DEB_PRINT("indice Matrice: "); _DEB_PRINTLN(ordinaleProgramma);
	if (_settimanale) {
		programma[ordinaleProgramma].giorno = day;
		programma[ordinaleProgramma].partenza = start;
		programma[ordinaleProgramma].durata = endurance;
		programma[ordinaleProgramma].attivo = true;
		if (day == 7) {
			if (((start + endurance) > 24 * 60)) {
				programma[ordinale].attivo = true;
				programma[ordinale].giorno = 1;
				programma[ordinale].partenza = start;
				programma[ordinale].durata = endurance;

			}
			else
				programma[ordinale].attivo = false;
		}
	_DEB_PRINT("Abilitato: "); _DEB_PRINTLN(programma[ordinaleProgramma].attivo);
	return programma[ordinaleProgramma].attivo;
	}
	else {
		programma[ordinaleProgramma].giorno = day;
		programma[ordinaleProgramma].partenza = start;
		programma[ordinaleProgramma].durata = endurance;
		if (((start + endurance) <= 24 * 60))
			programma[ordinaleProgramma].attivo = true;
		else
			programma[ordinaleProgramma].attivo = false;
		_DEB_PRINT("Abilitato: "); _DEB_PRINTLN(programma[ordinaleProgramma].attivo);
		return programma[ordinaleProgramma].attivo;

	}


	return false;
}

boolean Crono::runNow()
{
	// calcolo del minuto attuale del gg

	if (_sincronizzato) {
		int minutoAttuale = hour() * 60 + minute();
		int day = weekday();

		if (_settimanale) minutoAttuale += (day * 24 * 60);

		for (int i = 0; i < NUMEROPROGRAMMI; i++) {
			if (programma[i].attivo) {
				_DEB_PRINTLN("---------------------------------------------")
					_DEB_PRINT("ordinale: "); _DEB_PRINTLN(i);
				_DEB_PRINT("day: "); _DEB_PRINTLN(programma[i].giorno);
				_DEB_PRINT("Start: "); _DEB_PRINTLN(programma[i].partenza);
				_DEB_PRINT("endurance: "); _DEB_PRINTLN(programma[i].durata);
				int start;
				if (_settimanale) {
					start = programma[i].giorno * 24 * 60 + programma[i].partenza;
					if ((minutoAttuale >= start) && (minutoAttuale < start + programma[i].durata))
						return true;

				}
				else if (programma[i].giorno == day) {
					start = programma[i].partenza;
					if ((minutoAttuale >= start) && (minutoAttuale < (start + programma[i].durata)))
						return true;
				}

			}
		}

		return false;
	}
	else return false;
}

void Crono::setFusoOrario(int fuso)
{
	_fusoOrario = fuso;
}



String Crono::printDigits(int digits)
{
		// utility function for digital clock display: prints preceding colon and leading 0
	String data;
	if (digits < 10)
	  data += '0';
    data += String(digits);
	return data;
}

