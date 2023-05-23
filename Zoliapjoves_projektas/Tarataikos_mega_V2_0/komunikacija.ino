void gavimas_is_nano(){
  if(Serial2.available()){
     int a = Serial2.read();
     data[u] = a;
     u++;
     Serial.println(a);
     if(u==2){ gauta=1; u=0;}
     
  }
  if(gauta == 1){
    akumas = data[0] + float(data[1])/100;
    Serial.println(akumas);
    delay(1);
    gauta = 0;
  }
}
