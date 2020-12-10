/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

	//Defines the matrix for each side of the cube
	//Cube is oriented so Red is facing forward and green is on top

/* Orange  = 1
 * Yellow  = 2
 * White 	 = 3
 * Blue    = 4
 * Green   = 5
 * Red     = 6
 * */


int orange[3][3] = {
{5,2,1},
{3,1,5},
{2,3,1},
};

int yellow[3][3] = {
{5,4,6},
{3,2,5},
{2,2,6},
};

int white[3][3] = {
{3,1,6},
{4,3,1},
{1,1,5},
};

int blue[3][3] = {
{4,6,4},
{4,4,2},
{4,6,1},
};

int green[3][3] = {
{3,5,2},
{3,5,4},
{4,6,5},
};

int red[3][3] = {
{2,2,6},
{1,6,6},
{3,5,3},
};

int Moves[500];
int m = 0;

int Front = 0;
int Back = 0;
int Right = 0;
int Left = 0;
int Top = 0;
int Bottom = 0;


//pins PB5, PB6, and PB7 used for DEMUX selection of motors
void FrontRightMotor(void) {		//6 clockwise moves but are actually 6 counterclockwise moves from motor perspective
	int i;
	GPIOB->ODR = 0x00; //select 0

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}

void BackLeftMotor(void) {
	int i;
	GPIOB->ODR = 0x20;	//select 1

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}

void RightForwardMotor(void) {
	int i;
	GPIOB->ODR = 0x40;	//select 2

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}

void LeftBackwardMotor(void)	{
	int i;
	GPIOB->ODR = 0x60;	//select 3

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}

void TopRightMotor(void)	{
	int i;
	GPIOB->ODR = 0x80;	//select 4

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}

void BottomRightMotor(void) {
	int i;
	GPIOB->ODR = 0xA0;	//select 5

	GPIOA->ODR = 0x1;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x3;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x2;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0xA;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x8;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x18;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x10;
	for(i = 1; i<4000; i++);

	GPIOA->ODR = 0x11;
	for(i = 1; i<4000; i++);
}
void FrontLeftMotor(void) {	//6 counterclockwise moves but actually 6 clockwise moves from motor perspective
		int i;
		GPIOB->ODR = 0x00;	//select 0

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}

void BackRightMotor(void) {
		int i;
		GPIOB->ODR = 0x20;	//select 1

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}

void RightBackwardMotor(void) {
		int i;
		GPIOB->ODR = 0x40;	//select 2

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}

void LeftForwardMotor(void) {
		int i;
		GPIOB->ODR = 0x60;	//select 3

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}

void TopLeftMotor(void)	{
		int i;
		GPIOB->ODR = 0x80;		//select 4

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}

void BottomLeftMotor(void)	{
		int i;
		GPIOB->ODR = 0xA0;	//select 5

		GPIOA->ODR = 0x11;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x10;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x18;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x8;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0xA;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x2;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x3;
		for(i = 1; i<4000; i++);

		GPIOA->ODR = 0x1;
		for(i = 1; i<4000; i++);
}



void FrontRight(void) {

int red1 = red[0][0];
int red2 = red[0][1];
int red3 = red[0][2];
int red4 = red[1][0];
int red5 = red[1][1];
int red6 = red[1][2];
int red7 = red[2][0];
int red8 = red[2][1];
int red9 = red[2][2];

	red[0][0] = red7;
	red[0][1] = red4;
	red[0][2] = red1;
	red[1][0] = red8;
	red[1][1] = red5;
	red[1][2] = red2;
	red[2][0] = red9;
	red[2][1] = red6;
	red[2][2] = red3;

int	yprevious1 = yellow[0][2];
int	yprevious2 = yellow[1][2];
int	yprevious3 = yellow[2][2];

	yellow[0][2] = blue[0][0];
	yellow[1][2] = blue[0][1];
	yellow[2][2] = blue[0][2];

	blue[0][0] = white[2][0];
	blue[0][1] = white[1][0];
	blue[0][2] = white[0][0];

	white[0][0] = green[2][0];
	white[1][0] = green[2][1];
	white[2][0] = green[2][2];

	green[2][0] = yprevious3;
	green[2][1] = yprevious2;
	green[2][2] = yprevious1;

	if(Front == 1)
	{
		Moves[m] = 1;
		m = m + 1;
		Front = 1;
	}
	else if(Front == 2)
	{
		Moves[m] = 13;
		m = m + 1;
		Front = 1;
	}
	else
	{
		Moves[m] = 25;
		m = m + 1;
		Front = 1;
	}

}

void BackLeft(void) {

int orange1 = orange[0][0];
int orange2 = orange[0][1];
int orange3 = orange[0][2];
int orange4 = orange[1][0];
int orange5 = orange[1][1];
int orange6 = orange[1][2];
int orange7 = orange[2][0];
int orange8 = orange[2][1];
int orange9 = orange[2][2];

	orange[0][0] = orange7;
	orange[0][1] = orange4;
	orange[0][2] = orange1;
	orange[1][0] = orange8;
	orange[1][1] = orange5;
	orange[1][2] = orange2;
	orange[2][0] = orange9;
	orange[2][1] = orange6;
	orange[2][2] = orange3;

int	wprevious1 = white[0][2];
int	wprevious2 = white[1][2];
int	wprevious3 = white[2][2];

	white[0][2] = blue[2][2];
	white[1][2] = blue[2][1];
	white[2][2] = blue[2][0];

	blue[2][0] = yellow[0][0];
	blue[2][1] = yellow[1][0];
	blue[2][2] = yellow[2][0];

	yellow[0][0] = green[0][2];
	yellow[1][0] = green[0][1];
	yellow[2][0] = green[0][0];

	green[0][0] = wprevious1;
	green[0][1] = wprevious2;
	green[0][2] = wprevious3;

	if(Back == 1)
	{
		Moves[m] = 2;
		m = m + 1;
		Back = 1;
	}
	else if(Back == 2)
	{
		Moves[m] = 14;
		m = m + 1;
		Back = 1;
	}
		else
	{
		Moves[m] = 26;
		m = m + 1;
		Back = 1;
	}
}

void RightForward(void) {

int white1 = white[0][0];
int white2 = white[0][1];
int white3 = white[0][2];
int white4 = white[1][0];
int white5 = white[1][1];
int white6 = white[1][2];
int white7 = white[2][0];
int white8 = white[2][1];
int white9 = white[2][2];

	white[0][0] = white7;
	white[0][1] = white4;
	white[0][2] = white1;
	white[1][0] = white8;
	white[1][1] = white5;
	white[1][2] = white2;
	white[2][0] = white9;
	white[2][1] = white6;
	white[2][2] = white3;

int	rprevious1 = red[0][2];
int	rprevious2 = red[1][2];
int	rprevious3 = red[2][2];

	red[0][2] = blue[0][2];
	red[1][2] = blue[1][2];
	red[2][2] = blue[2][2];

	blue[0][2] = orange[2][0];
	blue[1][2] = orange[1][0];
	blue[2][2] = orange[0][0];

	orange[0][0] = green[2][2];
	orange[1][0] = green[1][2];
	orange[2][0] = green[0][2];

	green[0][2] = rprevious1;
	green[1][2] = rprevious2;
	green[2][2] = rprevious3;

	if(Right == 1)
	{
		Moves[m] = 3;
		m = m + 1;
		Right = 1;
	}
	else if(Right == 2)
	{
		Moves[m] = 15;
		m = m + 1;
		Right = 1;
	}
	else
	{
		Moves[m] = 27;
		m = m + 1;
		Right = 1;
	}
}

void LeftBackward(void) {

int yellow1 = yellow[0][0];
int yellow2 = yellow[0][1];
int yellow3 = yellow[0][2];
int yellow4 = yellow[1][0];
int yellow5 = yellow[1][1];
int yellow6 = yellow[1][2];
int yellow7 = yellow[2][0];
int yellow8 = yellow[2][1];
int yellow9 = yellow[2][2];

	yellow[0][0] = yellow7;
	yellow[0][1] = yellow4;
	yellow[0][2] = yellow1;
	yellow[1][0] = yellow8;
	yellow[1][1] = yellow5;
	yellow[1][2] = yellow2;
	yellow[2][0] = yellow9;
	yellow[2][1] = yellow6;
	yellow[2][2] = yellow3;

int	oprevious1 = orange[0][2];
int	oprevious2 = orange[1][2];
int	oprevious3 = orange[2][2];

	orange[0][2] = blue[2][0];
	orange[1][2] = blue[1][0];
	orange[2][2] = blue[0][0];

	blue[0][0] = red[0][0];
	blue[1][0] = red[1][0];
	blue[2][0] = red[2][0];

	red[0][0] = green[0][0];
	red[1][0] = green[1][0];
	red[2][0] = green[2][0];

	green[0][0] = oprevious3;
	green[1][0] = oprevious2;
	green[2][0] = oprevious1;

	if(Left == 1)
	{
		Moves[m] = 4;
		m = m + 1;
		Left = 1;
	}
	else if(Left == 2)
	{
		Moves[m] = 16;
		m = m + 1;
		Left = 1;
	}
	else
	{
		Moves[m] = 28;
		m = m + 1;
		Left = 1;
	}
}

