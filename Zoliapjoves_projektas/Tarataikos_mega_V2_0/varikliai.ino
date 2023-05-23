void motor(int left, int right){
  
   left=constrain(left, -255, 255);
  right=constrain(right, -255, 255);

  if(left>=0){
    digitalWrite(l_motor,HIGH);
    analogWrite(L_motor,left);
  }
  else{
    digitalWrite(l_motor,LOW);
    analogWrite(L_motor,left*(-1));
  }
  
  if(right>=0){
    digitalWrite(r_motor,HIGH);
    analogWrite(R_motor,right);
  }
  else{
    digitalWrite(r_motor,LOW);
    analogWrite(R_motor,right*(-1));
  }
}
void letejimas(int nuo, int iki, int laikas,bool puse){
  for(int i=nuo; i>=iki; i--){
    if(puse ==1){motor(i,i);}
    else{motor(-i,-i);}
    delay(laikas);
  }
}
void greitejimas(int nuo, int iki, int laikas, bool puse){
   for(int i=nuo; i<=iki; i++){
    if(puse ==1){motor(i,i);}
    else{motor(-i,-i);}
    delay(laikas);
  }
}
int taskas, atsisuke;
void linijos_palaikymas(int norimas_greitis,int palaikymo_taskas){
 if(palaikymo_taskas<320 && palaikymo_taskas>40){
   error = palaikymo_taskas - laipsniai;
 }
 else{
   /*if(palaikymo_taskas>=300){ taskas = map(palaikymo_taskas,180,360,0,180);}
   else if(palaikymo_taskas<=100) { taskas = map(palaikymo_taskas,0, 180,180,360);}
  
   if(laipsniai>=180){atsisuke = map(laipsniai, 180, 360,180,0);} 
   else if(laipsniai<180){atsisuke = laipsniai;}
  
   if(laipsniai < palaikymo_taskas){
     error = (taskas - atsisuke) * (-1); 
   }
   else { error = taskas - atsisuke; }*/
   error = 0;
 }
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  V = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
  
  if(V>255){V=255;}
  else if(V<-255){V=-255;}
  
  motor(norimas_greitis+V, norimas_greitis-V);
  Serial.print(laipsniai);
  Serial.print("      ");
  Serial.println(V);
}

void pasisukimas(int greitisx, long laikasx, bool puse, long greitejimo_laikas){
  for(int i=0; i<=greitisx; i++){
      if(puse == 0){ motor(-i,i);}
      else{ motor(i,-i);}
    delay(greitejimo_laikas);
  }
  if(puse == 0){ motor(-greitisx,greitisx);}
  else{ motor(greitisx,-greitisx);}
  
  delay(laikasx);
  
   for(int i=greitisx; i>=0; i--){
      if(puse == 0){ motor(-i,i);}
      else{ motor(i,-i);}
    delay(greitejimo_laikas);
  }
  motor(0,0);
  delay(10);
}


