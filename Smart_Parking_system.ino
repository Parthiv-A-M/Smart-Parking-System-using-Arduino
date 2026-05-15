#include <Servo.h>

// ----- IR SENSOR PINS -----
const int entrySensor = 2;   // Gate IR sensor

const int slot1 = 3;
const int slot2 = 4;
const int slot3 = 5;
const int slot4 = 6;

// ----- SERVO MOTOR -----
Servo gateServo;
const int servoPin = 9;

// ----- SLOT STATUS -----
int s1, s2, s3, s4;

void setup()
{
  Serial.begin(9600);

  pinMode(entrySensor, INPUT);

  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  pinMode(slot3, INPUT);
  pinMode(slot4, INPUT);

  gateServo.attach(servoPin);

  // Gate Closed Position
  gateServo.write(0);

  Serial.println("SMART PARKING SYSTEM");
}

void loop()
{
  // ----- READ SLOT STATUS -----
  s1 = digitalRead(slot1);
  s2 = digitalRead(slot2);
  s3 = digitalRead(slot3);
  s4 = digitalRead(slot4);

  Serial.println("-------- SLOT STATUS --------");

  if (s1 == LOW)
    Serial.println("Slot 1 : Occupied");
  else
    Serial.println("Slot 1 : Empty");

  if (s2 == LOW)
    Serial.println("Slot 2 : Occupied");
  else
    Serial.println("Slot 2 : Empty");

  if (s3 == LOW)
    Serial.println("Slot 3 : Occupied");
  else
    Serial.println("Slot 3 : Empty");

  if (s4 == LOW)
    Serial.println("Slot 4 : Occupied");
  else
    Serial.println("Slot 4 : Empty");

  // ----- CHECK AVAILABLE SLOTS -----
  int availableSlots = 0;

  if (s1 == HIGH) availableSlots++;
  if (s2 == HIGH) availableSlots++;
  if (s3 == HIGH) availableSlots++;
  if (s4 == HIGH) availableSlots++;

  Serial.print("Available Slots: ");
  Serial.println(availableSlots);

  // ----- ENTRY SENSOR -----
  int carAtGate = digitalRead(entrySensor);

  // If car detected and slots available
  if (carAtGate == LOW && availableSlots > 0)
  {
    Serial.println("Car Detected at Gate");
    Serial.println("Opening Gate");

    gateServo.write(90); // Open Gate
    delay(3000);

    gateServo.write(0);  // Close Gate
    Serial.println("Closing Gate");
  }

  // If parking full
  else if (carAtGate == LOW && availableSlots == 0)
  {
    Serial.println("Parking Full");
  }

  Serial.println();
  delay(1000);
}
