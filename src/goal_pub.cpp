#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>

class goal{
private:
    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::Publisher finish_flag_pub;
    ros::Subscriber sub;

    geometry_msgs::PoseStamped goal1;
    geometry_msgs::PoseStamped goal2;

    const double SAFETY_DISTANCE;

    nav_msgs::Odometry odom;

    int mode;
    int count;
public:
    goal(): SAFETY_DISTANCE(1.0){
        pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 100);
        finish_flag_pub = nh.advertise<std_msgs::Bool>("finish_flag", 100);
        sub = nh.subscribe("odom", 1, &goal::callback, this);

        mode = 1;
        count = 0;

        goal1.header.frame_id = "map";
        goal1.header.stamp = ros::Time::now();
        goal1.pose.position.x = 15;
        goal1.pose.position.y = 26;
        goal1.pose.orientation.w = 1;

        goal2.header.frame_id = "map";
        goal2.header.stamp = ros::Time::now();
        goal2.pose.position.x = 15;
        goal2.pose.position.y = 4;
        goal2.pose.orientation.w = 1;
    }

    void callback(const nav_msgs::Odometry::ConstPtr &msg){
        odom = *msg;

        if(mode == 1){
            if(distance(goal1.pose, odom.pose.pose) < SAFETY_DISTANCE){
                mode = 2;
                count++;
            }
        }else if (mode == 2){
            if(distance(goal2.pose, odom.pose.pose) < SAFETY_DISTANCE){
                mode = 1;
                count++;
            }
        }
        std::cout<<"flag"<<std::endl;
    }

    void publish(){
        if(getFinishFlag()){
            if(mode == 1)
                pub.publish(goal1);
            else if(mode == 2)
                pub.publish(goal2);
        }
        
        std_msgs::Bool flag;
        flag.data = getFinishFlag();
        finish_flag_pub.publish(flag);
    }

    double distance(geometry_msgs::Pose p1, geometry_msgs::Pose p2){
        return sqrt(pow((p1.position.x - p2.position.x),2) + pow((p1.position.y - p2.position.y), 2));
    }

    bool getFinishFlag(){
        if(count != 0)
            return false;
        else
            return true;
    }
};


int main(int argc, char** argv){
    ros::init(argc, argv, "goal_pub");
    goal goal;

    ros::Rate loop_rate(0.5);

    while(ros::ok() && goal.getFinishFlag()){
        ros::spinOnce();
        goal.publish();
        loop_rate.sleep();
    }

    return 0;
}