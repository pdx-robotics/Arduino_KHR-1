# KHR-1 With Arduino
The KHR-1 is made by Kondo Kagaku (近藤科学).

It will be modified to work with a Bluetooth module and an Arduino Board.

#### KHR-1 Hardware:
- Servos: KRS-784 ICS
- Servo Control Board: RCB-1

We will not be using the RCB-1 for this project. Servo Control will be done by
  Arduino

****
#### Servo Mapping

The Servos are mapped for reference as seen below:
![alt text](https://github.com/pdx-robotics/Arduino_KHR-1/blob/master/KHR-1_servonumbering_modified.png)

| Part | Right | Left |
|----|:-----:|:----:|
| Shoulder Pitch | 1  | 2  |
| Shoulder Roll  | 3  | 4  |
| Elbow          | 5  | 6  | 
| Hip Roll       | 7  | 8  |
| Hip Pitch      | 9  | 10 |
| Knee           | 11 | 12 |
| Ankle Pitch    | 13 | 14 | 
| Ankle Roll     | 15 | 16 |
| Head Pan       | 17 |

##### Part Terminology

###### Pitch and Roll
The terminology of "pitch" and "roll" is used to describe the different axes
that an aircraft in flight can freely rotate about. Here we take advantage of
these names to help us describe the movements of a single joint made up of many servos/motors.


* Pitch:
Aircraft: nose up or down about an axis from wing to wing
Humanoid: face up or down about an axis from hand to hand (see image above)

* Roll:
Aircraft: rotation about an axis running from nose to tail
Humanoid: rotation about an axis running from front to back 

* Yaw: (not needed for KHR-1)
Aircraft: nose left or right about an axis running up and down
Humanoid: face left or right about an ais running up and down

