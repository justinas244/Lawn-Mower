void sensoriai() {
  gavimas_is_nano();
  //komposas();
  if(akumas>11){greitis = 120; greitisA = 160;}
  else{ 
  greitis = int(keitiklis(akumas,9,11,170,120)); 
  greitisA = int(keitiklis(akumas,9,11,220,160));
  }
  //peilio_greitis = int(keitiklis(akumas,9,12,1700,1500));
  
  atstumasD = ultragarso_atstumas (desines_T, desines_E);
  atstumasC = ultragarso_atstumas (centro_T,  centro_E);
  atstumasK = ultragarso_atstumas (kaires_T,  kaires_E);
  
  Serial.print(atstumasK);
  Serial.print("     ");
  Serial.print(atstumasC);
  Serial.print("     ");
  Serial.print(atstumasD);
  Serial.println("     ");
  
}

int ultragarso_atstumas(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if(distance>400 || distance<0){distance = 400;}
  return distance;
}
