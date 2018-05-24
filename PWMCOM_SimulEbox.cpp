 #include "PWMCOM_SimulEbox.h"



PWMCOM_SimulEbox::PWMCOM_SimulEbox()
{

	_numParametri = SIMUL_TOTAL_N_OF_REG;
	_fileStorageParametri = SIMUL_FILESTORAGEPARAMETRI;
	A=0, B=0, C=0, R=0, N=0, Iout1=0, Iout2=0, TastoPompaA=0, TastoPompaB=0;
	UpTime=0, _correnteA=0, _correnteB=0, _TriggerCorrentePompaA=0, _TriggerCorrentePompaB=0;
	cicli=0,stato=0;
	pinMode(_pinA, OUTPUT); pinMode(_pinB, OUTPUT); pinMode(_pinC, OUTPUT); pinMode(_pinR, OUTPUT); pinMode(_pinN, OUTPUT);
	pinMode(_pinOutI1, OUTPUT); pinMode(_pinOutI2, OUTPUT);
	pinMode(_pinTastoPompaA, OUTPUT); pinMode(_pinTastoPompaB, OUTPUT);
	pinMode(_pinCorrentePompaA, INPUT);
	pinMode(_pinCorrentePompaB, INPUT);
	_errorePompaA = false;
	_errorePompaB = false;
	_TriggerCorrentePompaA = 30;
	_TriggerCorrentePompaB = 30;
	_fileStorageParametriRete = SIMUL_FILESTORAGEPARAMETRIRETE;
	_connectedToBridge = false;
	cicli = 0;
}


PWMCOM_SimulEbox::~PWMCOM_SimulEbox()
{

}


void PWMCOM_SimulEbox::begin() {

	String supp, valore;
	String Seriale, Add, chiave, Type, _fileDati;
	Process p;

	randomSeed(analogRead(0));

	//  inizializzazione parametri
	_parametri.begin(label_for_cs, _numParametri);
	_fileStorageParametri = SIMUL_FILESTORAGEPARAMETRI;
	
	// Inizializzazione Bridge
	Bridge.begin(250000);
	FileSystem.begin();
	Mailbox.begin();
	//watchdogReset();

	// lettura di tutti i dati dal file storage
	p.begin("cat");
	p.addParameter(_fileStorageParametri);
	//watchdogReset();
	p.run();
	//watchdogReset();
	_fileDati = "";
	_fileDati = p.readString();
	//while (p.available()) {
	//	_fileDati += (char)p.read();
	//	
	//}
	//_DEB_1_PRINT("Stampa Storageconfiguration:  ") _DEB_1_PRINTLN(_fileDati);;
	
	_parametri.setValue("UpTime", 0);

	//_invioDatiFast.setPeriod(SIMUL_INVIODATIFAST);
	_parametri.setValue("SampleRate", "0");

	//_seriale = getValueFromKey(_fileDati, "DUM21@Serial");
	_seriale="PRZQU-U03I0-QZV9D-ZLDTW-RQQU1-PWIU111";

	setSerial(_seriale);
	setNameConf(SIMUL_NOMECONFIGURAZIONE);
	_TriggerCorrentePompaA = getValueFromKey(_fileDati, "TriggerCorrentePompaA").toInt();
	_TriggerCorrentePompaB = getValueFromKey(_fileDati, "TriggerCorrentePompaB").toInt();
	aggiornaStato();
}


