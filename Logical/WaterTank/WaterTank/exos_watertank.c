/*Automatically generated c file from WaterTank.typ*/

#include "exos_watertank.h"

const char config_watertank[] = "{\"name\":\"struct\",\"attributes\":{\"name\":\"<NAME>\",\"dataType\":\"WaterTank\",\"info\":\"<infoId0>\"},\"children\":[{\"name\":\"enum\",\"attributes\":{\"name\":\"FillValve\",\"dataType\":\"VALVE_STATE\",\"comment\":\"PUB\",\"info\":\"<infoId1>\"},\"children\":[{\"name\":\"value\",\"attributes\":{\"name\":\"VALVE_CLOSED\",\"value\":0}},{\"name\":\"value\",\"attributes\":{\"name\":\"VALVE_OPEN\",\"value\":1}}]},{\"name\":\"variable\",\"attributes\":{\"name\":\"EnableHeater\",\"dataType\":\"BOOL\",\"comment\":\"PUB\",\"info\":\"<infoId2>\"}},{\"name\":\"struct\",\"attributes\":{\"name\":\"HeaterConfig\",\"dataType\":\"WaterTankHeaterConfig\",\"comment\":\"PUB SUB\",\"info\":\"<infoId3>\"},\"children\":[{\"name\":\"variable\",\"attributes\":{\"name\":\"MaxTemperature\",\"dataType\":\"REAL\",\"info\":\"<infoId4>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"MaxPower\",\"dataType\":\"REAL\",\"info\":\"<infoId5>\"}}]},{\"name\":\"struct\",\"attributes\":{\"name\":\"Status\",\"dataType\":\"WaterTankStatus\",\"comment\":\"SUB\",\"info\":\"<infoId6>\"},\"children\":[{\"name\":\"variable\",\"attributes\":{\"name\":\"LevelHigh\",\"dataType\":\"BOOL\",\"info\":\"<infoId7>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"LevelLow\",\"dataType\":\"BOOL\",\"info\":\"<infoId8>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"FillValveDelay\",\"dataType\":\"DINT\",\"info\":\"<infoId9>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"WaterLevel\",\"dataType\":\"DINT\",\"info\":\"<infoId10>\"}},{\"name\":\"struct\",\"attributes\":{\"name\":\"Heater\",\"dataType\":\"WaterTankHeaterStatus\",\"info\":\"<infoId11>\"},\"children\":[{\"name\":\"variable\",\"attributes\":{\"name\":\"WaterTemperature\",\"dataType\":\"REAL\",\"info\":\"<infoId12>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"HeatingActive\",\"dataType\":\"BOOL\",\"info\":\"<infoId13>\"}}]}]},{\"name\":\"variable\",\"attributes\":{\"name\":\"StatusDelay\",\"dataType\":\"DINT\",\"info\":\"<infoId14>\"}},{\"name\":\"variable\",\"attributes\":{\"name\":\"StatusUpdates\",\"dataType\":\"UDINT\",\"info\":\"<infoId15>\"}}]}";

/*Connect the WaterTank datamodel to the server*/
EXOS_ERROR_CODE exos_datamodel_connect_watertank(exos_datamodel_handle_t *datamodel, exos_datamodel_event_cb datamodel_event_callback)
{
    WaterTank data;
    exos_dataset_info_t datasets[] = {
        {EXOS_DATASET_BROWSE_NAME_INIT,{}},
        {EXOS_DATASET_BROWSE_NAME(FillValve),{}},
        {EXOS_DATASET_BROWSE_NAME(EnableHeater),{}},
        {EXOS_DATASET_BROWSE_NAME(HeaterConfig),{}},
        {EXOS_DATASET_BROWSE_NAME(HeaterConfig.MaxTemperature),{}},
        {EXOS_DATASET_BROWSE_NAME(HeaterConfig.MaxPower),{}},
        {EXOS_DATASET_BROWSE_NAME(Status),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.LevelHigh),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.LevelLow),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.FillValveDelay),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.WaterLevel),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.Heater),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.Heater.WaterTemperature),{}},
        {EXOS_DATASET_BROWSE_NAME(Status.Heater.HeatingActive),{}},
        {EXOS_DATASET_BROWSE_NAME(StatusDelay),{}},
        {EXOS_DATASET_BROWSE_NAME(StatusUpdates),{}}
    };

    exos_datamodel_calc_dataset_info(datasets, sizeof(datasets));

    return exos_datamodel_connect(datamodel, config_watertank, datasets, sizeof(datasets), datamodel_event_callback);
}
