/*
 * GraphicsEntity.h
 *
 *  Created on: Aug. 28, 2023
 *      Author: Dong Won Kim
 */

#ifndef GRAPHICSENTITY_H_
#define GRAPHICSENTITY_H_

#include <utility>

class GraphicsEntity {
private:
	Vector2 position;	

public:
	GraphicsEntity() {}
	GraphicsEntity(const Vector2& position) { this->position = position; }
	virtual ~GraphicsEntity() { };

	virtual const Vector2& get_position() const & { return position; }
	virtual Vector2 get_position() && { return std::move(position); }
	virtual void set_position(const Vector2& position) { this->position = position; }
	virtual void set_position(Vector2&& position) { this->position = std::move(position); }
	void set_position_x(float&& x) { position.x = std::move(x);}
	void set_position_y(float&& y) { position.x = std::move(y);}	

	virtual void Draw() = 0;
};

#endif // GRAPHICSENTITY_H_ 
