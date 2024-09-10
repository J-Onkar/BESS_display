/*
 * app.c
 *
 *  Created on: 20-Feb-2024
 *      Author: Hetesh S T
 */

#include "app.h"

#define MSG_QUERY_90 0x18900140U
#define MSG_QUERY_91 0x18910140U
#define MSG_QUERY_92 0x18920140U
#define MSG_QUERY_93 0x18930140U

#define MSG_RSP_90 0x18904001U
#define MSG_RSP_91 0x18914001U
#define MSG_RSP_92 0x18924001U
#define MSG_RSP_93 0x18934001U

#define UDAN_14 0x00001400U
#define UDAN_13 0x00001300U

#define INVALID_ID 0xFFFFFFFFU
#define QUEUE_LEN 12U

#define CUTOFF_VOLT 480

typedef union {
	struct {
		uint16_t batt_volt;
		uint16_t batt_curr;
		uint16_t batt_soc;
		uint16_t real_soc;

	} __attribute__((packed));
	uint8_t gen_data[8];
} udan_14_t;

typedef union {
	struct {
		uint8_t run_state : 4;
		uint8_t conn_status: 4;
		uint8_t pre_chg_status: 2;
		uint8_t self_check_status: 2;
		uint8_t balance_status: 1;
		uint8_t heating_status: 1;
		uint8_t refrige_status: 1;
		uint8_t hv_looplock_status: 1;
		uint16_t pos_ins_resistance;
		uint16_t neg_ins_resistance;
		uint8_t bms_alarm_level;
		uint8_t ready: 2;
		uint8_t bms_mode: 1;
		uint8_t batt_chg_state: 2;
		uint8_t reserved : 3;

	} __attribute__((packed));
	uint8_t gen_data[8];
} udan_13_t;



static uint32_t curr_id;
static queue_t rx_queue;
static q_member_t queue_arr[QUEUE_LEN];
static CAN_TxHeaderTypeDef tx_hdr;
static uint32_t tim1, tim2, tim3, tim4;

udan_14_t msg_14;
udan_13_t msg_13;

static inline uint16_t HTONS(uint16_t x) {
	return ((x << 8) | ((x >> 8) & 0xFF));
}

static void send_can_message() {

	tx_hdr.ExtId = curr_id;
	switch (curr_id) {
	case MSG_QUERY_90: {
		curr_id = MSG_QUERY_91;
		break;
	}

	case MSG_QUERY_91: {
		curr_id = MSG_QUERY_92;
		break;
	}

	case MSG_QUERY_92: {
		curr_id = MSG_QUERY_93;
		break;
	}

	case MSG_QUERY_93: {
		curr_id = INVALID_ID;
		break;
	}
	}

	uint32_t mailbox;
	uint8_t data[8] = { 0 };

	if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0) {
		if (HAL_CAN_AddTxMessage(&hcan, &tx_hdr, data, &mailbox) != HAL_OK) {
			Error_Handler();
		}
	}

}

static void tx_hdr_init(void) {
	tx_hdr.DLC = 8;
	tx_hdr.ExtId = INVALID_ID;
	tx_hdr.IDE = CAN_ID_EXT;
	tx_hdr.RTR = CAN_RTR_DATA;
	tx_hdr.TransmitGlobalTime = DISABLE;
}

static void update_udan_14(uint8_t data[]) {

	(void) memcpy(msg_14.gen_data, data, 8);

	update_batt_volt_label(HTONS(msg_14.batt_volt));
	update_batt_curr_label((HTONS(msg_14.batt_curr))-10000);
	update_batt_soc_label(HTONS(msg_14.batt_soc));
	update_soc_bar_label((HTONS(msg_14.batt_soc))/10);
}

static void update_udan_13(uint8_t data[]) {

	(void) memcpy(msg_13.gen_data, data, 8);

	if(msg_13.batt_chg_state == 0)
	{update_batt_status_label("Idle");}

	else if (msg_13.batt_chg_state == 1)
		{	update_batt_status_label("Charging");}
	else if (msg_13.batt_chg_state == 2)
		{	update_batt_status_label("Discharging");}

}


