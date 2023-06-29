void gavimas_is_nano() {
  if (Serial2.available() >= 9) {
    int a = Serial2.read();
    if (a == 255) {
      for (int i = 1; i <= 8; i++) {
        data[i] = Serial2.read();
        Serial.println(data[i]);
      }
      if (data[1] >= 0 && data[2] >= 0) {
        akumas = data[1] + float(data[2]) / 100 + baterijos_ofsetas;
      }
      if (data[3] >= 0) {
        hour = data[3];
      }
      if (data[4] >= 0) {
        minutes = data[4];
      }
      if (data[5] >= 1) {
        weekDay = data[5] - 1;
      }
      if (data[6] >= 0) {
        monthDay = data[6];
      }
      if (data[7] >= 0) {
        month = data[7];
      }
      if (data[8] >= 0) {
        year = data[8];
      }
    }
  }
}
void siuntimas_nameliui(int komanda, int siuntimo_kartai) {
  if (komanda == 0) {
    komanda = 10;
  }
  for (int i = 0; i < siuntimo_kartai; i++) {
    Serial3.write(komanda);
    delay(500);
  }
}
int a, b, c, d;
void gavimas_is_namelio() {
  if (Serial3.available()) {
    a = Serial3.read();
    b =  Serial3.read();
    c =  Serial3.read();
    d =   Serial3.read();

    if (a > 0) {
      state = a;
    }
    if (c > 0) {
      lietus = c;
    }
    if (b >= 0) {
      namo_mygtukas = b;
    }
    if (d > 0) {
      valymas = d;
    }
  }
}

