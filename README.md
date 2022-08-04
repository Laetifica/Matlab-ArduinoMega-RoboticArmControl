# Matlab-ArduinoMega-RoboticArmControl
 Matlab scripts and Arduino sketches for controlling a robotic arm.

## Getting Started
These instructions are for the robotic arm used in MECH 453 with 3 joints and a grasper. The arduino script converts joint angles that you specify in degrees into a pulse length, expressed as an integer (typically between 200 and 400, but every individual servo is a little unique).

Once you've assembled your robot and plugged your servos into the servo shield (pay attention to the orientation of the servo plugs here, aligning ground on the cabled (brown or black) to ground on the board), load servoRangeTest.ino onto your Arduino Mega.

Ensure that your mega is plugged into the usb port, and that the power leads are connected to the molex connector on the servo shield with the correct polarity.

When you load the program, the arm should move to a neutral position well between the limits of motion for each joint. If it does not, or is making loud grinding noises or alarming motions, turn it off (unplug power) and seek assistance.

If it reaches a neutral position, you should be able to open the serial monitor in your arduino client, set baud rate to 115200, and enter commands to move the joints by small increments:

a/d will control J0 right/left,
w/s will control J1 up/down,
r/f will control J2 up/down, and
q/e will control the grasper open/close.
Press enter to send your command.

If your servos respond well to commands, excellent! explore the range of motion in each direction, and when the mechanism binds or the servo stops responding, reverse direction until movement is detected. Note the pulselength displayed for that joint in the serial monitor. This is either your maximum or minimum pulselength for that joint, and you should record it along with the degree measurement it corresponds to. It may be a good idea to make your degree measurements and axes correspond with those given in the figures in assignment 4.

Once you have recorded pulselength and degree measurements for each extent of each joint, you can enter them in joint_angle_control.ino, save, and load joint_angle_control.ino onto your Mega.

At this point, you should be able to open array_angle_control.m in matlab, establish a connection, and see the robot move. You may replace the angles in angleData.txt to script other movements, as well as speeding up or slowing down the motion by altering the argument of the pause() function in array_angle_control.m.
