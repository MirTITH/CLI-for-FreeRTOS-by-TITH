/**
 * @file CLI_startup.c
 * @author TITH (1023515576@qq.com)
 * @brief CLI控制台启动代码，若要添加自定义命令，请在CLI_custom_command.c中添加
 * @version 1.5
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cmsis_os.h"
#include "serial.h"
#include "CLI.h"

UART_HandleTypeDef *CLI_huart;
osThreadId cli_taskHandle;

static uint8_t char_to_CLI;

extern void cli_task(void const * argument);

void CLI_Init(UART_HandleTypeDef *huart)
{
	/* creation of cli */
	CLI_huart = huart;
	osThreadDef(CLI, cli_task, osPriorityBelowNormal, 0, 128);
	cli_taskHandle = osThreadCreate(osThread(CLI), NULL);

	HAL_UART_Receive_IT(CLI_huart, &char_to_CLI, 1);
}

/**
 * @brief 串口发送完毕的回调函数
 * 
 * @param huart 串口句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == CLI_huart->Instance)
	{
		CLI_Input_Char(&char_to_CLI);
		HAL_UART_Receive_IT(CLI_huart, &char_to_CLI, 1);
	}
}

#if( configGENERATE_RUN_TIME_STATS == 1 )
unsigned long getRunTimeCounterValue(void)
{
	return xTaskGetTickCount(); //返回当前滴答数
}
#endif
