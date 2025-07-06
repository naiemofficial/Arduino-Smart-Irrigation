# 🌿 Arduino Smart Irrigation
This project automates the control of a water pump based on soil moisture levels. While it’s ideal for small-scale irrigation systems such as home gardens and greenhouses, it also has broader applications in agriculture and landscaping. The system helps maintain optimal soil moisture levels while preventing overwatering, promoting healthier plant growth and water efficiency.

<br>
This project includes two intelligent irrigation approaches:
<br>
<ol>
    <li>
        <b><a target="_blank" href="https://cutt.ly/smart-irrigation">Smart Irrigation (Basic)</a></b>
        <br>
        <small>Automatically detects soil moisture and activates the pump when the soil is dry.</small>
    </li>
    <li>
        <b><a target="_blank" href="https://cutt.ly/smart-irrigation-with-overwatring-prevention">Smart Irrigation with Overwatering Prevention</a></b>
        <br>
        <small>Uses a state tracking approach to monitor changes in soil moisture (Dry → Moderate → Wet). The pump runs only when truly necessary, avoiding redundant cycles and unnecessary water usage.</small>
    </li>
</ol>
These two modes provide flexibility, allowing you to choose between a straightforward solution or a more optimized, sensor-aware control system.

<br><br>
<blockquote>
    <b>📌 Note on Sensor Behavior & Calibration</b>
    <br><br>
    The moisture value, level, or interpreted state (<code>Dry</code>, <code>Moderate</code>, <code>Wet</code>) may vary depending on the sensor model or version you are using.
    <ul>
        <li>Some sensors return lower values for wet soil and higher values for dry soil.</li>
        <li>Others may return values in the opposite direction.</li>
    </ul>
    <br>
    Before using this system, it's important to:
    <ol>
        <li>Understand your specific sensor's behavior by testing it in dry and wet soil.</li>
        <li>Calibrate the moisture value thresholds accordingly in the code.</li>
    </ol>
</blockquote>

<br><br>
## 🧪 Moisture Sensor Calibration Guide
To ensure accurate pump control, you must first calibrate your soil moisture sensor, since different models may behave differently (some return lower values for wet, others higher).
<br><br>
<b>Step 1: Run a Basic Test:</b>
<br>
Upload this simple sketch to your microcontroller (Arduino example):
```cpp
int sensorPin = A0; // Change pin as needed
int moistureValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  moistureValue = analogRead(sensorPin);
  Serial.println(moistureValue); // Watch values in Serial Monitor
  delay(1000);
}
```

<b>Step 2: Record Values:</b>
<ul>
    <li>Measure and note the sensor value in dry air or dry soil → <code>dry</code></li>
    <li>Measure and note the sensor value in wet soil or submerged in water → <code>wet</code></li>
</ul>
<br>
<b>Step 3: Define Thresholds:</b>
<br>
Adjust your code thresholds based on your measurements. For example, the values I used in the simulator differed from those in my real-life project because I used the Capacitive V2 Soil Moisture Sensor, which reports values differently. Always test your specific sensor to calibrate thresholds accurately. Soil moisture sensor thresholds for:
<table width="100%">
    <thead>
        <tr>
            <th>Sensor</th>
            <th>Dry</th>
            <th>Wet</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th>Simulator <sup>[<a target="_blank" href="https://cutt.ly/smart-irrigation">1</a>] [<a target="_blank" href="https://cutt.ly/smart-irrigation-with-overwatring-prevention">2</a>]</sup></th>
            <td>500</td>
            <td>800</td>
        </tr>
        <tr>
            <th>Capacitive v2</th>
            <td>450</td>
            <td>250</td>
        </tr>
    </tbody>
</table>
<blockquote>Test and calibrate the sensor in the actual soil where it will be used, as soil type and conditions affect readings.</blockquote>

<br><br><br>
## 🛠️ Components, Equipments, Other Tools
<table width="1500px">
    <tbody>
        <tr>
            <th colspan="3" align="center">Components</th>
            <th rowspan="15"></th>
            <th colspan="3" rowspan="2" align="center">Equipments</th>
        </tr>
        <tr>
            <th colspan="2" align="center">Name</th>
            <th align="center">Quantity</th>
        </tr>
        <tr>
            <td colspan="2">Arduino Uno R3</td>
            <td align="center">1</td>
            <td>Breadboard or PCB (for circuit assembly)</td>
        </tr>
        <tr>
            <td>Resistor</td>
            <td align="center">680Ω</td>
            <td align="center">4</td>
            <td>Jumper Wires</td>
        </tr>
        <tr>
            <td rowspan="3"">LEDs</td>
            <td align="center">Red</td>
            <td align="center">1</td>
            <td>USB Cable (for Arduino)</td>
        </tr>
        <tr>
            <td>Yellow</td>
            <td align="center">1</td>
            <td>Power Supply (suitable for your pump and microcontroller)</td>
        </tr>
        <tr>
            <td>Green</td>
            <td align="center">1</td>
            <td>Multimeter (optional - for measuring and calibration)</td>
        </tr>
        <tr>
            <td colspan="2">Soil Moisture Sensor</td>
            <td align="center">1</td>
        </tr>
        <tr>
            <td colspan="2">DC Water Pump</td>
            <td align="center">1</td>
            <th>Other Tools</th>
        </tr>
        <tr>
            <td colspan="2">nMOS Transistor - IRFZ44N (MOSFET)</td>
            <td align="center">1</td>
            <td><b>Software:</b> <a target="_blank" href="https://www.arduino.cc/en/software/">Arduino IDE</a></td>
        </tr>
        <tr>
            <td colspan="2">Optocoupler</td>
            <td align="center">1</td>
            <td><b>Serial Monitor:</b> via Arduino IDE or similar tool</td>
        </tr>
    </tbody>
