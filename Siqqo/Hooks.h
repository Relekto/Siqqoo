#pragma once
#include "Globals.h"
#include "MainLoop.h"
#include <thread>
namespace Hooks {
	void SetupHooks();
	LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
}