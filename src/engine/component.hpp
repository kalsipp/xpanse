#pragma once
class GameObject;
class Component {
public:
	virtual void update(const GameObject & user);
	virtual ~Component(){}
private:
};