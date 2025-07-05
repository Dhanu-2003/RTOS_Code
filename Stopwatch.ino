#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WebServer.h>



// Create a web server on port 80
WebServer server(80);



const char* ssid = "ssid";       
const char* password = "password";

String receivedData = "None";
String val = "None";


// HTML Page (inline for simplicity)
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Multi Timer</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f2f5f9;
      padding: 20px;
      margin: 0;
    }

    h2 {
      text-align: center;
      color: #333;
      margin-top: 20px;
    }

    .timer-section {
      background: #fff;
      border-radius: 15px;
      box-shadow: 0 5px 15px rgba(0,0,0,0.1);
      padding: 20px;
      margin-bottom: 30px;
    }

    .timer-label {
      text-align: center;
      font-size: 1.1rem;
      color: #555;
      margin-bottom: 15px;
    }

    .time-cards {
      display: flex;
      justify-content: space-around;
      margin-bottom: 15px;
    }

    .card {
      background-color: #e8eef5;
      padding: 15px;
      border-radius: 10px;
      flex: 1;
      margin: 0 5px;
      text-align: center;
    }

    .card-title {
      font-size: 0.9rem;
      color: #666;
      margin-bottom: 5px;
    }

    .card-value {
      font-size: 1.8rem;
      font-weight: bold;
      color: #222;
    }

    .btn-group {
      display: flex;
      justify-content: space-around;
    }

    .btn {
      flex: 1;
      margin: 5px;
      padding: 12px;
      font-size: 1rem;
      font-weight: bold;
      border: 1px solid black;
      border-radius: 8px;
      cursor: pointer;
      color: black;
      background-color: white;
    }

    .start { background-color: #28a745; }
    .stop  { background-color: #daa520; }
    .step  { background-color: #dc3545; }

    @media (max-width: 576px) {
      .card-value { font-size: 1.4rem; }
      .btn { font-size: 0.9rem; padding: 10px; }
    }
  </style>
</head>
<body>

  <h2>Multi Timer</h2>

  <!-- Timer 1 -->
  <div class="timer-section" id = "t1">
    <div class="timer-label">Timer 1</div>

    <div class="time-cards">
      <!-- Hour -->
      <div class="card">
        <div class="card-title">Hour</div>
        <button class="btn" onclick="sendCommand('h11')">+</button>
        <div class="card-value" id="h1">00</div>
        <button class="btn" onclick="sendCommand('h10')">−</button>
      </div>

      <!-- Minute -->
      <div class="card">
        <div class="card-title">Minute</div>
        <button class="btn" onclick="sendCommand('m11')">+</button>
        <div class="card-value" id="m1">00</div>
        <button class="btn" onclick="sendCommand('m10')">−</button>
      </div>

      <!-- Second -->
      <div class="card">
        <div class="card-title">Second</div>
        <button class="btn" onclick="sendCommand('s11')">+</button>
        <div class="card-value" id="s1">00</div>
        <button class="btn" onclick="sendCommand('s10')">−</button>
      </div>
    </div>

    <div class="card-mode text-muted" style="font-size: 0.9rem; margin-top: 6px;">
      <span id="mode1">Timer</span>
      <button class="btn" onclick="sendCommand('m1')"> Switch </button>
    </div>

    <div class="btn-group">
      <button class="btn start" onclick="sendCommand('s1')">Start</button>
      <button class="btn stop" onclick="sendCommand('p1')">Pause</button>
      <button class="btn step" onclick="sendCommand('r1')">Reset</button>
    </div>
  </div>

  <!-- Timer 2 -->
  <div class="timer-section"  id = "t2">
    <div class="timer-label">Timer 2</div>
    <div class="time-cards">
      <!-- Hour -->
      <div class="card">
        <div class="card-title">Hour</div>
        <button class="btn" onclick="sendCommand('h21')">+</button>
        <div class="card-value" id="h2">00</div>
        <button class="btn" onclick="sendCommand('h20')">−</button>
      </div>

      <!-- Minute -->
      <div class="card">
        <div class="card-title">Minute</div>
        <button class="btn" onclick="sendCommand('m21')">+</button>
        <div class="card-value" id="m2">00</div>
        <button class="btn" onclick="sendCommand('m20')">−</button>
      </div>

      <!-- Second -->
      <div class="card">
        <div class="card-title">Second</div>
        <button class="btn" onclick="sendCommand('s21')">+</button>
        <div class="card-value" id="s2">00</div>
        <button class="btn" onclick="sendCommand('s20')">−</button>
      </div>
    </div>
    <div class="card-mode text-muted" style="font-size: 0.9rem; margin-top: 6px;">
       <span id="mode2">Timer</span> 
       <button class="btn" onclick="sendCommand('m2')"> Switch </button>
    </div>
    <div class="btn-group">
      <button class="btn start" onclick="sendCommand('s2')">Start</button>
      <button class="btn stop" onclick="sendCommand('p2')">Pause</button>
      <button class="btn step" onclick="sendCommand('r2')">Reset</button>
    </div>
  </div>

  <!-- Timer 3 -->
  <div class="timer-section"  id = "t3">
    <div class="timer-label">Timer 3</div>
    <div class="time-cards">
      <!-- Hour -->
      <div class="card">
        <div class="card-title">Hour</div>
        <button class="btn" onclick="sendCommand('h31')">+</button>
        <div class="card-value" id="h3">00</div>
        <button class="btn" onclick="sendCommand('h30')">−</button>
      </div>

      <!-- Minute -->
      <div class="card">
        <div class="card-title">Minute</div>
        <button class="btn" onclick="sendCommand('m31')">+</button>
        <div class="card-value" id="m3">00</div>
        <button class="btn" onclick="sendCommand('m30')">−</button>
      </div>

      <!-- Second -->
      <div class="card">
        <div class="card-title">Second</div>
        <button class="btn" onclick="sendCommand('s31')">+</button>
        <div class="card-value" id="s3">00</div>
        <button class="btn" onclick="sendCommand('s30')">−</button>
      </div>
    </div>
    <div class="card-mode text-muted" style="font-size: 0.9rem; margin-top: 6px;">
       <span id="mode3">Timer</span> 
       <button class="btn" onclick="sendCommand('m3')"> Switch </button>
    </div>
    <div class="btn-group">
      <button class="btn start" onclick="sendCommand('s3')">Start</button>
      <button class="btn stop" onclick="sendCommand('p3')">Stop</button>
      <button class="btn step" onclick="sendCommand('r3')">Reset</button>
    </div>
  </div>

  <script>
   
    function sendCommand(cmd) {
      fetch("/command?data=" + cmd)
        .then(response => response.text())
        .then(data => console.log("Response:", data))
        .catch(err => console.error("Error:", err));
    }
    function loadTimers() {
      fetch("/getTimers",{ cache: "no-store" })
        .then(res => res.json())
        .then(data => {
          data.forEach(timer => {
         
            document.getElementById(`h${timer.id}`).innerText = timer.hour.toString().padStart(2, '0');
            document.getElementById(`m${timer.id}`).innerText = timer.minute.toString().padStart(2, '0');
            document.getElementById(`s${timer.id}`).innerText = timer.second.toString().padStart(2, '0');
            
            const modeText = timer.mode == 1 ? "Stopwatch" : "Timer";
            document.getElementById(`mode${timer.id}`).innerText = "Mode: " + modeText;

            const color = timer.color == 1 ? "#dc3545" : "white";
            document.getElementById(`t${timer.id}`).style.background = color;

            

          });
        });
    }

    loadTimers();

    window.onload = () => {
      setInterval(loadTimers, 100);
    };
  </script>

</body>
</html>

)rawliteral";


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPins[7] = {0, 15, 4, 5, 13, 12, 14};

volatile bool buttonPressed[7] = {false};

void IRAM_ATTR handleInterrupt0() { buttonPressed[0] = true; }
void IRAM_ATTR handleInterrupt1() { buttonPressed[1] = true; }
void IRAM_ATTR handleInterrupt2() { buttonPressed[2] = true; }
void IRAM_ATTR handleInterrupt3() { buttonPressed[3] = true; }
void IRAM_ATTR handleInterrupt4() { buttonPressed[4] = true; }
void IRAM_ATTR handleInterrupt5() { buttonPressed[5] = true; }
void IRAM_ATTR handleInterrupt6() { buttonPressed[6] = true; }

void (*interruptHandlers[7])() = {
  handleInterrupt0,
  handleInterrupt1,
  handleInterrupt2,
  handleInterrupt3,
  handleInterrupt4,
  handleInterrupt5,
  handleInterrupt6
};

int boxWidth = 40;
int boxHeight = 40;
int gap = 2;
int y = 22;

const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x03, 0x80, 0x07, 0x01, 0xff, 0x00, 0x7c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x07, 0x03, 0xff, 0x80, 0x3c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x07, 0x03, 0xff, 0x80, 0x3e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x0f, 0x03, 0xc3, 0xc0, 0x3e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x0f, 0x03, 0x83, 0xc0, 0x3e, 0x00, 
	0x00, 0x1f, 0x9e, 0x78, 0xf1, 0xff, 0x07, 0xe1, 0xff, 0x06, 0x0e, 0x07, 0x87, 0x80, 0x3e, 0x00, 
	0x00, 0x3f, 0xdf, 0xff, 0xf9, 0xff, 0x8f, 0xf3, 0xff, 0x0e, 0x0e, 0x07, 0x87, 0x80, 0x3e, 0x00, 
	0x00, 0x79, 0xff, 0xff, 0x79, 0xef, 0x9e, 0xf7, 0xcf, 0x1e, 0x1e, 0x07, 0xff, 0x00, 0x3e, 0x00, 
	0x00, 0xf1, 0xde, 0x3c, 0x3b, 0xc3, 0xfc, 0x7f, 0x0e, 0x1e, 0x1e, 0x07, 0xfe, 0x00, 0x7e, 0x00, 
	0x00, 0xf3, 0xde, 0x3c, 0x7b, 0xc3, 0xfc, 0xff, 0x0e, 0x1e, 0x1c, 0x07, 0xfc, 0x00, 0x7e, 0x00, 
	0x00, 0xff, 0x9c, 0x3c, 0x7b, 0xc3, 0xff, 0xee, 0x0e, 0x1e, 0x1c, 0x0f, 0x3c, 0x00, 0xfc, 0x00, 
	0x00, 0xfe, 0x1c, 0x38, 0x73, 0x83, 0xff, 0x8e, 0x1e, 0x1e, 0x1c, 0x0f, 0x1e, 0x00, 0xfc, 0x00, 
	0x00, 0xe0, 0x3c, 0x38, 0x77, 0x87, 0xf8, 0x0e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1e, 0x01, 0xf8, 0x00, 
	0x00, 0xf0, 0xbc, 0x78, 0x77, 0x8f, 0x78, 0x0f, 0x3e, 0x1f, 0x1f, 0xfe, 0x1e, 0x03, 0xf8, 0x00, 
	0x00, 0xff, 0xbc, 0x78, 0xf7, 0xfe, 0x3f, 0xef, 0xfc, 0x1f, 0x0f, 0xfc, 0x0e, 0x07, 0xf0, 0x00, 
	0x00, 0x7f, 0x38, 0x78, 0xf7, 0xfc, 0x1f, 0xc7, 0xfc, 0x1f, 0x07, 0xf8, 0x0f, 0x07, 0xe0, 0x00, 
	0x00, 0x1c, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x03, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x1f, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x3f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x03, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x1f, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x1f, 0xf8, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#define BUZZER_PIN 27

int matrix[4][3][4] = {
  {{0, 4, 40, 14},{boxWidth+gap, 4, 40, 14},{2*(boxWidth+gap), 4, 40, 14}},
  {{0,y+5,40,8},{boxWidth,y+5,40,8},{2*(boxWidth+gap),y+5,40,8}},
  {{0,y+14,40,8},{boxWidth,y+14,40,8},{2*(boxWidth+gap),y+14,40,8}},
  {{0,y+25,40,8},{boxWidth,y+25,40,8},{2*(boxWidth+gap),y+25,40,8}}
};
int cursor[2] = {0,0};
static int temp = 0; 
SemaphoreHandle_t cur;

typedef struct {
  int id;
  int mode;
  int minute;
  int sec;
  int hour;
  int color;

}clock_tim;

volatile int toggle = 0;

int status[] = {0,0,0};
SemaphoreHandle_t status_c;

volatile int last_up = 10;
volatile int curr_pos = 0;

int blink[] = {0,0,0};
SemaphoreHandle_t blink_fn;

int selected = 0;

TaskHandle_t mainHandle;

clock_tim data[3];
SemaphoreHandle_t clock_data;


volatile int isPressed;

String json;
SemaphoreHandle_t j_mut;


volatile int virtual_access = 0;
volatile int perm = 0;
int selectedIndex = 0; // 0 = YES, 1 = NO
SemaphoreHandle_t mobile;

void button(void *param){
  while(1){
    for (int i = 0; i < 7; i++) {
      if(buttonPressed[i]){ // LOW = pressed
        isPressed = buttonPins[i];
        
      }
      else{
        continue;
      }
      
      if(xSemaphoreTake(cur,portMAX_DELAY) && xSemaphoreTake(clock_data,portMAX_DELAY)){
        switch(isPressed){
          case 4:{
            isPressed = 10;
            
            if(perm==1){
              selectedIndex = (selectedIndex+1)%2;
            }
            else if(selected==0){
              cursor[0]+=1;
              cursor[0]%=4;
          
            }
            else{
              if(cursor[0]==0 and cursor[1]==0){
                break;
              }
              else{
                if(cursor[0]==1){
                  if(data[cursor[1]].hour==0){
                    data[cursor[1]].hour=99;
                  }
                  else{
                    data[cursor[1]].hour-=1;
                  }
                }
                else if(cursor[0]==2){
                  if(data[cursor[1]].minute==0){
                    data[cursor[1]].minute=59;
                  }
                  else{
                    data[cursor[1]].minute-=1;
                  }
                }
                else if(cursor[0]==3){
                  if(data[cursor[1]].sec==0){
                    data[cursor[1]].sec=59;
                  }
                  else{
                    data[cursor[1]].sec-=1;
                  }
                }
              }
            }
        
          
            break;
           
          }
          case 12:{
            isPressed = 10;
          
            if(perm==1){
              if(selectedIndex==0){
                selectedIndex=1;
              }
              else{
                selectedIndex=0;
              }
            }
            else if(selected==0){
              if(cursor[0]==0){
                cursor[0]=3;
              }
              else{
                cursor[0]-=1;
              }
              break;
            }
            else{
              if(cursor[0]==0 and cursor[1]==0){
                break;
              }
              else{
                if(cursor[0]==1){
                  if(data[cursor[1]].hour==99){
                    data[cursor[1]].hour=0;
                  }
                  else{
                    data[cursor[1]].hour+=1;
                  }
                }
                else if(cursor[0]==2){
                  if(data[cursor[1]].minute==59){
                    data[cursor[1]].minute=0;
                  }
                  else{
                    data[cursor[1]].minute+=1;
                  }
                }
                else if(cursor[0]==3){
                  if(data[cursor[1]].sec==59){
                    data[cursor[1]].sec=0;
                  }
                  else{
                    data[cursor[1]].sec+=1;
                  }
                }
              }
            }
            
            break;
          }
          case 14:{
            isPressed = 10;
            if(selected==0){
              cursor[1]+=1;
              cursor[1]%=3;
              break;
            }
            else{
              if(cursor[0]==0){
                if(data[cursor[1]].mode==1){
                  data[cursor[1]].mode = 0;
                }
                else{
                  data[cursor[1]].mode = 1;
                }
              }
              break;
            }
          }
          case 13:{
            isPressed = 10;
            if(selected==0){
              if(cursor[1]==0){
                cursor[1]=2;
              }
              else{
                cursor[1]-=1;
              }
              break;
            }
            else{
              if(cursor[0]==0){
                if(data[cursor[1]].mode==1){
                  data[cursor[1]].mode = 0;
                }
                else{
                  data[cursor[1]].mode = 1;
                }
                
              }
              break;
            }
          }
          case 5:{
            isPressed = 10;   
            if(perm==1){
              if(selectedIndex==0){
                virtual_access=1;
              }
              else{
                virtual_access=0;
              }
              perm=0;
            }
            selected = (selected + 1)%2;
            break;
          }
          case 15:{
            isPressed = 10;
            if(xSemaphoreTake(status_c,portMAX_DELAY)){
              status[cursor[1]] = 1;
              cursor[0] = 0;
              xSemaphoreGive(status_c);
            
            }
            selected = 0;
            break;
          }
          case 0:{
            isPressed = 10;
            xSemaphoreGive(cur);
            xSemaphoreGive(clock_data);
            int count = 0;
            while(digitalRead(buttonPins[i]) == LOW && count<=4){
              count+=1;
              vTaskDelay(1000);
            }
            if(xSemaphoreTake(cur,portMAX_DELAY) && xSemaphoreTake(clock_data,portMAX_DELAY)){
              if(xSemaphoreTake(status_c,portMAX_DELAY)){
                status[cursor[1]] = 0;
                cursor[0] = 0;
                xSemaphoreGive(status_c);
              
              }
              if(count>=4){
                data[cursor[1]].hour = 0;
                data[cursor[1]].minute = 0;
                data[cursor[1]].sec = 0;
                data[cursor[1]].mode = 0;
                data[cursor[1]].color = 0;
                if(xSemaphoreTake(blink_fn,portMAX_DELAY)){
                  blink[cursor[1]]=0;
                  toggle = 0;
                  selected = 0;
                  digitalWrite(BUZZER_PIN,LOW);
                  xSemaphoreGive(blink_fn);

                }
              }
            }
            
            
            break;
          }
          default:
          break;
        }
        xSemaphoreGive(cur);
        xSemaphoreGive(clock_data);
      }
      
      vTaskDelay(pdMS_TO_TICKS(200));
      buttonPressed[i]=false;
    }

    last_up=10;
    
  }
}




void timer1(void *param){
  while(1){
    vTaskDelay(pdMS_TO_TICKS(1000));
    json = "[";
    if(xSemaphoreTake(j_mut,portMAX_DELAY) && xSemaphoreTake(clock_data,portMAX_DELAY) && xSemaphoreTake(status_c,portMAX_DELAY)  ){
      for(int i=0;i<3;i++){
        json += "{";
        json += "\"id\":" + String(data[i].id+1) + ",";
        json += "\"mode\":" + String(data[i].mode) + ",";
        json += "\"hour\":" + String(data[i].hour) + ",";
        json += "\"minute\":" + String(data[i].minute) + ",";
        json += "\"second\":" + String(data[i].sec) + ",";
        json += "\"color\":" + String(data[i].color);
        json += "}";
        if (i < 2) json += ","; 
        if(status[i]==1){
          if(data[i].mode==1){
            if(data[i].sec==59){
              if(data[i].minute==59){
                data[i].hour+=1;
                data[i].minute=0;
                data[i].sec = 0;
              }
              else{
                data[i].minute+=1;
                data[i].sec=0;
              }

            }
            else{
              data[i].sec+=1;
            }
          }
          else{
            if(data[i].hour==0 && data[i].minute==0 && data[i].sec==0){
              if(xSemaphoreTake(blink_fn,portMAX_DELAY)){
                blink[i]=1;
                data[i].color = 1;
                xSemaphoreGive(blink_fn);
              }
              
            }
            else{
              if(data[i].sec==0){
                if(data[i].minute==0){
                  data[i].hour-=1;
                  data[i].minute=59;
                  data[i].sec=59;
                }
                else{
                  data[i].minute-=1;
                  data[i].sec=59;
                }

              }
              else{
                data[i].sec-=1;
              }
            }
          }
        }
      }
      json += "]";
      
      xSemaphoreGive(clock_data);
      xSemaphoreGive(status_c);
      xSemaphoreGive(j_mut);
   
    }
    
    last_up = 10;
  }
  
}

void buzzer(void *param){
  while(1){
    if(xSemaphoreTake(blink_fn,portMAX_DELAY)){
      temp = 0;
      for(int i=0;i<3;i++){
        temp+=blink[i];
      }
      if(temp>=1){
        if(toggle==0){
          digitalWrite(BUZZER_PIN,HIGH);
          toggle  =1;
        }
        else{
          digitalWrite(BUZZER_PIN,LOW);
          toggle = 0;
        }
      }
      xSemaphoreGive(blink_fn);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void mainScreen(void *param){
  while(1){
    Serial.println(perm);
    if(perm==1){
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Allow control over phone?");
      display.setCursor(0, 20);

      if (selectedIndex == 0) {
        display.println("> YES");
        display.setCursor(0, 30);
        display.println("  NO");
      } else {
        display.println("  YES");
        display.setCursor(0, 30);
        display.println("> NO");
      }
      display.display();
      
    }
    else if(curr_pos==0 && last_up!=curr_pos && perm==0){
      display.clearDisplay();
      display.setTextSize(1);       // Smallest text
      display.setTextColor(WHITE);

      for (int i = 0; i < 3; i++) {
        int x = i * (boxWidth + gap);
        
        // Draw box
        display .drawRect(x, y, boxWidth, boxHeight, WHITE);
        display.setCursor(x + 2 + 14, 7);
        if(xSemaphoreTake(clock_data,portMAX_DELAY)){
          if(data[i].mode==0){
            display.print("TR"); 
            
            
            
          }
          else{
            display.print("SW");
          }
          xSemaphoreGive(clock_data);
        }
        
        display.setCursor(x + 3, y + 5);
        display.print("Hr");       // First number
        display.setCursor(x+40-3-12, y + 5);
        display.print(data[i].hour);
        display.setCursor(x + 3, y + 14);
        display.print("Min"); // Second number
        display.setCursor(x+40-3-12, y + 14);
        display.print(data[i].minute);
        display.setCursor(x + 3, y+25);
        display.print("Sec"); // Second number
        display.setCursor(x+40-3-12, y+25);
        display.print(data[i].sec);
        
  
      }
      last_up = curr_pos;
      if(xSemaphoreTake(cur,portMAX_DELAY)){
        
        display.fillRect(matrix[cursor[0]][cursor[1]][0], matrix[cursor[0]][cursor[1]][1], matrix[cursor[0]][cursor[1]][2], matrix[cursor[0]][cursor[1]][3], INVERSE);
        xSemaphoreGive(cur);
      }

      if(xSemaphoreTake(blink_fn,portMAX_DELAY)){
        for(int i=0;i<3;i++){
          int x = i * (boxWidth+gap);
          if(blink[i]==1){
            if(toggle==1){
              display .fillRect(x, y, boxWidth, boxHeight, INVERSE);
              display.drawRect(matrix[0][i][0], matrix[0][i][1], matrix[0][i][2], matrix[0][i][3], WHITE);

            }
            else{
              display.drawRect(matrix[0][i][0], matrix[0][i][1], matrix[0][i][2], matrix[0][i][3], BLACK);
            }
          }
        }
        xSemaphoreGive(blink_fn);
      }
      display.display();
    }
    
    
  }
}


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  clock_data = xSemaphoreCreateMutex(); 
  status_c =  xSemaphoreCreateMutex(); 
  cur =  xSemaphoreCreateMutex(); 
  blink_fn = xSemaphoreCreateMutex(); 
  j_mut = xSemaphoreCreateMutex(); 
  mobile = xSemaphoreCreateMutex();
  
  

  
 
  if (xSemaphoreTake(clock_data, portMAX_DELAY)) {
    data[0].id = 0;data[1].id = 1;data[2].id = 2;
    data[0].mode = 0;data[1].mode = 0;data[2].mode = 0;
    data[0].minute = 0;data[1].minute = 0;data[2].minute = 0;
    data[0].sec = 0;data[1].sec = 0;data[2].sec = 0;
    data[0].hour = 0;data[1].hour = 0;data[2].hour = 0;
    xSemaphoreGive(clock_data);
  }
  
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), interruptHandlers[i], FALLING);  // or RISING/CHANGE
  }

  pinMode(BUZZER_PIN,OUTPUT);

  

  
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Web Handlers
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", MAIN_page);
  });

  server.on("/command", HTTP_GET, []() {
    if (server.hasArg("data")) {
      receivedData = server.arg("data");
     
      if(virtual_access==0){
        perm = 1;
        last_up=10;
      }
      else{
        if(xSemaphoreTake(status_c,portMAX_DELAY)){
          int tempdata = (receivedData[1] - '0') - 1;;
          char first = receivedData[0];
          Serial.println(first);
          Serial.println(tempdata);
          if(receivedData.length()==3){
            if(xSemaphoreTake(clock_data,portMAX_DELAY)){
              if(first=='h'){
                if(receivedData[2]=='0'){
                  data[tempdata].hour -= 1;
                }
                else{
                  data[tempdata].hour += 1;
                }
              }
              else if(first=='m'){
                if(receivedData[2]=='0'){
                  data[tempdata].minute -= 1;
                }
                else{
                  data[tempdata].minute += 1;
                }
              }
              else{
                if(receivedData[2]=='0'){
                  data[tempdata].sec -= 1;
                }
                else{
                  data[tempdata].sec += 1;
                }
              }
              xSemaphoreGive(clock_data);
            }
          }
          else if(first=='s'){
            
            status[tempdata] = 1;
            
          }
          
          else if(first=='p'){
            status[tempdata] = 0;
          }
          else{
            
            if(xSemaphoreTake(clock_data,portMAX_DELAY)){
              if(first=='m'){
                data[tempdata].mode = (data[tempdata].mode+1)%2;
              
              }
              else{
                data[tempdata].mode = 0;
                data[tempdata].hour = 0;
                data[tempdata].minute = 0;
                data[tempdata].sec = 0;
                data[tempdata].color = 0;
                if(xSemaphoreTake(blink_fn,portMAX_DELAY)){
                  digitalWrite(BUZZER_PIN,LOW);
                  toggle = 0;
                  selected = 0;
                  blink[tempdata] = 0;
                  xSemaphoreGive(blink_fn);
                }
                status[tempdata]=0;
              }
              xSemaphoreGive(clock_data);
            }
          }
          xSemaphoreGive(status_c);
        }
      }
      Serial.println("Received from client: " + receivedData);
    } else {
      server.send(400, "text/plain", "Missing data");
    }
    
  });

  server.on("/getTimers", HTTP_GET, []() {
    if(xSemaphoreTake(j_mut,100)){
      server.send(200, "application/json", json);
      xSemaphoreGive(j_mut);
    }
  
  });
  server.begin();
  Serial.println("HTTP server started");
  vTaskDelay(pdMS_TO_TICKS(1000));
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  xTaskCreatePinnedToCore(timer1, "timer", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(buzzer, "buzzer", 1024, NULL, 1, NULL, 1);
  
  xTaskCreatePinnedToCore(button, "button", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(mainScreen, "mainScreen", 2048, NULL, 1, &mainHandle, 1);

}

void loop() {
  server.handleClient();

}
