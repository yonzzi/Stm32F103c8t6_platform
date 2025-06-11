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
void led_init()
{
	//before using any peripheral -> have to give clock for work
	__HAL_RCC_GPIOB_CLK_ENABLE(); //hal : tÃªn hÃ£ng, RCC: bá»™ táº¡o clock
	//initial to set PB6 in output push-pull
	uint32_t* GPIOB_CRL = (uint32_t*)(0x40010c00);// add base + add offset
	*GPIOB_CRL &=~(0b1111<<24);
	*GPIOB_CRL |=(0b0001<<24); //set PB6 in output config ( Mode[1,0] >00-> output; =00-> input) // <<22 lÃ  vá»‹ trÃ­ nha, do mÃ¬nh Ä‘á»ƒ cÃ³ 0bxx nÃªn nÃ³ Ä‘ang khÃ´ng lÃ  32 bit, pháº£i dá»‹ch nÃ³ Ä‘á»ƒ Ä‘Ãºng vá»‹ trÃ­
	//*GPIOB_CRL &=~(0b11<<10); // set PB6  in push-pull mode (01)

}
void led_control(char led_state)
{
	//set led in PB6 light
	// add of output data register
	uint32_t* GPIOB_ODR = (uint32_t*)(0x40010c0c);
	if( led_state==1)
	*GPIOB_ODR |= 1<<6;
	else
    *GPIOB_ODR &= ~(1<<6);
}


void capture_init()
{
	 //config for PA6 as TIM3 CH1
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    uint32_t *GPIOA_CRH = (uint32_t *)(0x40010800);
	    *GPIOA_CRL &= ~(0b1111 << 24);
	    *GPIOA_CRL |= (0b0100 << 24); // alternate function push-pull

	    uint32_t* AFIO_MAPR = (uint32_t*)(0x40010000 + 0x04);
		*AFIO_MAPR &=~(0x11<<6);
		*AFIO_MAPR =(0x01<<6);		//map as time3 channel 1 for PA11

	    __HAL_RCC_TIM3_CLK_ENABLE();
	    uint16_t *TIM3_PSC = (uint32_t *)(0x40000428); // pre scaler
	    uint16_t *TIM3_CR1 = (uint32_t *)(0x40000400);// timerx control
	    uint16_t *TIM3_ARR = (uint32_t *)(0x4000042c); // set count
	    uint16_t *TIM3_SMCR = (uint32_t *)(0x40000408); // set slave value
	    uint16_t *TIM3_CCMR1_Input = (uint32_t *)(0x40000418); //capture/compare mode output
	    uint16_t *TIM3_CCER = (uint32_t *)(0x40000420); // enable compare or capture

	    *TIM3_ARR = 0xFFFF; //max count = max
	    *TIM3_PSC = 800-1; //set timer basic with cycle

	    //select Channel 1 work at capture
	    *TIM3_CCMR1_Input |= (0b01<<0); // set channel in capture input mode

	    *TIM3_CCER &= ~(1<<1); //set rising as trigger to capture
	    *TIM3_CCER |=1<<0;//enable CH1( compare/capture)

	    *TIM3_SMCR |= (0b100 << 0) | (0b101 << 4); //reset cnt when rising
	    //enable counter
	    *TIM3_CR1 |=1<<0;
}
void capture_read()
{
	// read CCRx register
	uint32_t* TIM3_CCR1 = (uint32_t*)(0x40000434);
	return *TIM3_CCR1;
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
  led_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6); // đảo trạng thái trên chân PC13
	  led_control(1);
	  HAL_Delay(100);
	  led_control(0);
	  HAL_Delay(100);
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
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
