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