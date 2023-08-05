void krovimo_busena() {
  gavimas_is_namelio();
  delay(2000);
  lcd.clear();
  digitalWrite(Krovimo_pin, HIGH);
  digitalWrite(filtro_maitinimas, LOW);
  
  bool prasidejo_krovimas = false;
  bool uzdarytos_duris = false;
  rainDelay = lietaus_laukimo_v * 3600000 + lietaus_laukimo_m *60000;
  
  if(state == 1){ uzdarytos_duris = true;}
  else{ uzdarytos_duris = false;}
  
  sroves_sensorius();
  if (krovimo_srove > 0.35) {
    prasidejo_krovimas = true;
  }
  else {
    prasidejo_krovimas = false;
  }

  if (baigta_darbo_diena == true && duris_atidarytos == true) {
    vartu_uzdarymas();   //uzdarom namelio duris
     duris_atidarytos = false;
     uzdarytos_duris = true;
     delay(2000);
     siuntimas_nameliui(1, 3);
  }
   
  if (auto_start == false && duris_atidarytos == true) {
    vartu_uzdarymas(); //uzdarom namelio duris su ijungtu krovimu.
    duris_atidarytos = false;
    uzdarytos_duris = true;
    delay(2000);
    siuntimas_nameliui(1, 3);
  }
siuntimas_nameliui(1, 3);
  while (true) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      sroves_sensorius();
      pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
      pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
      dabartinis_laikas = laiko_konvertavimas(hour,minutes);
    }

    if(lietus == 2){ rain_status = true; }
    else if(lietus == 1){ rain_status = false; }

    if (rain_status == true && isRaining == false) {
      // Rain just started, record the start time
      isRaining = true;
    } else if (rain_status == false && isRaining == true) {
      // Rain has stopped, record the stop time and start the 6-hour timer
      isRaining = false;
      rainStartTime = millis();
    }
    if (isRaining == false && (millis() - rainStartTime >= rainDelay)) { sausa = true; }
    else{ sausa = false; }
    
    
   if(dirbimo[weekDay] == 1 && rankinis_paleidimas == false){
       if(dabartinis_laikas>=pasileidimo_laikas && dabartinis_laikas<=pabaigos_laikas){
         auto_start = true;
       }
       else{
        auto_start = false;
       }
     }
     
    if (krovimo_srove <= 0.75 &&  prasidejo_krovimas == true && akumas >= 14.8) {
      digitalWrite(Krovimo_pin, LOW);
      busena = 9;
      namu_pozicija = true;
      delay(1000);
      break;
    }

    if (krovimo_srove >= 0.35) {
      prasidejo_krovimas = true;
    }
    
    if (auto_start == false && uzdarytos_duris == false) {
      vartu_uzdarymas(); //uzdarom namelio duris su ijungtu krovimu.
      uzdarytos_duris = true;
      delay(2000);
      siuntimas_nameliui(1, 3);
    }
    
    if(isRaining == true && uzdarytos_duris == false){
      vartu_uzdarymas(); //uzdarom namelio duris su ijungtu krovimu. Uzdarom duris kad neprilytu i vidu
      uzdarytos_duris = true;
      delay(2000);
      siuntimas_nameliui(1, 3);
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
  delay(3000);

  while (true) {
    sroves_sensorius();
    gavimas_is_namelio();
    if (krovimo_srove >= 0.35) {
      busena = 6;
      delay(2000);
      break;
    }
    else {
      isvaziavimas_is_namelio(9000, 1);
      busena = 10;
      break;
    }
   sensoriai(1);
   
  if (stop_mygtukas == HIGH) {
      lcd.clear();
      delay(1);
      lcd.setCursor(3, 0);
      lcd.print("Avarinis");
      lcd.setCursor(3, 1);
      lcd.print("Sustabdymas");
      busena = 2;
      peilio_apsukos(1000);
      motor(0, 0);
      pypsejimas(200, 200, 3);
      siuntimas_nameliui(0, 4);
      Stop();
      delay(2000);
      stop_mygtukas = LOW;
      lcd.clear();
      delay(1);
      break;
    }

  }
}

