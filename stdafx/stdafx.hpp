#pragma once
////////////////////////////
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <msxml.h>    
#include <atomic>
#include <mutex>
#include <process.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <TlHelp32.h>
#include <list>
#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include <dxgi.h>
#include <string>
#include <D3D11.h>
#include <vector>
#include <sstream>
#include <string>
#include <thread>
#include "../axor/xor.h"
////////////////////////////
using namespace std;
////////////////////////////

HWND windows = NULL;

////////////////////////////
string ws2s(const wstring& wstr)
{
	string str(wstr.begin(), wstr.end());

	return str;
}

wstring s2ws(const string& wstr)
{
	wstring str(wstr.begin(), wstr.end());

	return str;
}
////////////////////////////

////////////////////////////
char* fast_strstr(const char* haystack, const char* needle)
{
	if (!*needle)
		return (char*)haystack;

	const char needle_first = *needle;

	haystack = strchr(haystack, needle_first);
	if (!haystack)
		return NULL;

	const char* i_haystack = haystack + 1
		, * i_needle = needle + 1;

	unsigned int  sums_diff = *haystack;
	bool          identical = true;

	while (*i_haystack && *i_needle)
	{
		sums_diff += *i_haystack;
		sums_diff -= *i_needle;
		identical &= *i_haystack++ == *i_needle++;
	}

	if (*i_needle)
		return NULL;
	else if (identical)
		return (char*)haystack;

	size_t needle_len = i_needle - needle;
	size_t needle_len_1 = needle_len - 1;

	const char* sub_start;
	for (sub_start = haystack; *i_haystack; i_haystack++)
	{
		sums_diff -= *sub_start++;
		sums_diff += *i_haystack;

		if (
			sums_diff == 0
			&& needle_first == *sub_start
			&& memcmp(sub_start, needle, needle_len_1) == 0
			)
			return (char*)sub_start;
	}

	return NULL;
}

int game_context;

wchar_t* fast_wcsstr(const wchar_t* haystack, const wchar_t* needle)
{
	if (!*needle)
		return (wchar_t*)haystack;

	const wchar_t needle_first = *needle;

	haystack = wcsrchr(haystack, needle_first);
	if (!haystack)
		return NULL;

	const wchar_t* i_haystack = haystack + 1
		, * i_needle = needle + 1;

	unsigned int  sums_diff = *haystack;
	bool          identical = true;

	while (*i_haystack && *i_needle)
	{
		sums_diff += *i_haystack;
		sums_diff -= *i_needle;
		identical &= *i_haystack++ == *i_needle++;
	}

	if (*i_needle)
		return NULL;
	else if (identical)
		return (wchar_t*)haystack;

	size_t needle_len = i_needle - needle;
	size_t needle_len_1 = needle_len - 1;

	const wchar_t* sub_start;
	for (sub_start = haystack; *i_haystack; i_haystack++)
	{
		sums_diff -= *sub_start++;
		sums_diff += *i_haystack;

		if (
			sums_diff == 0
			&& needle_first == *sub_start
			&& memcmp(sub_start, needle, needle_len_1) == 0
			)
			return (wchar_t*)sub_start;
	}

	return NULL;
}
////////////////////////////
////////////////////////////

#define debug false

////////////////////////////
////////////////////////////


void printinfo(const std::string& information, int color) {
	time_t now;
	time(&now);
	struct tm ltm;
	localtime_s(&ltm, &now);

	char timeBuffer[32];
	strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &ltm);
	std::cout << "[" << timeBuffer << "] ";

	std::cout << "-> ";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	std::cout << "[information]: ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printdbg(const std::string& information, int color) {
	time_t now;
	time(&now);
	struct tm ltm;
	localtime_s(&ltm, &now);

	char timeBuffer[32];
	strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &ltm);
	std::cout << "[" << timeBuffer << "] ";

	std::cout << "-> ";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	std::cout << "[debugger]: ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printfailure(const std::string& information, int color) {
	time_t now;
	time(&now);
	struct tm ltm;
	localtime_s(&ltm, &now);

	char timeBuffer[32];
	strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &ltm);
	std::cout << "[" << timeBuffer << "] ";

	std::cout << "-> ";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	std::cout << "[failure detected]: ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

static DWORD get_process_id(const wchar_t* process_name) {
	DWORD process_id = 0;

	HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (snap_shot == INVALID_HANDLE_VALUE)
		return process_id;

	PROCESSENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Process32FirstW(snap_shot, &entry) == TRUE) {
		if (_wcsicmp(process_name, entry.szExeFile) == 0) {
			process_id = entry.th32ProcessID;
		}
		else {
			while (Process32NextW(snap_shot, &entry) == TRUE) {
				if (_wcsicmp(process_name, entry.szExeFile) == 0) {
					process_id = entry.th32ProcessID;
					break;
				}
			}
		}
	}

	CloseHandle(snap_shot);
	return process_id;
}
////////////////////////////
////////////////////////////

std::mutex DataMutex;
