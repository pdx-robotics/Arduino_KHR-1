# KHR-1 With Arduino
The KHR-1 is made by Kondo Kagaku (近藤科学).

It will be modified to work with a Bluetooth module and an Arduino Board.

## KHR-1 Hardware:
- Servos: KRS-784 ICS
- Servo Control Board: RCB-1

We will not be using the RCB-1 for this project. Servo Control will be done by Arduino

****
## Servo Mapping
The Servos are mapped for reference as seen below:

![KHR-1_ServoChannels.png](https://github.com/pdx-robotics/Arduino_KHR-1/blob/08d8fdf9f8c0942e947cd8a796170fd26b10ed48/KHR-1_ServoChannels.png)

| Part | Left | Right|
|----|:-----:|:----:|
| Shoulder Pitch |   0   |  15   |
| Shoulder Roll  |   1   |  14   |
| Elbow          |   2   |  13   |
| Hip Roll       |   3   |  12   |
| Hip Pitch      |   4   |  11   |
| Knee           |   5   |  10   |
| Ankle Pitch    |   6   |   9   |
| Ankle Roll     |   7   |   8   |
| Head Pan       |  ???  |

### Part Terminology

#### Pitch and Roll
The terminology of "pitch" and "roll" is used to describe the different axes
that an aircraft in flight can freely rotate about. Here we take advantage of
these names to help us describe the movements of a single joint made up of many servos/motors.


##### Pitch:
- Aircraft: nose up or down about an axis from wing to wing
- Humanoid: face up or down about an axis from hand to hand (see image above)

##### Roll:
- Aircraft: rotation about an axis running from nose to tail
- Humanoid: rotation about an axis running from front to back 

##### Yaw: (not needed for KHR-1)
- Aircraft: nose left or right about an axis running up and down
- Humanoid: face left or right about an axis running up and down

