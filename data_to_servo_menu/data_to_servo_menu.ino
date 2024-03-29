#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo upper_rot;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


int angle_arm, angle_forearm, angle_hand, rot_hand, rot_shoulder, claw_on_off;
int rot_upper=10;
int INPUT_SIZE = 30;
char tempChars[21];
int winkels[4];
int data[7];
String msg;
char buffer[27];

int ledPinAC = 24;  //grün
int ledPin90= 28;   //gelb
int ledPinStop= 32;  //rot
int inPinAC= 22;    // pushbutton connected to digital pin 7
int inPin90= 26; 
int inPinStop= 30;
boolean val_AC= false;      // variable to store the read value
boolean val_90= false;
boolean val_Stop= true;

void setup() {

  pinMode(ledPinAC, OUTPUT);
  pinMode(ledPin90, OUTPUT);
  pinMode(ledPinStop, OUTPUT);
  pinMode(inPinAC, INPUT_PULLUP); 
  pinMode(inPin90, INPUT_PULLUP);
  pinMode(inPinStop, INPUT_PULLUP);
  
  Serial.begin(38400);
  Serial.println("<Arduino is ready>");
  
  base.attach(11);
  shoulder.attach(10);
  upper_rot.attach(9);     
  elbow.attach(8);
  wrist_rot.attach(6);
  wrist_ver.attach(5);
  gripper.attach(3);

  rot_shoulder = 34;
  angle_arm = 70;
  rot_upper = 85;
  angle_forearm = 1;
  angle_hand = 105;
  rot_hand = 87;
  claw_on_off = 4;  //70:zu 30:offen
 
}

void loop() {

  if(digitalRead(inPinStop)==LOW){
    val_AC = false;
    val_90=false;
    val_Stop=true;
    delay(10);
  }
    
  else if(digitalRead(inPinAC)==LOW){
    val_AC = true;
    val_90=false;
    val_Stop=false;
    delay(10);
  }

  else if(digitalRead(inPin90)==LOW){
    val_90 = true;
    val_AC=false;
    val_Stop=false;
    delay(10);
  }
  
  digitalWrite(ledPinStop,val_Stop);
  digitalWrite(ledPin90,val_90);
  digitalWrite(ledPinAC,val_AC);

  if(val_90==true){
    angle_90();
  }

  else if(val_AC==true){
    recvWithEndMarker();

    rot_shoulder = data[0];
    angle_arm = data[1];
    rot_upper = data[2];
    angle_forearm = data[3];
    angle_hand = data[4];
    rot_hand = data[5];
    claw_on_off = data[6];
  } 
  
    
    base.write(rot_shoulder);
    shoulder.write(angle_arm);
    upper_rot.write(rot_upper);
    elbow.write(angle_forearm);
    wrist_rot.write(rot_hand);
    wrist_ver.write(angle_hand);
    gripper.write(claw_on_off);
}

void recvWithEndMarker() {
  while (Serial.available() > 0) {


    //aktuelles Zeichen einlesen
    msg = Serial.readStringUntil('\n');

    Serial.println(msg);
    msg.toCharArray(buffer, 27);
    Serial.println(msg);
    strcpy(tempChars, buffer);




    char * buffer; // this is used by strtok() as an index

    buffer = strtok(tempChars, ",");
    data[0] = atoi(buffer);

    buffer = strtok(NULL, ","); // this continues where the previous call left off
    data[1] = atoi(buffer);     // convert this part to an integer

    buffer = strtok(NULL, ",");
    data[2] = atoi(buffer);

    buffer = strtok(NULL, ",");
    data[3] = atoi(buffer);

    buffer = strtok(NULL, ",");
    data[4] = atoi(buffer);

    buffer = strtok(NULL, ",");
    data[5] = atoi(buffer);

    buffer = strtok(NULL, ",");
    data[6] = atoi(buffer);


//               Serial.print("Data 0:");
//               Serial.println(data[0]);
//               Serial.print(" Data 1:");
//               Serial.println(data[1]);
//               Serial.print(" Data 2:");
//               Serial.println(data[2]);
//               Serial.print(" Data 3:");
//               Serial.println(data[3]);
//               Serial.print(" Data 4:");
//               Serial.println(data[4]);
//               Serial.print(" Data 5:");
//               Serial.println(data[5]);
//               Serial.print("Data 6:");
//               Serial.println(data[6]);
//               
    

  }
}


void angle_90(){
  rot_shoulder = 90;
  angle_arm = 90;
  rot_upper = 90;
  angle_forearm = 90;
  angle_hand = 90;
  rot_hand = 90;
  claw_on_off = 70;  //70:zu 30:offen
}
