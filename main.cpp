#include <Windows.h>
#include <iostream>
#include "memory.hpp"

using namespace std;

Injector inj;

DWORD pid;

bool DoesFileExist(const char* name) {
	if (FILE* file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

void bypass()
{
	// Restore original NtOpenFile from external process
	//credits: Daniel Krupiñski(pozdro dla ciebie byczku <3)
	LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{
		cout << "Unable to bypass :(\n";
	}
}

int main()
{
	SetConsoleTitle("totally not pasted injector :)");
	
	cout << "Credits:\n Daniel Krupinski\n online-9\n Hitchance\n\n" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		//file exist
	}
	else
	{
		cout << "cannot find cheat.dll\n\n";
		Sleep(2000);
		exit(0);
	}

	bypass();

	if (inj.inject(pid, "cheat.dll")) {
		cout << "module injected!\n\n" << endl;
		Sleep(2000);
		exit(0);
	}
	else
	{
		cout << "Injection failed!\n\n" << endl;
		Sleep(2000);
		exit(0);
	}

	return 0;
}