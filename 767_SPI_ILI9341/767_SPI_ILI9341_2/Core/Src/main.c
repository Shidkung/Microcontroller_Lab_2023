/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "ILI9341_Touchscreen.h"

#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "snow_tiger.h"
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
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

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

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_USART3_UART_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();//initial driver setup to drive ili9341
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //----------------------------------------------------------PERFORMANCE TEST
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("FPS TEST, 40 loop 2 screens", 10, 10, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		uint32_t Timer_Counter = 0;
	  		for(uint32_t j = 0; j < 2; j++)
	  		{
	  			HAL_TIM_Base_Start(&htim1);
	  			for(uint16_t i = 0; i < 10; i++)
	  			{
	  				ILI9341_Fill_Screen(WHITE);
	  				ILI9341_Fill_Screen(BLACK);
	  			}

	  			//20.000 per second!
	  			HAL_TIM_Base_Stop(&htim1);
	  			Timer_Counter += __HAL_TIM_GET_COUNTER(&htim1);
	  			__HAL_TIM_SET_COUNTER(&htim1, 0);
	  		}
	  		Timer_Counter /= 2;

	  		char counter_buff[30];
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		sprintf(counter_buff, "Timer counter value: %ld", Timer_Counter*2);
	  		ILI9341_Draw_Text(counter_buff, 10, 10, BLACK, 1, WHITE);

	  		double seconds_passed = 2*((float)Timer_Counter / 20000);
	  		sprintf(counter_buff, "Time: %.3f Sec", seconds_passed);
	  		ILI9341_Draw_Text(counter_buff, 10, 30, BLACK, 2, WHITE);

	  		double timer_float = 20/(((float)Timer_Counter)/20000);	//Frames per sec

	  		sprintf(counter_buff, "FPS:  %.2f", timer_float);
	  		ILI9341_Draw_Text(counter_buff, 10, 50, BLACK, 2, WHITE);
	  		double MB_PS = timer_float*240*320*2/1000000;
	  		sprintf(counter_buff, "MB/S: %.2f", MB_PS);
	  		ILI9341_Draw_Text(counter_buff, 10, 70, BLACK, 2, WHITE);
	  		double SPI_utilized_percentage = (MB_PS/(6.25 ))*100;		//50mbits / 8 bits
	  		sprintf(counter_buff, "SPI Utilized: %.2f", SPI_utilized_percentage);
	  		ILI9341_Draw_Text(counter_buff, 10, 90, BLACK, 2, WHITE);
	  		HAL_Delay(10000);


	  		static uint16_t x = 0;
	  		static uint16_t y = 0;

	  		char Temp_Buffer_text[40];

	  //----------------------------------------------------------COUNTING MULTIPLE SEGMENTS
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Counting multiple segments at once", 10, 10, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);


	  		for(uint16_t i = 0; i <= 10; i++)
	  		{
	  		sprintf(Temp_Buffer_text, "Counting: %d", i);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 30, BLUE, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 50, RED, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 70, GREEN, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 90, BLACK, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 110, BLUE, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 130, RED, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 150, GREEN, 2, WHITE);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 170, WHITE, 2, BLACK);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 190, BLUE, 2, BLACK);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 210, RED, 2, BLACK);
	  		}

	  		HAL_Delay(1000);

	  //----------------------------------------------------------COUNTING SINGLE SEGMENT
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Counting single segment", 10, 10, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		for(uint16_t i = 0; i <= 100; i++)
	  		{
	  		sprintf(Temp_Buffer_text, "Counting: %d", i);
	  		ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 3, WHITE);
	  		}

	  		HAL_Delay(1000);

	  //----------------------------------------------------------ALIGNMENT TEST
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Rectangle alignment check", 10, 10, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		ILI9341_Draw_Hollow_Rectangle_Coord(50, 50, 100, 100, BLACK);
	  		ILI9341_Draw_Filled_Rectangle_Coord(20, 20, 50, 50, BLACK);
	  		ILI9341_Draw_Hollow_Rectangle_Coord(10, 10, 19, 19, BLACK);
	  		HAL_Delay(1000);

	  //----------------------------------------------------------LINES EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Horizontal and Vertical lines", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		for(uint32_t i = 0; i < 30000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			radiusr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			colourr = random_num;

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;
	  			//ili9341_drawpixel(xr, yr, WHITE);
	  			ILI9341_Draw_Horizontal_Line(xr, yr, radiusr, colourr);
	  			ILI9341_Draw_Vertical_Line(xr, yr, radiusr, colourr);
	  		}

	  		HAL_Delay(1000);

	  //----------------------------------------------------------HOLLOW CIRCLES EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Circles", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);


	  		for(uint32_t i = 0; i < 3000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			radiusr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			colourr = random_num;

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;
	  			//ili9341_drawpixel(xr, yr, WHITE);
	  			ILI9341_Draw_Hollow_Circle(xr, yr, radiusr*2, colourr);
	  		}
	  		HAL_Delay(1000);

	  //----------------------------------------------------------FILLED CIRCLES EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Filled Circles", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		for(uint32_t i = 0; i < 1000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			radiusr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			colourr = random_num;

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;
	  			//ili9341_drawpixel(xr, yr, WHITE);
	  			ILI9341_Draw_Filled_Circle(xr, yr, radiusr/2, colourr);
	  		}
	  		HAL_Delay(1000);

	  //----------------------------------------------------------HOLLOW RECTANGLES EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Rectangles", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		for(uint32_t i = 0; i < 20000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			radiusr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			colourr = random_num;

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;
	  			//ili9341_drawpixel(xr, yr, WHITE);
	  			ILI9341_Draw_Hollow_Rectangle_Coord(xr, yr, xr+radiusr, yr+radiusr, colourr);
	  		}
	  		HAL_Delay(1000);

	  //----------------------------------------------------------FILLED RECTANGLES EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Filled Rectangles", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);

	  		for(uint32_t i = 0; i < 20000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			uint16_t radiusr = 0;
	  			uint16_t colourr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			radiusr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			colourr = random_num;

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			radiusr &= 0x001F;
	  			//ili9341_drawpixel(xr, yr, WHITE);
	  			ILI9341_Draw_Rectangle(xr, yr, radiusr, radiusr, colourr);
	  		}
	  		HAL_Delay(1000);

	  //----------------------------------------------------------INDIVIDUAL PIXEL EXAMPLE

	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Slow draw by selecting", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("and adressing pixels", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);


	  		x = 0;
	  		y = 0;
	  		while (y < 240)
	  		{
	  		while ((x < 320) && (y < 240))
	  		{

	  			if(x % 2)
	  			{
	  				ILI9341_Draw_Pixel(x, y, BLACK);
	  			}

	  			x++;
	  		}

	  			y++;
	  			x = 0;
	  		}

	  		x = 0;
	  		y = 0;


	  		while (y < 240)
	  		{
	  		while ((x < 320) && (y < 240))
	  		{

	  			if(y % 2)
	  			{
	  				ILI9341_Draw_Pixel(x, y, BLACK);
	  			}

	  			x++;
	  		}

	  			y++;
	  			x = 0;
	  		}
	  		HAL_Delay(2000);

	  //----------------------------------------------------------INDIVIDUAL PIXEL EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Random position and colour", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("500000 pixels", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Fill_Screen(WHITE);


	  		for(uint32_t i = 0; i < 500000; i++)
	  		{
	  			uint32_t random_num = 0;
	  			uint16_t xr = 0;
	  			uint16_t yr = 0;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			xr = random_num;
	  			random_num = HAL_RNG_GetRandomNumber(&hrng);
	  			yr = random_num;
	  			uint16_t color = HAL_RNG_GetRandomNumber(&hrng);

	  			xr &= 0x01FF;
	  			yr &= 0x01FF;
	  			ILI9341_Draw_Pixel(xr, yr, color);
	  		}
	  		HAL_Delay(2000);

	  //----------------------------------------------------------565 COLOUR EXAMPLE, Grayscale
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Colour gradient", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("Grayscale", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);


	  		for(uint16_t i = 0; i <= (320); i++)
	  		{
	  			uint16_t Red = 0;
	  			uint16_t Green = 0;
	  			uint16_t Blue = 0;

	  			Red = i/(10);
	  			Red <<= 11;
	  			Green = i/(5);
	  			Green <<= 5;
	  			Blue = i/(10);



	  			uint16_t RGB_color = Red + Green + Blue;
	  			ILI9341_Draw_Rectangle(i, x, 1, 240, RGB_color);

	  		}
	  		HAL_Delay(2000);

	  //----------------------------------------------------------IMAGE EXAMPLE, Snow Tiger
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("RGB Picture", 10, 10, BLACK, 1, WHITE);
	  		ILI9341_Draw_Text("TIGER", 10, 20, BLACK, 1, WHITE);
	  		HAL_Delay(2000);
	  		ILI9341_Draw_Image((const char*)snow_tiger, SCREEN_VERTICAL_2);
	  		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
	  		HAL_Delay(5000);


	  //----------------------------------------------------------TOUCHSCREEN EXAMPLE
	  		ILI9341_Fill_Screen(WHITE);
	  		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  		ILI9341_Draw_Text("Touchscreen", 10, 10, BLACK, 2, WHITE);
	  		ILI9341_Draw_Text("Touch to draw", 10, 30, BLACK, 2, WHITE);
	  		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);


	  		while(1)
	  		{
	  			HAL_Delay(20);

	  			if(TP_Touchpad_Pressed())
	          {

	  					uint16_t x_pos = 0;
	  					uint16_t y_pos = 0;


	  					HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_SET);

	            uint16_t position_array[2];

	  					if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
	  					{
	  					x_pos = position_array[0];
	  					y_pos = position_array[1];
	  					ILI9341_Draw_Filled_Circle(x_pos, y_pos, 2, BLACK);

	  					ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
	  					char counter_buff[30];
	  					sprintf(counter_buff, "POS X: %.3d", x_pos);
	  					ILI9341_Draw_Text(counter_buff, 10, 80, BLACK, 2, WHITE);
	  					sprintf(counter_buff, "POS Y: %.3d", y_pos);
	  					ILI9341_Draw_Text(counter_buff, 10, 120, BLACK, 2, WHITE);
	  					ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
	  					}

	  					ILI9341_Draw_Pixel(x_pos, y_pos, BLACK);

	          }
	  			else
	  			{
	  				HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
	  			}

	  		}

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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
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
  while(1)
  {
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
