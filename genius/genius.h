enum class State {
  init,
  blink_sequence, 
  user_input,
  finish  
};

const int kGreenLed = 2;
const int kBlueLed = 3;
const int kYellowLed = 4;
const int kRedLed = 5;

const int kBlueButton = 10;
const int kRedButton = 8;
const int kYellowButton = 9;
const int kGreenButton = 11;

const int kInterval = 800;
const int kHalfInterval = kInterval / 2;
const int kAQuarterOfInterval = kInterval / 4;

const int kAllLeds[] = { kGreenLed, kBlueLed, kYellowLed, kRedLed };
const int KAllLedsSize = sizeof(kAllLeds) / sizeof(kAllLeds[0]);

State state_game;

int color_sequence[100];
const int kColorSequenceSize = sizeof(color_sequence) / sizeof(color_sequence[0]);
int total_colors;

int input_sequence[kColorSequenceSize];
int inputs_count;


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

  state_game = State::init;
  total_colors = 0;
  inputs_count = 0;
}
