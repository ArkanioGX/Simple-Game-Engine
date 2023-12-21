#pragma once
#include "Component.h"
class DoorController : public Component
{
public:
	DoorController(Actor* ownerP, char kID);
	~DoorController();
	DoorController() = delete;
	DoorController(const DoorController&) = delete;
	DoorController& operator=(const DoorController&) = delete;

	bool checkKeyID(char kID) ;

	void destroyDoor();
private:
	char keyID;
};