void TopRight(void) {

int green1 = green[0][0];
int green2 = green[0][1];
int green3 = green[0][2];
int green4 = green[1][0];
int green5 = green[1][1];
int green6 = green[1][2];
int green7 = green[2][0];
int green8 = green[2][1];
int green9 = green[2][2];

	green[0][0] = green7;
	green[0][1] = green4;
	green[0][2] = green1;
	green[1][0] = green8;
	green[1][1] = green5;
	green[1][2] = green2;
	green[2][0] = green9;
	green[2][1] = green6;
	green[2][2] = green3;

int	yprevious1 = yellow[0][0];
int	yprevious2 = yellow[0][1];
int	yprevious3 = yellow[0][2];

	yellow[0][0] = red[0][0];
	yellow[0][1] = red[0][1];
	yellow[0][2] = red[0][2];

	red[0][0] = white[0][0];
	red[0][1] = white[0][1];
	red[0][2] = white[0][2];

	white[0][0] = orange[0][0];
	white[0][1] = orange[0][1];
	white[0][2] = orange[0][2];

	orange[0][0] = yprevious1;
	orange[0][1] = yprevious2;
	orange[0][2] = yprevious3;

	if(Top == 1)
	{
		Moves[m] = 5;
		m = m + 1;
		Top = 1;
	}
	else if(Top == 2)
	{
		Moves[m] = 17;
		m = m + 1;
		Top = 1;
	}
	else
	{
		Moves[m] = 29;
		m = m + 1;
		Top = 1;
	}
}

void BottomRight(void) {

int blue1 = blue[0][0];
int blue2 = blue[0][1];
int blue3 = blue[0][2];
int blue4 = blue[1][0];
int blue5 = blue[1][1];
int blue6 = blue[1][2];
int blue7 = blue[2][0];
int blue8 = blue[2][1];
int blue9 = blue[2][2];

	blue[0][0] = blue7;
	blue[0][1] = blue4;
	blue[0][2] = blue1;
	blue[1][0] = blue8;
	blue[1][1] = blue5;
	blue[1][2] = blue2;
	blue[2][0] = blue9;
	blue[2][1] = blue6;
	blue[2][2] = blue3;

int	yprevious1 = yellow[2][0];
int	yprevious2 = yellow[2][1];
int	yprevious3 = yellow[2][2];

	yellow[2][0] = orange[2][0];
	yellow[2][1] = orange[2][1];
	yellow[2][2] = orange[2][2];

	orange[2][0] = white[2][0];
	orange[2][1] = white[2][1];
	orange[2][2] = white[2][2];

	white[2][0] = red[2][0];
	white[2][1] = red[2][1];
	white[2][2] = red[2][2];

	red[2][0] = yprevious1;
	red[2][1] = yprevious2;
	red[2][2] = yprevious3;

	if(Bottom == 1)
	{
		Moves[m] = 6;
		m = m + 1;
		Bottom = 1;
	}
	else if(Bottom == 2)
	{
		Moves[m] = 18;
		m = m + 1;
		Bottom = 1;
	}
	else
	{
		Moves[m] = 30;
		m = m + 1;
		Bottom = 1;
	}
}

void FrontLeft(void) {

int red1 = red[0][0];
int red2 = red[0][1];
int red3 = red[0][2];
int red4 = red[1][0];
int red5 = red[1][1];
int red6 = red[1][2];
int red7 = red[2][0];
int red8 = red[2][1];
int red9 = red[2][2];

	red[0][0] = red3;
	red[0][1] = red6;
	red[0][2] = red9;
	red[1][0] = red2;
	red[1][1] = red5;
	red[1][2] = red8;
	red[2][0] = red1;
	red[2][1] = red4;
	red[2][2] = red7;

int	yprevious1 = yellow[0][2];
int	yprevious2 = yellow[1][2];
int	yprevious3 = yellow[2][2];

	yellow[0][2] = green[2][2];
	yellow[1][2] = green[2][1];
	yellow[2][2] = green[2][0];

	green[2][0] = white[0][0];
	green[2][1] = white[1][0];
	green[2][2] = white[2][0];

	white[0][0] = blue[0][2];
	white[1][0] = blue[0][1];
	white[2][0] = blue[0][0];

	blue[0][2] = yprevious3;
	blue[0][1] = yprevious2;
	blue[0][0] = yprevious1;

	if(Front == 2)
	{
		Moves[m] = 7;
		m = m + 1;
		Front = 2;
	}
	else if(Front == 1)
	{
		Moves[m] = 19;
		m = m + 1;
		Front = 2;
	}
	else
	{
		Moves[m] = 31;
		m = m + 1;
		Front = 2;
	}
}

void BackRight(void) {

int orange1 = orange[0][0];
int orange2 = orange[0][1];
int orange3 = orange[0][2];
int orange4 = orange[1][0];
int orange5 = orange[1][1];
int orange6 = orange[1][2];
int orange7 = orange[2][0];
int orange8 = orange[2][1];
int orange9 = orange[2][2];

	orange[0][0] = orange3;
	orange[0][1] = orange6;
	orange[0][2] = orange9;
	orange[1][0] = orange2;
	orange[1][1] = orange5;
	orange[1][2] = orange8;
	orange[2][0] = orange1;
	orange[2][1] = orange4;
	orange[2][2] = orange7;


int	wprevious1 = white[0][2];
int	wprevious2 = white[1][2];
int	wprevious3 = white[2][2];

	white[0][2] = green[0][0];
	white[1][2] = green[0][1];
	white[2][2] = green[0][2];

	green[0][0] = yellow[2][0];
	green[0][1] = yellow[1][0];
	green[0][2] = yellow[0][0];

	yellow[0][0] = blue[2][0];
	yellow[1][0] = blue[2][1];
	yellow[2][0] = blue[2][2];

	blue[2][0] = wprevious3;
	blue[2][1] = wprevious2;
	blue[2][2] = wprevious1;

	if(Back == 2)
	{
		Moves[m] = 8;
		m = m + 1;
		Back = 2;
	}
	else if(Back == 1)
	{
		Moves[m] = 20;
		m = m + 1;
		Back = 2;
	}
	else
	{
		Moves[m] = 32;
		m = m + 1;
		Back = 2;
	}
}

void RightBackward(void) {

int white1 = white[0][0];
int white2 = white[0][1];
int white3 = white[0][2];
int white4 = white[1][0];
int white5 = white[1][1];
int white6 = white[1][2];
int white7 = white[2][0];
int white8 = white[2][1];
int white9 = white[2][2];

	white[0][0] = white3;
	white[0][1] = white6;
	white[0][2] = white9;
	white[1][0] = white2;
	white[1][1] = white5;
	white[1][2] = white8;
	white[2][0] = white1;
	white[2][1] = white4;
	white[2][2] = white7;

int	rprevious1 = red[0][2];
int	rprevious2 = red[1][2];
int	rprevious3 = red[2][2];

	red[0][2] = green[0][2];
	red[1][2] = green[1][2];
	red[2][2] = green[2][2];

	green[0][2] = orange[2][0];
	green[1][2] = orange[1][0];
	green[2][2] = orange[0][0];

	orange[2][0] = blue[0][2];
	orange[1][0] = blue[1][2];
	orange[0][0] = blue[2][2];

	blue[0][2] = rprevious1;
	blue[1][2] = rprevious2;
	blue[2][2] = rprevious3;

	if(Right == 2)
	{
		Moves[m] = 9;
		m = m + 1;
		Right = 2;
	}
	else if(Right == 1)
	{
		Moves[m] = 21;
		m = m + 1;
		Right = 2;
	}
	else
	{
		Moves[m] = 33;
		m = m + 1;
		Right = 2;
	}
}

