/*
 * Model.h
 *
 *  Created on: Nov 23, 2013
 *      Author: mostafa
 */

#include "include/Angel.h"
#include <glm/glm.hpp>

#ifndef MODEL_H_
#define MODEL_H_
class Model {
public:
	Model();
	vec3 sideNumbers;
	vec3 pos;
	vec3 angles;
	vec3 indicies;
	vec3 stateCounters;
	vec2 *cubeX;
	vec2 *cubeY;
	vec2 *cubeZ;
	glm::mat4 rotationMat;
	void updatestates(int currentRotationAxis, bool clockwise);
	void initcounterstate();
	void updateIndicies(int whichaxis);


	virtual ~Model();
private:
	void doforx(bool clockwise);
	void dofory(bool clockwise);
	void doforz(bool clockwise);
};

#endif /* MODEL_H_ */
