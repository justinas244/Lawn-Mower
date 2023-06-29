
unsigned long praejes_mygtuku = 0;
unsigned long mygtuku_nuskaitymo_intervalas = 100;



float keitiklis(float x, float in_min, float in_max, float out_min, float out_max)
{
  float out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  if (out < out_min) {
    return out_min;
  }
  else if (out > out_max) {
    return out_max;
  }
  else {
    return out;
  }
}


void pypsejimas(long ijungimo, long isjungimo, int kartai) {
  for (int i = 0; i < kartai; i++) {
    digitalWrite(buzeris, HIGH);
    delay(ijungimo);
    digitalWrite(buzeris, LOW);
    delay(isjungimo);
  }
}

void eepromo_nuskaitymas() {
  for (int i = 0; i <= 6; i++) {
    dirbimo[i] = EEPROM.read(i);
    on_hour[i] = EEPROM.read(7 + i);
    on_min[i] = EEPROM.read(14 + i);
    off_hour[i] = EEPROM.read(21 + i);
    off_min[i] = EEPROM.read(28 + i);
  }// uzimti adresai nuo 0 ligi 34

  optikos_kaires_kampas = EEPROM.read(35);
  optikos_desines_kampas = EEPROM.read(36);

  for (int i = 0; i <= 2; i++) {
    ultragarsiniu_aptikimo_atstumas[i] =  EEPROM.read(37 + i);
    ultragarsiniu_matymo_atstumas[i] =    EEPROM.read(40 + i);
    ultragarsiniu_pasisukimo_kampas[i] =  EEPROM.read(43 + i);
  }
  int a = EEPROM.read(46);
  int b = EEPROM.read(47);
  int c = EEPROM.read(48);
  baterijos_ofsetas = keitiklis(a, 0, 40, -0.20, 0.20);
  iskrovimo_riba =    keitiklis(b, 80, 114, 8.0, 11.4);
  budejimo_krovimas = keitiklis(c, 118, 124, 11.8, 12.4);

  ribaKP = EEPROM.read(49) * 10;
  ribaDP = EEPROM.read(50) * 10;
  sekimo_KP = EEPROM.read(51) * 10;
  sekimo_DP = EEPROM.read(52) * 10;

  Kp = keitiklis(EEPROM.read(53), 0, 99, 0, 9.90);
  Ki = keitiklis(EEPROM.read(54), 0, 99, 0, 9.90);
  Kd = keitiklis(EEPROM.read(55), 0, 99, 0, 9.90);

  peilis_naudojamas = EEPROM.read(56);
  max_peilio_greitis = map(EEPROM.read(57), 0, 100, 1000, 2000);
  min_peilio_greitis = map(EEPROM.read(58), 0, 100, 1000, 2000);

}

void sensoriu_duomenis(bool sauga) {
  sensoriai(sauga);
  lcd.setCursor(0, 0);
  lcd.print(kairesP);
  lcd.print("  ");

  lcd.setCursor(0, 1);
  lcd.print(desinesP);
  lcd.print("  ");

  lcd.setCursor(0, 3);
  lcd.print(state);
  lcd.print("  ");

  lcd.setCursor(7, 0);
  lcd.print(atstumasK);
  lcd.print(" ");
  lcd.setCursor(7, 1);
  lcd.print(atstumasC);
  lcd.print(" ");
  lcd.setCursor(7, 2);
  lcd.print(atstumasD);
  lcd.print(" ");
  lcd.setCursor(7, 3);
  lcd.print(aukstis);
  lcd.print("  ");

  lcd.setCursor(12, 0);
  lcd.print(laipsniai);
  lcd.print(" ");
  lcd.setCursor(12, 1);
  lcd.print(setpoint);
  lcd.print(" ");
  lcd.setCursor(14, 2);
  lcd.write(0);
  lcd.print(akumas);
   
  lcd.setCursor(14, 3);
  lcd.write(1);
  if (hour < 10) {
    lcd.print("0");
  }
  lcd.print(hour);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);

}

void mygtukai() {
  unsigned long laikas_mygtuku = millis();
  if (laikas_mygtuku - praejes_mygtuku > mygtuku_nuskaitymo_intervalas) {
    praejes_mygtuku = laikas_mygtuku;
    Enter = digitalRead(Enter_pin);
    Plius = digitalRead(Plius_pin);
    Minus = digitalRead(Minus_pin);
    Save = digitalRead(Save_pin);
    stop_mygtukas = digitalRead(stop_mygtuko_pin);

    if ((Enter + Plius + Minus + Save + stop_mygtukas) != 0) {
      pypsejimas(100, 100, 1);
      //delay(200);
    }
  }
}

