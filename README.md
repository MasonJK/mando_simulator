# Mando Target Following Robot Simulator
Simulator designed to test robot's capability to follow target in human environment. The humans are generated using pedsim_ros package, pedestrian simulator based on social force model, and the robot is provided by Mando Mobile Robot package, which is a implementation of scout mini robot.

## Software Info.  
https://catnip-archive.tistory.com/entry/VMware-VMware%EC%97%90-%EA%B0%80%EC%83%81%EB%A8%B8%EC%8B%A0-%EC%B6%94%EA%B0%80%ED%95%98%EA%B8%B0feat-Ubuntu-1804-LTS    
1. ubuntu : 18.04
2. ROS : melodic version

## Required Package Installation
### pedsim_ros
```
cd [workspace]/src
git clone https://github.com/srl-freiburg/pedsim_ros.git  
cd pedsim_ros
git submodule update --init --recursive
cd ../..
catkin build -c  # or catkin_make
```
### mando_mobile_robot
```
cd [workspace]/src
git clone https://github.com/MANDO-ROBOT/mando_mobile_robot.git
cd ../..
catkin build -c  # or catkin_make
```

## Usage
### Simulator launch
```
roslaunch mando_simulator mando_target_follower.launch 
```
### Target controller
rosrun teleop_twist_keyboard teleop_twist_keyboard.py cmd_vel:=target/cmd_vel
```