String PWMCOM_SimulEbox::processCommand(String message) {
	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.processCommnad()   -------------    ");

	/* Richiesta inviata dal centro servizi:

	ID_richiesta/ID_device/Command/parametro_1/parametro_2/../parametro_n

	La richiesta elaborata dal PWM COM arriva a questo punto, sotto questa forma:

	Command/parametro_1/parametro_2/../parametro_n

	La risposta verso il centro servizi e:
	ID_richiesta/ID_device/risposa/parametro_1/parametro_2/../parametro_n

	in questa libreria vengono elaborate le risposte in questo modo:
	risposta: comando (lo stesso ricevuto)
	Lista di valori che rappresntano la riuscita dell'operazione.

	*/

	String  valore, risposta, parametro;
	int i = 0;
	String parameters[SIMUL_MAX_PARAMETERS_FROM_CS];


	// parser che prende la stringa di comando e la posiziona su un array
	for (int j = 0; j < SIMUL_MAX_PARAMETERS_FROM_CS; j++) {
		parameters[j] = "";
	}
	// _DEB_PRINT("Comando ricevuto dal lato linux: "); _DEB_PRINTLN(message);

	while ((message.indexOf('/') > 0) || (i < SIMUL_MAX_PARAMETERS_FROM_CS - 1)) {
		parameters[i] = message.substring(0, message.indexOf('/'));
		message = message.substring(message.indexOf('/') + 1);
		i++;
	}

	parameters[i] = message;
	risposta = "InvalidCommand";

	if (parameters[0] == "SetParam") {
		_invioDatiFast.start();
		parametro = parameters[1];
		valore = parameters[2];

/*------------------------- SampleRate --------------------------------------------*/
		if (parametro == "SampleRate") {
			risposta = valore;
			_parametri.setValue(parametro, valore);
			//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
			_invioDatiFast.start();
			unsigned long extraRate = getSampleRate() * 3;
			if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
			return parameters[0] + DUM_SEPARATORE + parameters[1] + DUM_SEPARATORE + risposta;
		};

		

	   /*------------------------- TriggerCorrentePompaA --------------------------------------------*/
		if (parametro == "TriggerCorrentePompaA") {
				risposta = valore;
				_parametri.setValue(parametro, valore);
				salvaParametroSuFile(parametro, valore);
				_TriggerCorrentePompaA = valore.toInt();
				//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
				_invioDatiFast.start();
				unsigned long extraRate = getSampleRate() * 3;
				if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
				return parameters[0] + DUM_SEPARATORE + parameters[1] + DUM_SEPARATORE + risposta;
		};
		/*------------------------- TriggerCorrentePompaB --------------------------------------------*/
		if (parametro == "TriggerCorrentePompaB") {
			risposta = valore;
			_parametri.setValue(parametro, valore);
			salvaParametroSuFile(parametro, valore);
			_TriggerCorrentePompaB = valore.toInt();
				//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
				_invioDatiFast.start();
			unsigned long extraRate = getSampleRate() * 3;
			if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
			return parameters[0] + DUM_SEPARATORE + parameters[1] + DUM_SEPARATORE + risposta;
		};


/*++++++++++++++++++++++++++++++++  Reboot  ++++++++++++++++++++++++++++++++++++++*/
		if (parametro == "Reboot") {
			while (1) { ;; }
		}
		return parameters[0] + DUM_SEPARATORE + "Invalid param";
	}
	else return parameters[0] + DUM_SEPARATORE + "Invalid command";
}

bool PWMCOM_SimulEbox::aggiornaStato() {

	// lo scopo di questa funzione è leggere lo stato di tutti i sensori e metterli a disposizione
	// legge posizione pwmcom
	// temperatura, umidità
	// posizione da sensore
	// posizione da n° di step

	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.aggiornastato()   -------------    ");

	Process p;
	String supp, result, chiave, valore;
	unsigned long now = millis();
	_errorePompaA = false;
	_errorePompaB = false;


	_parametri.setValue("UpTime", ( now / 1000));
	
	// Il sample rate deve essere sempre lo stesso
	//if (_invioDatiFast.test()) _parametri.setValue("SampleRate", "0");

	//// Parametri di rete numeri interi
	//p.begin("cat");
	//p.addParameter(_fileStorageParametriRete);
	//watchdogReset();
	//timeA = millis() - now;
	//p.runAsynchronously();
	//result = "";
	//for (int i = 0; i < 20; i++) {

	//	if (p.running()) { delay(100); }
	//	else {
	//		while (p.available()) {
	//			result += (char)p.read();
	//		}
	//		break;
	//	}
	//}
	
	stato = (cicli) % 4;
	//watchdogReset();

	if (stato == 0) {
		generazioneStati();
		inviaStati();
		delay(6000);
	}
	if (stato == 2) {
		statoStop();
		inviaStati();
		delay(6000);
	}
	
	//watchdogReset();
	leggiCorrenti();
	_parametri.setValue("IngressoR",R);
	_parametri.setValue("IngressoA",A);
	_parametri.setValue("IngressoB",B);
	_parametri.setValue("IngressoC",C);
	_parametri.setValue("IngressoN",N);
	_parametri.setValue("Iout 1", Iout1);
	_parametri.setValue("Iout 2", Iout2);

	_parametri.setValue("CorrentePompaA", _correnteA);
	_parametri.setValue("CorrentePompaB", _correnteB);
	_parametri.setValue("Cicli", cicli);
	_parametri.setValue("TastoPompaA", TastoPompaA);
	_parametri.setValue("TastoPompaB", TastoPompaB);
	if ((stato == 0) || (stato ==1)) 	_parametri.setValue("stato", 0);
	else _parametri.setValue("stato", 1);
	if ((stato == 2) || (stato == 3)) {
		if (_correnteA > _TriggerCorrentePompaA ) _errorePompaA = true;
		if (_correnteB > _TriggerCorrentePompaB) _errorePompaB = true;
	}
	_parametri.setValue("ErrorePompaA", _errorePompaA);
	_parametri.setValue("ErrorePompaB", _errorePompaB);
	_parametri.setValue("TriggerCorrentePompaB", _TriggerCorrentePompaB);
	_parametri.setValue("TriggerCorrentePompaA", _TriggerCorrentePompaA);
	cicli++;
	return true;
}

