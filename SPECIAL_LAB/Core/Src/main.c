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
#include "usart.h"
#include "gpio.h"
#include "stdbool.h"
#include "string.h"

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

char text[] = "Man from U.A.R.T.2!\r\nQuit PRESS q\r\n";

char ready[] = "	Name : ";

char otherReady[] = "\r\n is ready";

bool textSent = false;

char mymyText[] = "=>";

char myName[100];

char yourName[100];

char myotherText[] = ": ";

char otherText[] = "	Mr.Two =>";

char recieveText[100];

char inputBuffer[100];

char rc;

bool receivingData = true;

bool sendingData = false;

bool nameInput = true;

char nameTemp[100];

char waitingFor[] = "	Waiting For Mr.Two";

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
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	HAL_UART_Transmit(&huart3, (uint8_t*) text, sizeof(text), 100);
	//HAL_UART_Transmit(&huart3, (uint8_t*) ready, strlen(ready), 1000);
	while (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == RESET) {
	}
	HAL_UART_Receive_IT(&huart2, (uint8_t*) &rc, 1);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

//  void ProcessInputData(void)
//    {
//      if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET)
//      {
//        uint8_t receivedChar;
//
//        HAL_UART_Receive(&huart3, &receivedChar, 1, 1000);
//
//        if (receivedChar == '\r')
//        {
//
//          inputBuffer[strlen(inputBuffer)] = '\r';
//          nameTemp[strlen(nameTemp)] = '\r';
//
//          HAL_UART_Transmit(&huart1, (uint8_t *)inputBuffer, strlen(inputBuffer), 1000);
//          HAL_UART_Transmit(&huart3, (uint8_t *)"\r\n", strlen("\r\n"), 1000);
//          ongoing = false;
//          HAL_Delay(500);
//          ongoing = true;
//
////          if(HAL_UART_Transmit(&huart1, (uint8_t *)inputBuffer, strlen(inputBuffer), 1000) == HAL_OK)
////          {
////            HAL_UART_Transmit(&huart3, (uint8_t *)otherText, strlen(otherText), 1000);
////            HAL_UART_Transmit(&huart3, (uint8_t *)recieveText, strlen(recieveText), 1000);
////            HAL_UART_Transmit(&huart3, (uint8_t *)"\r\n", strlen("\r\n"), 1000);
////            receivingData = true;
////          }
////          if(HAL_UART_Transmit(&huart1, (uint8_t *)inputBuffer, strlen(inputBuffer), 1000) == HAL_OK && sendingData == false){
//////        	  HAL_UART_Transmit(&huart2, (uint8_t *)otherText, strlen(otherText), 1000);
//////        	  HAL_UART_Transmit(&huart2, (uint8_t *)inputBuffer, strlen(inputBuffer), 1000);
////        	  //HAL_UART_Transmit(&huart3, (uint8_t *)inputBuffer, strlen(inputBuffer), 1000);
////        	  receivingData = true;
////          }
////          if(HAL_UART_Receive(&huart2, (uint8_t *)recieveText, strlen(recieveText), 1000) == HAL_OK && receivingData == true){
////        	  HAL_UART_Transmit(&huart3, (uint8_t *)recieveText, strlen(recieveText), 1000);
////        	  sendingData = true;
////        	  receivingData = false;
////          }
//
//          memset(inputBuffer, 0, sizeof(inputBuffer));
//
//        }
//
//        else if (receivedChar == 0x08)
//        {
//
//          if (strlen(inputBuffer) > 0)
//          {
//        	 inputBuffer[strlen(inputBuffer) - 1] = '\0';
//        	 HAL_UART_Transmit(&huart3, (uint8_t *)"\b \b", 3, 1000);
//          }
//
//        }
//
//        else
//        {
//          HAL_UART_Transmit(&huart3, &receivedChar, 1, 1000);
//          inputBuffer[strlen(inputBuffer)] = receivedChar;
//        }
//      }
//    }
//
//
//  void NameInputData(void)
//      {
//        if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) == SET)
//        {
//          uint8_t receivedCharName;
//
//          HAL_UART_Receive(&huart3, &receivedCharName, 1, 1000);
//
//          if (receivedCharName == '\r')
//          {
//        	textSent = true;
//        	nameInput = false;
//        	strcpy(nameTemp,myName);
//        	strcat(nameTemp," is Ready!!!\r");
//        	HAL_UART_Transmit(&huart1, (uint8_t *)nameTemp, sizeof(nameTemp), 1000);
//        	strcpy(nameTemp,myName);
//        	memset(myName, 0, sizeof(myName));
//          }
//
//          else if (receivedCharName == 0x08)
//          {
//
//            if (strlen(myName) > 0)
//            {
//             myName[strlen(myName) - 1] = '\0';
//          	 HAL_UART_Transmit(&huart3, (uint8_t *)"\b \b", 3, 1000);
//            }
//
//          }
//
//          else
//          {
//            HAL_UART_Transmit(&huart3, &receivedCharName, 1, 1000);
//            myName[strlen(myName)] = receivedCharName;
//          }
//        }
//      }
	while (1) {
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (huart == &huart3 && nameInput == true) {
		if (rc == '\r') {
			nameInput = false;
			strcpy(nameTemp, myName);
			strcat(nameTemp, "\r");
			HAL_UART_Transmit(&huart2, (uint8_t*) nameTemp, sizeof(nameTemp),
					1000);
			strcpy(nameTemp, myName);
			memset(myName, 0, sizeof(myName));
			if (strcmp(nameTemp, "q") == 0) {
				HAL_UART_Transmit(&huart2, (uint8_t*) "q", sizeof("q"), 1000);
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n quit",
						sizeof("\r\n quit"), 1000);

			}
			HAL_UART_Receive_IT(&huart2, (uint8_t*) &rc, 1);
			rc = '\0';

		}

		else if (rc == 0x08) {

			if (strlen(myName) >= 0) {
				HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
				myName[strlen(myName) - 1] = '\0';
				HAL_UART_Transmit(&huart3, (uint8_t*) "\b \b", 3, 1000);
			}

		}

		else {
			HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
			myName[strlen(myName)] = rc;
			HAL_UART_Transmit(&huart3, (uint8_t*) &rc, 1, 1000);
		}
	}

	if (huart == &huart3 && !nameInput) {
		if (rc == '\r') {
			if (strcmp(inputBuffer, "q") == 0) {
				HAL_UART_Transmit(&huart2, (uint8_t*) 'q', 1,
				1000);
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n quit",
						sizeof("\r\n quit"), HAL_MAX_DELAY);



			}
			inputBuffer[strlen(inputBuffer)] = '\r';

			HAL_UART_Transmit(&huart2, (uint8_t*) inputBuffer,
					strlen(inputBuffer), 1000);
			HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n", strlen("\r\n"), 1000);
			//receivingData = true;
			memset(inputBuffer, 0, sizeof(inputBuffer));
			rc = '\0';
			HAL_UART_Receive_IT(&huart2, (uint8_t*) &rc, 1);
		}

		else if (rc == 0x08) {
			if (strlen(inputBuffer) >= 0) {
				HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
				inputBuffer[strlen(inputBuffer) - 1] = '\0';
				HAL_UART_Transmit(&huart3, (uint8_t*) "\b \b", 3, 1000);
			}

		}

		else {
			HAL_UART_Transmit(&huart3, (uint8_t*) &rc, 1, 1000);
			inputBuffer[strlen(inputBuffer)] = rc;
			HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
		}
	}
	if (huart == &huart2) {
		if (strlen(yourName) == 0) {
			if (rc == '\r') {
				strcpy(yourName, recieveText);
				memset(recieveText, '\0', sizeof(recieveText));
				if (strcmp(yourName, "q") == 0) {
					HAL_UART_Transmit(&huart2, (uint8_t*) "q", strlen("q"),
							1000);
					HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n quit",
							sizeof("\r\n quit"), HAL_MAX_DELAY);
					return 0;
				}
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n        ",
						strlen("\r\n        "), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) yourName,
						strlen(yourName), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) " is ready!!!",
						sizeof(" is ready!!!"), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n",
						strlen("\r\n"), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) ready, strlen(ready),
						1000);
				strcat(yourName, " : ");
				rc = '\0';

				HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
			} else {
				recieveText[strlen(recieveText)] = rc;
				HAL_UART_Receive_IT(&huart2, (uint8_t*) &rc, 1);
			}
		} else if (strlen(yourName) != 0) {
			if (rc == '\r') {
				if (strcmp(recieveText, "qq") == 0) {
					HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n quit",
							sizeof("\r\n quit"), HAL_MAX_DELAY);
					return 0;
				}
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n", sizeof("\r\n"),
				HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) "        ",
						strlen("        "), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) yourName,
						sizeof(yourName), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) recieveText,
						sizeof(recieveText), HAL_MAX_DELAY);
				memset(recieveText, '\0', sizeof(recieveText));
				rc = '\0';
				HAL_UART_Receive_IT(&huart3, (uint8_t*) &rc, 1);
				HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n", strlen("\r\n"),
				HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) "        ",
						strlen("        "), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) nameTemp,
						strlen(nameTemp), HAL_MAX_DELAY);
				HAL_UART_Transmit(&huart3, (uint8_t*) " => ", strlen(" => "),
				HAL_MAX_DELAY);

			}

			else {
				recieveText[strlen(recieveText)] = rc;
				HAL_UART_Receive_IT(&huart2, (uint8_t*) &rc, 1);
			}
		}
	}
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
