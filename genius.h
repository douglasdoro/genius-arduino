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

int state_game;

int color_sequence[100];
const int kColorSequenceSize = sizeof(color_sequence) / sizeof(color_sequence[0]);
int total_colors;

int input_sequence[kColorSequenceSize];
int inputs_count;

enum State {
  BEGIN = 0,
  SHOW_SEQUENCE = 1,
  INPUT_USER = 2,
  FAIL = 3
};
