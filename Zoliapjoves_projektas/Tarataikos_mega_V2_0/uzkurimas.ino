void uzkurti(){
  digitalWrite(varikliu_maitinimas, HIGH);
  digitalWrite(peilio_maitinimas,HIGH);
  delay(5000);
  peilis.writeMicroseconds(1000);
  delay(3000);
  peilis.writeMicroseconds(peilio_greitis);
  delay(7000);
  uzkurimas = 0;
}
void Stop(){
  peilis.writeMicroseconds(1000);
  motor(0,0);
  delay(2000);
  digitalWrite(peilio_maitinimas,LOW);
  uzkurimas = 1;
  busena = 0;
}


