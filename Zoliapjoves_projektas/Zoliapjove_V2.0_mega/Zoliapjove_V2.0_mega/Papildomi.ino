void Papildomas_meniu(){
  elementas = 19 + (kursorius+pastumimas);      
   while(true){
    mygtukai();
    elementas = 19 + (kursorius+pastumimas);  
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
      if(kursorius>3){pastumimas++; kursorius=3;}
      if(pastumimas>1){pastumimas =0; kursorius =0;}
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
       kursorius--;
      if(kursorius<0){pastumimas--; kursorius=0;}
      if(pastumimas<0){pastumimas =1; kursorius =3;}
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      busena = 3;
      kursorius = 3;
      pastumimas = 0;
      elementas = 3;
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
         stopas = 0;
         break;
    }

    
     lcd.setCursor(0,kursorius);
     lcd.print(">");
     
     
    for(byte i=0; i<=3; i++){
       lcd.setCursor(1,i);
       lcd.print(Papildomas_Meniu[i+pastumimas]);
     }
     
  }
}

void valymo_ciklas(){
  kursorius = 0;
  pastumimas = 0;
    while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 3;
           kursorius = 0;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}

void PIN_kodo_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
     while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 3;
           kursorius = 1;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}
void sviesu_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
    while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 3;
           kursorius = 2;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}
void mygtuku_garsas(){
  kursorius = 0;
  pastumimas = 0;
    while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 3;
           kursorius = 3;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}
void reseto_nustatymai(){
  kursorius = 0;
  pastumimas = 0;
   while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 3;
           kursorius = 3;
           pastumimas = 1;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}
int laiko_konvertavimas(int val,int mins){
  return val*60+mins;
}

int ms_min(unsigned long sekundes){
  return sekundes/60000 ;
}

