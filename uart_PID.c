#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<linux/fs.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
	 
	 int fd;
	 int bytes_recieved;
	 int write_bytes;
	 int bytes_w;
	 int i = 0 ;
	 int value;
	 float compass_reading;
	 int count = 0;
	 float arr[10];
	 int j = 0;
	 float error;
	 float value1;
	 int setpoint = 0;
	 char pwm[6] = "";
	 float I_error[6] = {};
	 float lasterror = 0;
	 float kp = 0.5;
	 float kd = 0.1;
	 float ki = 0.09;
	 float sumError = 0;

	 char buf1[20] ;//= { '0' , '0' ,'0' , '0'};

 	 fd = open("/dev/ttySAC3", O_RDWR);
	 printf("fd value id %d\n",fd);
	
	 if(fd < 0)
	 {
	 	 perror("open device serial uart");
                 exit(1);
	 } 	
  	 while(1)	
	 {	
		sleep(0.2);
		setpoint = 0;
		
		
		write_bytes = read(fd,buf1,sizeof(buf1));
		compass_reading = atof(buf1);
	    
		
		printf("value read is %0.2f\n ",compass_reading);	
		
		 float error;
        	 float P = error;
		 float D = (error - lasterror)/0.01;
		 float I = 0;
		 for(i = 0; i < 5; i++)
		 {
		 	I_error[i] = I_error[i + 1];
		 }
		 I_error[5] = error;
		 for(i = 0; i < 6 ; i++)
		 {
		  	I +=  I_error[i] * I_error[i];
		 }
		 I = I * 0.01;
		 error = 0 - compass_reading;
		 sumError = kp * P + kd * D + ki * I;
		 value1 = 0.053 * error;
		 printf("PWM %0.2f \n",value1);

		 sprintf(pwm,"%0.2f",value1);		
		

		sleep(0.07);
		bytes_w = write(fd,&pwm[0],sizeof(pwm[0]));
		sleep(0.07);
		bytes_w = write(fd,&pwm[1],sizeof(pwm[1]));	
		sleep(0.07);
		bytes_w = write(fd,&pwm[2],sizeof(pwm[2]));
		sleep(0.07);
		bytes_w = write(fd,&pwm[3],sizeof(pwm[3]));
		sleep(0.07);
		bytes_w = write(fd,&pwm[4],sizeof(pwm[4]));
		sleep(0.07);
		bytes_w = write(fd,&pwm[5],sizeof(pwm[5]));
		sleep(0.07);
		
		printf("value written is %s \n\n",value1);	
		
	 }
	
	 
	 
	 close(fd);
	 return 0;
}
