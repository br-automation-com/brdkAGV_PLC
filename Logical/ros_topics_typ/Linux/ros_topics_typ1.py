# Use import and sys.path.insert if this .py file is moved.
# The path should point to the directory containing _libros_topics_typ.so
# import sys
# sys.path.insert(1, 'ros_topics_typ/Linux/build')
import libros_topics_typ
from math import pi, cos, sin

from functools import partial
import rospy
import tf
import socket
from geometry_msgs.msg import Quaternion, Twist
from nav_msgs.msg import Odometry


__author__ = "buhl@brommeweb.dk (Jacob Buh)"

"""
libros_topics_typ datamodel features:

initialize and setup callback handler:
    ros_topics_typ_datamodel = libros_topics_typ.libros_topics_typ_init()
    handler = ros_topics_typEventHandler()
    libros_topics_typ.add_event_handler(ros_topics_typ_datamodel, handler)

main methods:
    ros_topics_typ_datamodel.connect()
    ros_topics_typ_datamodel.disconnect()
    ros_topics_typ_datamodel.process()
    ros_topics_typ_datamodel.set_operational()
    ros_topics_typ_datamodel.dispose()
    ros_topics_typ_datamodel.get_nettime() : (int32_t) get current nettime

def user callbacks in class ros_topics_typEventHandler:
    on_connected
    on_disconnected
    on_operational

boolean values:
    ros_topics_typ_datamodel.is_connected
    ros_topics_typ_datamodel.is_operational

logging methods:
    ros_topics_typ_datamodel.log.error(str)
    ros_topics_typ_datamodel.log.warning(str)
    ros_topics_typ_datamodel.log.success(str)
    ros_topics_typ_datamodel.log.info(str)
    ros_topics_typ_datamodel.log.debug(str)
    ros_topics_typ_datamodel.log.verbose(str)

dataset odemetry:
    ros_topics_typEventHandler:on_change_odemetry : void(void) user callback function
    ros_topics_typ_datamodel.odemetry.nettime : (int32_t) nettime @ time of publish
    ros_topics_typ_datamodel.odemetry.value : (ros_topic_odemety_typ)  actual dataset values

dataset twist:
    ros_topics_typ_datamodel.twist.publish()
    ros_topics_typ_datamodel.twist.value : (ros_topic_twist_typ)  actual dataset values

dataset config:
    ros_topics_typ_datamodel.config.publish()
    ros_topics_typ_datamodel.config.value : (ros_config_typ)  actual dataset values
"""

# create odometry topic for ROS
class EncoderOdom:
    def __init__(self):
  
        self.odom_pub = rospy.Publisher('/odom', Odometry, queue_size=10)
        self.last_enc_time = rospy.Time.now()

    @staticmethod
    def normalize_angle(angle):
        while angle > pi:
            angle -= 2.0 * pi
        while angle < -pi:
            angle += 2.0 * pi
        return angle

    def publish_odom(self, cur_x, cur_y, cur_theta, vx, vth):
        quat = tf.transformations.quaternion_from_euler(0, 0, cur_theta)
        current_time = rospy.Time.now()
        
        br = tf.TransformBroadcaster()
        br.sendTransform((cur_x, cur_y, 0),
                         tf.transformations.quaternion_from_euler(0, 0, cur_theta),
                         current_time,
                         "base_link",
                         "odom")

        odom = Odometry()
        odom.header.stamp = current_time
        odom.header.frame_id = 'odom'

        odom.pose.pose.position.x = cur_x
        odom.pose.pose.position.y = cur_y
        odom.pose.pose.position.z = 0.0
        odom.pose.pose.orientation = Quaternion(*quat)

        odom.pose.covariance[0] = 0.01
        odom.pose.covariance[7] = 0.01
        odom.pose.covariance[14] = 99999
        odom.pose.covariance[21] = 99999
        odom.pose.covariance[28] = 99999
        odom.pose.covariance[35] = 0.01

        odom.child_frame_id = 'base_link'
        odom.twist.twist.linear.x = vx
        odom.twist.twist.linear.y = 0
        odom.twist.twist.angular.z = vth
        odom.twist.covariance = odom.pose.covariance

        self.odom_pub.publish(odom)
       
