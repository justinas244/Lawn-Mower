void sensoriai(bool sauga) {
  gavimas_is_namelio();
  kampas();
  if(sauga == 1){
    avariniai_sensoriai();
   }
   
   desinesP = daznis(Perimetro_desines,10);
   kairesP = daznis(Perimetro_kaires,10);
   
  /* kairesN = daznis(Namu_kaires,10);
   desinesN = daznis(Namu_desines,10);*/
   
  atstumasD = ultragarso_atstumas (desines_T, desines_E, 2);
  atstumasC = ultragarso_atstumas (centro_T,  centro_E,  1);
  atstumasK = ultragarso_atstumas (kaires_T,  kaires_E,  0);
  
  if(hour>=16 && hour<=20){
    PK = HIGH;
    PD = HIGH;
    GK = HIGH;
    GD = HIGH;
  }
  else{
    PK = digitalRead(PK_pin);
    PD = digitalRead(PD_pin);
    GK = digitalRead(GK_pin);
    GD = digitalRead(GD_pin);
  }
  
  /*Serial.print(atstumasK);
  Serial.print("     ");
  Serial.print(atstumasC);
  Serial.print("     ");
  Serial.print(atstumasD);
  Serial.println("     ");*/
}
void sroves_sensorius(){
   int adc = analogRead(krovimo_sroves_pin);
  krovimo_srove = adc * faktorius;  
   if(krovimo_srove <= 0.28){
    krovimo_srove = 0.0;
   }
}

int ultragarso_atstumas(int trigPin, int echoPin, int tipas) {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH,timeout_ultrasonic(tipas));
  distance = (duration/2) / 29.1;
  
  if(distance>ultragarsiniu_matymo_atstumas[tipas] || distance<=0){distance = ultragarsiniu_matymo_atstumas[tipas];}
  return distance;
}
int timeout_ultrasonic(int puse){
  return ultragarsiniu_matymo_atstumas[puse]*29.1*2;
}
void avariniai_sensoriai(){
  stop_mygtukas = digitalRead(stop_mygtuko_pin);
  //aukstis = sensor.getDistance();
  gavimas_is_namelio();
//  mpu6050.update();
//  x_kampas  =  round(mpu6050.getAngleX());
  
   if(stop_mygtukas == HIGH){
     busena = 2;
     peilio_apsukos(1000);
     motor(0,0);
     pypsejimas(200,200,4);
     stopas = 1;
     siuntimas_nameliui(0,4);
     delay(3000);
    }
    //delay(5);
}


unsigned long daznis(int pin, unsigned long gateTime)
{ 
  unsigned long time, timeInitial;
  unsigned long count=0;
  boolean level, lastLevel;
  
  timeInitial = millis();
  time=timeInitial;
    
  while((time-timeInitial)<gateTime) 
  {    
    level = digitalRead(pin);
    if((level != lastLevel) ) // if transient
    { 
       lastLevel = level;
       if(level == HIGH) count++; //rising front
    }
   time=millis();
  }
  return count;
}
void sensoriu_reset(){
  atstumasC = 50;
  atstumasD = 50;
  atstumasK = 50;
  PK = HIGH;
  PD = HIGH;
  GK = HIGH;
  GD = HIGH;
  desinesP = 0;
  kairesP = 0;
}
int aptikti_sensoriai(){
     sensoriai(1);

    if(kairesP >= ribaKP && desinesP >= ribaDP) { return 2; }
    else if(kairesP >= ribaKP) {                  return 1; }
    else if(desinesP >= ribaDP){                  return 3; }

    if(atstumasC <= atstumo_ribaC){ return 2; }
    else if(atstumasC <= atstumo_ribaC && atstumasK <= atstumo_ribaK){ return 1; }
    else if(atstumasK <= atstumo_ribaK){ return 1; }
    else if(atstumasD <= atstumo_ribaD){ return 3; }
    else if(atstumasC <= atstumo_ribaC && atstumasD <= atstumo_ribaD){ return 3; }

     if(PD == LOW){ return 3;}
     else if(PK == LOW){ return 1;}
    
    return 0; 
}

