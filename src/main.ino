struct MotorCmd {
  bool dir;
  unsigned long steps;
  unsigned long stepsDone;
  unsigned long delay_us; //microseconds
  unsigned long lastStep;
  bool state;
};

int MOTOR_0_PIN = 10;
int MOTOR_0_DIR_PIN = 9;

int MOTOR_1_PIN = 8;
int MOTOR_1_DIR_PIN = 7;

int MOTOR_2_PIN = 6;
int MOTOR_2_DIR_PIN = 5;

int MOTOR_3_PIN = 4;
int MOTOR_3_DIR_PIN = 3;

bool failedRead = false;

void setup() {
  pinMode(MOTOR_0_PIN, OUTPUT);
  pinMode(MOTOR_0_DIR_PIN, OUTPUT);

  pinMode(MOTOR_1_PIN, OUTPUT);
  pinMode(MOTOR_1_DIR_PIN, OUTPUT);

  pinMode(MOTOR_2_PIN, OUTPUT);
  pinMode(MOTOR_2_DIR_PIN, OUTPUT);

  pinMode(MOTOR_3_PIN, OUTPUT);
  pinMode(MOTOR_3_DIR_PIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    delay(1000);
  }
  Serial.println("r");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming data until a newline character is received
    String data = Serial.readStringUntil('\n');

    // Parse the data and place it into structs
    MotorCmd m0, m1, m2, m3;
    m0.state = false;
    m0.stepsDone = 0;

    m1.state = false;
    m1.stepsDone = 0;

    m2.state = false;
    m2.stepsDone = 0;

    m3.state = false;
    m3.stepsDone = 0;
    parseData(data, m0, m1, m2, m3);

    if (!failedRead) {
      runCmds(m0, m1, m2, m3);
      Serial.println("r");
    } else {
      Serial.println("f");
    }
  }
}

void parseData(String data, MotorCmd& m0, MotorCmd& m1, MotorCmd& m2, MotorCmd& m3) {
  // Find the opening and closing curly braces to extract individual sensor data
  int start0 = data.indexOf('{');
  int end0 = data.indexOf('}', start0);

  int start1 = data.indexOf('{', end0 + 1);
  int end1 = data.indexOf('}', start1);

  int start2 = data.indexOf('{', end1 + 1);
  int end2 = data.indexOf('}', start2);

  int start3 = data.indexOf('{', end2 + 1);
  int end3 = data.indexOf('}', start3);

  // Extract substrings for each sensor
  String m0str = data.substring(start0 + 1, end0);
  String m1str = data.substring(start1 + 1, end1);
  String m2str = data.substring(start2 + 1, end2);
  String m3str = data.substring(start3 + 1, end3);

  // Parse and fill the SensorData structs
  parseStr(m0str, m0);
  parseStr(m1str, m1);
  parseStr(m2str, m2);
  parseStr(m3str, m3);
}

void parseStr(String motorStr, MotorCmd& motor) {
  // Use strtok to tokenize the string based on commas
  char *token = strtok(const_cast<char*>(motorStr.c_str()), ",");

  failedRead = false;
  // Parse and assign values to the struct members
  if (token != NULL) {
    motor.dir = (strcmp(token, "true") == 0);
    token = strtok(NULL, ",");
  }else {
    failedRead = true;
  }

  if (token != NULL) {
    motor.steps = strtoul(token, NULL, 0);
    token = strtok(NULL, ",");
  } else {
    failedRead = true;
  }

  if (token != NULL) {
    motor.delay_us = strtoul(token, NULL, 0);
  } else {
    failedRead = true;
  }
}

void runCmds(MotorCmd& m0,MotorCmd& m1,MotorCmd& m2,MotorCmd& m3) {
  unsigned long totalSteps = 0;
  totalSteps += m0.steps;
  totalSteps += m1.steps;
  totalSteps += m2.steps;
  totalSteps += m3.steps; // I have no idea why I can't all them all at once but I can't.

  digitalWrite(MOTOR_0_DIR_PIN, m0.dir);
  digitalWrite(MOTOR_1_DIR_PIN, m1.dir);
  digitalWrite(MOTOR_2_DIR_PIN, m2.dir);
  digitalWrite(MOTOR_3_DIR_PIN, m3.dir);

  unsigned long st = micros();
  m0.lastStep = st;
  m1.lastStep = st;
  m2.lastStep = st;
  m3.lastStep = st;

  unsigned long steps = 0;
  while (steps < totalSteps) {
    unsigned long timeNow = micros();
    if (timeNow - m0.lastStep > m0.delay_us && m0.stepsDone <= m0.steps) {
      digitalWrite(MOTOR_0_PIN, !m0.state);
      m0.lastStep = timeNow;
      m0.state = !m0.state;
      m0.stepsDone++;
      steps ++;
    }
    if (timeNow - m1.lastStep > m1.delay_us && m1.stepsDone <= m1.steps) {
      digitalWrite(MOTOR_1_PIN, !m1.state);
      m1.lastStep = timeNow;
      m1.state = !m1.state;
      m1.stepsDone++;
      steps ++;
    }
    if (timeNow - m2.lastStep > m2.delay_us && m2.stepsDone <= m2.steps) {
      digitalWrite(MOTOR_2_PIN, !m2.state);
      m2.lastStep = timeNow;
      m2.state = !m2.state;
      m2.stepsDone++;
      steps ++;
    }
    if (timeNow - m3.lastStep > m3.delay_us && m3.stepsDone <= m3.steps) {
      digitalWrite(MOTOR_3_PIN, !m3.state);
      m3.lastStep = timeNow;
      m3.state = !m3.state;
      m3.stepsDone++;
      steps ++;
    }
  }
  digitalWrite(MOTOR_0_PIN, LOW);
  digitalWrite(MOTOR_1_PIN, LOW);
  digitalWrite(MOTOR_2_PIN, LOW);
  digitalWrite(MOTOR_3_PIN, LOW);
}
