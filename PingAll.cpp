#include <Arduino.h>
#include <SCServo.h>

#define S_RXD 18
#define S_TXD 19

SMS_STS servos;

void setup() {
	Serial.begin(115200);

	Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
	servos.pSerial = &Serial1;

	delay(1000);

	for (int i = 0; i < 10; ++i) {
		Serial.println(servos.Ping(i));
		delay(100);
	}

}

void loop() {
}