void priekines_linijos_sensoriu_aptikimas(){
   if(atstumasC <= atstumo_ribaC){
      if(atstumasC <= 10){ motor(0,0);}
      else{ letejimas(greitis, 0, 3, 1); }
    greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    letejimas(greitis_atgal, 0, 5, 0);
    //pasisukimas(sukimosi_greitis, sukimosi_laikas_Centrui ,r,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    apsisukimas(ultragarsiniu_pasisukimo_kampas[1],r,sukimosi_greitis, sukimosi_greitejimo_laikas);
    //greitejimas(0, greitis, 5, 1,0);
    pid_nulinimas();
    //komposas();
    kampas();
    setpoint = laipsniai;
    r=!r;
    sensoriu_reset();
  }
  
  if(atstumasD <= atstumo_ribaD){
      if(atstumasD <= 10){ motor(0,0);}
      else{  letejimas(greitis, 0, 5, 1);}
    greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    letejimas(greitis_atgal, 0, 5, 0);
    //pasisukimas(sukimosi_greitis, sukimosi_laikas_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    apsisukimas(ultragarsiniu_pasisukimo_kampas[2],0,sukimosi_greitis, sukimosi_greitejimo_laikas);
   // greitejimas(0, greitis, 5, 1,0);
    pid_nulinimas();
    kampas();
    setpoint = laipsniai;
    sensoriu_reset();
     r=0;
  }
  
   if(atstumasK <= atstumo_ribaK){
      if(atstumasK <= 10){ motor(0,0); }
      else{ letejimas(greitis, 0, 5, 1); }
    greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    letejimas(greitis_atgal, 0, 5, 0);
    //pasisukimas(sukimosi_greitis+10, sukimosi_laikas_kaire ,1,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    apsisukimas(ultragarsiniu_pasisukimo_kampas[0],1,sukimosi_greitis, sukimosi_greitejimo_laikas);
    //greitejimas(0, greitis, 5, 1,0);
    pid_nulinimas();
    kampas();
    setpoint = laipsniai;
    sensoriu_reset();
    r=1;
  }
  
  if(PK == LOW && PD == HIGH){
    letejimas(greitis, 0, 5, 1);
    //greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    //letejimas(greitis_atgal, 0, 5, 0);
    pasisukimas(sukimosi_greitis+10, sukimosi_laikas_kaire ,1,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
   //apsisukimas(-optikos_kaires_kampas,1,sukimosi_greitis, sukimosi_greitejimo_laikas);
    greitejimas(0, greitis, 5, 1,0);
    pid_nulinimas();
     kampas();
    setpoint = laipsniai;
    sensoriu_reset();
  }
  else if(PK == HIGH && PD == LOW){
    letejimas(greitis, 0, 5, 1);
    //greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    //letejimas(greitis_atgal, 0, 5, 0);
     pasisukimas(sukimosi_greitis, sukimosi_laikas_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    //apsisukimas(optikos_desines_kampas,0,sukimosi_greitis, sukimosi_greitejimo_laikas);
    greitejimas(0, greitis, 5, 1,0);
    pid_nulinimas();
     kampas();
    setpoint = laipsniai;
    sensoriu_reset();
  }
}
///////////////////////// Meniu Dalis//////////////////////////////////////////////////////////////////////////////
void Sensorikos_nustatymai(){
      elementas = 9+(kursorius+pastumimas);
   while(true){
     mygtukai();
     
    if(Enter == HIGH){
      busena = 4;
      kursorius = 0;
      pastumimas = 0;
      delay(100);
      lcd.clear();
      break;
    }
    else if(Plius == HIGH){
      kursorius++;
      elementas++;
      if(kursorius>3){pastumimas++; kursorius=3;}
      if(pastumimas>2){pastumimas =0; kursorius =0; elementas = 9;}
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
       kursorius--;
      elementas--;
      if(kursorius<0){pastumimas--; kursorius=0;}
      if(pastumimas<0){pastumimas =2; kursorius =3; elementas = 14;}
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      busena = 3;
      kursorius = 1;
      pastumimas = 0;
      elementas = 1;
      lcd.clear();
      delay(10);
      break;
    }
    if(stop_mygtukas ==HIGH){
        lcd.clear();
        delay(10);
         for(int i=5; i>=1; i--){
            lcd.setCursor(10,2);
            lcd.print(i);
            delay(1000);
         }
         busena = 1;
         uzkurimas = 0;
         peilio_greitis = 1000;
         pypsejimas(100,100,3);
         setpoint = laipsniai;
         stopas = true;
         break;
    }

    
     lcd.setCursor(0,kursorius);
     lcd.print(">");
     
    for(byte i=0; i<=3; i++){
       lcd.setCursor(1,i);
       lcd.print(Sensorikos_meniu[i+pastumimas]);
     } 
  }
}

void optika(){
      kursorius = 0;
      pastumimas = 0;
      rodykle = 0;
      spaudimo_busena = 0;
       
    while(true){
       mygtukai();
       
        if(Enter == HIGH){
          spaudimo_busena++;
            if(kursorius == 0){
               if(spaudimo_busena==1){rodykle = 16; delay(50);}
               else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}
            }
            else if(kursorius == 1){
               if(spaudimo_busena == 1){rodykle = 16; delay(50);}
               else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}
            }
            else if(kursorius == 2){lcd.clear(); delay(50); optikos_sensoriu_testavimas(); spaudimo_busena=0;}
            else if(kursorius == 3){
              busena = 4;
              kursorius = 0;
              pastumimas = 0;
              elementas = 1;
              spaudimo_busena = 0;
              lcd.clear();
              delay(10);
              break;
            }
           lcd.clear(); 
        }
        else if(Plius == HIGH){
             if(spaudimo_busena==0){
                 kursorius++;
                 if(kursorius>3){ kursorius=0;}
                 delay(10);
                 lcd.clear();
             }
             else{
               if(kursorius == 0){
                 optikos_kaires_kampas+=5;
                 if(optikos_kaires_kampas>255){optikos_kaires_kampas=10;}
               }
               else if(kursorius == 1){
                 optikos_desines_kampas+=5;
                 if(optikos_desines_kampas>255){optikos_desines_kampas=10;}
               }
            }
        }
        else if(Minus == HIGH){
           if(spaudimo_busena==0){
                 kursorius--;
                 if(kursorius<0){ kursorius=3;}
                 delay(10);
                 lcd.clear();
           }
           else{
              if(kursorius == 0){
                 optikos_kaires_kampas-=5;
                 if(optikos_kaires_kampas<10){optikos_kaires_kampas=255;}
               }
              else if(kursorius == 1){
                 optikos_desines_kampas-=5;
                 if(optikos_desines_kampas<10){optikos_desines_kampas=255;}
               }
           }
       }
       else if(Save == HIGH){
           EEPROM.write(35,optikos_kaires_kampas);
           EEPROM.write(36,optikos_desines_kampas);
           busena = 4;
           kursorius = 0;
           pastumimas = 0;
           elementas = 1;
           saugojimo_animacija();
           break;
      }
      
        lcd.setCursor(rodykle,kursorius);
        lcd.print(">");
        for(byte i=0; i<=3; i++){
            lcd.setCursor(1,i);
            lcd.print(Optikos_langas[i+pastumimas]);
          } 
     
         lcd.setCursor(17,0);
         lcd.print(optikos_kaires_kampas);
         if(optikos_kaires_kampas<100){lcd.print(" ");}
         
         lcd.setCursor(17,1);
         lcd.print(optikos_desines_kampas);
         if(optikos_desines_kampas<100){lcd.print(" ");}
        
   }
}
void optikos_sensoriu_testavimas(){
    while(true){
       mygtukai();
        unsigned long currentMillis = millis();

        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 1;
           kursorius = 3;
           break;
        }
 
        if(currentMillis - previousMillis >= 100) {
            previousMillis = currentMillis;   
            PK = digitalRead(PK_pin);
            PD = digitalRead(PD_pin);
            GK = digitalRead(GK_pin);
            GD = digitalRead(GD_pin);
          }
          
       lcd.setCursor(0,0);
       lcd.print("PK: "); 
       lcd.print(!PK);

       lcd.setCursor(0,1);
       lcd.print("PD: "); 
       lcd.print(!PD);

       lcd.setCursor(0,2);
       lcd.print("GK: "); 
       lcd.print(!GK);

       lcd.setCursor(0,3);
       lcd.print("GD: "); 
       lcd.print(!GD);
    }
}


