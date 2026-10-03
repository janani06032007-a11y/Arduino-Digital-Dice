#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;
const int buzzerPin = 8;

int diceNumber = 0;
int rollCount = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  randomSeed(analogRead(A0));

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10, 15);
  display.println("DIGITAL");
  display.setCursor(25, 40);
  display.println("DICE!");
  display.display();

  delay(2000);
  showMessage();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50);

    if (digitalRead(buttonPin) == LOW) {
      rollDice();

      while (digitalRead(buttonPin) == LOW) {
        delay(10);
      }
    }
  }
}

void showMessage() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5, 10);
  display.println("PRESS");
  display.setCursor(5, 35);
  display.println("BUTTON!");
  display.display();
}

void rollDice() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(25, 5);
  display.println("ROLLING");

  for (int i = 0; i < 12; i++) {
    int tempNumber = random(1, 7);

    display.fillRect(45, 28, 40, 36, BLACK);
    display.setTextSize(4);
    display.setCursor(50, 28);
    display.print(tempNumber);
    display.display();

    tone(buzzerPin, 500 + tempNumber * 100, 50);
    delay(60 + (i * 25));
  }

  diceNumber = random(1, 7);
  rollCount++;

  tone(buzzerPin, 1200, 150);
  showDice();
}

void showDice() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(25, 2);
  display.println("DICE");

  display.setTextSize(4);
  display.setCursor(50, 22);
  display.print(diceNumber);

  display.setTextSize(1);
  display.setCursor(5, 55);
  display.print("TOTAL ROLLS: ");
  display.print(rollCount);

  display.display();
}
