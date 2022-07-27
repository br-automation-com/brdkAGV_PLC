# Use import and sys.path.insert if this .py file is moved.
# The path should point to the directory containing _libros_topics_typ.so
# import sys
# sys.path.insert(1, 'ros_topics_typ/Linux/build')
import libros_topics_typ

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

class ros_topics_typEventHandler(libros_topics_typ.ros_topics_typEventHandler):

    def __init__(self):
        libros_topics_typ.ros_topics_typEventHandler.__init__(self)

    def on_connected(self):
        self.ros_topics_typ_datamodel.log.success("python ros_topics_typ_datamodel connected!")

    # def on_disconnected(self):
    #     self.ros_topics_typ_datamodel. ..

    # def on_operational(self):
    #     self.ros_topics_typ_datamodel. ..

    def on_change_odemetry(self):
        self.ros_topics_typ_datamodel.log.verbose("python dataset odemetry changed!")
        # self.ros_topics_typ_datamodel.log.debug("on_change: ros_topics_typ_datamodel.odemetry: " + str(self.ros_topics_typ_datamodel.odemetry.value))
        
        # Your code here...
    

ros_topics_typ_datamodel = libros_topics_typ.libros_topics_typ_init()

handler = ros_topics_typEventHandler()
libros_topics_typ.add_event_handler(ros_topics_typ_datamodel, handler)

try:
    ros_topics_typ_datamodel.connect()
    while True:
        ros_topics_typ_datamodel.process()
        # if ros_topics_typ_datamodel.is_connected:
            # ros_topics_typ_datamodel.twist.value. .. = .. 
            # ros_topics_typ_datamodel.twist.publish()
            
            # ros_topics_typ_datamodel.config.value. .. = .. 
            # ros_topics_typ_datamodel.config.publish()
            
except(KeyboardInterrupt, SystemExit):
    ros_topics_typ_datamodel.log.success("Application terminated, shutting down")

ros_topics_typ_datamodel.disconnect()
ros_topics_typ_datamodel.dispose()