</table>

<br><br><br>
## 🔌 Wiring Diagram
The following diagram shows how to connect all components in the system, including the soil moisture sensor, pump (via transistor), and status LEDs.
<blockquote>⚠️ Always double-check your power ratings and connections before powering the circuit.</blockquote>
<img src="https://github.com/user-attachments/assets/4bd76aba-7f74-4c13-8275-5fe6ccdc80e3" alt="Wiring Diagram"/>

<br><br><br>
## 🖼️ Visual Diagram
<img src="https://github.com/user-attachments/assets/9ae40fdd-23a9-49b2-a287-4a05199e243f" alt="Visual Circuit Diagram" />

<br><br><br>
## 💧 Smart Irrigation (Basic)
This version provides a simple automated irrigation system. It continuously checks the soil moisture level, and if the soil is detected as dry, the pump is activated. The pump continues to run until the sensor detects that the soil has become wet.
<br><br>
<b>Here's the example code</b> 
```cpp
// Pin Definitions
const int sensorpin = A0;
const int sensorpower = 11;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int pumppin = 8;

// Variable for sensor reading
int sensor;

// Delay time between sensor readings (milliseconds)
const int delayTime = 1000;

// Moisture Thresholds "wet" and "dry" thresholds - these require calibration
// (Set wet=250, dry=450; also update the condition [Capactive v2 / or the sensor that provides lower value for dry state])
int wet = 800;
int dry = 500;

void setup() {
    // Set pins as outputs
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(sensorpower, OUTPUT);
    pinMode(pumppin, OUTPUT);

    // Initialize serial communication
    Serial.begin(9600);
}

void loop() { // code that loops forever
    // power on sensor and wait briefly
    digitalWrite(sensorpower, HIGH);
    delay(10);
    // take reading from sensor
    sensor = analogRead(sensorpin);
    // turn sensor off to help prevent corrosion
    digitalWrite(sensorpower, LOW);

    // print sensor reading
    Serial.println(sensor);

    // If sensor reading is greater than "wet" threshold,
    // turn on the blue LED. If it is less than the "dry"
    // threshold, turn on the red LED and the pump. 
    // If it is in between the two values, turn on 
    // the yellow LED.
    if (sensor > wet) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(pumppin, LOW);
    } else if (sensor < dry) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(pumppin, HIGH);
    } else {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(pumppin, LOW);
    }

    // wait before taking next reading
    delay(delayTime);
}
```

<br><br><br>
## 💧 Smart Irrigation with Overwatering Prevention
This version enhances the basic logic by adding a state-aware system to prevent unnecessary watering. Instead of turning on the pump immediately every time the soil is dry, it tracks transitions between states:  <code>Dry</code> → <code>Moderate</code> → <code>Wet</code> and back.
<br><br>
This version is especially useful because some soil moisture sensors respond slowly or take time to reflect accurate moisture levels. The delay interval after each pump cycle gives the sensor time to stabilize and provide correct data, ensuring that the pump doesn't run unnecessarily based on outdated or fluctuating readings.
<br><br>
The following table illustrates the state transitions that control the pump behavior based on soil moisture levels:
<table width="100%">
    <thead>
        <tr>
            <th>Current State</th>
            <th>Next State</th>
            <th>Pump</th>
            <th>Check state after</th>
            <th>Re-check</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td align="center">🔴</td>
            <td align="center">🟡</td>
            <td rowspan="2" align="center"><img src="https://github.com/user-attachments/assets/019d94fe-f2a9-48ac-8e14-8973c9ff3a00" alt="ON" width="48px"></td>
            <td rowspan="2" align="center">1 minute</td>
            <td rowspan="2" align="center">After Pump OFF</td>
        </tr>
        <tr>
            <td rowspan="2" align="center">🟡</td>
            <td align="center">🟢</td>
        </tr>
        <tr>
            <td align="center">🔴</td>
            <td rowspan="3" align="center"><img src="https://github.com/user-attachments/assets/372d0605-5597-4695-8079-31f91e66c523" alt="OFF" width="48px"></td>
            <td rowspan="3" align="center">1 second</td>
            <td rowspan="3" align="center">Immediately</td>
        </tr>
        <tr>
            <td rowspan="2" align="center">🟢</td>
            <td align="center">🔴</td>
        </tr>
        <tr>
            <td align="center">🟡</td>
        </tr>
    </tbody>