unsigned long int PWMCOM_SimulEbox::getSampleRate() {
		//M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.getsamplerate() ---------------------");
		unsigned long int value = 10000;
		if (_parametri.getValue("SampleRate") == "1") value = 15000;
		if (_parametri.getValue("SampleRate") == "2") value = 10000;
		if (_parametri.getValue("SampleRate") == "3") value = 5000;
		//M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.getsamplerate()");
		return value;
	}

/*
void PWMCOM_SimulEbox::aggiornaSito() {
	//M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.aggiornaSito() ---------------------");
	//M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.aggiornaSito()");
};
*/
void PWMCOM_SimulEbox::sendDataToCs() {
	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.sendDataToCs() ---------------------");

	String stringa, supp;
	aggiornaStato();
	if (_connectedToBridge) {
		File dataFile = FileSystem.open(SIMUL_NOME_FILE_CS_TXT	, FILE_WRITE);
		stringa = "[" + dataToCS(_seriale) + "]";
		while (stringa.length() > SIMUL_MAX_CAR_TO_BRIDGE) {
			supp = stringa.substring(0, SIMUL_MAX_CAR_TO_BRIDGE - 1);
			dataFile.print(supp);
			stringa = stringa.substring(SIMUL_MAX_CAR_TO_BRIDGE - 1);
		}

		dataFile.print(stringa);
		dataFile.close();
		
		Process invio_cs;
		supp = SIMUL_SENDDATATICS;
		invio_cs.begin(supp);
		invio_cs.runAsynchronously();

		for (int i = 0; i < 20; i++) {
			if (invio_cs.running()) {
				delay(200);
			}
			else break;
		}
		M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.sendDataToCs()");
	}
};

void PWMCOM_SimulEbox::riceviMessaggi() {
		M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.riceviMessaggi()  -----------------");
		String message = "";
		String risposta;
			if (Mailbox.messageAvailable() > 0)
			{
				// legge il messaggio scritto dal bridge e restituisce il risultato. 

				Mailbox.readMessage(message);
				M_CAFFE_INOUT_PRINT("Ricevuto Messaggio: "); M_CAFFE_INOUT_PRINT(message); M_CAFFE_INOUT_PRINT("  ");
				this->setSampleRate(3);
				M_CAFFE_INOUT_PRINTLN(" Cambio sampleRate  ");
				risposta = processMessage(message);
				M_CAFFE_INOUT_PRINT("Ottenuta Risposta da processMessagge: "); M_CAFFE_INOUT_PRINT(risposta); M_CAFFE_INOUT_PRINTLN("  ");

				Mailbox.writeMessage(risposta);
				M_CAFFE_INOUT_PRINTLN("Scrivo sulla mailBox  ");

				//_DEB_PRINT("Ricevuto risposta: "); _DEB_PRINTLN(risposta);
				// data_to_cs();
				sendDataToCs();
			}
		
		M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.riceviMessaggi()");
};


