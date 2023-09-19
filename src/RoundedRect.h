/*
 * RoundedRect.h
 *
 *  Created on: Aug. 27, 2023
 *      Author: Dong Won Kim
 */

#ifndef ROUNDEDRECT_H_
#define ROUNDEDRECT_H_

#include <utility>
#include "raylib.h"
#include "GraphicsEntity.h"

class RoundedRect : public GraphicsEntity {
private:
	Rectangle rec;
    float roundness = 0.2f;
    float segments = 0.0f;

public:
	RoundedRect(const float& width, const float& height, const float& roundness, const float& segments) {
    	this->rec.width = width;
    	this->rec.height = height;
    	this->roundness = roundness;
    	this->segments = segments;
	}

    RoundedRect(const Vector2& position, const float& width, const float& height, const float& roundness, const float& segments){
    	this->rec.x = position.x;
    	this->rec.y = position.y;
    	this->rec.width = width;
    	this->rec.height = height;
    	this->roundness = roundness;
    	this->segments = segments;
    }

	virtual ~RoundedRect() { };

	const float& get_roundness() const & { return roundness; }
	float get_roundness() && { return std::move(roundness); }
	const float& get_segments() const & { return segments; }
	float get_segments() && { return std::move(segments); }
	const Rectangle& get_rec() const & { return rec; }
	Rectangle get_rec() && { return std::move(rec); }

	const Vector2 get_position() const {
		return (Vector2){rec.x, rec.y}; 
	}

	void set_position(const Vector2& position) { 
		rec.x = position.x;
		rec.y = position.y;
	}
	
	void set_position(Vector2&& position) { 
		rec.x = std::move(position.x); 
		rec.y = std::move(position.y); 
	}	

	const float& get_position_x() const & { return rec.x; }
	float get_position_x() && { return std::move(rec.x); }		
	void set_position_x(const float& pos_x) { rec.x = pos_x; }
	void set_position_x(float&& pos_x) { rec.x = std::move(pos_x); }
};

#endif // ROUNDEDRECT_H_ 
