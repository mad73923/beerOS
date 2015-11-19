/*
 * dummyTask.c
 *
 * Created: 11.11.2015 14:29:48
 *  Author: matweis
 */ 

void dummyTask(){
	
	while(1){
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		int i=0;
		while(i<100){
			i++;
			asm volatile ("nop");			
		}
	}
	
}