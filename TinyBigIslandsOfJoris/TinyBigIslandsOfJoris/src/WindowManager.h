#pragma once

struct WindowManager {
	int Width = 1280;
	int Height = 720;

	int FPS = 60;
	float FrameDelay = (float)(1000.f / FPS);
	float TargetFps = (float)(FPS / 1000.f);
	float TargetDeltaTime = 1.5f;
};