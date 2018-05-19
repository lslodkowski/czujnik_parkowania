#include <LiquidCrystal.h>  //biblioteka do obsługi wyświetlacza LCD 2x16
#define trigLeftPin 8 //pin triggera lewego czujnika ultradźwiękowego
#define echoLeftPin 13  //pin echa lewego czujnika ultradźwiękowego
#define trigRightPin 10 //pin triggera prawego czujnika ultradźwiękowego
#define echoRightPin 9  //pin echa prawego czujnika ultradźwiękowego
#define buzzPin 7   //pin buzzera
//8 zakresów do wyświetlania "*" z lewej i prawej strony
#define scope1 5
#define scope2 10
#define scope3 15
#define scope4 20
#define scope5 25
#define scope6 30
#define scope7 35
#define scope8 40
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //piny, które wykorzystuje wyświetlacz

void setup() {
  lcd.begin(16, 2); //inicjalizacja wyświetlacza
  pinMode(trigRightPin, OUTPUT); //trigger, jako wyjście
  pinMode(echoRightPin, INPUT);  //echo, jako wejście
  pinMode(trigLeftPin, OUTPUT);  //trigger, jako wyjście
  pinMode(echoLeftPin, INPUT);   //echo, jako wejście
  pinMode(buzzPin, OUTPUT);      //buzzer, jako wyjście
}

