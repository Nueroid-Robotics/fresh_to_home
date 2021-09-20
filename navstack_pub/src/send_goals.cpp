#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
 
using namespace std;
 
// Action specification for move_base
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char** argv){
   
  // Connect to ROS
  ros::init(argc, argv, "simple_navigation_goals");
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
 
  // Wait for the action server to come up so that we can begin processing goals.
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  float villa[4][2] ={-0.5,4.5,-6.0,4.0,-6.3,-2.8,-3.0,1.0};
  int user_choice[4];
  /*int user_choice_2[2] =[-6,4];
  int user_choice_3[2] =[-6.3,-2.8];
  int user_choice_4[2] =[-3.0,1.0];*/

 // char choice_to_continue = 'Y';
  bool run = true;

  while(run) {

       // Ask the user where he wants the robot to go?
    cout << "\nWhere do you want the robot to go?" << endl;
    cout << "\n1 = Villa1" << endl;
    cout << "2 = Villa2" << endl;
    cout << "3 =  Villa3" << endl;
    cout << "4 =  Villa4" << endl;
    /*cout << "5 = Home Office" << endl;
    cout << "6 = Kitchen" << endl;*/
    cout << "\nEnter villa numbers in order: ";

    for (int i=0;i<4;i++){
    cin >> user_choice[i];
    }

     // Create a new goal to send to move_base 
    move_base_msgs::MoveBaseGoal goal;
 
    // Send a goal to the robot
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
         
    //bool valid_selection = true;

    for (int i=0; i<4; i++){

    int j=user_choice[i];

     cout << "\nGoal Location: Villa" <<user_choice[j]<<"\n" << endl;
        goal.target_pose.pose.position.x = villa[j][0];
	goal.target_pose.pose.position.y = villa[j][1];
        goal.target_pose.pose.orientation.w = 1.0;

        ROS_INFO("Sending goal");
    ac.sendGoal(goal);
 
    // Wait until the robot reaches the goal
    ac.waitForResult();
 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("The robot has arrived at the goal location");
    else
      ROS_INFO("The robot failed to reach the goal location for some reason");
    }
  }
   return 0;
}
