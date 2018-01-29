#include <map>
#include <memory>

/*
	Container class which has ownership of all gameobjects in a scene
	Responsible for creating gameobjects and removing them.
	Also responsible for ensuring that all traces of the scene 
	and the contained gameobjects are removed together with it.
*/

class Engine;
class Scene{
public:
	
private:
	friend class Engine;
	std::map<GAMEOBJECT_ID, std::shared_ptr<GameObject>> m_gameobjects;


};