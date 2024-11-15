/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"string.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

int adc_val_8 = 0;
int adc_val_16 = 0;
uint32_t Hex = 501;
volatile  uint32_t adc_val = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int average_8(int x);
int average_16(int x);
void displayHex(uint32_t x);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_USART3_UART_Init();
	MX_ADC3_Init();
	/* USER CODE BEGIN 2 */
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adc_val, 4096);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
			while(HAL_ADC_PollForConversion(&hadc1,100)!= HAL_OK){
			}
			adc_val =HAL_ADC_GetValue(&hadc1);
			adc_val_8 = average_8(adc_val);
			adc_val_16 = average_16(adc_val);
			displayHex(adc_val);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 216;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
int average_8(int x) {
	static int samples[8];
	static int i = 0;
	static int total = 0;
	total += x - samples[i];
	samples[i] = x;
	i = (i == 7 ? 0 : i + 1);
	return total >> 3;

}

int average_16(int x) {
	static int samples[16];
	static int i = 0;
	static int total = 0;
	total += x - samples[i];
	samples[i] = x;
	i = (i == 15 ? 0 : i + 1);
	return total >> 4;

}
void displayHex(uint32_t x) {
	float Vin = (x / (pow(2, 12))) * 3.6;

	char buf[100];
	sprintf(buf, "ADC1_CH10  0x%08x Vin = %.2f V\r\n", x, Vin);
	HAL_UART_Transmit(&huart3, (uint8_t*) &buf, strlen(buf), 1000);

	if (Vin < 0.72) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
	} else if (Vin < 1.14) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
	} else if (Vin < 1.86) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
	} else if (Vin < 2.58) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
	} else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
	}
	HAL_Delay(500);

}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
	char buf[100];
	sprintf(buf, "LD2 ON\r\n");
	HAL_UART_Transmit(&huart3, (uint8_t*) &buf, strlen(buf), 1000);
}
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
	char buf[100];
	sprintf(buf, "LD2 OFF\r\n");
	HAL_UART_Transmit(&huart3, (uint8_t*) &buf, strlen(buf), 1000);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
