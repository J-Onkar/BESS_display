/*
 * nextion_wrapper.c
 *
 *  Created on: 08-Jan-2024
 *      Author: Hetesh S T
 */

#include "usart.h"
#include "nextion_wrapper.h"

extern UART_HandleTypeDef huart1;

static Nextion nextion_instance;

static NexComp batt_volt_label;
static NexComp batt_curr_label;
static NexComp batt_soc_label;
static NexComp soc_bar_label;
static NexComp batt_status_label;


static NexComp min_cellv_label;
static NexComp min_cellv_id_label;

static NexComp max_cellt_label;
static NexComp max_cellt_id_label;
static NexComp min_cellt_label;
static NexComp min_cellt_id_label;

static NexComp comm_status_label;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	NextionUpdate(huart, &nextion_instance);
}

void nextion_disp_init(void) {
	NextionInit(&nextion_instance, &huart1);

	NextionAddComp(&nextion_instance, &batt_volt_label, "home.batt_volt", 1, 15,
	NULL, NULL);
	NextionAddComp(&nextion_instance, &batt_curr_label, "home.batt_curr", 1, 17, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &batt_soc_label, "home.batt_soc", 1, 18, NULL, NULL);

	NextionAddComp(&nextion_instance, &soc_bar_label, "home.soc_bar", 1, 4, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &batt_status_label, "home.batt_status", 1, 19, NULL,
	NULL);



	NextionAddComp(&nextion_instance, &comm_status_label, "home.comm_status", 3, 4, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &min_cellv_label, "page1.min_cellv", 5, 9, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &min_cellv_id_label, "page1.min_cellv_id", 5, 10, NULL,
	NULL);

	NextionAddComp(&nextion_instance, &max_cellt_label, "page2.max_cellt", 6, 7, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &max_cellt_id_label, "page2.max_cellt_id", 6, 8, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &min_cellt_label, "page2.min_cellt", 6, 9, NULL,
	NULL);
	NextionAddComp(&nextion_instance, &min_cellt_id_label, "page2.min_cellt_id", 6, 10, NULL,
	NULL);

}

void update_batt_volt_label(int val){
	NextionSetVal(&nextion_instance, &batt_volt_label, val);
}

void update_batt_curr_label(int val){
	NextionSetVal(&nextion_instance, &batt_curr_label, val);
}

void update_batt_soc_label(int val){
	NextionSetVal(&nextion_instance, &batt_soc_label, val);
}

void update_soc_bar_label(int val) {
	NextionSetVal(&nextion_instance, &soc_bar_label, val);
}

void update_comm_status_label(char *str) {
	NextionSetText(&nextion_instance, &comm_status_label, str);
}
void update_batt_status_label(char *str) {
	NextionSetText(&nextion_instance, &batt_status_label, str);
}





void update_min_cellv_label(int val) {
	NextionSetVal(&nextion_instance, &min_cellv_label, val);
}

void update_min_cellv_id_label(int val) {
	NextionSetVal(&nextion_instance, &min_cellv_id_label, val);
}


void update_max_cellt_label(int val) {
	NextionSetVal(&nextion_instance, &max_cellt_label, val);
}

void update_max_cellt_id_label(int val) {
	NextionSetVal(&nextion_instance, &max_cellt_id_label, val);
}

void update_min_cellt_label(int val) {
	NextionSetVal(&nextion_instance, &min_cellt_label, val);
}

void update_min_cellt_id_label(int val) {
	NextionSetVal(&nextion_instance, &min_cellt_id_label, val);
}



void reset_display(void) {
	update_batt_volt_label(0);
	update_batt_curr_label(0);
	update_batt_soc_label(0);
	update_soc_bar_label(0);
	update_batt_status_label("");

	update_min_cellv_label(0);
	update_min_cellv_id_label(0);
	update_max_cellt_label(0);
	update_max_cellt_id_label(0);
	update_min_cellt_label(0);
	update_min_cellt_id_label(0);
}

void reset_page1_display(void){
	update_batt_volt_label(0);
	update_batt_curr_label(0);
	update_batt_soc_label(0);
	update_soc_bar_label(0);
}

void reset_page2_display(void){

	update_min_cellv_label(0);
	update_min_cellv_id_label(0);
}


void reset_page3_display(void){
	update_max_cellt_label(0);
	update_max_cellt_id_label(0);
	update_min_cellt_label(0);
	update_min_cellt_id_label(0);
}
