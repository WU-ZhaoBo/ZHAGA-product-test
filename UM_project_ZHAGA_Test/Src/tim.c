/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"

uint8_t Capture_Count = 0;

extern uint8_t Tim_Count;
extern uint8_t L_Flag;
extern uint8_t H_Flag;
extern uint8_t System_Led_Flag;
extern uint8_t X_Standard_Flag;
extern uint8_t Y_Low_Flag;
extern uint8_t Z_High_Flag;
extern uint8_t Switch_Flag;
extern uint8_t Start_Flag;


extern uint16_t AD_Value;
/* USER CODE END 0 */

TIM_HandleTypeDef htim6;

/* TIM6 init function */
void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 7199;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* Prevent unused argument(s) compilation warning */
//    UNUSED(htim);
//    printf("AD_Value = %d\r\n", AD_Value);
//    printf("L_Flag = %d\r\n", L_Flag);
    if (1 == System_Led_Flag)
    {
        if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8))
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        else 
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    }
    if (1 == L_Flag)
    {
//        printf("AD_Value032 = %d\r\n", AD_Value);
        if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        else 
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);    
    }
    else if (1 == H_Flag)
    {
//        printf("AD_Value033 = %d\r\n", AD_Value);
        if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
        else 
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);         
    }
    if ((1 == X_Standard_Flag) || (1 == Y_Low_Flag) || (1 == Z_High_Flag))
    {       
        Tim_Count++;
        printf("Tim_Count = %d\r\n", Tim_Count);
    }
    /* NOTE : This function should not be modified, when the callback is needed,
              the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
     */
}

//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
////    if(TIM5 == htim->Instance)
////    {
//        printf("--------\r\n");
//        Capture_Count++;
//        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);
////    }
//}
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//  /* Prevent unused argument(s) compilation warning */
////    UNUSED(htim);
//    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
//    {   
//        printf("--------\r\n");
//        Capture_Count++;
////        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);   
//    }
//  /* NOTE : This function should not be modified, when the callback is needed,
//            the HAL_TIM_IC_CaptureCallback could be implemented in the user file
//   */
//}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
