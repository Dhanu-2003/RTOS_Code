#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"



#define START_BUTTON_PIN 12
#define STOP_BUTTON_PIN 13
#define RESET_BUTTON_PIN 14



volatile bool running = false;
volatile uint32_t elapsed_seconds = 0;



TimerHandle_t stopwatchTimer;



// Reads button state (simple debounce)
bool isButtonPressed(int pin) {
  static uint32_t lastPressTime[40] = {0};
  bool state = !digitalRead(pin);
  if (state && (millis() - lastPressTime[pin] > 200)) {
    lastPressTime[pin] = millis();
    return true;
  }
  return false;
}



// Timer callback (called every 1 second if running)
void timerCallback(TimerHandle_t xTimer) {
  if (running) {
    elapsed_seconds++;
  }
}



// Task: Reads button inputs
void ButtonTask(void *param) {
  while (1) {
    if (isButtonPressed(START_BUTTON_PIN)) {
      running = true;
    } else if (isButtonPressed(STOP_BUTTON_PIN)) {
      running = false;
    } else if (isButtonPressed(RESET_BUTTON_PIN)) {
      running = false;
      elapsed_seconds = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}



// Task: Displays stopwatch time
void DisplayTask(void *param) {
  while (1) {
    Serial.printf("Elapsed Time: %02d:%02d:%02d\r\n", elapsed_seconds / 3600, (elapsed_seconds / 60) % 60, elapsed_seconds % 60);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}



void setup() {
  Serial.begin(115200);



  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);



  // Create timer with 1-second interval
  stopwatchTimer = xTimerCreate("Stopwatch Timer", pdMS_TO_TICKS(1000), pdTRUE, NULL, timerCallback);
  if (stopwatchTimer != NULL) {
    xTimerStart(stopwatchTimer, 0);
  }



  // Create tasks
  xTaskCreate(ButtonTask, "Button Task", 2048, NULL, 1, NULL);
  xTaskCreate(DisplayTask, "Display Task", 2048, NULL, 1, NULL);
}



void loop() {
  // Nothing here. All handled by FreeRTOS tasks.
}
 



Bro this is stop watch code bro