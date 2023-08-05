String ddays[7] = {"Pr", "An", "Tr","Ke", "Pn", "Se","S"};
void laukimo_busena() {
  digitalWrite(filtro_maitinimas, LOW);
  lcd.clear();
  gavimas_is_nano();
  siuntimas_nameliui(0, 4);
  int ligi_paleidimo = 0;
  int ligi_baigimo = 0;
  
  int v = 0;  // valandos ligi paleidimo
  int mm = 0; // minutes ligi paleidimo
  bool galima_vaziuoti = true;
   
  pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
  pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
  dabartinis_laikas = laiko_konvertavimas(hour,minutes);

  rainDelay = lietaus_laukimo_v * 3600000 + lietaus_laukimo_m *60000;
  
  while (true) {
    gavimas_is_namelio();
    gavimas_is_nano();
    mygtukai();
    
    pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
    pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
    dabartinis_laikas = laiko_konvertavimas(hour,minutes);
    
    if(namo_mygtukas == 1){
      namu_pozicija = true;
    }

    if(lietus == 2){ rain_status = true; sausa = false;}
    else if(lietus == 1){ rain_status = false; }

    if (rain_status == true && isRaining == false) {
      // Rain just started, record the start time
      isRaining = true;
      sausa = false; 
    } else if (rain_status == false && isRaining == true) {
      // Rain has stopped, record the stop time and start the 6-hour timer
      isRaining = false;
      rainStartTime = millis();
    }
    
    if (isRaining == false && (millis() - rainStartTime >= rainDelay)) { sausa = true; }
    else{ sausa = false; }

    if(sausa == true){
    if(dirbimo[weekDay] == 1){
       if(dabartinis_laikas <= pasileidimo_laikas - pasileidimas_anksciau){
        v = (pasileidimo_laikas -pasileidimas_anksciau - dabartinis_laikas)/60;
        mm = (pasileidimo_laikas - pasileidimas_anksciau - dabartinis_laikas)-(v*60);
        lcd.setCursor(4, 2);
        lcd.print("Pasileis uz: ");
        lcd.setCursor(5, 3);
        lcd.print(v);
        lcd.print("val ");
        lcd.print(mm);
        lcd.print("min ");
         if(v== 3 && mm == 30){ busena = 6; break; }
         if(state != 1 && dabartinis_laikas <= pasileidimo_laikas - 20){
           vartu_uzdarymas();   //uzdarom namelio duris
           delay(2000);
          siuntimas_nameliui(0, 4);
         }
       }
       if(dabartinis_laikas >= pabaigos_laikas) {
           lcd.setCursor(2, 3);
          lcd.print("Liko: Kita diena");
       }
     }
     else{
       lcd.setCursor(2, 3);
       lcd.print("Liko: Kita diena");
        if(state != 1){
           vartu_uzdarymas();   //uzdarom namelio duris
           delay(2000);
          siuntimas_nameliui(0, 4);
         }
     }
    }
    else{

        v  = (laiko_konvertavimas(lietaus_laukimo_v,lietaus_laukimo_m) - ms_min(millis() - rainStartTime))/60;
        mm = (laiko_konvertavimas(lietaus_laukimo_v,lietaus_laukimo_m) - ms_min(millis() - rainStartTime))-(v*60);
        
        lcd.setCursor(4, 2);
        lcd.print("Lietaus rez. ");
        lcd.setCursor(5, 3);
        lcd.print(v);
        lcd.print("val ");
        lcd.print(mm);
        lcd.print("min ");
        
        if(v== 3 && mm == 30){ busena = 6; break; }
        
        if(state != 1){
           vartu_uzdarymas();   //uzdarom namelio duris
           delay(2000);
          siuntimas_nameliui(0, 4);
         }
    }
     
    lcd.setCursor(3, 1);
    lcd.print("Laukimo busena");

    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.print(akumas);
    lcd.print("V ");
    
    lcd.setCursor(10, 0);
    lcd.print(ddays[weekDay]);
    
    lcd.setCursor(14, 0);
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

    if (akumas <= budejimo_krovimas && namu_pozicija == true) {
      busena = 6;
      break;
    }
    if ((Enter + Save + Plius + Minus) != 0) {
      busena = 2;
      delay(100);
      lcd.clear();
      break;
    }
    ///////////////////// auto isvaziavimas //////////////////////////////////////
     if(auto_start == true && sausa == true && hour>=6){
         rankinis_paleidimas = false;
         baigta_darbo_diena = false;
         if(namu_pozicija == false){ nustatymas_kur_esu(); }
         if (namu_pozicija == true) {
           if(duris_atidarytos == false){
              vartu_atidarymas();
            }
           busena = 8;
           break;
         }
         else {
           paleidimas();
           break;
         }
     }
     
     if(dirbimo[weekDay] == 1 && hour>=6){
       if(dabartinis_laikas>=pasileidimo_laikas-pasileidimas_anksciau && dabartinis_laikas<pabaigos_laikas && sausa == true){
         auto_start = true;
       }
       else{
        auto_start = false;
       }
     }
    ////////////////////////////////////////////////////////////////////////////////

    if (stop_mygtukas == HIGH && hour>=6) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Rankinis Paleidimas");
      delay(3000);
      rankinis_paleidimas = true;
      baigta_darbo_diena = false;
      auto_start = false;
      if(namu_pozicija == false){ nustatymas_kur_esu(); }
      nustatymas_kur_esu();
      if (namu_pozicija == true) {
          if(duris_atidarytos == false){
              vartu_atidarymas();
            }
        busena = 8;
        break;
      }
      else {
        paleidimas();
        break;
      }
    }
  }
}
void nustatymas_kur_esu() {
  lcd.clear();
  lcd.setCursor(1, 5);
  lcd.print("Vietos nustatymas");
  digitalWrite(Krovimo_pin, HIGH);
  siuntimas_nameliui(5, 3);
  delay(3000);
  lcd.clear();
  while (true) {
    sroves_sensorius();
    gavimas_is_namelio();
    if (krovimo_srove >= 0.35) {
      namu_pozicija = true;
      lcd.print("Esu Namuose");
      delay(3000);
      lcd.clear();
      break;
    }
    else {
      namu_pozicija = false;
      lcd.print("Esu Lauke");
      delay(3000);
      lcd.clear();
      break;
    }
  }
  siuntimas_nameliui(0, 3);
}

