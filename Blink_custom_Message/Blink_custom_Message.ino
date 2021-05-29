/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <testing/Angles.h>

ros::NodeHandle  nh;

void messageCb( const testing::Angles& toggle_msg){
  if (toggle_msg.upper_rot == 10){
    digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
  }
}

ros::Subscriber<testing::Angles> sub("toggle_led", &messageCb );

void setup()
{ 
  nh.getHardware()->setBaud(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