void LeftForward(void) {

int yellow1 = yellow[0][0];
int yellow2 = yellow[0][1];
int yellow3 = yellow[0][2];
int yellow4 = yellow[1][0];
int yellow5 = yellow[1][1];
int yellow6 = yellow[1][2];
int yellow7 = yellow[2][0];
int yellow8 = yellow[2][1];
int yellow9 = yellow[2][2];

	yellow[0][0] = yellow3;
	yellow[0][1] = yellow6;
	yellow[0][2] = yellow9;
	yellow[1][0] = yellow2;
	yellow[1][1] = yellow5;
	yellow[1][2] = yellow8;
	yellow[2][0] = yellow1;
	yellow[2][1] = yellow4;
	yellow[2][2] = yellow7;

int	oprevious1 = orange[0][2];
int	oprevious2 = orange[1][2];
int	oprevious3 = orange[2][2];

	orange[0][2] = green[2][0];
	orange[1][2] = green[1][0];
	orange[2][2] = green[0][0];

	green[2][0] = red[2][0];
	green[1][0] = red[1][0];
	green[0][0] = red[0][0];

	red[2][0] = blue[2][0];
	red[1][0] = blue[1][0];
	red[0][0] = blue[0][0];

	blue[2][0] = oprevious1;
	blue[1][0] = oprevious2;
	blue[0][0] = oprevious3;

	if(Left == 2)
	{
		Moves[m] = 10;
		m = m + 1;
		Left = 2;
	}
	else if(Left == 1)
	{
		Moves[m] = 22;
		m = m + 1;
		Left = 2;
	}
	else
	{
		Moves[m] = 34;
		m = m + 1;
		Left = 2;
	}
}

void TopLeft(void) {

int green1 = green[0][0];
int green2 = green[0][1];
int green3 = green[0][2];
int green4 = green[1][0];
int green5 = green[1][1];
int green6 = green[1][2];
int green7 = green[2][0];
int green8 = green[2][1];
int green9 = green[2][2];

	green[0][0] = green3;
	green[0][1] = green6;
	green[0][2] = green9;
	green[1][0] = green2;
	green[1][1] = green5;
	green[1][2] = green8;
	green[2][0] = green1;
	green[2][1] = green4;
	green[2][2] = green7;


int	yprevious1 = yellow[0][0];
int	yprevious2 = yellow[0][1];
int	yprevious3 = yellow[0][2];

	yellow[0][0] = orange[0][0];
	yellow[0][1] = orange[0][1];
	yellow[0][2] = orange[0][2];

	orange[0][0] = white[0][0];
	orange[0][1] = white[0][1];
	orange[0][2] = white[0][2];

	white[0][0] = red[0][0];
	white[0][1] = red[0][1];
	white[0][2] = red[0][2];

	red[0][0] = yprevious1;
	red[0][1] = yprevious2;
	red[0][2] = yprevious3;

	if(Top == 2)
	{
		Moves[m] = 11;
		m = m + 1;
		Top = 2;
	}
	else if(Top == 1)
	{
		Moves[m] = 23;
		m = m + 1;
		Top = 2;
	}
	else
	{
		Moves[m] = 35;
		m = m + 1;
		Top = 2;
	}
}

void BottomLeft(void) {

int blue1 = blue[0][0];
int blue2 = blue[0][1];
int blue3 = blue[0][2];
int blue4 = blue[1][0];
int blue5 = blue[1][1];
int blue6 = blue[1][2];
int blue7 = blue[2][0];
int blue8 = blue[2][1];
int blue9 = blue[2][2];

	blue[0][0] = blue3;
	blue[0][1] = blue6;
	blue[0][2] = blue9;
	blue[1][0] = blue2;
	blue[1][1] = blue5;
	blue[1][2] = blue8;
	blue[2][0] = blue1;
	blue[2][1] = blue4;
	blue[2][2] = blue7;

int	yprevious1 = yellow[2][0];
int	yprevious2 = yellow[2][1];
int	yprevious3 = yellow[2][2];

	yellow[2][0] = red[2][0];
	yellow[2][1] = red[2][1];
	yellow[2][2] = red[2][2];

	red[2][0] = white[2][0];
	red[2][1] = white[2][1];
	red[2][2] = white[2][2];

	white[2][0] = orange[2][0];
	white[2][1] = orange[2][1];
	white[2][2] = orange[2][2];

	orange[2][0] = yprevious1;
	orange[2][1] = yprevious2;
	orange[2][2] = yprevious3;

	if(Bottom == 2)
	{
		Moves[m] = 12;
		m = m + 1;
		Bottom = 2;
	}
	else if(Bottom == 1)
	{
		Moves[m] = 24;
		m = m + 1;
		Bottom = 2;
	}
	else
	{
		Moves[m] = 36;
		m = m + 1;
		Bottom = 2;
	}
}

void RightAlg(void) {

	RightForward();
	TopRight();
	RightBackward();
	TopLeft();
}

void LeftAlg(void) {

	LeftForward();
	TopLeft();
	LeftBackward();
	TopRight();
}

