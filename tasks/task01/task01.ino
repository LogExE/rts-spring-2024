const int PINS_COUNT = 5;
const int PINS[PINS_COUNT] = {3, 5, 6, 9, 10};

const int INTER[PINS_COUNT] = {50, 100, 500, 1000, 10000};

unsigned long lastSent[PINS_COUNT];
int state[PINS_COUNT];

void setup() {
  unsigned long micros_now = micros();
  for (int i = 0; i < PINS_COUNT; ++i) {
    pinMode(PINS[i], OUTPUT);
    lastSent[i] = micros_now;
    state[i] = LOW;
  }
}

void loop() {
  unsigned long micros_now = micros();
  for (int i = 0; i < PINS_COUNT; ++i) {
    int diff = micros_now - lastSent[i];
    if (diff > INTER[i]) {
      state[i] = (state[i] == LOW) ? HIGH : LOW;
      digitalWrite(PINS[i], state[i]);
      lastSent[i] = micros_now;
    }
  }
}
