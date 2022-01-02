#include <stdio.h>
#include <time.h>
#include <string.h> 
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int dst_ip;
int len;
int priority;
int queue1[4][4],queue2[4][4],queue3[4][4],queue4[4][4]; /*queue of each port 10.0.20.x -> queue1 , 10.0.12.x -> queue2 , 10.0.50.x -> queue3 , 10.0.70.x -> queue4
                                                           4 is the head, 1 is the tail of the queue. */
int *p100=&queue1[0][0],*p101=&queue1[0][1],*p102=&queue1[0][2],*p103=&queue1[0][3],
	*p110=&queue1[1][0],*p111=&queue1[1][1],*p112=&queue1[1][2],*p113=&queue1[1][3],
	*p120=&queue1[2][0],*p121=&queue1[2][1],*p122=&queue1[2][2],*p123=&queue1[2][3],
	*p130=&queue1[3][0],*p131=&queue1[3][1],*p132=&queue1[3][2],*p133=&queue1[3][3];   // pointers of the rows and columns in queue1 

int *p200=&queue2[0][0],*p201=&queue2[0][1],*p202=&queue2[0][2],*p203=&queue2[0][3],
	*p210=&queue2[1][0],*p211=&queue2[1][1],*p212=&queue2[1][2],*p213=&queue2[1][3],
	*p220=&queue2[2][0],*p221=&queue2[2][1],*p222=&queue2[2][2],*p223=&queue2[2][3],
	*p230=&queue2[3][0],*p231=&queue2[3][1],*p232=&queue2[3][2],*p233=&queue2[3][3];   // pointers of the rows and columns in queue2 

int *p300=&queue3[0][0],*p301=&queue3[0][1],*p302=&queue3[0][2],*p303=&queue3[0][3],
	*p310=&queue3[1][0],*p311=&queue3[1][1],*p312=&queue3[1][2],*p313=&queue3[1][3],
	*p320=&queue3[2][0],*p321=&queue3[2][1],*p322=&queue3[2][2],*p323=&queue3[2][3],
	*p330=&queue3[3][0],*p331=&queue3[3][1],*p332=&queue3[3][2],*p333=&queue3[3][3];   // pointers of the rows and columns in queue3 

int *p400=&queue4[0][0],*p401=&queue4[0][1],*p402=&queue4[0][2],*p403=&queue4[0][3],
	*p410=&queue4[1][0],*p411=&queue4[1][1],*p412=&queue4[1][2],*p413=&queue4[1][3],
	*p420=&queue4[2][0],*p421=&queue4[2][1],*p422=&queue4[2][2],*p423=&queue4[2][3],
	*p430=&queue4[3][0],*p431=&queue4[3][1],*p432=&queue4[3][2],*p433=&queue4[3][3];   // pointers of the rows and columns in queue4 

int dropRate = 0;
long long int lenCounter = 0;
int routedpackets = 0;

int sizeof1,sizeof2,sizeof3,sizeof4;