void saugojimo_animacija() {
  lcd.clear();
  delay(10);
  lcd.setCursor(2, 0);
  lcd.print("Irasomi duomenys");
  for (int i = 2; i <= 17; i++) {
    lcd.setCursor(i, 1);
    lcd.write(255);
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Duomenys irasyti");
  delay(1000);
  lcd.clear();
}

void zoles_nustatymas() {
  float sum = 0;
  for (int i = 0; i <= 4; i++) {
    int sensorValue = analogRead(A0);
    float aukstis = (1023 - sensorValue) * (18.8 / 1023.0);
    sum = sum + (8.4 - aukstis);
    delay(200);
  }
  zoles_aukstis = sum / 5;
  if (zoles_aukstis < 0) {
    zoles_aukstis = (zoles_aukstis - 2.3) * (-1);
  }
  sum = 0;
}


void perimetro_sensoriu_skaitymas(bool puse) {

  kairesP = daznis(Perimetro_kaires, 10);
  desinesP = daznis(Perimetro_desines, 10);

  lcd.setCursor(0, 0);
  lcd.print(kairesP);
  lcd.print("  ");

  lcd.setCursor(0, 1);
  lcd.print(desinesP);
  lcd.print("  ");
  if (puse == 1) {
    if (desinesP >= 100 && desinesP < 200) {
      pypsejimas(100, 100, 1);
      delay(1000);
    }
    else if (desinesP >= 200 && desinesP < 300) {
      pypsejimas(100, 100, 2);
      delay(1000);
    }
    else if (desinesP >= 300 && desinesP < 400) {
      pypsejimas(100, 100, 3);
      delay(1000);
    }
    else if (desinesP >= 400 && desinesP < 500) {
      pypsejimas(100, 100, 4);
      delay(1000);
    }
    else if (desinesP >= 500 && desinesP < 600) {
      pypsejimas(100, 100, 5);
      delay(1000);
    }
  }
  else {
    if (kairesP >= 100 && kairesP < 200) {
      pypsejimas(100, 100, 1);
      delay(1000);
    }
    else if (kairesP >= 200 && kairesP < 300) {
      pypsejimas(100, 100, 2);
      delay(1000);
    }
    else if (kairesP >= 300 && kairesP < 400) {
      pypsejimas(100, 100, 3);
      delay(1000);
    }
    else if (kairesP >= 400 && kairesP < 500) {
      pypsejimas(100, 100, 4);
      delay(1000);
    }
    else if (kairesP >= 500 && kairesP < 600) {
      pypsejimas(100, 100, 5);
      delay(1000);
    }
  }
}

void PID_nustatymai() {
  kursorius = 0;
  pastumimas = 0;
  rodykle = 0;
  spaudimo_busena = 0;

  while (true) {
    mygtukai();

    if (Enter == HIGH) {
      spaudimo_busena++;
      if (kursorius <= 2) {
        if (spaudimo_busena == 1) {
          rodykle = 15;
          delay(50);
        }
        else if (spaudimo_busena > 1) {
          rodykle = 0;
          spaudimo_busena = 0;
          delay(50);
        }
      }
      else if (kursorius == 3) {
        busena = 4;
        elementas = 2;
        kursorius = 0;
        pastumimas = 1;
        lcd.clear();
        delay(10);
        break;
      }
      lcd.clear();
    }
    else if (Plius == HIGH) {
      if (spaudimo_busena == 0) {
        kursorius++;
        if (kursorius > 3) {
          kursorius = 0;
        }
        delay(1);
        lcd.clear();
      }
      else {
        if (kursorius == 0) {
          Kp += 0.1;
          if (Kp > 9.90) {
            Kp = 0;
          }
        }
        else if (kursorius == 1) {
          Ki += 0.1;
          if (Ki > 9.90) {
            Ki = 0;
          }
        }
        else if (kursorius == 2) {
          Kd += 0.1;
          if (Kd > 9.90) {
            Kd = 0;
          }
        }
      }
    }
    else if (Minus == HIGH) {
      if (spaudimo_busena == 0) {
        kursorius--;
        if (kursorius < 0) {
          kursorius = 3;
        }
        delay(1);
        lcd.clear();
      }
      else {
        if (kursorius == 0) {
          Kp -= 0.1;
          if (Kp < 0) {
            Kp = 9.90;
          }
        }
        else if (kursorius == 1) {
          Ki -= 0.1;
          if (Ki < 0) {
            Ki = 9.90;
          }
        }
        else if (kursorius == 2) {
          Kd -= 0.1;
          if (Kd < 0) {
            Kd = 9.90;
          }
        }
      }
    }
    else if (Save == HIGH) {
      EEPROM.write(53, Kp * 10);
      EEPROM.write(54, Ki * 10);
      EEPROM.write(55, Kd * 10);
      busena = 4;
      elementas = 2;
      kursorius = 0;
      pastumimas = 0;
      saugojimo_animacija();
      break;
    }

    lcd.setCursor(rodykle, kursorius);
    lcd.print(">");

    lcd.setCursor(16, 0);
    lcd.print(Kp);

    lcd.setCursor(16, 1);
    lcd.print(Ki);

    lcd.setCursor(16, 2);
    lcd.print(Kd);

    for (byte i = 0; i <= 3; i++) {
      lcd.setCursor(1, i);
      lcd.print(PID_langas[i]);
    }
  }
}
void PID_testavimas() {
  while (true) {
    mygtukai();
    if ((Enter + Plius + Minus + Save) != 0) {
      busena = 4;
      elementas = 2;
      kursorius = 3;
      pastumimas = 0;
      lcd.clear();
      delay(10);
      break;
    }

    lcd.setCursor(2, 1);
    lcd.print("Vis dar kuriama");
  }
}

void valymo_busena() {
  while (true) {
    lcd.setCursor(0, 0);
    lcd.print("Valymo ciklas");
  }
}
void kampo_parinkimas() {
  randomSeed(analogRead(A15));
  int puse = random(0, 10);

  if (puse >= 5) {
    puse = 1;
  }
  else {
    puse = 0;
  }

  int kampas = random(60, 130);
  apsisukimas(kampas, puse, sukimosi_greitis, sukimosi_greitejimo_laikas);

}
void isvaziavimas_is_namelio(unsigned long timeoutas, int tipas) {
  unsigned long now = millis();
  last_sent = now;
  previousMillis = now;
  kampas();
  lcd.clear();
  siuntimas_nameliui(4, 3);
  delay(1000);
  kampas();
  setpoint = laipsniai;
  while (true) {
    now = millis();
    if ( now - last_sent >= timeoutas) {
      last_sent = now;
      letejimas(greitis, 0, 5, 0);
      if (tipas == 0) {
        kampo_parinkimas();
        motor(0, 0);
        delay(3000);
        paleidimas();
      }
      else if ( tipas == 1) {
        busena = 10;
      }
      pid_nulinimas();
      kampas();
      setpoint = laipsniai;
      break;
    }
    kampas();
    linijos_palaikymas_atgal(-greitis, setpoint);

    lcd.setCursor(12, 0);
    lcd.print(laipsniai);
    lcd.print(" ");
    lcd.setCursor(12, 1);
    lcd.print(setpoint);
    lcd.print(" ");
    delay(1);
  }
}
void paleidimas() {
  digitalWrite(mygtuku_maitinimas, LOW);
  digitalWrite(filtro_maitinimas, HIGH);
  busena = 1;
  uzkurimas = 1;
  peilio_greicio_nustatymas();
  siuntimas_nameliui(2, 4);
  pypsejimas(100, 100, 3);
  kampas();
  setpoint = laipsniai;
  stopas = false;
  su_garsu = 1;
}

void vartu_atidarymas() {
  siuntimas_nameliui(6, 4);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Laukimo busena");
  lcd.setCursor(2, 1);
  lcd.print("Vartu atidarymas");
  gavimas_is_nano();
  for (int i = 140; i >= 0; i--) {
    lcd.setCursor(2, 2);
    lcd.print("Liko laiko: ");
    lcd.print(i);
    lcd.print("  ");
    delay(1000);
    gavimas_is_nano();
  }
  lcd.clear();
  while (true) {
    gavimas_is_namelio();
    gavimas_is_nano();
    if (state == 3) {
      lcd.setCursor(2, 0);
      lcd.print("Laukimo busena");
      lcd.setCursor(2, 1);
      lcd.print("Vartai OPEN");
      delay(5000);
      lcd.clear();
      baigta_darbo_diena = false;
      duris_atidarytos = true;
      break;
    }
    else {
      lcd.setCursor(2, 3);
      lcd.print(state);
    }
  }
}
void vartu_uzdarymas() {
  siuntimas_nameliui(7, 4);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Laukimo busena");
  lcd.setCursor(2, 1);
  lcd.print("Vartu uzdarymas");
  for (int i = 135; i >= 0; i--) {
    lcd.setCursor(2, 2);
    lcd.print("Liko laiko: ");
    lcd.print(i);
    lcd.print("  ");
    delay(1000);
    gavimas_is_nano();
  }
  lcd.clear();
  while (true) {
    gavimas_is_namelio();
    gavimas_is_nano();
    if (state == 1) {
      lcd.setCursor(2, 0);
      lcd.print("Laukimo busena");
      lcd.setCursor(2, 1);
      lcd.print("Vartai CLOSE");
      delay(5000);
      lcd.clear();
      baigta_darbo_diena = false;
      duris_atidarytos = false;
      break;
    }
    else {
      lcd.setCursor(2, 3);
      lcd.print(state);
    }
  }
}

