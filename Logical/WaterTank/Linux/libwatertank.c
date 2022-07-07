#include <string.h>
#define EXOS_ASSERT_LOG &logger
#include "exos_log.h"
#include "libwatertank.h"

#define SUCCESS(_format_, ...) exos_log_success(&logger, EXOS_LOG_TYPE_USER, _format_, ##__VA_ARGS__);
#define INFO(_format_, ...) exos_log_info(&logger, EXOS_LOG_TYPE_USER, _format_, ##__VA_ARGS__);
#define VERBOSE(_format_, ...) exos_log_debug(&logger, EXOS_LOG_TYPE_USER + EXOS_LOG_TYPE_VERBOSE, _format_, ##__VA_ARGS__);
#define ERROR(_format_, ...) exos_log_error(&logger, _format_, ##__VA_ARGS__);

static exos_log_handle_t logger;

typedef struct libWaterTankHandle
{
    libWaterTank_t ext_watertank;
    exos_datamodel_handle_t watertank;

    exos_dataset_handle_t fillvalve;
    exos_dataset_handle_t enableheater;
    exos_dataset_handle_t heaterconfig;
    exos_dataset_handle_t status;
} libWaterTankHandle_t;

static libWaterTankHandle_t h_WaterTank;

static void libWaterTank_datasetEvent(exos_dataset_handle_t *dataset, EXOS_DATASET_EVENT_TYPE event_type, void *info)
{
    switch (event_type)
    {
    case EXOS_DATASET_EVENT_UPDATED:
        VERBOSE("dataset %s updated! latency (us):%i", dataset->name, (exos_datamodel_get_nettime(dataset->datamodel) - dataset->nettime));
        //handle each subscription dataset separately
        if (0 == strcmp(dataset->name, "FillValve"))
        {
            //update the nettime
            h_WaterTank.ext_watertank.FillValve.nettime = dataset->nettime;

            //trigger the callback if assigned
            if (NULL != h_WaterTank.ext_watertank.FillValve.on_change)
            {
                h_WaterTank.ext_watertank.FillValve.on_change();
            }
        }
        else if (0 == strcmp(dataset->name, "EnableHeater"))
        {
            //update the nettime
            h_WaterTank.ext_watertank.EnableHeater.nettime = dataset->nettime;

            //trigger the callback if assigned
            if (NULL != h_WaterTank.ext_watertank.EnableHeater.on_change)
            {
                h_WaterTank.ext_watertank.EnableHeater.on_change();
            }
        }
        else if (0 == strcmp(dataset->name, "HeaterConfig"))
        {
            //update the nettime
            h_WaterTank.ext_watertank.HeaterConfig.nettime = dataset->nettime;

            //trigger the callback if assigned
            if (NULL != h_WaterTank.ext_watertank.HeaterConfig.on_change)
            {
                h_WaterTank.ext_watertank.HeaterConfig.on_change();
            }
        }
        break;

    default:
        break;
    }
}

static void libWaterTank_datamodelEvent(exos_datamodel_handle_t *datamodel, const EXOS_DATAMODEL_EVENT_TYPE event_type, void *info)
{
    switch (event_type)
    {
    case EXOS_DATAMODEL_EVENT_CONNECTION_CHANGED:
        INFO("application changed state to %s", exos_get_state_string(datamodel->connection_state));

        h_WaterTank.ext_watertank.is_connected = false;
        h_WaterTank.ext_watertank.is_operational = false;
        switch (datamodel->connection_state)
        {
        case EXOS_STATE_DISCONNECTED:
            if (NULL != h_WaterTank.ext_watertank.on_disconnected)
            {
                h_WaterTank.ext_watertank.on_disconnected();
            }
            break;
        case EXOS_STATE_CONNECTED:
            h_WaterTank.ext_watertank.is_connected = true;
            if (NULL != h_WaterTank.ext_watertank.on_connected)
            {
                h_WaterTank.ext_watertank.on_connected();
            }
            break;
        case EXOS_STATE_OPERATIONAL:
            h_WaterTank.ext_watertank.is_connected = true;
            h_WaterTank.ext_watertank.is_operational = true;
            if (NULL != h_WaterTank.ext_watertank.on_operational)
            {
                h_WaterTank.ext_watertank.on_operational();
            }
            SUCCESS("WaterTank operational!");
            break;
        case EXOS_STATE_ABORTED:
            if (NULL != h_WaterTank.ext_watertank.on_disconnected)
            {
                h_WaterTank.ext_watertank.on_disconnected();
            }
            ERROR("application error %d (%s) occured", datamodel->error, exos_get_error_string(datamodel->error));
            break;
        }
        break;
    case EXOS_DATAMODEL_EVENT_SYNC_STATE_CHANGED:
        break;

    default:
        break;

    }
}

static void libWaterTank_publish_heaterconfig(void)
{
    exos_dataset_publish(&h_WaterTank.heaterconfig);
}
static void libWaterTank_publish_status(void)
{
    exos_dataset_publish(&h_WaterTank.status);
}

static void libWaterTank_connect(void)
{
    //connect the datamodel
    EXOS_ASSERT_OK(exos_datamodel_connect_watertank(&(h_WaterTank.watertank), libWaterTank_datamodelEvent));
    
    //connect datasets
    EXOS_ASSERT_OK(exos_dataset_connect(&(h_WaterTank.fillvalve), EXOS_DATASET_SUBSCRIBE, libWaterTank_datasetEvent));
    EXOS_ASSERT_OK(exos_dataset_connect(&(h_WaterTank.enableheater), EXOS_DATASET_SUBSCRIBE, libWaterTank_datasetEvent));
    EXOS_ASSERT_OK(exos_dataset_connect(&(h_WaterTank.heaterconfig), EXOS_DATASET_PUBLISH + EXOS_DATASET_SUBSCRIBE, libWaterTank_datasetEvent));
    EXOS_ASSERT_OK(exos_dataset_connect(&(h_WaterTank.status), EXOS_DATASET_PUBLISH, libWaterTank_datasetEvent));
}
static void libWaterTank_disconnect(void)
{
    h_WaterTank.ext_watertank.is_connected = false;
    h_WaterTank.ext_watertank.is_operational = false;

    EXOS_ASSERT_OK(exos_datamodel_disconnect(&(h_WaterTank.watertank)));
}

