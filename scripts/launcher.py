#!/usr/bin/env python

from turtle import settiltangle
import roslaunch
import rosbag
import rospy
from std_msgs.msg import Bool

flag = True

def callback(msg):
    global flag 
    flag = msg.data

rospy.init_node('launcher', anonymous=True)
flag_sub = rospy.Subscriber("finish_flag", Bool, callback)

uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
roslaunch.configure_logging(uuid)

launch = roslaunch.parent.ROSLaunchParent(uuid, ["/home/junwoo/catkin_ws/src/mando_simulator/launch/mando_target_follower.launch"])

try:
    launch.start()
    rospy.sleep(10)
    launch.stop()
finally:
    rospy.sleep(10)
    print('hihello')



# for i in range(6):
#     launch.start()
#     rospy.loginfo("started")
#     print('hello' + str(i))
#     launch.shutdown()


# param setting
# rosbag setting
