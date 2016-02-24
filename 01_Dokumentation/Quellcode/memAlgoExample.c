uint16_t worstFit(uint16_t size){
	MemoryRequest memoryRequest;
	memoryManagement_initMemoryRequest(&memoryRequest, size);
	
    uint16_t memId = 0;
    uint16_t currentGapSize = MAX_UINT16;
    
	while(memId = memoryManagement_next(&memoryRequest)){
        uint16_t nextGapSize = memoryRequest.gapSize;
		
        if(nextGapSize > currentGapSize){
            currentGapSize = nextGapSize;
            memId = memoryRequest.memId;
        }		
	}
    
    if(currentGapSize == MAX_UINT16){
        return NULL;    
    }    
    
    memoryRequest.memId = memId;    
    return memoryManagement_alloc(&memoryRequest);	
}