#include <Servo.h>
Servo peilis;

#include <Wire.h>
#include <HMC5883L.h>
#include <MPU6050.h>

HMC5883L compass;
MPU6050 mpu;

float heading1;
float heading2;

int laipsniai = 180;
int setpoint = 180;

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
#define GD_pin 24
#define GK_pin 22

////////// Maitinimas ///////////////////
#define peilio_maitinimas 43
#define varikliu_maitinimas 45
#define buzeris 11
//////// Varikliai ///////////////////////
int L_motor = 9;
int l_motor = 7;
int R_motor = 10;
int r_motor = 8;

int peilio_pin = 6;

int atstumasK = 0;
int atstumasC = 0;
int atstumasD = 0;

int atstumo_ribaC = 20;
int atstumo_ribaD = 25;
int atstumo_ribaK = 25;

int greitis = 120;
int greitisA = 160;
int peilio_greitis = 1500;

int data[10];
int u=0;
float akumas = 0.0;
float iskrovimo_riba = 9.0;
int gauta = 0;
int uzkurimas = 0;
int busena = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long sensoriu_nuskaitymo_intervalas = 50; 

float Kp = 2;//5
float Ki = 1; //2.5
float Kd = 1.25;

float error = 0, P = 0, I = 0, D = 0, V = 0;
float previous_error = 0, previous_I = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
    mpu.setI2CMasterModeEnabled(false);
    mpu.setI2CBypassEnabled(true) ;
    mpu.setSleepEnabled(false);
    
    while (!compass.begin()){delay(500);}
   compass.setRange(HMC5883L_RANGE_0_88GA);
   compass.setMeasurementMode(HMC5883L_CONTINOUS);
   compass.setDataRate(HMC5883L_DATARATE_30HZ);
   compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(0, 0); 
  
  pinMode(desines_T,OUTPUT);
  pinMode(centro_T,OUTPUT);
  pinMode(kaires_T,OUTPUT);
  pinMode(peilio_maitinimas,OUTPUT);
  pinMode(varikliu_maitinimas,OUTPUT);
  pinMode(peilio_pin,OUTPUT);
  pinMode(buzeris,OUTPUT);
  
  pinMode(desines_E,INPUT);
  pinMode(centro_E,INPUT);
  pinMode(kaires_E,INPUT);
  pinMode(PK_pin, INPUT);
  pinMode(PD_pin, INPUT);
  pinMode(GK_pin, INPUT);
  pinMode(GD_pin, INPUT);
  
  TCCR1A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR1B = TCCR1B & 0b11111111111 | 0x02;
  
  digitalWrite(varikliu_maitinimas,HIGH);
  digitalWrite(peilio_maitinimas,LOW);
  peilis.attach(peilio_pin);
  motor(0,0);
  
  while(true){
    gavimas_is_nano();
    if(akumas>=iskrovimo_riba){
      busena = 1;
      uzkurimas = 1;
      pypsejimas(200,500,2);
      break;
    } 
  }
  
}
void loop(){
  
   if(busena == 1 ){
      if(uzkurimas == 1){
        uzkurti();
      }
      else{
        vaziavimas();
      }
    }
    else if(busena == 0){
      //Stopas
      Stop();
      pypsejimas(200,200,3);
    }
    
    
  if(akumas<=iskrovimo_riba){
   busena = 0;
  }
  
}

