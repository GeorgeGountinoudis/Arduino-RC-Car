/*George Gkountinoudis - UTH
 2020 - GPLv3
 Feel free to use, improve and share! */

char t;

int trigPin = 8;    // TRIG pin
int echoPin = 9;    // ECHO pin
float duration_us, distance_cm = 50;
const int buzzer = 7; // Buzzer to arduino pin 7

void setup() {

  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(13, OUTPUT);  // Left motors forward
  pinMode(12, OUTPUT);  // Left motors reverse
  pinMode(11, OUTPUT);  // Right motors forward
  pinMode(10, OUTPUT);  // Right motors reverse
  Serial.begin(9600);


  pinMode(trigPin, OUTPUT); // Configure the trigger pin to output mode
  pinMode(echoPin, INPUT); // Configure the echo pin to input mode

}

void loop() {

  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  } 
  switch (t) {

    case 'F' :          // Move forward(all motors rotate in forward direction)
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);

    case 'B' :          // Move reverse (all motors rotate in reverse direction)
    digitalWrite(12, HIGH);
    digitalWrite(10, HIGH);

    case 'R' :         // Turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    digitalWrite(11, HIGH);

    case 'L' :         // Turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    digitalWrite(13, HIGH);

    case 'S' :         // STOP (all motors stop)
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration_us = pulseIn(echoPin, HIGH); // Measure duration of pulse from ECHO pin
  distance_cm = 0.017 * duration_us; // Calculate the distance
  if ((distance_cm <= 30) && (distance_cm > 20)) {

    tone(buzzer, 700); // Send 0.700KHz sound signal...
    delay(35);         // ...for 0.35 sec
    noTone(buzzer);    // Stop sound...
  }

  if ((distance_cm <= 20) && (distance_cm > 10)) {

    tone(buzzer, 850); // Send 0.850KHz sound signal...
    delay(20);         // ...for 0.020 sec
    noTone(buzzer);    // Stop sound...
  }

  if (distance_cm <= 10) {

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(5);           // ...for 0.005 sec
    noTone(buzzer);     // Stop sound...
  }

  delay(20);
}
