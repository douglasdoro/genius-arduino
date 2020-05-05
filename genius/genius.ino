#include "./genius.h" 

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
void setup() {
  randomSeed(analogRead(0));
  ConfigPorts();

  ResetToDefault();
  
  Serial.begin(9600);
}

void loop() {

  if (state_game == State::init) {
 
    BlinkOneAtTime();
    BlinkAll(2);

    state_game = State::blink_sequence;
  }
  else if (state_game == State::blink_sequence) {
    
    AddColorToSequence();
    ColorSequence();
    BlinkAll(1);

    state_game = State::user_input;
  }
  else if (state_game == State::user_input) {
    
    int selected_led = ReadButtons();

    if (selected_led != 0) {
      delay(100);

      input_sequence[inputs_count] = selected_led;
      inputs_count ++;

      if (total_colors == inputs_count) {
        BlinkAll(1);

        state_game = State::blink_sequence;
      }

      if (!IsInTheColorSequence()) {
        state_game = State::finish;
      }
    }
  }
  else if (state_game == State::finish) {
    BlinkAll(5);   
    ResetToDefault();
  }
}
