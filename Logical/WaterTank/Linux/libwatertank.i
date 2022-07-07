%module(directors="1") libWaterTank
%{
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "exos_watertank.h"
#include "libwatertank.h"
%}

%include "typemaps.i"
%include "std_except.i"

%feature("director") WaterTankEventHandler;
%inline %{
struct WaterTankEventHandler
{
    virtual void on_connected(void) {}
    virtual void on_disconnected(void) {}
    virtual void on_operational(void) {}

    virtual void on_change_FillValve() {}
    virtual void on_change_EnableHeater() {}
    virtual void on_change_HeaterConfig() {}

    virtual ~WaterTankEventHandler() {}
    libWaterTank_t *watertank;
};
%}

%{
static WaterTankEventHandler *pWaterTankEventHandler = NULL;

static void libWaterTank_on_connected()
{
    pWaterTankEventHandler->on_connected();
}

static void libWaterTank_on_disconnected()
{
    pWaterTankEventHandler->on_disconnected();
}

static void libWaterTank_on_operational()
{
    pWaterTankEventHandler->on_operational();
}

static void libWaterTank_on_change_FillValve()
{
    pWaterTankEventHandler->on_change_FillValve();
}
static void libWaterTank_on_change_EnableHeater()
{
    pWaterTankEventHandler->on_change_EnableHeater();
}
static void libWaterTank_on_change_HeaterConfig()
{
    pWaterTankEventHandler->on_change_HeaterConfig();
}
%}

%inline %{
void add_event_handler(libWaterTank_t *watertank, WaterTankEventHandler *handler)
{
    pWaterTankEventHandler = handler;

    watertank->on_connected = &libWaterTank_on_connected;
    watertank->on_disconnected = &libWaterTank_on_disconnected;
    watertank->on_operational = &libWaterTank_on_operational;
    
    watertank->FillValve.on_change = &libWaterTank_on_change_FillValve;
    watertank->EnableHeater.on_change = &libWaterTank_on_change_EnableHeater;
    watertank->HeaterConfig.on_change = &libWaterTank_on_change_HeaterConfig;
    
    pWaterTankEventHandler->watertank = watertank;
    handler = NULL;
}
%}

%include "stdint.i"

/* Handle arrays in substructures, structs could be exposed using these two lines:
     %include "exos_watertank.h"
   But we need to disable the array members and add them again with the wrapped_array
*/
typedef struct WaterTankHeaterStatus
{
    float WaterTemperature;
    bool HeatingActive;

} WaterTankHeaterStatus;

typedef struct WaterTankStatus
{
    bool LevelHigh;
    bool LevelLow;
    int32_t FillValveDelay;
    int32_t WaterLevel;
    struct WaterTankHeaterStatus Heater;

} WaterTankStatus;

typedef struct WaterTankHeaterConfig
{
    float MaxTemperature;
    float MaxPower;

} WaterTankHeaterConfig;

typedef enum VALVE_STATE
{
    VALVE_CLOSED = 0,
    VALVE_OPEN = 1

} VALVE_STATE;

typedef struct libWaterTankFillValve
{
    void on_change(void);
    int32_t nettime;
    VALVE_STATE value;
} libWaterTankFillValve_t;

typedef struct libWaterTankEnableHeater
{
    void on_change(void);
    int32_t nettime;
    bool value;
} libWaterTankEnableHeater_t;

typedef struct libWaterTankHeaterConfig
{
    void publish(void);
    void on_change(void);
    int32_t nettime;
    WaterTankHeaterConfig value;
} libWaterTankHeaterConfig_t;

typedef struct libWaterTankStatus
{
    void publish(void);
    WaterTankStatus value;
} libWaterTankStatus_t;

typedef struct libWaterTank_log
{
    void error(char *log_entry);
    void warning(char *log_entry);
    void success(char *log_entry);
    void info(char *log_entry);
    void debug(char *log_entry);
    void verbose(char *log_entry);
} libWaterTank_log_t;

typedef struct libWaterTank
{
    void connect(void);
    void disconnect(void);
    void process(void);
    void set_operational(void);
    void dispose(void);
    int32_t get_nettime(void);
    libWaterTank_log_t log;
    void on_connected(void);
    void on_disconnected(void);
    void on_operational(void);
    bool is_connected;
    bool is_operational;
    libWaterTankFillValve_t FillValve;
    libWaterTankEnableHeater_t EnableHeater;
    libWaterTankHeaterConfig_t HeaterConfig;
    libWaterTankStatus_t Status;
} libWaterTank_t;

libWaterTank_t *libWaterTank_init(void);
