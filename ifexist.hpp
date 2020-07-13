#pragma once

//It didn't looked so good to me in main.cpp...
//So, I decided to make another file for it.

bool DoesFileExist(const char* name) {
	if (FILE* file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}