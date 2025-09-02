#include <SoftwareSerial.h>
#define SERIAL_BAUD 9600

// Bluetooth variables
SoftwareSerial bt(2, 3);  // (Tx, Rx) of BT
#define BLUETOOTH_BAUD 38400
#define BT_SIGNAL_DOT '2'
#define BT_SIGNAL_DASH '3'

// Output device variables
#define LED_RED_PIN 5
#define LED_GREEN_PIN 6
#define LED_BLUE_PIN 7

// Morse code logic variables
#define DOT_LED LED_GREEN_PIN
#define DASH_LED LED_BLUE_PIN
#define LED_ON_DURATION 10  // milliseconds

// Setup Logic
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Started base");

  // LEDs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  bt.begin(BLUETOOTH_BAUD);

  Serial.println("Initialized base!");
}

void loop() {

  // Bluetooth handling
  if (bt.available()) {
    handleBluetoothSignal(bt.read());
  }
}

/* Function to signal a dot in morse code
 * Arguments: None
 * Returns: None
 */
void morseDot() {
  Serial.print(".");
  digitalWrite(DOT_LED, HIGH);
  delay(LED_ON_DURATION);
  digitalWrite(DOT_LED, LOW);
}

/* Function to signal a dash in morse code
 * Arguments: None
 * Returns: None
 */
void morseDash() {
  Serial.print("_");
  digitalWrite(DASH_LED, HIGH);
  delay(LED_ON_DURATION);
  digitalWrite(DASH_LED, LOW);
}

/* Function called when a bluetooth signal is recieved
 * Use the switch-case to handle signals
 * Arguments: char (signal from serial)
 * Returns: None
 */
void handleBluetoothSignal(char signal) {

  switch (signal) {
    case BT_SIGNAL_DOT:
      morseDot();
      break;
    case BT_SIGNAL_DASH:
      morseDash();
      break;
  }
}
