
PROGRAM _INIT

END_PROGRAM

PROGRAM _CYCLIC
    
    //Auto connect:
    //WaterTankCyclic_0.Enable := ExComponentInfo_0.Operational;
	WaterTankCyclic_0(pWaterTank := ADR(WaterTank_0));
    
	ExComponentInfo_0(ExTargetLink := ADR(gTarget_0), ExComponentLink := ADR(gWaterTank_0), Enable := TRUE);
    
	ExDatamodelInfo_0(ExTargetLink := ADR(gTarget_0), Enable := TRUE, InstanceName := 'WaterTank_0');
    
	ExDataConnectionInfo_0(ExTargetLink := ADR(gTarget_0), Enable := TRUE);
	
END_PROGRAM

PROGRAM _EXIT

    WaterTankCyclic_0(Enable := FALSE);

END_PROGRAM
