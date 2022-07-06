
FUNCTION_BLOCK ExLogConfig (*Get or set the exOS data logger configuration.*)
	VAR_INPUT
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		LogConfig : REFERENCE TO ExLogConfigType; (*exOS Logger configuration.*)
		Update : BOOL; (*Update the exOS Logger configuration (if set, the configuration is updated, otherwise the current configuration is read).*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		UpdateDone : BOOL; (*exOS Logger configuration successfully updated.*)
	END_VAR
	VAR
		Internal : UDINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExSyncInfo (*Get synchronization information of an exOS Target.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		ProcessSync : ExProcessSyncType; (*Process synchronization information.*)
		TimeSync : ExTimeSyncType; (*Time synchronization information.*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExDataConnectionInfo (*Get information about the data connection to an exOS Target.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		TargetConnected : BOOL; (*Data connection to the exOS Target is established.*)
		TargetSynchronized : BOOL; (*exOS Target is synchronized with AR.*)
		LoggerConnected : BOOL; (*Remote Logger is connected.*)
		Diag : ExDataConnectionDiagType; (*Diagnostic data of the data connection.*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExDatamodelInfo (*Get information about a datamodel connection within an exOS Target.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
		InstanceName : STRING[35]; (*Instance name of the datamodel.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		TargetConnected : BOOL; (*Data connection to the exOS Target is established.*)
		PeersConnected : ExTargetCounterType; (*Number of conencted peers.*)
		Diag : ExDatamodelDiagType; (*Diagnostic data of the datamodel.*)
	END_VAR
	VAR
		internal : UDINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExTargetInfo (*Get deployment and execution information of an exOS Target.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		Deploying : BOOL; (*exOS Target is deploying.*)
		Operational : BOOL; (*exOS Target is operational.*)
		Stopped : BOOL; (*exOS Target is stopped.*)
		Aborted : BOOL; (*exOS Target is aborted.*)
		Diag : ExTargetDiagType; (*Diagnostic data of the exOS Target.*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExComponentInfo (*Get deployment and execution information of an exOS Component.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		ExComponentLink : REFERENCE TO ExComponentLink; (*Connection to exOS Component configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		Name : STRING[35]; (*Name of the exOS Component.*)
		Deploying : BOOL; (*exOS Component is deploying.*)
		Operational : BOOL; (*exOS Component is operational.*)
		Stopped : BOOL; (*exOS Component is stopped.*)
		Aborted : BOOL; (*exOS Component is aborted.*)
		Diag : ExComponenInfoDiagType; (*Diagnostic data of the exOS Component.*)
	END_VAR
	VAR
		internal : UDINT;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK ExTargetClockDeviation (*Get clock deviation of an exOS Target.*)
	VAR_INPUT
		ExTargetLink : REFERENCE TO ExTargetLink; (*Connection to exOS Target configuration.*)
		Enable : BOOL; (*The function block is active as long as this input is set.*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block active.*)
		Error : BOOL; (*Error occurred during execution.*)
		StatusID : DINT; (*Status information.*)
		DeviationPerHour : DINT; (*Clock deviation of the exOS Target per hour in microseconds.*)
	END_VAR
	VAR
		internal : ARRAY[0..4] OF DINT;
	END_VAR
END_FUNCTION_BLOCK
