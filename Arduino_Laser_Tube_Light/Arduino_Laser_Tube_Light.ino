// Author: Jordan Tryon - tool., Inc.
// Modified: 5/31/2024
// Project: Laser Tube Light
// Description: Arduino code for controlling a NeoPixel strip lighting fixture. 

// -------------------------------------- INCLUDE LIBRARIES -------------------------------------- //

#include <Adafruit_NeoPixel.h>

// --------------------------------------- PIN DEFINITIONS --------------------------------------- //

// Define input pins
#define pin_switch_a 2
#define pin_switch_b 3
#define pin_switch_c 4

// Define NeoPixel strip pin
#define pin_neopixel 5

// -------------------------------------- PROGRAM VARIABLES -------------------------------------- //

// Button & Switch Inputs
const int debounce_time = 10;

// NeoPixel
const int num_pixels = 71;
Adafruit_NeoPixel strip(num_pixels, pin_neopixel, NEO_GRB + NEO_KHZ800);

// Control
bool val_a = LOW;
bool val_b = LOW;
bool val_c = LOW;

// ----------------------------------- STATE MACHINE VARIABLES ----------------------------------- //

int state_switch_a = 2;
int state_switch_b = 2;
int state_switch_c = 2;

// ------------------------------------- Timers & Timestamps ------------------------------------- //

unsigned long t = 0;
unsigned long t_0 = 0;
unsigned long t_switch_a = 0;
unsigned long t_0_switch_a = 0;
unsigned long t_switch_b = 0;
unsigned long t_0_switch_b = 0;
unsigned long t_switch_c = 0;
unsigned long t_0_switch_c = 0;

// ----------------------------------------- SETUP LOOP ------------------------------------------ //

void setup(){
  // Wait for initial power-on
  delay(1000);
  
  // Initialize input pins
  pinMode(pin_switch_a, INPUT);
  pinMode(pin_switch_b, INPUT);
  pinMode(pin_switch_c, INPUT);

  // Initialize the NeoPixel object
  strip.begin();
  strip.setBrightness(255);
  strip.clear();
  strip.show();
  
  // Begin serial communication
  Serial.begin(115200);
}

// ---------------------------------------- PROGRAM LOOP ----------------------------------------- //

void loop(){
  // Wait to update the lighting mode, prevents repeatedly calling blocking functions after switches change position
  t_0 = millis();
  t = millis();
  while(t - t_0 <= 250){
    t = millis();
    SM_switch_a();
    SM_switch_b();
    SM_switch_c();
  }

  // Off
  if(val_c == LOW && val_b == LOW && val_a == LOW){
    strip.clear();
    strip.show();
  }

  // On - Cool White
  if(val_c == LOW && val_b == LOW && val_a == HIGH){
    strip_fill(255, 255, 255);
  }

  // On - Warm White
  if(val_c == LOW && val_b == HIGH && val_a == LOW){
    strip_fill(255, 100, 10);
  }

  // On - Wave Bounce
  if(val_c == LOW && val_b == HIGH && val_a == HIGH){
    wave_bounce(255, 100, 10);
  }

  // On - Laser Build
  if(val_c == HIGH && val_b == LOW && val_a == LOW){
    laser_build(255, 100, 10);
  }

  // On - Breathing Cycle
  if(val_c == HIGH && val_b == LOW && val_a == HIGH){
    breathing_cycle();
  }

  // On - Fill Cycle
  if(val_c == HIGH && val_b == HIGH && val_a == LOW){
    fill_cycle();
  }

  // On - Rainbow Slide
  if(val_c == HIGH && val_b == HIGH && val_a == HIGH){
    rainbow_slide();
  }
}

// --------------------------------------- STATE MACHINES ---------------------------------------- //

