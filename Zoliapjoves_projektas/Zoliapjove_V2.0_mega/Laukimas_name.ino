void laukimo_busena() {
  lcd.clear();
  gavimas_is_nano();
  siuntimas_nameliui(0, 4);
  int ligi_paleidimo = 0;
  int ligi_baigimo = 0;
  int dd = 0; // dienos ligi paleidimo
  int v = 0;  // valandos ligi paleidimo
  int mm = 0; // minutes ligi paleidimo
  while (true) {
    gavimas_is_namelio();
    gavimas_is_nano();
    mygtukai();

    ligi_paleidimo = likes_laikas(hour, minutes, weekDay);
    ligi_baigimo = likes_laikas(weekDay);
    if (ligi_paleidimo != - 10) {
      dd = ligi_paleidimo / 1440;
      v = (ligi_paleidimo - dd * 1440) / 60;
      mm = ligi_paleidimo -  dd * 1440 - v * 60;
      lcd.setCursor(4, 2);
      lcd.print("Pasileis uz: ");
      lcd.setCursor(3, 3);
      lcd.print(dd);
      lcd.print("d ");
      lcd.print(v);
      lcd.print("val ");
      lcd.print(mm);
      lcd.print("min ");
    }
    else {
      lcd.setCursor(2, 3);
      lcd.print("Liko: Nepasileis");
    }
    lcd.setCursor(2, 1);
    lcd.print("Laukimo busena");

    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.print(akumas);
    lcd.print("V ");

    lcd.setCursor(15, 0);
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
     if(ligi_paleidimo <= 2 && ligi_baigimo >=20 && ligi_paleidimo !=-10 && ligi_baigimo !=-10){
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
    ////////////////////////////////////////////////////////////////////////////////

    if (stop_mygtukas == HIGH) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Rankinis Paleidimas");
      delay(3000);
      rankinis_paleidimas = true;
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
  }
}
void nustatymas_kur_esu() {
  lcd.clear();
  lcd.setCursor(1, 5);
  lcd.print("Vietos nustatymas");
  digitalWrite(Krovimo_pin, HIGH);
  siuntimas_nameliui(5, 3);
  delay(2000);
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

int likes_laikas(int h, int mins, int dienele) {
  int rezultatas = 0;
  int ilgiau_negu_diena = 0;
  int i = 0;
  boolean radom = false;
  int rastu = 0;
  int pasalinta_pozicija = 0;
  boolean reikia_salinti = false;
 boolean reikia = true;

  for (int u = 0; u <= 6; u++) {
    if (dirbimo[u] == 1) {
      radom = true;
    }
  }
  if (radom == false) {
    return -10;
  }
  if (dirbimo[dienele] == 1 && laiko_konvertavimas(h, mins) >= laiko_konvertavimas(off_hour[dienele], off_min[dienele])) {
    dirbimo[dienele] = 0;
    pasalinta_pozicija = dienele;
    reikia_salinti = true;
    if (rastu == 1) {
      reikia = false;
      ilgiau_negu_diena = 7;
    }
    else {
      reikia_salinti = false;
      reikia = true;
    }
  }
  while (reikia == true) { //kiek skiriasi dienu
    if (dirbimo[dienele + i] == 1) {
      ilgiau_negu_diena = ilgiau_negu_diena + i;
      break;
    }
    else {
      i++;
      if (dienele + i > 6) {
        ilgiau_negu_diena = i;
        i = 0;
        dienele = 0;
      }
    }
  }

  if (ilgiau_negu_diena == 0) {
    if (dirbimo[dienele] == 1) {
      if (laiko_konvertavimas(h, mins) <= laiko_konvertavimas(on_hour[dienele], on_min[dienele])) {
        rezultatas = laiko_konvertavimas(on_hour[dienele], on_min[dienele]) - laiko_konvertavimas(h, mins);
      }
    }
    else {
      rezultatas = 0;
    }
  }
  else {
    int data = dienele + ilgiau_negu_diena;
    if (data > 6) {
      data = 0;
    }
    if (ilgiau_negu_diena == 1) {
      rezultatas = 1440 - laiko_konvertavimas(h, mins);
      rezultatas = rezultatas + laiko_konvertavimas(on_hour[data], on_min[data]);
    }
    else {
      rezultatas = 1440 - laiko_konvertavimas(h, mins);
      rezultatas = rezultatas + (1440 * (ilgiau_negu_diena - 1));
      rezultatas = rezultatas + laiko_konvertavimas(on_hour[data], on_min[data]);
    }
  }

  if (reikia_salinti == true) {
    dirbimo[pasalinta_pozicija] = 1;
    reikia_salinti = false;
  }

  return rezultatas;
}
int likes_laikas(int dienele){
     if(dirbimo[dienele] = 1){
        if(laiko_konvertavimas(hour, minutes) <= laiko_konvertavimas(off_hour[dienele], off_min[dienele])){
           return laiko_konvertavimas(off_hour[dienele], off_min[dienele]) - laiko_konvertavimas(hour, minutes);
        }
        else{
          return -10;
        }
     }
     else{
      return -10;
     }
}

