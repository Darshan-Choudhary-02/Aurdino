#define pinServo1 3
#define pinServo2 4
#define pinServo3 5
#define pinTast1 8
#define pinTast2 9
#define pinTast3 10
#define pinTast4 11
uint32_t curTime=0;
uint32_t temTime=0;
uint32_t S1Time=10000;
uint32_t S2Time=S1Time-8000;
uint32_t S3Time=S1Time-4000;
bool Tast4Enabled=true;
bool Tast4State=false;

void setup()
{
  pinMode(pinServo1, OUTPUT);
  pinMode(pinServo2, OUTPUT);
  pinMode(pinServo3, OUTPUT);
//Lampentest
  digitalWrite(pinServo1, HIGH);
  digitalWrite(pinServo2, HIGH);
  digitalWrite(pinServo3, HIGH);
  delay(750); // Wait for 750 millisecond(s)
  digitalWrite(pinServo1, LOW);
  digitalWrite(pinServo2, LOW);
  digitalWrite(pinServo3, LOW);
}
//Die ersten 3 Tasten als Schalter zum gleichzeitig betaetigen
void loop()
{
  curTime=millis(); //Aktuelle Zeit merken
  if(curTime<temTime)
  {
    temTime=0; //Wenn die 32bit Variable Millis() überläuft
               //startet sie neu bei 0 nach ~49,5 Tagen 
  }
  if(Tast4Enabled) //Taste 4 abfragen 1x bis zum Ablaufende
  {
    Tast4State=digitalRead(pinTast4); //Tastenzustand 4
	temTime=curTime; //Vergleichszeit setzen
  }
  if(digitalRead(pinTast1)||digitalRead(pinTast2)||digitalRead(pinTast3))
  {
    Tast4State=false; //Falls eine andere Taste betaetigt wird 
    Tast4Enabled=true;//bricht der Zeitgesteuerte Ablauf ab
  }
  switch(Tast4State){ //Case spart Zeit gegenüber mehreren IF
  case false:
    digitalWrite(pinServo1, digitalRead(pinTast1));
    digitalWrite(pinServo2, digitalRead(pinTast2));
    digitalWrite(pinServo3, digitalRead(pinTast3));
  break;
  case true:
    Tast4Enabled=false; //Damit der Taster nur 1x abgefragt wird
    digitalWrite(pinServo1, HIGH);
	if(curTime-temTime>=S2Time) //S2 startet nach Zeitablauf
    {
      digitalWrite(pinServo2, HIGH);
    }
    if(curTime-temTime>=S3Time) //S3 startet nach Zeitablauf
    {
      digitalWrite(pinServo3, HIGH);
    }
	if(curTime-temTime>=S1Time) //alles zurücksetzen nach Zeitablauf
    {
      Tast4Enabled=true;
      digitalWrite(pinServo1, LOW);
      digitalWrite(pinServo2, LOW);
      digitalWrite(pinServo3, LOW);
    }
  break;
  }
  delay(10); // Delay a little bit to improve simulation performance
}