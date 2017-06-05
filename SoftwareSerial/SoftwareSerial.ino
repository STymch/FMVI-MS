/*
 Name:		SoftwareSerial.ino
 Created:	05.06.2017 13:43:41
 Author:	Sergiy Tymchenko
*/

// SoftwareSerial library
#include <SoftwareSerial.h>

const int   LED_PIN = 13;				// LED pin
const int	RX_PIN = 10;				// Software UART RX pin, connect to TX of Bluetooth HC-05 
const int	TX_PIN = 11;				// Software UART TX pin, connect to RX of Bluetooth HC-05
const long  DR_HARDWARE_COM = 38400;	// Data rate for hardware COM
const long  DR_SOFTWARE_COM = 38400;	// Data rate for software COM
int			nLEDState = LOW;			// LED state

// SoftwareSerial* BTSerial;// (RX_PIN, TX_PIN); // Software UART RX, TX for Bluetooth HC-05
SoftwareSerial BTSerial(RX_PIN, TX_PIN);

void setup() {
	// Define pin modes for software TX, RX:
	pinMode(RX_PIN, INPUT);
	pinMode(TX_PIN, OUTPUT);

	// Set the data rate and open hardware COM port:
	Serial.begin(DR_HARDWARE_COM);
	BTSerial.begin(DR_SOFTWARE_COM);
	BTSerial.println("Starting BT software COM ...");

	// Wait for serial port to connect. Needed for native USB port only
	while (!Serial);
	Serial.println("Starting hardware COM ...");
	
	// Set pin mode for LED pin
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, nLEDState);

	delay(1000);
}

void loop() {
	if (BTSerial.available()) {
		Serial.write(BTSerial.read());
		nLEDState = !nLEDState;
		digitalWrite(LED_PIN, nLEDState);
		
		Serial.println("BT COM Read!");
	}

	if (Serial.available()) {
		BTSerial.write(Serial.read());
		nLEDState = !nLEDState;
		digitalWrite(LED_PIN, nLEDState);

		Serial.println("Hardware COM Read!");
	}
}


/*
#include <SoftwareSerial.h>
#include <Time.h>

int gLedPin = 13;
int gRxPin = 10;
int gTxPin = 11;

SoftwareSerial BTSerial(gRxPin, gTxPin);

void setup() {
	BTSerial.begin(38400);
	Serial.begin(384000);
	delay(500);
}

void loop() {
	if (BTSerial.available()) {
		Serial.write(BTSerial.read());
	}
	if (Serial.available()) {
		BTSerial.write(Serial.read());
	}
}
*/