// State machine to debounce switch a
void SM_switch_a(){
  bool currentVal = digitalRead(pin_switch_a);
  
  switch(state_switch_a){
    case 0: // 0 - Wait for LOW
      if(currentVal == LOW){
        t_0_switch_a = millis();
        state_switch_a = 1;
      }
    break;
    
    case 1: // 1 - Debounce
      t_switch_a = millis();
      if(currentVal == HIGH){ state_switch_a = 0; }
      if(t_switch_a - t_0_switch_a >= debounce_time){ state_switch_a = 2; }
    break;
    
    case 2: // 2 - Trigger LOW
      val_a = LOW;
      state_switch_a = 3;
    break;
    
    case 3: // 3 - Wait for HIGH
      if(currentVal == HIGH){
        t_0_switch_a = millis();
        state_switch_a = 4;
      }
    break;
    
    case 4: // 4 - Debounce
      t_switch_a = millis();
      if(currentVal == LOW){ state_switch_a = 3; }
      if(t_switch_a - t_0_switch_a >= debounce_time){ state_switch_a = 5; }
    break;
    
    case 5: // 5 - Trigger HIGH
      val_a = HIGH;
      state_switch_a = 0;
    break;
    
    default:
    break;
  }
}

// State machine to debounce switch b
void SM_switch_b(){
  bool currentVal = digitalRead(pin_switch_b);
  
  switch(state_switch_b){
    case 0: // 0 - Wait for LOW
      if(currentVal == LOW){
        t_0_switch_b = millis();
        state_switch_b = 1;
      }
    break;
    
    case 1: // 1 - Debounce
      t_switch_b = millis();
      if(currentVal == HIGH){ state_switch_b = 0; }
      if(t_switch_b - t_0_switch_b >= debounce_time){ state_switch_b = 2; }
    break;
    
    case 2: // 2 - Trigger LOW
      val_b = LOW;
      state_switch_b = 3;
    break;
    
    case 3: // 3 - Wait for HIGH
      if(currentVal == HIGH){
        t_0_switch_b = millis();
        state_switch_b = 4;
      }
    break;
    
    case 4: // 4 - Debounce
      t_switch_b = millis();
      if(currentVal == LOW){ state_switch_b = 3; }
      if(t_switch_b - t_0_switch_b >= debounce_time){ state_switch_b = 5; }
    break;
    
    case 5: // 5 - Trigger HIGH
      val_b = HIGH;
      state_switch_b = 0;
    break;
    
    default:
    break;
  }
}

// State machine to debounce switch c
void SM_switch_c(){
  bool currentVal = digitalRead(pin_switch_c);
  
  switch(state_switch_c){
    case 0: // 0 - Wait for LOW
      if(currentVal == LOW){
        t_0_switch_c = millis();
        state_switch_c = 1;
      }
    break;
    
    case 1: // 1 - Debounce
      t_switch_c = millis();
      if(currentVal == HIGH){ state_switch_c = 0; }
      if(t_switch_c - t_0_switch_c >= debounce_time){ state_switch_c = 2; }
    break;
    
    case 2: // 2 - Trigger LOW
      val_c = LOW;
      state_switch_c = 3;
    break;
    
    case 3: // 3 - Wait for HIGH
      if(currentVal == HIGH){
        t_0_switch_c = millis();
        state_switch_c = 4;
      }
    break;
    
    case 4: // 4 - Debounce
      t_switch_c = millis();
      if(currentVal == LOW){ state_switch_c = 3; }
      if(t_switch_c - t_0_switch_c >= debounce_time){ state_switch_c = 5; }
    break;
    
    case 5: // 5 - Trigger HIGH
      val_c = HIGH;
      state_switch_c = 0;
    break;
    
    default:
    break;
  }
}

// ------------------------------------------ FUNCTIONS ------------------------------------------ //