static void read_can_message(void) {

	q_member_t *q_member = peek(&rx_queue);

	if (q_member != NULL) {

		switch (q_member->can_id) {

		case UDAN_14: {
			update_udan_14(q_member->data);
			tim1 = HAL_GetTick();
			break;
		}

		case UDAN_13: {
			update_udan_13(q_member->data);
			tim2 = HAL_GetTick();
			break;
		}

		}
		dequeue(&rx_queue);

	}

}

static void timer_check(void) {

	if ((HAL_GetTick() - tim1) > 5000U) {
		reset_page1_display();
		tim1 = HAL_GetTick();
	}

	else if ((HAL_GetTick() - tim2) > 5000U) {
		reset_page2_display();
		tim2 = HAL_GetTick();
	}

	else if ((HAL_GetTick() - tim3) > 5000U) {

		reset_page3_display();
		tim3 = HAL_GetTick();

	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM1) {
		curr_id = MSG_QUERY_90;
		send_can_message();

	}

	else if (htim->Instance == TIM2) {
		update_comm_status_label("Loss of Comm");
		reset_display();
		if (htim3.State != HAL_TIM_STATE_READY) {
			HAL_GPIO_WritePin(Buzzer_pin_GPIO_Port, Buzzer_pin_Pin,
					GPIO_PIN_RESET);
			HAL_TIM_Base_Stop_IT(&htim3);
		}
	}

	else {
		if (htim->Instance == TIM3) {
			HAL_GPIO_TogglePin(Buzzer_pin_GPIO_Port, Buzzer_pin_Pin);
		}
	}

}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) {
	if (curr_id != INVALID_ID) {
		send_can_message();
	}
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan) {
	if (curr_id != INVALID_ID) {
		send_can_message();
	}
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan) {
	if (curr_id != INVALID_ID) {
		send_can_message();
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

	CAN_RxHeaderTypeDef rx_hdr;
	uint8_t rx_data[8] = { 0 };

	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_hdr, rx_data) != HAL_OK) {
		Error_Handler();
	}

	enqueue(&rx_queue, rx_hdr.ExtId, rx_data);
}

void app_init(void) {
	curr_id = INVALID_ID;
	tx_hdr_init();
	queue_init(&rx_queue, queue_arr, QUEUE_LEN);
	nextion_disp_init();
	reset_display();
	tim1 = HAL_GetTick();
	tim2 = HAL_GetTick();
	tim3 = HAL_GetTick();
	tim4 = HAL_GetTick();
	update_comm_status_label("");
}

void can_init(void) {

	CAN_FilterTypeDef filter1;

	filter1.FilterActivation = CAN_FILTER_ENABLE;
	filter1.FilterBank = 0;
	filter1.FilterFIFOAssignment = CAN_RX_FIFO0;
	filter1.FilterMode = CAN_FILTERMODE_IDMASK;
	filter1.FilterScale = CAN_FILTERSCALE_32BIT;
	filter1.FilterIdHigh = 0x0000;
	filter1.FilterIdLow = 0x8000;
	filter1.FilterMaskIdHigh = 0x0000;
	filter1.FilterMaskIdLow = 0x8000;


	if (HAL_CAN_ConfigFilter(&hcan, &filter1) != HAL_OK) {
		Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING)
			!= HAL_OK) {
		Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_TX_MAILBOX_EMPTY)
			!= HAL_OK) {
		Error_Handler();
	}

	if (HAL_CAN_Start(&hcan) != HAL_OK) {
		Error_Handler();
	}

}

void timer_init(void) {

	if (HAL_TIM_Base_Start_IT(&htim1)) {
		Error_Handler();
	}

	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

	if (HAL_TIM_Base_Start_IT(&htim2)) {
		Error_Handler();
	}

}

void app_handler(void) {

	while (1) {
		timer_check();

		if (!is_empty(&rx_queue)) {
			read_can_message();
			__HAL_TIM_SET_COUNTER(&htim2, 0);
			update_comm_status_label("");
		}
		HAL_IWDG_Refresh(&hiwdg);
	}

}
