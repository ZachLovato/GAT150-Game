#pragma once
#include "Core/file.h"
#include "Core/Memory.h"
#include "Core//Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Audio/AudioSystem.h"

#include <memory>
#include <list>
#include <vector>

namespace wrap
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audio;

}