String PWMCOM_SimulEbox::processMessage(String message) {
	String parameters[2]{ "","" };
	String risposta_2;
	bool trovato;
	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.processMessage()  -----------------");
	//_DEB_PRINT("Comando ricevuto dal lato linux (dentro process_message: "); _DEB_PRINTLN(message);


	/* Formato richiesta da CS:

	ID_richiesta/ID_device/Command/parametro_1/parametro_2/../parametro_n

	La risposta verso il centro servizi e:
	ID_richiesta/ID_device/risposa/parametro_1/parametro_2/../parametro_n

	risposta contiene:
	1) Il comando ricevuto se si Ã¨ riusciti ad elaborare il comando
	2) una stringa per il tipo di errore generato.
	parametro_1.. paramentro_n
	i dati ricevuti per questo parametro.

	*/


	// fino a 2 per separare ID_richiesta/ID_device/ 
	parameters[0] = message.substring(0, message.indexOf('/'));
	message = message.substring(message.indexOf('/') + 1);
	parameters[1] = message.substring(0, message.indexOf('/'));
	message = message.substring(message.indexOf('/') + 1);


	  //while ((message.indexOf('/') > 0) || (i < 2)) {
	  //  parameters[i] = message.substring(0, message.indexOf('/'));
	  //  message = message.substring(message.indexOf('/') + 1);
	  //  i++;
	  //}
	trovato = false;

	if (parameters[1] == "Inventory") {
		risposta_2 = parameters[0];
		risposta_2 += DUM_SEPARATORE + getSerial(); ;
		//_DEB_PRINT("Risposta ad Inventory dentro la funzione:  ");
		_connectedToBridge = true;
		//_DEB_PRINTLN(risposta_2);
		this->setSampleRate(0);
		return risposta_2;

	}

	if (getSerial() == parameters[1]) {
		trovato = true;
		return parameters[0] + DUM_SEPARATORE + parameters[1] + DUM_SEPARATORE + this->processCommand(message);
	}
	if (not trovato) return  parameters[0] + DUM_SEPARATORE + parameters[1] + DUM_SEPARATORE + "BAD DEVICE";
	return "no_risposta_2";

}

void PWMCOM_SimulEbox::generazioneStati()
{
	A = random(2); B = random(2); C = random(2);
	N = random(2); R = random(2);
	Iout1 = random(2);
	Iout2 = random(2);
	TastoPompaA = random(2);
	TastoPompaB = random(2);
	return;

}


void PWMCOM_SimulEbox::statoStop()
{
	A = 0; B = 0; C =0;
	N = 0; R = 1;
	Iout1 = 1;
	Iout2 = 1;


}
void PWMCOM_SimulEbox::inviaStati()
{
	digitalWrite(_pinA, A); 	digitalWrite(_pinB, B); digitalWrite(_pinC, C); 
	digitalWrite(_pinR, R); digitalWrite(_pinN, N);

	digitalWrite(_pinOutI1, Iout1); digitalWrite(_pinOutI2, Iout2);
	if (stato == 0) {
		digitalWrite(_pinTastoPompaA, TastoPompaA);
		digitalWrite(_pinTastoPompaB, TastoPompaB);
		delay(500);
		digitalWrite(_pinTastoPompaA, 0);
		digitalWrite(_pinTastoPompaB, 0);
	}
}

void PWMCOM_SimulEbox::leggiCorrenti()
{
	int correnteA = 0, correnteB = 0;
	int letturaA, letturaB;
	/*int mezzaDinamica = 4096 / 2;
	for (int i = 0; i < 100; i++) {
		correnteA += sq(((analogRead(_pinCorrentePompaA) - mezzaDinamica)));
		correnteB += sq(((analogRead(_pinCorrentePompaB) - mezzaDinamica)));
		delayMicroseconds(200);
	}

	correnteA = sqrt(correnteA) * fattoreDiCorrezione;
	correnteB = sqrt(correnteB)* fattoreDiCorrezione;*/

	for (int i = 0; i < 100; i++) {
		letturaA = (analogRead(_pinCorrentePompaA));
		letturaB = (analogRead(_pinCorrentePompaB));
		if (letturaA > correnteA) correnteA = letturaA;
		if (letturaB > correnteB) correnteB = letturaB;
		
		delayMicroseconds(200);
	}
	if (correnteA < 20) correnteA = 0;
	if (correnteB < 20) correnteB = 0;
	_correnteA = correnteA;
	_correnteB = correnteB;
	
}

