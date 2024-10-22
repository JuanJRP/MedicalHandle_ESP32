void PLX_DAQ(int BPM, float SpO2, float temperatura_Corporal, float humedad, float temperatura){
  Serial.print("DATA,DATE,TIME,TIMER,"); 
  Serial.print(BPM);
  Serial.print(","); 
  Serial.print(SpO2);
  Serial.print(",");
  Serial.print(temperatura_Corporal);
  Serial.print(",");
  Serial.print(humedad);
  Serial.print(","); 
  Serial.print(temperatura);
  Serial.println("");
}