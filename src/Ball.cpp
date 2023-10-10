/*
 * Ball.cpp
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#include "Ball.h"

// Initializing ball
Ball::Ball(const Sound &hit_bar_sound, const Sound &hit_block_sound, const Color &color, float pos_y, const Vector2 &speed) : MovingEntity(speed), GraphicsEntity<Circle>(circle(), position(pos_y)), hit_bar_sound(hit_bar_sound), hit_block_sound(hit_block_sound), color(color)
{
	auto shape = get_shape();
	set_shape(Scale(std::move(shape)));
}

Circle Ball::Scale(Circle &&circle)
{
	circle.set_radius(circle.get_radius() * WindowManager::scale().x);
	return std::move(circle);
}

void Ball::Move()
{
	auto position = get_position();
	position.x += get_speed().x;
	position.y += get_speed().y;

	if (position.x >= (WindowManager::window_size().width - get_shape().get_radius()) || (position.x <= get_shape().get_radius()))
	{
		auto speed = get_speed();
		set_speed((Vector2){speed.x * -1.0f, speed.y});
		if (!enabled)
			enabled = true; // It is enabled when it hits walls
	}

	if (position.y >= (WindowManager::window_size().height - get_shape().get_radius()) || (position.y <= get_shape().get_radius()))
	{
		auto speed = get_speed();
		set_speed((Vector2){speed.x, speed.y * -1.0f});

		if (!enabled)
			enabled = true; // It is enabled when it hits ceiling or floor
		if (position.y <= get_shape().get_radius())
		{
			if (risk_rate < 2)
			{
				risk_rate = 0;
			}
			else
			{
				++risk_rate;
			}
		}
		else if (position.y >= (WindowManager::window_size().height - get_shape().get_radius()))
		{
			++risk_rate;
		}
	}

	set_position(position);
}

void Ball::Draw()
{
	DrawCircleV(get_position(), get_shape().get_radius(), color);
}

bool Ball::IsCollided(const Rectangle &rec)
{
	return CheckCollisionCircleRec(get_position(), get_shape().get_radius(), rec);
}

int Ball::CollidedBlock(Block *blocks, int number_of_blocks)
{
	for (int i = 0; i < number_of_blocks; ++i)
	{
		if (enabled && !blocks[i].is_falling() && IsCollided(blocks[i].get_shape()))
		{
			blocks[i].set_falling();
			enabled = false; // It is disabled to prevent from having other blocks fallen nearby accidently
			++risk_rate;
			return i;
		}
	}

	return -1;
}

// Colliding with rectangle
void Ball::Collide(const Rectangle &rec, const Vector2 &speed)
{
	const auto position = get_position();
	const auto radius = get_shape().get_radius();

	// Repositioning of ball when its position is located in the rectangle
	if (position.y + radius >= rec.y && position.y < rec.y + rec.height)
	{
		set_position((Vector2){position.x, rec.y - radius - 0.1f});
	}
	else if (position.y > rec.y && position.y - radius <= rec.y + rec.height)
	{
		set_position((Vector2){position.x, rec.y + rec.height + radius + 0.1f});
	}
	set_speed((Vector2){speed.x, speed.y * -1.0f});
}

// Colliding with playing bar
void Ball::Collide(const HUD &hud, const Rectangle &rec, int level_num)
{
	const auto speed = get_speed();

	if (!held && hud.IsControlPointTouched(hud.hit_back_control())) // Hit back in the same direction
	{
		Collide(rec, (Vector2){speed.x * -1.0f, speed.y});
	}
	else
	{
		Collide(rec, (Vector2){RandomSpeedX(speed, level_num), speed.y});
	}

	enabled = true; // It is enabled again when it hits playing bar
	risk_rate = 0;
}

void Ball::Collide(const Rectangle &rec, int level_num)
{
	const auto speed = get_speed();

	if (!held && IsKeyDown(KEY_SPACE)) // Hit back in the same direction
	{
		Collide(rec, (Vector2){speed.x * -1.0f, speed.y});
	}
	else
	{
		Collide(rec, (Vector2){RandomSpeedX(speed, level_num), speed.y});
	}

	enabled = true; // It is enabled again when it hits playing bar
	risk_rate = 0;
}

float Ball::RandomSpeedX(const Vector2 &speed, int level_num)
{
	const float maximum_speed_on_x = fabs(speed.y) + (level_num * kSpeedIncrementRate);
	const float minimum_speed_on_x = ball_inital_speed_x() + (level_num * kSpeedIncrementRate);
	const float medium_speed_on_x = maximum_speed_on_x - (maximum_speed_on_x - minimum_speed_on_x) / 2;

	// std::cout << "maximum: "  << maximum_speed_on_x << ", minimum: " << minimum_speed_on_x << ", medium: " <<  medium_speed_on_x << std::endl;

	int direction = 0;
	if (fabs(speed.x) > medium_speed_on_x)
		direction = -1;
	else
		direction = 1;

	const float random_speed = (speed.x < 0) ? -1 * direction * random_speed_rate_x() : direction * random_speed_rate_x();
	const float speed_x = speed.x + random_speed;

	if (fabs(speed_x) > maximum_speed_on_x)
	{
		return (speed.x < 0) ? -1 * maximum_speed_on_x : maximum_speed_on_x;
	}
	else if (fabs(speed_x) < minimum_speed_on_x)
	{
		return (speed.x < 0) ? -1 * minimum_speed_on_x : minimum_speed_on_x;
	}
	else
	{
		return speed_x;
	}
}