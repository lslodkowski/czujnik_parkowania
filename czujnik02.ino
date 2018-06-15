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
//sygnalizacja włączenia czujnika
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
}

void loop() {
  long distanceRight, distanceLeft, distance;
  
//wykonanie pomiaru prawego czujnika
  distanceRight = getDistance(trigRightPin,echoRightPin);
//wykonanie pomiaru lewego czujnika
  distanceLeft = getDistance(trigLeftPin,echoLeftPin);

//ustawienie najbliższej odległości z danych dwóch czujników
  if(distanceRight<distanceLeft)
    distance=distanceRight;
  else
    distance=distanceLeft;
  
//wyświetlanie informacji
  lcd.clear();
  lcd.setCursor(0, 0);    //ustawienie kursora na górny wiersz od segmentu 0
  
//zapalanie lewej strony segementów - czujnik lewy
  if(distanceLeft <= scope1){
    lcd.print("********");
  }
  else{
    if((distanceLeft>scope1) && (distanceLeft<=scope2))
      lcd.print("******* ");
     else{
        if((distanceLeft>scope2) && (distanceLeft<=scope3))
          lcd.print("******  ");
        else{
          if((distanceLeft>scope3) && (distanceLeft<=scope4))
            lcd.print("*****   ");
          else{
            if((distanceLeft>scope4) && (distanceLeft<=scope5))
              lcd.print("****    ");
             else{
               if((distanceLeft>scope5) && (distanceLeft<=scope6))
                  lcd.print("***     ");
               else{
                  if((distanceLeft>scope6) && (distanceLeft<=scope7))
                    lcd.print("**      ");
                  else{
                    if((distanceLeft>scope7) && (distanceLeft<=scope8))
                      lcd.print("*       ");
                    else
                      lcd.print("        ");
                  }
               }
             }
          }
        }
     }
  }

  lcd.setCursor(8, 0);    // ustawinie kursora na górny wiersz od segmentu 8

//zapalanie prawej strony segementów - czujnik prawy
  if(distanceRight <= scope1){
    lcd.print("********");
  }
  else{
    if((distanceRight>scope1) && (distanceRight<=scope2))
      lcd.print(" *******");
     else{
        if((distanceRight>scope2) && (distanceRight<=scope3))
          lcd.print("  ******");
        else{
          if((distanceRight>scope3) && (distanceRight<=scope4))
            lcd.print("   *****");
          else{
            if((distanceRight>scope4) && (distanceRight<=scope5))
              lcd.print("    ****");
             else{
               if((distanceRight>scope5) && (distanceRight<=scope6))
                  lcd.print("     ***");
               else{
                  if((distanceRight>scope6) && (distanceRight<=scope7))
                    lcd.print("      **");
                  else{
                    if((distanceRight>scope7) && (distanceRight<=scope8))
                      lcd.print("       *");
                    else
                      lcd.print("        ");
                  }
               }
             }
          }
        }
     }
  }

  lcd.setCursor(6, 1);    //ustawienie kursora na dolny wiersz od segmentu 6
  if(distance <= scope8){
    lcd.print(distance);    //wyświetlanie najbliższej odległości
    lcd.print(" cm ");       //wyświetlanie informacji o jednostce odległości (cm)
  }
  else
    lcd.print(" OK      ");  //czujnik działa, a odległość jest bezpieczna
  
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

//funkcja zwraca odegłość od czujnika w centymetrach
long getDistance (int trigger, int echo){
  long timeTE;
  digitalWrite(trigger, LOW); //ustawienie stanu niskiego
  delayMicroseconds(2); //opóźnienie
  digitalWrite(trigger, HIGH);  //ustawienie stanu wysokiego
  delayMicroseconds(10);  //opóźnienie
  digitalWrite(trigger, LOW); //ustawienie stanu niskiego
  timeTE = pulseIn(echo, HIGH);  //pomiar czasu czujnika
  //Aby uzyskać odległość w cm, należy czas podzielić przez 58 (informacja od producenta).
  return timeTE / 58;
}
