// Only one servo should be connected


#include <Arduino.h>
#include <SCServo.h>

#define S_RXD 18
#define S_TXD 19

SMS_STS st;

void setup() {
	Serial.begin(115200);
	delay(1000);

	Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
	st.pSerial = &Serial1;

	delay(1000);

	constexpr int idToChange = 1;
	constexpr int idToSet = 2;

	int model = st.Ping(idToChange);

	if (model != -1) {
		Serial.print("Model: "); Serial.println(model);
	} else {
		Serial.println("No id: "); Serial.println(idToChange);
	}

	delay(1000);

	st.unLockEprom(idToChange);
	st.writeByte(idToChange, SMS_STS_ID, idToSet);
	st.LockEprom(idToChange);

	delay(1000);

	model = st.Ping(idToSet);

	if (model != -1) {
		Serial.print("Model: "); Serial.println(model);
	} else {
		Serial.println("No id: "); Serial.println(idToSet);
	}
}

void loop() {
}
