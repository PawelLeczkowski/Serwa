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
	delay(1000);

	servos.WheelMode(1);
	servos.WriteSpe(1, 100, 50);

	servos.WheelMode(2);
	servos.WriteSpe(2, -100, 50);
}

unsigned long delay_led = 0;
byte color = 0;
void colorsUpdate() {
	leds.setBrightness(50);

	unsigned long current_millis = millis();
	if (current_millis - delay_led > 1000) {
		delay_led = current_millis;
		int r = color == 0 ? 255 : 0;
		int g = color == 1 ? 255 : 0;
		int b = color == 2 ? 255 : 0;

		leds.setPixelColor(0, Adafruit_NeoPixel::Color(r, g, b));
		leds.setPixelColor(1, Adafruit_NeoPixel::Color(g, b, r));


		color = ++color % 3;
	}
	leds.show();
}

void screenUpdate(){
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0,0);

	display.println(color);

	display.display();

	int LEDpin = 13;
	pinMode(LEDpin,OUTPUT);
}

void serialCommunication() {
	if (Serial.available()) {
		String s = Serial.readStringUntil('\n');
		Serial.println(s);
		const int angle = s.toInt();
		Serial.println(angle);
	}
}

void loop() {
	serialCommunication();
	screenUpdate();
	colorsUpdate();
}
