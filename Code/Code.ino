/******************************************************************
*   Programador..............: (c) Tiago Machado
*   Data.....................: 21/01/2025
*   Observações..............: Alarme							
******************************************************************/

const int BAUD_RATE = 9600;
const byte POWER_LED = 2;
const byte POWER_BUTTON = 3;
const byte PIR_SENSOR = 4;
const byte BUZZER = 5;

const byte STANDBY = 0;
const byte POWER_ON = 1;
const byte ALARM_ON = 2;
const byte PIR_DETECT = 3;

const bool DEBUG = true;

byte alarmState;

  void setup() {
    Serial.begin(BAUD_RATE);

    pinMode(POWER_LED, OUTPUT);
    pinMode(POWER_BUTTON, INPUT);
    pinMode(PIR_SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);

    alarmState = STANDBY;
    digitalWrite(POWER_LED, LOW);
}

  void loop() {
    switch (alarmState) {
      case STANDBY: {
        if (DEBUG) Serial.println("Standby...");

        if (digitalRead(POWER_BUTTON) == LOW) {
        alarmState = POWER_ON;
      }
        break;
    }

      case POWER_ON: {
        if (DEBUG) Serial.println("Power ON...");

      digitalWrite(POWER_LED, HIGH);
      delay(300);
      alarmState = ALARM_ON;
      break;
    }

    case ALARM_ON: {
        if (DEBUG) Serial.println("Alarm ON...");

        if (digitalRead(PIR_SENSOR) == HIGH) {
        alarmState = PIR_DETECT;
      }
      break;
    }

    case PIR_DETECT: {
        if (DEBUG) Serial.println("PIR DETECT...");

        for (int i = 700; i <= 800; i++) {
        tone(BUZZER, i);
        delay(15);
      }
        for (int i = 800; i >= 700; i--) {
        tone(BUZZER, i);
        delay(15);
      }

        noTone(BUZZER);
        alarmState = ALARM_ON;
      break;
    }
  }
}
