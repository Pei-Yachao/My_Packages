#!/usr/bin/env python


import rospy
import roslib
from std_msgs.msg import Float32
from geometry_msgs.msg import Twist 

#############################################################
#############################################################
class TwistToMotors():
#############################################################
#############################################################

    #############################################################
    def __init__(self):
    #############################################################
        rospy.init_node("merge_twist")
        nodename = rospy.get_name()
       # rospy.loginfo("%s started" % nodename)
    
           
        self.pub_lmotor = rospy.Publisher('cmd_vel_', Twist,queue_size=10)

        rospy.Subscriber('cmd_vel', Twist, self.keyboardCallback)
        rospy.Subscriber('cmd_vel_move_base', Twist, self.move_baseCallback)
        
    
        self.rate = rospy.get_param("~rate", 50)
        self.timeout_ticks = rospy.get_param("~timeout_ticks", 2)

        self.merge_cmd_vel = Twist()
        self.dx = 0
        self.dy = 0
        self.dz = 0
        
    #############################################################
    def spin(self):
    #############################################################
    
        r = rospy.Rate(self.rate)
        idle = rospy.Rate(10)
        then = rospy.Time.now()
        self.ticks_since_target = self.timeout_ticks
    
        ###### main loop  ######
        while not rospy.is_shutdown():
        
            while not rospy.is_shutdown() and self.ticks_since_target < self.timeout_ticks:
                self.spinOnce()
                r.sleep()
            idle.sleep()
                
    #############################################################
    def spinOnce(self):
    #############################################################
        self.merge_cmd_vel.linear.x = self.dx;
        self.merge_cmd_vel.linear.y = self.dy;
        self.merge_cmd_vel.angular.z = self.dz;
        self.pub_lmotor.publish(self.merge_cmd_vel)

            
        self.ticks_since_target += 1

    #############################################################
    def keyboardCallback(self,msg):
    #############################################################
        # rospy.loginfo("-D- keyboardCallback: %s" % str(msg))
        self.ticks_since_target = 0
        self.dx = msg.linear.x
        self.dy = msg.linear.y
    
    #############################################################
    def move_baseCallback(self,msg):
    #############################################################
        # rospy.loginfo("-D- keyboardCallback: %s" % str(msg))
        self.ticks_since_target = 0
        self.dz = msg.angular.z
    
#############################################################
#############################################################
if __name__ == '__main__':
    """ main """
    twistToMotors = TwistToMotors()
    twistToMotors.spin()
