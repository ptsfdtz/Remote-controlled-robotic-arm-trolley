#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// 创建一个 Adafruit_PWMServoDriver 实例
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  // 初始化 PWM 驱动板
  pwm.begin();
  pwm.setPWMFreq(50);  // 设置 PWM 频率，通常为 50Hz

  // 设置舵机参数
  int servoMin = 10;  // 舵机的最小脉冲宽度
  int servoMax = 500;  // 舵机的最大脉冲宽度

  // 控制舵机
  pwm.setPWM(0, 0, 250);
  
  delay(500);
}

void loop() {
  // 在 loop() 中可以添加其他操作
}

