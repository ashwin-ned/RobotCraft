#include <iostream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"


class TurtleController
{
private:
	ros::NodeHandle n;
    ros::Publisher cmd_vel_pub;
    ros::ServiceServer pause_server;
    //ros::Subscribe pose_subs;

    //turtlesim::Pose latest_pose;

    float linear_vel;
    float angular_vel;

    bool is_moving;

    geometry_msgs::Twist calculateCommand()
    {
        auto msg = geometry_msgs::Twist();

        if(this->is_moving){
        	//commandUpdate();

        // TODO: Control code goes here
        	msg.linear.x = 2.0; // [m/s]
        	msg.angular.z = 1.3; // [rad/s]
        }
        

        return msg;
    }


    bool flip(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res){
    	this->is_moving =! (this->is_moving);

    	return true;
    }

        
    /*
    void poseUpdate(const turtlesim::Pose::ConstPtr& msg){

    	this->latest_pose.x = msg.x;
    	this->latest_pose.y = msg.y;
    	this->latest_pose.theta = msg.theta;
    	this->latest_pose.linear_velocity = msg.linear_velocity;
    	this->latest_pose.angular_velocity = msg.angular_velocity;
    }

    void commandUpdate()
    {
    	this->linear_vel = 0;
    	this->angular_vel = 0;
    }
    */

public:
    TurtleController(){
        // Initialize ROS
        this->is_moving = true;
        this->n = ros::NodeHandle();

        this->linear_vel = 0;
        this->angular_vel = 0;
        

        // Create a publisher object, able to push messages
        this->cmd_vel_pub = this->n.advertise<geometry_msgs::Twist>("cmd_vel", 5);

        this->pause_server = this->n.advertiseService("pause_service", &TurtleController::flip, this);
        // TODO
        auto priv_nh = ros::NodeHandle("~");
        priv_nh.getParam("linear_vel", this->linear_vel);
        priv_nh.getParam("angular_vel", this->angular_vel);

        //this->pose_sub = n.subscribe("pose",10,poseUpdate)
    }

    void run(){
        // Send messages in a loop
        ros::Rate loop_rate(10);
        while (ros::ok())
        {
            // Calculate the command to apply
            auto msg = calculateCommand();

            // Publish the new command
            this->cmd_vel_pub.publish(msg);
            // TODO
            ros::spinOnce();
            // And throttle the loop
            loop_rate.sleep();
        }
    }

};


int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "talker");

    // Create our controller object and run it
    auto controller = TurtleController();
    controller.run();

    // And make good on our promise
    return 0;
}