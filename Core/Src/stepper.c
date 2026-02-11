/*
 * stepper.c
 *
 *  Created on: 2026. 2. 4.
 *      Author: kimsuyeon
 */

#include "stepper.h"

static const uint8_t HALF_STEP_SEQ[8][4] =
		{
				{1, 0, 0, 0},		// step1
				{1, 1, 0, 0},		// step2
				{0, 1, 0, 0},		// step3
				{0, 1, 1, 0},		// step4
				{0, 0, 1, 0},		// step5
				{0, 0, 1, 1},		// step6
				{0, 0, 0, 1},		// step7
				{1, 0, 0, 1},		// step8
		};

void stepMotor(uint8_t step)
{
	HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, HALF_STEP_SEQ[step][0]);
	HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, HALF_STEP_SEQ[step][1]);
	HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, HALF_STEP_SEQ[step][2]);
	HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, HALF_STEP_SEQ[step][3]);
}

void rotateSteps(uint16_t steps, uint8_t direction)
{
	for(uint16_t i=0; i<steps; i++)
	{
		// 회전방향에 따른 스텝 설정
		uint8_t step;
		if (direction == DIR_CW)
		{
			step = i % 8;
		}
		else
		{
		  step = 7 - (i % 8);
		}
		stepMotor(step);

		HAL_Delay(1);
	}
}
void rotateDegrees(uint16_t degrees, uint8_t direction)
{
	// 각도에 해당하는 스텝수를 계
	uint16_t steps = (uint16_t)((uint32_t)(degrees * STEPS_PER_REVOLATION) / 360);
	rotateSteps(steps, direction); // 지정된 방향으로 회
}
