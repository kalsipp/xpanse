#include "../../engine/gameobject.hpp"
#include "../../engine/components/spritecomponent.hpp"
#include "../components/playercontroller.hpp"
#include "../../engine/basics/rect.hpp"
class Player:public GameObject{
public:
	Player(GAMEOBJECT_ID);
};