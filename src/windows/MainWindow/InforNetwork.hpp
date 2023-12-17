#pragma once
#include <string>
#include <WS2tcpip.h>
#include <Iphlpapi.h>
#include <Windows.h>
#include <Strsafe.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")


std::string GetMACAddress();
// std::string GetOSVersion();
std::string GetIPAddress();
std::string GetCurrentWindowName();
std::string GetWindowName(HWND hWnd);