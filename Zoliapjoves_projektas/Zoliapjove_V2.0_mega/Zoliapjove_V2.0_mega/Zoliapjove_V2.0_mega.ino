#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);

#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DS1307_ADDRESS 0x68

byte batlevel[8] = {
  B01110,
  B11011,
  B10001,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte laikrodis[] = {
  B00000,
  B01110,
  B10101,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000
};

byte lasas[] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};

int namu_mygtukas;

int laipsniai;
int x_kampas;
int y_kampas;
int setpoint;
int pasisukimo_kampas;

#include <SharpIR.h>

int pakelimo_pin = A0;
int pakelimo_riba = 6;
int aukstis = 0;

bool auto_start = false;

int stop_mygtuko_pin = 19;
bool stop_mygtukas = 0;
bool stopas = false;

SharpIR sensor(GP2YA41SK0F, pakelimo_pin);
float zoles_aukstis = 0;

#include <Servo.h>
Servo peilis;

////////////////// Perimetro sensoriai /////////////
#define Perimetro_kaires  4
#define Perimetro_desines 5

#define Namu_kaires  32
#define Namu_desines 34

//////// Ultragarso sensoriai/////////////
#define desines_T 33
#define desines_E 31

#define centro_T 37
#define centro_E 35

#define kaires_T 41
#define kaires_E 39

//////// Optiniai ///////////////////////
#define PD_pin 28
#define PK_pin 26
#define GD_pin 22
#define GK_pin 24
int PD, PK, GD, GK;

////////// Maitinimas ///////////////////
#define filtro_maitinimas 43
#define mygtuku_maitinimas 45
#define buzeris 11

//////// Varikliai ///////////////////////
int L_motor = 9;  //10
int l_motor = 7;   //8
int R_motor = 10;   //9
int r_motor = 8;   //7

/////////// MYGTUKAI///////////////////
#define Enter_pin 23
#define Plius_pin 25
#define Minus_pin 27
#define Save_pin  29
bool Enter, Plius, Minus, Save;
//////////////Sroves sensoriai /////////////////
#define krovimo_sroves_pin  A4
float faktorius = 0.02134;
//////////PASISUKIMO KAPMPAI///////////////
int optikos_kaires_kampas = 25;
int optikos_desines_kampas = 25;
int ultragarsiniu_pasisukimo_kampas[3] = {130, 100, 130};

/////////////////Ultragarsiniu Matymo atstumai//////////////////////////
int ultragarsiniu_matymo_atstumas[3] = {40, 40, 40};
int ultragarsiniu_aptikimo_atstumas[3] = {25, 25, 25};

/////////////////////MENIU PUSLAPIAI//////////////////////////////////////////////////
String Meniu[5] = {"Laikas/Data", "Sensoriai", "Varikliai", "Papildomi", "Gamykliniai"};
String Sensorikos_meniu[6] = {"Optiniai", "Giroskopas", "Ultragarsiniai", "Baterija", "Perimetras", "Temperatura"};
String Varikliu_meniu[4] = {"PID Nustatymai", "Peilio Nustatymai", "Greicio Nustatymai", "Testuoti PID"};
String Laiko_meniu[3] = {"Laiko Nustatymai", "Datos Nustatymai", "Darbo Laikas"};
String Papildomas_Meniu[6] = {"Roboto Valymas", "PIN Keitimas", "Sviesos", "Garsas", "Restartuoti"};

String Optikos_langas[4] = {"K.Pasisukimas:", "D.Pasisukimas:", "Testuoti Sensorius", "Atgal"};
String Ultragarso_langas[4] = {"Kaires sensorius", "Centro sensorius", "Desines sensorius", "Sensoriu testavimas"};
String sensoriaus_langas[4] = {"Aptikimo ats.:", "Matymo ats.:", "Pasi. kampas:", "Atgal"};
String baterijos_langas[4] = {"Ofsetas:", "Iskrovimas:", "Budejimo:", "Atgal"};
String perimetro_langas[3] = {"Isorinis perimetras", "Namu perimetras", "Testavimas"};
String perimetro_reiksmiu_nustatymai[3] = {"Kaire:", "Desine:", "Atgal"};
String PID_langas[4] = {"P:", "I:", "D:", "Atgal"};
String Peilio_langas[4] = {"Naudoti:", "Max Apsukos:", "Min apsukos:", "Atgal"};
////////////////////////////////////////////////////////////////////////////////////////
int ofsetas_x;
int ofsetas_y;
float baterijos_ofsetas = 0.15;


int kursorius = 0;
int pastumimas = 0;
byte rodyti = 0;
bool isvalymas = 0;
int elementas = 0;


int peilio_pin = 6;
int Krovimo_pin = 47;

unsigned long kairesP;
unsigned long desinesP;
unsigned long kairesN;
unsigned long desinesN;

