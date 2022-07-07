
TYPE
	WaterTank : 	STRUCT 
		FillValve : VALVE_STATE; (*PUB*)
		EnableHeater : BOOL; (*PUB*)
		HeaterConfig : WaterTankHeaterConfig; (*PUB SUB*)
		Status : WaterTankStatus; (*SUB*)
		StatusDelay : DINT;
		StatusUpdates : UDINT;
	END_STRUCT;
	WaterTankHeaterConfig : 	STRUCT 
		MaxTemperature : REAL;
		MaxPower : REAL;
	END_STRUCT;
	WaterTankStatus : 	STRUCT 
		LevelHigh : BOOL;
		LevelLow : BOOL;
		FillValveDelay : DINT;
		WaterLevel : DINT;
		Heater : WaterTankHeaterStatus;
	END_STRUCT;
	WaterTankHeaterStatus : 	STRUCT 
		WaterTemperature : REAL;
		HeatingActive : BOOL;
	END_STRUCT;
	VALVE_STATE : 
		(
		VALVE_CLOSED := 0,
		VALVE_OPEN := 1
		);
END_TYPE
