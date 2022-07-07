/* Automation Studio generated header file */
/* Do not edit ! */
/* ExOS 2.01.0 */

#ifndef _EXOS_
#define _EXOS_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _ExOS_VERSION
#define _ExOS_VERSION 2.01.0
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
#ifdef _SG3
		#include "ExDeploy.h"
		#include "ExData.h"
#endif
#ifdef _SG4
		#include "ExDeploy.h"
		#include "ExData.h"
#endif
#ifdef _SGC
		#include "ExDeploy.h"
		#include "ExData.h"
#endif


/* Datatypes and datatypes of function blocks */
typedef enum ExLogLevelEnum
{	exOS_LOG_LEVEL_ERROR,
	exOS_LOG_LEVEL_WARNING,
	exOS_LOG_LEVEL_SUCCESS,
	exOS_LOG_LEVEL_INFO,
	exOS_LOG_LEVEL_DEBUG
} ExLogLevelEnum;

typedef enum ExErrorEnum
{	exOS_ERR_OK = 0,
	exOS_ERR_BAD_TARGET_LINK,
	exOS_ERR_BAD_COMPONENT_LINK,
	exOS_ERR_INVALID_DATAMODEL,
	exOS_ERR_NOT_RESPONSIVE,
	exOS_ERR_NOT_SYNCHRONIZED,
	exOS_ERR_NOT_CONFIGURED,
	exOS_ERR_OVERFLOW,
	exOS_ERR_PARAMETER_MISSING,
	exOS_ERR_API_ERROR
} ExErrorEnum;

typedef struct ExComponentLink
{	unsigned long internal;
} ExComponentLink;

typedef struct ExLogConfigFilterType
{	plcbit User;
	plcbit System;
	plcbit Verbose;
} ExLogConfigFilterType;

typedef struct ExLogConfigType
{	enum ExLogLevelEnum Level;
	struct ExLogConfigFilterType Filter;
	plcstring ExcludeModule[20][36];
} ExLogConfigType;

typedef struct ExProcessSyncTargetType
{	unsigned long CycleTime;
	unsigned long ProcessTime;
	unsigned long IdleTime;
	unsigned long CycleTimeViolations;
	unsigned long MissedCycles;
} ExProcessSyncTargetType;

typedef struct ExProcessSyncType
{	struct ExProcessSyncTargetType Local;
	struct ExProcessSyncTargetType Remote;
} ExProcessSyncType;

typedef struct ExTimeSyncType
{	plcbit TargetResponsive;
	plcbit PrecisionReached;
	signed long PrecisionError;
} ExTimeSyncType;

typedef struct ExTargetLink
{	unsigned long internal;
} ExTargetLink;

typedef struct ExDataConnectionDiagTargetType
{	unsigned long DatamodelsConfigured;
	unsigned long DatamodelsActive;
	unsigned long DatamodelErrors;
} ExDataConnectionDiagTargetType;

typedef struct ExDataTransferType
{	unsigned long Bytes;
	unsigned long KiB;
	unsigned long MiB;
	unsigned long GiB;
} ExDataTransferType;

typedef struct ExDataConnectionDiagType
{	struct ExDataConnectionDiagTargetType Local;
	struct ExDataConnectionDiagTargetType Remote;
	struct ExDataTransferType DataTransmitted;
	struct ExDataTransferType DataReceived;
} ExDataConnectionDiagType;

typedef struct ExTargetCounterType
{	unsigned long Local;
	unsigned long Remote;
} ExTargetCounterType;

typedef struct ExTargetDiagComponentType
{	unsigned long Configured;
	unsigned long Deploying;
	unsigned long Operational;
	unsigned long Stopped;
	unsigned long Aborted;
} ExTargetDiagComponentType;

typedef struct ExTargetDiagType
{	struct ExTargetDiagComponentType Components;
} ExTargetDiagType;

typedef struct ExDatamodelDiagTargetType
{	unsigned long DatasetsActive;
	unsigned long DatasetErrors;
} ExDatamodelDiagTargetType;

typedef struct ExDatamodelDiagType
{	struct ExDatamodelDiagTargetType Local;
	struct ExDatamodelDiagTargetType Remote;
	struct ExDataTransferType DataTransmitted;
	struct ExDataTransferType DataReceived;
} ExDatamodelDiagType;

typedef struct ExComponenInfoDiagFilesType
{	unsigned long Configured;
	unsigned long Deployed;
	unsigned long Failed;
} ExComponenInfoDiagFilesType;

typedef struct ExComponenInfoDiagStartSvcType
{	unsigned long Configured;
	unsigned long Finished;
	unsigned long Failed;
} ExComponenInfoDiagStartSvcType;

typedef struct ExComponenInfoDiagRunSvcType
{	unsigned long Configured;
	unsigned long Running;
	unsigned long Stopped;
	unsigned long Failed;
} ExComponenInfoDiagRunSvcType;

typedef struct ExComponenInfoDiagType
{	struct ExComponenInfoDiagFilesType Files;
	struct ExComponenInfoDiagStartSvcType StartupServices;
	struct ExComponenInfoDiagRunSvcType RuntimeServices;
} ExComponenInfoDiagType;

typedef struct ExLogConfig
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	struct ExLogConfigType* LogConfig;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	signed long ErrorID;
	/* VAR (analog) */
	unsigned long Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit Update;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit UpdateDone;
} ExLogConfig_typ;

typedef struct ExSyncInfo
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct ExProcessSyncType ProcessSync;
	struct ExTimeSyncType TimeSync;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
} ExSyncInfo_typ;

typedef struct ExDataConnectionInfo
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct ExDataConnectionDiagType Diag;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit TargetConnected;
	plcbit TargetSynchronized;
	plcbit LoggerConnected;
} ExDataConnectionInfo_typ;

typedef struct ExDatamodelInfo
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	plcstring InstanceName[36];
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct ExTargetCounterType PeersConnected;
	struct ExDatamodelDiagType Diag;
	/* VAR (analog) */
	unsigned long internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit TargetConnected;
} ExDatamodelInfo_typ;

typedef struct ExTargetInfo
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct ExTargetDiagType Diag;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit Deploying;
	plcbit Operational;
	plcbit Stopped;
	plcbit Aborted;
} ExTargetInfo_typ;

typedef struct ExComponentInfo
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	struct ExComponentLink* ExComponentLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	plcstring Name[36];
	struct ExComponenInfoDiagType Diag;
	/* VAR (analog) */
	unsigned long internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit Deploying;
	plcbit Operational;
	plcbit Stopped;
	plcbit Aborted;
} ExComponentInfo_typ;

typedef struct ExTargetClockDeviation
{
	/* VAR_INPUT (analog) */
	struct ExTargetLink* ExTargetLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	signed long DeviationPerHour;
	/* VAR (analog) */
	signed long internal[5];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
} ExTargetClockDeviation_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void ExLogConfig(struct ExLogConfig* inst);
_BUR_PUBLIC void ExSyncInfo(struct ExSyncInfo* inst);
_BUR_PUBLIC void ExDataConnectionInfo(struct ExDataConnectionInfo* inst);
_BUR_PUBLIC void ExDatamodelInfo(struct ExDatamodelInfo* inst);
_BUR_PUBLIC void ExTargetInfo(struct ExTargetInfo* inst);
_BUR_PUBLIC void ExComponentInfo(struct ExComponentInfo* inst);
_BUR_PUBLIC void ExTargetClockDeviation(struct ExTargetClockDeviation* inst);


#ifdef __cplusplus
};
#endif
#endif /* _EXOS_ */

