void Varikliu_nustatymai() {
  elementas = 15 + kursorius;
  while (true) {
    mygtukai();
    elementas = 15 + kursorius;
    if (Enter == HIGH) {
      busena = 4;
      kursorius = 0;
      pastumimas = 0;
      delay(100);
      lcd.clear();
      break;
    }
    else if (Plius == HIGH) {
      kursorius++;
      if (kursorius > 3) {
        kursorius = 0;
      }

      delay(10);
      lcd.clear();
    }
    else if (Minus == HIGH) {
      kursorius--;
      if (kursorius < 0) {
        kursorius = 3;
      }

      delay(10);
      lcd.clear();
    }
    else if (Save == HIGH) {
      pastumimas = 0;
      kursorius = 2;
      elementas = 2;
      busena = 3;
      lcd.clear();
      delay(10);
      break;
    }
    if (stop_mygtukas == HIGH) {
      lcd.clear();
      delay(10);
      for (int i = 5; i >= 1; i--) {
        lcd.setCursor(10, 2);
        lcd.print(i);
        delay(1000);
      }
      busena = 1;
      pastumimas = 0;
      kursorius = 0;
      uzkurimas = 0;
      peilio_greitis = 1000;
      pypsejimas(100, 100, 3);
      setpoint = laipsniai;
      stopas = 0;
      break;
    }


    lcd.setCursor(0, kursorius);
    lcd.print(">");
    for (byte i = 0; i <= 3; i++) {
      lcd.setCursor(1, i);
      lcd.print(Varikliu_meniu[i]);
    }

  }
}
void greicio_nustatymai() {
  while (true) {
    mygtukai();
    if ((Enter + Plius + Minus + Save) != 0) {
      busena = 4;
      elementas = 2;
      kursorius = 2;
      pastumimas = 0;
      lcd.clear();
      delay(10);
      break;
    }

    lcd.setCursor(2, 1);
    lcd.print("Vis dar kuriama");
  }
}

////////////////////////// Varikliu funkcijos //////////////////////////////////////////
void motor(int left, int right) {
  //right = right * (-1);
  //left = left * (-1);

  right = constrain(right, -255, 255);
  left = constrain(left, -255, 255);

  if (right >= 0) {
    digitalWrite(r_motor, LOW);
    analogWrite(R_motor, right);
  }
  else {
    digitalWrite(r_motor, HIGH);
    analogWrite(R_motor, right * (-1));
  }
  if (left >= 0) {
    digitalWrite(l_motor, LOW);
    analogWrite(L_motor, left);
  }
  else {
    digitalWrite(l_motor, HIGH);
    analogWrite(L_motor, left * (-1));
  }
}
void letejimas(int nuo, int iki, int laikas, bool puse) {
  while (stopas == false) {
    for (int i = nuo; i >= iki; i--) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = iki;
        break;
      }
      if (puse == 1) {
        motor(i, i);
      }
      else {
        motor(-i, -i);
      }
      delay(laikas);
    }
    motor(0, 0);
    delay(100);
    break;
  }
}
void greitejimas(int nuo, int iki, int laikas, bool puse, long laikas_pilnu) {

  while (stopas == false) {
    for (int i = nuo; i <= iki; i++) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = iki;
        laikas = 0;
        break;
      }
      if (puse == 1) {
        motor(i, i);
      }
      else {
        motor(-i, -i);
      }
      delay(laikas);
    }
    avariniai_sensoriai();

    for (int i = 0; i <= laikas_pilnu; i++) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = laikas_pilnu;
        break;
      }
      if (puse == 1) {
        motor(iki, iki);
      }
      else {
        motor(-iki, -iki);
      }
      delay(1);
    }
    break;
  }
}
int taskas, atsisuke;

