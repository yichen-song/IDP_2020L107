#include <Servo.h>
<<<<<<< Updated upstream
=======
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "Chassis.h"

>>>>>>> Stashed changes
Servo servo1;
Servo servo2;

int servo_motor1 = 1;
int servo_motor2 = 2;
int power_motorL = 3;
int power_motorR = 4;
int arm_motor = 5;
int distance_sensor1 = A1;
<<<<<<< Updated upstream
int distance_sensor2 = A2;
int light_sensorL = A3;
int light_sensorR = A4;

class chassis {
  public:
  int traverse_speed = 50; //pwm of 0-255
  int rotate_speed = 10; //pwm of 0-255
  int rotate90_duration = 1000; //TODO: measure how long to rotate 90 deg
  void traverse(bool front) //if front = 1, go forward
  {
    if(front == 1)
    {
      analogWrite(power_motorR, traverse_speed);
      analogWrite(power_motorL, traverse_speed);
    }
    else //figure out how to drive motor backwards
    {
      analogWrite(power_motorR, -1 * rotate_speed);
      analogWrite(power_motorL, -1 * rotate_speed);
    }
  }
  void rotate(bool right) //if right = 1, turn rightward
  {
    if(right == 1)
    {
      analogWrite(power_motorR, -1 * traverse_speed);
      analogWrite(power_motorL, traverse_speed);
    }
    else //figure out how to drive motor backwards
    {
      analogWrite(power_motorR, traverse_speed);
      analogWrite(power_motorL, -1 * traverse_speed);
    }
  }
  void rotate90(bool right)
  {
    if(right == 1)
    {
      analogWrite(power_motorR, -1 * traverse_speed);
      analogWrite(power_motorL, traverse_speed);
    }
    else //figure out how to drive motor backwards
    {
      analogWrite(power_motorR, traverse_speed);
      analogWrite(power_motorL, -1 * traverse_speed);
    }
    delay(rotate90_duration);
    digitalWrite(power_motorR, LOW);
    digitalWrite(power_motorL, LOW);
  }
  void halt()
  {
    digitalWrite(power_motorR, LOW);
    digitalWrite(power_motorL, LOW);
  }
};

