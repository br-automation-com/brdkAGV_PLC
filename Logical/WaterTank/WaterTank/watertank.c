#include <string.h>
#include <stdbool.h>
#include "libwatertank.h"

/* libWaterTank_t datamodel features:

main methods:
    watertank->connect()
    watertank->disconnect()
    watertank->process()
    watertank->set_operational()
    watertank->dispose()
    watertank->get_nettime() : (int32_t) get current nettime

void(void) user callbacks:
    watertank->on_connected
    watertank->on_disconnected
    watertank->on_operational

boolean values:
    watertank->is_connected
    watertank->is_operational

logging methods:
    watertank->log.error(char *)
    watertank->log.warning(char *)
    watertank->log.success(char *)
    watertank->log.info(char *)
    watertank->log.debug(char *)
    watertank->log.verbose(char *)

dataset FillValve:
    watertank->FillValve.publish()
    watertank->FillValve.value : (VALVE_STATE)  actual dataset values

dataset EnableHeater:
    watertank->EnableHeater.publish()
    watertank->EnableHeater.value : (bool)  actual dataset value

dataset HeaterConfig:
    watertank->HeaterConfig.publish()
    watertank->HeaterConfig.on_change : void(void) user callback function
    watertank->HeaterConfig.nettime : (int32_t) nettime @ time of publish
    watertank->HeaterConfig.value : (WaterTankHeaterConfig)  actual dataset values

dataset Status:
    watertank->Status.on_change : void(void) user callback function
    watertank->Status.nettime : (int32_t) nettime @ time of publish
    watertank->Status.value : (WaterTankStatus)  actual dataset values
*/
int snprintf(char *s, size_t n, const char *format, ...);

static libWaterTank_t *watertank;
static struct WaterTankCyclic *cyclic_inst;

static void on_change_heaterconfig(void)
{
    watertank->log.success("dataset config changed, check your new datasets");
    memcpy(&(cyclic_inst->pWaterTank->HeaterConfig), &(watertank->HeaterConfig.value), sizeof(cyclic_inst->pWaterTank->HeaterConfig));
}
static void on_change_status(void)
{
    cyclic_inst->pWaterTank->StatusDelay = watertank->get_nettime() - watertank->Status.nettime;
    cyclic_inst->pWaterTank->StatusUpdates++;

    //check for changes in the received data
    if (watertank->Status.value.LevelHigh > cyclic_inst->pWaterTank->Status.LevelHigh)
    {
        watertank->log.success("Level High reached");
    }
    if (watertank->Status.value.LevelLow > cyclic_inst->pWaterTank->Status.LevelLow)
    {
        watertank->log.success("Level Low reached");
    }
    if (watertank->Status.value.Heater.WaterTemperature != cyclic_inst->pWaterTank->Status.Heater.WaterTemperature)
    {
        char message[256];
        snprintf(message, 256, "Water temperature is now: %f nettime delay: %d us", watertank->Status.value.Heater.WaterTemperature, cyclic_inst->pWaterTank->StatusDelay);
        watertank->log.verbose(message);
    }

    memcpy(&(cyclic_inst->pWaterTank->Status), &(watertank->Status.value), sizeof(cyclic_inst->pWaterTank->Status));
}
_BUR_PUBLIC void WaterTankCyclic(struct WaterTankCyclic *inst)
{
    // check if function block has been created before
    if (cyclic_inst != NULL)
    {
        // return error if more than one function blocks have been created
        if (inst != cyclic_inst)
        {
            inst->Operational = false;
            inst->Connected = false;
            inst->Error = true;
            return;
        }
    }
    cyclic_inst = inst;
    // initialize library
    if ((libWaterTank_t *)inst->_Handle == NULL || (libWaterTank_t *)inst->_Handle != watertank)
    {
        //retrieve the watertank structure
        watertank = libWaterTank_init();

        //setup callbacks
        watertank->HeaterConfig.on_change = on_change_heaterconfig;
        watertank->Status.on_change = on_change_status;

        inst->_Handle = (UDINT)watertank;
    }
    // return error if reference to structure is not set on function block
    if (inst->pWaterTank == NULL)
    {
        inst->Operational = false;
        inst->Connected = false;
        inst->Error = true;
        return;
    }
    if (inst->Enable && !inst->_Enable)
    {
        //connect to the server
        watertank->connect();
    }
    if (!inst->Enable && inst->_Enable)
    {
        //disconnect from server
        cyclic_inst = NULL;
        watertank->disconnect();
    }
    inst->_Enable = inst->Enable;

    if (inst->Start && !inst->_Start && watertank->is_connected)
    {
        watertank->set_operational();
        inst->_Start = inst->Start;
    }
    if (!inst->Start)
    {
        inst->_Start = false;
    }

    //trigger callbacks
    watertank->process();

    if (watertank->is_connected)
    {
        if (memcmp(&(watertank->FillValve.value), &(inst->pWaterTank->FillValve), sizeof(inst->pWaterTank->FillValve)))
        {
            memcpy(&(watertank->FillValve.value), &(inst->pWaterTank->FillValve), sizeof(watertank->FillValve.value));
            watertank->FillValve.publish();
        }

        if (watertank->EnableHeater.value != inst->pWaterTank->EnableHeater)
        {
            watertank->EnableHeater.value = inst->pWaterTank->EnableHeater;
            watertank->EnableHeater.publish();
        }

        if (memcmp(&(watertank->HeaterConfig.value), &(inst->pWaterTank->HeaterConfig), sizeof(inst->pWaterTank->HeaterConfig)))
        {
            memcpy(&(watertank->HeaterConfig.value), &(inst->pWaterTank->HeaterConfig), sizeof(watertank->HeaterConfig.value));
            watertank->HeaterConfig.publish();
        }
    }
    inst->Connected = watertank->is_connected;
    inst->Operational = watertank->is_operational;
}

UINT _EXIT ProgramExit(unsigned long phase)
{
    //shutdown
    watertank->dispose();
    cyclic_inst = NULL;
    return 0;
}
