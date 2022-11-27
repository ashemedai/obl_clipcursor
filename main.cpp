#include "main.hpp"

#include "windows_lean.h"

#include <string>
#include <sstream>

#include "obse/PluginAPI.h"
#include "obse_common/obse_version.h"

#include "utils.hpp"

#define MOD_VERSION 1

static const int TryFindWindowIntervalMs = 1000;
static const char* ModName = "obl_clipcursor";
static const char* GameClassName = "Oblivion";

static HWND GameWindow = NULL;
static WNDPROC GameWndProc = NULL;

BOOL WINAPI DllMain(HANDLE, DWORD, LPVOID)
{
	return true;
}

extern "C" {

EXPORT bool OBSEPlugin_Query(
	const OBSEInterface* obse,
	PluginInfo* info
) {
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = ModName;
	info->version = MOD_VERSION;

	std::string log_filename(ModName);
	log_filename.append(".log");
	gLog.Open(log_filename.c_str());

	if (!version_check(obse))
		return false;

	return true;
}

EXPORT bool OBSEPlugin_Load(
	const OBSEInterface* obse
) {
	_MESSAGE("load");

	if (
		SetTimer(
			NULL,
			0,
			TryFindWindowIntervalMs,
			find_game_window_timer) == 0
	) {
		fatal_error("Failed to set timer");
		return false;
	}

	return true;
}

}

bool version_check(const OBSEInterface* obse) {
	if (obse->isEditor)
		return false;

	if (obse->obseVersion < OBSE_VERSION_INTEGER) {
		std::stringstream ss;
		ss
			<< "OBSE version is too old ("
			<< obse->obseVersion
			<< "), expected at least "
			<< OBSE_VERSION_INTEGER;

		std::string str = ss.str();
		fatal_error(str.c_str(), false);
		return false;
	}

	return true;
}

void CALLBACK find_game_window_timer(
	HWND window,
	UINT wm_timer,
	UINT_PTR timer_id,
	DWORD tick_count
) {
	GameWindow = FindWindowA(GameClassName, NULL);

	if (GameWindow == NULL)
		return;

	KillTimer(window, timer_id);
	inject_wndproc();
}

void inject_wndproc() {
	GameWndProc = reinterpret_cast<WNDPROC>(
		GetWindowLongPtrA(GameWindow, GWLP_WNDPROC));

	if (GameWndProc == NULL) {
		fatal_error("Failed to get game wndproc");
		return;
	}

	if (
		SetWindowLongPtrA(
			GameWindow,
			GWLP_WNDPROC,
			reinterpret_cast<LONG>(&injected_wndproc)) == 0
	) {
		fatal_error("Failed to set injected wndproc");
		return;
	}

	setup_clipcursor(GameWindow);

	_MESSAGE("obl_clipcursor setup correctly");
}

LRESULT CALLBACK injected_wndproc(
	HWND window,
	UINT message,
	WPARAM w_param,
	LPARAM l_param
) {
	switch (message) {
		case WM_ACTIVATE: {
			if (w_param == WA_INACTIVE)
				unset_clipcursor();
			else
				setup_clipcursor(window);

			break;
		}
		case WM_MOUSEMOVE: {
			setup_clipcursor(window);
			break;
		}
		case WM_SETFOCUS: {
			setup_clipcursor(window);
			break;
		}
		case WM_KILLFOCUS: {
			unset_clipcursor();
			break;
		}
	}

	return GameWndProc(window, message, w_param, l_param);
}

void setup_clipcursor(HWND window) {
	RECT rect;
	if (!GetWindowRect(window, &rect)) {
		fatal_error("Failed to get window rect");
		return;
	}

	if (!ClipCursor(&rect))
		fatal_error("Failed to setup clip cursor");
}

void unset_clipcursor() {
	if (!ClipCursor(NULL))
		fatal_error("Failed to unset clip cursor");
}
