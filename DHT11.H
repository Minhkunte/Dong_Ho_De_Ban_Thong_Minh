#define _DHT11_H_

//#include <def_877a.h>

#BIT  DHT_DATA_OUT =  0x06.0
#BIT  DHT_DATA_IN  =  0x06.0
#BIT  DHT_DDR_DATA =  0x86.0

#define DHT_ER       0
#define DHT_OK       1

#define DDROUT    0
#define DDRIN     1

unsigned int8 DHT_GetTemHumi (unsigned int8 &tem1,&tem2,unsigned int8 &humi1,&humi2);

unsigned int8 DHT_GetTemHumi (unsigned int8 &tem1,&tem2,unsigned int8 &humi1,&humi2)
{
   unsigned int8 buffer[5]={0,0,0,0,0};
   unsigned int8 ii,i,checksum;
   
   DHT_DDR_DATA=DDROUT;   // set la cong ra
   DHT_DATA_OUT=1;
   delay_us(60);
   DHT_DATA_OUT=0;
   delay_ms(25); // it nhat 18ms
   DHT_DATA_OUT=1;    
   DHT_DDR_DATA=DDRIN;//set la cong vao
   delay_us(60);
   if(DHT_DATA_IN)return DHT_ER ;
   else while(!(DHT_DATA_IN));   //Doi DaTa len 1
   delay_us(60);//cho 60us
   if(!DHT_DATA_IN)return DHT_ER;
   else while((DHT_DATA_IN));    //Doi Data ve 0
   //Bat dau doc du lieu
   for(i=0;i<5;i++)
   {
      for(ii=0;ii<8;ii++)
      {   
         while((!DHT_DATA_IN));//Doi Data len 1
         delay_us(50);
         if(DHT_DATA_IN)
         {
            buffer[i]|=(1<<(7-ii));
            while((DHT_DATA_IN));//Doi Data xuong 0
         }
      }
   }
   checksum=buffer[0]+buffer[1]+buffer[2]+buffer[3];
   if((checksum)!=buffer[4])return DHT_ER;
   tem1  =   buffer[2];//gia tri phan nguyen
   tem2  =   buffer[3];//gia tri phan thap phan
   humi1 =   buffer[0];//gia tri phan nguyen
   humi2 =   buffer[1];//gia tri phan thap phan
   return DHT_OK;
}
