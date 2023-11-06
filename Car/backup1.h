#include "Motor.h"
#include <PS2X_lib.h>  //for v1.6
Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// 创建一个 Adafruit_PWMServoDriver 实例
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define PS2_DAT 13  //14
#define PS2_CMD 11  //15
#define PS2_SEL 10  //16
#define PS2_CLK 12  //17
int speedPinA = 8;
int speedPinB = 9;
#define pressures true
//#define pressures   false
#define rumble true
//#define rumble      false
PS2X ps2x;  // create PS2 Controller Class
//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;
void setup() {
  motor.speed(100);
  Serial.begin(9600);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  pwm.begin();
  pwm.setPWMFreq(50);  // 设置 PWM 频率，通常为 50Hz

  // 设置舵机参数
  int servoMin = 10;   // 舵机的最小脉冲宽度
  int servoMax = 500;  // 舵机的最大脉冲宽度
  Servos_begin();
}
int begin1 = 250;
int begin2 = 250;
int begin3 = 10;
void Servos_begin() {
  pwm.setPWM(0, 0, begin1);
  pwm.setPWM(1, 0, begin2);
  pwm.setPWM(2, 0, begin3);
}
void loop() {
  if (error == 1)  //skip loop if no controller found
    return;

  if (type == 2) {  //Guitar Hero Controller
    return;
  } else {                              //DualShock Controller
    ps2x.read_gamepad(false, vibrate);  //read controller and set large motor to spin at 'vibrate' speed

    byte LY = ps2x.Analog(PSS_LY);
    byte LX = ps2x.Analog(PSS_LX);
    byte RY = ps2x.Analog(PSS_RY);
    byte RX = ps2x.Analog(PSS_RX);

    Serial.print(LY);
    Serial.print(LX);
    Serial.print(RY);
    Serial.println(RX);
    if (LY < 110)  //前进
    {
      motor.speed(250 - LY);
      motor.forward();
      delay(50);
    }
    //后退
    if (LY > 140) {
      motor.speed(LY - 10);
      motor.backward();
      delay(50);
    }
    //左转
    if (LX < 110) {
      motor.speed(255);
      motor.left();
      delay(50);
    }
    //右转
    if (LX > 140) {
      motor.speed(255);
      motor.right();
      delay(50);
    }
    if (ps2x.Button(PSB_L1)) {
      motor.speed(255);
      motor.forward();
      delay(50);
    }
    if (ps2x.Button(PSB_R1)) {
      motor.speed(255);
      motor.horizontal_L();
      delay(50);
    }
    //如果摇杆居中
    if (LY >= 110 && LY <= 140 && LX >= 110 && LX <= 140) {
      motor.stop();
      delay(50);
    }
    if (RY < 110)  //前进
    {
      begin1 = begin1 + 5;
      pwm.setPWM(0, 0, begin1);
    }

    if (RY > 140) {
      begin1 = begin1 - 5;
      pwm.setPWM(0, 0, begin1);
    }
    if (RX < 110) {
      begin2 = begin2 - 5;
      pwm.setPWM(1, 0, begin2);
    }
    //右转
    if (RX > 140) {
      begin2 = begin2 + 5;
      pwm.setPWM(1, 0, begin2);
    }
  }
}