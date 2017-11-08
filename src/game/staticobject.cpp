#include "staticobject.hpp"

StaticObject::StaticObject(){
	std::string filename = "./media/stat.png";
	Component * spritecomp = new SpriteComponent(filename);
	m_components.push_back(spritecomp);
}

StaticObject::~StaticObject(){

}


void StaticObject::render(){
	for(auto i = m_components.begin(); i != m_components.end(); ++i){
		SpriteComponent * spritecomponent = dynamic_cast<SpriteComponent*>(*i);
		if(spritecomponent != NULL){
			(*i)->update(*this);
		}
	}
}