void enqueue(int packet_array[]){
	if(packet_array[0] == 20){
		if (*p101 == 0){
		*p101 = packet_array[0];*p102 = packet_array[1];*p103 = packet_array[2];
		}
		else{
			if(*p111 == 0){
				*p111 = *p101;*p112 = *p102;*p113 = *p103;
				*p101 = packet_array[0];*p102 = packet_array[1];*p103 = packet_array[2];
			}
			else{
				if(*p121 == 0){
					*p121 = *p111;*p122 = *p112;*p123 = *p113;
					*p111 = *p101;*p112 = *p102;*p113 = *p103;
					*p101 = packet_array[0];*p102 = packet_array[1];*p103 = packet_array[2];
				}
				else{
					*p131 = *p121;*p132 = *p122;*p133 = *p123;
					*p121 = *p111;*p122 = *p112;*p123 = *p113;
					*p111 = *p101;*p112 = *p102;*p113 = *p103;
					*p101 = packet_array[0];*p102 = packet_array[1];*p103 = packet_array[2];
				}
			}
		}
	}
	if (packet_array[0] == 12){if (*p201 == 0){
		*p201 = packet_array[0];*p202 = packet_array[1];*p203 = packet_array[2];
		}
		else{
			if(*p211 == 0){
				*p211 = *p201;*p212 = *p202;*p213 = *p203;
				*p201 = packet_array[0];*p202 = packet_array[1];*p203 = packet_array[2];
			}
			else{
				if(*p221 == 0){
					*p221 = *p211;*p222 = *p212;*p223 = *p213;
					*p211 = *p201;*p212 = *p202;*p213 = *p203;
					*p201 = packet_array[0];*p202 = packet_array[1];*p203 = packet_array[2];
				}
				else{
					*p231 = *p221;*p232 = *p222;*p233 = *p223;
					*p221 = *p211;*p222 = *p212;*p223 = *p213;
					*p211 = *p201;*p212 = *p202;*p213 = *p203;
					*p201 = packet_array[0];*p202 = packet_array[1];*p203 = packet_array[2];
				}
			}
		}
	}
	if (packet_array[0] == 50){if (*p301 == 0){
		*p301 = packet_array[0];*p302 = packet_array[1];*p303 = packet_array[2];
		}
		else{
			if(*p311 == 0){
				*p311 = *p301;*p312 = *p302;*p313 = *p303;
				*p301 = packet_array[0];*p302 = packet_array[1];*p303 = packet_array[2];
			}
			else{
				if(*p321 == 0){
					*p321 = *p311;*p322 = *p312;*p323 = *p313;
					*p311 = *p301;*p312 = *p302;*p313 = *p303;
					*p301 = packet_array[0];*p302 = packet_array[1];*p303 = packet_array[2];
				}
				else{
					*p331 = *p321;*p332 = *p322;*p333 = *p323;
					*p321 = *p311;*p322 = *p312;*p323 = *p313;
					*p311 = *p301;*p312 = *p302;*p313 = *p303;
					*p301 = packet_array[0];*p302 = packet_array[1];*p303 = packet_array[2];
				}
			}
		}
	}
	if (packet_array[0] == 70){if (*p401 == 0){
		*p401 = packet_array[0];*p402 = packet_array[1];*p403 = packet_array[2];
		}
		else{
			if(*p411 == 0){
				*p411 = *p401;*p412 = *p402;*p413 = *p403;
				*p401 = packet_array[0];*p402 = packet_array[1];*p403 = packet_array[2];
			}
			else{
				if(*p421 == 0){
					*p421 = *p411;*p422 = *p412;*p423 = *p413;
					*p411 = *p401;*p412 = *p402;*p413 = *p403;
					*p401 = packet_array[0];*p402 = packet_array[1];*p403 = packet_array[2];
				}
				else{
					*p431 = *p421;*p432 = *p422;*p433 = *p423;
					*p421 = *p411;*p422 = *p412;*p423 = *p413;
					*p411 = *p401;*p412 = *p402;*p413 = *p403;
					*p401 = packet_array[0];*p402 = packet_array[1];*p403 = packet_array[2];
				}
			}
		}
	}
}

