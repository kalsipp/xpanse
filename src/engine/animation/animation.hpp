#pragma once
#include <vector>
#include "../basics/logging.hpp"
#include "../basics/sprite.hpp"

class Frame {
public:
	Frame(Sprite x);
	bool transit();
	void should_transit_to(Frame *, const Transition &);
	Transition  transition();

private:
	Sprite m_sprite;
	Transition m_transition;
	Frame * next_frame;
};

class Animation {
public:
	Animation(std::vector<Frame>);
private:
	std::vector<Frame> m_frames;
	Frame * current_frame;
};


