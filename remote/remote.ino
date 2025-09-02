#define SERIAL_BAUD 9600

// Input device variables
#define BUTTON_PIN 4

// Morse code logic variables
#define MIN_HOLD_DURATION 200  // milliseconds
#define MIN_PAUSE_DURATION 200 // milliseconds

// Setup Logic
void setup() {
  Serial.begin(SERIAL_BAUD);

  // INPUT_PULLUP because button connects to GND when pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP);
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

void morseDot() {
  Serial.println("MORSE: DOT");
}

void morseDash() {
  Serial.println("MORSE: DASH");
}
