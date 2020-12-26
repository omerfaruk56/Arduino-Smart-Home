#include <Servo.h>
Servo myservo;
void setup() {

  Serial.begin(9600);
}
void loop() {
  gazSensor(0);//A0
  getSicaklik(1);//A1
  fanCalistir(5);
  ultrasonikMesafeSensor(8, 9);
  servoMotor(3);
  odaAydinlatma();
  magnetSensor();
}
//--------------SICAKLIK ÖLÇÜMÜ VE FAN ÇALIŞTIRMA------------------//
float getSicaklik(int sicaklikAnalogPin) {
  float deger;
  deger = analogRead(sicaklikAnalogPin);
  deger = deger * 0.48828125; // (deger / 1023) * 500;
  Serial.print("Sıcaklığımız: ");
  Serial.print(deger);
  Serial.println("°C");
  //delay(200);
  return deger;
}
void fanCalistir(int fanPwmPin)
{
  pinMode(fanPwmPin, OUTPUT);
  if (getSicaklik(1) > 41)
  {
    analogWrite(fanPwmPin, 200);
  }
  else if (getSicaklik(1) > 40)
  {
    analogWrite(fanPwmPin, 150);
  }
  else if (getSicaklik(1) > 39)
  {
    analogWrite(fanPwmPin, 100);
  }
  else
    analogWrite(fanPwmPin, 0);
}
//----------------------ZİL ÇALDIR-------------------------------//
void runBuzzer(int buzzerPin, int frequency, int second)
{
  tone(buzzerPin, frequency);
  delay(second);
  noTone(buzzerPin);
  delay(second);
}
//----------------GAZ SENSÖRÜ-----------------------------//
void gazSensor(int gazAnalogPin)
{
  // pinMode(gazAnalogPin, OUTPUT);
  int gazDeger = analogRead(gazAnalogPin);
  Serial.print("Gaz değeri: ");
  Serial.println(gazDeger);

  if (gazDeger >= 200)
  {
    tone(6, 500);
    delay(1000);
    noTone(6);
    delay(25);
  }
}
//----------------------GARAJ KAPI KONTROLÜ---------------------------//
//------------------------MESAFE SENSÖRÜ--------------------------//
int ultrasonikMesafeSensor(byte echoPin, byte triggerPin)
{
  unsigned long sure;
  double toplamYol;
  int aradakiMesafe;
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  // Aşağıda yapılan süre-mesafe dönüşüm işlemleri
  toplamYol = (double)sure * 0.034;
  aradakiMesafe = toplamYol / 2;
  Serial.print(aradakiMesafe);
  Serial.println("cm\n");
  return aradakiMesafe;

}
//--------------------SERVO MOTOR-------------------------//

void servoMotor(int servoMotorPwmPin)
{
  myservo.attach(servoMotorPwmPin);

  if (ultrasonikMesafeSensor(8, 9) < 5)
  {
    myservo.write(map(512, 0, 1023, 0, 180));
    delay(5000);
  }
  else
  {
    myservo.write(map(0, 0, 1023, 0, 180));
  }

}
int potansiyometre()
{
  int potDeger = analogRead(2);
  Serial.print("potansiyometre");
  Serial.println(potDeger);
  return potDeger;
}
int ldrSensor()
{
  int ldrDeger = analogRead(3);
  Serial.print("LDR sensör: ");
  Serial.println(ldrDeger);
  return ldrDeger;
}
void magnetSensor()
{
  pinMode(11, INPUT);
  int magnetState = digitalRead(11);
  if (magnetState == HIGH) {
    noTone(6);
  } else {
    tone(6, 2000, 200);
  }
}
void odaAydinlatma()
{
  pinMode(10, OUTPUT);
  if (ldrSensor() > 40)
  {
    digitalWrite(10, LOW);
  }
  else
  {
    if (potansiyometre() > 700)
      analogWrite(10, 255);
    else if (potansiyometre() > 500)
      analogWrite(10, 250);
    else if (potansiyometre() > 200)
      analogWrite(10, 245);
    else if (potansiyometre() > 50)
      analogWrite(10, 0);
  }

}