void drop(int packet_array[]){
	dropRate += 1;
	if (packet_array[2] == 0){
		packet_array[0] = 0; packet_array[1] = 0; packet_array[2] = 2; // if the incoming packet is low priority, it gets dropped.
	}
	else{
		if(packet_array[0] == 20){
			if (*p103 == 0){
				*p101 = 0; *p102 = 0; *p103 = 2;
			}
			else{
				if (*p113 == 0){
					*p111 = *p101; *p112 = *p102; *p113 = *p103;
					*p101 = 0; *p102 = 0; *p103 = 2;
				}
				else{
					if(*p123 == 0){
						*p121 = *p111; *p122 = *p112; *p123 = *p113;
						*p111 = *p101; *p112 = *p102; *p113 = *p103;
						*p101 = 0; *p102 = 0; *p103 = 2;
					}
					else{
						if (*p133 == 0){
							*p131 = *p121; *p132 = *p122; *p133 = *p123;
							*p121 = *p111; *p122 = *p112; *p123 = *p113;
							*p111 = *p101; *p112 = *p102; *p113 = *p103;
							*p101 = 0; *p102 = 0; *p103 = 2;
						}
						else{
							packet_array[0] = 0; packet_array[1] = 0; packet_array[2] = 2; // if there is no low priority packets, incoming packet gets dropped.
						}
					}
				}
			}
		}
		if(packet_array[0] == 12){if (*p203 == 0){
				*p201 = 0; *p202 = 0; *p203 = 2;
			}
			else{
				if (*p213 == 0){
					*p211 = *p201; *p212 = *p202; *p213 = *p203;
					*p201 = 0; *p202 = 0; *p203 = 2;
				}
				else{
					if(*p223 == 0){
						*p221 = *p211; *p222 = *p212; *p223 = *p213;
						*p211 = *p201; *p212 = *p202; *p213 = *p203;
						*p201 = 0; *p202 = 0; *p203 = 2;
					}
					else{
						if (*p233 == 0){
							*p231 = *p221; *p232 = *p222; *p233 = *p223;
							*p221 = *p211; *p222 = *p212; *p223 = *p213;
							*p211 = *p201; *p212 = *p202; *p213 = *p203;
							*p201 = 0; *p202 = 0; *p203 = 2;
						}
						else{
							packet_array[0] = 0; packet_array[1] = 0; packet_array[2] = 2; // if there is no low priority packets, incoming packet gets dropped.
						}
					}
				}
			}
		}
		if(packet_array[0] == 50){if (*p303 == 0){
				*p301 = 0; *p302 = 0; *p303 = 2;
			}
			else{
				if (*p313 == 0){
					*p311 = *p301; *p312 = *p302; *p313 = *p303;
					*p301 = 0; *p302 = 0; *p303 = 2;
				}
				else{
					if(*p323 == 0){
						*p321 = *p311; *p322 = *p312; *p323 = *p313;
						*p311 = *p301; *p312 = *p302; *p313 = *p303;
						*p301 = 0; *p302 = 0; *p303 = 2;
					}
					else{
						if (*p333 == 0){
							*p331 = *p321; *p332 = *p322; *p333 = *p323;
							*p321 = *p311; *p322 = *p312; *p323 = *p313;
							*p311 = *p301; *p312 = *p302; *p313 = *p303;
							*p301 = 0; *p302 = 0; *p303 = 2;
						}
						else{
							packet_array[0] = 0; packet_array[1] = 0; packet_array[2] = 2; // if there is no low priority packets, incoming packet gets dropped.
						}
					}
				}
			}
		}
		if(packet_array[0] == 70){if (*p403 == 0){
				*p401 = 0; *p402 = 0; *p403 = 2;
			}
			else{
				if (*p413 == 0){
					*p411 = *p401; *p412 = *p402; *p413 = *p403;
					*p401 = 0; *p402 = 0; *p403 = 2;
				}
				else{
					if(*p423 == 0){
						*p421 = *p411; *p422 = *p412; *p423 = *p413;
						*p411 = *p401; *p412 = *p402; *p413 = *p403;
						*p401 = 0; *p402 = 0; *p403 = 2;
					}
					else{
						if (*p433 == 0){
							*p431 = *p421; *p432 = *p422; *p433 = *p423;
							*p421 = *p411; *p422 = *p412; *p423 = *p413;
							*p411 = *p401; *p412 = *p402; *p413 = *p403;
							*p401 = 0; *p402 = 0; *p403 = 2;
						}
						else{
							packet_array[0] = 0; packet_array[1] = 0; packet_array[2] = 2; // if there is no low priority packets, incoming packet gets dropped.
						}
					}
				}
			}
		}
	}    	
}

void dequeue(void){
	if(*p103 == 2){
		;
	}
	else{
	lenCounter += *p132;
	*p131 = *p121; *p132 = *p122; *p133 = *p123;
	*p121 = *p111; *p122 = *p112; *p123 = *p113;
	*p111 = *p101; *p112 = *p102; *p113 = *p103;
	*p101 = 0; *p102 = 0; *p103 = 2;
	routedpackets += 1;
	}
	if(*p203 == 2){
	;
	}
	else{
	lenCounter += *p232;
	*p231 = *p221; *p232 = *p222; *p233 = *p223;
	*p221 = *p211; *p222 = *p212; *p223 = *p213;
	*p211 = *p201; *p212 = *p202; *p213 = *p203;
	*p201 = 0; *p202 = 0; *p203 = 2;
	routedpackets += 1;
	}
	if(*p303 == 2){
		;
	}
	else{
	lenCounter += *p332;
	*p331 = *p321; *p332 = *p322; *p333 = *p323;
	*p321 = *p311; *p322 = *p312; *p323 = *p313;
	*p311 = *p301; *p312 = *p302; *p313 = *p303;
	*p301 = 0; *p302 = 0; *p303 = 2;
	routedpackets += 1;
	}
	if(*p403 == 2){
		;
	}
	else{
	lenCounter += *p432;
	*p431 = *p421; *p432 = *p422; *p433 = *p423;
	*p421 = *p411; *p422 = *p412; *p423 = *p413;
	*p411 = *p401; *p412 = *p402; *p413 = *p403;
	*p401 = 0; *p402 = 0; *p403 = 2;
	routedpackets += 1;
	}
}

