int BG_level = 0;

int AchtergrondLicht = 0;
int LaserActief = 0;
int verschil;


//neopixel

#include <Adafruit_NeoPixel.h>

#define LED_PIN 7
#define LED_COUNT 37
#define BRIGHTNESS 50  // NeoPixel brightness, 0 (min) to 255 (max)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

uint32_t color;

int knipper = 0;
int vertraging = 0;
int verveel_level;

uint32_t ikverveelme = millis();



/*************************************
************   SETUP  ****************
*************************************/


void setup() {
  Serial.begin(9600);


  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();
  strip.setBrightness(BRIGHTNESS);

  color = strip.Color(255, 0, 0);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }

  color = strip.Color(0, 255, 0);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }
  color = strip.Color(0, 0, 255);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }

  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, 0);
    strip.show();
    delay(100);
  }


  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
}


void effects(int effect) {

  /*
    for (int i=0; i<(LED_COUNT*3); i++ ) {

    strip.getPixelColor((i+1) % LED_COUNT);


    }
  */

  color = strip.Color(255, 0, 0);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }

  color = strip.Color(0, 255, 0);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }
  color = strip.Color(0, 0, 255);
  //Serial.println(color);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }

  strip.clear();
  strip.show();
}


/*

int ledwrap(int lednr) {
  if (lednr < 0) return lednr = lednr + LED_COUNT;
  if (lednr >= LED_COUNT) return lednr = lednr - LED_COUNT;

}


/*
void turnled() {

  int color;

  strip.clear();

  //strip.setPixelColor()

}

*/

int LaserDetect() {

  // Meet achtergrondlicht

  int AchtergrondLicht = 0;
  int LaserActief = 0;
  digitalWrite(5, LOW);  //laser uit
  for (int i = 0; i < 10; i++) {
    AchtergrondLicht += analogRead(A7);
    delay(1);
  }
  AchtergrondLicht = AchtergrondLicht / 10;

  // Meet laser

  digitalWrite(5, HIGH);  //laser aan
  for (int i = 0; i < 10; i++) {
    LaserActief += analogRead(A7);
    delay(1);
  }
  LaserActief = LaserActief / 10;

  // verschil

  int verschil = AchtergrondLicht - LaserActief;

  return verschil;
}


int wachteffect(int v_level, int tempo) {

  int return_tempo = tempo;

  switch (v_level) {
      case 1:
        if (tempo > 30) {
          color = strip.Color(255, 0, 0);
          strip.clear();
          for (int j = 0; j < 6; j++) {
            strip.setPixelColor(((knipper + (j * 6)) % 37), color);
          }

          knipper++;
          knipper = knipper % 37;
          strip.show();
          return_tempo=0;
        }
        break;
      case 2:
        if (tempo > 5) {
          strip.clear();
          color = strip.Color(128, 255, 0);
          for (int j = 0; j < 6; j++) {
            strip.setPixelColor(37-((knipper + (j * 6)) % 37), color);
          }

          knipper++;
          knipper = knipper % 37;
          strip.show();
          return_tempo = 0;
        }

        break;

      case 3:
        if (tempo > 5) {
          strip.clear();
          color = strip.Color(0, 255, 0);
          for (int j = 0; j < 6; j++) {
            strip.setPixelColor(((knipper + (j * 12)) % 37), color);
            strip.setPixelColor(((38-knipper + (j * 12)) % 37), strip.Color(0, 0, 255));
          }

          knipper++;
          knipper = knipper % 37;
          strip.show();
          return_tempo = 0;
        }
        break;

      default:
        break;
    }
    return return_tempo;
}


/*************************************
************   loop  ****************
*************************************/

void loop() {

  vertraging++;

  //Serial.println(ikverveelme);
  //delay(100);

  if (millis() > ikverveelme) {
    //Serial.println("zucht");
  
    if (verveel_level < 3) verveel_level++;;
    ikverveelme = millis() + 60000 * 5;  //wachttijd van 5 minuten
    Serial.println(verveel_level);
  }

  vertraging=wachteffect(verveel_level, vertraging);




  if (LaserDetect() < 100) {
    Serial.println("1");
    effects(1);
    ikverveelme = millis() + 60000 * 5; //wachttijd van 5 minuten
    verveel_level = 1;
    delay(200);



    while (LaserDetect() < 100) {
      delay(100);
      color = strip.Color(0, 255, 0);
      for (int i = 10; i < 20; i++) strip.setPixelColor(i, color);
      strip.show();
      delay(100);
      strip.clear();
      strip.show();
    }
  }
}