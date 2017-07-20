#include<Stepper.h>
#include<Servo.h>

#define ARDUINO  A1 //arduino交流
#define XINHAO   A0//蛋筒检查信号口
#define KAIGUAN  10  //舵机控制开关的
#define ICE_OPEN_1  0 //冰淇淋开口的直流电机口1,1高2第是打开阀门的
#define ICE_OPEN_2  1//冰淇淋开口的直流电机口2
//待测

#define DOOR_1   2       //门，1高2低是打开的
#define DOOR_2   3   //门
//待测

#define ICE_OPEN    0//冰淇淋机开关舵机角度,打开,待定
#define ICE_CLOSE   30//冰淇淋机开关舵机角度，关闭，待定

Stepper myStepper1(200, 4, 5, 6, 7); //旋转
Stepper myStepper2(200, 8, 12, 11, 13); //蛋筒调整,旋转

Servo myservo1;//舵机控制开关

void setup() {
  myStepper1.setSpeed(20);
  myStepper2.setSpeed(30);
  myservo1.attach(KAIGUAN);
  myservo1.write(ICE_CLOSE);//冰淇淋开关初始关闭，度数待定
  pinMode(ICE_OPEN_1, OUTPUT);
  digitalWrite(ICE_OPEN_1, LOW);
  pinMode(ICE_OPEN_2, OUTPUT);
  digitalWrite(ICE_OPEN_2, LOW);
}

void loop() {
  while (1) {
    if (analogRead(ARDUINO) > 500) {
      while (1) {
        if (analogRead(ARDUINO) < 500) {
          break;
        }
      }
      break;
    }
  }
  delay(500);
  myStepper1.step(30);//步数待测，转筒
  if (analogRead(XINHAO) < 500) {
    ice();//出冰淇淋全套
  }
  myStepper1.step(30);//步数待测，转筒，至门口
  while (1) {
    if (analogRead(XINHAO) > 500) {
      break;
    }
  }
  door_open();
  myStepper1.step(-60);//步数待测，转筒，从门口转回去
  door_close();
}

void ice() {
  myservo1.write(ICE_OPEN);//角度待定，控制开关，打开
  delay(1000);//先搅拌，时间未定

  digitalWrite(ICE_OPEN_1, HIGH);
  digitalWrite(ICE_OPEN_2, LOW);
  delay(500);//时间待测，打开阀门

  digitalWrite(ICE_OPEN_1, LOW);

  delay(500);//时间待测，出冰淇淋

  digitalWrite(ICE_OPEN_1, LOW);
  digitalWrite(ICE_OPEN_2, HIGH);
  delay(500);//时间待测，关闭阀门
  digitalWrite(ICE_OPEN_2, LOW);

  myservo1.write(ICE_CLOSE);//角度待定，控制开关，关闭
}

void door_open() {
  digitalWrite(DOOR_1, HIGH);
  digitalWrite(DOOR_2, LOW);
  delay(500);//时间待测，打开门

  digitalWrite(DOOR_1, LOW);
}
void door_close() {
  digitalWrite(DOOR_1, LOW);
  digitalWrite(DOOR_2, HIGH);
  delay(500);//时间待测，关闭门

  digitalWrite(DOOR_2, LOW);
}

