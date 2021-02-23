/*
 * Application_layer.c
 *
 *  Created on: Feb 23, 2021
 *      Author: mostafa
 */

#include "stm32g4xx_hal.h"
#include "stm32g4xx_nucleo.h"

FDCAN_HandleTypeDef hfdcan1;
FDCAN_FilterTypeDef sFilterConfig;
FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef RxHeader;

static GPIO_TypeDef*   LED_PORT[LEDn] = {LED2_GPIO_PORT};

static const uint16_t  LED_PIN[LEDn] = {LED2_PIN};


static GPIO_TypeDef*   BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT};

static const uint16_t  BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN};

static const IRQn_Type BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

uint8_t TxData[] = {0x10, 0x32, 0x54, 0x76, 0x98, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x00};




/**
  * @brief  Configures LED GPIO.
  * @param  Led Specifies the Led to be configured.
  *         This parameter can be one of following parameters:
  *           @arg  LED2
  * @retval BSP status
  */
int32_t BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIO LED Clock */
  LED2_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  gpio_init_structure.Pin   = LED_PIN[Led];
  gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(LED_PORT[Led], &gpio_init_structure);
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);

  return BSP_ERROR_NONE;
}

/**
  * @brief  DeInit LEDs.
  * @param  Led Specifies the Led to be de-init.
  *         This parameter can be one of the following values:
  *           @arg  LED2
  * @note Led DeInit does not disable the GPIO clock
  * @retval BSP status
  */
int32_t BSP_LED_DeInit(Led_TypeDef Led)
{
  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);

  /* DeInit the GPIO_LED pin */
  HAL_GPIO_DeInit(LED_PORT[Led], LED_PIN[Led]);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Turns selected LED On.
  * @param  Led Specifies the Led to be set on.
  *         This parameter can be one of following parameters:
  *           @arg  LED2
  * @retval BSP status
  */
int32_t BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led Specifies the Led to be set off.
  *         This parameter can be one of following parameters:
  *           @arg  LED2
  * @retval BSP status
  */
int32_t BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led Specifies the Led to be toggled.
  *         This parameter can be one of following parameters:
  *           @arg  LED2
  * @retval BSP status
  */
int32_t BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);

  return BSP_ERROR_NONE;
}

/**
  * @brief  Get the status of the selected LED.
  * @param  Led Specifies the Led to get its state.
  *         This parameter can be one of following parameters:
  *           @arg  LED2
  * @retval LED status
  */
int32_t BSP_LED_GetState(Led_TypeDef Led)
{
  return (int32_t)HAL_GPIO_ReadPin(LED_PORT[Led], LED_PIN[Led]);
}
