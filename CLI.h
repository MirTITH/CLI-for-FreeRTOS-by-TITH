/**
 * @file CLI.h
 * @author TITH (1023515576@qq.com)
 * @brief CLI控制台启动代码头文件，在外部只包含本文件即可
 * @version 1.4
 * @date 2022-01-13
 * @copyright Copyright (c) 2022
 * 
 * 使用方法：
 * (1) 在CubeMX中配置串口，并使能global中断
 * (2) (可选) 打开串口的 DMA 发送，并在 CLI_config.h 中打开宏定义 CLI_config_use_DMA（注意 DMA 要在串口之前初始化）
 * (3) 打开 FreeRTOS 的 USE_TRACE_FACILITY 和 USE_STATS_FORMATTING_FUNCTIONS
 * (4) 在代码中调用 CLI_Init() 初始化 CLI 控制台
 * (5) 如果在代码其他地方有 HAL_UART_RxCpltCallback()，需参考 CLI_startup.c 作相应修改
 * 
 */

#pragma once

#include "usart.h"

/**
 * @brief 初始化CLI控制台
 * 
 * @param huart 该串口需要已经初始化、使能global中断。如果定义 CLI_config_use_DMA ，则还需启用DMA发送
 */
void CLI_Init(UART_HandleTypeDef* huart);
