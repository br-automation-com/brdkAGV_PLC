# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.1
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _libWaterTank
else:
    import _libWaterTank

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


import weakref

class WaterTankEventHandler(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def on_connected(self):
        return _libWaterTank.WaterTankEventHandler_on_connected(self)

    def on_disconnected(self):
        return _libWaterTank.WaterTankEventHandler_on_disconnected(self)

    def on_operational(self):
        return _libWaterTank.WaterTankEventHandler_on_operational(self)

    def on_change_FillValve(self):
        return _libWaterTank.WaterTankEventHandler_on_change_FillValve(self)

    def on_change_EnableHeater(self):
        return _libWaterTank.WaterTankEventHandler_on_change_EnableHeater(self)

    def on_change_HeaterConfig(self):
        return _libWaterTank.WaterTankEventHandler_on_change_HeaterConfig(self)
    __swig_destroy__ = _libWaterTank.delete_WaterTankEventHandler
    watertank = property(_libWaterTank.WaterTankEventHandler_watertank_get, _libWaterTank.WaterTankEventHandler_watertank_set)

    def __init__(self):
        if self.__class__ == WaterTankEventHandler:
            _self = None
        else:
            _self = self
        _libWaterTank.WaterTankEventHandler_swiginit(self, _libWaterTank.new_WaterTankEventHandler(_self, ))
    def __disown__(self):
        self.this.disown()
        _libWaterTank.disown_WaterTankEventHandler(self)
        return weakref.proxy(self)

# Register WaterTankEventHandler in _libWaterTank:
_libWaterTank.WaterTankEventHandler_swigregister(WaterTankEventHandler)


def add_event_handler(watertank, handler):
    return _libWaterTank.add_event_handler(watertank, handler)
class WaterTankHeaterStatus(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    WaterTemperature = property(_libWaterTank.WaterTankHeaterStatus_WaterTemperature_get, _libWaterTank.WaterTankHeaterStatus_WaterTemperature_set)
    HeatingActive = property(_libWaterTank.WaterTankHeaterStatus_HeatingActive_get, _libWaterTank.WaterTankHeaterStatus_HeatingActive_set)

    def __init__(self):
        _libWaterTank.WaterTankHeaterStatus_swiginit(self, _libWaterTank.new_WaterTankHeaterStatus())
    __swig_destroy__ = _libWaterTank.delete_WaterTankHeaterStatus

# Register WaterTankHeaterStatus in _libWaterTank:
_libWaterTank.WaterTankHeaterStatus_swigregister(WaterTankHeaterStatus)

class WaterTankStatus(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    LevelHigh = property(_libWaterTank.WaterTankStatus_LevelHigh_get, _libWaterTank.WaterTankStatus_LevelHigh_set)
    LevelLow = property(_libWaterTank.WaterTankStatus_LevelLow_get, _libWaterTank.WaterTankStatus_LevelLow_set)
    FillValveDelay = property(_libWaterTank.WaterTankStatus_FillValveDelay_get, _libWaterTank.WaterTankStatus_FillValveDelay_set)
    WaterLevel = property(_libWaterTank.WaterTankStatus_WaterLevel_get, _libWaterTank.WaterTankStatus_WaterLevel_set)
    Heater = property(_libWaterTank.WaterTankStatus_Heater_get, _libWaterTank.WaterTankStatus_Heater_set)

    def __init__(self):
        _libWaterTank.WaterTankStatus_swiginit(self, _libWaterTank.new_WaterTankStatus())
    __swig_destroy__ = _libWaterTank.delete_WaterTankStatus

# Register WaterTankStatus in _libWaterTank:
_libWaterTank.WaterTankStatus_swigregister(WaterTankStatus)

class WaterTankHeaterConfig(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    MaxTemperature = property(_libWaterTank.WaterTankHeaterConfig_MaxTemperature_get, _libWaterTank.WaterTankHeaterConfig_MaxTemperature_set)
    MaxPower = property(_libWaterTank.WaterTankHeaterConfig_MaxPower_get, _libWaterTank.WaterTankHeaterConfig_MaxPower_set)

    def __init__(self):
        _libWaterTank.WaterTankHeaterConfig_swiginit(self, _libWaterTank.new_WaterTankHeaterConfig())
    __swig_destroy__ = _libWaterTank.delete_WaterTankHeaterConfig

# Register WaterTankHeaterConfig in _libWaterTank:
_libWaterTank.WaterTankHeaterConfig_swigregister(WaterTankHeaterConfig)

VALVE_CLOSED = _libWaterTank.VALVE_CLOSED
VALVE_OPEN = _libWaterTank.VALVE_OPEN
class libWaterTankFillValve_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def on_change(self):
        return _libWaterTank.libWaterTankFillValve_t_on_change(self)
    nettime = property(_libWaterTank.libWaterTankFillValve_t_nettime_get, _libWaterTank.libWaterTankFillValve_t_nettime_set)
    value = property(_libWaterTank.libWaterTankFillValve_t_value_get, _libWaterTank.libWaterTankFillValve_t_value_set)

    def __init__(self):
        _libWaterTank.libWaterTankFillValve_t_swiginit(self, _libWaterTank.new_libWaterTankFillValve_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTankFillValve_t

# Register libWaterTankFillValve_t in _libWaterTank:
_libWaterTank.libWaterTankFillValve_t_swigregister(libWaterTankFillValve_t)

class libWaterTankEnableHeater_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def on_change(self):
        return _libWaterTank.libWaterTankEnableHeater_t_on_change(self)
    nettime = property(_libWaterTank.libWaterTankEnableHeater_t_nettime_get, _libWaterTank.libWaterTankEnableHeater_t_nettime_set)
    value = property(_libWaterTank.libWaterTankEnableHeater_t_value_get, _libWaterTank.libWaterTankEnableHeater_t_value_set)

    def __init__(self):
        _libWaterTank.libWaterTankEnableHeater_t_swiginit(self, _libWaterTank.new_libWaterTankEnableHeater_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTankEnableHeater_t

# Register libWaterTankEnableHeater_t in _libWaterTank:
_libWaterTank.libWaterTankEnableHeater_t_swigregister(libWaterTankEnableHeater_t)

class libWaterTankHeaterConfig_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def publish(self):
        return _libWaterTank.libWaterTankHeaterConfig_t_publish(self)

    def on_change(self):
        return _libWaterTank.libWaterTankHeaterConfig_t_on_change(self)
    nettime = property(_libWaterTank.libWaterTankHeaterConfig_t_nettime_get, _libWaterTank.libWaterTankHeaterConfig_t_nettime_set)
    value = property(_libWaterTank.libWaterTankHeaterConfig_t_value_get, _libWaterTank.libWaterTankHeaterConfig_t_value_set)

    def __init__(self):
        _libWaterTank.libWaterTankHeaterConfig_t_swiginit(self, _libWaterTank.new_libWaterTankHeaterConfig_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTankHeaterConfig_t

# Register libWaterTankHeaterConfig_t in _libWaterTank:
_libWaterTank.libWaterTankHeaterConfig_t_swigregister(libWaterTankHeaterConfig_t)

class libWaterTankStatus_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def publish(self):
        return _libWaterTank.libWaterTankStatus_t_publish(self)
    value = property(_libWaterTank.libWaterTankStatus_t_value_get, _libWaterTank.libWaterTankStatus_t_value_set)

    def __init__(self):
        _libWaterTank.libWaterTankStatus_t_swiginit(self, _libWaterTank.new_libWaterTankStatus_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTankStatus_t

# Register libWaterTankStatus_t in _libWaterTank:
_libWaterTank.libWaterTankStatus_t_swigregister(libWaterTankStatus_t)

class libWaterTank_log_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def error(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_error(self, log_entry)

    def warning(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_warning(self, log_entry)

    def success(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_success(self, log_entry)

    def info(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_info(self, log_entry)

    def debug(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_debug(self, log_entry)

    def verbose(self, log_entry):
        return _libWaterTank.libWaterTank_log_t_verbose(self, log_entry)

    def __init__(self):
        _libWaterTank.libWaterTank_log_t_swiginit(self, _libWaterTank.new_libWaterTank_log_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTank_log_t

# Register libWaterTank_log_t in _libWaterTank:
_libWaterTank.libWaterTank_log_t_swigregister(libWaterTank_log_t)

class libWaterTank_t(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def connect(self):
        return _libWaterTank.libWaterTank_t_connect(self)

    def disconnect(self):
        return _libWaterTank.libWaterTank_t_disconnect(self)

    def process(self):
        return _libWaterTank.libWaterTank_t_process(self)

    def set_operational(self):
        return _libWaterTank.libWaterTank_t_set_operational(self)

    def dispose(self):
        return _libWaterTank.libWaterTank_t_dispose(self)

    def get_nettime(self):
        return _libWaterTank.libWaterTank_t_get_nettime(self)
    log = property(_libWaterTank.libWaterTank_t_log_get, _libWaterTank.libWaterTank_t_log_set)

    def on_connected(self):
        return _libWaterTank.libWaterTank_t_on_connected(self)

    def on_disconnected(self):
        return _libWaterTank.libWaterTank_t_on_disconnected(self)

    def on_operational(self):
        return _libWaterTank.libWaterTank_t_on_operational(self)
    is_connected = property(_libWaterTank.libWaterTank_t_is_connected_get, _libWaterTank.libWaterTank_t_is_connected_set)
    is_operational = property(_libWaterTank.libWaterTank_t_is_operational_get, _libWaterTank.libWaterTank_t_is_operational_set)
    FillValve = property(_libWaterTank.libWaterTank_t_FillValve_get, _libWaterTank.libWaterTank_t_FillValve_set)
    EnableHeater = property(_libWaterTank.libWaterTank_t_EnableHeater_get, _libWaterTank.libWaterTank_t_EnableHeater_set)
    HeaterConfig = property(_libWaterTank.libWaterTank_t_HeaterConfig_get, _libWaterTank.libWaterTank_t_HeaterConfig_set)
    Status = property(_libWaterTank.libWaterTank_t_Status_get, _libWaterTank.libWaterTank_t_Status_set)

    def __init__(self):
        _libWaterTank.libWaterTank_t_swiginit(self, _libWaterTank.new_libWaterTank_t())
    __swig_destroy__ = _libWaterTank.delete_libWaterTank_t

# Register libWaterTank_t in _libWaterTank:
_libWaterTank.libWaterTank_t_swigregister(libWaterTank_t)


def libWaterTank_init():
    return _libWaterTank.libWaterTank_init()

