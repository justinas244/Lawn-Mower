int sekimo_greitis = 140;
unsigned long sekimo_perimetro_riba = 110;

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already
unsigned long pametimo_timeout = 3000;
int kiek_laiko_jau_aptikes = 0;
unsigned long pametimo_extra = 0;

int pirminis_aptikimas = 0;
int pirminio_aptikimo_aklosios_zonos_laikas = 12000;

void Laido_sekimas(bool reikalingas_pametimas) {
  aptiktas_laidas = 1;
  siuntimas_nameliui(5, 3);

  unsigned long now = millis();
  last_sent = now;
  previousMillis = now;
  kiek_laiko_jau_aptikes = now;
  pirminis_aptikimas = now;
  digitalWrite(Krovimo_pin, HIGH);

  while (true) {
    now = millis();
    if (now - previousMillis >= sensoriu_nuskaitymo_intervalas) {
      previousMillis = now;
      sensoriu_duomenis(1);
      sroves_sensorius();
    }

    gavimas_is_namelio();
    gavimas_is_nano();

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

    if (namo_mygtukas == 1 || krovimo_srove >= 0.35 && reikalingas_pametimas == false) {
      motor(80, 80);
      delay(500);
      motor(0, 0);
      peilio_apsukos(1000);
      last_sent = now;
      kiek_laiko_jau_aptikes = now;
      busena = 11;
      siuntimas_nameliui(1, 3);
      break;
    }

    if (kairesP >= sekimo_KP && desinesP < sekimo_DP) {
      motor(50, sekimo_greitis);
      last_sent = now;
    }
    else if (kairesP < sekimo_KP && desinesP >= sekimo_DP) {
      motor(sekimo_greitis + 30, 50);
      last_sent = now;
    }
    else if (kairesP < sekimo_KP && desinesP < sekimo_DP) {
      motor(sekimo_greitis, sekimo_greitis);
      kiek_laiko_jau_aptikes = now;
    }
    else if (kairesP >= sekimo_KP && desinesP >= sekimo_DP) {
      motor(sekimo_greitis, sekimo_greitis);
      last_sent = now;
    }
    
    if ( now - last_sent >= (pametimo_timeout + pametimo_extra) && reikalingas_pametimas == 1) {
      last_sent = now;
      busena = 7;
      break;
    }
    if (now - kiek_laiko_jau_aptikes >= 8000) {
      pametimo_extra = 0;
      pametimo_timeout = 4000;
    }
    else {
      pametimo_extra = 0;
      pametimo_timeout = 6000;
      
      atstumasD = ultragarso_atstumas (desines_T, desines_E, 2);
      atstumasC = ultragarso_atstumas (centro_T,  centro_E,  1);
      atstumasK = ultragarso_atstumas (kaires_T,  kaires_E,  0);
      
      if (atstumasC <= atstumo_ribaC) {
        if (atstumasC <= 10) {letejimas(greitis, 0, 1, 1);}
        else {letejimas(greitis, 0, 3, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis, sukimosi_laikas_Centrui ,r,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[1], r, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        r = !r;
        sensoriu_reset();
        busena = 7;
        break;
      }
      if (atstumasD <= atstumo_ribaD) {
        if(atstumasD <= 10){letejimas(greitis, 0, 1, 1);}
        else{letejimas(greitis, 0, 5, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis, sukimosi_laikas_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[2], 0, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        sensoriu_reset();
        busena = 7;
        break;
      }

      if (atstumasK <= atstumo_ribaK) {
        if (atstumasK <= 10){letejimas(greitis, 0, 1, 1);}
        else {letejimas(greitis, 0, 5, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis+10, sukimosi_laikas_kaire ,1,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[0], 1, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        sensoriu_reset();
        busena = 7;
        break;
      }
    }
  }
}

void laido_radimas() {
  peilio_apsukos(1000);
  siuntimas_nameliui(4, 3);
  unsigned long now = millis();
  last_sent = now;
  lcd.clear();
  pid_nulinimas();
  kampas();
  setpoint = laipsniai;
  stopas = 0;
  while (true) {
     sensoriai(1);
     sensoriu_duomenis(1);
     priekines_linijos_sensoriu_aptikimas();
     
  if(stop_mygtukas == HIGH) {
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

    if (desinesP >= ribaDP && kairesP >= ribaKP) {
       letejimas(greitis, 0, 2, 1);
      pypsejimas(100, 100, 1);
      motor(0, 0);
      aptiktas_laidas = 1;
      siuntimas_nameliui(3, 3);
      delay(intervalas_nuskaitymui);
      sensoriu_duomenis(1);
      if (kairesP >= ribaKP) {
        ivaziavimas_laidu(1);
        break;
      }
      else {
        siuntimas_nameliui(4, 3);
        kaires_perimetro_atsitraukimas();
        break;
      }
    }

    if(kairesP >= ribaKP) {
      letejimas(greitis, 0, 2, 1);
      pypsejimas(100, 100, 1);
      motor(0, 0);
      aptiktas_laidas = 1;
      siuntimas_nameliui(3, 3);
      delay(intervalas_nuskaitymui);
      sensoriu_duomenis(1);
      if (kairesP >= ribaKP) {
        ivaziavimas_laidu(1);
        break;
      }
      else {
        siuntimas_nameliui(4, 3);
        kaires_perimetro_atsitraukimas();
        break;
      }
    }

    if(desinesP >= ribaDP) {
      letejimas(greitis, 0, 2, 1);
      pypsejimas(100, 100, 1);
      motor(0, 0);
      aptiktas_laidas = 1;
      siuntimas_nameliui(3, 3);
      delay(intervalas_nuskaitymui);
      sensoriu_duomenis(1);
      if (desinesP >= ribaDP) {
        ivaziavimas_laidu(0);
        break;
      }
      else {
        siuntimas_nameliui(4, 3);
        desines_perimetro_atsitraukimas();
        break;
      }
    }
    
     if(atstumasC <= atstumo_ribaC) {
        if (atstumasC <= 10) {letejimas(greitis, 0, 1, 1);}
        else {letejimas(greitis, 0, 3, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis, sukimosi_laikas_Centrui ,r,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[1], r, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        r = !r;
        sensoriu_reset();
      }
      
      if (atstumasD <= atstumo_ribaD) {
        if(atstumasD <= 10){letejimas(greitis, 0, 1, 1);}
        else{letejimas(greitis, 0, 5, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis, sukimosi_laikas_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[2], 0, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        sensoriu_reset();
      }

      if (atstumasK <= atstumo_ribaK) {
        if (atstumasK <= 10){letejimas(greitis, 0, 1, 1);}
        else {letejimas(greitis, 0, 5, 1);}
        greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
        letejimas(greitis_atgal, 0, 5, 0);
        //pasisukimas(sukimosi_greitis+10, sukimosi_laikas_kaire ,1,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
        apsisukimas(ultragarsiniu_pasisukimo_kampas[0], 1, sukimosi_greitis, sukimosi_greitejimo_laikas);
        greitejimas(0, greitis, 5, 1, 0);
        pid_nulinimas();
        kampas();
        setpoint = laipsniai;
        sensoriu_reset();
      }
      
    else {
      linijos_palaikymas(greitis, setpoint);
    }
    
  }
}
void kaires_perimetro_atsitraukimas() {
  motor(0, 0);
  pypsejimas(100, 100, 1);
  greitejimas(0, greitis_atgal, 5, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
  letejimas(greitis_atgal, 0, 5, 0);
  apsisukimas(120, 1, sukimosi_greitis, sukimosi_greitejimo_laikas);
  greitejimas(0, greitis, 5, 1, 0);
  pid_nulinimas();
  kampas();
  setpoint = laipsniai;
  sensoriu_reset();
}

void desines_perimetro_atsitraukimas() {
  //letejimas(greitis, 0, 2, 1);
  motor(0, 0);
  pypsejimas(90, 90, 1);
  greitejimas(0, greitis_atgal, 5, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
  letejimas(greitis_atgal, 0, 5, 0);
  // pasisukimas(sukimosi_greitis,sukimosi_laikas_Perimetro_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
  apsisukimas(120, 0, sukimosi_greitis, sukimosi_greitejimo_laikas);
  greitejimas(0, greitis, 5, 1, 0);
  pid_nulinimas();
  kampas();
  setpoint = laipsniai;
  sensoriu_reset();
}

void ivaziavimas_laidu(bool puse) {
  pypsejimas(100, 100, 3);

  //greitejimas(0, sekimo_greitis, 3, 1, 1000);
  //letejimas(greitis, 0, 2, 1);
  for (int i = 30; i <= sekimo_greitis; i++) {
    motor(i, i);
    delay(4);
  }
  for (int i = sekimo_greitis; i >= 0; i--) {
    motor(i, i);
    delay(3);
  }
  motor(0, 0);
  unsigned long now = millis();
  last_sent = now;

  while (true) {
    now = millis();
    //kairesP = daznis(Perimetro_kaires, 10);
    //desinesP = daznis(Perimetro_desines, 10);
    sensoriai(1);
    sensoriu_duomenis(1);
    
    if (atstumasC <= atstumo_ribaC) {
      motor(0, 0);
      busena = 7;
      kaires_perimetro_atsitraukimas();
      break;
    }
    if (atstumasD <= atstumo_ribaD) {
      motor(0, 0);
      busena = 7;
      kaires_perimetro_atsitraukimas();
      break;
    }
    if (atstumasK <= atstumo_ribaK) {
      motor(0, 0);
      busena = 7;
      desines_perimetro_atsitraukimas();
      break;
    }

    if (puse == 1) {
      if (kairesP < sekimo_perimetro_riba) {
        motor(190, 50);
      }
      else {
        motor(0, 0);
        last_sent = now;
        busena = 5;
        break;
      }
    }
    else {
      if (desinesP < sekimo_perimetro_riba) {
        motor(50, 190);
      }
      else {
        motor(0, 0);
        last_sent = now;
        busena = 5;
        break;
      }
    }

    if ( now - last_sent >= 10000) {
      last_sent = now;
      busena = 7;
      break;
    }
  }
}

