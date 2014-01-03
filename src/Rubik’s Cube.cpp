//#include "include/Angel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"
#include <stdlib.h>
//#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
const int NumPoints = 100 + 1800;
const GLfloat WindowWidth = 600;
const GLfloat WindowHeight = 400;

using namespace std;

vector<vec2*> undoStack;

void display();
void rotateAroundAxis(int);

float camXPOS = 3, camYPOS = 0, camZPOS;
glm::vec3 camPostion = glm::vec3(3.0, 3.0, 3.0);

GLint currentColor;

GLint currentCirclePOS;

GLint currentFallingCirclePOS;

GLint Angle;
GLint uniView;

GLint transAroundX;
GLint transAroundY;
GLint RotationMat;
GLint cubeTranslations;
GLint cubeRotations;
GLint uniNormal;


glm::mat4 proj;
glm::mat4 view;
glm::mat4 trans;
glm::mat4 view1;
glm::mat4 view2;

Model models[27];
bool dragging = false;

int drag_x_origin;
int drag_y_origin;
float camera_angle_v;
float camera_angle_h;
glm::mat4 angleRotX;
glm::mat4 angleRotY;
glm::mat4 angleRotZ;

glm::mat4 angleViewRotX;
glm::mat4 angleViewRotY;
glm::mat4 angleViewRotZ;

glm::mat4 NangleViewRotX;
glm::mat4 NangleViewRotY;
glm::mat4 NangleViewRotZ;

int timerWait = 7;

// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static GLfloat g_vertex_buffer_data[] = { -0.25f, 0.25f, 0.25f, //   v1                  triangle 1 : begin	//v1
		0.25f, 0.25f, 0.25f,	//v4
		0.25f, 0.25f, -0.25f, // v6    triangle 1 : end

		-0.25f, 0.25f, -0.25f, // v5     triangle 2 : begin
		-0.25f, 0.25f, 0.25f,	// v1
		0.25f, 0.25f, -0.25f, // v6  triangle 2 : end

		0.25f, 0.25f, -0.25f,	//v6
		0.25f, -0.25f, 0.25f,	//v3
		0.25f, -0.25f, -0.25f,	//v7

		0.25f, 0.25f, 0.25f,	//v4
		0.25f, 0.25f, -0.25f,	//v6
		0.25f, -0.25f, 0.25f,	//v3

		-0.25f, -0.25f, 0.25f,	//v2
		-0.25f, -0.25f, -0.25f,	//v8
		0.25f, -0.25f, 0.25f,	//v3

		0.25f, -0.25f, -0.25f,	//v7
		-0.25f, -0.25f, -0.25f,	//v8
		0.25f, -0.25f, 0.25f,	//v3

		-0.25f, -0.25f, 0.25f,	//v2
		-0.25f, 0.25f, -0.25f, // v5
		-0.25f, -0.25f, -0.25f,	//v8

		-0.25f, -0.25f, 0.25f,	//v2
		-0.25f, 0.25f, -0.25f, // v5
		-0.25f, 0.25f, 0.25f,	// v1

		-0.25f, 0.25f, -0.25f, // v5
		0.25f, 0.25f, -0.25f,	//v6
		0.25f, -0.25f, -0.25f,	//v7

		-0.25f, 0.25f, -0.25f, 	// v5
		0.25f, -0.25f, -0.25f,	//v7
		-0.25f, -0.25f, -0.25f,		//v8

		-0.25f, -0.25f, 0.25f,	//v2
		0.25f, 0.25f, 0.25f,	//v4
		0.25f, -0.25f, 0.25f,	//v3

		-0.25f, -0.25f, 0.25f,	//v2
		0.25f, 0.25f, 0.25f,	//v4
		-0.25f, 0.25f, 0.25f,	// v1
		};

const float DEG2RAD = 3.14159 / 180;
float angleRotationCounter = 0.0;
bool isAnimating = false;
float angle = 00.000f;
int whichAxis = 0, index = 0;

