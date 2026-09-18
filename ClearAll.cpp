/*
https://www.waveshare.com/servo-driver-with-esp32.htm

https://docs.waveshare.com/Servo_Driver_with_ESP32/Resources-And-Documents

https://docs.waveshare.com/Servo_Driver_with_ESP32/Product-Use
*/


#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <SCServo.h>

// display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels, 32 as default.
#define OLED_RESET     (-1) // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ledy
#define NUMPIXELS 2
#define RGB_LED 23
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, RGB_LED, NEO_GRB + NEO_KHZ800);

// serva
#define S_RXD 18
#define S_TXD 19
SMS_STS servos;

void setup() {
	// usb serial
	Serial.begin(115200);

	// display screen
	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
	}
	display.clearDisplay();
	display.display();

	// ledy
	leds.begin();
	leds.clear();
	leds.show();

	// serva
	Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
	servos.pSerial = &Serial1;

	servos.unLockEprom(1);
	servos.writeByte(1, SMS_STS_MODE, 0);
	servos.LockEprom(1);

	servos.unLockEprom(2);
	servos.writeByte(2, SMS_STS_MODE, 0);
	servos.LockEprom(2);

	servos.WritePosEx(1, 0, 100, 50);
	servos.WritePosEx(2, 0, 100, 50);
}

void loop() {
}
