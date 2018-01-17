#pragma once
#include "../component.hpp"
class BasicSquareCollider:public Component{
public:
	void update(GameObject &)override;
	std::vector<std::weak_ptr<GameObject>> get_colliding_objects();
private:
	std::vector<std::weak_ptr<GameObject>> colliding_objects;
};