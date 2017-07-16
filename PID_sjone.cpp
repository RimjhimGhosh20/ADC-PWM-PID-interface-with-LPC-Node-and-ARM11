int count = 0;
float value = 0;
double compass_reading;
int compass_last;
double final_Reading  = 0;
uint8_t data;
uint8_t compass[2] = {0};
char reg_address ; //command register
char dev_address= 0xC0 ; //device address
uint16_t compass1;
uint16_t compass2;
double turn_angle1;
double turn_angle2;
int count1 = 0;
char chDat[6] = "";
char buff[20] = "";
char ch;
float pwm_value;


int main(void)
{

	Uart2::getInstance().init(115200,1000,1000);
	while(1)
	{

		static PWM motor(PWM::pwm1,50);

		float dataSend = 0;
		reg_address = 0x02;
		I2C2::getInstance().readRegisters(dev_address, reg_address, compass, 16);
		compass1 = ((compass[0]<<8) | (compass[1] & 0xFF));
		compass_last = compass1%10;
		compass2 = (compass1/10) ;
		final_Reading = (int)compass2 + 0.1 * compass_last;
		//printf("Read %0.2f\n",final_Reading);


		if(final_Reading > 180)
		{
			dataSend = 360 - final_Reading;
		}
		else
		{
			dataSend = - final_Reading;
		}

		sprintf(buff,"%0.2f",dataSend);

		delay_ms(20);
		printf("Final Reading: %s \n", buff);

		Uart2::getInstance().putline(buff,20);

		if(Uart2::getInstance().getChar(&ch,10))
		{
			chDat[count1] = ch;

			count1++;
			if(count1 == 6)
			{

				pwm_value = atof(chDat);
				motor.set(pwm_value);
				printf("PWM %0.2f \n\n", pwm_value);
				for(int i = 0; i < 6; i++)
					chDat[i]= ' ';
				count1 = 0;
			}
		}
	}
}