class rescue_arm {
  public:
  int motor_power = 50; //pwm of 0-255 TODO:callibrate this
=======
int distance_sensor2 = A0;
int light_sensorL = A2;
int light_sensorR = A3;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorL = AFMS.getMotor(power_motorL);
Adafruit_DCMotor *motorR = AFMS.getMotor(power_motorR);
Adafruit_DCMotor *motor_arm = AFMS.getMotor(arm_motor);

class rescue_arm
{
public:
  int motor_speed = 50; //pwm of 0-255 TODO:callibrate this
>>>>>>> Stashed changes
  int power_at_rest = 10;
  int rescue_arm_duration = 500; //the time before the motor reduces power
  void hold()
  {
    analogWrite(arm_motor, motor_power);
    delay(rescue_arm_duration);
    analogWrite(arm_motor, power_at_rest);
  }
  void relax()
  {
    analogWrite(arm_motor, -1 * motor_power);
    delay(rescue_arm_duration);
    digitalWrite(arm_motor, LOW);
  }
};

class sensors
{
public:
  int color_threshold = 490; //TODO: callibrate this
  int detect_white()         //0 if both black, 1 if left white, 2 if right white, 3 if both white
  {
    if ((analogRead(light_sensorL) < color_threshold) and (analogRead(light_sensorR) < color_threshold))
    {
      return 0;
    }
    else if ((analogRead(light_sensorL) > color_threshold) and (analogRead(light_sensorR) < color_threshold))
    {
      return 1;
    }
    else if ((analogRead(light_sensorL) < color_threshold) and (analogRead(light_sensorR) > color_threshold))
    {
      return 2;
    }
    else if ((analogRead(light_sensorL) > color_threshold) and (analogRead(light_sensorR) > color_threshold))
    {
      return 3;
    }
  }
  float detect_distance1() //return distance from sensor 1 in cm
  {
    float sensorValue = analogRead(distance_sensor1);
    float cm = 10650.08 * pow(sensorValue, -0.935) - 10;
    cm = roundf(cm);
    return cm;
  }
  float detect_distance2() //return distance from sensor 2 in cm
  {
    float sensorValue = analogRead(distance_sensor2);
    float cm = 10650.08 * pow(sensorValue, -0.935) - 10;
    cm = roundf(cm);
    return cm;
  }
  void radar_angle(int angle) //TODO: test this
  {
    servo1.write(angle);
  }
};

<<<<<<< Updated upstream
void state0(int* state)
{
  //initialize
=======
Chassis chassis(power_motorL, power_motorR);
rescue_arm rescue_arm;
sensors sensors;
unsigned long start_time;

void state0(int *state)
{
  //initialize

  motor_arm->setSpeed(0);
>>>>>>> Stashed changes
  servo1.write(90);
  servo2.write(90);
  chassis.halt();
  digitalWrite(arm_motor, LOW);
  delay(100);
<<<<<<< Updated upstream
  while(sensors.detect_white() != 2)
  {
    //if(sensors.detect_white() != 0){//throw color sensor calliration error}
    chassis.traverse(1);
  }
  delay(10);
  chassis.rotate90(1);
  delay(10);
  while(sensors.detect_white() != 3)
  {
    //if(sensors.detect_white() != 0){//throw color sensor calliration error}
    chassis.traverse(1);
=======

  chassis.traverse(1);
  int i = 0;
  bool swc = 1;
  delay(2000);
  start_time = millis();
  while ((millis() - start_time) < 6000)
  {
    if (sensors.detect_white() == 2)
    {
      chassis.manual(240, 1);
      delay(400);
    }
    else
    {
      chassis.manual(240, 255);
    }
    delay(1);
  }
  chassis.halt();
  delay(1000);
  /*
  motorL->setSpeed(50);
  motorR->setSpeed(50);*/
  //int swc = 1;

  while (1)
  {
    if (sensors.detect_white() == 2)
    {
      chassis.manual(150, 1);
      delay(150);
    }
    else if (sensors.detect_white() == 1)
    {
      chassis.manual(1, 150);
      delay(150);
    }
    else if (sensors.detect_white() == 0)
    {
      chassis.manual(255, 255);
      delay(50);
    }
    else
    {
      chassis.manual(0, 0);
      break;
    }

    delay(1);
    i++;
>>>>>>> Stashed changes
  }

  *state = 1;
}

void state1(int *state)
{
<<<<<<< Updated upstream
  
=======
  int location = 3;             //0 = at center, 1 = at left, 2 = at right, 3 = error
  float distance_to_wall = 100; //TODO: callibrate this
  int angle = 80;
  sensors.radar_angle(angle);
  while (angle < 100)
  {
    float distance1 = sensors.detect_distance1();
    float distance2 = sensors.detect_distance2();
    if ((distance1 < distance_to_wall) and (distance2 < distance_to_wall))
    {
      location = 0;
    }
    sensors.radar_angle(angle);
    angle++;
    delay(10);
  }
  if (location == 0)
  {
    sensors.radar_angle(90);
    while ((sensors.detect_distance1() > 5) and (sensors.detect_distance2() > 5))
    {
      chassis.traverse(1);
    }
    chassis.halt();
    *state = 2;
  }
  else
  {
    bool at_left = 0;
    float cnt = 0;                //TODO: callibrate this
    float distance_to_side = 100; //TODO: callibrate this
    sensors.radar_angle(0);
    while (cnt < 10000)
    {
      chassis.traverse(1);
      if ((sensors.detect_distance1() < distance_to_side) and (sensors.detect_distance2() < distance_to_side))
      {
        at_left = 1;
        break;
      }
    }
    chassis.halt();
    if (at_left == 1)
    {
      chassis.rotate90(0);
      while ((sensors.detect_distance1() > 5) and (sensors.detect_distance2() > 5))
      {
        chassis.traverse(1);
      }
      chassis.halt();
      *state = 2;
    }
    else
    {
      chassis.rotate90(0);
      chassis.rotate90(0);
      int at_right;
      cnt = 0;
      while (cnt < 10000)
      {
        chassis.traverse(1);
        if ((sensors.detect_distance1() < distance_to_side) and (sensors.detect_distance2() < distance_to_side))
        {
          at_right = 1;
          break;
        }
      }
      if (at_right == 1)
      {
        chassis.rotate90(0);
        while ((sensors.detect_distance1() > 5) and (sensors.detect_distance2() > 5))
        {
          chassis.traverse(1);
        }
        chassis.halt();
        *state = 2;
      }
      else
      {
        //throw victim not found error
      }
    }
  }
>>>>>>> Stashed changes
}

void state2(int *state)
{
  int swc = 1;
  chassis.manual(75, 75);
  start_time = millis();
  while ((millis() - start_time) < 6000)
  {
    if (sensors.detect_white() == 0)
    {
      chassis.manual(75, 75);
    }
    else if (sensors.detect_white() == 1)
    {
      chassis.manual(0, 75);
      delay(200);
      chassis.manual(-50, -50);
      delay(200);
    }
    else if (sensors.detect_white() == 2)
    {
      chassis.manual(75, 0);
      delay(200);
      chassis.manual(-50, -50);
      delay(200);
    }
    else
    {
      if (swc == 0)
      {
        break;
      }
      chassis.manual(-25, -25);
      delay(200);
      swc = 0;
    }
    delay(1);
  }
  chassis.halt();
  while (1)
  {
  }
  chassis.traverse(1);
  bool swc1 = 0;
  bool swc2 = 0;

  while (swc2 == 0)
  {
    if (sensors.detect_white() == 3)
    {
      swc1 = 1;
    }
    if ((sensors.detect_white() == 0) and (swc1 == 1))
    {
      swc2 = 1;
    }
  }

  int i = 0;
  while (i < 30)
  {
    if (sensors.detect_white() == 2)
    {
      chassis.manual(240, 1);
      delay(2);
    }
    else
    {
      chassis.manual(240, 255);
    }
    delay(1);
    i++;
  }
  i = 0;
  //chassis.rotate45(1);
  //chassis.manual(140, 150);
  /*
  while(1)
  {
    if(sensors.detect_white() == 2)
    {
      chassis.rotate45(1);
      break;
    }
  }*/

  while (i < 40)
  {
    if ((sensors.detect_white() == 2) or (sensors.detect_white() == 3))
    {
      chassis.rotate10(1);
    }
    else
    {
      chassis.manual(255, 255);
    }
    delay(1);
    i++;
  }
  //while(1){chassis.halt();}
  /*
  motorL->setSpeed(50);
  motorR->setSpeed(50);*/
  //int swc = 1;

  while (1) //i < 50)
  {
    if (sensors.detect_white() == 2)
    {
      chassis.manual(255, 1);
    }
    else if (sensors.detect_white() == 1)
    {
      chassis.manual(1, 255);
    }
    else if (sensors.detect_white() == 0)
    {
      chassis.manual(255, 255);
    }
    else
    {
      chassis.manual(0, 0);
      break;
    }

    delay(1);
    i++;
  }

  *state = 3;
}

void state3(int *state)
{
  //chassis.traverse(1);
  int i = 0;
  bool swc = 1;
  while (i < 50)
  {
    if (sensors.detect_white() == 1)
    {
      chassis.rotate10(0);
    }
    else
    {
      chassis.manual(255, 255);
    }
    delay(1);
    i++;
  }
  /*
  motorL->setSpeed(50);
  motorR->setSpeed(50);*/
  //int swc = 1;

  while (1)
  {
    if (sensors.detect_white() == 2)
    {
      chassis.manual(255, 1);
    }
    else if (sensors.detect_white() == 1)
    {
      chassis.manual(1, 255);
    }
    else if (sensors.detect_white() == 0)
    {
      chassis.manual(255, 255);
    }
    else
    {
      chassis.manual(0, 0);
      break;
    }

    delay(1);
    i++;
  }

  *state = 1;
}

void state4(int *state)
{
}

void state5(int *state)
{
}

<<<<<<< Updated upstream
void setup() {
  // put your setup code here, to run once:
  servo1.attach(servo_motor1); 
  servo2.attach(servo_motor2); 
  pinMode(power_motorL, OUTPUT); 
  pinMode(power_motorR, OUTPUT); 
  pinMode(arm_motor, OUTPUT);
  pinMode(distance_sensor1, INPUT); 
  pinMode(distance_sensor2, INPUT); 
  pinMode(light_sensorL, INPUT); 
=======
void setup()
{
  // put your setup code here, to run once:
  servo1.attach(servo_motor1);
  servo2.attach(servo_motor2);
  pinMode(distance_sensor1, INPUT);
  pinMode(distance_sensor2, INPUT);
  pinMode(light_sensorL, INPUT);
>>>>>>> Stashed changes
  pinMode(light_sensorR, INPUT);
}

int state = 0;
chassis chassis;
rescue_arm rescue_arm;
sensors sensors;

<<<<<<< Updated upstream
void loop() {

  switch(state){
    case 0:
      state0(&state); 
      break;
    case 1:
      state1(&state);
      break;
    case 2:
      state2(&state);
      break;
    case 3:
      state3(&state);
      break;
    case 4:
      state4(&state);
      break;
    case 5:
      state5(&state);
      break;
  }
=======
void loop()
{
  delay(5000);
>>>>>>> Stashed changes

  //state0(&state);
  //state1(&state);
  //delay(2000);
  state2(&state);
  chassis.rotate90(1);
  chassis.rotate90(1);
  state3(&state);
}
