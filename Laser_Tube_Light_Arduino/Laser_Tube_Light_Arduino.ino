// Author: Jordan Tryon - tool., Inc.
// Modified: 5/31/2024
// Project: Laser Tube Light
// Description: Arduino code for controlling a NeoPixel strip lighting fixture. 

// --------------------------------------- PIN DEFINITIONS --------------------------------------- //

// Define NeoPixel strip pin
#define pin_neopixel 2

// Define input pins
#define pin_switch_a 3
#define pin_switch_b 4

// -------------------------------------- PROGRAM VARIABLES -------------------------------------- //

// Button & Switch Inputs
const int debounce_time = 10;

// ----------------------------------- STATE MACHINE VARIABLES ----------------------------------- //

int state_switch_a = 0;
int state_switch_b = 0;

// ------------------------------------- Timers & Timestamps ------------------------------------- //

unsigned long t = 0;
unsigned long t_0 = 0;
unsigned long t_switch_a = 0;
unsigned long t_0_switch_a = 0;
unsigned long t_switch_b = 0;
unsigned long t_0_switch_b = 0;

// ----------------------------------------- SETUP LOOP ------------------------------------------ //

void setup(){
  // Initialize input pins
  pinMode(pin_switch_a, INPUT_PULLUP);
  pinMode(pin_switch_b, INPUT_PULLUP);
  
  // Begin serial communication
  Serial.begin(115200);
}

// ---------------------------------------- PROGRAM LOOP ----------------------------------------- //

void loop(){
  SM_switch_a();
  SM_switch_b();
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
      
      state_switch_b = 0;
    break;
    
    default:
    break;
  }
}

// ------------------------------------------ FUNCTIONS ------------------------------------------ //
