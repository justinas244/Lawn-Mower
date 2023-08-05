void atidarymas_vartu() {
  duru_state = 2;
   Serial.println("Vartai atidaromi");
  while(true) {
     mygtuku_nuskaitymas();
     siuntimas_robotui();
    
    if(atidarymo_mygtukas == LOW) {
      delay(3000);
      duru_busena = 1;
      duru_state = 3;
      motor(0);
      delay(100);
      break;
    }
    else{
      motor(1);
      delay(50);
    }
  }
}
void uzdarymas_vartu() {
  duru_state = 2;
  Serial.println("Vartai uzdaromi");
  while (true) {
    mygtuku_nuskaitymas();
    siuntimas_robotui();
    if(uzdarymo_mygtukas == LOW){
      delay(1500);
      duru_busena = 0;
      duru_state = 1;
      motor(0);
      delay(2000);
      break;
    }
    else{
      motor(-1);
      delay(50);
    }
  }
}

