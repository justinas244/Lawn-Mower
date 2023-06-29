void setHour()
{
  hour++; 
  if(hour > 23)
  {
    hour = 0; 
   minutes = 0;
  }
  
}
void setMinutes()
{
  minutes++;  
  if(minutes > 59)
  { minutes = 0;}
}


////////////////////////////////// LAIKO IR DATOS NUSTATYMAI ///////////////////////////////////////////////////////

void Laiko_ir_Datos_nustatymai(){
     laikas_nespaudimo = millis();
     praejes_nuo_paspaudimo = laikas_nespaudimo;
     elementas = 5 + kursorius;
    while(true){
    mygtukai();
    
     if(Enter == HIGH){
       busena = 4;
       kursorius = 0;
       pastumimas = 0;
       delay(10);
       lcd.clear();
      break;
    }
    else if(Plius == HIGH){
      elementas++;
      kursorius++;
      if(kursorius>2){kursorius =0;}
      if(elementas>7){elementas = 5;}
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
      kursorius--;
      elementas--;
      if(kursorius<0){kursorius =2;}
      if(elementas<5){elementas = 7;}
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      pastumimas = 0;
      kursorius = 0;
      elementas = 0;
      busena = 3;
      lcd.clear();
       laikas_nespaudimo = millis();
       praejes_nuo_paspaudimo = laikas_nespaudimo;
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
          pastumimas = 0;
          kursorius = 0;
          uzkurimas = 0;
         peilio_greitis = 1000;
         pypsejimas(100,100,3);
         setpoint = laipsniai;
         stopas = 0;
         break;
    }

    
     lcd.setCursor(0,kursorius);
     lcd.print(">");
    for(byte i=0; i<=2; i++){
       lcd.setCursor(1,i);
       lcd.print(Laiko_meniu[i]);
     }   
  }
}
void laiko_nustatymas(){
     laikas_nespaudimo = millis();
     praejes_nuo_paspaudimo = laikas_nespaudimo;
     
     while(true){ 
       mygtukai();
    
     if(Enter == HIGH){
        }
    else if(Plius == HIGH){
       setHour();
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
       setMinutes();
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      pastumimas = 0;
      kursorius = 0;
      elementas = 0;
      busena = 4;
      lcd.clear();
       laikas_nespaudimo = millis();
       praejes_nuo_paspaudimo = laikas_nespaudimo;
      delay(100);
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
          pastumimas = 0;
          kursorius = 0;
          uzkurimas = 0;
         peilio_greitis = 1000;
         pypsejimas(100,100,3);
         setpoint = laipsniai;
         stopas = 0;
         break;
    }
      lcd.setCursor(6,0);
      lcd.print("Laikas");
  }
}
void datos_nustatymas(){
     laikas_nespaudimo = millis();
     praejes_nuo_paspaudimo = laikas_nespaudimo;
     while(true){
     mygtukai();
       //if(auto_isejimas_is_meniu() == true){busena =2; break;}

       if(Enter == HIGH){
        }
        
     else if(Plius == HIGH){
      delay(10);
      lcd.clear();
     }
    else if(Minus == HIGH){
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      pastumimas = 0;
      kursorius = 1;
      elementas = 0;
      busena = 4;
      lcd.clear();
       laikas_nespaudimo = millis();
       praejes_nuo_paspaudimo = laikas_nespaudimo;
      delay(100);
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
          pastumimas = 0;
          kursorius = 0;
          uzkurimas = 0;
         peilio_greitis = 1000;
         pypsejimas(100,100,3);
         setpoint = laipsniai;
         stopas = 0;
         break;
    }
      lcd.setCursor(7,0);
      lcd.print("Data");
       
      }
}
String Dienos[7] = {"Pirmadienis", "Antradienis", "Treciadienis","Ketvirtadienis", "Penktadienis", "Sestadienis","Sekmadienis"};
byte darbo_diena=0;

void Darbo_Laiko_nustatymas(){
    laikas_nespaudimo = millis();
    praejes_nuo_paspaudimo = laikas_nespaudimo;
   while(true){
      mygtukai();
        //if(auto_isejimas_is_meniu() == true){busena =2; break;}
        
    if(Enter == HIGH){
      busena = 4;
      kursorius = 0;
      pastumimas = 0;
      elementas = 8;
      delay(100);
      lcd.clear();
      break;
      lcd.clear();
      break;
    }
    else if(Plius == HIGH){
      kursorius++;
      if(kursorius>3){pastumimas++; kursorius=3;}
      if(pastumimas>3){pastumimas =0; kursorius =0;}
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
       kursorius--;
      if(kursorius<0){pastumimas--; kursorius=0;}
      if(pastumimas<0){pastumimas =3; kursorius =3;}
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      busena = 4;
      kursorius = 0;
      pastumimas = 0;
      elementas = 0;
      lcd.clear();
       laikas_nespaudimo = millis();
       praejes_nuo_paspaudimo = laikas_nespaudimo;
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
         stopas = 0;
         break;
    }

    
     lcd.setCursor(0,kursorius);
     lcd.print(">");
     
     darbo_diena = kursorius + pastumimas;
     
    for(byte i=0; i<=3; i++){
       lcd.setCursor(1,i);
       lcd.print(Dienos[i+pastumimas]);
        if(dirbimo[i+pastumimas]== 0){
            lcd.setCursor(17,i);
            lcd.print("OFF");
        }
        else{
            lcd.setCursor(17,i);
            lcd.print("ON");
        }
     }
   }
}

