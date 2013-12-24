//SETTINGS

//We can't get any more 'on' than 'on'.
#define MAX_BRIGHTNESS 255

// The pin the IR receiver is connected to
#define IR_PIN 11

// the pin that the LED(s) are attached to
#define LED_PIN 6 

// How long in ms a light should last
#define LIGHT_DECAY 125.0

#define NUM_LEDS 3

//Classes

class Colour {
  public: 
    float r,g,b;
    void zero() {r = 0;g = 0;b = 0;}
    void set(uint8_t red, uint8_t green, uint8_t blue);
    void decay(Colour initial, unsigned long t0, unsigned long t);
    uint8_t decay_component(uint8_t current, float initial, unsigned long t0, unsigned long t);
    Colour();
//    void decay(unsigned long t);
//    void set(uint8_t red, uint8_t green, uint8_t blue);
} ;

class Led {
  uint8_t id;
  Adafruit_NeoPixel *strip;
  public:
    Led(Adafruit_NeoPixel *xstrip, int xid);
    Led();
    
    Colour current;
    Colour initial;
    unsigned long t0;
    void reset();
    int get_id() {return id;}
    
    void change(uint8_t r, uint8_t g, uint8_t b); //Component colour
    void draw();
    void decay(unsigned long t);
    void save_colour(uint8_t r, uint8_t g, uint8_t b);
};

