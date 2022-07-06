/*
Copyright (C) 2021 B&R Danmark
All rights reserved
*/

#ifndef _EXOS_LOG_H_
#define _EXOS_LOG_H_

#include "exos_api.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define EXOS_LOG_EXCLUDE_LIST_LEN 20 /**< The current maximum number of modules that can be excluded (filtered at the source) using exos_log_config is 20, let us know why you would need more*/
#define EXOS_LOG_MAX_NAME_LENGTH 35  /**< Object Names (used in exos_log_init) cannot preceed 35 characters as a limitation in the AR logger */
#define EXOS_LOG_MESSAGE_LENGTH 256  /**< Messages cannot preceed 256 characters as a limitation in the AR logger*/

#ifdef _SG4
#include <bur/plctypes.h>
typedef STRING exos_string;
typedef BOOL exos_bool;
#else
typedef char exos_string;
typedef bool exos_bool;
#endif

typedef enum
{
    EXOS_LOG_FACILITY_AR = 0,
    EXOS_LOG_FACILITY_GPOS = 1
} EXOS_LOG_FACILITY;

typedef enum
{
    EXOS_LOG_LEVEL_ERROR,
    EXOS_LOG_LEVEL_WARNING,
    EXOS_LOG_LEVEL_SUCCESS,
    EXOS_LOG_LEVEL_INFO,
    EXOS_LOG_LEVEL_DEBUG,
} EXOS_LOG_LEVEL;

typedef enum
{
    EXOS_LOG_TYPE_ALWAYS = 0,
    EXOS_LOG_TYPE_USER = 1,
    EXOS_LOG_TYPE_SYSTEM = 2,
    EXOS_LOG_TYPE_VERBOSE = 4,
} EXOS_LOG_TYPE;

/**
 * \private
*/
typedef struct exos_log_private
{
    uint32_t _magic;
    void *_log;
    void *_reserved[4];
} exos_log_private_t;

typedef struct exos_log_handle exos_log_handle_t;
typedef struct exos_log_config_type exos_log_config_type_t;
typedef struct exos_log_config exos_log_config_t;

typedef void (*exos_config_change_cb)(const exos_log_handle_t *log, const exos_log_config_t *new_config, void *user_context);
struct exos_log_handle
{
    char *name;                             //name of the log handle set in exos_log_init(). read-only
    bool ready;                             //log handle received log config. read-only
    bool excluded;                          //current config excluded this module from logging. read-only
    bool console;                           //additionally log outputs to the console. can be set during runtime by the user
    exos_config_change_cb config_change_cb; //configured config change callback set by exos_log_config_listener()
    void *config_change_user_context;       //configured user context set for the config change callback
    bool _reserved_bool[4];
    uint32_t _reserved_uint32[4];
    void *_reserved[4];

    exos_log_private_t _private;
};

/**
 * Initialize the log handle
 * 
 * very application has a 35 character long name that should preferrably be unique 
 * within the system to easier identify where the specific log message originated from.
*/
EXOS_ERROR_CODE exos_log_init(exos_log_handle_t *log, const char *name);

/**
 * Receive current log configuration
 * 
 * This function is used to receive the log configuration (filter) that is broadcast by the log server.
 * As soon as a configuration has been recieved (i.e. the module knows which filter the log-server / system has set), 
 * the application can send out its logs to the log-server.
*/
EXOS_ERROR_CODE exos_log_process(const exos_log_handle_t *log);

/**
 * Release all resources for a log handle
 * 
 * This function is used to free up the allocated resources (pre-operational send buffer, message queue handles ..) 
 * for this log handle.
*/
EXOS_ERROR_CODE exos_log_delete(exos_log_handle_t *log);

/**
 * Log error message
 * 
 * Only log errors, if you have a problem.
*/
EXOS_ERROR_CODE exos_log_error(const exos_log_handle_t *log, const char *format, ...);

/**
 * Log warning messages
 * 
 * If you want to log warnings that you wish to be visible by default, you should log with the 
 * type flag `EXOS_LOG_TYPE_ALWAYS`.
*/
EXOS_ERROR_CODE exos_log_warning(const exos_log_handle_t *log, EXOS_LOG_TYPE type, const char *format, ...);

/**
 * Log success messages
 * 
 * Success messages constitute rather important information, as it might be a recovery from an error. 
 * 
 * If you want to log messages that you wish to be visible by default, you should log with the
 * type flag `EXOS_LOG_TYPE_ALWAYS`.
*/
EXOS_ERROR_CODE exos_log_success(const exos_log_handle_t *log, EXOS_LOG_TYPE type, const char *format, ...);

/**
 * Log info messages
 * 
 * Info messages are rather pointing to something beyond what is necessary to know for normal operation.
*/
EXOS_ERROR_CODE exos_log_info(const exos_log_handle_t *log, EXOS_LOG_TYPE type, const char *format, ...);

