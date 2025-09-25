// Arduino pin assignment
#define PIN_LED 9        // PWM 출력 가능 핀
#define PIN_TRIG 12      // sonar sensor TRIGGER
#define PIN_ECHO 13      // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficent to convert duration to distance

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // sonar TRIGGER
  pinMode(PIN_ECHO, INPUT);   // sonar ECHO
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  float distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance
  int brightness = 0;

  if (distance <= 100) {
    brightness = 255;  // 100mm 이하 → LED 꺼짐
  } else if (distance <= 200) {
    // 100mm -> 0, 200mm -> 255
    brightness = map(distance, 100, 200, 225, 0);
  } else if (distance <= 300) {
    // 200mm -> 255, 300mm -> 0
    brightness = map(distance, 200, 300, 0, 255);
  } else {
    brightness = 255;  // 300mm 초과 → LED 꺼짐
  }

  // PWM 출력 (0~255)
  analogWrite(PIN_LED, brightness);

  // Serial 출력
  Serial.print("distance: ");  Serial.print(distance);
  Serial.print(" mm, Brightness: "); Serial.println(brightness);
  
  delay(INTERVAL);
}

// 초음파 거리 측정 (단위: mm)
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}
