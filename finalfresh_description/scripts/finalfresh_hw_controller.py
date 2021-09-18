#!/usr/bin/env python

import rospy
import sys
from std_msgs.msg import Float64
from sensor_msgs.msg import JointState
from std_srvs.srv import Empty, EmptyResponse

global ns 
ns = rospy.get_namespace()
print("Controller started with ns " + ns)

LID_OPEN = -1.57075
LID_CLOSED = 0.0

lid_pub = rospy.Publisher(
    rospy.names.ns_join(ns, "lid_position_controller/command"),
    Float64,
    queue_size=10
)

def open_bot_lid(req):
    rospy.loginfo("Opening Bot Lid")
    lid_pub.publish(LID_OPEN)
    return EmptyResponse()

def close_bot_lid(req):
    rospy.loginfo("Closing Bot Lid")
    lid_pub.publish(LID_CLOSED)
    return EmptyResponse()

if __name__ == "__main__":
    rospy.init_node("finalfresh_hw_controller")    
    rospy.Service('close_bot_lid', Empty, close_bot_lid)
    rospy.Service('open_bot_lid', Empty, open_bot_lid)
    rospy.spin()