</table>

<br><br>
<b>Here's the example code</b> 

```cpp
// Pin Definitions
const int sensorpin = A0;
const int sensorpower = 11;
const int RED = 2;
const int YELLOW = 3;
const int BLUEGREEN = 4;
const int pumppin = 8;

// Moisture Thresholds "wet" and "dry" thresholds - these require calibration
// (Set wet=250, dry=450; also update the condition [Capactive v2 / or the sensor that provides lower value for dry state])
int wet = 800;
int dry = 500;

// Timing Constants
const unsigned long PUMP_RUN_DURATION = 10000; // Pump runs for 10 seconds
const unsigned long PUMP_WAIT_INTERVAL = 60000; // Check after 60 Seconds

// Delay time between sensor readings (milliseconds)
const int delayTime = 1000;

// State Management
enum MoistureState {
    STATE_UNKNOWN = -1, STATE_WET = 0, STATE_MODERATE = 1, STATE_DRY = 2
};

// Forward Declarations
String getMoistureStateName(MoistureState state);
void setLEDs(bool red, bool yellow, bool green);

// Variable for sensor reading
int sensor;

// Vartiable for Time Tracking
unsigned long lastCheckTime = 0, pumpStartTime = 0;
bool pumpRunning = false, waitingToCheck = false, pumpCycleOriginatedFromDry = false;
MoistureState previousMoistureState = STATE_UNKNOWN;

String getMoistureStateName(MoistureState state) {
    switch (state) {
    case STATE_WET:
        return "WET";
    case STATE_MODERATE:
        return "MODERATE";
    case STATE_DRY:
        return "DRY";
    default:
        return "UNKNOWN";
    }
}

void setLEDs(bool red, bool yellow, bool green) {
    digitalWrite(RED, red ? HIGH : LOW);
    digitalWrite(YELLOW, yellow ? HIGH : LOW);
    digitalWrite(BLUEGREEN, green ? HIGH : LOW);
}

void setup() {
    // Set pins as outputs
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(BLUEGREEN, OUTPUT);
    pinMode(sensorpower, OUTPUT);
    pinMode(pumppin, OUTPUT);

    // Initialize serial communication
    Serial.begin(9600);
    Serial.println("System starting...");
}

void loop() {
    // Sensor Reading
    digitalWrite(sensorpower, HIGH);
    delay(10);
    sensor = analogRead(sensorpin);
    digitalWrite(sensorpower, LOW);
    Serial.println("\n--- New Loop Cycle ---");
    Serial.print("Sensor value: ");
    Serial.println(sensor);

    // Determine Moisture State
    MoistureState currentMoistureState;
    if (sensor >= wet) currentMoistureState = STATE_WET;
    else if (sensor <= dry) currentMoistureState = STATE_DRY;
    else currentMoistureState = STATE_MODERATE;

    Serial.print("Current State: ");
    Serial.println(getMoistureStateName(currentMoistureState));
    Serial.print("Previous State: ");
    Serial.println(getMoistureStateName(previousMoistureState));

    // LED Control
    if (currentMoistureState == STATE_WET) setLEDs(false, false, true);
    else if (currentMoistureState == STATE_DRY) setLEDs(true, false, false);
    else setLEDs(false, true, false);

    // Pump Control Logic based on change state
    if (currentMoistureState == STATE_WET) {
        digitalWrite(pumppin, LOW);
        pumpRunning = waitingToCheck = pumpCycleOriginatedFromDry = false;
        Serial.println("ACTION: Wet state detected. Pump OFF.");
    } else if (pumpRunning) {
        if (millis() - pumpStartTime >= PUMP_RUN_DURATION) {
            digitalWrite(pumppin, LOW);
            pumpRunning = false;
            waitingToCheck = true;
            lastCheckTime = millis();
            Serial.println("ACTION: Pump stopped. Entering wait state.");
        }
    } else if (waitingToCheck) {
        if (millis() - lastCheckTime >= PUMP_WAIT_INTERVAL) {
            waitingToCheck = false;
            if (currentMoistureState == STATE_DRY ||
                (currentMoistureState == STATE_MODERATE && pumpCycleOriginatedFromDry)) {
                digitalWrite(pumppin, HIGH);
                pumpRunning = true;
                pumpStartTime = millis();
                Serial.println("ACTION: Conditions met. Pump STARTING.");
            } else {
                pumpCycleOriginatedFromDry = false;
                Serial.println("INFO: Conditions not met. Pump remains OFF.");
            }
        }
    } else if (currentMoistureState == STATE_DRY ||
        (currentMoistureState == STATE_MODERATE && previousMoistureState == STATE_DRY)) {
        digitalWrite(pumppin, HIGH);
        pumpRunning = true;
        pumpStartTime = millis();
        pumpCycleOriginatedFromDry = (currentMoistureState == STATE_DRY);
        Serial.println("ACTION: Pump STARTING.");
    }

    previousMoistureState = currentMoistureState;
    delay(delayTime);
}
```
