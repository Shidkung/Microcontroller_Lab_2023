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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint8_t pwm;
float duty_cycle = 0.0;
float duty_cycle1 = 0.0;
float duty_cycle2 = 0.0;
char bucket[8];
char ch1 = 'A';
char Kidpass[] = "64010591\r\n\n";
char Kidname[] = "Pitpibul Phongphotjanatham\r\n\n";
char ninpass[] = "64010454\r\n\n";
char ninname[] = "Bantita WongWan\r\n\n";
char Patpass[] = "64010400\r\n\n";
char Patname[] = "Nonthaphat Jitchiranant\r\n\n";
char ch2[] ="Input : ";
char ch3[] = "Unknown Command\r\n";
char ch4[] ="\r\n";
char quit[] ="Quit\r\n";
char c;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		htim2.Instance->CCR3 = (10000 - 1) * duty_cycle;
		htim2.Instance->CCR2 = (10000 - 1) * duty_cycle1;
		htim2.Instance->CCR4 = (10000 - 1) * duty_cycle2;
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

		pwm = (GPIOB->IDR & GPIO_PIN_10) >> 10;

		while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TC) == RESET) {
					}
					HAL_UART_Transmit(&huart3, (uint8_t*) &ch2, strlen(ch2), 1000);

					while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET) {}
					HAL_UART_Receive(&huart3, (uint8_t*) &c, 1, 1000);
					HAL_Delay(10);

					HAL_UART_Transmit(&huart3, (uint8_t*) &c, 1, 1000);
					HAL_UART_Transmit(&huart3, (uint8_t*) &ch4, strlen(ch4), 1000);

					while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET) {}

//		while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == RESET) {}
//		HAL_UART_Receive(&huart3, bucket, strlen(bucket), 1000);
//		HAL_Delay(200);
//
//
//
//		while (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET) {}
//		HAL_UART_Transmit(&huart3, bucket, strlen(bucket), 1000);
//		HAL_Delay(500);
		switch (c)
		{
			case 'r':
				if (duty_cycle1 < 1) {
								duty_cycle1 += 0.2;
							} else {
								duty_cycle1 = 0.0;
							}
				break;

			case 'b':
				if (duty_cycle2 < 1) {
								duty_cycle2 += 0.2;
							} else {
								duty_cycle2 = 0.0;
							}
				break;

			case 'g':
				if (duty_cycle < 1) {
								duty_cycle += 0.2;
							} else {
								duty_cycle = 0.0;
							}
				break;

		}

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
