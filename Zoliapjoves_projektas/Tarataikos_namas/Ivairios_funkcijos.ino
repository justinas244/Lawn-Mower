bool lauko_led_busena = 0;
bool vidaus_led_busena = 0;

void Lauko_led(bool busena){
  sr.set(Led_lauko,busena);
}
void Vidaus_led(bool busena){
  sr.set(Led_vidus,busena);
}

