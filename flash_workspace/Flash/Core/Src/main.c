/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define FLASH_BASE_ADDR 0x40022000
void flash_erase_page (int page)
{
	uint32_t* FLASH_SR= (uint32_t*)(FLASH_BASE_ADDR + 0x0c);
	uint32_t* FLASH_CR= (uint32_t*)(FLASH_BASE_ADDR + 0x10);
	uint32_t* FLASH_AR= (uint32_t*)(FLASH_BASE_ADDR + 0x14);
	uint32_t* FLASH_KEYR= (uint32_t*)(FLASH_BASE_ADDR + 0x04);

	while(((*FLASH_SR>>0) & 1) == 1); //wait when no flash memory operation ongoing.Wait BSY
	if(((*FLASH_CR>>7) & 1) == 1) //check lock bit
	{
		//unlock CR
		*FLASH_KEYR= 0x45670123 ;
		*FLASH_KEYR= 0xCDEF89AB ;
	}
	*FLASH_CR |= (1<<1);// set per bit
	//*FLASH_AR |=(1 << page);
	*FLASH_AR=(uint32_t*)(0x08000000 +(page*1024));
	*FLASH_CR |= (1<<6); //start erase operation
	while(((*FLASH_SR>>0) & 1) == 1); //wait BSY is clear.
	*FLASH_CR &= ~(1<<1);
}
// addr must uint16_t as it just write half word once
void flash_program(uint16_t* addr, uint8_t value)
{
	uint32_t* FLASH_SR= (uint32_t*)(FLASH_BASE_ADDR + 0x0c);
	uint32_t* FLASH_CR= (uint32_t*)(FLASH_BASE_ADDR + 0x10);
	uint32_t* FLASH_OPTKEYR= (uint32_t*)(FLASH_BASE_ADDR + 0x08);
	uint32_t* FLASH_KEYR= (uint32_t*)(FLASH_BASE_ADDR + 0x04);

	if(((*FLASH_CR>>7) & 1) == 1) //check lock bit
	{
		//*FLASH_OPTKEYR = 0x00A5;// enable to set Option bytes write enable
		//unlock CR
		*FLASH_KEYR= 0x45670123 ;
		*FLASH_KEYR= 0xCDEF89AB ;
	}
	while(((*FLASH_SR>>0) & 1) == 1); //wait when no flash memory operation ongoing.Wait BSY
	*FLASH_CR |= 1<<0; //enable programing operation
	//*FLASH_CR |= (1<<5)|(1<<9);// enable option bytes to write single byte. ( with default it write half word)
	*addr=value;
	while(((*FLASH_SR>>0) & 1) == 1); //wait BSY is clear.
	*FLASH_CR &= ~(1<<0);

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
  /* USER CODE BEGIN 2 */
  flash_erase_page(4); //The FW contains more than 3KB so you cannot delete pages from 0-4 otherwise it will delete your FW.
  flash_program(0x08001000, 0x12);
  __asm("nop");
  /* USER CODE END 2 */

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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
  while (1)
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
