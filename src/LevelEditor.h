/*
 * LevelEditor.h
 *
 *  Created on: Sep. 08, 2023
 *      Author: Dong Won Kim
 */

#ifndef LEVEL_EDITOR_H_
#define LEVEL_EDITOR_H_

#include "raylib.h"

class LevelEditor {
private:
	int radius;

public:
	LevelEditor(const Vector2& position, const int& radius);
	virtual ~LevelEditor() { }

};




#endif // LEVEL_EDITOR_H_