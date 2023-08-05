#include <DHT.h>
#include <ShiftRegister74HC595.h>
#include <Wire.h>
// create a global shift register object
// parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<1> sr(2, 4, 3);

#include <SoftwareSerial.h>;
#define RX 9 //Connect to the TX pin of the HC-12
#define TX 10 //Connect to the RX pin of the HC-12
SoftwareSerial robotas(RX, TX);

#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE, 11);
#define DS1307_ADDRESS 0x68

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already
int interval = 1000;

float akumas, krovimo_srove;
//////// MYGTUKAI /////////
#define atidarymo_pin A2
#define uzdarymo_pin  A3
#define centro_pin    A7
#define stogo_pin     A6

////// SHIFTTO pinai //////////////
#define Led_vidus        0
#define Led_lauko        1
#define Namu_perimetras  2
#define Perimetras       4
#define Krovimo          3
#define variklio_atidarymo 5
#define variklio_uzdarymo 6

byte duru_busena = 2;
byte duru_state = 2;
int atidarymo_mygtukas, uzdarymo_mygtukas, centro_mygtukas, stogo_mygtukas;
int siusta = 0;
int aptiktas_robotas = 0;
int busena = 1;
int laido_modas = 0;
int d[4] = {0, 0, 0, 0};

int lietaus_pin = 6;
int lietus = 0;
void setup() {
  sr.setAllLow(); // set all pins LOW
  pinMode(atidarymo_pin, INPUT_PULLUP);
  pinMode(uzdarymo_pin, INPUT_PULLUP);
  pinMode(lietaus_pin, INPUT);
  Serial.begin(9600);
  robotas.begin(9600);
  dht.begin();
  Wire.begin();

  delay(10);
  Lauko_led(0);
  Vidaus_led(0);
  //mygtuku_nuskaitymas();
   Serial.println("Testas");

    delay(5000);
    uzdarymas_vartu();
    delay(5000);
    atidarymas_vartu();
  Serial.println("pradedam beta");
}

void loop() {
  //Laikas();
  mygtuku_nuskaitymas();
  dht_nuskaitymas();
  roboto_nuskaitymas();
  siuntimas_robotui();
  Serial.print("reali::::::::::::::::::::::  ");
  Serial.println(busena);
  
  if(busena==10) {
    sr.set(Krovimo, LOW);
    sr.set(Perimetras, LOW);
    sr.set(Namu_perimetras, LOW);
    motor(0);
    Vidaus_led(0);
  }
  else if(busena==1) {
    sr.set(Krovimo, HIGH);
    sr.set(Perimetras, LOW);
    sr.set(Namu_perimetras, LOW);
    Vidaus_led(0);
  }
  else if(busena==2) {
    sr.set(Perimetras, HIGH);
    sr.set(Namu_perimetras, LOW);
    sr.set(Krovimo, LOW);
    Vidaus_led(0);
  }
  else if(busena==3) {
    sr.set(Namu_perimetras, HIGH);
    sr.set(Perimetras, LOW);
    sr.set(Krovimo, LOW);
    Vidaus_led(1);
  }
  else if(busena==4) {
    sr.set(Perimetras, HIGH);
    sr.set(Namu_perimetras, HIGH);
    sr.set(Krovimo, LOW);
    Vidaus_led(1);
  }
  else if(busena==5) {
    sr.set(Perimetras, LOW);
    sr.set(Namu_perimetras, HIGH);
    sr.set(Krovimo, HIGH);
    Vidaus_led(1);
  }
  else if(busena==6) {
    mygtuku_nuskaitymas();
    if(atidarymo_mygtukas == LOW){ busena = 10; }
    else{ atidarymas_vartu(); }
    duru_state = 3;
  }
  else if(busena == 7) {
    mygtuku_nuskaitymas();
    if(uzdarymo_mygtukas == LOW){ busena = 1; }
    else{ uzdarymas_vartu(); }
    duru_state = 1;
  }
  delay(50);

}
void mygtuku_nuskaitymas() {
  atidarymo_mygtukas = digitalRead(atidarymo_pin);
  uzdarymo_mygtukas = digitalRead(uzdarymo_pin);
  centro_mygtukas =  analogRead(centro_pin);
  stogo_mygtukas = analogRead(stogo_pin);
  lietus = digitalRead(lietaus_pin);
  
  d[0] =  duru_state;
  if (centro_mygtukas >= 512) {
    d[1] = 0;
  }
  else {
    d[1] = 1;
  }
  if(lietus == HIGH) { d[2] = 2; }
  else{ d[2] = 1; }
  
  d[3] = 0;
}
void motor(int state) {
  if (state == 0) {
    sr.set(variklio_atidarymo, LOW);
    sr.set(variklio_uzdarymo, LOW);
  }
  else if (state == 1) {
    sr.set(variklio_atidarymo, HIGH);
    sr.set(variklio_uzdarymo, LOW);
  }
  else if (state == -1) {
    sr.set(variklio_atidarymo, LOW);
    sr.set(variklio_uzdarymo, HIGH);
  }
  else {
    sr.set(variklio_atidarymo, LOW);
    sr.set(variklio_uzdarymo, LOW);
  }
}

