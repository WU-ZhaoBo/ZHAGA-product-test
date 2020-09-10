/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

extern uint8_t Usart_Rx_Buffer[1];

//SemaphoreHandle_t xSemaphore1 = NULL;
//SemaphoreHandle_t xSemaphore2 = NULL;
//uint8_t Tx_Buffer[] = "*********´®¿Ú·¢ËÍ**********\r\n"; 
//uint8_t Usart_Rx_Buffer[1];
//uint8_t Usart_Tx_Buffer[1];

//extern uint8_t Tim_Count;
//extern uint8_t L_Flag;
//extern uint8_t H_Flag;
//extern uint8_t System_Led_Flag;
//extern uint8_t X_Standard_Flag;
//extern uint8_t Y_Low_Flag;
//extern uint8_t Z_High_Flag;
//extern uint8_t Switch_Flag;
//extern uint8_t Start_Flag;


//extern uint16_t AD_Value;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define  USE_FULL_ASSERT
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
SemaphoreHandle_t Test_Start_Semaphore = NULL;//Production test start
SemaphoreHandle_t Standard_Semaphore = NULL;//Start switch standard illumination
SemaphoreHandle_t Standard_Success_Semaphore = NULL;//Switch standard illumination success
SemaphoreHandle_t low_Semaphore = NULL;//Start switch low illumination
SemaphoreHandle_t low_Success_Semaphore = NULL;//Switch low illumination success
SemaphoreHandle_t High_Semaphore = NULL;//Start switch high illumination
SemaphoreHandle_t High_Success_Semaphore = NULL;//Switch high illumination success
SemaphoreHandle_t Low_Failure_Semaphore = NULL;//low illumination failure
SemaphoreHandle_t High_Failure_Semaphore = NULL;//high illumination failure
SemaphoreHandle_t Test_Pass_Semaphore = NULL;//Production test pass

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    /* Prevent unused argument(s) compilation warning */
////    UNUSED(htim);
////    printf("AD_Value = %d\r\n", AD_Value);
////    printf("Switch_Flag = %d,Start_Flag = %d,HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) = %d\r\n", Switch_Flag,Start_Flag,HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2));
//    if (1 == System_Led_Flag)
//    {
//        if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8))
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
//        else 
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//    }
//    if (1 == L_Flag)
//    {
////        printf("AD_Value032 = %d\r\n", AD_Value);
//        if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
//        else 
//            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);    
//    }
//    else if (1 == H_Flag)
//    {
////        printf("AD_Value033 = %d\r\n", AD_Value);
//        if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
//        else 
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);         
//    }
//    if ((1 == X_Standard_Flag) || (1 == Y_Low_Flag) || (1 == Z_High_Flag))
//    {       
//        Tim_Count++;
//        printf("Tim_Count = %d\r\n", Tim_Count);
//    }
//    /* NOTE : This function should not be modified, when the callback is needed,
//              the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
//     */
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
////    printf ("++++++++++++++++++++++++++++++++++++++++++++++++\r\n");
//    if(huart->Instance == USART2)
//	{
////        printf ("----------------------------------------------\r\n");
////        printf ("Usart_Rx_Buffer = %d\r\n",(uint32_t)Usart_Rx_Buffer);
////		HAL_UART_Transmit(&huart2,Usart_Rx_Buffer,1,100);
//		HAL_UART_Receive_IT(&huart2,Usart_Rx_Buffer,1);		
//	}
//}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
//	xSemaphore1 = xSemaphoreCreateBinary();
//	xSemaphore2 = xSemaphoreCreateBinary();
//    if( xSemaphore1 == NULL || xSemaphore2 == NULL)
//	{
//			// The semaphore was created successfully.
//        printf("The semaphore was created successfully\r\n");
//			// The semaphore can now be used.
//	}
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

    HAL_UART_Receive_IT(&huart2,Usart_Rx_Buffer,1);
    HAL_TIM_Base_Start_IT(&htim6);
//    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);
    Test_Start_Semaphore = xSemaphoreCreateBinary();
    Standard_Semaphore = xSemaphoreCreateBinary();
    Standard_Success_Semaphore = xSemaphoreCreateBinary();
    low_Semaphore = xSemaphoreCreateBinary();
    low_Success_Semaphore = xSemaphoreCreateBinary();
    High_Semaphore = xSemaphoreCreateBinary();
    High_Success_Semaphore = xSemaphoreCreateBinary();
    Low_Failure_Semaphore = xSemaphoreCreateBinary();
    High_Failure_Semaphore = xSemaphoreCreateBinary();
    Test_Pass_Semaphore = xSemaphoreCreateBinary();

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init(); 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
