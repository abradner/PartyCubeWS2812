#include <Adafruit_NeoPixel.h>
#include <MinimalRemote.h>
#include "PartyCube.h"

IRrecv irrecv(IR_PIN);
decode_results results;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel *strip_ptr= &strip;
Led Leds[NUM_LEDS];

const float lightLambda = 1.0/(float)LIGHT_DECAY;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for (int i=0; i<NUM_LEDS;i++) {
    Leds[i] = Led(strip_ptr,i);
  }

  irrecv.enableIRIn(); // Start the receiver
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    Leds[i].change(255,0,0);
  }

  delay(100);

    for(uint16_t i=0; i<strip.numPixels(); i++) {
    Leds[i].change(0,255,0);
  }

}


void decay_leds() {
  unsigned long t=millis();
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    Leds[i].decay(t);
  }
}

void parse_signal(int code) {
  return; //Stub
}

void loop() {
  if (irrecv.decode(&results)) {
    parse_signal(results.value);
    irrecv.resume(); // Receive the next value
  }

  decay_leds();
}


