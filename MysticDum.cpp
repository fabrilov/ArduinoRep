 #include "MysticDum.h"

//invoco costruttore per sens temperatura
DHT dht(DHTPIN, DHTTYPE);


MysticDum::MysticDum()
{
	_numParametri = SIMUL_TOTAL_N_OF_REG;
	_fileStorageParametri = SIMUL_FILESTORAGEPARAMETRI;
	_fileStorageParametriRete = SIMUL_FILESTORAGEPARAMETRIRETE;
	_connectedToBridge = false;

	_temperature = 0; //valori dei sensori
	_humidity = 0;
	_luminosity = 0;
	_luminosityThreshold=28;
	_switch1=0;

	pinMode(DHTPIN, INPUT);
	pinMode(LDRPIN, INPUT);

/*
	_errorePompaA = false;
	_errorePompaB = false;
	_TriggerCorrentePompaA = 30;
	_TriggerCorrentePompaB = 30;
	*/

//	cicli = 0;
}


MysticDum::~MysticDum()
{

}

//nel begin si inizializzano le strutture: creo variabili di supporto, leggo da filesystem
//quei parametri che poi me serviranno nelle successive operazioni

void MysticDum::begin() {
	//inizializzo sensore temperatura
	dht.begin();

	String supp, valore;
	String Seriale, Add, chiave, Type, _fileDati;
	Process p;
	//serve per la generazione di valori random basandosi su lettura di A0
	randomSeed(analogRead(0));

	//  inizializzazione parametri
	_parametri.begin(label_for_cs, _numParametri);
	_fileStorageParametri = SIMUL_FILESTORAGEPARAMETRI;
	
	// Inizializzazione Bridge
	Bridge.begin(250000);
	FileSystem.begin();
	Mailbox.begin();
	//watchdogReset();

	// lettura di tutti i dati dal filesystem
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
	

	//FIX ME: FLO: inserisco seriale Hardcoded per velocità
	//_seriale = getValueFromKey(_fileDati, "DUM21@Serial");
	_seriale="PRZQU-U03I0-QZV9D-ZLDTW-RQQU1-PWIU111";
	setSerial(_seriale);
	setNameConf(SIMUL_NOMECONFIGURAZIONE);
	//inizializzo a 0 uptime e inizio sparando dati frquentemente
	_parametri.setValue("UpTime", 0);
	_parametri.setValue("SampleRate", "0");

	//legge da filesystem il valore del parametro, lo usa anche come archiviazione della soglia stessa
	_luminosityThreshold = getValueFromKey(_fileDati, "LuminosityThreshold").toInt();
	//_TriggerCorrentePompaA = getValueFromKey(_fileDati, "TriggerCorrentePompaA").toInt();
	//_TriggerCorrentePompaB = getValueFromKey(_fileDati, "TriggerCorrentePompaB").toInt();
	aggiornaStato();
}