byte dienos_centravimas[7]={4,4,4,3,4,5,5};
byte rodykle=0;
byte spaudimas =0;
byte spaudimo_busena =0;
byte paskutinis_spaudimas=0;

void Darbo_laikas(){
    laikas_nespaudimo = millis();
    praejes_nuo_paspaudimo = laikas_nespaudimo;
    kursorius = 1;
    rodykle = 0;
    spaudimo_busena = 0;
    while(true){
       mygtukai();
       //if(auto_isejimas_is_meniu() == true){busena =2; break;}

         if(Enter == HIGH){
             spaudimo_busena++;
             if(kursorius==0){
                    busena = 4;
                    if(darbo_diena>=3){kursorius =3; pastumimas=darbo_diena-3;}
                    else{kursorius = darbo_diena; pastumimas=0;}
                    elementas = 7;
                    lcd.clear();
                    delay(10);
                    break;
               }
             else if(kursorius==1 ){
                    if(spaudimo_busena==1){rodykle=16+dirbimo[darbo_diena]; kursorius =1; delay(50);}
                    else if(spaudimo_busena==0){rodykle=0; delay(50);}
                    else if(spaudimo_busena>1) {rodykle=0; spaudimo_busena=0; delay(50);}
               }
              else if(kursorius==2 || kursorius==3){
                    if(spaudimo_busena==1){rodykle=14; delay(50);}
                    else if(spaudimo_busena==0){rodykle=0; delay(50);}
                    else if(spaudimo_busena>1) {rodykle=0; spaudimo_busena=0; delay(50);}
              }
              lcd.clear();
            }
         else if(Plius == HIGH){
             if(spaudimo_busena==0){
                kursorius++;
                if(kursorius>3){kursorius=0;}
                delay(10);
                lcd.clear();
             }
             else{
                 if(kursorius==1){dirbimo[darbo_diena]=1; rodykle=17; delay(10); lcd.clear();}
                 else if(kursorius==2){on_hour[darbo_diena]++; if(on_hour[darbo_diena]>24){on_hour[darbo_diena]=0;}delay(10);}
                 else if(kursorius==3){off_hour[darbo_diena]++; if(off_hour[darbo_diena]>24){off_hour[darbo_diena]=0;}delay(10);}
             }
             
              delay(10);
              //lcd.clear();
            }
         else if(Minus == HIGH){
             if(spaudimo_busena==0){
                 kursorius--;
                 if(kursorius<0){kursorius=3;}
                   delay(10);
                  lcd.clear();
              }
             else{
                 if(kursorius==1){dirbimo[darbo_diena]=0; rodykle=16; delay(10); lcd.clear();}
                 else if(kursorius==2){on_min[darbo_diena]++; if(on_min[darbo_diena]>59){on_min[darbo_diena]=0;}delay(10);}
                 else if(kursorius==3){off_min[darbo_diena]++; if(off_min[darbo_diena]>59){off_min[darbo_diena]=0;}delay(10);}
             }
          }
         else if(Save == HIGH){
              busena = 4;
              elementas = 7;
               if(darbo_diena>=3){kursorius =3; pastumimas=darbo_diena-3;}
               else{kursorius = darbo_diena; pastumimas=0;}
              darbo_dienos_irasymas();
              lcd.clear();
              delay(10);
              break;
          }
        
        lcd.setCursor(dienos_centravimas[darbo_diena],0);
        lcd.print(Dienos[darbo_diena]);
         
        lcd.setCursor(rodykle,kursorius);
        lcd.print(">");
        
         if(dirbimo[darbo_diena]==1){lcd.setCursor(18,1); lcd.print("ON");}
         else{lcd.setCursor(17,1); lcd.print("OFF");}
          
        lcd.setCursor(1,1);
        lcd.print("Naudoti");
        lcd.setCursor(1,2);
        lcd.print("Pradzia"); 
        lcd.setCursor(1,3);
        lcd.print("Pabaiga"); 
    
         lcd.setCursor(15,2);
         if(on_hour[darbo_diena] <10){lcd.print("0"); lcd.print(on_hour[darbo_diena]);}
         else{ lcd.print(on_hour[darbo_diena]);}
         lcd.print(":");
         if(on_min[darbo_diena] <10){lcd.print("0"); lcd.print(on_min[darbo_diena]);}
         else{lcd.print(on_min[darbo_diena]);}

         lcd.setCursor(15,3);
         if(off_hour[darbo_diena] <10){lcd.print("0"); lcd.print(off_hour[darbo_diena]);}
         else{ lcd.print(off_hour[darbo_diena]);}
         lcd.print(":");
         if(off_min[darbo_diena] <10){lcd.print("0"); lcd.print(off_min[darbo_diena]);}
         else{lcd.print(off_min[darbo_diena]);}

         
    }
}

void darbo_dienos_irasymas(){
   EEPROM.write(darbo_diena, dirbimo[darbo_diena]);
   EEPROM.write(7+darbo_diena, on_hour[darbo_diena]);
   EEPROM.write(14+darbo_diena, on_min[darbo_diena]);
   EEPROM.write(21+darbo_diena, off_hour[darbo_diena]);
   EEPROM.write(28+darbo_diena, off_min[darbo_diena]);
   delay(100);
   saugojimo_animacija();
}




