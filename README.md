# Mando Target Following Robot Simulator
Simulator designed to test robot's capability to follow target in human environment. The humans are generated using pedsim_ros package(a pedestrian simulator based on social force model) and the robot is provided by Mando Mobile Robot package, which is a implementation of scout mini robot.

## Software Info.  
https://catnip-archive.tistory.com/entry/VMware-VMware%EC%97%90-%EA%B0%80%EC%83%81%EB%A8%B8%EC%8B%A0-%EC%B6%94%EA%B0%80%ED%95%98%EA%B8%B0feat-Ubuntu-1804-LTS    
1. ubuntu : 18.04
2. ROS : melodic version


## Settings
### rosdep init (if you haven't done it yet)
```
sudo rosdep init
rosdep update
```
### If having gazebo error 
1. Error in REST request 
   -> add 'export SVGA_VGPU10=0' in bashrc file
2. libcurl: (51) SSL: no alternative certificate subject name matches target host name 'api.ignitionfuel.org'
   -> cd ~/.ignition/fuel
   -> gedit config.yaml
   -> change 'url: https://api.ignitionfuel.org' to  'url: https://api.ignitionrobotics.org'


## Required Package Installation
### basic installation
```
sudo apt-get install ros-melodic-amcl \ 
sudo apt-get install ros-melodic-map-server \ 
sudo apt-get install ros-melodic-move-base \ 
sudo apt-get install ros-melodic-velodyne* \ 
sudo apt-get install ros-melodic-dwa-local-planner -y
```
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
### mando_gazebo
```
cd [workspace]/src
git clone https://github.com/MANDO-ROBOT/mando_gazebo.git
cd ../..
catkin_build -c # or catkin_make
```

## Usage
### Simulator launch
```
roslaunch mando_simulator mando_target_follower.launch 
```
### Target controller
```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py cmd_vel:=target/cmd_vel
```
