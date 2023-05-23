void STOPAS(){
   stop_mygtukas = digitalRead(stop_mygtuko_pin);
}
void meniu(){
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
      if(pastumimas>1){pastumimas =0; kursorius =0; elementas = 0;}
      delay(10);
      lcd.clear();
    }
    else if(Minus == HIGH){
       kursorius--;
      elementas--;
      if(kursorius<0){pastumimas--; kursorius=0;}
      if(pastumimas<0){pastumimas =1; kursorius =3; elementas = 4;}
      delay(10);
      lcd.clear();
    }
    else if(Save == HIGH){
      busena = 2;
      kursorius = 0;
      pastumimas = 0;
      elementas = 0;
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
       lcd.print(Meniu[i+pastumimas]);
     }
     
  }
}
void funkcijos(){
    if(elementas == 0){        Laiko_ir_Datos_nustatymai(); }
    else if(elementas == 1){   Sensorikos_nustatymai();     }
    else if(elementas == 2){   Varikliu_nustatymai();       }
    else if(elementas == 3){   Papildomas_meniu();          }
    else if(elementas == 5){   laiko_nustatymas();          }
    else if(elementas == 6){   datos_nustatymas();          }
    else if(elementas == 7){   Darbo_Laiko_nustatymas();    }
    else if(elementas == 8){   Darbo_laikas();              }
    else if(elementas == 9){   optika();                    }
    else if(elementas == 10){  giroskopo_meniu();           }
    else if(elementas == 11){  ultragarsiniu_meniu();       }
    else if(elementas == 12){  baterijos_nustatymai();      }
    else if(elementas == 13){  perimetro_nustatymai();      }
    else if(elementas == 14){  temperaturiniu_nustatymai(); }  
    else if(elementas == 15){  PID_nustatymai();            }
    else if(elementas == 16){  peilio_nustatymai();         }
    else if(elementas == 17){  greicio_nustatymai();        }
    else if(elementas == 18){  PID_testavimas();            }
    else if(elementas == 19){  valymo_ciklas();             }
    else if(elementas == 20){  PIN_kodo_nustatymai();       }
    else if(elementas == 21){  sviesu_nustatymai();         }
    else if(elementas == 22){  mygtuku_garsas();            }
    else if(elementas == 23){  reseto_nustatymai();         }
    
    
    
    
}

