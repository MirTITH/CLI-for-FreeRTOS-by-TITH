/**
 * @file CLI_custom_command.c
 * @author TITH (1023515576@qq.com)
 * @brief 在此处添加自定义命令，具体方法可以参考Sample-CLI-commands.c
 * @version 1.4
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "CLI_custom_command.h"

/**
 * @brief 自定义命令在这里注册
 * 
 */
void vRegisterCustomCLICommands(void)
{
	CLI_New_Command(testvar, setting CLI_test_var, F_Set_CLI_test_var, -1);
	CLI_New_Command(kamimadoka, kami.im, F_kamimadoka, 0);
}


//-------------------------------自定义命令写在下面（记得在上面的vRegisterCustomCLICommands()中注册）--------------------------

float CLI_test_var = 2.78;
/**
 * @brief 查看与更改浮点数变量
 * 
 * @param pcWriteBuffer 待输出的内容
 * @param xWriteBufferLen pcWriteBuffer 的长度（输出内容不能超过此长度，否则数组越界）
 * @param pcCommandString 命令行输入的完整字符串
 * @return BaseType_t pdFALSE 结束执行，pdTrue 循环执行
 */
BaseType_t F_Set_CLI_test_var(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) 
{
	BaseType_t xParameterStringLength;
	const char *pcParameter;
	pcParameter = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength);

	if (pcParameter == NULL) // 说明没有带参数
	{
		sprintf(pcWriteBuffer, "CLI_test_var == %g", CLI_test_var);
		// sprintf(pcWriteBuffer, "CLI_test_var == %.15lg", CLI_test_var); //double 型数据用这行更好
	}
	else
	{
		CLI_test_var = atof(pcParameter);
		sprintf(pcWriteBuffer, "Set CLI_test_var = %g", CLI_test_var);
		// sprintf(pcWriteBuffer, "Set CLI_test_var = %.15lg", CLI_test_var); //double 型数据用这行更好
	}

	return pdFALSE; // 结束执行
}


BaseType_t F_kamimadoka(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) 
{
	const char poem[] = "Darkness cannot drive out darkness\r\n\r\nonly light can do that\r\n\r\nHate cannot drive out hate\r\n\r\nonly love can do that.\r\n\r\nYour sin , I bear\r\n\r\n";
	const uint16_t length = strlen(poem);
	static uint16_t i = 0;

	sprintf(pcWriteBuffer, "%c", poem[i++]);//输出一个字符，然后 i++

	osDelay(50);

	if (i >= length) return pdFALSE; // 结束执行

	return pdPASS; // 循环执行
}


