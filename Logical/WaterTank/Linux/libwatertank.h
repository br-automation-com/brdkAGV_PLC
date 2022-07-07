#ifndef _LIBWATERTANK_H_
#define _LIBWATERTANK_H_

#include "exos_watertank.h"

typedef void (*libWaterTank_event_cb)(void);
typedef void (*libWaterTank_method_fn)(void);
typedef int32_t (*libWaterTank_get_nettime_fn)(void);
typedef void (*libWaterTank_log_fn)(char *log_entry);

typedef struct libWaterTankFillValve
{
    libWaterTank_event_cb on_change;
    int32_t nettime;
    VALVE_STATE value;
} libWaterTankFillValve_t;

typedef struct libWaterTankEnableHeater
{
    libWaterTank_event_cb on_change;
    int32_t nettime;
    bool value;
} libWaterTankEnableHeater_t;

typedef struct libWaterTankHeaterConfig
{
    libWaterTank_method_fn publish;
    libWaterTank_event_cb on_change;
    int32_t nettime;
    WaterTankHeaterConfig value;
} libWaterTankHeaterConfig_t;

typedef struct libWaterTankStatus
{
    libWaterTank_method_fn publish;
    WaterTankStatus value;
} libWaterTankStatus_t;

typedef struct libWaterTank_log
{
    libWaterTank_log_fn error;
    libWaterTank_log_fn warning;
    libWaterTank_log_fn success;
    libWaterTank_log_fn info;
    libWaterTank_log_fn debug;
    libWaterTank_log_fn verbose;
} libWaterTank_log_t;

typedef struct libWaterTank
{
    libWaterTank_method_fn connect;
    libWaterTank_method_fn disconnect;
    libWaterTank_method_fn process;
    libWaterTank_method_fn set_operational;
    libWaterTank_method_fn dispose;
    libWaterTank_get_nettime_fn get_nettime;
    libWaterTank_log_t log;
    libWaterTank_event_cb on_connected;
    libWaterTank_event_cb on_disconnected;
    libWaterTank_event_cb on_operational;
    bool is_connected;
    bool is_operational;
    libWaterTankFillValve_t FillValve;
    libWaterTankEnableHeater_t EnableHeater;
    libWaterTankHeaterConfig_t HeaterConfig;
    libWaterTankStatus_t Status;
} libWaterTank_t;

#ifdef __cplusplus
extern "C" {
#endif
libWaterTank_t *libWaterTank_init(void);
#ifdef __cplusplus
}
#endif
#endif // _LIBWATERTANK_H_
