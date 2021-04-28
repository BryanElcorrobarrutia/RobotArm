#include <Servo.h>

Servo waist;
Servo arm;
Servo laser;
const int num_joints = 3;
int q[num_joints]; 
int index = 0;


void setup() {
  waist.attach(9,510,2500); 
  arm.attach(10,510,2500);
  laser.attach(11,510,2500);
  waist.write(90);
  arm.write(90);
  laser.write(0);

  Serial.begin(9600); 

  for (int i = 0; i < num_joints; i++){
    q[i] = 0;
  }
}


void flush(){
  /* Empties the left over bytes in the serial buffer. */
  while (Serial.available() > 0){
    Serial.read();
  }
}


void set_configuration(int q1, int q2, int q3){
  /* Sets the robot's joint angles.
   * 
   * Parameters:
   *  q1: The angle to set the waist axis to.
   *  q2: The angle to set the arm axis to.
   *  q3: The anggle to set the laser/wrist axis to. 
   */

  // Checks if the joint angles are within the correct range [0,180] before updating. 
  if (q1 >= 0 && q1 <= 180){
    waist.write(q1);
  }
  if (q2 >= 0 && q2 <= 180){
    arm.write(q2);
  }
  
  if (q3 >= 0 && q3 <= 180){
    laser.write(q3);
  }
  
}


void loop() {
 
  if (Serial.available() > 0){
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9'){
      q[index] = q[index] * 10 + ch - '0';
    }
    else if (ch == ','){ // expecting only 3 commas in the message.
      index += 1;
    }
    else{

      Serial.println("Configuration set to " + String(q[0]) + ", " + String(q[1]) + ", " + String(q[2]));
      set_configuration(q[0], q[1], q[2]);
      index = 0;
      for (int i = 0; i < num_joints; i++){
        q[i] = 0;
      }
    }
   }
}
