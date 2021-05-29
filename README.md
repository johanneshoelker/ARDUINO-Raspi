The previous Arduino Sketch is rooted in data_to_servo_menu. Based on this a copy is made which contains a ros implementation.

Arduino IDE is supposed to run in a setup with XMing and Putty with an SSH connection on Windows 10.
The ros library is made with the command (delete old one before):
rosrun rosserial_arduino make_libraries.py /home/ros/Arduino/libraries
and afterwards the following changes should be made in ArduinoHardware.h:
Serial1 -> Serial	(because of Arduino Due. The according ArduinoHardware.h is attached in arduino_ws)
In order to communicate with the Arduino the following command should be played:
rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0 _baud:=115200