int main(void){
	*p100 = 1; *p110 = 2; *p120 = 3; *p130 = 4; //definiton of the queue slot indexes for each queue
	*p200 = 1; *p210 = 2; *p220 = 3; *p230 = 4;
	*p300 = 1; *p310 = 2; *p320 = 3; *p330 = 4;
	*p400 = 1; *p410 = 2; *p420 = 3; *p430 = 4;
	
	*p103 = 2; *p113 = 2; *p123 = 2; *p133 = 2; //at first the priority values are set to be different than 0 and 1.
	*p203 = 2; *p213 = 2; *p223 = 2; *p233 = 2;
	*p303 = 2; *p313 = 2; *p323 = 2; *p333 = 2;
	*p403 = 2; *p413 = 2; *p423 = 2; *p433 = 2;
	
	srand(time(NULL)); //to create a random number
	int dst_ip_generator[] = {20,12,50,70};
	
	float congestion_ratio;
	float sim_time;
	
	printf("Enter the congestion ratio between 0 and 1:");
	scanf("%f",&congestion_ratio);
	printf("\nEnter total simulation time:");
	scanf("%f",&sim_time);
	
	
	int enqueueRate,dequeueRate; //how many times enqueue and dequeue functions will be called
	
	clock_t t1,t2,t3;
	float executionTime,displayCheck;
	int int_displayCheck;	
	t1 = clock();
	
	while (1){
		
		int packet_ip1 = rand() % 256; //these variables work as 192.168.packet_ip1.packet_ip2
		int packet_ip2 = rand() % 256;
		
		len = rand() % 1401 + 100; //packet length between 100-1500 bytes.
		
		int packet[] = {dst_ip_generator[rand() % 4],len,rand() % 2};
		
		if (packet[0] == 20){
			if(*p103 != 2 && *p113 != 2 && *p123 != 2 && *p133 != 2){
				drop(packet);
			}
		}
		
		if (packet[0] == 12){
			if(*p203 != 2 && *p213 != 2 && *p223 != 2 && *p233 != 2){
				drop(packet);
			}
		}
		
		if (packet[0] == 50){
			if(*p303 != 2 && *p313 != 2 && *p323 != 2 && *p333 != 2){
				drop(packet);
			}
		}
		
		if (packet[0] == 70){
			if(*p403 != 2 && *p413 != 2 && *p423 != 2 && *p433 != 2){
				drop(packet);
			}
		}
		
		enqueueRate = 10;
		dequeueRate = 10 - (congestion_ratio * 10);
		int i=0; int j=0;
		while (i++ < enqueueRate){
			enqueue(packet);
		}
		while (j++ < dequeueRate){
			dequeue();
		}
		t3 = clock();
		
		displayCheck = (float)(t3 - t1) / CLOCKS_PER_SEC;
		int_displayCheck = (int)displayCheck;
		
		if(displayCheck - int_displayCheck == 0){
		sizeof1 = 0,sizeof2 = 0,sizeof3 = 0,sizeof4 = 0;
		if (*p102 != 0){sizeof1 +=1;} if (*p112 != 0){sizeof1 +=1;} if (*p122 != 0){sizeof1 +=1;} if (*p132 != 0){sizeof1 +=1;}
		if (*p202 != 0){sizeof2 +=1;} if (*p212 != 0){sizeof2 +=1;} if (*p222 != 0){sizeof2 +=1;} if (*p232 != 0){sizeof2 +=1;}
		if (*p302 != 0){sizeof3 +=1;} if (*p312 != 0){sizeof3 +=1;} if (*p322 != 0){sizeof3 +=1;} if (*p332 != 0){sizeof3 +=1;}
		if (*p402 != 0){sizeof4 +=1;} if (*p412 != 0){sizeof4 +=1;} if (*p422 != 0){sizeof4 +=1;} if (*p432 != 0){sizeof4 +=1;}
		printf("Size of Queue 1:%d Queue 2:%d Queue 3:%d Queue 4:%d\n",sizeof1,sizeof2,sizeof3,sizeof4);
		printf("Number of packets dropped:%d\n",dropRate);
		printf("Number of high/low priority packets routed successfully:%d\n",routedpackets);
		printf("Number of bytes routed successfully: %d bytes\n\n",lenCounter);
		}
		
		t2 = clock();
		executionTime = (float)(t2 - t1) / CLOCKS_PER_SEC;
		if (executionTime >= sim_time){
			break;
		}
	}
	
	printf("End of simulation.");

	return 0;
}
