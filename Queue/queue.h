/*
 * queue.h
 *
 *  Created on: Feb 21, 2024
 *      Author: Hetesh S T
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/*
 * can_queue.h
 *
 *  Created on: 05-Oct-2023
 *      Author: Hetesh H T
 */

#ifndef CAN_QUEUE_H_
#define CAN_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
	uint32_t can_id;
	uint8_t data[8];
} q_member_t;

typedef struct {
	uint8_t front_idx;
	uint8_t rear_idx;
	uint8_t q_len;
	uint8_t q_max_len;
	q_member_t *q_member_ptr;
} queue_t;

void queue_init(queue_t *q_instance, q_member_t queue_arr[], uint8_t max_len);
bool is_empty(queue_t *q_instance);
bool is_full(queue_t *q_instance);
void enqueue(queue_t *q_instance, uint32_t rx_can_id, uint8_t rx_data[]);
void dequeue(queue_t *q_instance);
q_member_t* peek(queue_t *q_instance);

#endif /* CAN_QUEUE_H_ */



#endif /* QUEUE_H_ */