void WhiteCross(void) {

	while ((white[0][1] != 3) || (green[1][2] != 5) || (white[1][0] != 3) || (red[1][2] != 6) || (white[2][1] != 3) || (blue[1][2] != 4) || (white[1][2] != 3) || (orange[1][0] != 1))
	{

		while ((yellow[0][1] != 3) || (green[1][0] != 5) || (yellow[1][0] != 3) || (orange[1][2] != 1) || (yellow[2][1] != 3) || (blue[1][0] != 4) || (yellow[1][2] != 3) || (red[1][0] != 6))  //Forming the Daisy
		{
			while(green[1][0] != 5 || yellow[0][1] != 3) //green's side
			{
				//top layer (close to yellow)
				if(red[1][0] == 5 && yellow[1][2] == 3)
				{
					FrontRight();
					FrontRight();
					RightForward();
					TopLeft();
					TopLeft();
				}
				if(blue[1][0] == 5 && yellow[2][1] == 3)
				{
					BottomRight();
					BottomRight();
					RightForward();
					RightForward();
					TopLeft();
					TopLeft();
				}
				if(orange[1][2] == 5 && yellow[1][0] == 3)
				{
					BackRight();
					BackRight();
					RightBackward();
					TopLeft();
					TopLeft();
				}//------------------------------------------
				//top layer edge inverted
				if(green[1][0] == 3 && yellow[0][1] == 5)
				{
					TopRight();
					TopRight();
					RightBackward();
					FrontLeft();
					TopRight();
					FrontRight();
				}
				if(yellow[1][2] == 5 && red[1][0] == 3)
				{
					FrontRight();
					TopRight();
					FrontLeft();
				}
				if(yellow[2][1] == 5 && blue[1][0] == 3)
				{
					BottomRight();
					BottomRight();
					RightForward();
					FrontLeft();
					TopRight();
					FrontRight();
				}
				if(yellow[1][0] == 5 && orange[1][2] == 3)
				{
					BackRight();
					TopLeft();
					BackLeft();
				}//------------------------------------------
				//Bottom Layer (close to white)
				if(green[1][2] == 5 && white[0][1] == 3)
				{
					TopRight();
					TopRight();
				}
				if(white[1][2] == 3 && orange[1][0] == 5)
				{
					RightBackward();
					TopRight();
					TopRight();
				}
				if(white[2][1] == 3 && blue[1][2] == 5)
				{
					RightForward();
					RightForward();
					TopRight();
					TopRight();
				}
				if(white[1][0] == 3 && red[1][2] == 5)
				{
					RightForward();
					TopRight();
					TopRight();
				}
				//--------------------------------------------
				//Bottom Layer Inverted
				if(green[1][2] == 3 && white[0][1] == 5)
				{
					RightBackward();
					FrontLeft();
					TopRight();
					FrontRight();
				}
				if(white[1][2] == 5 && orange[1][0] == 3)
				{
					BackLeft();
					TopLeft();
					BackRight();
				}
				if(white[2][1] == 5 && blue[1][2] == 3)
				{
					RightForward();
					FrontLeft();
					TopRight();
					FrontRight();
				}
				if(white[1][0] == 5 && red[1][2] == 3)
				{
					FrontLeft();
					TopRight();
					FrontRight();
				}
				//--------------------------------------------
				//Middle Layer
				if(green[0][1] == 5 && orange[0][1] == 3)
				{
					TopLeft();
				}
				if(green[2][1] == 5 && red[0][1] == 3)
				{
					TopRight();
				}
				if(green[2][1] == 3 && red[0][1] == 5)
				{
					FrontRight();
					RightForward();
					FrontLeft();
					TopRight();
					TopRight();
				}
				if(red[2][1] == 5 && blue[0][1] == 3)
				{
					FrontLeft();
					RightForward();
					FrontRight();
					TopRight();
					TopRight();
				}
				if(red[2][1] == 3 && blue[0][1] == 5)
				{
					BottomRight();
					RightForward();
					RightForward();
					BottomLeft();
					TopRight();
					TopRight();
				}
				if(blue[2][1] == 5 && orange[2][1] == 3)
				{
					BottomLeft();
					RightForward();
					RightForward();
					BottomRight();
					TopRight();
					TopRight();
				}
				if(blue[2][1] == 3 && orange[2][1] == 5)
				{
					BackLeft();
					RightBackward();
					BackRight();
					TopRight();
					TopRight();
				}
				if(green[0][1] == 3 && orange[0][1] == 5)
				{
					BackRight();
					RightBackward();
					TopRight();
					TopRight();
				}
			}
			while(red[1][0] != 6 || yellow[1][2] != 3) //red's side
			{
				//top layer (close to yellow)
				if(blue[1][0] == 6 && yellow[2][1] == 3)
				{
					BottomRight();
					BottomRight();
					RightForward();
					FrontRight();
					FrontRight();
				}
				if(orange[1][2] == 6 && yellow[1][0] == 3)
				{
					BackRight();
					BackRight();
					RightBackward();
					RightBackward();
					FrontRight();
					FrontRight();
				}
				if(green[1][0] == 6 && yellow[0][1] == 3)
				{
					TopRight();
					TopRight();
					RightBackward();
					FrontRight();
					FrontRight();
				}
				//------------------------------------
				//top layer inverted
				if(red[1][0] == 3 && yellow[1][2] == 6)
				{
					FrontRight();
					FrontRight();
					RightBackward();
					BottomLeft();
					FrontRight();
					BottomRight();
				}
				if(blue[1][0] == 3 && yellow[2][1] == 6)
				{
					BottomRight();
					FrontRight();
					BottomLeft();
				}
				if(orange[1][2] == 3 && yellow[1][0] == 6)
				{
					BackRight();
					BackRight();
					RightBackward();
					TopRight();
					FrontLeft();
					TopLeft();
				}
				if(green[1][0] == 3 && yellow[0][1] == 6)
				{
					TopLeft();
					FrontLeft();
					TopRight();
				}
				//--------------------------------------
				//Bottom layer {close to white}
				if(red[1][2] == 6 && white[1][0] == 3)
				{
					FrontRight();
					FrontRight();
				}
				if(green[1][2] == 6 && white[0][1] == 3)
				{
					RightBackward();
					FrontRight();
					FrontRight();
				}
				if(orange[1][0] == 6 && white[1][2] == 3)
				{
					RightBackward();
					RightBackward();
					FrontRight();
					FrontRight();
				}
				if(blue[1][2] == 6 && white[2][1] == 3)
				{
					RightForward();
					FrontRight();
					FrontRight();
				}
				//---------------------------------------
				//Bottom layer inverted
				if(red[1][2] == 3 && white[1][0] == 6)
				{
					RightBackward();
					BottomLeft();
					FrontRight();
					BottomRight();
				}
				if(green[1][2] == 3 && white[0][1] == 6)
				{
					TopRight();
					FrontLeft();
					TopLeft();
				}
				if(orange[1][0] == 3 && white[1][2] == 6)
				{
					RightBackward();
					TopRight();
					FrontLeft();
					TopLeft();
				}
				if(blue[1][2] == 3 && white[2][1] == 6)
				{
					BottomLeft();
					FrontRight();
					BottomRight();
				}
				//-----------------------------------------
				//Middle Layer
				if(red[0][1] == 6 && green[2][1] == 3)
				{
					FrontLeft();
				}
				if(red[2][1] == 6 && blue[0][1] == 3)
				{
					FrontRight();
				}
				if(red[2][1] == 3 && blue[0][1] == 6)
				{
					BottomRight();
					RightForward();
					BottomLeft();
					FrontRight();
					FrontRight();
				}
				if(blue[2][1] == 6 && orange[2][1] == 3)
				{
					BottomLeft();
					RightForward();
					BottomRight();
					FrontRight();
					FrontRight();
				}
				if(blue[2][1] == 3 && orange[2][1] == 6)
				{
					BottomLeft();
					BottomLeft();
					FrontRight();
					BottomRight();
					BottomRight();
				}
				if(green[0][1] == 3 && orange[0][1] == 6)
				{
					TopRight();
					TopRight();
					FrontLeft();
					TopLeft();
					TopLeft();
				}
				if(green[0][1] == 6 && orange[0][1] == 3)
				{
					TopRight();
					RightBackward();
					TopLeft();
					FrontRight();
					FrontRight();
				}
				if(red[0][1] == 3 && green[2][1] == 6)
				{
					TopLeft();
					RightBackward();
					TopRight();
					FrontRight();
					FrontRight();
				}
			}
			while(blue[1][0] != 4 || yellow[2][1] != 3)  //blue's side
			{
				//top layer (close to yellow)
				if(orange[1][2] == 4 && yellow[1][0] == 3)
				{
					BackLeft();
					BackLeft();
					RightForward();
					BottomLeft();
					BottomLeft();
				}
				if(green[1][0] == 4 && yellow[0][1] == 3)
				{
					TopRight();
					TopRight();
					RightForward();
					RightForward();
					BottomLeft();
					BottomLeft();
				}
				if(red[1][0] == 4 && yellow[1][2] == 3)
				{
					FrontRight();
					FrontRight();
					RightBackward();
					BottomLeft();
					BottomLeft();
				}
				//-----------------------------------------
				//top layer edge inverted
				if(blue[1][0] == 3 && yellow[2][1] == 4)
				{
					 BottomRight();
					 BottomRight();
					 RightForward();
					 FrontRight();
					 BottomLeft();
					 FrontLeft();
				}
				if(orange[1][2] == 3 && yellow[1][0] == 4)
				{
					BackLeft();
					BottomRight();
					BackRight();
				}
				if(green[1][0] == 3 && yellow[0][1] == 4)
				{
					TopLeft();
					TopLeft();
					RightBackward();
					FrontRight();
					BottomLeft();
					FrontLeft();
				}
				if(red[1][0] == 3 && yellow[1][2] == 4)
				{
					FrontLeft();
					BottomLeft();
					FrontRight();
				}
				//-------------------------------------------
				//bottom layer (close to white)
				if(blue[1][2] == 4 && white[2][1] == 3)
				{
					BottomLeft();
					BottomLeft();
				}
				if(orange[1][0] == 4 && white[1][2] == 3)
				{
					RightForward();
					BottomLeft();
					BottomLeft();
				}
				if(green[1][2] == 4 && white[0][1] == 3)
				{
					RightForward();
					RightForward();
					BottomLeft();
					BottomLeft();
				}
				if(red[1][2] == 4 && white[1][0] == 3)
				{
					RightBackward();
					BottomLeft();
					BottomLeft();
				}
				//-------------------------------------------
				//bottom layer edge inverted
				if(blue[1][2] == 3 && white[2][1] == 4)
				{
					RightForward();
					FrontRight();
					BottomLeft();
					FrontLeft();
				}
				if(orange[1][0] == 3 && white[1][2] == 4)
				{
					BackRight();
					BottomRight();
					BackLeft();
				}
				if(green[1][2] == 3 && white[0][1] == 4)
				{
					RightBackward();
					FrontRight();
					BottomLeft();
					FrontLeft();
				}
				if(red[1][2] == 3 && white[1][0] == 4)
				{
					FrontRight();
					BottomLeft();
					FrontLeft();
				}
				//------------------------------------------
				//Middle layer
				if(blue[0][1] == 4 && red[2][1] == 3)
				{
					BottomLeft();
				}
				if(blue[2][1] == 4 && orange[2][1] == 3)
				{
					BottomRight();
				}
				if(blue[2][1] == 3 && orange[2][1] == 4)
				{
					BackLeft();
					RightForward();
					BackRight();
					BottomLeft();
					BottomLeft();
				}
				if(green[0][1] == 3 && orange[0][1] == 4)
				{
					BackRight();
					RightForward();
					BackLeft();
					BottomLeft();
					BottomLeft();
				}
				if(green[0][1] == 4 && orange[0][1] == 3)
				{
					BackRight();
					BackRight();
					BottomRight();
					BackLeft();
					BackLeft();
				}
				if(green[2][1] == 4 && red[0][1] == 3)
				{
					FrontRight();
					FrontRight();
					BottomLeft();
					FrontLeft();
					FrontLeft();
				}
				if(green[2][1] == 3 && red[0][1] == 4)
				{
					TopLeft();
					RightBackward();
					TopRight();
					FrontRight();
					BottomLeft();
					FrontLeft();
				}
				if(red[2][1] == 4 && blue[0][1] == 3)
				{
					FrontLeft();
					RightBackward();
					FrontRight();
					BottomLeft();
					BottomLeft();
				}
		}
			while(orange[1][2] != 1 || yellow[1][0] != 3)  //orange's side
			{
				//top layer (close to yellow)
				if(green[1][0] == 1 && yellow[0][1] == 3)
				{
					TopLeft();
					TopLeft();
					RightForward();
					BackLeft();
					BackLeft();
				}
				if(red[1][0] == 1 && yellow[1][2] == 3)
				{
					FrontRight();
					FrontRight();
					RightForward();
					RightForward();
					BackLeft();
					BackLeft();
				}
				if(blue[1][0] == 1 && yellow[2][1] == 3)
				{
					BottomRight();
					BottomRight();
					RightBackward();
					BackLeft();
					BackLeft();
				}
				//--------------------------------------
				//top layer edge inverted
				if(orange[1][2] == 3 && yellow[1][0] == 1)
				{
					BackRight();
					TopRight();
					RightForward();
					TopLeft();
					BackLeft();
					BackLeft();
				}
				if(green[1][0] == 3 && yellow[0][1] == 1)
				{
					TopRight();
					BackLeft();
					TopLeft();
				}
				if(red[1][0] == 3 && yellow[1][2] == 1)
				{
					FrontRight();
					TopLeft();
					RightForward();
					TopRight();
					BackLeft();
					BackLeft();
				}
				if(blue[1][0] == 3 && yellow[2][1] == 1)
				{
					BottomLeft();
					BackRight();
					BottomLeft();
				}
				//---------------------------------------
				//bottom layer (close to white)
				if(orange[1][0] == 1 && white[1][2] == 3)
				{
					BackLeft();
					BackLeft();
				}
				if(green[1][2] == 1 && white[0][1] == 3)
				{
					RightForward();
					BackLeft();
					BackLeft();
				}
				if(red[1][2] == 1 && white[1][0] == 3)
				{
					RightForward();
					RightForward();
					BackLeft();
					BackLeft();
				}
				if(blue[1][2] == 1 && white[2][1] == 3)
				{
					RightBackward();
					BackLeft();
					BackLeft();
				}
				//--------------------------------------
				//bottom layer edge inverted
				if(orange[1][0] == 3 && white[1][2] == 1)
				{
					RightBackward();
					TopLeft();
					BackLeft();
					TopRight();
				}
				if(green[1][2] == 3 && white[0][1] == 1)
				{
					TopLeft();
					BackLeft();
					TopRight();
				}
				if(red[1][2] == 3 && white[1][0] == 1)
				{
					RightForward();
					TopLeft();
					BackLeft();
					TopRight();
				}
				if(blue[1][2] == 3 && white[2][1] == 1)
				{
					BottomRight();
					BackRight();
					BottomLeft();
				}
				//---------------------------------------
				//Middle Layer
				if(orange[2][1] == 1 && blue[2][1] == 3)
				{
					BackRight();
				}
				if(orange[0][1] == 1 && green[0][1] == 3)
				{
					BackLeft();
				}
				if(orange[0][1] == 3 && green[0][1] == 1)
				{
					TopRight();
					RightForward();
					TopLeft();
					BackLeft();
					BackLeft();
				}
				if(green[2][1] == 1 && red[0][1] == 3)
				{
					TopLeft();
					RightForward();
					TopRight();
					BackLeft();
					BackLeft();
				}
				if(green[2][1] == 3 && red[0][1] == 1 )
				{
					TopLeft();
					TopLeft();
					BackLeft();
					TopRight();
					TopRight();
				}
				if(red[2][1] == 1 && blue[0][1] == 3)
				{
					FrontLeft();
					RightForward();
					RightForward();
					FrontRight();
					BackLeft();
					BackLeft();
				}
				if(red[2][1] == 3 && blue[0][1] == 1)
				{
					BottomRight();
					RightBackward();
					BottomLeft();
					BackLeft();
					BackLeft();
				}
				if(orange[2][1] == 3 && blue[2][1] == 1)
				{
					BottomLeft();
					RightBackward();
					BottomRight();
					BackLeft();
					BackLeft();
				}
			}
		}
			FrontRight();
			FrontRight();
			TopLeft();
			TopLeft();
			BackRight();
			BackRight();
			BottomRight();
			BottomRight();
}
}

