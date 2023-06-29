String ddays[7] = {"Pr", "An", "Tr","Ke", "Pn", "Se","S"};
void laukimo_busena() {
  lcd.clear();
  gavimas_is_nano();
  siuntimas_nameliui(0, 4);
  int ligi_paleidimo = 0;
  int ligi_baigimo = 0;
  
  int v = 0;  // valandos ligi paleidimo
  int mm = 0; // minutes ligi paleidimo
  
  pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
  pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
  dabartinis_laikas = laiko_konvertavimas(hour,minutes);
  
  while (true) {
    gavimas_is_namelio();
    gavimas_is_nano();
    mygtukai();
    
    pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay],on_min[weekDay]);
    pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay],off_min[weekDay]);
    dabartinis_laikas = laiko_konvertavimas(hour,minutes);


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
         if(v== 4 && mm == 0){ busena = 6; break; }
       }
       if(dabartinis_laikas >= pabaigos_laikas) {
           lcd.setCursor(2, 3);
          lcd.print("Liko: Kita diena");
       }
     }
     else{
       lcd.setCursor(2, 3);
       lcd.print("Liko: Kita diena");
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
     if(auto_start == true){
         rankinis_paleidimas = false;
         baigta_darbo_diena = false;
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
     if(dirbimo[weekDay] == 1){
       if(dabartinis_laikas>=pasileidimo_laikas-pasileidimas_anksciau && dabartinis_laikas<pabaigos_laikas){
         auto_start = true;
       }
       else{
        auto_start = false;
       }
     }
    ////////////////////////////////////////////////////////////////////////////////

    if (stop_mygtukas == HIGH) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Rankinis Paleidimas");
      delay(3000);
      rankinis_paleidimas = true;
      baigta_darbo_diena = false;
      auto_start = false;
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

