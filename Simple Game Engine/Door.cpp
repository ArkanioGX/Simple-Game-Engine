#include "Door.h"


Door::Door(Vector2 pos = Vector2::zero, float size = 2, char kID = '0') : Tile(pos, size, true, false, 3), keyID(kID) {
	dc = new DoorController(this, kID);
}



