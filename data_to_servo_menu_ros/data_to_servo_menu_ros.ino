#include <ros.h>
#include <Servo.h>
#include <testing/Angles.h>
ros::NodeHandle nh;

Servo base;
Servo shoulder;
Servo elbow;
Servo upper_rot;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


int angle_arm, angle_forearm, angle_hand, rot_hand, rot_shoulder, claw_on_off,rot_upper;
//int INPUT_SIZE = 30;
//char tempChars[21];
//int winkels[4];
//int data[7];
//String msg;
//char buffer[27];

int ledPinAC = 24;  //rot
int ledPin90= 28;   //gelb
int ledPinOff= 32;  //grün
int inPinAC= 22;    // pushbutton connected to digital pin 7
int inPin90= 26; 
int inPinOff= 30;
boolean val_AC= false;      // variable to store the read value
boolean val_90= false;
boolean val_Off= true;

void servo_cb( const testing::Angles& cmd_msg){
  rot_shoulder=cmd_msg.base;
  angle_arm=cmd_msg.shoulder;
  rot_upper=cmd_msg.upper_rot;
  angle_forearm=cmd_msg.elbow;
  rot_hand=cmd_msg.wrist_rot;
  angle_hand=cmd_msg.wrist_ver;
  claw_on_off=cmd_msg.gripper;
}

//ros::Publisher chatter("arduino_response", &str_msg);
ros::Subscriber<testing::Angles> sub("servo", servo_cb);

void setup() {
  pinMode(ledPinAC, OUTPUT);
  pinMode(ledPin90, OUTPUT);
  pinMode(ledPinOff, OUTPUT);
  pinMode(inPinAC, INPUT_PULLUP); 
  pinMode(inPin90, INPUT_PULLUP);
  pinMode(inPinOff, INPUT_PULLUP);

  pinMode(13, OUTPUT);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  //nh.advertise(chatter);
  nh.subscribe(sub);

  base.attach(11);
  shoulder.attach(10);
  upper_rot.attach(2);     
  elbow.attach(8);
  wrist_rot.attach(6);
  wrist_ver.attach(5);
  gripper.attach(3);
}

void loop() {
  angle_down();
  
  if(digitalRead(inPinAC)==LOW){
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led 
    val_AC = true;
    val_Off=false;
    delay(10);
  }

  if(digitalRead(inPin90)==LOW){
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led 
    val_90 = true;
    val_Off=false;
    delay(10);
  }

  digitalWrite(ledPinOff,val_Off);
  digitalWrite(ledPin90,val_90);
  digitalWrite(ledPinAC,val_AC);
  
  if(val_90==true){
    digitalWrite(ledPinOff,LOW);
    while(val_Off==LOW){
      angle_90();
      if(digitalRead(inPinOff)==LOW){
        val_Off = true;
        delay(10);
      }
    }
  }

  else if(val_AC==true){
    digitalWrite(ledPinOff,LOW);
    while(val_Off==LOW){
      recvWithEndMarker();
      if(digitalRead(inPinOff)==LOW){
        val_Off = true;
        delay(10);
      }
    }
  }
  val_AC=false;
  val_90=false;
  val_Off=true;
  //delay(1);
}

void recvWithEndMarker() {
  nh.spinOnce();
  delay(1);
  base.write(rot_shoulder);
  shoulder.write(angle_arm);
  upper_rot.write(rot_upper);
  elbow.write(angle_forearm);
  wrist_rot.write(rot_hand);
  wrist_ver.write(angle_hand);
  gripper.write(claw_on_off);
}

void angle_down(){
  rot_shoulder = 10;
  angle_arm = 10;
  rot_upper = 10;
  angle_forearm = 10;
  angle_hand = 10;
  rot_hand = 10;
  claw_on_off = 30;  //70:zu 30:offen
  
  base.write(rot_shoulder);
  shoulder.write(angle_arm);
  upper_rot.write(rot_upper);
  elbow.write(angle_forearm);
  wrist_rot.write(rot_hand);
  wrist_ver.write(angle_hand);
  gripper.write(claw_on_off);
}

void angle_90(){
  rot_shoulder = 90;
  angle_arm = 90;
  rot_upper = 90;
  angle_forearm = 90;
  angle_hand = 90;
  rot_hand = 90;
  claw_on_off = 70;  //70:zu 30:offen
  
  base.write(rot_shoulder);
  shoulder.write(angle_arm);
  upper_rot.write(rot_upper);
  elbow.write(angle_forearm);
  wrist_rot.write(rot_hand);
  wrist_ver.write(angle_hand);
  gripper.write(claw_on_off);
}
