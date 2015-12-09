/*
 * SignalTest.c
 *
 * Created: 09.12.2015 18:53:21
 *  Author: anreinha
 */ 

volatile signal signal1;

volatile int task1Cnt = 0;
volatile int task2Cnt = 0;

void dummyTaskSignalTest(){
	if(task == 0){
		initSignal(&signal1);
	}
	while(1){
		if(task == 0){
			yieldTask();
			yieldTask();
			sendSignal(&signal1);
			task1Cnt++;
		}else{
			waitSignal(&signal1);
			task2Cnt++;
		}
		asm volatile ("nop");
		if(task1Cnt - task2Cnt > 1 || task1Cnt - task2Cnt < -1){
			kernelPanic();
		}
	}
}