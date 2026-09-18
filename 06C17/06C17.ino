const int ledPin = 7;

int g_period = 10000;  // microseconds
int g_duty = 0;        // 0 ~ 100 %

void set_period(int period) {
  if (period < 100) period = 100;
  if (period > 10000) period = 10000;
  g_period = period;
}

void set_duty(int duty) {
  if (duty < 0) duty = 0;
  if (duty > 100) duty = 100;
  g_duty = duty;
}

void pwm_once() {
  int onTime = (long)g_period * g_duty / 100;
  int offTime = g_period - onTime;

  if (onTime > 0) {
    digitalWrite(ledPin, LOW);
    delayMicroseconds(onTime);
  }
  if (offTime > 0) {
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(offTime);
  }
}

void triangle_fade_1s() {
  long long start = micros();

  while (micros() - start < 1000000) {
    unsigned long elapsed = micros() - start;
    int duty;

    if (elapsed < 500000) {
      duty = elapsed * 100 / 500000;
    } else {
      unsigned long remaining = 1000000 - elapsed;
      duty = remaining * 100 / 500000;
    }

    set_duty(duty);
    pwm_once();
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  set_period(10000);  // 10 ms
  triangle_fade_1s();

  set_period(1000);   // 1 ms
  triangle_fade_1s();

  set_period(100);    // 0.1 ms
  triangle_fade_1s();
  
  delay(1000);
}
