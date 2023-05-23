#include <SoftwareSerial.h>
SoftwareSerial mega(A1, A0); // RX, TX
#include <Wire.h>
#define DS1307_ADDRESS 0x68

float max_V = 20.3;
float akumas = 0.0;

int akumo_pin = A2;
int data[10];
float suma = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 2000;
int second, minute, hour, weekDay, monthDay, month, year;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(akumo_pin, INPUT);
  mega.begin(9600);
  data[0] = 255;
  laiko_gavimas();
  delay(5000);
  Serial.print("Pirminis baterijos nuskaitymas: ");
  for (int u = 0; u <= 4; u++) {
    laiko_gavimas();
    int akumo_analogas = analogRead(akumo_pin);
    akumas = akumo_analogas * (max_V / 1024.0);
    // if(akumas<=8.00){akumas = 0.0;}
    data[1] = int(akumas);
    data[2] = (akumas - int(akumas)) * 100;
    Serial.println(akumas);
    Serial.println("-----");
    for (int i = 0; i <= 8; i++) {
      mega.write(data[i]);
      Serial.println(data[i]);
    }
    delay(5000);
  }
}

// the loop routine runs over and over again forever:
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    int akumo_analogas = analogRead(akumo_pin);
    akumas = akumo_analogas * (max_V / 1024.0);
    if (akumas <= 8.00) {
      akumas = 0.0;
    }
    laiko_gavimas();
    
    data[1] = int(akumas);
    data[2] = (akumas - int(akumas)) * 100;
    siuntimas();
    previousMillis = currentMillis;
    suma = 0;
  }
}
void siuntimas() {
    Serial.println("-----");
    for (int i = 0; i <= 8; i++) {
      mega.write(data[i]);
      Serial.println(data[i]);
    }
}

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
void laiko_gavimas() {
  Wire.beginTransmission(DS1307_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);

  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0b111111);
  weekDay = bcdToDec(Wire.read());
  monthDay = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
  
  data[3] = hour;
  data[4] = minute;
  data[5] = weekDay;
  data[6] = monthDay;
  data[7] = month;
  data[8] = year;
}