vector<int> randoms;
void randomizer(int mod) {
	srand((unsigned) time(0));

	int random_integer;
	for (int index = 0; index < 50; index++) {
		random_integer = (rand() % 33) + 33;
		random_integer = random_integer % 77;
		randoms.push_back(random_integer);
		cout << random_integer << endl;
	}

}
int ii = 0;
int whichaxistoberotated = 0;
int iii = 0;
int randC;
int maxx;
bool isStarting = true;
void startR() {

	//ii = 0;
	timerWait = 3;
	cout << "iii = " << iii << endl;
	if (isStarting == false)
		return;
	if (iii >= maxx) {
		timerWait = 7;
		isStarting = false;
		return;
	}
	whichaxistoberotated = 0;
	cout << "Max " << maxx << endl;
	if (!isAnimating) {
		whichaxistoberotated = randoms.at(ii) % 3;
		ii++;
		ii = ii % 50;

		switch (whichaxistoberotated) {
		case 0:
			randC = randoms.at(ii) % 3;

			whichAxis = 0;
			index = randC;
			ii++;
			ii = ii % 50;
			iii++;
			angle = 1;
			rotateAroundAxis(0);
			cout << "Works for x>0.84" << endl;

			cout << "Rotation around x = " << randC << " and then.." << endl;
			break;
		case 1:
			randC = randoms.at(ii) % 3;
			;
			whichAxis = 1;
			index = randC;
			ii++;
			ii = ii % 50;
			iii++;
			angle = 1;

			rotateAroundAxis(0);
			cout << "Works for x>0.84" << endl;
			cout << "Rotation around y = " << randC << " and then.." << endl;
			break;
		case 2:
			randC = randoms.at(ii) % 3;
			;
			whichAxis = 2;
			index = randC;
			ii++;
			ii = ii % 50;
			iii++;
			angle = 1;

			rotateAroundAxis(0);
			cout << "Works for x>0.84" << endl;

			cout << "Rotation around z = " << randC << " and then.." << endl;
			break;
		default:
			break;
		}

	} else {
		cout << ":O" << endl;

	}

}
void randomstart() {
	//int startRotationNum = randomizer();

	randomizer(55);
	maxx = randoms.at(0);
//	while (maxx < 10) {
//		maxx = maxx * 7;
//	}
	maxx = 7;
	//maxx = 5;

	startR();

}

