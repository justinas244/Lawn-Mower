unsigned long  veikimo_timeout = 120000;
unsigned long baterijos_patikros_laikas = 5000;
void vaziavimas() {

  veikimo_laikas = millis();
  baterijos_check = millis();
  while (true) {
    if (millis() - previousMillis >= sensoriu_nuskaitymo_intervalas) {
      previousMillis = millis();
      //sensoriai(1);
      sensoriu_duomenis(1);
    }

    if (millis() - baterijos_check >= baterijos_patikros_laikas) {
      baterijos_check = millis();
      if (akumas <= iskrovimo_riba) {
        iskrautas++;
      }
      else {
        iskrautas = 0;
      }
    }

    /* if(currentMillis - veikimo_laikas >= veikimo_timeout) {
     peilio_apsukos(1000);
     peilio_greitis = 1000;
     motor(0,0);
     pypsejimas(200,200,5);
     delay(5000);
     busena = 7;
    }*/

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

    gavimas_is_namelio();
    gavimas_is_nano();

    pasileidimo_laikas = laiko_konvertavimas(on_hour[weekDay], on_min[weekDay]);
    pabaigos_laikas = laiko_konvertavimas(off_hour[weekDay], off_min[weekDay]);
    dabartinis_laikas = laiko_konvertavimas(hour, minutes);

    if (dirbimo[weekDay] == 1 && rankinis_paleidimas == false) {
      if (dabartinis_laikas >= pabaigos_laikas - 1) {
        auto_start = false;
        busena = 7;
        peilio_apsukos(1000);
        peilio_greitis = 1000;
        motor(0, 0);
        delay(5000);
        baigta_darbo_diena = true;
        rankinis_paleidimas = false;
        break;
      }
    }

    if (akumas <= iskrovimo_riba) {
      if (iskrautas >= 6) {
        busena = 7;
        peilio_apsukos(1000);
        peilio_greitis = 1000;
        motor(0, 0);
        delay(5000);
        if (rankinis_paleidimas == true) {
          baigta_darbo_diena = true;
        } else {
          baigta_darbo_diena = false;
        }
        break;
      }
    }
    else {
      if (akumas <= 10.0) {
        peilio_apsukos(peilio_greitis + 100);
        greitis = 150;
        greitis_atgal = 220;
        sukimosi_greitis = 190;
        sukimosi_laikas_Perimetro_kaire = 420;
        sukimosi_laikas_Perimetro_desine = 350;
        sukimosi_laikas_Centrui = 360;
        sukimosi_laikas_desine = 350;
        sukimosi_laikas_kaire = 420;
        atgal_vaziavimo_laikas = 80;
      }
      else {
        peilio_apsukos(peilio_greitis);
      }
    }
    priekines_linijos_sensoriu_aptikimas();
     if (kairesP >= ribaKP && desinesP >= ribaDP) {
       letejimas(greitis, 0, 2, 1);
       pypsejimas(110, 110, 1);
       greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
       letejimas(greitis_atgal, 0, 5, 0);
       apsisukimas(ultragarsiniu_pasisukimo_kampas[1],r,sukimosi_greitis, sukimosi_greitejimo_laikas);
       greitejimas(0, greitis, 5, 1,0);
       pid_nulinimas();
      kampas();
      setpoint = laipsniai;
      r=!r;
      sensoriu_reset();
     }
    else if (kairesP >= ribaKP) {
      letejimas(greitis, 0, 2, 1);
      pypsejimas(100, 100, 1);
      greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
      letejimas(greitis_atgal, 0, 5, 0);
      apsisukimas(120, 1, sukimosi_greitis, sukimosi_greitejimo_laikas);
      greitejimas(0, greitis, 5, 1, 0);
      pid_nulinimas();
      kampas();
      setpoint = laipsniai;
      sensoriu_reset();
      r=1;
    }
    if (desinesP >= ribaDP) {
      letejimas(greitis, 0, 2, 1);
      pypsejimas(90, 90, 1);
      greitejimas(0, greitis_atgal, greitejimo_laikas_atgal, 0, atgal_vaziavimo_laikas); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
      letejimas(greitis_atgal, 0, 5, 0);
      // pasisukimas(sukimosi_greitis,sukimosi_laikas_Perimetro_desine ,0,sukimosi_greitejimo_laikas); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
      apsisukimas(120, 0, sukimosi_greitis, sukimosi_greitejimo_laikas);
      greitejimas(0, greitis, 5, 1, 0);
      pid_nulinimas();
      kampas();
      setpoint = laipsniai;
      sensoriu_reset();
      r=0;
    }
    else {
      linijos_palaikymas(greitis, setpoint);
    }
  }
}