class ros_topics_typEventHandler(libros_topics_typ.ros_topics_typEventHandler):

    def __init__(self):
        libros_topics_typ.ros_topics_typEventHandler.__init__(self)
        self.encodm = EncoderOdom()

    def on_connected(self):
        self.ros_topics_typ_datamodel.log.success("python ros_topics_typ_datamodel connected!")
    
    def on_disconnected(self):
        self.encodm.publish_odom(self.ros_topics_typ_datamodel.odemetry.value.pose.pose.position.x,self.ros_topics_typ_datamodel.odemetry.value.pose.pose.position.y, self.ros_topics_typ_datamodel.odemetry.value.pose.pose.orientation.z, 0, 0)

    def on_operational(self):
        self.ros_topics_typ_datamodel.config.value.maxSpeed = float(rospy.get_param("~max_speed", "2.0"))
        self.ros_topics_typ_datamodel.config.value.minSpeed = float(rospy.get_param("~min_speed", "2.0"))
        self.ros_topics_typ_datamodel.config.value.baseWidt = float(rospy.get_param("~base_width", "0.53"))
        self.ros_topics_typ_datamodel.config.publish()
        #self.TICKS_PER_METER = float(rospy.get_param("~tick_per_meter", "105860"))
 
    def on_change_odemetry(self):
        self.ros_topics_typ_datamodel.log.verbose("python dataset odemetry changed!")
        # self.ros_topics_typ_datamodel.log.debug("on_change: ros_topics_typ_datamodel.odemetry: " + str(self.ros_topics_typ_datamodel.odemetry.value))
        self.encodm.publish_odom(self.ros_topics_typ_datamodel.odemetry.value.pose.pose.position.x,self.ros_topics_typ_datamodel.odemetry.value.pose.pose.position.y, self.ros_topics_typ_datamodel.odemetry.value.pose.pose.orientation.z, self.ros_topics_typ_datamodel.odemetry.value.twist.twist.linear.x, self.ros_topics_typ_datamodel.odemetry.value.twist.twist.angular.z) 

class Node:
    def __init__(self):
        rospy.init_node("motor_controller_node")
        rospy.on_shutdown(self.shutdown)
        rospy.loginfo("Connecting to motor controller")
        
        #exOs communication
        self.ros_topics_typ_datamodel = libros_topics_typ.libros_topics_typ_init()
        self.handler = ros_topics_typEventHandler()
        libros_topics_typ.add_event_handler(self.ros_topics_typ_datamodel, self.handler)
        self.ros_topics_typ_datamodel.connect()
    
        self.VEL_TOPIC = '/'+rospy.get_param("~vel_topic", "cmd_vel")    
        self.last_set_speed_time = rospy.get_rostime()
        rospy.Subscriber(self.VEL_TOPIC, Twist, self.vel_callback)

     
        rospy.sleep(1)

        rospy.logdebug("max_speed %f", self.MAX_SPEED)
        rospy.logdebug("min_speed %f", self.MIN_SPEED)
        rospy.logdebug("ticks_per_meter %f", self.TICKS_PER_METER)
        rospy.logdebug("base_width %f", self.BASE_WIDTH)
        rospy.logdebug("OPC UA topic prefix %s", self.OPCUA_TOPIC_PREFIX)
        rospy.logdebug("vel topic %s", self.VEL_TOPIC)
       
    def run(self):
        rospy.loginfo("Starting motor drive")
        r_time = rospy.Rate(10)
           
        while not rospy.is_shutdown():
            self.ros_topics_typ_datamodel.process()
            r_time.sleep()
            
    def vel_callback(self, twist):
        self.last_set_speed_time = rospy.get_rostime()
        rospy.logdebug('vel_callback')
        if self.ros_topics_typ_datamodel.is_connected:
            self.ros_topics_typ_datamodel.twist.value.angular.z = twist.angular.z
            self.ros_topics_typ_datamodel.twist.value.linear.x = twist.linear.x
            self.ros_topics_typ_datamodel.twist.publish()
            rospy.logdebug("Write to angular z: %f and linear x: %f",twist.linear.x,twist.angular.z)
        else:
            rospy.logdebug("Not connected to PLC")
 
    # TODO: need clean shutdown so motors stop even if new msgs are arriving
    def shutdown(self):
        rospy.loginfo("Shutting down")
        self.ros_topics_typ_datamodel.disconnect()
        self.ros_topics_typ_datamodel.dispose()
        


