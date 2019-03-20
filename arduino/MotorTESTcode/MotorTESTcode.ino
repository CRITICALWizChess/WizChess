// David Gingles MOTOR TEST

int STEPX = 9;
int DIRX = 8;
int STEPY = 6;
int DIRY = 7;
int LED = 13;
int var = 0;

void setup() {
  delay(5000);
  // put your setup code here, to run once:
  // initialize outputs and inputs
  pinMode(LED, OUTPUT);
  pinMode(STEPX, OUTPUT);
  pinMode(DIRX, OUTPUT);
  pinMode(STEPY, OUTPUT);
  pinMode(DIRY, OUTPUT);

  digitalWrite(LED, HIGH); // Turns LED on while motor is moving
  delay(1000);
  digitalWrite(LED, LOW);
}

void loop() {
  //digitalWrite(DIRY,LOW);
  digitalWrite(DIRX,HIGH);
  delay(1000);
  //digitalWrite(DIRY,HIGH);
  //digitalWrite(DIRX,HIGH);
  
  for (int i = 0; i <= 1000; i++){
    digitalWrite(STEPX, HIGH);
    //digitalWrite(STEPY, HIGH);
    delay(1);
    digitalWrite(STEPX, LOW);
    //digitalWrite(STEPY, LOW);
    delay(1);
  }

  
  
}