bool checkScore() {
	float currangleY_X0 = -100;
	float currangleZ_X0 = -100;

	float currangleY_X2 = -100;
	float currangleZ_X2 = -100;

	float currangleX_Y0 = -100;
	float currangleZ_Y0 = -100;

	float currangleX_Y2 = -100;
	float currangleZ_Y2 = -100;

	float currangleX_Z0 = -100;
	float currangleY_Z0 = -100;

	float currangleX_Z2 = -100;
	float currangleY_Z2 = -100;

	for (int i = 0; i < 27; ++i) {

		if (models[i].indicies.x == 0) {
			if (currangleY_X0 != -100) {
				if (currangleY_X0 != models[i].angles.y) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleY_X0 = models[i].angles.y;
			}

			if (currangleZ_X0 != -100) {
				if (currangleZ_X0 != models[i].angles.z) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleZ_X0 = models[i].angles.z;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (models[i].indicies.x == 2) {

			if (currangleY_X2 != -100) {
				if (currangleY_X2 != models[i].angles.y) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleY_X2 = models[i].angles.y;
			}

			if (currangleZ_X2 != -100) {
				if (currangleZ_X2 != models[i].angles.z) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleZ_X2 = models[i].angles.z;
			}
///////////////////////////////////////////////////////////////////////////////////////////////
		} else if (models[i].indicies.y == 0) {
			if (currangleX_Y0 != -100) {
				if (currangleX_Y0 != models[i].angles.x) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleX_Y0 = models[i].angles.x;
			}

			if (currangleZ_Y0 != -100) {
				if (currangleZ_Y0 != models[i].angles.z) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleZ_Y0 = models[i].angles.z;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (models[i].indicies.y == 2) {
			if (currangleX_Y2 != -100) {
				if (currangleX_Y2 != models[i].angles.x) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleX_Y2 = models[i].angles.x;
			}

			if (currangleZ_Y2 != -100) {
				if (currangleZ_Y2 != models[i].angles.z) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleZ_Y2 = models[i].angles.z;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (models[i].indicies.z == 0) {
			if (currangleY_Z0 != -100) {
				if (currangleY_Z0 != models[i].angles.y) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleY_Z0 = models[i].angles.y;
			}

			if (currangleX_Z0 != -100) {
				if (currangleX_Z0 != models[i].angles.x) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleX_Z0 = models[i].angles.x;
			}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if (models[i].indicies.z == 2) {
			if (currangleY_Z2 != -100) {
				if (currangleY_Z2 != models[i].angles.y) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleY_Z2 = models[i].angles.y;
			}

			if (currangleX_Z2 != -100) {
				if (currangleX_Z2 != models[i].angles.x) {
					cout << "models[i].angles.x = " << models[i].angles.x
							<< "models[i].angles.y = " << models[i].angles.y
							<< "models[i].angles.z = " << models[i].angles.z
							<< endl;
					return false;
				}
			} else {
				currangleX_Z2 = models[i].angles.x;
			}
		}
	}
	cout << "Winneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer  ))))" << endl;
	return true;
}

static const GLfloat g_color_buffer_data[] = { 0.583f, 0.771f, 0.014f, 0.609f,
		0.115f, 0.436f, 0.327f, 0.483f, 0.844f, 0.822f, 0.569f, 0.201f, 0.435f,
		0.602f, 0.223f, 0.310f, 0.747f, 0.185f, 0.597f, 0.770f, 0.761f, 0.559f,
		0.436f, 0.730f, 0.359f, 0.583f, 0.152f, 0.483f, 0.596f, 0.789f, 0.559f,
		0.861f, 0.639f, 0.195f, 0.548f, 0.859f, 0.014f, 0.184f, 0.576f, 0.771f,
		0.328f, 0.970f, 0.406f, 0.615f, 0.116f, 0.676f, 0.977f, 0.133f, 0.971f,
		0.572f, 0.833f, 0.140f, 0.616f, 0.489f, 0.997f, 0.513f, 0.064f, 0.945f,
		0.719f, 0.592f, 0.543f, 0.021f, 0.978f, 0.279f, 0.317f, 0.505f, 0.167f,
		0.620f, 0.077f, 0.347f, 0.857f, 0.137f, 0.055f, 0.953f, 0.042f, 0.714f,
		0.505f, 0.345f, 0.783f, 0.290f, 0.734f, 0.722f, 0.645f, 0.174f, 0.302f,
		0.455f, 0.848f, 0.225f, 0.587f, 0.040f, 0.517f, 0.713f, 0.338f, 0.053f,
		0.959f, 0.120f, 0.393f, 0.621f, 0.362f, 0.673f, 0.211f, 0.457f, 0.820f,
		0.883f, 0.371f, 0.982f, 0.099f, 0.879f };
//----------------------------------------------------------------------------

glm::vec3 GetOGLPosAzmy(int x, int y) {
	GLint viewport[4];
	GLfloat winY, z;
	glGetIntegerv(GL_VIEWPORT, viewport);

	winY = viewport[3] - y;

	glReadPixels(x, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	glm::vec3 screen = glm::vec3(x, winY, z);

	glm::vec3 pos = glm::unProject(screen, view, proj,
			glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));

	//glm::mat4 Invrot =glm::rotate(Invrot, 45.0f, glm::vec3(0, 1, 0));
	//glm::vec4 pos2 = Invrot * glm::vec4(pos,1.0);
	//pos.x = pos2.x;
	//pos.y = pos2.y;
	//pos.z = pos2.z;
	return pos;
}

void initiateStateCounters(int i, int j, int k) {

}

/**
 * solves the current cube
 */
bool isSolving = false;
int RotCount = 0; //to simulate clockwise rotations do 3 counterclock rots
void solveCube() {

	//cout<<"UNDO SIZE "<<undoStack.size()<<endl;
	isSolving = true;
	timerWait = 3;
	if (undoStack.size() == 0) {
		isSolving = false;
		timerWait = 7;
		return;
	}
	++RotCount;
	vec2 *move;
	move = undoStack.at(undoStack.size() - 1);
	if (RotCount == 3) {
		//last rotation remove play from stack
		undoStack.pop_back();
		RotCount = 0;
	}
	angle = 1;
	whichAxis = move->x;
	index = move->y;
	rotateAroundAxis(0);
	return;

}
void rotateAroundAxis(int _ptr) {
	isAnimating = true;

//	if (isStarting)
//		cout << "is Starting" << endl;
	switch (whichAxis) {
	case 0:
		for (int i = 0; i < 27; ++i) {
			if (models[i].indicies.x == index) {
				models[i].angles.x += angle;
				if (models[i].angles.x >= 360.0f) {
					models[i].angles.x = 0.0f;
				}
				models[i].rotationMat = angleRotX * models[i].rotationMat;
			}

		}
		angleRotationCounter += angle;
		if (angleRotationCounter >= 90.0 || angleRotationCounter <= -90.0) {
			if(!isSolving){
			vec2 *move = new vec2(whichAxis, index);
			undoStack.push_back(move);
			}
			isAnimating = false;
			bool isclockwise = false;
			if (angleRotationCounter >= 90.0)
				isclockwise = false;
			else
				isclockwise = true;
			for (int i = 0; i < 27; ++i) {
				if (models[i].indicies.x == index) {
					cout << "///////////////////////////////////////" << endl;
					/*
					 cout << "Before" << endl;
					 cout << "X: " << models[i].indicies.x << endl;
					 cout << "Y: " << models[i].indicies.y << endl;
					 cout << "Z: " << models[i].indicies.z << endl;
					 */
					models[i].updateIndicies(whichAxis);
					/*
					 cout << "After" << endl;
					 cout << "X: " << models[i].indicies.x << endl;
					 cout << "Y: " << models[i].indicies.y << endl;
					 cout << "Z: " << models[i].indicies.z << endl;
					 cout << "///////////////////////////////////////" << endl;
					 */
				}
			}

			angleRotationCounter = 000.000;
			if (isStarting == true) {
				startR();
			}
			if (isSolving == true) {
				solveCube();
			}
		} else {
			glutTimerFunc(timerWait, rotateAroundAxis, 0);
		}
		break;
	case 1:
		for (int i = 0; i < 27; ++i) {
			if (models[i].indicies.y == index) {
				//	models[i].angles.x = 0;
				models[i].angles.y += angle;
				models[i].rotationMat = angleRotY * models[i].rotationMat;
				if (models[i].angles.y >= 360.0f) {
					models[i].angles.y = 0.0f;
				}
			}

		}
		angleRotationCounter += angle;
		if (angleRotationCounter >= 90.0 || angleRotationCounter <= -90.0) {
			if(!isSolving){
			vec2 *move = new vec2(whichAxis, index);
			undoStack.push_back(move);
			}
			isAnimating = false;
			bool isclockwise = false;
			if (angleRotationCounter >= 90.0)
				isclockwise = true;
			else
				isclockwise = false;
			for (int i = 0; i < 27; ++i) {
				if (models[i].indicies.y == index) {
					/*
					 cout << "///////////////////////////////////////" << endl;
					 cout << "Before" << endl;
					 cout << "X: " << models[i].indicies.x << endl;
					 cout << "Y: " << models[i].indicies.y << endl;
					 cout << "Z: " << models[i].indicies.z << endl;
					 */
					models[i].updateIndicies(whichAxis);
//					cout << "After" << endl;
//					cout << "X: " << models[i].indicies.x << endl;
//					cout << "Y: " << models[i].indicies.y << endl;
//					cout << "Z: " << models[i].indicies.z << endl;
//					cout << "///////////////////////////////////////" << endl;
				}
			}
			angleRotationCounter = 000.000;
			if (isStarting == true) {
				startR();
			}
			if (isSolving == true) {
				solveCube();
			}
		} else {
			glutTimerFunc(timerWait, rotateAroundAxis, 0);
		}
		break;
	case 2:
		for (int i = 0; i < 27; ++i) {
			if (models[i].indicies.z == index) {
				models[i].angles.z += angle;
				models[i].rotationMat = angleRotZ * models[i].rotationMat;
//				models[i].rotationMat = glm::rotate(models[i].rotationMat,
//						angle, glm::vec3(0.0f, 0.0f, 1.0f));

				if (models[i].angles.z >= 360.0f) {
					models[i].angles.z = 0.0f;
				}
			}

		}
		angleRotationCounter += angle;
		if (angleRotationCounter >= 90.0 || angleRotationCounter <= -90.0) {
			if(!isSolving){
			vec2 *move = new vec2(whichAxis, index);
			undoStack.push_back(move);
			}
			isAnimating = false;
			bool isclockwise = false;
			if (angleRotationCounter >= 90.0)
				isclockwise = false;
			else
				isclockwise = true;
			for (int i = 0; i < 27; ++i) {
				if (models[i].indicies.z == index) {
//					cout << "///////////////////////////////////////" << endl;
//					cout << "Before" << endl;
//					cout << "X: " << models[i].indicies.x << endl;
//					cout << "Y: " << models[i].indicies.y << endl;
//					cout << "Z: " << models[i].indicies.z << endl;
					models[i].updateIndicies(whichAxis);
//					cout << "After" << endl;
//					cout << "X: " << mode,ls[i].indicies.x << endl;
//					cout << "Y: " << models[i].indicies.y << endl;
//					cout << "Z: " << models[i].indicies.z << endl;
//					cout << "///////////////////////////////////////" << endl;
				}
			}
			angleRotationCounter = 000.000;
			if (isStarting == true) {
				startR();
			}
			if (isSolving == true) {
				solveCube();
			}
		} else {
			glutTimerFunc(timerWait, rotateAroundAxis, 0);
		}
		break;
	default:
		perror(":O");
		break;
	}
	display();

}

void initModels() {

	float i = 0, j = 0, k = 0, x, y, z;

	int modelCount = 0;

	float xc, yc, zc = 0;
	for (i = 0; i < 3; ++i) {
		models[modelCount].sideNumbers = vec3(0.0, 0.0, 0.0);
		x = (i - 1) * 0.6f;
		if (i == 0)
			models[modelCount].sideNumbers.x = 4;
		else if (i == 2)
			models[modelCount].sideNumbers.x = 2;
		for (j = 0; j < 3; ++j) {
			y = (1 - j) * 0.6f;
			if (j == 0)
				models[modelCount].sideNumbers.y = 3;
			else if (j == 2)
				models[modelCount].sideNumbers.y = 1;
			for (k = 0; k < 3; ++k) {
				z = (1 - k) * 0.6f;
				if (k == 0)
					models[modelCount].sideNumbers.z = 6;
				else if (k == 2)
					models[modelCount].sideNumbers.z = 5;
				models[modelCount].pos = vec3(x, y, z);
				models[modelCount].angles = vec3(0.0, 0.0, 0.0);
				models[modelCount].indicies = vec3(i, j, k);
				models[modelCount].initcounterstate();

				glm::mat4 rotZ;
				rotZ = glm::rotate(rotZ, models[modelCount].angles.x,
						glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(RotationMat, 1, GL_FALSE,
						glm::value_ptr(rotZ));
				modelCount++;
			}
		}
	}
}

void init(void) {

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	angleRotZ = glm::rotate(angleRotZ, 1.0f, glm::vec3(0.0, 0.0, 1.0));
	angleRotY = glm::rotate(angleRotY, 1.0f, glm::vec3(0.0, 1.0, 0.0));
	angleRotX = glm::rotate(angleRotX, 1.0f, glm::vec3(1.0, 0.0, 0.0));

	NangleViewRotZ = glm::rotate(angleRotZ, 1.0f, glm::vec3(0.0, 0.0, 1.0));
	NangleViewRotY = glm::rotate(angleRotZ, 1.0f, glm::vec3(0.0, 1.0, 0.0));
	NangleViewRotX = glm::rotate(angleRotZ, 1.0f, glm::vec3(1.0, 0.0, 0.0));

	NangleViewRotZ = glm::rotate(angleRotZ, -1.0f, glm::vec3(0.0, 0.0, 1.0));
	NangleViewRotY = glm::rotate(angleRotZ, -1.0f, glm::vec3(0.0, 1.0, 0.0));
	NangleViewRotX = glm::rotate(angleRotZ, -1.0f, glm::vec3(1.0, 0.0, 0.0));

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
			g_vertex_buffer_data, GL_STATIC_DRAW);

//	GLuint colorbuffer;
//	glGenBuffers(1, &colorbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//	glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(g_color_buffer_data), g_color_buffer_data);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	//--------------------------------------------------------
	//calculating view matrix
	view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	uniView = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	view1 = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//----------------------------------
	//calculating projection matrix
	proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	///////////////////////////////////////////////////////////////////////

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

//	GLuint loc2 = glGetAttribLocation(program, "vColor");
//	glEnableVertexAttribArray(loc2);
//	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vertex_buffer_data)) );

	currentColor = glGetUniformLocation(program, "faceColor");
	cubeTranslations = glGetUniformLocation(program, "cubeTrans");
	uniNormal = glGetUniformLocation(program, "vNormal");

	glClearColor(0.0, 0.0, 0.0, 1.0);		// white background

	transAroundX = glGetUniformLocation(program, "rotAroundX");
	transAroundY = glGetUniformLocation(program, "rotAroundY");
	RotationMat = glGetUniformLocation(program, "RotationMat");


	glEnable(GL_LIGHTING);
	   glEnable(GL_LIGHT0);

	//trans = glm::rotate(trans, 90.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	//glUniformMatrix4fv(transAroundX, 1, GL_FALSE, glm::value_ptr(trans));
	initModels();

}

//----------------------------------------------------------------------------

void display(void) {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//0 --> one point
	//1-2 --> line
	//3-6 --> wireframe squre
	//7-9 --> triangle square

	glm::mat4 transM;
	for (int i = 0; i < 27; i++) {
		glm::mat4 rotX;
		glm::mat4 rotY;
		glm::mat4 rotZ;

		//glm::mat4 rotation;

		//cout<<"XPOS: "<<models[i].pos.x<<endl;
		//cout<<"YPOS: "<<models[i].pos.y<<endl;
		//cout<<"ZPOS: "<<models[i].pos.z<<endl;

//			rotation  = glm::rotate(rotation, models[i].angles.x,
//					glm::vec3(1.0f, 0.0f, 0.0f));
//			glUniformMatrix4fv(transAroundX, 1, GL_FALSE, glm::value_ptr(rotation));
//			rotation = glm::rotate(rotation, models[i].angles.y,
//					glm::vec3(0.0f, 1.0f, 0.0f));
//			glUniformMatrix4fv(transAroundX, 1, GL_FALSE, glm::value_ptr(rotation));
//			rotation= glm::rotate(rotation, models[i].angles.z,
//						glm::vec3(0.0f, 0.0f, 1.0f));
//				glUniformMatrix4fv(transAroundX, 1, GL_FALSE, glm::value_ptr(rotX));

//		rotY = glm::rotate(rotY, models[i].angles.y,
//				glm::vec3(0.0f, 1.0f, 0.0f));
//		glUniformMatrix4fv(transAroundY, 1, GL_FALSE, glm::value_ptr(rotY));
//
//		rotZ = glm::rotate(rotZ, models[i].angles.z,
//				glm::vec3(0.0f, 0.0f, 1.0f));
//		glUniformMatrix4fv(transAroundZ, 1, GL_FALSE, glm::value_ptr(rotZ));

		//	cout << "models[" << i << "].angles = " << models[i].angles.z << endl;

//		transM = glm::translate(transM,
//				glm::vec3(models[i].pos.x, models[i].pos.y, models[i].pos.z));
//		glUniformMatrix4fv(cubeTranslations, 1, GL_FALSE,
//				glm::value_ptr(transM));
//		glUniformMatrix4fv(transAroundX, 1, GL_FALSE, glm::value_ptr(trans));

		glUniformMatrix4fv(RotationMat, 1, GL_FALSE,
				glm::value_ptr(models[i].rotationMat));	//send the rotationmatrix;
		glUniform3f(cubeTranslations, models[i].pos.x, models[i].pos.y,
				models[i].pos.z);
		glUniform3f(currentColor, 0.0f, 0.0f, 1.0f);
		glUniform3f(uniNormal, 0.0f, -1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 6);			// first face


		glUniform3f(currentColor, 1.0f, 1.0f, 0.0f);
		glUniform3f(uniNormal, -1.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 6, 6);

		glUniform3f(currentColor, 0.0f, 1.0f, 0.25f);
		glUniform3f(uniNormal, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 12, 6);

		glUniform3f(currentColor, 1.0f, 1.0f, 1.0f);
		glUniform3f(uniNormal, 1.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 18, 6);

		glUniform3f(currentColor, 1.00f, 0.5f, 0.0f);
		glUniform3f(uniNormal, 0.0f, 0.0f, -1.0f);
		glDrawArrays(GL_TRIANGLES, 24, 6);

		glUniform3f(currentColor, 1.0f, 0.0f, 0.0f);
		glUniform3f(uniNormal, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}

	glutSwapBuffers();

	//cout << "Display" << endl;
}

//----------------------------------------------------------------------------

//---------------------------------------------------------------------

void keyboard_special(int key, int x, int y) {

//	  switch (key)
//	    {
//	       case 27 :      break;
//	       case 100 : cout<<"GLUT_KEY_LEFT "<<key<<endl;   break;
//	       case 102: cout<<"GLUT_KEY_RIGHT "<<key<<endl  ;  break;
//	       case 101   : cout<<"GLUT_KEY_UP "<<key <<endl ;  break;
//	       case 103 : cout<<"GLUT_KEY_DOWN "<<key<<endl;  ;  break;
//	    }

	switch (key) {
	case 102: //rotate view around y anticlock

		view = glm::rotate(view, -2.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		//cout << "GLUT_KEY_RIGHT " << key << endl;
		break;
	case 100: //rotate view around y clock
		//cout << "GLUT_KEY_left " << key << endl;
		view = glm::rotate(view, 2.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		break;

	case 101:			//rotate view around z anti clock
		view = glm::rotate(view, -2.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		break;
	case 103:			//rotate view around z clock
		view = glm::rotate(view, 2.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		break;
//	case 223:
//		view = NangleViewRotX * view;
//		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
//		break;
//	case 234:
//		view = angleViewRotX * view;
//		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
//		break;
	}
	display();
}
int countg = 1;
void keyboard(unsigned char key, int x, int y) {
	//cout << "Randdom Started" << endl;
	if (countg == 1) {
		randomstart();
		++countg;
	} else {
		solveCube();
	}

}

//----------------------------------------------------------------------------

int releesFix = 0;
//on press and release
float viewangle = 0000000.00;

float viewangleY = 0000000.00;

float fXnow = -100;
float fXlast = -100;

float fYnow = -100;
float fYlast = -100;

float direction = 1;
int buttonP = 0;
int count = 1;
void onPressMouse(int button, int state, int x, int y) {

	angle = 1;
	if (button == GLUT_LEFT_BUTTON && isAnimating == false) {
		if (state == GLUT_UP) {
			checkScore();

			cout << "mouse pressed" << endl;
			glm::vec3 pos = GetOGLPosAzmy(x, y);

			int i, j, k = 0;
			if (pos.x > -0.86f && pos.x < -0.4f) {
				i = 0;
			} else if (pos.x > -0.25f && pos.x < 0.25f) {
				i = 1;
			} else if (pos.x > 0.4f && pos.x < 0.86f) {
				i = 2;
			} else {
				return;
			}

			if (pos.y < 0.86 && pos.y > 0.4) {
				j = 0;
			} else if (pos.y < 0.25 && pos.y > -0.25) {
				j = 1;
			} else if (pos.y < -0.4 && pos.y > -0.86) {
				j = 2;
			} else {
				return;
			}

			if (pos.z < 0.86 && pos.z > 0.4) {
				k = 0;
			} else if (pos.z < 0.25 && pos.z > -0.25) {
				k = 1;
			} else if (pos.z < -0.4 && pos.z > -0.86) {
				k = 2;
			} else {
				return;
			}

			if (k == 2 && i == 2 && pos.x > 0.84) {
				whichAxis = 1;
				index = j;
				rotateAroundAxis(0);
				cout << "Works for x<0.85" << endl;
			}

			if (j == 2) {

				if ((k == 0 || k == 2) && pos.x < 0.84) {
					whichAxis = 0;
					index = i;
					rotateAroundAxis(0);
					cout << "Works for x>0.84" << endl;
				} else if ((i == 0 || i == 2) && pos.y > 0.85) {
				}
			}

			if (i == 0 && j == 0 && pos.y < 0.85) {
				whichAxis = 2;
				index = k;
				rotateAroundAxis(0);
				cout << "Works for y<-0.85" << endl;

			}
			cout << "____________________________________________" << endl;
			cout << "I :" << i << endl;
			cout << "J :" << pos.y << endl;
			cout << "K :" << k << endl;

		}
		/*

		 if (count == 1 && false) {
		 //		//rotate y
		 //		angle = 1;
		 //		index = 0;
		 //		whichAxis = 1;
		 //		rotateAroundAxis(0);
		 //		++count;
		 }
		 glm::vec3 pos = GetOGLPosAzmy(x, y);

		 cout << "____________________________________----" << endl;
		 cout << "x: " << pos.x << endl;
		 cout << "y: " << pos.y << endl;
		 cout << "z: " << pos.z << endl;

		 //	models[0].angles = vec3(90.0, 0.0, 0.0);
		 if (!isAnimating && false) {
		 if (button == GLUT_LEFT_BUTTON) {
		 if (state == GLUT_UP) {
		 cout << "Hena " << endl;
		 if (count == 1) {
		 angle = 1;
		 index = 2;
		 whichAxis = 0;
		 rotateAroundAxis(0);
		 ++count;

		 //				angle = 1;
		 //				index = 0;
		 //				whichAxis = 1;
		 //				rotateAroundAxis(0);
		 //				++count;
		 } else if (count == 3) {
		 angle = 1;
		 index = 0;
		 whichAxis = 1;
		 rotateAroundAxis(0);
		 ++count;
		 count = 1;
		 } else if (count == 2) {
		 cout << "kj;ln;kjj;l'lm';,m" << endl;
		 angle = 1;
		 index = 0;
		 whichAxis = 2;
		 rotateAroundAxis(0);

		 //				angle = 1;
		 //				index = 0;
		 //				whichAxis = 1;
		 //				rotateAroundAxis(0);
		 //				++count;
		 //
		 ++count;
		 //				count = 1;
		 }
		 }
		 }
		 }
		 return;

		 float fX = x / (float) glutGet(GLUT_WINDOW_WIDTH) * (1 - (-1)) + (-1);
		 float fY = y / (float) glutGet(GLUT_WINDOW_HEIGHT) * (1 - (-1)) + (-1);

		 //	glm::mat4 camRotate;
		 //	camRotate = glm::rotate(camRotate, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		 //	if (button == GLUT_LEFT_BUTTON) {
		 //		if (state == GLUT_UP) {
		 //			buttonP = 1;
		 //			if (dragging == true) {
		 //				dragging = false;
		 //			} else {
		 //				dragging = true;
		 //				fXnow = fX;
		 //				fYnow = fY;
		 //			}
		 //			drag_x_origin = x;
		 //			drag_y_origin = y;
		 //			cout << "Pressed down" << endl;
		 //		} else
		 //			cout << "Pressed up" << endl;
		 //		//dragging = false;
		 //	} else if (button == GLUT_RIGHT_BUTTON) {
		 //		if (state == GLUT_UP) {
		 //			buttonP = 2;
		 //
		 //			if (dragging == true) {
		 //				dragging = false;
		 //			} else {
		 //				dragging = true;
		 //				fXnow = fX;
		 //				fYnow = fY;
		 //			}
		 //			drag_x_origin = x;
		 //			drag_y_origin = y;
		 //			cout << "Pressed down" << endl;
		 //		} else
		 //			cout << "Pressed up" << endl;
		 //
		 //	}
		 */
	}
}

vec3 GetOGLPos(int x, int y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float) x;
	winY = (float) viewport[3] - (float) y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX,
			&posY, &posZ);

	return vec3(posX, posY, posZ);
}
GLdouble x;
GLdouble y;
GLdouble z;

int a = 1;
void project(int x_cursor, int y_cursor) {

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY;
	glGetIntegerv(GL_VIEWPORT, viewport);
	//glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	//glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glm::vec4 gggg;

	if (a == 1) {
		int k = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {

				projection[k] = proj[i][j];
				modelview[k] = view[i][j];
				cout << projection[k] << " ";
				k++;
			}
		}
		cout << endl;
		k = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				cout << modelview[k] << " ";
				k++;
			}
		}

		cout << endl << "To2zan ya 3am " << endl;
		a++;

		glm::mat4 prod = glm::inverse(proj) * glm::inverse(view);	// p-1 v-1
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {

				cout << prod[i][j] << " ";
				k++;
			}
			cout << endl;
		}

	}

// obtain the Z position (not world coordinates but in range 0 - 1)
	GLfloat z_cursor;
	winX = (float) x_cursor;
	winY = (float) viewport[3] - (float) y_cursor;
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

// obtain the world coordinates

	z = 0.0;
	gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &x, &y,
			&z);

	GLfloat f;
	glReadPixels(z, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &f);

	gluUnProject(z, winY, f, modelview, projection, viewport, &x, &y, &z);
	cout << "-------------------  " << x << endl;

}

//Called when the mouse moves
//within the window while no mouse buttons are pressed
void onMouseMove(int x, int y) {

//cout << "dragging = " << dragging << endl;

	float fX = x / (float) glutGet(GLUT_WINDOW_WIDTH) * (1 - (-1)) + (-1);
//	cout << "onMouseMove fx = " << fX << endl;
	float fY = y / (float) glutGet(GLUT_WINDOW_HEIGHT) * (1 - (-1)) + (-1);
//cout << "onMouseMove fy = " << fY << endl;

	if (dragging) {
		fXlast = fX;
		fYlast = fY;
		//cout << "Dragging" << endl;
		camera_angle_v += ((float) (y - drag_y_origin)) * 0.3;
		camera_angle_h += ((float) (x - drag_x_origin)) * 0.3;
		drag_x_origin = x;
		drag_y_origin = y;

		if ((buttonP == 1)) {
			if (fXlast > fXnow) {
				viewangle = 2.5;
			} else {
				viewangle = -2.5;
			}
			//view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f),
			//	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::rotate(view, viewangle, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

			fXnow = fXlast;
		} else if ((buttonP == 2)) {
			if (fYlast > fYnow) {
				cout << "Fynow < fylast" << endl;
				viewangleY = 2.5;
				view = glm::rotate(view, viewangleY,
						glm::vec3(0.0f, 0.0f, 1.0f));
			} else if ((buttonP == 2) && (fYnow > fYlast)) {
				viewangleY = -2.5;
				cout << "Fynow > fylast" << endl;
				view = glm::rotate(view, viewangleY,
						glm::vec3(0.0f, 0.0f, 1.0f));
			}
			glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

			fYnow = fYlast;

			//view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f),
			//	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		//glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		display();
	}

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WindowWidth, WindowHeight);

//----------------------------------------
// If you are using freeglut, the next two lines will check if
// the code is truly 3.2. Otherwise, comment them out

//glutInitContextVersion( 3, 2 );
//glutInitContextProfile( GLUT_CORE_PROFILE );
//----------------------------------------
//	srand((unsigned) time(0));
//	int random_integer;
//	for (int index = 0; index < 20; index++) {
//		random_integer = (rand() % 33) + 33;
//		random_integer = random_integer % 3;
//		cout << random_integer << endl;
//	}

	glutCreateWindow("hello world");

	glewInit();

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_special);
	glutPassiveMotionFunc(onMouseMove);
	glutMouseFunc(onPressMouse);

	glutMainLoop();
	display();

	return 0;
}