void ultragarsiniu_meniu(){
  kursorius = 0;
  pastumimas = 0;
  while(true){
      mygtukai();
        if(Enter == HIGH){
          if(kursorius<=2){lcd.clear(); ultragarso_sensoriaus_nustatymas(kursorius); delay(10);}
          else if(kursorius == 3){lcd.clear(); ultragarso_testavimas(); delay(10); }
        }
        else if(Plius == HIGH){
             kursorius++;
             if(kursorius>3){kursorius=0;}
             delay(1);
             lcd.clear();
        }
        else if(Minus == HIGH){
             kursorius--;
             if(kursorius<0){kursorius=3;}
             delay(1);
             lcd.clear();
       }
       else if(Save == HIGH){
             busena = 4;
             elementas = 1;
             kursorius = 2;
             pastumimas = 0;
             lcd.clear();
             delay(10);
             break;
       }
       
       lcd.setCursor(0,kursorius);
       lcd.print(">");
       
        for(byte i=0; i<=3; i++){
            lcd.setCursor(1,i);
            lcd.print(Ultragarso_langas[i]);
          } 
       }
}
void ultragarso_sensoriaus_nustatymas(int u){
     kursorius = 0;
     pastumimas = 0;
     rodykle = 0;
     spaudimo_busena = 0;
     
     while(true){
         mygtukai();
         
        if(Enter == HIGH){
           spaudimo_busena++;
           
            if(kursorius == 3){
               kursorius = u;
               pastumimas = 0;
               spaudimo_busena = 0;
               rodykle = 0;
               lcd.clear(); 
               delay(10);
               break;
            }
            else if(kursorius <=2){
                if(spaudimo_busena==1){rodykle = 16; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
             }
            lcd.clear();
         }
        else if(Plius == HIGH){
            if(spaudimo_busena==0){
                  kursorius++;
                  if(kursorius>3){kursorius=0;}
                  delay(1);
                  lcd.clear();
             }
             else{
                if(kursorius == 0){
                    ultragarsiniu_aptikimo_atstumas[u]++;
                    if(ultragarsiniu_aptikimo_atstumas[u]>=100){ultragarsiniu_aptikimo_atstumas[u] = 15;}
                    if(ultragarsiniu_matymo_atstumas[u]<ultragarsiniu_aptikimo_atstumas[u]){ultragarsiniu_aptikimo_atstumas[u] = ultragarsiniu_matymo_atstumas[u];}
                  }
                else if(kursorius == 1){
                  ultragarsiniu_matymo_atstumas[u]++;
                  if(ultragarsiniu_matymo_atstumas[u]>=120){ultragarsiniu_matymo_atstumas[u]=25;}
                }
                else if(kursorius == 2){
                  ultragarsiniu_pasisukimo_kampas[u]++;
                  if(ultragarsiniu_pasisukimo_kampas[u]>255){ultragarsiniu_pasisukimo_kampas[u] = 20;}
                }
             }
        }
        else if(Minus == HIGH){
            if(spaudimo_busena==0){
                kursorius--;
                if(kursorius<0){kursorius=3;}
                 delay(1);
                lcd.clear();
            }
           else{
                if(kursorius == 0){
                    ultragarsiniu_aptikimo_atstumas[u]--;
                    if(ultragarsiniu_aptikimo_atstumas[u]<15){ultragarsiniu_aptikimo_atstumas[u] = 100;}
                    if(ultragarsiniu_matymo_atstumas[u]<ultragarsiniu_aptikimo_atstumas[u]){ultragarsiniu_aptikimo_atstumas[u] = ultragarsiniu_matymo_atstumas[u];}
                  }
                else if(kursorius == 1){
                  ultragarsiniu_matymo_atstumas[u]--;
                  if(ultragarsiniu_matymo_atstumas[u]<25){ultragarsiniu_matymo_atstumas[u]=120;}
                }
                else if(kursorius == 2){
                  ultragarsiniu_pasisukimo_kampas[u]--;
                  if(ultragarsiniu_pasisukimo_kampas[u]<20){ultragarsiniu_pasisukimo_kampas[u] = 255;}
                }
             }
       }
        else if(Save == HIGH){
           EEPROM.write(37+u,ultragarsiniu_aptikimo_atstumas[u]);
           EEPROM.write(40+u,ultragarsiniu_matymo_atstumas[u]);
           EEPROM.write(43+u,ultragarsiniu_pasisukimo_kampas[u]);
           kursorius = u;
           pastumimas = 0;
           saugojimo_animacija();
           break;
         }
       
       lcd.setCursor(17,0);
       lcd.print(ultragarsiniu_aptikimo_atstumas[u]);
       if(ultragarsiniu_aptikimo_atstumas[u]<100){lcd.print(" ");}
       
       lcd.setCursor(17,1);
       lcd.print(ultragarsiniu_matymo_atstumas[u]);
       if(ultragarsiniu_matymo_atstumas[u]<100){lcd.print(" ");}
       
       lcd.setCursor(17,2);
       lcd.print(ultragarsiniu_pasisukimo_kampas[u]);
       if(ultragarsiniu_pasisukimo_kampas[u]<100){lcd.print(" ");}
       
       lcd.setCursor(rodykle,kursorius);
       lcd.print(">");
       
        for(byte i=0; i<=3; i++){
            lcd.setCursor(1,i);
            lcd.print(sensoriaus_langas[i]);
          } 
         
     }  
}

void ultragarso_testavimas(){
  while(true){
      mygtukai();

        if((Enter + Plius + Minus +Save)!=0){
           kursorius = 3;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }
        
       unsigned long currentMillis = millis();
       
       if(currentMillis - previousMillis >= 50) {
           previousMillis = currentMillis;   
           atstumasD = ultragarso_atstumas (desines_T, desines_E, 2);
           atstumasC = ultragarso_atstumas (centro_T,  centro_E,  1);
           atstumasK = ultragarso_atstumas (kaires_T,  kaires_E,  0);
       }

       lcd.setCursor(0,0);
       lcd.print(atstumasK);
       lcd.print(" ");

       lcd.setCursor(8,0);
       lcd.print(atstumasC);
       lcd.print(" ");
       
       lcd.setCursor(17,0);
       lcd.print(atstumasD);
       lcd.print(" ");
    
  }
}
void baterijos_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
  rodykle = 0;
  spaudimo_busena = 0;
   while(true){
     mygtukai();
       if(Enter == HIGH){
        spaudimo_busena++;
          if(kursorius == 3){
             busena = 4;
             elementas = 1;
             kursorius = 3;
             pastumimas = 0;
             lcd.clear();
             delay(10);
             break;
          }
           else if(kursorius == 0){
                if(spaudimo_busena==1){rodykle = 13; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
             }
           else if(kursorius == 1){
                if(spaudimo_busena==1){rodykle = 13; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
            }
           else if(kursorius == 2){
                if(spaudimo_busena==1){rodykle = 13; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
            }
          lcd.clear();
       }
       else if(Plius == HIGH){
           if(spaudimo_busena==0){
               kursorius++;
               if(kursorius>3){kursorius=0;}
               delay(1);
               lcd.clear();
           }
           else{
               if(kursorius == 0){
                   baterijos_ofsetas+=0.01;
                   if(baterijos_ofsetas > 0.20){baterijos_ofsetas = -0.20;}
               }
               else if(kursorius == 1){
                   iskrovimo_riba+=0.1;
                   if(iskrovimo_riba > 11.4){iskrovimo_riba = 8.0;}
               }
               else if(kursorius == 2){
                   budejimo_krovimas+=0.1;
                   if(budejimo_krovimas > 12.4){ budejimo_krovimas = 11.8;}
               }
           }
              
       }
       else if(Minus == HIGH){
         if(spaudimo_busena==0){
           kursorius--;
           if(kursorius<0){kursorius=3;}
           delay(1);
           lcd.clear();
         }
         else{
              if(kursorius == 0){
                baterijos_ofsetas-=0.01;
                if(baterijos_ofsetas <-0.20){baterijos_ofsetas =0.20;}
              }
              else if(kursorius == 1){
                   iskrovimo_riba-=0.1;
                   if(iskrovimo_riba < 8.0){iskrovimo_riba = 11.4;}
               }
             else if(kursorius == 2){
                   budejimo_krovimas-=0.1;
                   if(budejimo_krovimas < 11.8){budejimo_krovimas = 12.4;}
               }
           }
        }
       else if(Save == HIGH){
           int a = keitiklis(baterijos_ofsetas,-0.20,0.20,0,40);
           int b = keitiklis(iskrovimo_riba,8.0,11.4,80,114);
           int c = keitiklis(budejimo_krovimas,11.8,12.4,118,124);
           EEPROM.write(46,a);
           EEPROM.write(47,b);
           EEPROM.write(48,c);
           busena = 4;
           elementas = 1;
           kursorius = 3;
           pastumimas = 0;
           saugojimo_animacija();
           break;
       }

       lcd.setCursor(rodykle,kursorius);
       lcd.print(">");

        
       lcd.setCursor(14,0);
       lcd.print(baterijos_ofsetas);
       lcd.print("V");
       if(baterijos_ofsetas>=0.0){
        lcd.print(" ");
       }
       
       lcd.setCursor(14,1);
       lcd.print(iskrovimo_riba);
       lcd.print("V");
       if(iskrovimo_riba<10.0){
        lcd.print(" ");
       }
       
       lcd.setCursor(14,2);
       lcd.print(budejimo_krovimas);
       lcd.print("V");
       
        for(byte i=0; i<=3; i++){
            lcd.setCursor(1,i);
            lcd.print(baterijos_langas[i]);
          }   
   }
}
void perimetro_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
   while(true){
       mygtukai();
       if(Enter == HIGH){
          if(kursorius == 0){
             lcd.clear();
             delay(1);
             isorinis_perimetras();
             delay(10);
          }
          else if(kursorius == 1){
             lcd.clear();
             delay(1);
             Namu_perimetras();
             delay(10);
          }
          else if(kursorius == 2){
             lcd.clear();
             delay(1);
             perimetro_sensoriu_testas();
             delay(10);
          }
       }
       else if(Plius == HIGH){
           kursorius++;
           if(kursorius>2){kursorius=0;}
           delay(1);
           lcd.clear();
       }
       else if(Minus == HIGH){
          kursorius--;
          if(kursorius<0){kursorius=2;}
          delay(1);
          lcd.clear();
       }
       else if(Save == HIGH){
           busena = 4;
           elementas = 1;
           kursorius = 3;
           pastumimas = 1;
           delay(10);
           lcd.clear();
           break;
       }
       lcd.setCursor(0,kursorius);
       lcd.print(">");
       
       for(byte i=0; i<=2; i++){
            lcd.setCursor(1,i);
            lcd.print(perimetro_langas[i]);
        }   
   }
}
void isorinis_perimetras(){
     kursorius = 0;
     pastumimas = 0;
     rodykle = 0;
     spaudimo_busena = 0;
     
  while(true){
     mygtukai();
         if(Enter == HIGH){
           spaudimo_busena++;
            if(kursorius <= 1){
                if(spaudimo_busena==1){rodykle = 16; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
            }
            else if(kursorius == 2){
                kursorius = 0;
                delay(10);
                lcd.clear();
                break;
            }
            lcd.clear();
       }
       else if(Plius == HIGH){
        if(spaudimo_busena == 0){
           kursorius++;
           if(kursorius>2){kursorius=0;}
           delay(1);
           lcd.clear();
         }
         else{
            if(kursorius == 0){ribaKP+=10;if(ribaKP>990){ribaKP=50;}}
            else if(kursorius == 1){ribaDP+=10;if(ribaDP>990){ribaDP=50;}}
         }
       }
       else if(Minus == HIGH){
         if(spaudimo_busena == 0){
             kursorius--;
             if(kursorius<0){kursorius=2;}
             delay(1);
             lcd.clear();
         }
         else{
            if(kursorius == 0){ribaKP-=10;if(ribaKP<50){ribaKP=990;}}
            else if(kursorius == 1){ribaDP-=10;if(ribaDP<50){ribaDP=990;}}
         }
       }
       else if(Save == HIGH){
           EEPROM.write(49,ribaKP/10);
           EEPROM.write(50,ribaDP/10);
           kursorius = 0;
           saugojimo_animacija();
           break;
       }
       lcd.setCursor(2,0);
       lcd.print("Lauko Perimetras");
        
       lcd.setCursor(rodykle,kursorius+1);
       lcd.print(">");
       
       lcd.setCursor(17,1);
       lcd.print(ribaKP);
       if(ribaKP<100){lcd.print(" ");}
       
       lcd.setCursor(17,2);
       lcd.print(ribaDP);
       if(ribaDP<100){lcd.print(" ");}
       
       for(byte i=0; i<=2; i++){
            lcd.setCursor(1,i+1);
            lcd.print(perimetro_reiksmiu_nustatymai[i]);
        }     
  }
}

void Namu_perimetras(){
     kursorius = 0;
     pastumimas = 0;
     rodykle = 0;
     spaudimo_busena = 0;
     
  while(true){
     mygtukai();
         if(Enter == HIGH){
           spaudimo_busena++;
            if(kursorius <= 1){
                if(spaudimo_busena==1){rodykle = 16; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
            }
            else if(kursorius == 2){
                kursorius = 0;
                delay(10);
                lcd.clear();
                break;
            }
            lcd.clear();
       }
       else if(Plius == HIGH){
        if(spaudimo_busena == 0){
           kursorius++;
           if(kursorius>2){kursorius=0;}
           delay(1);
           lcd.clear();
         }
         else{
            if(kursorius == 0){sekimo_KP+=10;if(sekimo_KP>990){sekimo_KP=50;}}
            else if(kursorius == 1){sekimo_DP+=10;if(sekimo_DP>990){sekimo_DP=50;}}
         }
       }
       else if(Minus == HIGH){
         if(spaudimo_busena == 0){
             kursorius--;
             if(kursorius<0){kursorius=2;}
             delay(1);
             lcd.clear();
         }
         else{
            if(kursorius == 0){sekimo_KP-=10;if(sekimo_KP<50){sekimo_KP=990;}}
            else if(kursorius == 1){sekimo_DP-=10;if(sekimo_DP<50){sekimo_DP=990;}}
         }
       }
       else if(Save == HIGH){
           EEPROM.write(51,sekimo_KP/10);
           EEPROM.write(52,sekimo_DP/10);
           kursorius = 1;
           saugojimo_animacija();
           break;
       }
       lcd.setCursor(3,0);
       lcd.print("Namu Perimetras");
       lcd.setCursor(rodykle,kursorius+1);
       lcd.print(">");
       
       lcd.setCursor(17,1);
       lcd.print(sekimo_KP);
       if(sekimo_KP<100){lcd.print(" ");}
       
       lcd.setCursor(17,2);
       lcd.print(sekimo_DP);
       if(sekimo_DP<100){lcd.print(" ");}
       
       for(byte i=0; i<=2; i++){
            lcd.setCursor(1,i+1);
            lcd.print(perimetro_reiksmiu_nustatymai[i]);
        }     
  }
}
void perimetro_sensoriu_testas(){
   while(true){
        mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           kursorius = 2;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
     }
}

void temperaturiniu_nustatymai(){
      while(true){
        mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 1;
           kursorius = 3;
           pastumimas = 2;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
     }
}
  

