const int chanA = 5;
const int chanB = 6;
unsigned char stateChannelA;
unsigned char stateChannelB;
unsigned char prevStateChannelA = 0;
int prevValue;
int value;
int imp;
int impAnt;
const int timeThreshold = 5;
unsigned long currentTime;
unsigned long loopTime;
int lectura();

void setup() 
{
  Serial.begin(9600);
  pinMode(chanA, INPUT);
  pinMode(chanB, INPUT);
  value = 0;
  prevValue = 0;
  imp = 0;
  impAnt = 0;
}

void loop() 
{
 imp = lectura();
 if (impAnt != imp){
 Serial.println(imp);
 imp = impAnt;}
}

int lectura()
{
  currentTime = millis();
  if (currentTime >= (loopTime + timeThreshold))
  {
    stateChannelA = digitalRead(chanA);
    stateChannelB = digitalRead(chanB);
    delayMicroseconds(10);
        
    if (stateChannelA != prevStateChannelA)
    {
      if (stateChannelA) {if (stateChannelB) value++;}
      if (!stateChannelA){if (stateChannelB) value--;}
    }
    prevStateChannelA = stateChannelA;
    
    if (prevValue != value)
    {
      prevValue = value;
      return (value);
    }
    loopTime = currentTime;
  }
}


