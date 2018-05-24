#include "cea_12845.h"



CEA_12845::CEA_12845()
{
		_numParametri = TOTAL_N_OF_REG_CEA;
}


CEA_12845::~CEA_12845()
{
}

void CEA_12845::begin(uint8_t _slave_id, ModbusMaster *Nodo) {

	SerialUSB.print("dentro CEA_12845.begin");
	SerialUSB.print("_numParamentri vale: ");
	SerialUSB.println(_numParametri);
	slave_id = _slave_id;
	Modbus = Nodo;
	(*Modbus).SlaveAddress(slave_id);
	_parametri.begin(label_for_cs, _numParametri);
}

bool  CEA_12845::aggiornaStato() {
	bool lettura_ok = true;
	uint8_t j, result;
	int value;
	delayMicroseconds(DELAY_BETWEEN_READS);
	//(*Modbus).SlaveAddress(slave_id);
	//for(int i=0; i < _numParametri ; i++) {old_regs[i] = regs[i];}
	result = (*Modbus).readInputRegisters(pack_1.base - 1, pack_1.n_dati);
	if (result == (*Modbus).ku8MBSuccess)
	{
		for (j = 0; j < pack_1.n_dati; j++)
		{
			pack_1.regs[j] = ((*Modbus).getResponseBuffer(j));
		}
	}
	else {
		for (j = 0; j < pack_1.n_dati; j++)
		{
			pack_1.regs[j] = NOT_READ_VALUE;
		}
		lettura_ok = false;
	}

	delayMicroseconds(DELAY_BETWEEN_READS);
	(*Modbus).clearResponseBuffer();
	if (lettura_ok) result = (*Modbus).readDiscreteInputs(pack_2.base - 1, pack_2.n_dati);
	(*Modbus).readDiscreteInputs(pack_2.base - 1, pack_2.n_dati);
	_DEB_PRINTLN("scrittura Array dati letti da Centralina antincnedio Read Discrete imputs");

	if (result == (*Modbus).ku8MBSuccess)
	{
		for (j = 0; j <= (pack_2.n_dati / 16); j++)
		{
			pack_2.regs[j] = ((*Modbus).getResponseBuffer(j));
#ifdef CEA_12845_DEBUG

			SerialUSB.println(pack_2.regs[j], HEX);

#endif // CEA_12845_DEBUG
		}
	}
	else {
		for (j = 0; j < pack_2.n_dati; j++)
		{
			pack_2.regs[j] = NOT_READ_VALUE;
		}
		lettura_ok = false;
	}




	condizionamentoDati();
	dato_ok = lettura_ok;
	return lettura_ok;

}







void CEA_12845::condizionamentoDati() {
	String data = "";
	String supp;
	bool primo_record_inserito = false;
	bool new_data = true;
	_DEB_PRINTLN("Dentro CEA_12845 data_to_CS  ");
	_DEB_PRINT("Dentro CEA_12845 TOTAL_N_OF_REG:  ");  _DEB_PRINTLN(_numParametri);
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

