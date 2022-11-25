#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <math.h>
#include <iostream>


class SetGoals{
private:
    ros::NodeHandle nh;
    ros::Subscriber odom_target_sub;
    ros::Subscriber odom_robot_sub;
    ros::Publisher goal_pub;
    nav_msgs::Odometry odom_target;
    nav_msgs::Odometry odom_robot;
    double safety_radius;
    int sequence;
public:
    SetGoals(){
        odom_target_sub = nh.subscribe("/target/odom", 1, &SetGoals::TargetCallback, this);
        odom_robot_sub = nh.subscribe("/robot/odom", 1, &SetGoals::RobotCallback, this);
        goal_pub = nh.advertise<geometry_msgs::PoseStamped>("robot/move_base_simple/goal", 10);
        sequence = 0;
        // nh.getParam("/safety_radius", safety_radius);
        ros::param::get("~safety_radius", safety_radius);
        // ros::param::get("/follow_target/safety_radius", safety_radius);
    }
    void TargetCallback(const nav_msgs::Odometry::ConstPtr& msg){
        odom_target = *msg;
    }
    void RobotCallback(const nav_msgs::Odometry::ConstPtr msg){
        odom_robot = *msg;
    }

    double CalculateAngle(){
        double angle;
        if(odom_target.pose.pose.position.x == odom_robot.pose.pose.position.x){
            if(odom_target.pose.pose.position.y >= odom_robot.pose.pose.position.y)
                angle = M_PI/2;
            else
                angle = -M_PI/2;
        }else{
            angle = atan2(odom_target.pose.pose.position.y - odom_robot.pose.pose.position.y, odom_target.pose.pose.position.x - odom_robot.pose.pose.position.x);
        }
        return angle;
    }

    geometry_msgs::Quaternion ConvertToQuaternion(double euler){
        tf2::Quaternion tf2Quaternion;
        geometry_msgs::Quaternion geoQuaternion;

        tf2Quaternion.setRPY(0,0,euler);
        tf2::convert(tf2Quaternion, geoQuaternion);
        return geoQuaternion;
    }

    void PublishGoal(){
        double euler = CalculateAngle();
        geometry_msgs::PoseStamped goal;

        goal.header.frame_id = "map";
        goal.header.seq = sequence++;
        goal.header.stamp = ros::Time::now();
        goal.pose.position.x = odom_target.pose.pose.position.x - safety_radius*cos(euler);
        goal.pose.position.y = odom_target.pose.pose.position.y - safety_radius*sin(euler);
        goal.pose.position.x = odom_target.pose.pose.position.x - safety_radius*cos(euler);
        goal.pose.position.y = odom_target.pose.pose.position.y - safety_radius*sin(euler);

        goal.pose.orientation = ConvertToQuaternion(euler);
        goal_pub.publish(goal);
    }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "follow_target");
    SetGoals goal_setter;

    ros::Rate loop_rate(1);
    while(ros::ok()){
        ros::spinOnce();
        goal_setter.PublishGoal();
        loop_rate.sleep();
    }
}