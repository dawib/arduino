String odbior = "";
String liczba = "";
int val = 0;
int trash = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    val = Serial.read();
    Serial.print('\n');
    Serial.print(val);
    if(val>0 and val<200) analogWrite(9,val);
    else if(val>200) analogWrite(9,0);
  }
}
