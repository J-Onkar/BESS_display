/*
 * app.h
 *
 *  Created on: 20-Feb-2024
 *      Author: Hetesh S T
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>
#include <string.h>
#include "nextion_wrapper.h"
#include "tim.h"
#include "can.h"
#include "iwdg.h"
#include "queue.h"

void app_init(void);
void can_init(void);
void timer_init(void);
void app_handler(void);

#endif /* APP_H_ */