unsigned long ribaKP = 110;
unsigned long ribaDP = 130;

unsigned long namu_aptikimo_riba = 130;

unsigned long sekimo_KP = 110;
unsigned long sekimo_DP = 110;

int atstumasK = 0;
int atstumasC = 0;
int atstumasD = 0;

int atstumo_ribaC = 15;
int atstumo_ribaD = 20;
int atstumo_ribaK = 20;

int greitis = 140;
int peilio_greitis;

bool peilis_naudojamas = 1;
int max_peilio_greitis = 1600;
int min_peilio_greitis = 1400;

int data[10];

int state = 0;
int lietus = 0;
int namo_mygtukas = 0;
int valymas = 0;

int u = 0;
float akumas = 0.0;
float budejimo_krovimas = 12.00;

float krovimo_srove = 0;
float multiplier = 0.066;

float iskrovimo_riba = 9.2;;
int iskrautas = 0;
int gauta = 0;
int uzkurimas = 0;
int busena = 2;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long sensoriu_nuskaitymo_intervalas = 10;
unsigned long veikimo_laikas = 0;

unsigned long laikas_nespaudimo = 0;
unsigned long praejes_nuo_paspaudimo = 0;
unsigned long nespaudimo_intervalas = 30000;

unsigned long  baterijos_check;

float Kp = 2;//1.5
float Ki = 1; //2.5
float Kd = 1;

float error = 0, P = 0, I = 0, D = 0, V = 0;
float previous_error = 0, previous_I = 0;

int r = 0;
int greitis_atgal = 220;
int sukimosi_greitis = 180;
int sekimo_greitis = 140;

int greitejimo_laikas_atgal = 4;
int atgal_vaziavimo_laikas = 60;
int atgal_vaziavimo_laikas_Perimetro = 100;

int sukimosi_greitejimo_laikas = 0;
int sukimosi_laikas_Centrui = 340;
int sukimosi_laikas_desine = 280;
int sukimosi_laikas_kaire = 380;

int sukimosi_laikas_Perimetro_kaire = 380;
int sukimosi_laikas_Perimetro_desine = 300;

bool aptiktas_laidas = 0;
bool su_garsu = 1;

long intervalas_nuskaitymui = 1000;
long praejo = 0;
bool lietaus_efektas = 0;

int minutes; //00-59;
int hour;//1-12 - 00-23;
int weekDay;//1-7
int monthDay;
int month;//01-12
int year;//0-99;

byte on_hour[7] = {8, 10, 9, 11, 15, 10, 8};
byte on_min[7] = {0, 10, 9, 11, 20, 10, 8};
byte off_hour[7] = {20, 20, 20, 22, 21, 22, 19};
byte off_min[7] = {0, 10, 9, 11, 20, 10, 8};
byte dirbimo[7] = {1, 0, 0, 1, 0, 0, 0};

int pasileidimo_laikas;
int pabaigos_laikas;
int dabartinis_laikas;

byte pasileidimas_anksciau = 2;

bool namu_pozicija = false;
bool baigta_darbo_diena = false;
bool rankinis_paleidimas = false;
bool duris_atidarytos = false;

bool rain_status = false;
bool isRaining = false;
unsigned long rainStartTime = 0;
int lietaus_laukimo_v = 6;
int lietaus_laukimo_m = 0;
unsigned long rainDelay =0; //6 valandu laikotarpis
bool sausa = true;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0 , batlevel);
  lcd.createChar(1 , laikrodis);
  lcd.createChar(2,  lasas);

  Wire.begin();
  Wire.setWireTimeout(3000, true);
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial3.begin(9600);
  delay(10);


  pinMode(desines_T, OUTPUT);
  pinMode(centro_T, OUTPUT);
  pinMode(kaires_T, OUTPUT);
  pinMode(filtro_maitinimas, OUTPUT);
  pinMode(mygtuku_maitinimas, OUTPUT);
  pinMode(Krovimo_pin, OUTPUT);
  pinMode(buzeris, OUTPUT);
  pinMode(R_motor, OUTPUT);
  pinMode(r_motor, OUTPUT);
  pinMode(L_motor, OUTPUT);
  pinMode(l_motor, OUTPUT);

  pinMode(desines_E, INPUT);
  pinMode(centro_E, INPUT);
  pinMode(kaires_E, INPUT);
  pinMode(PK_pin, INPUT_PULLUP);
  pinMode(PD_pin, INPUT_PULLUP);
  pinMode(GK_pin, INPUT_PULLUP);
  pinMode(GD_pin, INPUT_PULLUP);
  pinMode(pakelimo_pin, INPUT);
  pinMode(stop_mygtuko_pin, INPUT);
  pinMode(Perimetro_kaires, INPUT);
  pinMode(Perimetro_desines, INPUT);
  pinMode(Namu_kaires, INPUT);
  pinMode(Namu_desines, INPUT);

  digitalWrite(mygtuku_maitinimas, LOW);
  digitalWrite(filtro_maitinimas, HIGH);
  digitalWrite(Krovimo_pin, LOW);
  motor(0, 0);

  lcd.setCursor(4, 0);
  lcd.print("TARATAIKA ");
  lcd.setCursor(4, 1);
  lcd.print("V2.0 Beta");
  Peilio_aktyvavimas();
  eepromo_nuskaitymas();
  
  rainDelay = lietaus_laukimo_v * 3600000 + lietaus_laukimo_m *60000;
   
  //komposo_nustatymai();
  giroskopo_ofsetai();

  lcd.clear();
  // while(true){
  //  perimetro_sensoriu_skaitymas(0);
  // }

  while (true) {
    gavimas_is_nano();
    if (akumas >= iskrovimo_riba) {
      peilis.writeMicroseconds(1000);
      busena = 2;
      uzkurimas = 0;
      //pypsejimas(200, 500, 2);
      kampas();
      setpoint = laipsniai;
      sensoriu_duomenis(1);
      break;
    }
  }
  //apsisukimas(-120,1,sukimosi_greitis, sukimosi_greitejimo_laikas);
  laikas_nespaudimo = millis();
}

