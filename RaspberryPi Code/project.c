#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<wiringPi.h>
#include<wiringSerial.h>
#define delay_ms delay
#include <stdlib.h>
#include <unistd.h>

#include <json.h>

#include "pubnub.h"
#include "pubnub-sync.h"
#include <wiringPi.h>

#define PUBLISH_KEY "pub-c-e6f68289-bf76-45b0-8f89-cb3ba5bd841b"
#define SUBSCRIBE_KEY "sub-c-ca09adf2-c07d-11e7-a836-5205f39adfa6"

#define dW digitalWrite
#define dR digitalRead
char str[100]={0};

int main()
{
	int i,fd;
//	int data ;
	char j,arr[10],time[9];
	fd=serialOpen("/dev/ttyS0",9600);
	if(fd<0)
	{
		fprintf(stderr,"UNABLE TO OPEN SERIAL DEVICE:%s\n",strerror(errno));
		return 1;
	}

	while(1)
	{
		strcpy(arr,str);
		for(i=0;(j=serialGetchar(fd))!='$';i++)
		{
		//	data=0;
		//	while((data=serialDataAvail(fd))==0);
			arr[i]=j;
		}
	/*for(i=0;i<=10;i++)
	{
		arr[i]=serialGetchar(fd);
	}*/

//	printf("DATA ON SERIALGETCHAR: %s",arr);//Checking received data
	serialFlush(fd) ;
//	serialPuts(fd,arr) ;//CUTECOM
/*	for(tx=arr[i];tx=arr[i];i++)
	{
		serialPutchar(fd,tx);
		rx=serialGetchar(fd);
		printf("RECVD:%c\n",rx);
	}*/
	struct pubnub_sync *sync = pubnub_sync_init();
	struct pubnub *p = pubnub_init( PUBLISH_KEY , SUBSCRIBE_KEY ,&pubnub_sync_callbacks,sync);
	json_object *msg ; //Creating Pointer to store *NEW* json_object
	msg=json_object_new_object();
	//json_object_object_add(msg, "DATA", json_object_new_string(arr));
	if(arr[0]=='2')
	{	
		json_object_object_add(msg,"ENVIRONMENT:",json_object_new_string("Beautiful Day"));
		json_object_object_add(msg,"Light State:",json_object_new_string("OFF"));
	}
	if(arr[0]=='1')
	{	
		json_object_object_add(msg,"ENVIRONMENT:",json_object_new_string("Dark Night"));
		json_object_object_add(msg,"Light State:",json_object_new_string("ON"));
	}	
	if(arr[0]=='0')
	{	
		json_object_object_add(msg,"ENVIRONMENT:",json_object_new_string("Dark Night"));
		json_object_object_add(msg,"Light State:",json_object_new_string("OFF"));
	json_object_object_add(msg,"WARNING !!!",json_object_new_string("Light Is Not Working"));
	}	
	time[0]=arr[1];time[1]=arr[2];time[2]=':';time[3]=arr[3];time[4]=arr[4];
	time[5]=':';time[6]=arr[5];time[7]=arr[6];time[8]='\0';
		json_object_object_add(msg,"Bulb On Time",json_object_new_string(time));
	//	json_object_object_add(msg," ",json_object_new_string("$"));
		
		
		pubnub_publish(
			/* struct pubnub */ p,
			/* channel */ "project",
			/* message */ msg,
			/* default timeout */ -1,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);

		json_object_put(msg);
				
		if (pubnub_sync_last_result(sync) != PNR_OK)
			return EXIT_FAILURE;
		msg = pubnub_sync_last_response(sync);
		printf("pubnub publish ok: %s\n", json_object_get_string(msg));
		json_object_put(msg);

		pubnub_done(p);
		delay(1000);
	}

	return 0;

}