//riceve e parsa dal centro servizi i comandi per poi fare le relative operazioni
String MysticDum::processCommand(String message) {
	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.processCommnad()-------------    ");

	/* Richiesta inviata dal centro servizi:

	ID_richiesta/ID_device/Command/parametro_1/parametro_2/../parametro_n

	La richiesta elaborata dal PWM COM arriva a questo punto, sotto questa forma:

	Command/parametro_1/parametro_2/../parametro_n

	La risposta verso il centro servizi e:
	ID_richiesta/ID_device/risposta/parametro_1/parametro_2/../parametro_n

	in questa libreria vengono elaborate le risposte in questo modo:
	risposta: comando (lo stesso ricevuto)
	Lista di valori che rappresntano la riuscita dell'operazione.
	*/

	String comm_param[SIMUL_MAX_PARAMETERS_FROM_CS]; //array contenente i parametri che possono arrivare dal CS
	for (int j = 0; j < SIMUL_MAX_PARAMETERS_FROM_CS; j++) {
		comm_param[j] = "";
	}
	// _DEB_PRINT("Comando ricevuto dal lato linux: "); _DEB_PRINTLN(message);

	// parser che prende la stringa di comando e la posiziona su un array
	//indexOf() method gives you the ability to search for the first instance of a particular character value in a String
	//substring() with only one parameter looks for a given substring from the position given to the end of the string
	int i = 0;
	while ((message.indexOf('/') > 0) || (i < SIMUL_MAX_PARAMETERS_FROM_CS - 1)) {
		comm_param[i] = message.substring(0, message.indexOf('/')); //popolo array
		message = message.substring(message.indexOf('/') + 1); // trimmo la coda messaggi del parametro+sepatore e ciclo
		i++;
	}
	comm_param[i] = message; //ultima occorrenza
	String risposta = "InvalidCommand";
	String comando = comm_param[0];
	String parametro = comm_param[1];
	String valore = comm_param[2];
	String returnPattern = comando + DUM_SEPARATORE + parametro + DUM_SEPARATORE + risposta;
// cerco una logica: comando->parametro,valore il  coamndo è il primo parsato e inserito nell'array, seguono parametro e valore
	if (comando == "SetParam") {
		_invioDatiFast.start();
		//parametro = comm_param[1];
		//valore = comm_param[2];
		/*------------------------- SampleRate --------------------------------------------*/
		if (parametro == "SampleRate") {
			risposta = valore;
			_parametri.setValue(parametro, valore);
			//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
			_invioDatiFast.start();
			unsigned long extraRate = getSampleRate() * 3;
			if (_invioDatiFast.getPeriod() < extraRate) _invioDatiFast.setPeriod(extraRate);
			return returnPattern;
		};

//		------------------------- LuminosityThreshold --------------------------------------------
		if (parametro == "LuminosityThreshold") {
				risposta = valore;
				_parametri.setValue(parametro, valore);
				salvaParametroSuFile(parametro, valore);
				_luminosityThreshold = valore.toInt();
				//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
				_invioDatiFast.start();
				unsigned long extraRate = getSampleRate() * 3;
				if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
				return returnPattern;
		};




/*
		------------------------- TriggerCorrentePompaA --------------------------------------------
		if (parametro == "TriggerCorrentePompaA") {
				risposta = valore;
				_parametri.setValue(parametro, valore);
				salvaParametroSuFile(parametro, valore);
				_TriggerCorrentePompaA = valore.toInt();
				//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
				_invioDatiFast.start();
				unsigned long extraRate = getSampleRate() * 3;
				if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
				return returnPattern;
		};
		------------------------- TriggerCorrentePompaB --------------------------------------------
		if (parametro == "TriggerCorrentePompaB") {
			risposta = valore;
			_parametri.setValue(parametro, valore);
			salvaParametroSuFile(parametro, valore);
			_TriggerCorrentePompaB = valore.toInt();
			//_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(risposta);
			_invioDatiFast.start();
			unsigned long extraRate = getSampleRate() * 3;
			if (_invioDatiFast.getPeriod() < extraRate)   _invioDatiFast.setPeriod(extraRate);
			return returnPattern;
		};
*/

		/*++++++++++++++++++++++++++++++++  Reboot  ++++++++++++++++++++++++++++++++++++++*/
		if (parametro == "Reboot") {
			while (1) { ;; }
		}
	/*++++++++++++++++++++++++++++++++  param non valido  ++++++++++++++++++++++++++++++++++++++*/
		else{
			//Pattern composto da comando + DUM_SEPARATORE + parametro + DUM_SEPARATORE + risposta;
			return comando + DUM_SEPARATORE + parametro + " :InvalidParam";}
	}
/*++++++++++++++++++++++++++++++++  comando non valido  ++++++++++++++++++++++++++++++++++++++*/
	else return comando + DUM_SEPARATORE + " :Invalid command";
}




bool MysticDum::aggiornaStato() {

	// lo scopo di questa funzione è leggere lo stato di tutti i sensori e metterli a disposizione
	// legge posizione pwmcom es 	// temperatura, umidità, etc


	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.aggiornastato()   -------------    ");

	Process p;
	String supp, result, chiave, valore;
	unsigned long now = millis();
	//_errorePompaA = false;
	//_errorePompaB = false;

	_parametri.setValue("UpTime", ( now / 1000));
	_parametri.setValue("Temperature", _temperature);
	_parametri.setValue("Humidity", _humidity);
	_parametri.setValue("Luminosity", _luminosity);
	_parametri.setValue("LuminosityThreshold", _luminosityThreshold);

	
/*	stato = (cicli) % 4;
	//watchdogReset();

	if (stato == 0) {
		generaValoriRandom();
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
*/
	return true;
}

