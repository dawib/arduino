int zielonaDioda = 2;
int czerwonaDioda = 7;
int wejscie[6];
int liczba;
int iterator=0;
int haslo[6]={4,2,3,1,4,1};
int dlugosc = 4;
int zgodnosc;

int przycisk[4];
int wcisnietyPrzycisk;

void setup() {
  // put your setup code here, to run once:
  pinMode(zielonaDioda,OUTPUT);
  pinMode(czerwonaDioda,OUTPUT);

  for(int i=0; i<4; i++){
    przycisk[i] = i+8;
    pinMode(przycisk[i],INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(przycisk[0])==HIGH and digitalRead(przycisk[1])==HIGH and digitalRead(przycisk[2])==HIGH and digitalRead(przycisk[3])==HIGH){}//czekaj na wcisniecie przycisku
  if(digitalRead(przycisk[0])==LOW) {delay(300); wcisnietyPrzycisk=0;}
  else if(digitalRead(przycisk[1])==LOW) {delay(300); wcisnietyPrzycisk=1;}
  else if(digitalRead(przycisk[2])==LOW) {delay(300); wcisnietyPrzycisk=2;}
  else {delay(300); wcisnietyPrzycisk=3;}

  wejscie[iterator]=wcisnietyPrzycisk+1;
  iterator++;

  if(iterator==dlugosc){
    iterator=0;

    zgodnosc=1;
    for(int i=0; i<dlugosc; i++){
      if(haslo[i]!=wejscie[i]) zgodnosc=0;
    }

    if(zgodnosc == 1) { digitalWrite(zielonaDioda,HIGH); delay(3000); digitalWrite(zielonaDioda,LOW);}
    else {digitalWrite(czerwonaDioda,HIGH); delay(3000); digitalWrite(czerwonaDioda,LOW);}
  }
}
