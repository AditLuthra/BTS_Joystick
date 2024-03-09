// Receiver signal pins
int vx = A0;  // Analog pin for joystick x-axis
int vy = A1;  // Analog pin for joystick y-axis

// Right motor driver pins
int R_EN_right = 2; 
int L_EN_right = 4;
int R_PWM_right = 6; // PWM pin
int L_PWM_right = 9; // PWM pin

// Left motor driver pins
int R_EN_left = 7; 
int L_EN_left = 8;
int R_PWM_left = 10; // PWM pin
int L_PWM_left = 11; // PWM pin

void setup()
{
  Serial.begin(9600);
  pinMode(vx, INPUT);
  pinMode(vy, INPUT);
  pinMode(R_EN_right, OUTPUT);
  pinMode(L_EN_right, OUTPUT);
  pinMode(R_PWM_right, OUTPUT); 
  pinMode(L_PWM_right, OUTPUT);
  pinMode(R_EN_left, OUTPUT);
  pinMode(L_EN_left, OUTPUT);
  pinMode(R_PWM_left, OUTPUT); 
  pinMode(L_PWM_left, OUTPUT);
}

void loop()
{
  int x = analogRead(vx);
  int y = analogRead(vy);

  Serial.print("X ");
  Serial.println(x);
  Serial.print("\t");
  Serial.print("Y ");
  Serial.println(y);
  
  if (x > 507) {
    if (y > 523) {
      int out1 = map(x, 507, 1023, 0, 255);
      int out2 = map(y, 523, 1023, 0, 255);
      int sub = abs(out2 - out1);
      int add = out2 + out1;
      analogWrite(R_PWM_right, sub);
      analogWrite(R_PWM_left, add);
      analogWrite(L_PWM_right, 0);
      analogWrite(L_PWM_left, 0);
    }
    else if (y < 523) {
      int out1 = map(x, 507, 1023, 0, 255);
      int out2 = map(y, 523, 0, 255);
      int sub = abs(out2 - out1);
      int add = out2 + out1;
      analogWrite(R_PWM_right, add);
      analogWrite(R_PWM_left, sub);
      analogWrite(L_PWM_right, 0);
      analogWrite(L_PWM_left, 0);
    }
    else {
      int out1 = map(x, 507, 1023, 0, 255);
      analogWrite(R_PWM_right, out1);
      analogWrite(R_PWM_left, out1);
      analogWrite(L_PWM_right, 0);
      analogWrite(L_PWM_left, 0);
    }
  }
  else if (x < 507) {
    if (y > 523) {
      int out1 = map(x, 507, 0, 0, 255);
      int out2 = map(y, 523, 1023, 0, 255);
      int sub = abs(out2 - out1);
      int add = out2 + out1;
      analogWrite(L_PWM_right, sub);
      analogWrite(L_PWM_left, add);
      analogWrite(R_PWM_right, 0);
      analogWrite(R_PWM_left, 0);
    }
    else if (y < 523) {
      int out1 = map(x, 507, 0, 0, 255);
      int out2 = map(y, 523, 0, 255);
      int sub = abs(out2 - out1);
      int add = out2 + out1;
      analogWrite(L_PWM_right, add);
      analogWrite(L_PWM_left, sub);
      analogWrite(R_PWM_right, 0);
      analogWrite(R_PWM_left, 0);
    }
    else {
      int out1 = map(x, 507, 0, 0, 255);
      analogWrite(L_PWM_right, out1);
      analogWrite(L_PWM_left, out1);
      analogWrite(R_PWM_right, 0);
      analogWrite(R_PWM_left, 0);
    }
  }
  else {
    analogWrite(R_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_right, 0);
    analogWrite(L_PWM_left, 0);
  }
}
