void vaziavimas(){
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= sensoriu_nuskaitymo_intervalas) {
    previousMillis = currentMillis;   
    sensoriai();
  }
  if(akumas<10.5){ peilio_greitis = 1600;}
  peilis.writeMicroseconds(peilio_greitis);
  
  if(atstumasC <= atstumo_ribaC){
    letejimas(greitis, 0, 5, 1);
    delay(100);
    greitejimas(0, greitisA, 5, 0); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    motor(-greitisA,-greitisA);
    delay(1000);
    letejimas(greitisA, 0, 5, 0);
    pasisukimas(greitisA,1400,0,5); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    greitejimas(0, greitis, 5, 1);
    //komposas();
    setpoint = laipsniai;
  }
  else if(atstumasD <= atstumo_ribaD){
    letejimas(greitis, 0, 5, 1);
    delay(100);
    greitejimas(0, greitisA, 5, 0); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    motor(-greitisA,-greitisA);
    delay(1000);
    letejimas(greitisA, 0, 5, 0);
    pasisukimas(greitisA,1200,0,5); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    greitejimas(0, greitis, 5, 1);
    //komposas();
    setpoint = laipsniai;
    
  }
   else if(atstumasK <= atstumo_ribaK){
    letejimas(greitis, 0, 5, 1);
    delay(100);
    greitejimas(0, greitisA, 5, 0); // nuo, iki, laikas, puse(priekis = 1, atgal = 0)
    motor(-greitisA,-greitisA);
    delay(1000);
    letejimas(greitisA, 0, 5, 0);
    pasisukimas(greitisA,1400,1,5); //greitis, laikas sukimosi, puse, greitejimo,letejimo greitis
    greitejimas(0, greitis, 5, 1);
   // komposas();
    setpoint = laipsniai;
  }
  else{
    linijos_palaikymas(greitis, setpoint);
  }
}