void loop() {
  long timeRight, timeLeft, distanceRight, distanceLeft, distance;
  int i;
  char starsLeft[9] = {' ',' ',' ',' ',' ',' ',' ',' ','/0'};
  char starsRight[9] = {' ',' ',' ',' ',' ',' ',' ',' ','/0'};
  
//wykonanie pomiaru prawego czujnika
  digitalWrite(trigRightPin, LOW); //ustawienie stanu niskiego
  delayMicroseconds(2); //opóźnienie
  digitalWrite(trigRightPin, HIGH);  //ustawienie stanu wysokiego
  delayMicroseconds(10);  //opóźnienie
  digitalWrite(trigRightPin, LOW); //ustawienie stanu niskiego
  timeRight = pulseIn(echoRightPin, HIGH);  //pomiar czasu prawego czujnika

//wykonanie pomiaru lewego czujnika
  digitalWrite(trigLeftPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeftPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigLeftPin, LOW);
  timeLeft = pulseIn(echoLeftPin, HIGH); //pomiar czasu lewego czujnika
  
//Aby uzyskać odległość w cm, należy czas podzielić przez 58 (informacja od producenta).
  distanceRight = timeRight / 58;   //odległość od prawego czujnika
  distanceLeft = timeLeft / 58;     //odległość od lewego czujnika

//zapalanie lewej strony segementów - czujnik lewy
  if(distanceLeft <= scope1){
    for(i=0;i<9;i++)
      starsLeft[i]='*';
  }
  else{
    if((distanceLeft>scope1) && (distanceLeft<=scope2))
      for(i=0;i<9;i++){
        if(i<7)
          starsLeft[i]='*';
        else
          starsLeft[i]=' ';
      }
     else{
        if((distanceLeft>scope2) && (distanceLeft<=scope3))
          for(i=0;i<9;i++){
            if(i<6)
              starsLeft[i]='*';
            else
              starsLeft[i]=' ';
          }
        else{
          if((distanceLeft>scope3) && (distanceLeft<=scope4))
            for(i=0;i<9;i++){
              if(i<5)
                starsLeft[i]='*';
              else
                starsLeft[i]=' ';
            }
          else{
            if((distanceLeft>scope4) && (distanceLeft<=scope5))
              for(i=0;i<9;i++){
                if(i<4)
                  starsLeft[i]='*';
                else
                  starsLeft[i]=' ';
              }
             else{
               if((distanceLeft>scope5) && (distanceLeft<=scope6))
                  for(i=0;i<9;i++){
                    if(i<3)
                      starsLeft[i]='*';
                    else
                      starsLeft[i]=' ';
                  }
               else{
                  if((distanceLeft>scope6) && (distanceLeft<=scope7))
                    for(i=0;i<9;i++){
                      if(i<2)
                        starsLeft[i]='*';
                      else
                        starsLeft[i]=' ';
                    }
                  else{
                    if((distanceLeft>scope7) && (distanceLeft<=scope8))
                      for(i=0;i<9;i++){
                        if(i<1)
                          starsLeft[i]='*';
                        else
                          starsLeft[i]=' ';
                      }
                  }
               }
             }
          }
        }
     }
  }

//zapalanie prawej strony segementów - czujnik prawy
  if(distanceRight <= scope1){
    for(i=0;i<9;i++)
      starsRight[i]='*';
  }
  else{
    if((distanceRight>scope1) && (distanceRight<=scope2))
      for(i=0;i<9;i++){
        if(i<1)
          starsRight[i]=' ';
        else
          starsRight[i]='*';
      }
     else{
        if((distanceRight>scope2) && (distanceRight<=scope3))
          for(i=0;i<9;i++){
            if(i<2)
              starsRight[i]=' ';
            else
              starsRight[i]='*';
          }
        else{
          if((distanceRight>scope3) && (distanceRight<=scope4))
            for(i=0;i<9;i++){
              if(i<3)
                starsRight[i]=' ';
              else
                starsRight[i]='*';
            }
          else{
            if((distanceRight>scope4) && (distanceRight<=scope5))
              for(i=0;i<9;i++){
                if(i<4)
                  starsRight[i]=' ';
                else
                  starsRight[i]='*';
              }
             else{
               if((distanceRight>scope5) && (distanceRight<=scope6))
                  for(i=0;i<9;i++){
                    if(i<5)
                      starsRight[i]=' ';
                    else
                      starsRight[i]='*';
                  }
               else{
                  if((distanceRight>scope6) && (distanceRight<=scope7))
                    for(i=0;i<9;i++){
                      if(i<6)
                        starsRight[i]=' ';
                      else
                        starsRight[i]='*';
                    }
                  else{
                    if((distanceRight>scope7) && (distanceRight<=scope8))
                      for(i=0;i<9;i++){
                        if(i<7)
                          starsRight[i]=' ';
                        else
                          starsRight[i]='*';
                      }
                  }
               }
             }
          }
        }
     }
  }

//ustawienie najbliższej odległości z danych dwóch czujników
  if(distanceRight<distanceLeft)
    distance=distanceRight;
  else
    distance=distanceLeft;
  
//wyświetlanie informacji
  lcd.setCursor(0, 0);    //ustawienie kursora na górny wiersz od segmentu 0
  lcd.print(starsLeft);   //zapalanie "*" z lewej strony
  lcd.setCursor(8, 0);    // ustawinie kursora na górny wiersz od segmentu 8
  lcd.print(starsRight);  //zapalanie "*" z prawej strony
  lcd.setCursor(6, 1);    //ustawienie kursora na dolny wiersz od segmentu 6
  if(distance <= scope8){
    lcd.print(distance);    //wyświetlanie najbliższej odległości
    lcd.print(" cm");       //wyświetlanie informacji o jednostce odległości (cm)
  }
  else
    lcd.clear();          //czyszczenie informacji na wyświetlaczu, gdy odległość jest duża
  
//ustawienie buzzera w stan wysoki i niski uzależnione jest od odległości (distance)
//im bliżej przeszkody, tym przełączenie HIGH/LOW odbywa się częściej (delay uzależnione jest od distance)
  if((distance>0) && (distance<=scope8)){
    digitalWrite(buzzPin, HIGH);
    delay(distance*10);
    digitalWrite(buzzPin, LOW);
    delay(distance*10);
  }
  else
    delay(250); //opóźnienie dla całej pętli
}
