#include <SoftwareSerial.h>
#define SERIAL_BAUD 9600

// Bluetooth variables
SoftwareSerial bt(2, 3);  // (Tx, Rx) of BT
#define BLUETOOTH_BAUD 38400
#define BT_SIGNAL_DOT '2'
#define BT_SIGNAL_DASH '3'

// Input device variables
#define BUTTON_PIN 4

// Output device variables
#define LED_RED_PIN 5
#define LED_GREEN_PIN 6
#define LED_BLUE_PIN 7

// Morse code logic variables
#define MIN_HOLD_DURATION 200   // milliseconds
#define MIN_PAUSE_DURATION 200  // milliseconds
#define DOT_LED LED_GREEN_PIN
#define DASH_LED LED_BLUE_PIN
#define LED_ON_DURATION 10  // milliseconds

// Setup Logic
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Started remote");

  // LEDs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  // INPUT_PULLUP because button connects to GND when pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  bt.begin(BLUETOOTH_BAUD);

  Serial.println("Initialized remote!");
}

// Loop logic (main code)
void loop() {

  bool button_state = digitalRead(BUTTON_PIN);

  if (button_state == LOW) {
    handleButtonPress(BUTTON_PIN);
  }
}

/* Function called when the button is pressed
 * Arguments: int (pin)
 * Returns: None
 */
void handleButtonPress(int button_pin) {

  unsigned long press_start_time = millis();
  while (digitalRead(button_pin) == LOW) {
    // Wait for button release
  }

  unsigned long press_duration = millis() - press_start_time;

  if (press_duration >= MIN_HOLD_DURATION) {
    // Long press
    morseDash();
  } else {
    // Short press
    morseDot();
  }

  delay(MIN_PAUSE_DURATION);
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

  sendBluetoothSignal(BT_SIGNAL_DOT);
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

  sendBluetoothSignal(BT_SIGNAL_DASH);
}

/* Function to send a signal via bluetooth
 * Arguments: char (signal to send)
 * Returns: None
 */
void sendBluetoothSignal(char signal) {
  // Serial.print("BLUETOOTH: sending -> ");
  // Serial.println(signal);

  bt.write(signal);
}
