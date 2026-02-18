#pragma once

struct Animation {
	int Index;
	int Frames;
	int Delay;

	Animation() = default;
	Animation(int idx, int frames, int delay) {
		Index = idx;
		Frames = frames;
		Delay = delay;
	}
};
