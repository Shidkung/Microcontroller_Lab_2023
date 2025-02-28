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
#include "i2c.h"
#include "rng.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdint.h> // Include this header for uint16_t

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

uint32_t progress = 0;
extern uint32_t count = 0;

uint32_t maxProgress = 100; // ค่า progress สูงสุด
uint32_t progressBarWidth = 0; // ความ�?ว้างของ progress bar
uint32_t progressBarHeight = 10; // ความสูงของ progress bar
uint32_t xStart = 10; // ตำ�?หน่งเริ่มต้น x ของ progress bar
uint32_t yStart = 50; // ตำ�?หน่งเริ่มต้น y ของ progress bar

float temp = 0;
float RH = 0;
uint16_t Red = 0 ;
uint16_t Green = 0;
uint16_t Blue = 0;


uint8_t ch2 = 0;
uint8_t state = 0;
uint8_t step = 0;
uint8_t cmdBuffer[3];
uint8_t dataBuffer[8];

uint32_t timestart = 0;
uint32_t timecurrent = 0;

uint16_t CRC16_2(uint8_t * , uint8_t);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t RGB565(uint16_t R, uint16_t G, uint16_t B) {

		float Rr = (R * 255)/(float)100;
		float Gg = (G * 255)/(float)100;
		float Bb = (B * 255)/(float)100;

		// ปรับค่าสี R, G, B ให้อยู่ในช่วง 0-255
		    uint8_t R8 = (uint8_t)(Rr + 0.5);  // �?าร�?ปลงค่าทศนิยมเป็นจำนวนเต็ม
		    uint8_t G8 = (uint8_t)(Gg + 0.5);
		    uint8_t B8 = (uint8_t)(Bb + 0.5);

		    // ทำ�?ารลดขนาดค่าสี R, G, B เข้าให้เป็นช่วง 0-31
		    uint8_t R5 = (R8 * 31) / 255;
		    uint8_t G6 = (G8 * 63) / 255;
		    uint8_t B5 = (B8 * 31) / 255;


		    // คำนวณค่า RGB565
		    uint16_t RGB565 = ((R5 << 11) | (G6 << 5) | B5);


		    return RGB565;
}



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
  MX_RNG_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();//initial driver setup to drive ili9341
  HAL_TIM_Base_Start_IT (&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  ILI9341_Fill_Screen(WHITE);
  ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);


  cmdBuffer[0] = 0x03;
  cmdBuffer[1] = 0x00;
  cmdBuffer[2] = 0x04;


  ex1();

  //ex2();

  //ILI9341_Draw_Image(Image_Array, 2);
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  //---------------------------------------------------------- Ex 01


	  //ex1();

	 if (state == 0){
		 ex1();
		// HAL_Delay(1000);
	 }
	 else if (state == 1){

		 if(ch2 == 0){
			 ex2();
			 ch2+=1;
		 }
	if((count - timestart) > 5000 ){

		 state = 0;
		ILI9341_Fill_Screen(WHITE);
	}
	 if(TP_Touchpad_Pressed()){

		uint16_t x_pos1 = 0;
		uint16_t y_pos1 = 0;


		//HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_SET);

		uint16_t position_array[2];

		if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
		{
		x_pos1 = position_array[0];
		y_pos1 = position_array[1];

//		char str = "";
//		sprintf(str,"%d", x_pos1);
//		 ILI9341_Draw_Text(str,135 , 180 , BLACK, 2, WHITE);
//		 str = "";
//		 sprintf(str,"%d", y_pos1);
//		 ILI9341_Draw_Text(str,135 , 200 , BLACK, 2, WHITE);

				if(x_pos1 > 115 && x_pos1 < 200){
					if(y_pos1 > 40 && y_pos1< 76){

					state = 0;
					ch2 = 0;
					ILI9341_Fill_Screen(WHITE);
					}
				}
			}
		else
		{
			//HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
		}

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

uint16_t CRC16_2(uint8_t *ptr, uint8_t lenght){
	uint16_t crc = 0xffff;
	uint8_t s = 0x00;

	while (lenght--){
		crc ^= *ptr++;

		for (s = 0 ; s <8 ;s++){
			if ((crc & 0x01) != 0){
				crc >>= 1;
				crc ^= 0xA001;

			}
			else{
				crc >>= 1;
			}
		}
	}
	return crc;
}

void updateSensor(){
			HAL_I2C_Master_Transmit(&hi2c1, 0x5c << 1 , cmdBuffer, 3, 200);
		  	HAL_I2C_Master_Transmit(&hi2c1, 0x5c << 1 , cmdBuffer, 3, 200);
		  	HAL_Delay(1);
		  	// receive sensor data
		  	HAL_I2C_Master_Receive(&hi2c1, 0x5c << 1 , dataBuffer , 8, 200);
		  	uint16_t Rcrc = dataBuffer[7] << 8 ;
		  	Rcrc += dataBuffer[6];
		  	if (Rcrc == CRC16_2(dataBuffer,6)){
		  		uint16_t temperature = ((dataBuffer[4] & 0x7F) << 8 ) + dataBuffer[5];
		  		temp = temperature  / 10.0 ;
		  		temp = (((dataBuffer[4] & 0x80) >> 7 ) == 1)? (temp * (-1)) : temp ;

		  		uint16_t humi = (dataBuffer[2] << 8) + dataBuffer[3] ;
		  		RH = humi / 10.0 ;
		  	}
}


void ex1(){
	updateSensor();

		  unsigned short int color = RGB565(Red,Green,Blue);
		  char strcolor[]="";

				    		    sprintf(strcolor,"%d",color);

				    		    ILI9341_Draw_Text(strcolor, 120, 60, BLACK, 2, WHITE);


		  	  	char s[] = "";

		  	  	sprintf(s,"%.1f C",temp);

		  	  	ILI9341_Draw_Text(s, 20, 30, BLACK, 2, WHITE);

		  	  	ILI9341_Draw_Filled_Circle(135, 35, 27,color );

		  	  sprintf(s,"%.1f %%RH",RH);

		  	  	ILI9341_Draw_Text(s, 170, 30, BLACK, 2, WHITE);



		  		ILI9341_Draw_Filled_Circle(60, 85, 20, RED);

		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 75, 190, 95, 0xFDD7);

		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 75, Red+90, 95, RED);

		  		char str[] ="";
		  		sprintf(str,"%d %%",Red);

		  		ILI9341_Draw_Text(str, 200, 75, BLACK, 2, WHITE);

		  		////////////////

		  		ILI9341_Draw_Filled_Circle(60, 145, 20, GREEN);


		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 135, 190, 155, 0xCFF8);

		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 135, Green+90, 155, GREEN);



		  		sprintf(str,"%d %%",Green);

		  		ILI9341_Draw_Text(str, 200, 135, BLACK, 2, WHITE);

		  		//////


		  		ILI9341_Draw_Filled_Circle(60, 205, 20, BLUE);

		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 195, 190, 215, 0xCE7F);

		  		ILI9341_Draw_Filled_Rectangle_Coord(90, 195, Blue+90, 215, BLUE);

		  		sprintf(str,"%d %%",Blue);
		  		ILI9341_Draw_Text(str, 200, 195, BLACK, 2, WHITE);




		  		if(TP_Touchpad_Pressed()){

					uint16_t x_pos = 0;
					uint16_t y_pos = 0;


					//HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_SET);

					uint16_t position_array[2];

					if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
					{
					x_pos = position_array[0];
					y_pos = position_array[1];



					if (x_pos > 200 && x_pos < 222) {
						if (y_pos > 115 && y_pos < 157 ){
							state = 1;
							ch2 = 0;
							timestart = count;

						}
					}





					// RED

					if (x_pos > 135 && x_pos < 160) {
						if (y_pos > 40 && y_pos < 70 ){
							Red += 10;

							if (Red > 100){
								Red = 0;
								ILI9341_Draw_Filled_Rectangle_Coord(90, 75, 300, 95, WHITE);

							}
						}
					}

					else if (x_pos > 80 && x_pos < 100) {
						if (y_pos > 40 && y_pos < 70 ){

							Green += 10;

							if (Green > 100){
								Green = 0;

								ILI9341_Draw_Filled_Rectangle_Coord(90, 135, 300, 155, WHITE);
							}

						}
					}
					else if (x_pos > 20 && x_pos < 50) {
							if (y_pos > 40 && y_pos < 70 ){
								Blue += 10;

								if (Blue > 100){
									Blue = 0;

									ILI9341_Draw_Filled_Rectangle_Coord(90, 195, 300, 215, WHITE);
								}
							}
						}





					}



		  }

}

void ex2(){

	  ILI9341_Draw_Image((const char*) snow_tiger, SCREEN_HORIZONTAL_1);

	  ILI9341_Draw_Text("Group No.18",135 , 70 , BLACK, 2, WHITE);

	  ILI9341_Draw_Text("PITPIBUL",135 , 100 , BLACK, 2, WHITE);

	  ILI9341_Draw_Text("PHONGPHOTJANATHAM",135 , 130 , BLACK, 1, WHITE);

	  ILI9341_Draw_Text("64010591",135 , 160 , BLACK, 2, WHITE);


}


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