/**
 * Log debug messages
 * 
 * For debug purposes where detailed information is needed, there is one level beyond `EXOS_LOG_LEVEL_INFO` 
 * that should be used for dispatching debug information.
*/
EXOS_ERROR_CODE exos_log_debug(const exos_log_handle_t *log, EXOS_LOG_TYPE type, const char *format, ...);

/**
 * Log output to the console
 * 
 * - In Linux, `exos_log_stdout()` goes directly to the console output of the individual program - identical to `printf(" .. ")`
 * 
 * - The `exos_log_stdout_callback()` can redirect this output to another output function instead of the default `printf()`
 * 
 * - In Automation Runtime, the console output needs to be redirected via `exos_log_stdout_callback()` in order to have any effect.
*/
void exos_log_stdout(const char *format, ...);

/*function to output log message via exos_log_stdout, using the format: [FAC:name] <LEVEL> : text*/
void exos_log_stdout_format(EXOS_LOG_FACILITY facility, const char *name, EXOS_LOG_LEVEL level, const char *text);

typedef void (*exos_log_stdout_cb)(const char *text, void *user_context);

/*function to set the logging callback that is called when exos_log_stdout() is called in this program*/
void exos_log_stdout_callback(exos_log_stdout_cb stdout_callback, void *user_context);

struct exos_log_config_type
{
    exos_bool user;
    exos_bool system;
    exos_bool verbose;
    exos_bool _reserved_bool[8];
};

struct exos_log_config
{
    EXOS_LOG_LEVEL level;
    exos_log_config_type_t type;
    int32_t _reserved_int32[4];
    exos_bool _reserved_bool[4];
    exos_string exclude[EXOS_LOG_EXCLUDE_LIST_LEN][EXOS_LOG_MAX_NAME_LENGTH + 1];
};

/**
 * Change the current log configuration
 * 
 * This function changes the log-server filters (log configuration), i.e. configures which messages (level / type) that should be 
 * sent out. This log configuration is distributed to all logging applications across the system.
*/
EXOS_ERROR_CODE exos_log_change_config(exos_log_handle_t *log, const exos_log_config_t *config);

/**
 * Listen to configuration changes
 * 
 * This function initializes a listener that triggers an `exos_config_change_cb` callback whenever a new configuration is received.
*/
EXOS_ERROR_CODE exos_log_config_listener(exos_log_handle_t *log, exos_config_change_cb config_change_callback, void *user_context);

#define ANSI_COLOR_RED "\x1b[31m"     /**< \private */
#define ANSI_COLOR_GREEN "\x1b[32m"   /**< \private */
#define ANSI_COLOR_RESET "\x1b[0m"    /**< \private */
#define ANSI_COLOR_YELLOW "\x1b[33m"  /**< \private */
#define ANSI_COLOR_BLUE "\x1b[34m"    /**< \private */
#define ANSI_COLOR_WHITE "\x1b[37m"   /**< \private */
#define ANSI_COLOR_MAGENTA "\x1b[35m" /**< \private */
#define ANSI_COLOR_CYAN "\x1b[36m"    /**< \private */

#ifndef EXOS_ASSERT_CALLBACK
#define EXOS_ASSERT_CALLBACK
#endif

//EXOS_ASSERT_LOG should be defined as something like: &log
#ifdef EXOS_ASSERT_LOG
#define ERR_ASSERT(_format_, ...) exos_log_error(EXOS_ASSERT_LOG, _format_, ##__VA_ARGS__);
#else

//EXOS_ASSERT_LOG undefined, use stdout
#ifdef _SG4
#define ERR_ASSERT(_format_, ...)
#else
#define ERR_ASSERT(_format_, ...) exos_log_stdout(ANSI_COLOR_RED _format_ ANSI_COLOR_RESET "\n", ##__VA_ARGS__);
#endif

#endif //EXOS_ASSERT_LOG

#define EXOS_ASSERT(_error_, _exp_)                                                                                     \
    do                                                                                                                  \
    {                                                                                                                   \
        EXOS_ERROR_CODE err = _exp_;                                                                                    \
        if (_error_ != err)                                                                                             \
        {                                                                                                               \
            ERR_ASSERT("Error in file %s:%d", __FILE__, __LINE__);                                                      \
            ERR_ASSERT("%s returned %d (%s) instead of expected %d", #_exp_, err, exos_get_error_string(err), _error_); \
            EXOS_ASSERT_CALLBACK;                                                                                       \
        }                                                                                                               \
    } while (0)

#define EXOS_ASSERT_OK(_exp_) EXOS_ASSERT(EXOS_ERROR_OK, _exp_)

#endif //_EXOS_LOG_H_
