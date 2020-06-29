#pragma once



#include <Windows.h>
#include <TlHelp32.h>





class Injector
{
public:
	HANDLE process;
	HWND hwndproc;
	DWORD clientDLL;

	DWORD GetModule(DWORD pid, const char* name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		MODULEENTRY32 mEntry;
		mEntry.dwSize = sizeof(MODULEENTRY32);
		do
		{
			if (!strcmp(mEntry.szModule, name))
			{
				CloseHandle(snapshot);
				return (DWORD)mEntry.modBaseAddr;
			}
		} while (Module32Next(snapshot, &mEntry));
	}

	bool inject(DWORD pid, const char* dll)
	{
		if (pid == 0)
		{
			std::cout << "cannot find processID";
			return FALSE;
		}

		char myDLL[MAX_PATH];
		GetFullPathName(dll, MAX_PATH, myDLL, 0);

		HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);

		LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);

		CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

		CloseHandle(hProcess);

		return TRUE;
	}

private:
};