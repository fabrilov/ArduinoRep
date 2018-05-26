/*
  LBA

 Affinche tutto funzioni serve che venga inizializzata una variabile di tipo node.

*/

#include "Dum.h"


Dum::Dum(){
/* lo scopo di questa funzione è verificare che ci sia tutto quello che serve per chiamare far funzionare questa classe

Queste sono le strutture dati da attivare
*/
//FLO
_numParametri = 0;
//_parametriCS.begin(label_for_cs,_numParametri);

}


void Dum::begin() {
	/* lo scopo di questa funzione è attivare la classee questa classe

	Queste sono le strutture dati da attivare
	_numParametri = TOTAL_N_OF_REG;
	_fileStorageParametri = FILESTORAGEPARAMETRI;
	_parametriCS.begin(label_for_cs,_numParametri);

	*/
  
}

Dum::~Dum(){

}


String  Dum::getSerial() {

	return _seriale;
  
}  

void Dum::resetData(){
	_parametri.resetData();
		
}


 bool Dum::aggiornaStato() {

	 // lo scopo di questa funzione Ã¨ leggere lo stato di tutti i sensori e metterli a disposizione
	 // legge dati Dum e Dum

	 /*  Esempio di uso di questa funzione

	 Process p;
	 char c;


	 uint8_t j, result;
	 int value;
	 String supp;
	 //  const String label_for_cs[TOTAL_N_OF_REG] PROGMEM =
	 // {"UpTime" 0,"Temperature" 1,"Muovi" 2,"Stato" 3,"MemFree" 4,"SwapFree" 5,"Posizione" 6,
	 // "PassiPerSecondo 7","SampleRate" 8,"StepPerChiusura" 9,"Umidita" 10,"TemperaturaPercepita" 11,"Version","DabMgr"};
	 _parametriCS.setValue("UpTime",String(millis() / 1000));
	 float temperature = _dht.readTemperature();
	 float umidita = _dht.readHumidity();
	 float temperaturaPercepita = _dht.computeHeatIndex(temperature,umidita,false);
	 if(temperature != NAN) _parametriCS.setValue("Temperature",String(temperature,2));
	 if(umidita != NAN)_parametriCS.setValue("Umidita",String(umidita,2));
	 if ((temperature != NAN) ||(umidita != NAN)) _parametriCS.setValue("TemperaturaPercepita",String(temperaturaPercepita,2));
	 _parametriCS.setValue("MemFree",catgrepInt("/proc/meminfo","MemFree"));
	 // _parametriCS.setValue("SwapFree",catgrepInt("/proc/meminfo","SwapFree"));

	 */

  _DEB_PRINTLN("Funzione da Definire nelle classi derivate");  
  return true;

}

 void Dum::setNameConf(String nome) {

	 _nomeConfigurazione = nome;
	// example "name":"DConnectBox_V1.0.1",
 }

 String Dum::dataToCS() {
	 return dataToCS(_seriale);
 }

String Dum::dataToCS(String seriale) {
  String data = ""; 
  String supp;
  bool primo_record_inserito = false;
  //bool new_data = true;
  _DEB_PRINT("dentro dum::dataToCs con il seriale:  "); _DEB_PRINTLN(seriale);
  _DEB_PRINT("numero di paramentri da inviare: ");  _DEB_PRINTLN(_numParametri);
  if (_nomeConfigurazione =="") data = "{\"serial\":\"" + seriale + "\",\"param\":{";
  else data = "{\"serial\":\"" + seriale + "\",\"name\":\"" + _nomeConfigurazione + "\",\"param\":{";
  for(int i=0; i <_numParametri; i++) {
     supp = _parametri.getValueIJson(i);
     if (supp != "") {
  	   if ( primo_record_inserito == false) { 
		   data += supp;
  	     primo_record_inserito = true; 
	   }
  	  else data += ',' + supp;
     }  
	}
	data += "}}"; 
	_DEB_PRINTLN("dentro dum::dataToCs Uscita  ");
   return data;

}



String Dum::processCommand(String message){
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
  
/*
Esempio del codcie da mettere qa:....

  if (comm_param[0] == "SetParam") {
  // Qui conviene mettere una
  comando = comm_param[1];
  valore = comm_param[2];
  }
*/
return message;
}

