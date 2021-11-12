#include<Keypad.h>
#include<Servo.h>

Servo serwo;

//setup klawiatury-----------------------------------
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {17,16,15,14};
byte colPins[COLS] = {13,12,11,10};

Keypad klawiatura = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);
//-----------------------------------------------------

char klucz[4] = {'1','2','3','4'};
char wejscie[4];

char klawisz;
bool zgodny = 1;
bool aktywny = 0;
int it = 0;

unsigned long startCzas = 0;
unsigned long czas = 0;
unsigned long czasDiody = 0;
unsigned long czasLampki = 0;

bool stanDiody = 0;
bool stanLampki = 0;
bool mrugaj = 1;
bool uwaga = 0;

bool otwarte = 1;

bool programowanie = 0;
char krokProgramowania = 0;

int dioda[4] = {5,6,7,8};
int lampka = 2;
int przycisk = 4;

void wylaczDiody(){
  for(int i=0; i<4; i++){
    digitalWrite(dioda[i],LOW);
  }
  digitalWrite(lampka,LOW);
}

void uspij(){
  aktywny = 0;
  mrugaj = 1;
  uwaga = 0;
  it = 0;
  zgodny = 1;
  stanDiody = 0;
  czasDiody = 0;
  startCzas = 0;
  czas = 0;
  wylaczDiody();
  programowanie = 0;
}

void zamknij(){
  wylaczDiody();
  otwarte = 0;
  serwo.write(0);
  for(int i=0; i<3; i++){
    digitalWrite(dioda[i],HIGH);
  }
  //serwo.write(0);
  delay(2000);
  uspij();
}

void otworz(){
  wylaczDiody();
  serwo.write(140);
  for(int i=1;i<4;i++){
    digitalWrite(dioda[i],HIGH);
  }
  
  delay(3000);
  wylaczDiody();
  otwarte = 1;
  uwaga=0;
}

void setup() {//------------------------------------------------------------------------------------------------SETUP
  // put your setup code here, to run once:
  //Serial.begin(9600);
 
  for(int i=0; i<4; i++){
  pinMode(dioda[i],OUTPUT);
  }

  pinMode(przycisk,INPUT_PULLUP);
  pinMode(lampka,OUTPUT);

  serwo.attach(3);
  //serwo.write(0);
}

