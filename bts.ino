//Receiver signal pins
int ch1_pin = A0;  // Analog pin for joystick x-axis
int ch2_pin = A1;  // Analog pin for joystick y-axis

//Right motor driver pins
int R_EN_right = 2; 
int L_EN_right = 4;
int R_PWM_right = 6; //PWM pin
int L_PWM_right = 9; //PWM pin

//Left motor driver pins
int R_EN_left = 7; 
int L_EN_left = 8;
int R_PWM_left = 10; //PWM pin
int L_PWM_left = 11; //PWM pin

// ---**---   Rx threshold values - Update based on your TX values
//FWD
int Ch1Ch2_start_Fwd = 1530;
int Ch1Ch2_End_Fwd = 1980;
//BACK
int Ch1Ch2_start_Bac = 1460;
int Ch1Ch2_End_Bac = 960;

// ---------***---------------***----------

void setup()
{
  Serial.begin(9600);
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
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
  //Receiver signal pins data
  int ch1 = analogRead(ch1_pin);
  int ch2 = analogRead(ch2_pin);

  Serial.print("ch1: ");
  Serial.println(ch1);
  //Serial.print("\t");
  //Serial.print("ch2: ");
  //Serial.print(ch2);
  //Serial.println("");

  //Speed mapping for right motor driver
  int spdFwd_RightLeft = map(ch1, Ch1Ch2_start_Fwd, Ch1Ch2_End_Fwd, 0, 255);   
  int spdBac_RightLeft = map(ch1, Ch1Ch2_start_Bac, Ch1Ch2_End_Bac, 0, 255);    

  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);

  if ((ch1 == 0) && (ch2 == 0)) {     
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, 0);
  }
  //FWD
  else if ((ch1 > Ch1Ch2_start_Fwd) && (ch2 > Ch1Ch2_start_Fwd)) {     
    analogWrite(R_PWM_right, spdFwd_RightLeft);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, spdFwd_RightLeft);
    analogWrite(L_PWM_left, 0); 
  }
  //RIGHT
  else if ((ch1 > Ch1Ch2_start_Fwd) && (ch2 < Ch1Ch2_start_Bac)) { 
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, spdFwd_RightLeft);
    analogWrite(R_PWM_left, spdFwd_RightLeft);
    analogWrite(L_PWM_left, 0);
  }
  //LEFT
  else if ((ch1 < Ch1Ch2_start_Bac) && (ch2 > Ch1Ch2_start_Fwd)) {     
    analogWrite(R_PWM_right, spdBac_RightLeft);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, spdBac_RightLeft);
  }
  //BACK
  else if ((ch1 < Ch1Ch2_start_Bac) && (ch2 < Ch1Ch2_start_Bac)) {  
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, spdBac_RightLeft); 
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, spdBac_RightLeft); 
  }
  else {     
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, 0);
  }
}
