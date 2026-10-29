#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10

// configurable parameters
#define _DUTY_MIN 600 // servo full clockwise position (0 degree)
#define _DUTY_NEU                                                              \
  ((_DUTY_MIN + _DUTY_MAX) / 2) // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counterclockwise position (180 degree)

#define _POS_START (_DUTY_MIN + 100) // servo start position
#define _POS_END (_DUTY_MAX - 100)   // servo end position

#define _SERVO_SPEED 800 // servo speed limit (unit: degree/second)
#define INTERVAL 20     // servo update interval (unit: msec)

// global variables
unsigned long last_sampling_time; // unit: msec

Servo servo;

int duty_change_per_interval; // maximum duty difference per interval
int duty_target;              // Target duty time
int duty_curr;                // Current duty time

int toggle_interval, toggle_interval_cnt;

void setup() {
  // initialize GPIO pins
  servo.attach(PIN_SERVO);

  duty_target = duty_curr = _POS_START;
  servo.writeMicroseconds(duty_curr);

  // initialize serial port
  Serial.begin(57600);

  // convert angular speed into duty change per interval.
  duty_change_per_interval = (long)(_DUTY_MAX - _DUTY_MIN) * _SERVO_SPEED * INTERVAL / 180000;

  Serial.print("duty_change_per_interval:");
  Serial.println(duty_change_per_interval);

  // initialize variables for servo update.
  toggle_interval = (180.0 / _SERVO_SPEED) * 1000 / INTERVAL;
  toggle_interval_cnt = toggle_interval;

  // initialize last sampling time
  last_sampling_time = 0;
}

void loop() {
  // wait until next sampling time.
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  // adjust duty_curr toward duty_target by duty_change_per_interval
  if (duty_target > duty_curr) {
    duty_curr += duty_change_per_interval;
    if (duty_curr > duty_target)
      duty_curr = duty_target;
  } else {
    duty_curr -= duty_change_per_interval;
    if (duty_curr < duty_target)
      duty_curr = duty_target;
  }

  // update servo position
  servo.writeMicroseconds(duty_curr);

  // output the read value to the serial port
  Serial.print("Min:1000");
  Serial.print(",duty_target:");
  Serial.print(duty_target);
  Serial.print(",duty_curr:");
  Serial.print(duty_curr);
  Serial.println(",Max:2000");

  // toggle duty_target between _DUTY_MIN and _DUTY_MAX.
  if (toggle_interval_cnt >= toggle_interval) {
    toggle_interval_cnt = 0;
    if (duty_target == _POS_START)
      duty_target = _POS_END;
    else
      duty_target = _POS_START;
  } else {
    toggle_interval_cnt++;
  }

  // update last sampling time
  last_sampling_time += INTERVAL;
}
