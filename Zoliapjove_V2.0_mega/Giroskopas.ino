
void kampas(){
  mpu6050.update();
  laipsniai =  round(mpu6050.getAngleZ());
  x_kampas  =  round(mpu6050.getAngleX());
  y_kampas  =  round(mpu6050.getAngleY());
  //pasisukimo_kampas = pasisukimo_perskaiciavimas(laipsniai);
}
void giroskopo_ofsetai(){
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void giroskopo_meniu(){
    while(true){
       mygtukai();
        if((Enter + Plius + Minus +Save)!=0){
           busena = 4;
           elementas = 1;
           kursorius = 1;
           pastumimas = 0;
           lcd.clear();
           delay(10);
           break;
        }

        lcd.setCursor(2,1);
        lcd.print("Vis dar kuriama");
    }
}

