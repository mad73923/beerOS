

static const uint32_t MEMORY_SIZE = 2**20;
uint32_t numberOfSegments = MEMORY_SIZE/sizeof(Segment);

Segment theHeap[numberOfSegments];