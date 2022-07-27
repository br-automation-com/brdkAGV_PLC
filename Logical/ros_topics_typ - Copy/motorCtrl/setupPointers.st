
ACTION setupPointers: 

	this ACCESS ADR(localVariables[i]);
	config ACCESS ADR(localVariables[i].hmi.config);
	hw ACCESS ADR(localVariables[i].hw);
	hmi ACCESS ADR(localVariables[i].hmi);
	
END_ACTION


ACTION setupWatchPointers: 
	
	i := watchIdx;
	this ACCESS ADR(localVariables[i]);
	config ACCESS ADR(localVariables[i].hmi.config);
	hw ACCESS ADR(localVariables[i].hw);
	hmi ACCESS ADR(localVariables[i].hmi);
	
END_ACTION
