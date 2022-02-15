#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "gametimer.h"
#include "mysoundengine.h"

class Spaceship
{
private:
	Vector2D velocity;
	Vector2D position;
	Vector2D direction;
	bool status;
	PictureIndex spaceshipPicture;
public:
	Spaceship();
	Initialise();
	Render();
	Update();
};