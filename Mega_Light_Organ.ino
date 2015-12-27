int analogPin=0;
int strobePin=2;
int resetPin=3;
int ledred=9;
int ledblue=10;
int ledgreen=11;

double vals[7];
double valAvgs[7];
double valTotals[7];
//long strt = 0;

//long coolDownTime = 120000;
//long onTime = 900000;

int filter=90;
int del = 15;
 
int samplesTaken = 0;
int samplesToAvg = 10;

void setup(){
  Serial.begin(9600);
  
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  
  for (int i = 5; i < 12; i++) {
     pinMode(i, OUTPUT); 
  }
  
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}
  
void loop(){
  //if (millis() - strt > onTime) {
    //delay(coolDownTime);
    //strt = millis();
  //}
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  
  for (int i=0;i<7;i++){
    digitalWrite(strobePin, LOW);
    delay(del);
  
    vals[i]=analogRead(analogPin);
    vals[i]=constrain(vals[i], filter, 1023);
    vals[i] /= 1023.0;

    valTotals[i] += vals[i];
  
    digitalWrite(strobePin, HIGH);
  }
  
  samplesTaken++;
  
  if (samplesTaken > samplesToAvg) {
    for (int i = 0; i < 7; i++) {
      valAvgs[i] = valTotals[i] / samplesToAvg;
      valTotals[i] = 0;  
    }
    
    samplesTaken = 0; 
  }

  for (int i = 0; i < 7; i++) {
    Serial.print(valAvgs[i]);
    Serial.print("\t");
  }
  
  Serial.println();
  digitalWrite(5, (vals[0] + vals[1]) / 2.0 > ((valAvgs[0] + valAvgs[1]) / 2.0) ? LOW:HIGH);
  digitalWrite(6, (vals[0] + vals[1]) / 2.0 > ((valAvgs[0] + valAvgs[1]) / 2.0) ? LOW:HIGH);  
  digitalWrite(7, (vals[0] + vals[1]) / 2.0 > ((valAvgs[0] + valAvgs[1]) / 2.0) ? LOW:HIGH);
  digitalWrite(8, (vals[0] + vals[1]) / 2.0 > ((valAvgs[0] + valAvgs[1]) / 2.0) ? LOW:HIGH);
  digitalWrite(9, vals[2] > valAvgs[2] ? LOW:HIGH);
  digitalWrite(10, vals[4] > valAvgs[4] ? LOW:HIGH);
  digitalWrite(11, (vals[5] + vals[6]) / 2.0 > ((valAvgs[5] + valAvgs[6]) / 2.0) ? LOW:HIGH);

}

