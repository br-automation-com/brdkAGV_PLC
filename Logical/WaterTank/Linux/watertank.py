# Use import and sys.path.insert if this py file is moved.
# The path should point to the directory containing _libWaterTank.so
# import sys
# sys.path.insert(1, 'WaterTank_py/Linux')
import libWaterTank

"""
libWaterTank datamodel features:

initialize and setup callback handler:
    watertank = libWaterTank.libWaterTank_init()
    handler = WaterTankEventHandler()
    libWaterTank.add_event_handler(watertank, handler)

main methods:
    watertank.connect()
    watertank.disconnect()
    watertank.process()
    watertank.set_operational()
    watertank.dispose()
    watertank.get_nettime() : (int32_t) get current nettime

def user callbacks in class WaterTankEventHandler:
    on_connected
    on_disconnected
    on_operational

boolean values:
    watertank.is_connected
    watertank.is_operational

logging methods:
    watertank.log.error(str)
    watertank.log.warning(str)
    watertank.log.success(str)
    watertank.log.info(str)
    watertank.log.debug(str)
    watertank.log.verbose(str)

dataset FillValve:
    WaterTankEventHandler:on_change_FillValve : void(void) user callback function
    watertank.FillValve.nettime : (int32_t) nettime @ time of publish
    watertank.FillValve.value : (VALVE_STATE)  actual dataset values

dataset EnableHeater:
    WaterTankEventHandler:on_change_EnableHeater : void(void) user callback function
    watertank.EnableHeater.nettime : (int32_t) nettime @ time of publish
    watertank.EnableHeater.value : (bool)  actual dataset value

dataset HeaterConfig:
    watertank.HeaterConfig.publish()
    WaterTankEventHandler:on_change_HeaterConfig : void(void) user callback function
    watertank.HeaterConfig.nettime : (int32_t) nettime @ time of publish
    watertank.HeaterConfig.value : (WaterTankHeaterConfig)  actual dataset values

dataset Status:
    watertank.Status.publish()
    watertank.Status.value : (WaterTankStatus)  actual dataset values
"""

EPSILON = 0.0001

def check_heaterconfig():
    values_changed = False
    if watertank.HeaterConfig.value.MaxPower > 1.0 :
        watertank.HeaterConfig.value.MaxPower = 1.0
        values_changed = True
    
    if watertank.HeaterConfig.value.MaxPower < EPSILON :
        watertank.HeaterConfig.value.MaxPower = 0.5
        values_changed = True

    if watertank.HeaterConfig.value.MaxTemperature > 90 :
        watertank.HeaterConfig.value.MaxTemperature = 90
        values_changed = True

    if watertank.HeaterConfig.value.MaxTemperature < EPSILON :
        watertank.HeaterConfig.value.MaxTemperature = 45
        values_changed = True

    if values_changed:
        watertank.log.success("HeaterConfig changed, values limited")
        watertank.HeaterConfig.publish()

class WaterTankEventHandler(libWaterTank.WaterTankEventHandler):

    def __init__(self):
        libWaterTank.WaterTankEventHandler.__init__(self)

    def on_connected(self):
        self.watertank.log.success("python watertank connected!")

    # def on_disconnected(self):
    #     self.watertank. ..

    # def on_operational(self):
    #     self.watertank. ..

    def on_change_FillValve(self):
        self.watertank.log.verbose("python dataset FillValve changed!")
        diff = self.watertank.get_nettime() - self.watertank.FillValve.nettime
        self.watertank.log.info("Filling Valve Changed to " + str(self.watertank.FillValve.value) + ", timedelay " + str(diff))
        self.watertank.Status.value.FillValveDelay = diff
        self.watertank.Status.publish()
        
    def on_change_EnableHeater(self):
        self.watertank.log.verbose("python dataset EnableHeater changed!")
        if self.watertank.EnableHeater.value:
            self.watertank.log.success("Heater Enabled!")
        else:
            self.watertank.log.success("Heater Disabled!")
    
    def on_change_HeaterConfig(self):
        self.watertank.log.verbose("python dataset HeaterConfig changed!")
        check_heaterconfig()
    

watertank = libWaterTank.libWaterTank_init()

handler = WaterTankEventHandler()
libWaterTank.add_event_handler(watertank, handler)



class sim_t:
    def __init__(self):
        self.old_high = False
        self.old_low = False

def run_tanksimulator(sim):
    watertank.Status.value.LevelLow = (watertank.Status.value.WaterLevel < 200)
    watertank.Status.value.LevelHigh = (watertank.Status.value.WaterLevel > 800)
    if sim.old_low != watertank.Status.value.LevelLow :
        watertank.log.info("Level LOW changed to " + str(watertank.Status.value.LevelLow) + ", Water Level: " + str(watertank.Status.value.WaterLevel))
        watertank.Status.publish()
    
    if sim.old_high != watertank.Status.value.LevelHigh :
        watertank.log.info("Level HIGH changed to " + str(watertank.Status.value.LevelHigh) + ", Water Level: " + str(watertank.Status.value.WaterLevel))
        watertank.Status.publish()
    
    sim.old_low = watertank.Status.value.LevelLow
    sim.old_high = watertank.Status.value.LevelHigh

    if watertank.FillValve.value:
        if watertank.Status.value.WaterLevel < 1000 :
            watertank.Status.value.WaterLevel += 5
            watertank.Status.publish()
    else:
        if watertank.Status.value.WaterLevel > 0:
            watertank.Status.value.WaterLevel -= 2
            watertank.Status.publish()

    if watertank.EnableHeater.value:
        if watertank.Status.value.Heater.WaterTemperature < watertank.HeaterConfig.value.MaxTemperature :
            watertank.Status.value.Heater.WaterTemperature += watertank.HeaterConfig.value.MaxPower
            watertank.Status.value.Heater.HeatingActive = True
            watertank.Status.publish()
        else:
            watertank.Status.value.Heater.WaterTemperature -= 3 * watertank.HeaterConfig.value.MaxPower
            watertank.Status.value.Heater.HeatingActive = False
            watertank.Status.publish()
    else:
        watertank.Status.value.Heater.HeatingActive = False
        if watertank.Status.value.Heater.WaterTemperature >= 20.1:
            watertank.Status.value.Heater.WaterTemperature -= 0.1
            watertank.Status.publish()
    
try:
    watertank.connect()
    sim = sim_t()
    while True:
        watertank.process()
        if watertank.is_operational:
            check_heaterconfig()
            run_tanksimulator(sim)
            
except(KeyboardInterrupt, SystemExit):
    watertank.log.success("Application terminated, shutting down")

watertank.disconnect()
watertank.dispose()