void loop() {
  if (busena == 1 ) {
    if (uzkurimas == 1 && peilis_naudojamas == 1) {
      uzkurti();
    }
    else {
      vaziavimas();
    }
  }
  else if (busena == 0) {
    Stop();
    motor(0, 0);
    siuntimas_nameliui(0, 4);
    if (su_garsu == 1) {
      pypsejimas(200, 200, 3);
    }
    iskrautas = 0;
    delay(5000);
  }
  else if (busena == 2) {
    gavimas_is_nano();
    gavimas_is_namelio();
    digitalWrite(mygtuku_maitinimas, LOW);
    digitalWrite(filtro_maitinimas, LOW);
    peilio_apsukos(1000);
    motor(0, 0);
    stop_mygtukas = digitalRead(stop_mygtuko_pin);
    //aukstis = sensor.getDistance();
    //sensoriu_duomenis();
    mygtukai();
    if (stop_mygtukas == HIGH) {
      delay(1000);
       if(dirbimo[weekDay] == 1){
          pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
          pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
          dabartinis_laikas = laiko_konvertavimas(hour,minutes);

          if(dabartinis_laikas>=pasileidimo_laikas-pasileidimas_anksciau && dabartinis_laikas<pabaigos_laikas){
                 rankinis_paleidimas = false;
                 baigta_darbo_diena = false;
                 if(namu_pozicija == false){ nustatymas_kur_esu(); }
                 if (namu_pozicija == true) {
                   if(duris_atidarytos == false){
                      vartu_atidarymas();
                    }
                   busena = 8;
                   
                 }
                 else {
                   paleidimas();
                  
                 }
           }
           else{
             kampas();
             setpoint = laipsniai;
             busena = 5;
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Rankinis Paleidimas");
                delay(3000);
             
           }
        }
        else{
          rankinis_paleidimas = true;
           baigta_darbo_diena = false;
           nustatymas_kur_esu();
            if (namu_pozicija == true) {
              if (duris_atidarytos == false) {
                vartu_atidarymas();
              }
              busena = 8;
            }
            else {
              paleidimas();
            }
         delay(100);
       }
    }
    sensoriu_duomenis(0);
    /*else if (stop_mygtukas == HIGH && aukstis >= pakelimo_riba) {
      pypsejimas(500, 500, 2);
      digitalWrite(mygtuku_maitinimas, LOW);
      delay(1000);
      }*/
    if ((Plius + Minus) != 0) {
      pastumimas = 0;
      kursorius = 0;
      elementas = 0;
      busena = 3;
      delay(100);
      lcd.clear();
    }
    if ((Enter + Save) != 0) {
      busena = 9;
      delay(100);
      lcd.clear();
    }
    delay(100);
  }
  else if (busena == 3) {
    digitalWrite(mygtuku_maitinimas, HIGH);
    meniu();
  }

  else if (busena == 4)  {
    funkcijos();
  }
  else if (busena == 5)  {
    Laido_sekimas(1);                  //Normalus laido sekimas
  }
  else if (busena == 6)  {
    krovimo_busena();
  }
  else if (busena == 7)  {
    laido_radimas();
  }
  else if (busena == 8)  {
    isvaziavimas_is_namelio(10000, 0);
  }
  else if (busena == 9)  {
    laukimo_busena();
  }
  else if (busena == 10) {
    Laido_sekimas(0);                  //Laido sekimas krovimo pataisymui
  }
  else if (busena == 11) {
    Ivaziavimo_patikra();              //Laido sekimas krovimo pataisymui
  }


}
