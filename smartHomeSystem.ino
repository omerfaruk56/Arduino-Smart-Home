#include <Servo.h>
Servo myservo;
void setup() {

  Serial.begin(9600);
}
void loop() {
  getSicaklik(1);
 
}
float getSicaklik(int sicaklikAnalogPin) {
  float deger;
  deger = analogRead(sicaklikAnalogPin);
  deger = deger * 0.48828125;
  Serial.print("Sıcaklığımız: ");
  Serial.print(deger);
  Serial.println("°C");
  return deger;
  //------------------------------Kodların Devamı için---------------------------//
  //-----------omerfaruk56@live.com adresinden iletişime geçebilirsiniz----------//
}
