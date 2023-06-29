/*void vaziavimas_atgal(int greitisx, unsigned long vaziavimo_laikas){
  unsigned long now = millis();
  last_sent = now;
  previousMillis = now;
  kampas();
  while(true){
    now = millis();
    sensoriai(1);
    if ( now - last_sent >= vaziavimo_laikas){
      pid_nulinimas();
      break;
    }
    else{
     kampas();
     linijos_palaikymas_atgal(-greitisx, setpoint);
    }

    if(stop_mygtukas == HIGH){
      busena = 2;
      peilio_apsukos(1000);
      motor(0,0);
      break;
    }
  } 
}*/

