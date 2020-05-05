#include "genius.h" 

// ** Buttons ** //

int ReadButtons() {

  int led = 0;

  int green_button = digitalRead(kGreenButton);
  int red_button = digitalRead(kRedButton);
  int yellow_button = digitalRead(kYellowButton);
  int blue_button = digitalRead(kBlueButton);

  if (green_button == 0) {
    led = kGreenLed;

  } else if (red_button == 0) {
    led = kRedLed;

  } else if (yellow_button == 0 ) {
    led = kYellowLed;

  } else if (blue_button == 0) {
    led = kBlueLed;

  }

  Blink(led, kAQuarterOfInterval);

  return led;
}

// ** Leds Control ** //

void BlinkAll(int times) {
  for (int i = 0; i < times; i++) {
    for (int i = 0; i < KAllLedsSize; i++) {
      TurnOnLed(kAllLeds[i], HIGH);
    }

    delay(kAQuarterOfInterval);

    for (int i = 0; i < KAllLedsSize; i++) {
      TurnOnLed(kAllLeds[i], LOW);
    }

    delay(kAQuarterOfInterval);
  }
}

void BlinkOneAtTime() {
  for (int i = 0; i < KAllLedsSize; i++) {
    Blink(kAllLeds[i], kAQuarterOfInterval);
  }
}

void Blink(int led, int interval) {
  TurnOnLed(led, HIGH);
  delay(interval);
  TurnOnLed(led, LOW);
  delay(interval);
}

void TurnOnLed(int led, int turn_on ) {
  digitalWrite(led, turn_on);
}

// ** Setup ** //

void ConfigPorts() {
  pinMode(kGreenLed, OUTPUT);
  pinMode(kBlueLed, OUTPUT);
  pinMode(kYellowLed, OUTPUT);
  pinMode(kRedLed, OUTPUT);

  pinMode(kGreenButton, INPUT_PULLUP);
  pinMode(kRedButton, INPUT_PULLUP);
  pinMode(kYellowButton, INPUT_PULLUP);
  pinMode(kBlueButton, INPUT_PULLUP);

}

int RandomNumber() {
  int rand_number;

  rand_number = random(KAllLedsSize);

  return rand_number;
}

void ResetToDefault() {
  for (int i = 0; i < kColorSequenceSize; i++) {
    color_sequence[i] = -1;
    input_sequence[i] = -1;
  }

  state_game = BEGIN;
  total_colors = 0;
  inputs_count = 0;
}

void setup() {
  randomSeed(analogRead(0));
  ConfigPorts();

  ResetToDefault();
  
  //Serial.begin(9600);

}

// ** BUSSINESS ** //

void AddColorToSequence() {
  if (kColorSequenceSize == total_colors + 1) {
    ResetToDefault();
  }

  color_sequence[total_colors] = kAllLeds[RandomNumber()];
  total_colors++;

  inputs_count = 0;
}

void ColorSequence() {
  for (int i = 0; i < total_colors; i++ ) {
    Blink(color_sequence[i], kInterval);
  }
}

int IsInTheColorSequence() {
  int is_in_the_color_sequence = 1;

  for (int i = 0; i < inputs_count; i++ ) {
    if (color_sequence[i] != input_sequence[i]) {
       is_in_the_color_sequence = 0;
      break;
    }
  }

  return is_in_the_color_sequence;
}

// ** Run ** //

void loop() {

  if (state_game == BEGIN) {
 
    BlinkOneAtTime();
    BlinkAll(2);

    state_game = SHOW_SEQUENCE;
  }
  else if (state_game == SHOW_SEQUENCE) {
    
    AddColorToSequence();
    ColorSequence();
    BlinkAll(1);

    state_game = INPUT_USER;
  }
  else if (state_game == INPUT_USER) {
    
    int selected_led = ReadButtons();

    if (selected_led != 0) {
      delay(100);

      input_sequence[inputs_count] = selected_led;
      inputs_count ++;

      if (total_colors == inputs_count) {
        BlinkAll(1);

        state_game = SHOW_SEQUENCE;
      }

      if (!IsInTheColorSequence()) {
        state_game = FAIL;
      }
    }
  }
  else if (state_game == FAIL) {
    BlinkAll(5);   
    ResetToDefault();
  }
}
