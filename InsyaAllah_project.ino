#include <SimpleDHT.h>
#include <Servo.h>

//Sensor DHT11
int pinDHT11 = A0;

//Sensor LDR-Light
int LDR = A2;

//Soil Moisture Sensor
int sensorMpin = A1;
int sensorMvalue = 0;
int percentMvalue = 0;

SimpleDHT11 dht11(pinDHT11);
Servo servoKu;

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor suhu");
  servoKu.attach(6); //servo ada di pin 6
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A2, INPUT);
  servoKu.write(0);
}

void loop() {
  Serial.println("Hasil pembacaan sensor kelembaban tanah");
  
  //Baca data analog untuk soil moisture
  sensorMvalue = analogRead(sensorMpin);
  Serial.print("Data Analog = ");
  Serial.println(sensorMvalue);
  percentMvalue = map(sensorMvalue, 1023, 200, 0, 100);
  Serial.print("Persentase = ");
  Serial.print(percentMvalue);
  Serial.println("%");
  Serial.println("=====================");
  if(percentMvalue < 50)
  {
    servoKu.write(90);
    delay(3000);
  }
  else
  {
    servoKu.write(0);
  }

  //Baca data analog untuk sensor LDR
  int LDRvalue = analogRead(LDR);
  Serial.print("Intensitas cahaya = ");
  Serial.println(LDRvalue);
  Serial.println("=====================");
  if(LDRvalue < 300)
  {
    digitalWrite(9, HIGH);
  }
  else
  {
    digitalWrite(9, LOW);
  }
  
  //Baca data analog untuk sensor suhu
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(1000);
    return;
  }
  Serial.println("Hasil pembacaan sensor DHT11");
  Serial.print("Suhu sekarang = ");
  Serial.print((int)temperature); 
  Serial.println(" *C, "); 
  Serial.print("Kelembaban ruangan = ");
  Serial.print((int)humidity); 
  Serial.println(" H");
  Serial.println("=============================================");
  if((int)temperature < 30)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
   
  delay(3000);
}