unsigned long int MysticDum::getSampleRate() {
		//M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.getsamplerate() ---------------------");
		unsigned long int value = 10000;
		if (_parametri.getValue("SampleRate") == "1") value = 15000;
		if (_parametri.getValue("SampleRate") == "2") value = 10000;
		if (_parametri.getValue("SampleRate") == "3") value = 5000;
		//M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.getsamplerate()");
		return value;
	}

/*
void MysticDum::aggiornaSito() {
	//M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.aggiornaSito() ---------------------");
	//M_CAFFE_INOUT_PRINTLN("Uscita Macchinetta caffe.aggiornaSito()");
};
*/
void MysticDum::sendDataToCs() {
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

void MysticDum::riceviMessaggi() {
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


String MysticDum::processMessage(String message) {
	String comm_param[2]{ "","" };
	String risposta_2;
	bool trovato;
	M_CAFFE_INOUT_PRINT("Ingresso Macchinetta caffe.processMessage()  -----------------");
	//_DEB_PRINT("Comando ricevuto dal lato linux (dentro process_message: "); _DEB_PRINTLN(message);

	/* Formato richiesta da CS:
	ID_richiesta/ID_device/Command/parametro_1/parametro_2/../parametro_n

	La risposta verso il centro servizi e:
	ID_richiesta/ID_device/risposta/parametro_1/parametro_2/../parametro_n

	risposta contiene:
	1) Il comando ricevuto se si è riusciti ad elaborare il comando
	2) una stringa per il tipo di errore generato.
	parametro_1.. paramentro_n
	i dati ricevuti per questo parametro.
	*/

	// fino a 2 per separare ID_richiesta/ID_device/
	String reply = comm_param[0];
	String parametro = comm_param[1];
	reply = message.substring(0, message.indexOf('/'));
	message = message.substring(message.indexOf('/') + 1);
	parametro = message.substring(0, message.indexOf('/'));
	message = message.substring(message.indexOf('/') + 1);
	trovato = false;
//++++++++++++++++++++++++++++++++++++++++++++Inventory++++++++++++++++++++++++++++++++++++++
	if (parametro == "Inventory") {
		//risposta_2 = reply;
		//risposta_2 += DUM_SEPARATORE + getSerial();
		risposta_2 = reply + DUM_SEPARATORE + getSerial();
		//_DEB_PRINT("Risposta ad Inventory dentro la funzione:  ");
		_connectedToBridge = true;
		//_DEB_PRINTLN(risposta_2);
		this->setSampleRate(0);
		return risposta_2;

	}
//++++++++++++++++++++++++++++++++++++++++++++ getSerial+++++++++++++++++++++++++++++++++++++++
	if (parametro == getSerial()) {
		trovato = true;
		return reply + DUM_SEPARATORE + parametro + DUM_SEPARATORE + this->processCommand(message);
	}
	if (not trovato) return  reply + DUM_SEPARATORE + parametro + DUM_SEPARATORE + "BAD DEVICE";
	return "no_risposta_2";

}

//inserire logica di controllo per dht22 per esempio per tararlo correttamente
void MysticDum::getTemperature(){
	 //   _temperature = dht.readTemperature();
	 _temperature = getRandomFloatValue(20,25);
}

void MysticDum::getHumidity(){
	// _humidity = dht.readHumidity();
	_humidity = getRandomFloatValue(60, 95);
}

void MysticDum::getLuminosity(){
	// _luminosity = analogRead(LDRPIN);
	_luminosity = getRandomIntValue(1, 100);
}

void MysticDum::getSwitchStatus(){
	_switch1 = getRandomIntValue(0, 2); //FIX per debug da valori 0/1
}

int MysticDum::getRandomIntValue(int min, int max){
	int val;
	val = random(min,max);
	return val;
}


float MysticDum::getRandomFloatValue(int min, int max){
	float val = random(min, max)/100.0;
	return val;
}

/*
void MysticDum::statoStop()
{
	A = 0; B = 0; C =0;
	N = 0; R = 1;
	Iout1 = 1;
	Iout2 = 1;
}

*/

/*
void MysticDum::inviaStati()
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

*/



