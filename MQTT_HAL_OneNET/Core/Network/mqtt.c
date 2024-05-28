#include "mqtt.h"
#include "esp8266.h"
#include "stm32f1xx_it.h"
#include <stdio.h>

/* MQTT DEBUG */
#define MQTT_DEBUG 	1

/** MQTT ���Ӳ������� **/
/* �ͻ���ID PS:������ƹ���֮����Ҫ�ڶ���ǰ��\\ */
#define Client_ID 		 "mqtt_stm32_onenet"

/* Broker������ַ */
#define Broker_Address 	 "mqtts.heclouds.com"

/* �û��� */
#define User_Name 		 "j6mQCOH76X"

/* �û����� */
#define Password 		 "version=2018-10-31&res=products%2Fj6mQCOH76X%2Fdevices%2Fmqtt_stm32_onenet&et=7557387130&method=md5&sign=4ETvR4RF9B3VY3sELkf6qw%3D%3D"

/* �������� */
#define Sub_Topic        "$sys/j6mQCOH76X/mqtt_stm32_onenet/dp/post/json/+"

/* �������� */
#define Pub_Topic        "$sys/j6mQCOH76X/mqtt_stm32_onenet/dp/post/json"

/* �����ĸ�ʽ */
//#define JSON_FORMAT      "{\\\"params\\\":{\\\"LEDSwitch\\\":%d\\}\\,\\\"version\\\":\\\"1.0.0\\\"}"

#define JSON_FORMAT      "{\\\"id\\\":%d\\,\\\"dp\\\":{\\\"LOCKLOG\\\":[{\\\"v\\\":%d\\,}]\\,}}"

/**
  * @brief  mqtt����OneNET
  * @param	void
  * 
  * @retval void
  */
void mqtt_connect(void)
{
	/* MQTT�û����� */
#if MQTT_DEBUG
	printf("1. MQTT USER CONFIG\r\n");
#endif
	while(ESP8266_SendCmd((char *)"AT+MQTTUSERCFG=0,1,\""Client_ID"\",\""User_Name"\",\""Password"\",0,0,\"\"\r\n", "OK"))
		HAL_Delay(500);
	
	/* MQTT Broker���� */
#if MQTT_DEBUG
	printf("2.CONNECT MQTT BROKER\r\n");
#endif
	while(ESP8266_SendCmd((char *)"AT+MQTTCONN=0,\""Broker_Address"\",1883,0\r\n", "OK"))
		HAL_Delay(500); 
	
	/* �������� */
#if MQTT_DEBUG
	printf("3.SUBSCRIBE TOPIC\r\n");
#endif
	while(ESP8266_SendCmd((char *)"AT+MQTTSUB=0,\""Sub_Topic"\",0\r\n", "OK"))
		HAL_Delay(500); 
#if MQTT_DEBUG	
	printf("4.MQTT CONNECT SUCCEED");
#endif
}

/**
  * @brief  mqtt��������
  * @param	void
  * 
  * @retval void
  */
void mqtt_pub(void)
{
	unsigned char msg_buf[256];
	
	/* ����JSON_FORMAT��ʽ�����Ӧ���ݼ��� */
	sprintf((char *)msg_buf, "AT+MQTTPUB=0,\""Pub_Topic"\",\""JSON_FORMAT"\",0,0\r\n", 1, 1);
	
	while(ESP8266_SendCmd((char *)msg_buf, "OK"));
	
#if MQTT_DEBUG	
	printf("mqtt pub succeed");	
#endif
}

/**
  * @brief  mqtt��������
  * @param	void
  * 
  * @retval void
  */
void mqtt_sub(unsigned char* dataPtr)
{
	
}



