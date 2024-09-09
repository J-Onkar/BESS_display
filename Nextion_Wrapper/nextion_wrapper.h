/*
 * nextion_wrapper.h
 *
 *  Created on: 08-Jan-2024
 *      Author: Hetesh S T
 */

#ifndef NEXTION_WRAPPER_H_
#define NEXTION_WRAPPER_H_

#include "Nextion.h"

void nextion_disp_init(void);
void update_batt_volt_label(int val);
void update_batt_curr_label(int val);
void update_batt_soc_label(int val);
void update_comm_status_label(char *str);
void update_max_cellv_label(int val);
void update_max_cellv_id_label(int val);
void update_min_cellv_label(int val);
void update_min_cellv_id_label(int val);
void update_max_cellt_label(int val);
void update_max_cellt_id_label(int val);
void update_min_cellt_label(int val);
void update_min_cellt_id_label(int val);
void reset_display(void);
void reset_page1_display(void);
void reset_page2_display(void);
void reset_page3_display(void);


#endif /* NEXTION_WRAPPER_H_ */
