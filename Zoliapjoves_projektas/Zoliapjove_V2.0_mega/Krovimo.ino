void krovimo_busena() {
  siuntimas_nameliui(1, 3);
  lcd.clear();
  digitalWrite(Krovimo_pin, HIGH);
  digitalWrite(filtro_maitinimas, LOW);
  bool prasidejo_krovimas = false;
  bool uzdarytos_duris = false;
  sroves_sensorius();
  if (krovimo_srove > 0.35) {
    prasidejo_krovimas = true;
  }
  else {
    prasidejo_krovimas = false;
  }

  if (baigta_darbo_diena == true && duris_atidarytos == true) {
    vartu_uzdarymas();   //uzdarom namelio duris
  }
  if (dirbimo[weekDay] == 1 && laiko_konvertavimas(hour, minutes) >= laiko_konvertavimas(off_hour[weekDay], off_min[weekDay]) && duris_atidarytos == true) {
    vartu_uzdarymas(); //uzdarom namelio duris su ijungtu krovimu.
  }

  while (true) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      sroves_sensorius();
    }

    if (krovimo_srove <= 0.55 &&  prasidejo_krovimas == true) {
      digitalWrite(Krovimo_pin, LOW);
      busena = 9;
      delay(1000);
      break;
    }

    if (krovimo_srove >= 0.35) {
      prasidejo_krovimas = true;
    }
    
    if (dirbimo[weekDay] == 1 && laiko_konvertavimas(hour, minutes) >= laiko_konvertavimas(off_hour[weekDay], off_min[weekDay]) && uzdarytos_duris == false) {
      vartu_uzdarymas(); //uzdarom namelio duris su ijungtu krovimu.
      uzdarytos_duris = true;
    }
    
    gavimas_is_nano();
    gavimas_is_namelio();

    lcd.setCursor(2, 0);
    lcd.print("Krovimo busena");

    lcd.setCursor(0, 1);
    lcd.print("Baterija:");

    lcd.setCursor(12, 1);
    lcd.print(akumas);
    lcd.print("V ");

    lcd.setCursor(0, 2);
    lcd.print("Srove:");

    lcd.setCursor(13, 2);
    lcd.print(krovimo_srove);
    lcd.print("A ");
    motor(0, 0);      //Krovimas

    lcd.setCursor(0, 3);
    lcd.print("Kraunasi:");
    lcd.setCursor(13, 3);
    if (prasidejo_krovimas == true) {
      lcd.print("TAIP");
      namu_pozicija = true;
    }
    else {
      lcd.print("NE  ");
    }
  }
}
void Ivaziavimo_patikra() {
  lcd.clear();
  lcd.setCursor(1, 5);
  lcd.print("Ivaziavimo patikra");
  digitalWrite(Krovimo_pin, HIGH);
  siuntimas_nameliui(5, 3);
  delay(2000);

  while (true) {
    sroves_sensorius();
    gavimas_is_namelio();
    if (krovimo_srove >= 0.35) {
      busena = 6;
      delay(2000);
      break;
    }
    else {
      isvaziavimas_is_namelio(2400, 1);
      busena = 10;
      break;
    }
  }
}

