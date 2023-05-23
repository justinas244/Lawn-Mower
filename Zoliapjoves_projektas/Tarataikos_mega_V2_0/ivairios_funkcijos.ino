float keitiklis(float x, float in_min, float in_max, float out_min, float out_max)
{
return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void pypsejimas(long ijungimo,long isjungimo,int kartai){
  for(int i=0; i<kartai; i++){
   digitalWrite(buzeris, HIGH);
   delay(ijungimo);
   digitalWrite(buzeris,LOW);
   delay(isjungimo);
  }
}
