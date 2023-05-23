float dregnumas,temperatura;


void dht_nuskaitymas(){
   dregnumas = dht.readHumidity();
   temperatura = dht.readTemperature();
   if (isnan(dregnumas) || isnan(temperatura)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

