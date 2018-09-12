int motor_p = 7;
int motor_n = 8;
int df = 0;
int b;
int bt = 500;
unsigned long bc = 900;
bool bf = false;
float timec = 0.3;
bool b2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(motor_p,OUTPUT);
pinMode(motor_n, OUTPUT);
}
void StartMotor(int dir)
{
  if (dir ==1)
  {
    digitalWrite(motor_p,HIGH);
    digitalWrite(motor_n,HIGH);
  }
}
void StopMotor()
{
  digitalWrite(motor_p,LOW);
  digitalWrite(motor_n,LOW);
}
void SendPourSignal()
{
  digitalWrite(motor_p,LOW);
  digitalWrite(motor_n,HIGH);
}
void SendPassSignal()
{
  digitalWrite(motor_p,HIGH);
  digitalWrite(motor_n,LOW);
}
void readSens()
{
  
  b = analogRead(3);
  if (b<bt)
  {
    b2 = 0;
  }
  else
    b2 = 1;

}
void process()
{

  unsigned long bti,ti;
  bti=0;
  //readsensors
  StartMotor(1);
  readSens();
  //check if intersection

  if(b2==0)
  {
    ti = millis();
    df = 1;
    while(b2!=1)
    {
      readSens();
      if(b2!=0 && !bf)
      {
        bf = true;
        bti = millis()-ti;
        Serial.println(bti);
      }
    }
    StopMotor();
  }
  //check for end of all intersections with length count
  //decide
  if(bti>=bc)
  {
    Serial.println(bti);
    SendPourSignal();
  }
  else
  {
    SendPassSignal();
  }
}
void loop() {
  bt = 500;
  bc = 900;
  bf = false;
  timec = 0.3;
  process();
  if(df==1)
  {
    //Wait cycle codes
    while(1);
  }
}



