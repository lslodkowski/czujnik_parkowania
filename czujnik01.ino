#include <LiquidCrystal.h>  //biblioteka do obsługi wyświetlacza LCD 2x16
#define trigPin 8 //pin triggera czujnika ultradźwiękowego
#define echoPin 13  //pin echo czujnika ultradźwiękowego
#define buzzPin 7   //pin buzzera
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //piny, które wykorzystuje wyświetlacz

void setup() {
  lcd.begin(16, 2); //inicjalizacja wyświetlacza
  pinMode(trigPin, OUTPUT); //trigger, jako wyjście
  pinMode(echoPin, INPUT);  //echo, jako wejście
  pinMode(buzzPin, OUTPUT); //buzzer, jako wyjście
}

void loop() {
  long czas, dystans;
  //wykonanie pomiaru
  digitalWrite(trigPin, LOW); //ustawienie stanu niskiego na triggerze
  delayMicroseconds(2); //opóźnienie
  digitalWrite(trigPin, HIGH);  //ustawienie stanu wysokiego na triggerze
  delayMicroseconds(10);  //opóźnienie
  digitalWrite(trigPin, LOW); //ustawienie stanu niskiego na triggerze
  //funkcja mierzy czas trwania impulsu
  czas = pulseIn(echoPin, HIGH);
  //aby uzyskać odległość w cm, należy czas podzielić przez 58 (informacja od producenta)
  dystans = czas / 58;
  //wyświtlanie informacji
  lcd.clear();
  lcd.setCursor(0, 0);  //ustawienie kursora na górny wiersz
  lcd.print("Odleglosc:");
  lcd.setCursor(0, 1);  //ustawienie kursora na dolny wiersz
  lcd.print(dystans);   //wyświetlanie odległości
  lcd.print(" cm");
  //ustawienia buzzera
  //określenie zakresu odległości w "cm"
  if((dystans>1) && (dystans<100)){
    digitalWrite(buzzPin, HIGH);
    delay(dystans*10);
    digitalWrite(buzzPin, LOW);
    delay(dystans*10);
  }
  else
    delay(250);
}
