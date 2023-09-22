/*
 * Ball.cpp
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */
#include <cmath>
#include <iostream>
#include "EasyBreakout.h"
#include "Ball.h"

// Initializing ball 
Ball :: Ball (const Sound * hit_bar_sound, const Sound * hit_block_sound, const Color& color, 
				const float& playing_bar_position_y, const Vector2& speed, const int& radius) : MovingEntity(speed), 
				Circle((Vector2){(float)SCREEN_WIDTH/2, playing_bar_position_y - radius}, radius), 
				hit_bar_sound(hit_bar_sound), hit_block_sound(hit_block_sound), color(color) {
}

bool Ball :: IsHeld() const {
	return held;
}

bool Ball :: IsEnabled() const {
	return enabled;
}

void Ball :: Move() {
	auto position = get_position();
	position.x += get_speed().x;
	position.y += get_speed().y;

    if (position.x >= (GetScreenWidth() - get_radius()) || (position.x <= get_radius())) {
		auto speed = get_speed();
		set_speed( (Vector2){ speed.x * -1.0f, speed.y } );
		if (!enabled) enabled = true;       		// It is enabled when it hits walls
	}

    if (position.y >= (GetScreenHeight() - get_radius()) || (position.y <= get_radius())) {
		auto speed = get_speed();
		set_speed( (Vector2){ speed.x, speed.y * -1.0f } );
		if (!enabled) enabled = true;				// It is enabled when it hits ceiling or floor
		if (position.y <= get_radius()) {
			if (risk_rate < 2) {
				risk_rate = 0;
			} else {
				++risk_rate;
			}
		} else if (position.y >= (GetScreenHeight() - get_radius())) {
			++risk_rate;
		}
	}

	set_position(position);	
}

void Ball :: Draw() {
	DrawCircleV(get_position(), get_radius(), color);
}

bool Ball :: IsCollided(const Rectangle& rec) const {
	return CheckCollisionCircleRec(get_position(), get_radius(), rec); 
}

const int Ball :: IsCollided(Block * blocks, const int& number_of_blocks) {	
	for (int i = 0; i < number_of_blocks; ++i) {
		if (enabled && !blocks[i].is_falling() && IsCollided(blocks[i].get_rec())) {
			blocks[i].set_falling();
			enabled = false;					// It is disabled to prevent from falling other blocks nearby accidently
			++risk_rate;
			return i;
		}
	}

	return -1;
}

// Colliding with rectangle 
void Ball :: Collide(const Rectangle& rec, const Vector2& speed) {
	const auto position = get_position();
	const auto radius = get_radius();

	// Repositioning of ball when its position is located in the rectangle
    if (position.y + radius >= rec.y && position.y < rec.y + rec.height) {
		set_position((Vector2){position.x, rec.y - radius - 0.1f});
	} 
	else if (position.y > rec.y  && position.y - radius <= rec.y + rec.height) {
		set_position((Vector2){position.x, rec.y + rec.height + radius + 0.1f});
	}
	set_speed( (Vector2){ speed.x, speed.y * -1.0f } );
}

// Colliding with playing bar 
void Ball :: Collide(const Rectangle& rec, const int& level_num) {
	const auto speed =  get_speed();

	if (!held && IsKeyDown(KEY_SPACE)) {
		Collide(rec, (Vector2){ speed.x * -1.0f, speed.y } );
	} else {
		Collide(rec, (Vector2){ RandomSpeedOnX(speed, level_num), speed.y } );	
	}

	enabled = true; 										// It is enabled again when it hits playing bar
	risk_rate = 0;					
}

const float Ball :: RandomSpeedOnX(const Vector2& speed, const int& level_num) const {
	const float maximum_speed_on_x = fabs(speed.y) + (level_num * kSpeedIncrementRate);	
	const float minimum_speed_on_x = kInitalSpeedOnX + (level_num * kSpeedIncrementRate);
	const float medium_speed_on_x = maximum_speed_on_x - (maximum_speed_on_x - minimum_speed_on_x) / 2;

	// std::cout << "maximum: "  << maximum_speed_on_x << ", minimum: " << minimum_speed_on_x << ", medium: " <<  medium_speed_on_x << std::endl; 

	int direction = 0;
	if (fabs(speed.x) > medium_speed_on_x) direction = -1;
	else direction = 1;

	const float random_speed = (speed.x < 0) ? -1 * direction * RandomRateOfSpeedOnX() : direction * RandomRateOfSpeedOnX();	
	const float speed_x = speed.x + random_speed;

	if (fabs(speed_x) > maximum_speed_on_x) {
		return (speed.x < 0) ? -1 * maximum_speed_on_x : maximum_speed_on_x;
	} else if (fabs(speed_x) < minimum_speed_on_x) {
		return (speed.x < 0) ? -1 * minimum_speed_on_x : minimum_speed_on_x;
	} else {	
		return speed_x;
	} 
}