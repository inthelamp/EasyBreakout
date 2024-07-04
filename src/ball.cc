/*
 * ball.cc
 *
 *  Created on: Aug. 22, 2023
 *      Author: Dong Won Kim
 */

#include "ball.h"

// Initializing ball
Ball::Ball(const Sound &hit_bar_sound, const Sound &hit_block_sound, const Color &color, float pos_y, const Vector2 &speed) : MovingEntity(speed), GraphicsEntity<Circle>(circle(), position(pos_y)), hit_bar_sound_(hit_bar_sound), hit_block_sound_(hit_block_sound), color_(color)
{
	auto shape = GraphicsEntity::shape();
	GraphicsEntity::shape(Scale(std::move(shape)));
}

Circle Ball::Scale(Circle &&circle)
{
	circle.radius(circle.radius() * Screen::scale().x);
	return std::move(circle);
}

void Ball::Move()
{
	auto position = GraphicsEntity::position();
	position.x += speed().x;
	position.y += speed().y;

	if (position.x >= (Screen::window_size().width - shape().radius()) || (position.x <= shape().radius()))
	{
		auto speed = MovingEntity::speed();
		MovingEntity::speed({speed.x * -1.0f, speed.y});
		if (!enabled_)
			enabled_ = true; // It is enabled when it hits walls
	}

	if (position.y >= (Screen::window_size().height - shape().radius()) || (position.y <= shape().radius()))
	{
		auto speed = MovingEntity::speed();
		MovingEntity::speed({speed.x, speed.y * -1.0f});

		if (!enabled_)
			enabled_ = true; // It is enabled when it hits ceiling or floor
		if (position.y <= shape().radius())
		{
			if (risk_rate_ < 2)
			{
				risk_rate_ = 0;
			}
			else
			{
				++risk_rate_;
			}
		}
		else if (position.y >= (Screen::window_size().height - shape().radius()))
		{
			++risk_rate_;
		}
	}

	GraphicsEntity::position(position);
}

void Ball::Draw()
{
	DrawCircleV(GraphicsEntity::position(), shape().radius(), color_);
}

bool Ball::IsCollided(const Rectangle &rec)
{
	return CheckCollisionCircleRec(GraphicsEntity::position(), shape().radius(), rec);
}

int Ball::block_collided_with(Block *blocks, int number_of_blocks)
{
	for (int i = 0; i < number_of_blocks; ++i)
	{
		if (enabled_ && !blocks[i].falling() && IsCollided(blocks[i].shape()))
		{
			blocks[i].falling(true);
			enabled_ = false; // It is disabled to prevent from having other blocks fallen nearby accidently
			++risk_rate_;
			return i;
		}
	}

	return -1;
}

// Colliding with rectangle
void Ball::Collide(const Rectangle &rec, const Vector2 &speed)
{
	const auto position = GraphicsEntity::position();
	const auto radius = shape().radius();

	// Repositioning of ball when its position is located in the rectangle
	if (position.y + radius >= rec.y && position.y < rec.y + rec.height)
	{
		GraphicsEntity::position({position.x, rec.y - radius - 0.1f});
	}
	else if (position.y > rec.y && position.y - radius <= rec.y + rec.height)
	{
		GraphicsEntity::position({position.x, rec.y + rec.height + radius + 0.1f});
	}
	MovingEntity::speed({speed.x, speed.y * -1.0f});
}

// Colliding with playing bar
void Ball::Collide(HUD *hud, const Rectangle &rec, int level_num)
{
	const auto speed = MovingEntity::speed();

	auto hbcp = hud->hit_back_control();
	if (!held_ && hud->IsControlPointTouched(hbcp)) // Hit back in the same direction
	{
		// Tutorial condition is met
		if (hbcp->condition_started())
		{
			hbcp->condition_achieved(true);
		}
		Collide(rec, {speed.x * -1.0f, speed.y});
	}
	else
	{
		Collide(rec, {random_speed_x(speed, level_num), speed.y});
	}

	enabled_ = true; // It is enabled again when it hits playing bar
	risk_rate_ = 0;
}

void Ball::Collide(const Rectangle &rec, int level_num)
{
	const auto speed = MovingEntity::speed();

	if (!held_ && IsKeyDown(KEY_TAB)) // Hit back in the same direction
	{
		// Tutorial condition is met
		if (condition_started())
		{
			condition_achieved(true);
		}
		Collide(rec, {speed.x * -1.0f, speed.y});
	}
	else
	{
		Collide(rec, {random_speed_x(speed, level_num), speed.y});
	}

	enabled_ = true; // It is enabled again when it hits playing bar
	risk_rate_ = 0;
}

float Ball::random_speed_x(const Vector2 &speed, int level_num)
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

void Ball::PlayHitBarSound()
{
	PlaySound(hit_bar_sound_);
}

void Ball::PlayHitBlockSound()
{
	PlaySound(hit_block_sound_);
}