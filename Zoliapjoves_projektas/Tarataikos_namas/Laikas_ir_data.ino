byte sekundes, valandos, minutes, savaites_diena, menesio_diena, menesis, metai;

byte bcdToDec(byte val) {
  return ( (val / 16 * 10) + (val % 16) );
}
void Laikas() {
  Wire.beginTransmission(DS1307_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  sekundes = bcdToDec(Wire.read());
  minutes = bcdToDec(Wire.read());
  valandos = bcdToDec(Wire.read() & 0b111111);
  savaites_diena = bcdToDec(Wire.read());
  menesio_diena = bcdToDec(Wire.read());
  menesis = bcdToDec(Wire.read());
  metai = bcdToDec(Wire.read());

}