static void libWaterTank_set_operational(void)
{
    EXOS_ASSERT_OK(exos_datamodel_set_operational(&(h_WaterTank.watertank)));
}

static void libWaterTank_process(void)
{
    EXOS_ASSERT_OK(exos_datamodel_process(&(h_WaterTank.watertank)));
    exos_log_process(&logger);
}

static void libWaterTank_dispose(void)
{
    h_WaterTank.ext_watertank.is_connected = false;
    h_WaterTank.ext_watertank.is_operational = false;

    EXOS_ASSERT_OK(exos_datamodel_delete(&(h_WaterTank.watertank)));
    exos_log_delete(&logger);
}

static int32_t libWaterTank_get_nettime(void)
{
    return exos_datamodel_get_nettime(&(h_WaterTank.watertank));
}

static void libWaterTank_log_error(char* log_entry)
{
    exos_log_error(&logger, log_entry);
}

static void libWaterTank_log_warning(char* log_entry)
{
    exos_log_warning(&logger, EXOS_LOG_TYPE_USER, log_entry);
}

static void libWaterTank_log_success(char* log_entry)
{
    exos_log_success(&logger, EXOS_LOG_TYPE_USER, log_entry);
}

static void libWaterTank_log_info(char* log_entry)
{
    exos_log_info(&logger, EXOS_LOG_TYPE_USER, log_entry);
}

static void libWaterTank_log_debug(char* log_entry)
{
    exos_log_debug(&logger, EXOS_LOG_TYPE_USER, log_entry);
}

static void libWaterTank_log_verbose(char* log_entry)
{
    exos_log_warning(&logger, EXOS_LOG_TYPE_USER + EXOS_LOG_TYPE_VERBOSE, log_entry);
}

libWaterTank_t *libWaterTank_init(void)
{
    memset(&h_WaterTank, 0, sizeof(h_WaterTank));

    h_WaterTank.ext_watertank.HeaterConfig.publish = libWaterTank_publish_heaterconfig;
    h_WaterTank.ext_watertank.Status.publish = libWaterTank_publish_status;
    
    h_WaterTank.ext_watertank.connect = libWaterTank_connect;
    h_WaterTank.ext_watertank.disconnect = libWaterTank_disconnect;
    h_WaterTank.ext_watertank.process = libWaterTank_process;
    h_WaterTank.ext_watertank.set_operational = libWaterTank_set_operational;
    h_WaterTank.ext_watertank.dispose = libWaterTank_dispose;
    h_WaterTank.ext_watertank.get_nettime = libWaterTank_get_nettime;
    h_WaterTank.ext_watertank.log.error = libWaterTank_log_error;
    h_WaterTank.ext_watertank.log.warning = libWaterTank_log_warning;
    h_WaterTank.ext_watertank.log.success = libWaterTank_log_success;
    h_WaterTank.ext_watertank.log.info = libWaterTank_log_info;
    h_WaterTank.ext_watertank.log.debug = libWaterTank_log_debug;
    h_WaterTank.ext_watertank.log.verbose = libWaterTank_log_verbose;
    
    exos_log_init(&logger, "gWaterTank_0");

    SUCCESS("starting gWaterTank_0 application..");

    EXOS_ASSERT_OK(exos_datamodel_init(&h_WaterTank.watertank, "WaterTank_0", "gWaterTank_0"));

    //set the user_context to access custom data in the callbacks
    h_WaterTank.watertank.user_context = NULL; //not used
    h_WaterTank.watertank.user_tag = 0; //not used

    EXOS_ASSERT_OK(exos_dataset_init(&h_WaterTank.fillvalve, &h_WaterTank.watertank, "FillValve", &h_WaterTank.ext_watertank.FillValve.value, sizeof(h_WaterTank.ext_watertank.FillValve.value)));
    h_WaterTank.fillvalve.user_context = NULL; //not used
    h_WaterTank.fillvalve.user_tag = 0; //not used

    EXOS_ASSERT_OK(exos_dataset_init(&h_WaterTank.enableheater, &h_WaterTank.watertank, "EnableHeater", &h_WaterTank.ext_watertank.EnableHeater.value, sizeof(h_WaterTank.ext_watertank.EnableHeater.value)));
    h_WaterTank.enableheater.user_context = NULL; //not used
    h_WaterTank.enableheater.user_tag = 0; //not used

    EXOS_ASSERT_OK(exos_dataset_init(&h_WaterTank.heaterconfig, &h_WaterTank.watertank, "HeaterConfig", &h_WaterTank.ext_watertank.HeaterConfig.value, sizeof(h_WaterTank.ext_watertank.HeaterConfig.value)));
    h_WaterTank.heaterconfig.user_context = NULL; //not used
    h_WaterTank.heaterconfig.user_tag = 0; //not used

    EXOS_ASSERT_OK(exos_dataset_init(&h_WaterTank.status, &h_WaterTank.watertank, "Status", &h_WaterTank.ext_watertank.Status.value, sizeof(h_WaterTank.ext_watertank.Status.value)));
    h_WaterTank.status.user_context = NULL; //not used
    h_WaterTank.status.user_tag = 0; //not used

    return &(h_WaterTank.ext_watertank);
}
