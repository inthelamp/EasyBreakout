/*
 * Ball.cpp
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */
#include <cstdlib>
#include "EasyBreakout.h"
#include "Ball.h"

// Initializing ball 
Ball :: Ball (const Color& color, const float& playing_bar_position_y, const Vector2& speed, const int& radius)
			: MovingEntity(speed), Circle({(float)SCREEN_WIDTH/2, playing_bar_position_y - radius}, radius) {
		this->color = color;
}

bool Ball :: IsHeld() const {
	return held;
}

bool Ball :: IsEnabled() const {
	return enabled;
}

void Ball :: Move() {
	auto position = this->get_position();
	position.x += this->get_speed().x;
	position.y += this->get_speed().y;

    if (position.x >= (GetScreenWidth() - this->get_radius()) || (position.x <= this->get_radius())) {
		auto speed = this->get_speed();
		this->set_speed( { speed.x * -1.0f, speed.y } );
		if (!this->enabled) this->enabled = true;       		// It is enabled when it hits walls
	}

    if (position.y >= (GetScreenHeight() - this->get_radius()) || (position.y <= this->get_radius())) {
		auto speed = this->get_speed();
		this->set_speed( { speed.x, speed.y * -1.0f } );
		if (!this->enabled) this->enabled = true;				// It is enabled when it hits ceiling or floor
	}

	this->set_position(position);	
}

void Ball :: Draw() {
	DrawCircleV(this->get_position(), this->get_radius(), this->color);
}

bool Ball :: IsCollided(const Rectangle& rec) const {
	return CheckCollisionCircleRec(this->get_position(), this->get_radius(), rec); 
}

const int Ball :: IsCollided(Block * blocks, const int& number_of_blocks) {	
	for (int i = 0; i < number_of_blocks; ++i) {
		if (this->enabled && !blocks[i].is_falling() && IsCollided(blocks[i].get_rec())) {
			this->enabled = false;								// It is disabled to prevent from falling other blocks nearby accidently
			blocks[i].set_falling();
			return i;
		}
	}

	return -1;
}

void Ball :: Collide(const Rectangle& rec, const Vector2& speed) {
	const auto position = this->get_position();
	const auto radius = this->get_radius();

	// Repositioning of ball when its position is located in the rectangle
    if (position.y + radius >= rec.y && position.y < rec.y + rec.height) {
		this->set_position({position.x, rec.y - radius - 0.1f});
	} 
	else if (position.y > rec.y  && position.y - radius <= rec.y + rec.height) {
		this->set_position({position.x, rec.y + rec.height + radius + 0.1f});
	}
	this->set_speed( { speed.x, speed.y * -1.0f } );
}

// Colliding with playing bar 
void Ball :: Collide(const Rectangle& rec, const int& level_num) {
	const auto speed =  this->get_speed();

	if (!held && IsKeyDown(KEY_SPACE)) {
		this->Collide(rec, { speed.x * -1.0f, speed.y } );
	} else {
		this->Collide(rec, { RandomSpeedOnX(speed.x, level_num), speed.y } );	
	}

	this->enabled = true; 										// It is enabled again when it hits playing bar
}

const float Ball :: RandomSpeedOnX(const float& speed_x, const int& level_num) const {
	int direction = 0;

	if (abs(speed_x) > (kInitalSpeedOnX + level_num * kSpeedIncrementRate) * 2) direction = -1;
	else if(abs(speed_x) < kInitalSpeedOnX + level_num * kSpeedIncrementRate) direction = 1; 

	return speed_x + (direction * RandomRateOfSpeedOnX());
}