void strip_fill(int r, int g, int b){
  for(int i = 0; i < num_pixels; i++){
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void fill_cycle(){
  fill_cycle(10);
}

void fill_cycle(unsigned long d){
  int r = 255;
  int g = 0;
  int b = 0;

  for(int i = 0; i <= 255; i++){
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
}

void breathing_cycle(){
  breathing_cycle(10);
}

void breathing_cycle(unsigned long d){
  int r = 0;
  int g = 0;
  int b = 0;

  for(int i = 0; i <= 255; i++){
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    r = i;
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    r = i;
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    g = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    g = i;
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    g = i;
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    b = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 0; i <= 255; i++){
    b = i;
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
  for(int i = 255; i >= 0; i--){
    b = i;
    r = i;
    strip_fill(r, g, b);
    delay(d);
  }
}

void block_bounce(int r, int g, int b){
  block_bounce(r, g, b, 10, 30);
}

void block_bounce(int r, int g, int b, int L){
  block_bounce(r, g, b, L, 30);
}

void block_bounce(int r, int g, int b, int L, unsigned long d){
  // Send pixels up the strip
  for(int i = 0; i <= num_pixels - L; i++){
    // Turn on pixels
    for(int j = 0; j < L; j++){
      strip.setPixelColor(i + j, strip.Color(r, g, b));
    }
    // Turn off trailing pixel
    if(i > 0){
      strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(d);
  }

  // Send pixels down the strip
  for(int i = num_pixels - L; i >= 0; i--){
    // Turn on pixels
    for(int j = 0; j < L; j++){
      strip.setPixelColor(i + j, strip.Color(r, g, b));
    }
    // Turn off trailing pixel
    if(i + L < num_pixels){
      strip.setPixelColor(i + L, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(d);
  }
}

void wave_bounce(int r, int g, int b){
  wave_bounce(r, g, b, 15, 30);
}

void wave_bounce(int r, int g, int b, int L){
  wave_bounce(r, g, b, L, 30);
}

void wave_bounce(int r, int g, int b, int L, unsigned long d){
  // Calculate mid point
  int mid = L/2;

  // Send pixels up the strip
  for(int i = -mid; i <= num_pixels - mid - 1; i++){
    // Turn on pixels
    for(int j = 0; j < L; j++){
      // Exp map | y = e^(-(x^2)) | the domain from 0 to 2 looks good
      float x = abs(j-mid)/(float)mid*2.0;
      float y = exp(-pow(x,2));
      int r_map = r*y;
      int g_map = g*y;
      int b_map = b*y;
      strip.setPixelColor(i + j, strip.Color(r_map, g_map, b_map));
    }
    // Turn off trailing pixel
    if(i > 0){
      strip.setPixelColor(i - 1, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(d);
  }

  // Send pixels down the strip
  for(int i = num_pixels - mid - 1; i >= -mid; i--){
    // Turn on pixels
    for(int j = 0; j < L; j++){
      // Exp map | y = e^(-(x^2)) | the domain from 0 to 2 looks good
      float x = abs(j-mid)/(float)mid*2.0;
      float y = exp(-pow(x,2));
      int r_map = r*y;
      int g_map = g*y;
      int b_map = b*y;
      strip.setPixelColor(i + j, strip.Color(r_map, g_map, b_map));
    }
    // Turn off trailing pixel
    if(i + L < num_pixels){
      strip.setPixelColor(i + L, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(d);
  }
}

void laser_build(int r, int g, int b){
  laser_build(r, g, b, 3);
}

void laser_build(int r, int g, int b, unsigned long d){
  // Build the strip
  for(int i = num_pixels; i > 0; i--){
    for(int j = 0; j < i; j++){
      strip.setPixelColor(j, strip.Color(r, g, b));
      if(j > 0){
        strip.setPixelColor(j - 1, strip.Color(0, 0, 0));
      }
      strip.show();
      delay(d);
    }
    delay(d*100);
  }

  // Clear the strip
  for(int i = 0; i < num_pixels; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(d);
  }
  delay(d*100);
}

void rainbow_slide(){
  rainbow_slide(15);
}

void rainbow_slide(unsigned long d){
  uint16_t max_val = 65535;
  uint16_t step_size = 100;
  uint16_t step_count = max_val/step_size;
  
  for(uint16_t i = 0; i <= step_count; i++){
    strip.rainbow(i*step_size, 1);
    strip.show();
    delay(d);
  }
}
