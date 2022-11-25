#!/bin/bash
rosservice call /finish_trajectory 0
rosservice call /write_state "{filename: '${HOME}/catkin_ws/src/mando_simulator/maps/corridor_map.pbstream'}" 
echo "Map saved to ${HOME}/catkin_ws/src/mando_simulator/maps/corridor_map.pbstream"