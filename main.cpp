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
		cout << "NO SE PUEDE HACER BACKUP :(\n";
		Sleep(2000);
		exit(-1);
	}
}

int main()
{
	SetConsoleTitle(" Inyector VACa v.2.1 - www.CheatersUnidos.tk - 16 - Julio - 2020 :)");

	cout << "888     888     d8888  .d8888b.                 .d8888b.       d888  " << endl;
	cout << "888     888    d88888 d88P  Y88b               d88P  Y88b     d8888   " << endl;
	cout << "888     888   d88P888 888    888                      888       888  " << endl;
	cout << "Y88b   d88P  d88P 888 888         8888b.            .d88P       888  " << endl;
	cout << " Y88b d88P  d88P  888 888            88b.        od888P         888  " << endl;
	cout << "  Y88o88P  d88P   888 888    888 .d888888      d88P             888  " << endl;
	cout << "   Y888P  d8888888888 Y88b   d88 888  888      888        d8b   888  " << endl;
	cout << "    Y8P  d88P     888   Y8888P   Y888888.      888888888  Y8P 8888888\n" << endl;


	cout << "*****************************************************************" << endl;
	cout << "*  Inyector VACa 2.1 - www.CheatersUnidos.tk - 16 - Julio - 2020 *" << endl;
	cout << "*****************************************************************\n\n" << endl;



	cout << "Creadores y Agradecimientos Especiales para:\n Daniel Krupinski, online-9, Hitchance\n\n" << endl;

	cout << "Traducido y Recompilado:\n SuperK2 & Gauxalot\n\n" << endl;

	cout << "www.CheatersUnidos.tk - Discord: https://discord.gg/4Sh8PJP \n\n" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		bypass();

		if (inj.inject(pid, "cheat.dll")) {
			cout << "CHEAT INYECTADO CORRECTAMENTE, DISFRUTA ! GLHF !!\n\n" << endl;
			Backup();
			Sleep(5000);
			exit(0);
		}
		else
		{
			cout << "ERROR ! La Inyeccion ha fallado!\n\n" << endl;
			Backup();
			Sleep(5000);
			exit(-1);
		}
	
	}
	else
	{
		cout << "EL FICHERO cheat.dll NO SE HA ENCONTRADO, RECUERDA RENOMBRAR TU .DLL como cheat.dll\n\n";
		Sleep(5000);
		exit(-1);
	}

	return 0;
}
