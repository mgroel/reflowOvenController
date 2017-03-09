/* http://rn-wissen.de/wiki/index.php/Gleitender_Mittelwert_in_C */

#include "floatAverage.h"


void floatAverageClass::setAverage(FloatAverage_t i_DefaultValue) { 
 	// Den Buffer mit dem Initialisierungswert fuellen:
	for (uint8_t i = 0; i < SIZE_OF_AVG; ++i) {
		this->aData[i] = i_DefaultValue;
	}

	// Der naechste Wert soll an den Anfang des Buffers geschrieben werden:
	this->IndexNextValue = 0;
} 


void floatAverageClass::AddToFloatAverage(FloatAverage_t i_ui16NewValue) {
	// Neuen Wert an die dafuer vorgesehene Position im Buffer schreiben.
	this->aData[this->IndexNextValue] =	i_ui16NewValue;
	
	// Der naechste Wert wird dann an die Position dahinter geschrieben.
	this->IndexNextValue++;
	
	// Wenn man hinten angekommen ist, vorne wieder anfangen.
	this->IndexNextValue %= SIZE_OF_AVG;
}

FloatAverage_t floatAverageClass::getAverage() {
	TempSum_t TempSum=0;		//0 by default, but only on first init! so it has to be initialized here
	
	// Durchschnitt berechnen
	for (uint8_t i = 0; i < SIZE_OF_AVG; ++i) {
		TempSum += this->aData[i];
	}
	
	// Der cast is OK, wenn tFloatAvgType und tTempSumType korrekt gewaehlt wurden.
	FloatAverage_t o_Result = (FloatAverage_t) (TempSum / SIZE_OF_AVG);
	
	return o_Result;
}


FloatAverage_t floatAverageClass::getLeastAddedValue() {
	if(this->IndexNextValue==0)
		return this->aData[SIZE_OF_AVG-1];
	else
		return this->aData[this->IndexNextValue-1];
}

FloatAverage_t floatAverageClass::getOldestAddedValue() {
	return this->aData[this->IndexNextValue];
}



