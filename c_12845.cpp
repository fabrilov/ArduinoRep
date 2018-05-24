/*
  LBA

 Affinche tutto funzioni serve che venga inizializzata una variabile di tipo node.

*/

#include "c_12845.h"

//#include <ModbusMaster.h>


C_12845::~C_12845(){
	
}

C_12845::C_12845() {
	_numParametri = TOTAL_N_OF_REG_C;
}


void C_12845::begin(uint8_t _slave_id, ModbusMaster *Nodo) {

	SerialUSB.print("dentro C_12845.begin");
	SerialUSB.print("_numParamentri vale: ");
	SerialUSB.println(_numParametri);
	slave_id = _slave_id;
	Modbus = Nodo;
	(*Modbus).SlaveAddress(slave_id);
	_parametri.begin(label_for_cs, _numParametri);
}
///* */

bool  C_12845::aggiornaStato() {
  bool lettura_ok = true;
	uint8_t j, result;
	int value;
    delayMicroseconds(DELAY_BETWEEN_READS); 
    result = (*Modbus).readInputRegisters(pack_1.base-1, pack_1.n_dati);
    if (result == (*Modbus).ku8MBSuccess)
       { for (j = 0; j < pack_1.n_dati; j++)
          { pack_1.regs[j] = ((*Modbus).getResponseBuffer(j));
          }
     } else {
		 for (j = 0; j < pack_1.n_dati; j++)
          {  pack_1.regs[j] = NOT_READ_VALUE;
          }
		lettura_ok = false;
	 }
    
    delayMicroseconds(DELAY_BETWEEN_READS); 
	(*Modbus).clearResponseBuffer();
    if (lettura_ok) result = (*Modbus).readDiscreteInputs(pack_2.base -1, pack_2.n_dati);
	(*Modbus).readDiscreteInputs(pack_2.base - 1, pack_2.n_dati);
	_DEB_PRINTLN("scrittura Array dati letti da Centralina antincnedio Read Discrete imputs");	

    if (result == (*Modbus).ku8MBSuccess)
       { for (j = 0; j <= (pack_2.n_dati / 16); j++)
          { pack_2.regs[j] = ((*Modbus).getResponseBuffer(j));
			#ifdef C_12845_DEBUG

			SerialUSB.println(pack_2.regs[j], HEX);

			#endif // C_12845_DEBUG
          }
	 } else { for (j = 0; j < pack_2.n_dati; j++)
          { pack_2.regs[j] = NOT_READ_VALUE;
          }
	lettura_ok = false;
	 }
   

	
		 


//    delayMicroseconds(DELAY_BETWEEN_READS); 
//    if (lettura_ok) result = (*Modbus).readHoldingRegisters(pack_3.base-1, pack_3.n_dati);
//    if (result == (*Modbus).ku8MBSuccess)
//       { for (j = 0; j < pack_3.n_dati; j++)
//          { pack_3.regs[j] = ((*Modbus).getResponseBuffer(j));
//          }
//       } else {for (j = 0; j < pack_3.n_dati; j++)
//          {pack_3.regs[j] = NOT_READ_VALUE;
//          }
//		lettura_ok = false;
//	} 
//   delayMicroseconds(DELAY_BETWEEN_READS); 
//    if (lettura_ok) result = (*Modbus).readHoldingRegisters(pack_4.base-1, pack_4.n_dati);
//    if (result == (*Modbus).ku8MBSuccess)
//       { for (j = 0; j < pack_4.n_dati; j++)
//          { pack_4.regs[j] = ((*Modbus).getResponseBuffer(j));
//          }
//       } else {for (j = 0; j < pack_4.n_dati; j++)
//          {  pack_4.regs[j] = NOT_READ_VALUE;
//          }
//		 lettura_ok = false;
//	 }  
//    delayMicroseconds(DELAY_BETWEEN_READS); 
//    if (lettura_ok) result = (*Modbus).readHoldingRegisters(pack_5.base-1, pack_5.n_dati);
//    if (result == (*Modbus).ku8MBSuccess)
//       { for (j = 0; j < pack_5.n_dati; j++)
//          { pack_5.regs[j] = ((*Modbus).getResponseBuffer(j));
//          }
//       } else { for (j = 0; j < pack_5.n_dati; j++)
//          { pack_5.regs[j] = NOT_READ_VALUE;
//          }       
//	      lettura_ok = false;
//	 } 
//		  
//    delayMicroseconds(DELAY_BETWEEN_READS); 
//    if (lettura_ok) result = (*Modbus).readHoldingRegisters(pack_6.base-1, pack_6.n_dati);
//    if (result == (*Modbus).ku8MBSuccess)
//       { for (j = 0; j < pack_6.n_dati; j++)
//          { pack_6.regs[j] = ((*Modbus).getResponseBuffer(j));
//          }
//       } else { for (j = 0; j < pack_6.n_dati; j++)
//          { pack_6.regs[j] = NOT_READ_VALUE;
//          }       
//		  lettura_ok = false;
//	 } 
	 

	dato_ok = lettura_ok;
	condizionamentoDati();
    return lettura_ok;

}








