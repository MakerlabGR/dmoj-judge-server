#pragma once

#ifndef id_26FCBE24_1243_4829_89F4_B266B158236E
#define id_26FCBE24_1243_4829_89F4_B266B158236E

#include <windows.h>
#include <exception>
#include <string>

class AutoHandle {
	HANDLE handle;
public:
	AutoHandle() : handle(nullptr) {}
	explicit AutoHandle(HANDLE h) : handle(h) {}
	~AutoHandle() { CloseHandle(handle); }
	operator HANDLE() { return handle; }

	AutoHandle &operator=(HANDLE h) {
		if (handle)
			CloseHandle(handle);
		handle = h;
		return *this;
	}

	HANDLE detach() {
		HANDLE h = handle;
		handle = nullptr;
		return h;
	}
};

std::string FormatWindowsError(DWORD error);

class WindowsException : public std::exception {
	DWORD error;
	mutable char message[1024];
	const char *location;
public:
	WindowsException(const char* location);
	WindowsException(const char* location, DWORD error);
	const char* what() const override;
};

#endif