void loop() {//---------------------------------------------------------------------------------------------------LOOP
  if(aktywny) czas = millis()-startCzas;//sprawdz ile czasu minelo od ostatniej aktywnosci
  
  if(czas>20000) uspij();//uspij sie jesli minelo wiecej niz 20sek

  else if(czas>15000){//ostrzegaj miganiem jesli minelo wiecej niz 15sek
    uwaga = 1;
  }

  if(!otwarte){
    czas = millis() - czasLampki;
    if(czas>100 and stanLampki == 1){
      digitalWrite(lampka, LOW);
      stanLampki = 0;
      czasLampki = millis();
    }
    else if(czas>1900){
      digitalWrite(lampka,HIGH);
      stanLampki = 1;
      czasLampki = millis();
    }
  }

  if(aktywny and uwaga and otwarte){//ostrzeganie dioda gdy drzwi otwarte
    czas = millis() - czasDiody;
    if(czas>100 and stanDiody == 0){
      //digitalWrite(dioda[1],HIGH);
      //digitalWrite(dioda[2],HIGH);
      digitalWrite(dioda[3],HIGH);
      stanDiody = 1;
      czasDiody=millis();
    }
    else if(czas>100){
      //digitalWrite(dioda[1],LOW);
      //digitalWrite(dioda[2],LOW);
      digitalWrite(dioda[3],LOW);
      stanDiody = 0;
      czasDiody=millis();
    }
  }
  else if(aktywny and uwaga and !otwarte){//ostrzeganie dioda gdy drzwi zamkniete
    czas = millis() - czasDiody;
    if(czas>100 and stanDiody == 0){
      //digitalWrite(dioda[1],HIGH);
      //digitalWrite(dioda[2],HIGH);
      digitalWrite(dioda[0],HIGH);
      stanDiody = 1;
      czasDiody=millis();
    }
    else if(czas>100){
      //digitalWrite(dioda[1],LOW);
      //digitalWrite(dioda[2],LOW);
      digitalWrite(dioda[0],LOW);
      stanDiody = 0;
      czasDiody=millis();
    }
  }
  else if(aktywny and mrugaj and otwarte){//miganie dioda w gotowosci gdy drzwi otwarte
    czas = millis() - czasDiody;
    if(czas>500 and stanDiody == 0){
      //digitalWrite(dioda[1],HIGH);
      //digitalWrite(dioda[2],HIGH);
      digitalWrite(dioda[3],HIGH);
      stanDiody = 1;
      czasDiody=millis();
    }
    else if(czas>500){
      //digitalWrite(dioda[1],LOW);
      //digitalWrite(dioda[2],LOW);
      digitalWrite(dioda[3],LOW);
      stanDiody = 0;
      czasDiody=millis();
    }
  }
  else if(aktywny and mrugaj and !otwarte){//miganie dioda w gotowosci gdy drzwi zamkniete
    czas = millis() - czasDiody;
    if(czas>500 and stanDiody == 0){
      //digitalWrite(dioda[1],HIGH);
      //digitalWrite(dioda[2],HIGH);
      digitalWrite(dioda[0],HIGH);
      stanDiody = 1;
      czasDiody=millis();
    }
    else if(czas>500){
      //digitalWrite(dioda[1],LOW);
      //digitalWrite(dioda[2],LOW);
      digitalWrite(dioda[0],LOW);
      stanDiody = 0;
      czasDiody=millis();
    }
  }//-----------------------------------------------------------------------------------------------------------------

  if(digitalRead(przycisk) == LOW){
    delay(500);
    startCzas = millis();
    if(otwarte) zamknij();
    else otworz();
  }
  
  klawisz = klawiatura.getKey();

  if(klawisz){
    startCzas = millis();

    if(aktywny){
      if(otwarte){
        if(klawisz == '#') zamknij();
        else if(klawisz=='A') uspij();
        else if(klawisz == 'D'){
          krokProgramowania = 1;
          it = 0;
          stanDiody = 0;
          mrugaj = 1;
          wylaczDiody();
          while(krokProgramowania == 1){
            czas = millis()-czasDiody;
            if(czas>500 and stanDiody == 0 and mrugaj){
              digitalWrite(dioda[1],HIGH);
              digitalWrite(dioda[2],HIGH);
              stanDiody = 1;
              czasDiody = millis();
            }
            else if(czas>500 and mrugaj){
              digitalWrite(dioda[1],LOW);
              digitalWrite(dioda[2],LOW);
              stanDiody = 0;
              czasDiody = millis();
            }

            klawisz = klawiatura.getKey();

            if(klawisz){
              if(mrugaj) wylaczDiody();
              mrugaj = 0;
              if(klawisz == '*'){
                krokProgramowania = 0;
                wylaczDiody();
                mrugaj = 1;
              }
              else{
                wejscie[it] = klawisz;
                digitalWrite(dioda[it],HIGH);
                it++;
              }

              if(it == 4){
                delay(300);
                zgodny = 1;
                for(int i=0; i<4;i++){
                  if(wejscie[i]!=klucz[i]) zgodny = 0;
                }

                if(zgodny) krokProgramowania = 2;
                else krokProgramowania = 0;
              }
            }        
          }
          it = 0;
          stanDiody = 0;
          mrugaj = 1;
          wylaczDiody();

          while(krokProgramowania == 2){
            czas = millis()-czasDiody;
            if(czas>500 and stanDiody == 0 and mrugaj){
              for(int i=0; i<4; i++){
                digitalWrite(dioda[i],HIGH);
              }
              stanDiody = 1;
              czasDiody = millis();
            }
            else if(czas>500 and mrugaj){
              for(int i=0; i<4; i++){
                digitalWrite(dioda[i],LOW);
              }
              stanDiody = 0;
              czasDiody = millis();
            }

            klawisz = klawiatura.getKey();

            if(klawisz){
              if(mrugaj) wylaczDiody();
              mrugaj = 0;

              if(klawisz == '*'){
                krokProgramowania = 0;
                mrugaj = 1;
                wylaczDiody();
              }
              else{
                klucz[it]=klawisz;
                digitalWrite(dioda[it],HIGH);
                it++;
              }
            }

            if(it == 4){
              delay(300);
              wylaczDiody();
              mrugaj = 1;
              krokProgramowania = 0;
              it = 0;
            }
          }

          startCzas = millis();
        }
        else{
          wylaczDiody();
          for(int i=1;i<4;i++){
            digitalWrite(dioda[i],HIGH);
          }
          delay(2000);
          wylaczDiody();
        }
      }
      else if(!otwarte){
        if(klawisz=='*'){
          wylaczDiody();
          mrugaj = 1;
          uwaga = 0;
          it = 0;
        }
        else{
          if(uwaga) digitalWrite(dioda[0],LOW);
          if(mrugaj) digitalWrite(dioda[3],LOW);
          mrugaj = 0;
          uwaga = 0;

          wejscie[it] = klawisz;
          digitalWrite(dioda[it],HIGH);
          it++;
        }
      }
    }
    else {aktywny=1; czas=millis();}
    
  }

  if(it == 4){
    delay(500);
    wylaczDiody();
    it = 0;
    zgodny = 1;
    for(int i=0; i<4; i++){
      if(wejscie[i]!=klucz[i]) zgodny = 0;
    }

    if(zgodny) otworz();
    else{
      for(int i=0;i<3;i++){
        digitalWrite(dioda[i],HIGH);
      }
      delay(2000);
      wylaczDiody();
    }

    mrugaj = 1;
  }
}