void C_12845::condizionamentoDati() {
	String data = "";
	String supp;
	bool primo_record_inserito = false;
	bool new_data = true;

	for (int i = 0; i <_numParametri; i++) {
		if (label_for_cs[i].length() > 0) {
			if ((regs[i] == NOT_READ_VALUE) || (regs[i] == NOT_READ_VALUE_1)) {
				supp = STRING_NOT_VALID_VALUE;
				if (i == 30) supp = WIDGET_DISABLED;
				if (i == 31) supp = WIDGET_DISABLED;
				if (i == 41) supp = WIDGET_DISABLED;
				if (i == 42) supp = WIDGET_DISABLED;
				if (i == 37) supp = WIDGET_DISABLED;
			}
			else { // gestione delle eccesioni: versioni software
				supp = String(regs[i]);
				// temperature - conversione in intero con segno 
				if (i == 30) supp = String(unsignet_to_int(regs[i]));
				if (i == 31) supp = String(unsignet_to_int(regs[i]));
				if (i == 41) supp = String(unsignet_to_int(regs[i]));
				if (i == 42) {
					if (unsignet_to_int(regs[i]) > -50) supp = String(unsignet_to_int(regs[i]));
					else supp = WIDGET_DISABLED;
				}

				// Versioni software - combinazione parte alta e parte bassa				   
				if (i == 62) supp = "\"" + supp + "." + String(regs[i + 1]) + "\"";
				if (i == 64) supp = "\"" + supp + "." + String(regs[i + 1]) + "\"";
				if (i == 66) supp = "\"" + supp + "." + String(regs[i + 1]) + "\"";
				// ore di funzionamento 
				if (i == 37) { supp = String((regs[i] << 16) + regs[i + 1]); }
			};
			// eccezione per gestire l'invio della versione software nello small in cui il prima valore Ã¨ 0xFFFF 
			if ((i == 64) && (regs[i] == NOT_READ_VALUE_1)) supp = "\"0." + String(regs[i + 1]) + "\"";
			_parametri.setValue(label_for_cs[i], supp);
			// data += "\"" + label_for_cs[i] + "\":" + supp ;
		}

	}

	// gestione eccezioni

	// eccezione Modi di regolazione
	// "Setpoint RPM"  "Ext signal type"  "Regulation Setpoint" "Regulation T Max"

	//pressione diff proporzionale
	if (_parametri.getValue("Regulation mode") == "0") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Ext signal type", WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}

	// pressione diff prop con ingresso PWM 
	if (_parametri.getValue("Regulation mode") == "1") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		// _parametri.setValue("Ext signal type",WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}

	// pressione diff proporzionale con set poin tin T
	if (_parametri.getValue("Regulation mode") == "2") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		_parametri.setValue("Ext signal type", WIDGET_DISABLED);
		//_parametri.setValue("Regulation T Max",WIDGET_DISABLED); 
	}

	// pressione diff costante
	if (_parametri.getValue("Regulation mode") == "3") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		// _parametri.setValue("Regulation Setpoint",WIDGET_DISABLED);
		_parametri.setValue("Ext signal type", WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}
	// pressione diff costante con ingresso PWM
	if (_parametri.getValue("Regulation mode") == "4") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		//_parametri.setValue("Ext signal type",WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}

	// pressione diff costante in funzione di T
	if (_parametri.getValue("Regulation mode") == "5") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		_parametri.setValue("Ext signal type", WIDGET_DISABLED);
		//_parametri.setValue("Regulation T Max",WIDGET_DISABLED); 
	}

	// curva fissa
	if (_parametri.getValue("Regulation mode") == "6") {
		//_parametri.setValue("Setpoint RPM",WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		_parametri.setValue("Ext signal type", WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}

	// curva fissa con ingresso PWM
	if (_parametri.getValue("Regulation mode") == "7") {
		_parametri.setValue("Setpoint RPM", WIDGET_DISABLED);
		_parametri.setValue("Regulation Setpoint", WIDGET_DISABLED);
		//_parametri.setValue("Ext signal type",WIDGET_DISABLED);
		_parametri.setValue("Regulation T Max", WIDGET_DISABLED);
	}

	// Economy
	if (_parametri.getValue("Economy") == "0") {
		_parametri.setValue("Economy Setpoint Reduction", WIDGET_DISABLED);
	}



}


String C_12845::processCommand(String message) {
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
	int id_slave;
	String  valore, risposta, valore_riletto;
	int result; int i = 0;
	unsigned int registro_modbus, value, modbus_slave_add;
	String parameters[MAX_PARAMETERS_FROM_CS];


	// parser che prende la stringa di comando e la posiziona su un array
	for (int j = 0; j < MAX_PARAMETERS_FROM_CS; j++) {
		parameters[j] = "";
	}
	_DEB_PRINT("Comando ricevuto dal lato linux: "); _DEB_PRINTLN(message);

	while ((message.indexOf('/') > 0) || (i < MAX_PARAMETERS_FROM_CS - 1)) {
		parameters[i] = message.substring(0, message.indexOf('/'));
		message = message.substring(message.indexOf('/') + 1);
		i++;
	}

	parameters[i] = message;
	risposta = "InvalidCommand";

	if (parameters[0] == "SetParam") {
		// Scrittura su modbus: SetParam/chiave/valore
		// risposta: SetParam/chiave/valore_riletto
		registro_modbus = 0;
		for (i = 0; i < _numParametri; i++) {
			if (parameters[1] == label_for_cs[i]) {
				registro_modbus = Mreg_for_cs[i];
				break;
			}
		}
		value = parameters[2].toInt();

		//      _DEB_PRINT("Add:  ");         _DEB_PRINTLN(registro_modubus);
		//      _DEB_PRINT("value:  ");       _DEB_PRINTLN(value);
		if (registro_modbus != 0) {
			valore_riletto = String(write(registro_modbus - 1, value));
			_DEB_PRINT("Scritto valore e riletto "); _DEB_PRINTLN(valore_riletto);
			return parameters[0] + SEPARATORE + parameters[1] + SEPARATORE + valore_riletto;
		}
		else return parameters[0] + SEPARATORE + "Invalid value";
	}

	return risposta;

}



