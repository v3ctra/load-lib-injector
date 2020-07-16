#include <Windows.h>
#include <iostream>

#include "memory.hpp"
#include "ifexist.hpp"

using namespace std;

Injector inj;

DWORD pid;

//now it's global
LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	// Restore original NtOpenFile from external process
	//credits: Daniel Krupiñski(pozdro dla ciebie byczku <3)
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{

		cout << "Imposible Hacer Bypass :(\n";
		Sleep(2000);
		exit(-1);
	}
}

void Backup()
{
	if (ntOpenFile) {
		//So, when I patching first 5 bytes I need to backup them to 0? (I think)
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	}
	else
	{
		cout << "Unable to backup :(\n";
		Sleep(2000);
		exit(-1);

	}
}

int main()
{
	SetConsoleTitle("VACa Inyector v.1 - www.CheatersUnidos.tk - 9 - Julio - 2020 :)");
	
	cout << "****************************************************************" << endl;
	cout << "* VACa Inyector v.1 - www.CheatersUnidos.tk - 9 - Julio - 2020 *" << endl;
	cout << "****************************************************************\n\n" << endl;
	
	
	cout << "Creadores:\n Daniel Krupinski, online-9, Hitchance\n\n" << endl;

	cout << "Traducido y Recompilado:\n SuperK2 & Gauxalot\n\n" << endl;

	cout << "www.CheatersUnidos.tk - Discord: https://discord.gg/4Sh8PJP" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		bypass();

		if (inj.inject(pid, "cheat.dll")) {

			cout << "CHEAT INYECTADO CORRECTAMENTE, DISFRUTA ! GLHF !\n\n" << endl;
			Sleep(5000);

			exit(0);
		}
		else
		{

			cout << "ERROR ! La Inyeccion ha fallado! \n\n" << endl;
			Sleep(5000);
			exit(0);

		}
	
	}
	else

		cout << "EL FICHERO cheat.dll NO SE HA ENCONTRADO, RECUERDA RENOMBRAR TU .DLL como cheat.dll\n\n";
		Sleep(5000);
		exit(0);

	}

	return 0;
}
