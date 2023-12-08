#define RED_PIN D1    // Red pin connected to D1
#define GREEN_PIN D2  // Green pin connected to D2
#define BLUE_PIN D3   // Blue pin connected to D3

#define COLOR_DURATION 60000 // Time for each color in milliseconds (1 minute = 60,000 ms)

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Define the colors
  int colors[][3] = {
    {255, 0, 0},     // Red
    {0, 255, 0},     // Green
    {0, 0, 255},     // Blue
    {255, 255, 0},   // Yellow
    {255, 0, 255},   // Magenta
    {0, 255, 255},   // Cyan
    {255, 255, 255}  // White
  };

  // Display each color for one minute
  for (int i = 0; i < 7; i++) {
    analogWrite(RED_PIN, colors[i][0]);
    analogWrite(GREEN_PIN, colors[i][1]);
    analogWrite(BLUE_PIN, colors[i][2]);
    delay(COLOR_DURATION);
  }
}
