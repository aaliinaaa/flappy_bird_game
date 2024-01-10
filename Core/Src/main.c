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
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "disp1color.h"
#include "font.h"
#include <locale.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define f6x8_MONO_WIDTH 3
#define WIDTH 32
#define HEIGHT 16
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

extern uint8_t data1[16], data2[16], data3[16], data4[16];


char hitbox[HEIGHT][WIDTH + 10]; // отвечает за работу хитбоксов


int16_t h;
int16_t counter;
int16_t numb;
int16_t number;
int16_t gameover = 0;
uint16_t flag3;
uint8_t flag4 = 0;
uint8_t flag5 = 0;
uint8_t flag6 = 0;
int16_t a, b, c, d, e, f, g, t = 1;
uint16_t count;
uint16_t pred_count;
uint16_t score;
uint16_t score1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void disp_row(uint16_t row) {

	if (row == 0) {

		for (uint8_t i = 0; i < 6; i++) {
			HAL_SPI_Transmit(&hspi1, &data1, 16, 1);
		}

		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
	}
	if (row == 1) {

		for (uint8_t i = 0; i < 6; i++) {
			HAL_SPI_Transmit(&hspi1, &data2, 16, 1);
		}

		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
	}

	if (row == 2) {

		for (uint8_t i = 0; i < 6; i++) {
			HAL_SPI_Transmit(&hspi1, &data3, 16, 1);
		}

		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	}

	if (row == 3) {

		for (uint8_t i = 0; i < 6; i++) {
			HAL_SPI_Transmit(&hspi1, &data4, 16, 1);
		}

		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
	for (uint32_t g = 0; g <= 500; g++) {};
	HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
}

void draw_screen(uint8_t state) { // включает/выключает все светодиоды на экране
	for (uint16_t i = 0; i < WIDTH; i++) {
		for (uint16_t j = 0; j < HEIGHT; j++) {
			disp1color_DrawPixel(i, j, state);
		}
	}
}

void draw_bird(int16_t h) {
	disp1color_DrawRectangle(14 + h, 6, 17 + h, 9);
}

void draw_box(int16_t number, int16_t counter) {
	disp1color_DrawRectangle(21 - number, 11 + counter, 31, 15 + counter); //верхний
	disp1color_DrawRectangle(10 - number, 11 + counter, 0, 15 + counter); //нижний

}

void is_gameover(int16_t number, int16_t counter, int16_t h) {
	if (t > 0) {
		a = 11 + counter;
		d = 21 - number - 17 - h;
		g = 14 + h - 10 + number;
		if (11 + counter >= 2 && 11 + counter <= 9 && ((21 - number - 17 - h < 2) || (14 + h - 10 + number < 2))) {
			gameover = 1;
		}
		else {gameover = 0;}
		}
	else {gameover = 0;}

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
  MX_ADC3_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);

	char *gameoverr = "LOSER";
	char *pMyStr[1000];
	char *scor[5];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		if (gameover == 0) {
			draw_screen(0);
			draw_bird(h);
			number = (numb - 1) * 2;
			draw_box(number, counter);
			is_gameover(number, counter, h);
			disp1color_UpdateFromBuff(); //Перевод рассчитанных данных в массив
			prepare_data(); //Разбиение массива на массивы под каждую строку
			for (uint8_t i = 0; i < 20; i++) {
				disp_row(0);
				disp_row(1);
				disp_row(2);
				disp_row(3);
			}
		}
		else {
			if (flag4 == 0) {
					disp1color_UpdateFromBuff(); //Перевод рассчитанных данных в массив
					prepare_data(); //Разбиение массива на массивы под каждую строку
					for (uint8_t i = 0; i < 20; i++) {
						disp_row(0);
						disp_row(1);
						disp_row(2);
						disp_row(3);
					}
					if (flag5 == 0) {pred_count = count; flag5 = 1;}
					if (count - pred_count > 15){ flag4 = 1; }
			}
			else {
//					draw_screen(0);
//					snprintf(pMyStr, sizeof pMyStr, "%s", gameoverr); //вывод строки горизонтально
//					disp1color_printf(1, 4, FONTID_6X8M, pMyStr);
//					disp1color_UpdateFromBuff(); //Перевод рассчитанных данных в массив
//					prepare_data(); //Разбиение массива на массивы под каждую строку
//					for (uint8_t i = 0; i < 20; i++) {
//						disp_row(0);
//						disp_row(1);
//						disp_row(2);
//						disp_row(3);
//					}
					if (flag6 == 0) {score1 = score; flag6 = 1;}
					draw_screen(0);
					sprintf(scor, "%d", score1);
					disp1color_printf(11, 4, FONTID_6X8M, scor);
					disp1color_UpdateFromBuff(); //Перевод рассчитанных данных в массив
										prepare_data(); //Разбиение массива на массивы под каждую строку
										for (uint8_t i = 0; i < 20; i++) {
											disp_row(0);
											disp_row(1);
											disp_row(2);
											disp_row(3);
										}

			}
		}
	}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