void linijos_palaikymas(int norimas_greitis, int palaikymo_taskas) {
  /*if(palaikymo_taskas<280 && palaikymo_taskas>80){
    error = palaikymo_taskas - laipsniai;
  }
  else{
   if(palaikymo_taskas>=0 && palaikymo_taskas<=80 & laipsniai>180 & laipsniai<=360){
     error = (palaikymo_taskas+360) - laipsniai;
   }
   else if(palaikymo_taskas>=0 && palaikymo_taskas<=80 & laipsniai>=0 & laipsniai<=180){
     error = palaikymo_taskas - laipsniai;
   }
    else if(palaikymo_taskas>=280 && palaikymo_taskas<=360 & laipsniai>=0 & laipsniai<=180){
     error = palaikymo_taskas - (laipsniai+360);
   }
    else if(palaikymo_taskas>=280 && palaikymo_taskas<=360 & laipsniai>180 & laipsniai<=360){
     error = palaikymo_taskas - laipsniai;
   }
   else{
       error = palaikymo_taskas - laipsniai;
   }
  }*/
  error = (palaikymo_taskas - laipsniai) * (-1);


  error = constrain(error, -70, 70);

  P = error;
  I = I + previous_I;
  D = error - previous_error;

  V = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;

  if (V >= 255) {
    V = 255;
  }
  else if (V < -255) {
    V = -255;
  }

  motor(norimas_greitis + V, norimas_greitis - V);
  Serial.print(laipsniai);
  Serial.print("      ");
  Serial.println(V);
}

void pasisukimas(int greitisx, long sukimosi, bool puse, long greitejimo_laikas) {
  while (stopas == false) {
    for (int i = 50; i <= greitisx; i++) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = greitisx;
        break;
      }
      if (puse == 0) {
        motor(-i, i);
      }
      else {
        motor(i, -i);
      }
      delay(greitejimo_laikas);
    }

    for (int i = 0; i <= sukimosi / 10; i++) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = sukimosi / 100;
        break;
      }
      if (puse == 0) {
        motor(-greitisx, greitisx);
      }
      else {
        motor(greitisx, -greitisx);
      }
      delay(10);
    }

    for (int i = greitisx; i >= 0; i--) {
      avariniai_sensoriai();
      if (stopas == true) {
        i = 0;
        break;
      }
      if (puse == 0) {
        motor(-i, i);
      }
      else {
        motor(i, -i);
      }
      delay(greitejimo_laikas);
    }
    motor(0, 0);
    delay(50);
    break;
  }
}


void pid_nulinimas() {
  error = 0;
  P = 0;
  I = 0;
  D = 0;
  V = 0;
  previous_error = 0;
  previous_I = 0;
}

void apsisukimas(long pasisukimo_kampas, bool puse, int pasisukimo_greitis, int greitejimo_laikas) {
  kampas();
  if (puse == 1) {
    pasisukimo_kampas = pasisukimo_kampas * (-1);
  }
  pasisukimo_kampas = laipsniai + pasisukimo_kampas * 2;
  //delay(5);
  for (int i = 50; i <= pasisukimo_greitis; i++) {
    avariniai_sensoriai();
    if (stopas == true) {
      break;
    }
    if (puse == 0) {
      motor(-i, i);
    }
    else {
      motor(i, -i);
    }
    delay(greitejimo_laikas);
  }
  unsigned long nuskaitymui = millis();
  unsigned long sukimosi_taimeris = millis();
   sensoriu_reset();
   
  while (stopas == false) {
    kampas();
    if (millis() - nuskaitymui >= 20) {
      nuskaitymui = millis();
      avariniai_sensoriai();
    }
   
    if (millis() - sukimosi_taimeris >= 6000) {
      sukimosi_taimeris = millis();
      motor(0, 0);
      break;
    }

    if (pasisukimo_kampas == laipsniai || pasisukimo_kampas == (laipsniai + 13) || pasisukimo_kampas == (laipsniai - 13)) {
      motor(0, 0);
      break;
    }
    else if (pasisukimo_kampas > laipsniai) {
      motor(-pasisukimo_greitis, pasisukimo_greitis);
    }
    else if (pasisukimo_kampas < laipsniai) {
      motor(pasisukimo_greitis, -pasisukimo_greitis);
    }
    else if (pasisukimo_kampas - laipsniai >= 1500 || pasisukimo_kampas - laipsniai <= -1500) {
      motor(0, 0);
      break;
    }
  }
  for (int i = pasisukimo_greitis; i >= 0; i--) {
    avariniai_sensoriai();
    if (stopas == true) {
      break;
    }
    if (puse == 0) {
      motor(-i, i);
    }
    else {
      motor(i, -i);
    }
    delay(greitejimo_laikas);
  }
    isejimas:
    motor(0,0);
}

