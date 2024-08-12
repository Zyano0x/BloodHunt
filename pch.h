// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "MinHook/MinHook.h"
#pragma comment(lib, "MinHook.lib")

#include "Virtualizer/VirtualizerSDK.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"

#include "Font/Fonts.h"

#include "Lazy.h"
#include "Obfuscate.h"
#include "Memory.h"
#include "RetSpoofer.h"

#include "SDK.h"
#include "CVars.h"
#include "Hooking.h"
#include "Console.h"
#include "Drawing.h"
#include "Render.h"
#include "Feature.h"
#include "DX11.h"

#endif // PCH_H
