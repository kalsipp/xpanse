#include "animation.hpp"

Animation::Animation() {
	Frame frame1(sprite);
	Frame frame2(sprite2);
	frame1.should_transit_to(frame2, aftertime(10))
	frame2.should_transit_to(frame1, aftertime(4))
	current_frame = &frame1;
}


void Animation::update() {
	render(*current_frame.sprite());
	if (current_frame->transition()->transit()) {
		current_frame->transition()->stop();
		current_frame = current_frame->next_frame();
		ASSERT(current_frame, "Animation frame is null");
		current_frame->transition()->start();
	}
}