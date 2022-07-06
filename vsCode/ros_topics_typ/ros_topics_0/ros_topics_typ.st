
PROGRAM _INIT

    ros_topics_typInit_0();

END_PROGRAM

PROGRAM _CYCLIC
    
    //Auto connect:
    //ros_topics_typCyclic_0.Enable := ExComponentInfo_0.Operational; // Component has been deployed and started up successfully
    
    //Auto connect when deployment is off and manually started in GPOS:
    //ros_topics_typCyclic_0.Enable := TRUE;
    //ros_topics_typCyclic_0.Start := ros_topics_typCyclic_0.Connected;
    
    ros_topics_typCyclic_0(Handle := ros_topics_typInit_0.Handle, pros_topics_typ := ADR(ros_topics_typ_0));
    
    ExComponentInfo_0(ExTargetLink := ADR(gTarget_0), ExComponentLink := ADR(gros_topics_typ_0), Enable := TRUE);
    
    ExDatamodelInfo_0(ExTargetLink := ADR(gTarget_0), Enable := TRUE, InstanceName := 'ros_topics_typ_0');
    
END_PROGRAM

PROGRAM _EXIT

    ros_topics_typExit_0(Handle := ros_topics_typInit_0.Handle);

END_PROGRAM
