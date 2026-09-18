/*
https://www.waveshare.com/servo-driver-with-esp32.htm

https://docs.waveshare.com/Servo_Driver_with_ESP32/Resources-And-Documents

https://docs.waveshare.com/Servo_Driver_with_ESP32/Product-Use
*/


#include <Arduino.h>
#include <SCServo.h>

#define S_RXD 18
#define S_TXD 19
SMS_STS servos;

void setup() {
	// usb serial
	Serial.begin(115200);

	// serva
	Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
	servos.pSerial = &Serial1;

	// ze strony botlandu (rozdzielcznosc) 360 stopni = 4096 krokow
	// https://botland.com.pl/serwa-praca-ciagla-360/21963-30kg-serial-bus-servo-serwomechanizm-z-enkoderem-magnetycznym-360-stopni-waveshare-22414.html

	constexpr int angle = 0;
	s16 position = (angle * 4096) / 360 ;
	servos.WritePosEx(2, position, 16960, 50);
}

void loop() {
}
