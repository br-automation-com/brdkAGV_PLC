/*Automatically generated header file from WaterTank.typ*/

#ifndef _EXOS_COMP_WATERTANK_H_
#define _EXOS_COMP_WATERTANK_H_

#include "exos_api.h"

#if defined(_SG4)
#include <WaterTank.h>
#else
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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

typedef struct WaterTank
{
    VALVE_STATE FillValve; //PUB
    bool EnableHeater; //PUB
    struct WaterTankHeaterConfig HeaterConfig; //PUB SUB
    struct WaterTankStatus Status; //SUB
    int32_t StatusDelay;
    uint32_t StatusUpdates;

} WaterTank;

#endif // _SG4

EXOS_ERROR_CODE exos_datamodel_connect_watertank(exos_datamodel_handle_t *datamodel, exos_datamodel_event_cb datamodel_event_callback);

#endif // _EXOS_COMP_WATERTANK_H_
