#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

class SetGoals{
private:
    ros::NodeHandle nh;
    ros::Subscriber odom_target_sub;
    ros::Publisher goal_pub;
    nav_msgs::Odometry odom_target;
public:
    SetGoals(){
        odom_target_sub = nh.subscribe("/target/odom", 1, &SetGoals::Callback, this);
        goal_pub = nh.advertise<geometry_msgs::PoseStamped>("robot/move_base_simple/goal", 10);
    }
    void Callback(const nav_msgs::Odometry::ConstPtr& msg){
        odom_target = *msg;
        geometry_msgs::PoseStamped goal;
        goal.header = odom_target.header;
        goal.header.frame_id = "map";
        goal.pose = odom_target.pose.pose;
        goal.pose.position.x--;
        goal.pose.position.y--;
        goal_pub.publish(goal);
    }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "follow_target");
    SetGoals goal_setter;

    ros::Rate loop_rate(1);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
}