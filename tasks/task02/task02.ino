#include <TaskManagerIO.h>

const int PINS_COUNT = 5;
const int PINS[PINS_COUNT] = {3, 5, 6, 9, 10};
const TimePeriod INTER[PINS_COUNT] = {repeatMillis(10), repeatMillis(1), repeatMicros(500), repeatMicros(100), repeatMicros(50)};

taskid_t tasks[PINS_COUNT];

class Exec : public Executable {
private:
  int _state = LOW;

public:
  int pin;
  void exec() override {
      digitalWrite(pin, _state);
      _state = (_state == LOW) ? HIGH : LOW;
  }
} execs[PINS_COUNT];

void setup() {
  for (int i = 0; i < PINS_COUNT; ++i) {
    execs[i] = Exec();
    execs[i].pin = PINS[i];
    pinMode(PINS[i], OUTPUT);
    tasks[i] = taskManager.schedule(INTER[i], &execs[i]);
  }
}

void loop() {
  taskManager.runLoop();
}

