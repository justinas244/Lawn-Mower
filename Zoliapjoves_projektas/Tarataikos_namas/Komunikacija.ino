void siuntimas_robotui() {
  // Check the network regularly
  unsigned long now = millis();              // If it's time to send a message, send it!
  if ( now - last_sent >= interval  )
  {
    mygtuku_nuskaitymas();
    last_sent = now;
    for (int i = 0; i <= 3; i++) {
      robotas.write(d[i]);
    }
  }
}

void roboto_nuskaitymas() {
  if(robotas.available()){
    int a = robotas.read();
    busena = a;
    Serial.print("Gauta busena: ");
    Serial.println(busena);
  }
}

