const int triggerPin = 12;
const int echoPin = 11;
int beeperPin = 13;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(beeperPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  double duration, inches;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  inches = microsecondsToInches(duration);

  if (inches < 10) {
    
  }
  
  Serial.print(inches);
  Serial.print("in");
  Serial.println();

  delay(100);
}

float microsecondsToInches(float microseconds) {
  return microseconds / 74 / 2;
}