int Dum::unsignet_to_int(uint16_t u){
	
	if (u > 0x7FFF) return  u - 0xFFFF;
	else return u;

}

String Dum::catgrepString(String cat ,String grep){
/*
La funzione fa il cat ed il grep, esegue lo script seguente:

# file di catgrep.sh abinato a questa funzione. Si trova in /evplus/ 
#!/bin/ash

if [ -n "$2" ]
# Verifica se Ã¨ presente un'opzione da riga di comando (non-vuota).
then
  cat $1 | grep $2
else  
  cat $1
fi


Si deve usare questo script perchÃ¨ non funziona con p.run la redirezione dell'output, quindi | > >> etc...
*/


  
      String command= DUM_CATEGREPSCRIPS + cat + " " + grep ;
      String result="";
      Process p; 
      p.runShellCommand(command);
      while (p.available()>0) {
        result += (char)p.read();
       }
    return result;
    
}
String Dum::catgrepInt(String cat ,String grep){
/*
La funzione fa il cat ed il grep, esegue lo script seguente:

# file di catgrep.sh abinato a questa funzione. Si trova in /evplus/ 
#!/bin/ash

if [ -n "$2" ]
# Verifica se Ã¨ presente un'opzione da riga di comando (non-vuota).
then
  cat $1 | grep $2
else  
  cat $1
fi

Si deve usare questo script perchÃ¨ non funziona con p.run la redirezione dell'output, quindi | > >> etc...
*/
   String command= DUM_CATEGREPSCRIPS + cat + " " + grep ;
   String result="";
   char c;
   Process p; 
   p.runShellCommand(command);
   while (p.available()>0) {
     c = p.read();
     if (isDigit(c)) {
     result += (char)c;
    }
   }
  return result;
  
}

void Dum::salvaParametroSuFile(String chiave, String valore, String nomeFile){
/*
Funzione per il salvataggio dei parametri sul file system linux.
Il file dove salvare i parametri Ã¨ sempre lo stesso e si trova in FILESTORAGEPARAMETRI
Prima vengono cancellati i parametri, poi viene appeso al file il dato da salvare.
vengono aggiunti i ":" inizio e fine chiave e '"' inizio e  fine  valore
Se il file non c'Ã¨ viene creato
*/
  
  Process p;
  char buf[nomeFile.length()+1] ;
  nomeFile.toCharArray(buf, nomeFile.length()+1);
  String supp;
  p.begin("sed");
  p.addParameter("-i");
  supp = "/:" + chiave + ":/d";
  p.addParameter(supp);
  p.addParameter(nomeFile);
  p.run();
  //  p.begin("echo");
  //if ( !FileSystem.exists(fileStorageParameri)) FileSystem.remove(nome_file_cs_txt);
  File dataFile = FileSystem.open(buf,FILE_APPEND);
  supp = ':' + chiave + ": \"" + valore + '"'; 
  dataFile.println(supp);
  dataFile.close();    
  
}


void Dum::setSampleRate(int sampleRate) {
	_parametri.setValue("SampleRate", String(sampleRate));
	_invioDatiFast.start();


}

int Dum::stringToInt(String parametro)
{
	
	String valoreNumerico="";
	for (size_t i = 0; i < parametro.length(); i++)
	{
		char c = parametro.charAt(i);
		if (isDigit(c) || (c == '-')) valoreNumerico += c;
	}

	return valoreNumerico.toInt() ;
}

String Dum::getValueFromKey(String stringaDoveCercare, String chiave) {
	// Vedere se aggiungere i controlli per chiave presente e valore no
	int inizioDato, inizioValore, fineValore;
	inizioDato = stringaDoveCercare.indexOf(chiave);
	if (inizioDato != -1) {
		inizioValore = stringaDoveCercare.indexOf('"', inizioDato + 1);
		if (inizioValore == -1) return "";
		fineValore = stringaDoveCercare.indexOf('"', inizioValore + 1);
		if (fineValore == -1) return "";
		return stringaDoveCercare.substring(inizioValore + 1, fineValore);
	}
	return "";
}

void Dum::setSerial(String seriale) {
	// Vedere se aggiungere i controlli per chiave presente e valore no
	_seriale = seriale;

}