void WhiteCorners(void) {

	while((red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3) || (green[0][2] != 5 || orange[0][0] != 1 || white[0][2] != 3) || (orange[2][0] != 1 || blue[2][2] != 4 || white[2][2] != 3) || (blue[0][2] != 4 || red[2][2] != 6 || white[2][0] != 3))
	{
		//RED GREEN corner
		//top layer(close to yellow)
		if((red[0][0] == 5 && green[2][0] == 6 && yellow[0][2] == 3) || (red[0][0] == 3 && green[2][0] == 5 && yellow[0][2] == 6) || (red[0][0] == 6 && green[2][0] == 3 && yellow[0][2] == 5))
		{
			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((red[2][0] == 5 && yellow[2][2] == 6 && blue[0][0] == 3) || (red[2][0] == 3 && yellow[2][2] == 5 && blue[0][0] == 6) || (red[2][0] == 6 && yellow[2][2] == 3 && blue[0][0] == 5))
		{
			LeftForward();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((blue[2][0] == 3 && yellow[2][0] == 5 && orange[2][2] == 6) || (blue[2][0] == 6 && yellow[2][0] == 3 && orange[2][2] == 5) || (blue[2][0] == 5 && yellow[2][0] == 6 && orange[2][2] == 3))
		{
			LeftForward();
			LeftForward();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((green[0][0] == 6 && orange[0][2] == 3 && yellow[0][0] == 5) || (green[0][0] == 3 && orange[0][2] == 5 && yellow[0][0] == 6) || (green[0][0] == 5 && orange[0][2] == 6 && yellow[0][0] == 3))
		{
			LeftBackward();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		//---------------------------------------------------------------
		//bottom layer (close to white)
		if((red[0][2] == 5 && green[2][2] == 3 && white[0][0] == 6) || (red[0][2] == 3 && green[2][2] == 6 && white[0][0] == 5))
		{
			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((red[2][2] == 6 && white[2][0] == 5 && blue[0][2] == 3) || (red[2][2] == 5 && white[2][0] == 3 && blue[0][2] == 6) || (red[2][2] == 3 && white[2][0] == 6 && blue[0][2] == 5))
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			LeftForward();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((blue[2][2] == 3 && white[2][2] == 6 && orange[2][0] == 5) || (blue[2][2] == 6 && white[2][2] == 5 && orange[2][0] == 3) || (blue[2][2] == 5 && white[2][2] == 3 && orange[2][0] == 6))
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftBackward();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		if((green[0][2] == 5 && white[0][2] == 6 && orange[0][0] == 3) || (green[0][2] == 3 && white[0][2] == 5 && orange[0][0] == 6) || (green[0][2] == 6 && white[0][2] == 3 && orange[0][0] == 5))
		{
			BackLeft();
			LeftBackward();
			BackRight();

			while(red[0][2] != 6 || green[2][2] != 5 || white[0][0] != 3)
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
			}
		}
		//--------------------------------------------------------------
		//GREEN ORANGE corner
		//top layer(close to yellow)
		if((green[0][0] == 5 && yellow[0][0] == 1 && orange[0][2] == 3) || (green[0][0] == 1 && yellow[0][0] == 3 && orange[0][2] == 5) || (green[0][0] == 3 && yellow[0][0] == 5 && orange[0][2] == 1))
		{
			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			}
		}
		if((red[0][0] == 3 && yellow[0][2] == 5 && green[2][0] == 1) || (red[0][0] == 5 && yellow[0][2] == 1 && green[2][0] == 3) || (red[0][0] == 1 && yellow[0][2] == 3 && green[2][0] == 5))
		{
			LeftForward();

			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		if((red[2][0] == 1 && blue[0][0] == 3 && yellow[2][2] == 5) || (red[2][0] == 3 && blue[0][0] == 5 && yellow[2][2] == 1) || (red[2][0] == 5 && blue[0][0] == 1 && yellow[2][2] == 3))
		{
			LeftForward();
			LeftForward();

			while(green[0][2] != 5 || white[0][2] != 3 || orange [0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		if((blue[2][0] == 1 && yellow[2][0] == 5 && orange[2][2] == 3) || (blue[2][0] == 3 && yellow[2][0] == 1 && orange[2][2] == 5) || (blue[2][0] == 5 && yellow[2][0] == 3 && orange[2][2] == 1))
		{
			LeftBackward();

			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		//-------------------------------------------------------------
		//bottom layer(close to white)
		if((green[0][2] == 3 && white[0][2] == 1 && orange[0][0] == 5) || (green[0][2] == 1 && white[0][2] == 5 && orange[0][0] == 3))
		{
			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		if((red[0][2] == 1 && green[2][2] == 3 && white[0][0] == 5) || (red[0][2] == 3 && green[2][2] == 5 && white[0][0] == 1) || (red[0][2] == 5 && green[2][2] == 1 && white[0][0] == 3))
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			LeftForward();

			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		if((red[2][2] == 1 && white[2][0] == 3 && blue[0][2] == 5) || (red[2][2] == 3 && white[2][0] == 5 && blue[0][2] == 1) || (red[2][2] == 5 && white[2][0] == 1 && blue[0][2] == 3))
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftBackward();

			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		if((blue[2][2] == 5 && white[2][2] == 1 && orange[2][0] == 3) || (blue[2][2] == 1 && white[2][2] == 3 && orange[2][0] == 5) || (blue[2][2] == 3 && white[2][2] == 5 && orange[2][0] == 1))
		{
			BottomRight();
			LeftBackward();
			BottomLeft();

			while(green[0][2] != 5 || white[0][2] != 3 || orange[0][0] != 1)
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
			}
		}
		//------------------------------------------------------------
		//ORANGE BLUE corner
		//top layer (close to yellow)
		if((blue[2][0] == 4 && yellow[2][0] == 1 && orange[2][2] == 3) || (blue[2][0] == 3 && yellow[2][0] == 4 && orange[2][2] == 1) || (blue[2][0] == 1 && yellow[2][0] == 3 && orange[2][2] == 4))
		{
			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((green[0][0] == 4 && yellow[0][0] == 3 && orange[0][2] == 1) || (green[0][0] == 3 && yellow[0][0] == 1 && orange[0][2] == 4) || (green[0][0] == 1 && yellow[0][0] == 4 && orange[0][2] == 3))
		{
			LeftForward();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((red[0][0] == 4 && green[2][0] == 1 && yellow[0][2] == 3) || (red[0][0] == 1 && green[2][0] == 3 && yellow[0][2] == 4) || (red[0][0] == 3 && green[2][0] == 4 && yellow[0][2] == 1))
		{
			LeftForward();
			LeftForward();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((red[2][0] == 1 && yellow[2][2] == 3 && blue[0][0] == 4) || (red[2][0] == 4 && yellow[2][2] == 1 && blue[0][0] == 3) || (red[2][0] == 3 && yellow[2][2] == 4 && blue[0][0] == 1))
		{
			LeftBackward();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		//-------------------------------------------------------------
		//bottom layer (close to white)
		if((blue[2][2] == 3 && white[2][2] == 1 && orange[2][0] == 4) || (blue[2][2] == 1 && white[2][2] == 4 && orange[2][0] == 3))
		{
			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((red[2][2] == 1 && white[2][0] == 4 && blue[0][2] == 3) || (red[2][2] == 4 && white[2][0] == 3 && blue[0][2] == 1) || (red[2][2] == 3 && white[2][0] == 1 && blue[0][2] == 4))
		{
			FrontRight();
			LeftBackward();
			FrontLeft();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((red[0][2] == 3 && white[0][0] == 4 && green[2][2] == 1) || (red[0][2] == 1 && white[0][0] == 3 && green[2][2] == 4) || (red[0][2] == 4 && white[0][0] == 1 && green[2][2] == 3))
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftBackward();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		if((green[0][2] == 3 && white[0][2] == 4 && orange[0][0] == 1) || (green[0][2] == 1 && white[0][2] == 3 && orange[0][0] == 4) || (green[0][2] == 4 && white[0][2] == 1 && orange[0][0] == 3))
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			LeftForward();

			while(blue[2][2] != 4 || white[2][2] != 3 || orange[2][0] != 1)
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
			}
		}
		//---------------------------------------------------------------
		//BLUE RED corner
		//top layer (close to yellow)
		if((red[2][0] == 6 && yellow[2][2] == 4 && blue[0][0] == 3) || (red[2][0] == 3 && yellow[2][2] == 6 && blue[0][0] == 4) || (red[2][0] == 4 && yellow[2][2] == 3 && blue[0][0] == 6))
		{
			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((green[2][0] == 6 && yellow[0][2] == 4 && red[0][0] == 3) || (green[2][0] == 3 && yellow[0][2] == 6 && red[0][0] == 4) || (green[2][0] == 4 && yellow[0][2] == 3 && red[0][0] == 6))
		{
			LeftBackward();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((green[0][0] == 3 && yellow[0][0] == 4 && orange[0][2] == 6) || (green[0][0] == 4 && yellow[0][0] == 6 && orange[0][2] == 3) || (green[0][0] == 6 && yellow[0][0] == 3 && orange[0][2] == 4))
		{
			LeftBackward();
			LeftBackward();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((blue[2][0] == 6 && yellow[2][0] == 4 && orange[2][2] == 3) || (blue[2][0] == 3 && yellow[2][0] == 6 && orange[2][2] == 4) || (blue[2][0] == 4 && yellow[2][0] == 3 && orange[2][2] == 6))
		{
			LeftForward();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		//---------------------------------------------------------------
		//bottom layer (close to white}
		if((red[2][2] == 4 && blue[0][2] == 3 && white[2][0] == 6) || (red[2][2] ==  3 && blue[0][2] == 6 && white[2][0] == 4))
		{
			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((blue[2][2] == 3 && white[2][2] == 4 && orange[2][0] == 6) || (blue[2][2] == 4 && white[2][2] == 6 && orange[2][0] == 3) || (blue[2][2] == 6 && white[2][2] == 3 && orange[2][0] == 4))
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			LeftForward();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((green[0][2] == 3 && white[0][2] == 6 && orange[0][0] == 4) || (green[0][2] == 4 && white[0][2] == 3 && orange[0][0] == 6) || (green[0][2] == 6 && white[0][2] == 4 && orange[0][0] == 3))
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftBackward();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
		if((red[0][2] == 3 && green[2][2] == 4 && white[0][0] == 6) || (red[0][2] == 4 && green[2][2] == 6 && white[0][0] == 3) || (red[0][2] == 6 && green[2][2] == 3 && white[0][0] == 4))
		{
			TopRight();
			LeftBackward();
			TopLeft();

			while(red[2][2] != 6 || white[2][0] != 3 || blue[0][2] !=  4)
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
			}
		}
	}
}

void MiddleLayer(void) {

	while(red[0][1] != 6 || green[2][1] != 5 || green[0][1] != 5 || orange[0][1] != 1 || orange[2][1] != 1 || blue[2][1] != 4 || blue[0][1] != 4 || red[2][1] != 6)
	{
		//GREEN RED edge
		//red facing, top layer (close to yellow)
		if(red[1][0] == 6 && yellow[1][2] == 5)
		{
			LeftBackward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(green[1][0] == 6 && yellow[0][1] == 5)
		{
			LeftBackward();
			LeftBackward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(orange[1][2] == 6 && yellow[1][0] == 5)
		{
			LeftForward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(blue[1][0] == 6 && yellow[2][1] == 5)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		//------------------------------------------------------------
		//green facing, top layer (close to yellow)
		if(red[1][0] == 5 && yellow[1][2] == 6)
		{
			LeftForward();
			LeftForward();

			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		if(green[1][0] == 5 && yellow[0][1] == 6)
		{
			LeftForward();

			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		if(orange[1][2] == 5 && yellow[1][0] == 6)
		{
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		if(blue[1][0] == 5 && yellow[2][1] == 6)
		{
			LeftBackward();

			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		//--------------------------------------------------------------
		//Middle layer corrent orientation of two colors
		if(green[0][1] == 6 && orange[0][1] == 5)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();

			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		if(orange[2][1] == 6 && blue[2][1] == 5)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			LeftBackward();

			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			TopRight();
			LeftBackward();
			TopLeft();
		}
		if(blue[0][1] == 6 && red[2][1] == 5)
		{
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		//--------------------------------------------------------------
		//Middle layer incorrect orientation of two colors
		if(red[0][1] == 5 && green[2][1] == 6)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftForward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(green[0][1] == 5 && orange[0][1] == 6)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(orange[2][1] == 5 && blue[2][1] == 6)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		if(blue[0][1] == 5 && red[2][1] == 6)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			LeftBackward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
		}
		//--------------------------------------------------------------
		//GREEN ORANGE edge
		//green facing, top layer (close to yellow)
		if(green[1][0] == 5 && yellow[0][1] == 1)
		{
			LeftBackward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(orange[1][2] == 5 && yellow[1][0] == 1)
		{
			LeftBackward();
			LeftBackward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(blue[1][0] == 5 && yellow[2][1] == 1)
		{
			LeftForward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(red[1][0] == 5 && yellow[1][2] == 1)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		//------------------------------------------------------------
		//orange facing top layer(close to yellow)
		if(green[1][0] == 1 && yellow[0][1] == 5)
		{
			LeftForward();
			LeftForward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		if(orange[1][2] == 1 && yellow[1][0] == 5)
		{
			LeftForward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		if(blue[1][0] == 1 && yellow[2][1] == 5)
		{
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		if(red[1][0] == 1 && yellow[1][2] == 5)
		{
			LeftBackward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		//-----------------------------------------------------------
		//Middle layer correct orientation of two colors
		if(orange[2][1] == 5 && blue[2][1] == 1)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		if(red[2][1] == 1 && blue[0][1] == 5)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			LeftBackward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		if(red[0][1] == 5 && green[2][1] == 1)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftForward();

			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			BackLeft();
			LeftBackward();
			BackRight();
		}
		//-------------------------------------------------------------
		//Middle layer incorrect orientation of two colors
		if(green[0][1] == 1 && orange[0][1] == 5)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftForward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(orange[2][1] == 1 && blue[2][1] == 5)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(red[2][1] == 5 && blue[0][1] == 1)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		if(red[0][1] == 1 && green[2][1] == 5)
		{
			TopLeft();
			LeftBackward();
			TopRight();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			LeftBackward();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
		}
		//--------------------------------------------------------------
		//ORANGE BLUE edge
		//orange facing, top layer (close to yellow)
		if(red[1][0] == 1 && yellow[1][2] == 4)
		{
			LeftForward();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(green[1][0] == 1 && yellow[0][1] == 4)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(orange[1][2] == 1 && yellow[1][0] == 4)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(blue[1][0] == 1 && yellow[2][1] == 4)
		{
			LeftForward();
			LeftForward();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		//----------------------------------------------------------
		//blue facing, top layer (close to yellow)
		if(red[1][0] == 4 && yellow[1][2] == 1)
		{
			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		if(green[1][0] == 4 && yellow[0][1] == 1)
		{
			LeftBackward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		if(orange[1][2] == 4 && yellow[1][0] == 1)
		{
			LeftBackward();
			LeftBackward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		if(blue[1][0] == 4 && yellow[2][1] == 1)
		{
			LeftForward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		//------------------------------------------------------------
		//Middle layer correct orientation of two colors
		if(red[2][1] == 4 && blue[0][1] == 1)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		if(green[2][1] == 4 && red[0][1] == 1)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();
			LeftBackward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		if(orange[0][1] == 4 && green[0][1] == 1)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftForward();

			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			BottomRight();
			LeftBackward();
			BottomLeft();
		}
		//------------------------------------------------------------
		//Middle layer incorrec orientation of two colors
		if(blue[2][1] == 1 && orange[2][1] == 4)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftForward();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(red[2][1] == 1 && blue[0][1] == 4)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(green[2][1] == 1 && red[0][1] == 4)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		if(orange[0][1] == 1 && green[0][1] == 4)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			LeftBackward();

			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
		}
		//------------------------------------------------------------
		// RED BLUE edge
		// red facing, top layer (close to yellow)
		if(red[1][0] == 6 && yellow[1][2] == 4)
		{
			LeftForward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		if(green[1][0] == 6 && yellow[0][1] == 4)
		{
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		if(orange[1][2] == 6 && yellow[1][0] == 4)
		{
			LeftBackward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		if(blue[1][0] == 6 && yellow[2][1] == 4)
		{
			LeftForward();
			LeftForward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		//----------------------------------------------------------
		//blue facing, top layer (close to yellow)
		if(red[1][0] == 4 && yellow[1][2] == 6)
		{
			LeftBackward();
			LeftBackward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(green[1][0] == 4 && yellow[0][1] == 6)
		{
			LeftForward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(orange[1][2] == 4 && yellow[1][0] == 6)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(blue[1][0] == 4 && yellow[2][1] == 6)
		{
			LeftBackward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		//--------------------------------------------------------------
		//Middle layer correct orientation of two colors
		if(red[0][1] == 4 && green[2][1] == 6)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();
			LeftBackward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		if(green[0][1] == 4 && orange[0][1] == 6)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			LeftBackward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		if(orange[2][1] == 4 && blue[2][1] == 6)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftForward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			FrontRight();
			LeftBackward();
			FrontLeft();
		}
		//--------------------------------------------------------------
		//Middle layer incorrect orientation of two colors
		if(red[2][1] == 4 && blue[0][1] == 6)
		{
			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftForward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(red[0][1] == 6 && green[2][1] == 4)
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			FrontLeft();
			LeftForward();
			FrontRight();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(green[0][1] == 6 && orange[0][1] == 4)
		{
			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
		if(blue[2][1] == 4 && orange[2][1] == 6)
		{
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BackRight();
			LeftForward();
			BackLeft();
			LeftBackward();
			LeftBackward();

			FrontRight();
			LeftBackward();
			FrontLeft();
			LeftForward();
			BottomLeft();
			LeftForward();
			BottomRight();
		}
	 }
}

void YellowCross(void) {

	while(yellow[1][0] != 2 || yellow[2][1] != 2 || yellow[1][2] != 2 || yellow[0][1] != 2)
	{
		//the dot
		if(yellow[1][0] != 2 && yellow[2][1] != 2 && yellow[1][2] != 2 && yellow[0][1] != 2)
		{
			BottomRight();

			LeftBackward();
			FrontRight();
			LeftForward();
			FrontLeft();

			BottomLeft();
		}
		//---------------------------------------------------------------
		//the L
		if(yellow[1][0] != 2 && yellow[2][1] != 2 && yellow[1][2] == 2 && yellow[0][1] == 2)
		{
			BackLeft();

			LeftBackward();
			BottomRight();
			LeftForward();
			BottomLeft();

			BackRight();
		}
		if(yellow[1][0] != 2 && yellow[2][1] == 2 && yellow[1][2] == 2 && yellow[0][1] != 2)
		{
			TopRight();

			LeftBackward();
			BackLeft();
			LeftForward();
			BackRight();

			TopLeft();
		}
		if(yellow[1][0] == 2 && yellow[2][1] == 2 && yellow[1][2] != 2 && yellow[0][1] != 2)
		{
			FrontRight();

			LeftBackward();
			TopRight();
			LeftForward();
			TopLeft();

			FrontLeft();
		}
		if(yellow[1][0] == 2 && yellow[2][1] != 2 && yellow[1][2] != 2 && yellow[0][1] == 2)
		{
			BottomRight();

			LeftBackward();
			FrontRight();
			LeftForward();
			FrontLeft();

			BottomLeft();
		}
		//--------------------------------------------------------------
		//the line
		if(yellow[1][0] == 2 && yellow[2][1] != 2 && yellow[1][2] == 2 && yellow[0][1] != 2)
		{
			TopRight();

			BackLeft();
			LeftBackward();
			BackRight();
			LeftForward();

			TopLeft();
		}
		if(yellow[1][0] != 2 && yellow[2][1] == 2 && yellow[1][2] != 2 && yellow[0][1] == 2)
		{
			FrontRight();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();

			FrontLeft();
		}
	}
}

void OrientYellowCorners(void) {

	//Lining up the RED GREEN corner
	if((green[0][0] == 5 && yellow[0][0] == 6 && orange[0][2] == 2) || (green[0][0] == 6 && yellow[0][0] == 2 && orange[0][2] == 5) || (green[0][0] == 2 && yellow[0][0] == 5 && orange[0][2] == 6))
	{
		LeftBackward();
	}
	if((orange[2][2] == 5 && yellow[2][0] == 6 && blue[2][0] == 2) || (orange[2][2] == 6 && yellow[2][0] == 2 && blue[2][0] == 5) || (orange[2][2] == 2 && yellow[2][0] == 5 && blue[2][0] == 6))
	{
		LeftBackward();
		LeftBackward();
	}
	if((red[2][0] == 2 && blue[0][0] == 5 && yellow[2][2] == 6) || (red[2][0] == 5 && blue[0][0] == 6 && yellow[2][2] == 2) || (red[2][0] == 6 && blue[0][0] == 2 && yellow[2][2] == 5))
	{
		LeftForward();
	}
	//orienting the corners
	if((red[0][0] == 5 && yellow[0][2] == 6 && green[2][0] == 2) || (red[0][0] == 6 && yellow[0][2] == 2 && green[2][0] == 5) || (red[0][0] == 2 && yellow[0][2] == 5 && green[2][0] == 6))
	{
		while((green[0][0] != 5 && yellow[0][0] != 5 && orange[0][2] != 5) || (green[0][0] != 1 && yellow[0][0] != 1 && orange[0][2] != 1) || (orange[2][2] != 1 && yellow[2][0] != 1 && blue[2][0] != 1) || (orange[2][2] != 4 && yellow[2][0] != 4 && blue[2][0] != 4) || (red[2][0] != 6 && blue[0][0] != 6 && yellow[2][2] != 6) || (red[2][0] != 4 && blue[0][0] != 4 && yellow[2][2] != 4))
		{
			LeftBackward();
			TopRight();
			LeftForward();
			BottomLeft();
			LeftBackward();
			TopLeft();
			LeftForward();
			BottomRight();

			if((green[0][0] == 4 || yellow[0][0] == 4 || orange[0][2] == 4) && (green[0][0] == 1 || yellow[0][0] == 1 || orange[0][2] == 1) && (orange[2][2] == 5 || yellow[2][0] == 5 || blue[2][0] == 5))
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();

				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
			}

			if((red[2][0] == 4 || yellow[2][2] == 4 || blue[0][0] == 4) && (red[2][0] == 1 || yellow[2][2] == 1 || blue[0][0] == 1) && (yellow[2][0] == 4 || orange[2][2] == 4 || blue[2][2] == 4) && (yellow[2][0] == 6 || orange[2][2] == 6 || blue[2][2] == 6))
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();

				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
			}
		}
	}
}

void FullYellowSide(void) {

	//Using the RED BLUE corner as constant point

	while(yellow[0][0] != 2 || yellow[0][2] != 2 || yellow[2][0] != 2 || yellow[2][2] != 2)
	{
		if(red[2][0] == 2 || blue[0][0] == 2)
		{
			while(yellow[2][2] != 2)
			{
				BottomRight();
				RightForward();
				BottomLeft();
				RightBackward();
			}
		}
		LeftBackward();
	}
}

void OrientFinalEdges(void) {

	while(green[0][0] != 5 || green[1][0] != 5 || green[2][0] != 5 || red[0][0] != 6 || red[1][0] != 6 || red[2][0] != 6)
	{
		//NO side completed
		if((green[0][0] != green[1][0]) && (red[0][0] != red[1][0]) && (blue[0][0] != blue[1][0]) && (orange[0][2] != orange[1][2]))
		{
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();

			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();
			TopRight();
			LeftBackward();
			TopLeft();
			LeftForward();

			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
			BottomLeft();
			LeftForward();
			BottomRight();
			LeftBackward();
		}
		//--------------------------------------------------------------
		//GREEN side completed
		//lining up green top layer (close to yellow) with green bottom layers (close to white)
		if(red[0][0] == 5 && red[1][0] == 5 && red[2][0] == 5)
		{
			LeftForward();
		}
		if(blue[0][0] == 5 && blue[1][0] == 5 && blue[2][0] == 5)
		{
			LeftForward();
			LeftForward();
		}
		if(orange[0][2] == 5 && orange[1][2] == 5 && orange[2][2] == 5)
		{
			LeftBackward();
		}
		//Finishing solve
		if(green[0][0] == 5 && green[1][0] == 5 && green[2][0] == 5)
		{
			while(red[0][0] != red[1][0])
			{
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();

				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();

				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();

				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
			}
		}
		//--------------------------------------------------------------
		//RED side completed
		//lining up red top layer (close to yellow) with red bottom layers (close to white)
		if(green[0][0] == 6 && green[1][0] == 6 && green[2][0] == 6)
		{
			LeftBackward();
		}
		if(orange[0][2] == 6 && orange[1][2] == 6 && orange[2][2] == 6)
		{
			LeftBackward();
			LeftBackward();
		}
		if(blue[0][0] == 6 && blue[1][0] == 6 && blue[2][0] == 6)
		{
			LeftForward();
		}
		//Finishing solve
		if(red[0][0] == 6 && red[1][0] == 6 && red[2][0] == 6)
		{
			while(green[0][0] != green[1][0])
			{
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();

				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();

				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();

				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
			}
		}
		//-------------------------------------------------------------
		//BLUE side completed
		if(red[0][0] == 4 && red[1][0] == 4 && red[2][0] == 4)
		{
			LeftBackward();
		}
		if(green[0][0] == 4 && green[1][0] == 4 && green[2][0] == 4)
		{
			LeftBackward();
			LeftBackward();
		}
		if(orange[0][2] == 4 && orange[1][2] == 4 && orange[2][2] == 4)
		{
			LeftForward();
		}
		//Finishing solve
		if(blue[0][0] == 4 && blue[1][0] == 4 && blue[2][0] == 4)
		{
			while(red[0][0] != red[1][0])
			{
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();

				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();

				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();
				FrontRight();
				LeftBackward();
				FrontLeft();
				LeftForward();

				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
				BackRight();
				LeftForward();
				BackLeft();
				LeftBackward();
			}
		}
		//-------------------------------------------------------------
		//ORANGE side completed
		if(blue[0][0] == 1 && blue[1][0] == 1 && blue[2][0] == 1)
		{
			LeftBackward();
		}
		if(red[0][0] == 1 && red[1][0] == 1 && red[2][0] == 1)
		{
			LeftBackward();
			LeftBackward();
		}
		if(green[0][0] == 1 && green[1][0] == 1 && green[2][0] == 1)
		{
			LeftForward();
		}
		//Finishing solve
		if(orange[0][2] == 1 && orange[1][2] == 1 && orange[2][2] == 1)
		{
			while(green[0][0] != green[1][0])
			{
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();

				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();

				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();
				BottomRight();
				LeftBackward();
				BottomLeft();
				LeftForward();

				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
				TopLeft();
				LeftForward();
				TopRight();
				LeftBackward();
			}
		}
	}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


//These functions solve the cube and find the array of moves needed for the solve
/*WhiteCross();
WhiteCorners();
MiddleLayer();
YellowCross();
OrientYellowCorners();
FullYellowSide();
OrientFinalEdges();*/

/* FrontRight    = 1
 * BackLeft      = 2
 * RightForward  = 3
 * LeftBackward  = 4
 * TopRight      = 5
 * BottomRight   = 6
 * FrontLeft     = 7
 * BackRight     = 8
 * RightBackward = 9
 * LeftForward   = 10
 * TopLeft       = 11
 * BottomLeft    = 12
 * */


for(int i = 0; i <= m; i++)
		{
			switch(Moves[i])	//switch case for all moves to be performed by motors on cube
			{
				case 1:																		//first twelve cases are for a move in the same direction as the previous move for that particular motor
					for(int i = 0; i <= 31; i++)
					{
						FrontRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 2:
					for(int i = 0; i <= 31; i++)
					{
						BackLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 3:
					for(int i = 0; i <= 31; i++)
					{
						RightForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 4:
					for(int i = 0; i <= 32; i++)
					{
						LeftBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 5:
					for(int i = 0; i <= 31; i++)
					{
						TopRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 6:
					for(int i = 0; i <= 31; i++)
					{
						BottomRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 7:
					for(int i = 0; i <= 31; i++)
					{
						FrontLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 8:
					for(int i = 0; i <= 31; i++)
					{
						BackRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 9:
					for(int i = 0; i <= 31; i++)
					{
						RightBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 10:
					for(int i = 0; i <= 31; i++)
					{
						LeftForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 11:
					for(int i = 0; i <= 31; i++)
					{
						TopLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 12:
					for(int i = 0; i <= 31; i++)
					{
						BottomLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 13:																			//second 12 cases are for a move in the opposite direction of the previous move for that particular motor (needs to turn more because of hitch observed)
					for(int i = 0; i <= 36; i++)
					{
						FrontRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 14:
					for(int i = 0; i <= 36; i++)
					{
						BackLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 15:
					for(int i = 0; i <= 36; i++)
					{
						RightForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 16:
					for(int i = 0; i <= 36; i++)
					{
						LeftBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 17:
					for(int i = 0; i <= 36; i++)
					{
						TopRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 18:
					for(int i = 0; i <= 36; i++)
					{
						BottomRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 19:
					for(int i = 0; i <= 36; i++)
					{
						FrontLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 20:
					for(int i = 0; i <= 36; i++)
					{
						BackRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 21:
					for(int i = 0; i <= 36; i++)
					{
						RightBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 22:
					for(int i = 0; i <= 36; i++)
					{
						LeftForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 23:
					for(int i = 0; i <= 36; i++)
					{
						TopLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 24:
					for(int i = 0; i <= 36; i++)
					{
						BottomLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 25:																		//last 12 cases are for the first move of the solve (After the motor are hand turned they need a small amount of extra movement for a 90 degree turn)
					for(int i = 0; i <= 34; i++)
					{
						FrontRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 26:
					for(int i = 0; i <= 34; i++)
					{
						BackLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 27:
					for(int i = 0; i <= 34; i++)
					{
						RightForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 28:
					for(int i = 0; i <= 34; i++)
					{
						LeftBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 29:
					for(int i = 0; i <= 34; i++)
					{
						TopRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 30:
					for(int i = 0; i <= 34; i++)
					{
						BottomRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 31:
					for(int i = 0; i <= 34; i++)
					{
						FrontLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 32:
					for(int i = 0; i <= 34; i++)
					{
						BackRightMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 33:
					for(int i = 0; i <= 34; i++)
					{
						RightBackwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 34:
					for(int i = 0; i <= 34; i++)
					{
						LeftForwardMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 35:
					for(int i = 0; i <= 34; i++)
					{
						TopLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				case 36:
					for(int i = 0; i <= 34; i++)
					{
						BottomLeftMotor();
					}
					GPIOA->ODR = 0x0;
					for(int i = 0; i <= 500000; i++);
					break;
				default:		//for empty spaces at the end of the Moves array
					break;
			}
		}

		GPIOB->ODR = 0x8;  //signifies that the solve has completed

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

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = LD3_Pin|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
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
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
