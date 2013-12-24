
Colour::Colour() {
  zero();
}

void Colour::set(uint8_t red, uint8_t green, uint8_t blue) {
  r = red;
  g = green;
  b = blue;
}

void Colour::decay(Colour initial, unsigned long t0, unsigned long t) {

  r= decay_component(r, initial.r, t0, t);
  g= decay_component(g, initial.g, t0, t);
  b= decay_component(b, initial.b, t0, t);

 
}

uint8_t Colour::decay_component(uint8_t current, float initial, unsigned long t0, unsigned long t) {
    if (round(current) == 0) { return 0; }  
    float newVal = (exp_decay(initial, lightLambda, t - t0));
    return (uint8_t)newVal;
//  // Update LED and colour object
//  if ((uint_8)newVal != current) {  
//    draw();
//  }

}

Led::Led(Adafruit_NeoPixel *strip, int id) {
  this->id = id;
  this->strip = strip;
}

Led::Led() {
  id = -1;
}

void Led::reset() {
  current.zero();
  initial.zero();
  t0 = 0;
}

void Led::change(uint8_t r, uint8_t g, uint8_t b) {
  current.set(r,g,b); //  Set the colour components...
  initial.set(r,g,b); //  Set the colour components...
  t0 = millis();
  draw();
}

void Led::draw() {
  strip->setPixelColor(id, current.g,current.r,current.b);
  strip->show();
}


void Led::decay(unsigned long t) {
  if (t0 == 0) {return;}  
  current.decay(initial,t0,t);
  draw();
}


