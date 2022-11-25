#!/bin/bash

gnome-terminal -- roslaunch mando_simulator mando_eval.launch
sleep 10
gnome-terminal -- rosrun teleop_twist_keyboard teleop_twist_keyboard.py
# gnome-terminal -- rqt