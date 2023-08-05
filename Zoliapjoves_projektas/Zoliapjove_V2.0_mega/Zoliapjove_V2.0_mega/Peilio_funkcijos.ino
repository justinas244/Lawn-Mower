void uzkurti(){
  //digitalWrite(varikliu_maitinimas, HIGH);
  peilis.writeMicroseconds(1000);
  delay(3000);
  peilis.writeMicroseconds(peilio_greitis);
  delay(7000);
  uzkurimas = 0;
}
void Stop(){
  digitalWrite(filtro_maitinimas, LOW);
  peilis.writeMicroseconds(1000);
  motor(0,0);
  uzkurimas = 1;
  busena = 2;
  siuntimas_nameliui(0,4);
}
void Peilio_aktyvavimas(){
  peilis.attach(peilio_pin);
  peilis.writeMicroseconds(1000);
  delay(5000);
}
void peilio_apsukos(int apsukos){
  if(peilis_naudojamas == 1){ peilis.writeMicroseconds(apsukos);}
  else{peilis.writeMicroseconds(1000);}
}

void peilio_greicio_nustatymas(){
   lcd.clear();
   zoles_nustatymas();
   lcd.setCursor(0,0);
   lcd.print("Zole: ");
   lcd.print(zoles_aukstis);
    peilio_greitis = keitiklis(zoles_aukstis,2.5,5,min_peilio_greitis,max_peilio_greitis);
    peilio_greitis = 1300;
  lcd.setCursor(0,1);
  lcd.print("Peilis: ");
  lcd.print(peilio_greitis);
  delay(5000);
  lcd.clear();

}

void peilio_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
  rodykle = 0;
  spaudimo_busena = 0;
  
   while(true){
     mygtukai();
     
       if(Enter == HIGH){
           spaudimo_busena++;
            if(kursorius <= 2){
                if(spaudimo_busena==1){rodykle = 16; delay(50);}
                else if(spaudimo_busena>1){rodykle= 0; spaudimo_busena = 0; delay(50);}  
            }
            else if(kursorius == 3){
                 busena = 4;
                 elementas = 2;
                 kursorius = 1;
                 pastumimas = 0;
                 lcd.clear();
                 delay(10);
                 break;
            }
            lcd.clear();
       }
       else if(Plius == HIGH){
        if(spaudimo_busena == 0){
           kursorius++;
           if(kursorius>3){kursorius=0;}
           delay(1);
           lcd.clear();
         }
         else{
            if(kursorius == 0){peilis_naudojamas = !peilis_naudojamas; delay(30);}
            else if(kursorius == 1){max_peilio_greitis+=10; if(max_peilio_greitis>2000){max_peilio_greitis = 1250;}}
            else if(kursorius == 2){min_peilio_greitis+=10; if(min_peilio_greitis>1800){min_peilio_greitis = 1150;}}
         }
       }
       else if(Minus == HIGH){
         if(spaudimo_busena == 0){
             kursorius--;
             if(kursorius<0){kursorius=3;}
             delay(1);
             lcd.clear();
         }
         else{
            if(kursorius == 0){peilis_naudojamas = !peilis_naudojamas; delay(30);}
            else if(kursorius == 1){max_peilio_greitis-=10; if(max_peilio_greitis<1250){max_peilio_greitis = 2000;}}
            else if(kursorius == 2){min_peilio_greitis-=10; if(min_peilio_greitis<1150){min_peilio_greitis = 1800;}}
         }
       }
       else if(Save == HIGH){
             EEPROM.write(56,peilis_naudojamas);
             EEPROM.write(57,map(max_peilio_greitis,1000,2000,0,100));
             EEPROM.write(58,map(min_peilio_greitis,1000,2000,0,100));
            busena = 4;
            elementas = 2;
            kursorius = 1;
            pastumimas = 0;
            saugojimo_animacija();
            break;
       }

       lcd.setCursor(rodykle,kursorius);
       lcd.print(">");

       lcd.setCursor(17,0);
       if(peilis_naudojamas == 1){lcd.print("ON ");}
       else{ lcd.print("OFF");}
       
       lcd.setCursor(17,1);
       lcd.print(map(max_peilio_greitis,1000,2000,0,100));
       if(map(max_peilio_greitis,1000,2000,0,100)<100){ lcd.print(" ");}

       lcd.setCursor(17,2);
       lcd.print(map(min_peilio_greitis,1000,2000,0,100));
       if(map(min_peilio_greitis,1000,2000,0,100)<100){ lcd.print(" ");}
       
       for(byte i=0; i<=3; i++){
            lcd.setCursor(1,i);
            lcd.print(Peilio_langas[i]);
        }   
   }
}

