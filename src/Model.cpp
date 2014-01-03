/*
 * Model.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: mostafa
 */

#include "Model.h"

#include <iostream>
using namespace std;

vec2 c1[] = { vec2(0.0f, 0.0), vec2(2.0f, 0.0f), vec2(2.0f, 2.0f), vec2(0.0f,
		2.0f) };

vec2 c2[] = { vec2(1.0f, 0.0f), vec2(2.0f, 1.0f), vec2(1.0f, 2.0f), vec2(0.0f,
		1.0f) };

/*Before
 X: 2
 Z: 1
 After
 X: 0
 Z: 2
 */

/*vec2 c3[] = { vec2(2.0f, 0.0f), vec2(2.0f, 2.0f), vec2(0.0f, 2.0f), vec2(0.0f,
 0.0f) };
 */
Model::Model() {
	// TODO Auto-generated constructor stub


}

void Model::initcounterstate() {

	// setting cx first for x = zy
	int cubeNum = indicies.z;

	vec2 *lookup;

//	cout << "----------------------------------------" << endl;
	//cout << "according to x " << endl;
	if (indicies.y == 0 || indicies.y == 2) {
		if (indicies.z == 1) {
			lookup = c2;
			cubeX = c2;
			//	cout << "lookup is c2" << endl;
		} else {
			lookup = c1;
			cubeX = c1;
			//cout << "lookup is c1" << endl;
		}
	} else if (indicies.y == 1) {
		if (indicies.z == 1) {
			stateCounters.x = -100;			// no change no move
//			cout << "MIDDLE CUBE" << endl;
			cubeX = NULL;
		} else {
			lookup = c2;
			cubeX = c2;
			//		cout << "lookup is c2" << endl;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (indicies.y == lookup[i].y && indicies.z == lookup[i].x) {
			if (stateCounters.x != -100)
				stateCounters.x = i;
			break;
		}
	}
	//cout << "CX = " << stateCounters.x << endl;

	// setting cy first for y = xz

	cout << "----------------------------------------" << endl;
	cout << "according to y " << endl;

	if (indicies.x == 0 || indicies.x == 2) {
		if (indicies.z == 1) {
			lookup = c2;
			cubeY = c2;
			cout << "lookup is c2" << endl;
		} else {
			cout << "lookup is c1" << endl;
			cubeY = c1;
			lookup = c1;
		}
	} else if (indicies.x == 1) {
		if (indicies.z == 1) {
			stateCounters.y = -100;			// no change no move
			cout << "MIDDLE CUBE" << endl;
			cubeY = NULL;
		} else {
			lookup = c2;
			cubeY = c2;
			cout << "lookup is c2" << endl;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (indicies.x == lookup[i].x && indicies.z == lookup[i].y) {
			if (stateCounters.y != -100)
				stateCounters.y = i;
			break;
		}
	}
	cout << "CY = " << stateCounters.y << endl;

	// setting cz first for z = xy

	if (indicies.x == 0 || indicies.x == 2) {
		if (indicies.y == 1) {
			lookup = c2;
			cubeZ = c2;
		} else {
			lookup = c1;
			cubeZ = c1;
		}
	} else if (indicies.x == 1) {
		if (indicies.y == 1) {
			stateCounters.z = -100;	// no change no move
			cubeZ = NULL;
		} else {
			lookup = c2;
			cubeZ = c2;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (indicies.x == lookup[i].x && indicies.y == lookup[i].y) {
			if (stateCounters.z != -100)
				stateCounters.z = i;
			break;
		}
	}

}

void Model::updateIndicies(int whichaxis) {

	int i, j, k;
	i = indicies.x;
	j = indicies.y;
	k = indicies.z;
	if (whichaxis == 0) {			// x
		if (k == 0) {
			j = j + 2;
			if (j == 2) {
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (j == 3) {
				j = 2;
				k = 1;
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (j == 4) {
				j = 2;
				k = 2;
				indicies.z = k;
				indicies.y = j;
				return;
			}
		}
		if (j == 2) {
			k = k + 2;
			if (k == 2) {
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (k == 3) {
				k = 2;
				j = 1;
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (k == 4) {
				k = 2;
				j = 0;
				indicies.z = k;
				indicies.y = j;
				return;
			}
		}
		if (k == 2) {
			j = j - 2;
			if (j == 0) {
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (j == -1) {
				j = 0;
				k = 1;
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (j == -2) {
				j = 0;
				k = 0;
				indicies.z = k;
				indicies.y = j;
				return;
			}
		}
		if (j == 0) {
			k = k - 2;
			if (k == 0) {
				indicies.z = k;
				indicies.y = j;
				return;
			}
			if (k == -1) {
				k = 0;
				j = 1;
				indicies.z = k;
				indicies.y = j;
				return;

			}
			if (k == -2) {
				j = 2;
				k = 0;
				indicies.z = k;
				indicies.y = j;
				return;
			}
		}
	} else if (whichaxis == 2) {
		if (i == 0) {
				j = j + 2;
				if (j == 2) {
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (j == 3) {
					j = 2;
					i = 1;
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (j == 4) {
					j = 2;
					i = 2;
					indicies.x = i;
					indicies.y = j;
					return;
				}
			}
			if (j == 2) {
				i = i + 2;
				if (i == 2) {
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (i == 3) {
					i = 2;
					j = 1;
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (i == 4) {
					i = 2;
					j = 0;
					indicies.x = i;
					indicies.y = j;
					return;
				}
			}
			if (i == 2) {
				j = j - 2;
				if (j == 0) {
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (j == -1) {
					j = 0;
					i = 1;
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (j == -2) {
					j = 0;
					i = 0;
					indicies.x = i;
					indicies.y = j;
					return;
				}
			}
			if (j == 0) {
				i = i - 2;
				if (i == 0) {
					indicies.x = i;
					indicies.y = j;
					return;
				}
				if (i == -1) {
					i = 0;
					j = 1;
					indicies.x = i;
					indicies.y = j;
					return;

				}
				if (i == -2) {
					j = 2;
					i = 0;
					indicies.x = i;
					indicies.y = j;
					return;
				}
			}
	} else if (whichaxis == 1) {
		if (k == 0) {
			i = i + 2;
			if (i == 2) {
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (i == 3) {
				i = 2;
				k = 1;
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (i == 4) {
				i = 2;
				k = 2;
				indicies.z = k;
				indicies.x = i;
				return;
			}
		}
		if (i == 2) {
			k = k + 2;
			if (k == 2) {
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (k == 3) {
				k = 2;
				i = 1;
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (k == 4) {
				k = 2;
				i = 0;
				indicies.z = k;
				indicies.x = i;
				return;
			}
		}
		if (k == 2) {
			 i= i - 2;
			if (i == 0) {
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (i == -1) {
				i = 0;
				k = 1;
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (i == -2) {
				i = 0;
				k = 0;
				indicies.z = k;
				indicies.x = i;
				return;
			}
		}
		if (i == 0) {
			k = k - 2;
			if (k == 0) {
				indicies.z = k;
				indicies.x = i;
				return;
			}
			if (k == -1) {
				k = 0;
				i = 1;
				indicies.z = k;
				indicies.x = i;
				return;

			}
			if (k == -2) {
				i = 2;
				k = 0;
				indicies.z = k;
				indicies.x = i;
				return;
			}
		}

	}

}

void Model::doforx(bool clockwise) {
	if (cubeX == NULL)
		return;
	if (clockwise) {
		stateCounters.x++;
		if (stateCounters.x > 3.0f)
			stateCounters.x = 0.0f;

	} else {
		stateCounters.x--;
		if (stateCounters.x < 0)
			stateCounters.x = 3;
	}
	indicies.y = cubeX[(int) stateCounters.x].y;
	indicies.z = cubeX[(int) stateCounters.x].x;

	for (int i = 0; i < 4; i++) {
		if (indicies.x == cubeY[i].x && indicies.z == cubeY[i].y) {
			if (stateCounters.y != -100)
				stateCounters.y = i;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (indicies.x == cubeZ[i].x && indicies.y == cubeZ[i].y) {
			if (stateCounters.z != -100)
				stateCounters.z = i;
			break;
		}
	}
}
void Model::dofory(bool clockwise) {
	if (cubeY == NULL)
		return;
	if (clockwise) {
		stateCounters.y++;
		if (stateCounters.y > 3.0f)
			stateCounters.y = 0.0f;
	} else {
		stateCounters.y--;
		if (stateCounters.y < 0)
			stateCounters.y = 3;
	}

	float fx = indicies.x;
	float fy = indicies.y;
	float fz = indicies.z;

	indicies.x = cubeY[(int) stateCounters.y].x;
	indicies.z = cubeY[(int) stateCounters.y].y;

	if (indicies.x == 0 && indicies.y == 0 && indicies.z == 2 && fx == 2
			&& fy == 0 && fz == 1) {
		cout << "27aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
		cout << "Cx = " << stateCounters.y << endl;
	}

	for (int i = 0; i < 4; i++) {
		if (indicies.y == cubeX[i].y && indicies.z == cubeX[i].x) {
			if (stateCounters.x != -100)
				stateCounters.x = i;
			break;
		} else if (i == 3) {
			cout
					<< "=============================================>>>>>>>>>>>>>.Not Found"
					<< endl;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (indicies.x == cubeZ[i].x && indicies.y == cubeZ[i].y) {
			if (stateCounters.z != -100)
				stateCounters.z = i;
			break;
		} else if (i == 3) {
			cout
					<< "=============================================>>>>>>>>>>>>>.Not Found"
					<< endl;
		}
	}
	/*Before
	 X: 2
	 Y: 0
	 Z: 1
	 After
	 X: 0
	 Y: 0
	 Z: 2*/

}
void Model::doforz(bool clockwise) {
	if (cubeZ == NULL)
		return;
	if (clockwise) {
		stateCounters.z++;
		if (stateCounters.z > 3.0f)
			stateCounters.z = 0.0f;
	} else {
		stateCounters.z--;
		if (stateCounters.z < 0)
			stateCounters.z = 3;
	}
	indicies.x = cubeZ[(int) stateCounters.z].x;
	indicies.y = cubeZ[(int) stateCounters.z].y;

}
void Model::updatestates(int currentRotationAxis, bool clockwise) {
	switch (currentRotationAxis) {
	case 1:
		doforx(clockwise);
		break;
	case 2:
		dofory(clockwise);

		break;
	case 3:
		doforz(clockwise);

		break;

	default:
		break;
	}
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

