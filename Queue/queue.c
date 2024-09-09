/*
 * can_queue.c
 *
 *  Created on: 05-Oct-2023
 *      Author: Hetesh S T
 */

#include "queue.h"

void queue_init(queue_t *q_instance, q_member_t queue_arr[], uint8_t max_len) {
	q_instance->front_idx = 0;
	q_instance->rear_idx = 0;
	q_instance->q_len = 0;
	q_instance->q_max_len = max_len;
	q_instance->q_member_ptr = queue_arr;
}

bool is_empty(queue_t *q_instance) {
	return (q_instance->q_len == 0u);

}

bool is_full(queue_t *q_instance) {
	return (q_instance->q_len == q_instance->q_max_len);
}

void enqueue(queue_t *q_instance, uint32_t rx_can_id, uint8_t rx_data[]) {

	if (is_full(q_instance)) {
		return;
	}

	q_member_t *temp_member = q_instance->q_member_ptr + q_instance->rear_idx;
	temp_member->can_id = rx_can_id;
	(void) memcpy(temp_member->data, rx_data, 8);

	q_instance->rear_idx = (q_instance->rear_idx + 1) % q_instance->q_max_len;
	q_instance->q_len++;

}

void dequeue(queue_t *q_instance) {
	if (is_empty(q_instance)) {
		return;
	}

	(void) memset((q_instance->q_member_ptr + q_instance->front_idx), 0,
			sizeof(q_member_t));
	q_instance->front_idx = (q_instance->front_idx + 1) % q_instance->q_max_len;
	q_instance->q_len--;
}

q_member_t* peek(queue_t *q_instance) {
	if (is_empty(q_instance)) {
		return NULL;
	}

	return (q_instance->q_member_ptr + q_instance->front_idx);
}

