#include <Arduino.h>
#include "positions.h"
#include "odometry.h"

struct goto_fields
{
	struct odometry_position position;
	uint8_t speed;
	uint8_t direction;
	uint8_t	(*callback)(uint32_t start_time);
	uint8_t (*callback_end)(uint32_t start_time);
};

const struct goto_fields tactic_one[] = {
	{{100, 100}, 50, FORWARD, NULL, NULL}
};
