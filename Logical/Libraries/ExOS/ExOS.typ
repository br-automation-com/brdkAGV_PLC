
TYPE
	ExComponentLink : 	STRUCT  (*Unique identification of an exOS Component.*)
		internal : UDINT;
	END_STRUCT;
	ExLogConfigFilterType : 	STRUCT  (*exOS Logger message filter settings.*)
		User : BOOL; (*Log user-application specific messages.*)
		System : BOOL; (*Log system messages of the Data Message Router.*)
		Verbose : BOOL; (*Log verbose messages.*)
	END_STRUCT;
	ExLogConfigType : 	STRUCT  (*exOS Logger configuration.*)
		Level : ExLogLevelEnum; (*Log level setting.*)
		Filter : ExLogConfigFilterType; (*exOS Logger message filter settings.*)
		ExcludeModule : ARRAY[0..19]OF STRING[35]; (*List of exOS Logger modules that are excluded from logging.*)
	END_STRUCT;
	ExLogLevelEnum : 
		( (*Log levels of the exOS Logger.*)
		exOS_LOG_LEVEL_ERROR, (*Log only errors.*)
		exOS_LOG_LEVEL_WARNING, (*Log errors and warnings.*)
		exOS_LOG_LEVEL_SUCCESS, (*Log errors, warnings, and success events.*)
		exOS_LOG_LEVEL_INFO, (*Log errors, warnings, success events and further information.*)
		exOS_LOG_LEVEL_DEBUG (*Log everything (incl. debug messages).*)
		);
	ExProcessSyncTargetType : 	STRUCT  (*Process synchronization information of a specific target.*)
		CycleTime : UDINT; (*Cycle time of the Data Message Router in microseconds.*)
		ProcessTime : UDINT; (*Process time of the Data Message Router in microseconds.*)
		IdleTime : UDINT; (*Idle time of the Data Message Router in microseconds.*)
		CycleTimeViolations : UDINT; (*Number of cycle time violations (always 0 on AR).*)
		MissedCycles : UDINT; (*Number of missed cycles (always 0 on AR).*)
	END_STRUCT;
	ExProcessSyncType : 	STRUCT  (*Process synchronization information.*)
		Local : ExProcessSyncTargetType; (*Process synchronization information for the local system.*)
		Remote : ExProcessSyncTargetType; (*Process synchronization information for the remote system.*)
	END_STRUCT;
	ExTimeSyncType : 	STRUCT  (*Time synchronization information.*)
		TargetResponsive : BOOL; (*The exOS Target is responding (i.e. answering a request within the timeout interval).*)
		PrecisionReached : BOOL; (*The exOS Target has reached the configured precision of synchronization.*)
		PrecisionError : DINT; (*Current NETTIME deviation in Linux, measured in microseconds.*)
	END_STRUCT;
	ExErrorEnum : 
		( (*exOS error numbers.*)
		exOS_ERR_OK := 0, (*No error.*)
		exOS_ERR_BAD_TARGET_LINK, (*The provided ExTargetLink is invalid.*)
		exOS_ERR_BAD_COMPONENT_LINK, (*The provided ExComponentLink is invalid.*)
		exOS_ERR_INVALID_DATAMODEL, (*The datamodel has become invalid.*)
		exOS_ERR_NOT_RESPONSIVE, (*The time synchronization is not responsive.*)
		exOS_ERR_NOT_SYNCHRONIZED, (*The time synchronization has not reached the configured precision.*)
		exOS_ERR_NOT_CONFIGURED, (*The datamodel is not configured on this target.*)
		exOS_ERR_OVERFLOW, (*An overflow occurred.*)
		exOS_ERR_PARAMETER_MISSING, (*A mandatory parameter is missing.*)
		exOS_ERR_API_ERROR (*An internal API error occured, see ErrorID.*)
		);
	ExTargetLink : 	STRUCT  (*Unique identification of an exOS Target.*)
		internal : UDINT;
	END_STRUCT;
	ExDataConnectionDiagTargetType : 	STRUCT  (*Diagnostic data of the data connection of a specific target.*)
		DatamodelsConfigured : UDINT; (*Number of datamodels in the target configuration*)
		DatamodelsActive : UDINT; (*Number datamodels connected to local applications.*)
		DatamodelErrors : UDINT; (*Counter failed connection attempts from local applications.*)
	END_STRUCT;
	ExDataConnectionDiagType : 	STRUCT  (*Diagnostic data of the data connection.*)
		Local : ExDataConnectionDiagTargetType; (*Diagnostic data of the data connection for AR.*)
		Remote : ExDataConnectionDiagTargetType; (*Diagnostic data of the data connection for Linux.*)
		DataTransmitted : ExDataTransferType; (*Counter of overall transmitted data to Linux.*)
		DataReceived : ExDataTransferType; (*Counter of overall received data from Linux.*)
	END_STRUCT;
	ExDataTransferType : 	STRUCT  (*Counter of transferred data.*)
		Bytes : UDINT; (*Number of Bytes (0..1023).*)
		KiB : UDINT; (*Number of Kibibytes (0..1023).*)
		MiB : UDINT; (*Number of Mebibytes (0..1023).*)
		GiB : UDINT; (*Number of Gibibytes.*)
	END_STRUCT;
	ExTargetCounterType : 	STRUCT  (*Number of conencted peers.*)
		Local : UDINT; (*Number of AR connections to this datamodel.*)
		Remote : UDINT; (*Number of Linux connections to this datamodel.*)
	END_STRUCT;
	ExTargetDiagComponentType : 	STRUCT  (*Diagnostic data of the exOS Components of an exOS Target.*)
		Configured : UDINT; (*Number of configured components.*)
		Deploying : UDINT; (*Number of deploying components.*)
		Operational : UDINT; (*Number of operational components.*)
		Stopped : UDINT; (*Number of stopped components.*)
		Aborted : UDINT; (*Number of aborted components.*)
	END_STRUCT;
	ExTargetDiagType : 	STRUCT  (*Diagnostic data of an exOS Target.*)
		Components : ExTargetDiagComponentType; (*Diagnostic data of the exOS Components of an exOS Target.*)
	END_STRUCT;
	ExDatamodelDiagTargetType : 	STRUCT  (*Diagnostic data of the datamodel of a specific target.*)
		DatasetsActive : UDINT; (*Number of datasets registered from local applications.*)
		DatasetErrors : UDINT; (*Counter of dataset errors, due to buffer overflow or configuration errors.*)
	END_STRUCT;
	ExDatamodelDiagType : 	STRUCT  (*Diagnostic data of the datamodel.*)
		Local : ExDatamodelDiagTargetType; (*Diagnostic data of the datamodel in AR.*)
		Remote : ExDatamodelDiagTargetType; (*Diagnostic data of the datamodel in Linux.*)
		DataTransmitted : ExDataTransferType; (*Counter of transmitted data to Linux.*)
		DataReceived : ExDataTransferType; (*Counter of received data from Linux.*)
	END_STRUCT;
	ExComponenInfoDiagFilesType : 	STRUCT  (*Diagnostic data of the files of an exOS Component.*)
		Configured : UDINT; (*Number of configured files.*)
		Deployed : UDINT; (*Number of deployed files.*)
		Failed : UDINT; (*Number of failed (not found) files.*)
	END_STRUCT;
	ExComponenInfoDiagStartSvcType : 	STRUCT  (*Diagnostic data of the startup services of an exOS Component.*)
		Configured : UDINT; (*Number of configured startup services.*)
		Finished : UDINT; (*Number of finished startup services.*)
		Failed : UDINT; (*Number of failed startup services.*)
	END_STRUCT;
	ExComponenInfoDiagRunSvcType : 	STRUCT  (*Diagnostic data of the runtime services of an exOS Component.*)
		Configured : UDINT; (*Number of configured services.*)
		Running : UDINT; (*Number of running services.*)
		Stopped : UDINT; (*Number of actively stopped services.*)
		Failed : UDINT; (*Number of failed runtime services.*)
	END_STRUCT;
	ExComponenInfoDiagType : 	STRUCT  (*Diagnostic data of an exOS Component.*)
		Files : ExComponenInfoDiagFilesType; (*Diagnostic data of the files of an exOS Component.*)
		StartupServices : ExComponenInfoDiagStartSvcType; (*Diagnostic data of the startup services of an exOS Component.*)
		RuntimeServices : ExComponenInfoDiagRunSvcType; (*Diagnostic data of the runtime services of an exOS Component.*)
	END_STRUCT;
END_TYPE
