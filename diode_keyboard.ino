int dioda[3];
int przycisk[4];
int stanDiody[3];

int wcisnietyPrzycisk;

void setup() {
  // put your setup code here, to run once:
  //int i;
  for(int i=0; i<3; i=i+1){//konfiguracja diod
    dioda[i] = i+2;
    stanDiody[i] = 0;
    pinMode(dioda[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(przycisk[0]) == HIGH and digitalRead(przycisk[1]) == HIGH and digitalRead(przycisk[2]) == HIGH and digitalRead(przycisk[3]) == HIGH){}//czekaj na wcisniecie ktoregos z przyciskow

  if(digitalRead(przycisk[0]) == LOW){
    delay(300);
    wcisnietyPrzycisk = 0;
  }
  else if(digitalRead(przycisk[1]) == LOW){
    delay(300);
    wcisnietyPrzycisk = 1;
  }
  else if(digitalRead(przycisk[2]) == LOW){
    delay(300);
    wcisnietyPrzycisk = 2;
  }
  else{
    delay(300);
    wcisnietyPrzycisk = 3;
  }

  if(wcisnietyPrzycisk == 3){
    for(int i=0; i<3; i++){
      digitalWrite(dioda[i],LOW);
      stanDiody[i] = 0;
    }
  }
  else{
    if(stanDiody[wcisnietyPrzycisk] == 0){
      digitalWrite(dioda[wcisnietyPrzycisk],HIGH);
      stanDiody[wcisnietyPrzycisk] = 1;
    }
    else{
      digitalWrite(dioda[wcisnietyPrzycisk],LOW);
      stanDiody[wcisnietyPrzycisk] = 0;
    }
  }
}
