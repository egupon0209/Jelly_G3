#include "include.h"

using namespace std;

HWND ProcessMemory::hGameWindow;
DWORD ProcessMemory::pID;
HANDLE ProcessMemory::pHandle;

void ProcessMemory::GetHandle() {
	hGameWindow = FindWindow(NULL, TEXT("PuyoPuyoTetris"));
	GetWindowThreadProcessId(hGameWindow, &pID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
}

intptr_t ProcessMemory::ReadMemorys(LPCVOID addr) {
	intptr_t readaddr;
	ReadProcessMemory(pHandle, (LPCVOID)(addr), &readaddr, 4, 0);
	return readaddr;
}
int ProcessMemory::ReadMemory(LPCVOID addr) {
	int readaddr;
	ReadProcessMemory(pHandle, (LPCVOID)(addr), &readaddr, 4, 0);
	return readaddr;
}
intptr_t ProcessMemory::ReadBytes(LPCVOID addr, int bytes) {
	intptr_t readaddr;
	ReadProcessMemory(pHandle, (LPCVOID)(addr), &readaddr, bytes, 0);
	return readaddr;
}

int ProcessMemory::GetHoldmino(int player) {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378 + (player - 1) * 0x8))
				+ 0xA8))
			+ 0x3D0))
		+ 0x8));
	if (addr < 10) {
		return addr;
	}
	else {
		return 8;
	}

}

int ProcessMemory::GetCurrentmino(int player) {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378 + (player - 1) * 0x8))
				+ 0xA8))
			+ 0x3C8))
		+ 0x8));
	if (addr >= 0 && addr < 10) {
		return addr;
	}
	else {
		return 9;
	}
}

int ProcessMemory::GetNextmino(int i, int player) {			//i: next number
	int addr = 0;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)0x000140461B20)
				+ 0x378 + (player - 1) * 0x8))
			+ 0xB8))
		+ 0x15C + 0x4 * (i - 1)));


	if (addr < 10) {
		return addr;
	}
	else {
		return 9;
	}
}

int ProcessMemory::GetBoard(int x, int y, int player) {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)(
							(INT64)ReadMemory((LPCVOID)(
								(INT64)ReadMemory((LPCVOID)0x000140461B20)
								+ 0x378 + (player - 1) * 0x8))
							+ 0xC0))
						+ 0x10))
					+ 0x3C0))
				+ 0x18))
			+ 0x08 * x))
		+ 0x04 * y));


	if (addr <= 9 && addr >= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bool ProcessMemory::IsGame() {
	int addr;
	addr = ReadMemory((LPCVOID)(0x000140461B20));
	if (addr == 0) {
		return false;
	}
	else {
		return true;
	}
}

int ProcessMemory::GetFrames() {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)0x0001405989F0)
		+ 0x594));
	return addr;

}

int ProcessMemory::GetScore() {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)0x00014057F048)
		+ 0x38));
	return addr;

}

int ProcessMemory::GetLinesCleared() {
	int addr;
	addr = ReadBytes((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)0x000140461B20)
				+ 0x378))
			+ 0xA8))
		+ 0x2F8), 1);
	return addr;

}

int ProcessMemory::GetY(int player) {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378 + (player - 1) * 0x8))
				+ 0xA8))
			+ 0x3C8))
		+ 0x10));
	return addr;
}

int ProcessMemory::GetX(int player) {
	int addr;
	addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378 + (player - 1) * 0x8))
				+ 0xA8))
			+ 0x3C8))
		+ 0xC));
	return addr;
}

int ProcessMemory::GetRotation(int player) {
	int addr;
	switch (player)
	{
	case 1:
		addr =
			ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)(
							(INT64)ReadMemory((LPCVOID)(
								(INT64)ReadMemory((LPCVOID)0x000140460C08)
								+ 0x18))
							+ 0x268))
						+ 0x38))
					+ 0x3C8))
				+ 0x18));
		break;
	case 2:
		addr =
			ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)(
							(INT64)ReadMemory((LPCVOID)(
								(INT64)ReadMemory((LPCVOID)0x0001405989D0)
								+ 0x78))
							+ 0x20))
						+ 0xA8))
					+ 0x3C8))
				+ 0x18));
		break;
	}
	return addr;
}

bool ProcessMemory::IsCharacterSelect() {
	int P1state = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			0x140460690
			)) + 0x274
		));
	return P1state > 0 && P1state < 16;
}

int ProcessMemory::GetCharacter(int player) {
	int addr = ReadMemory((LPCVOID)(
		0x140598C28 + (player - 1) * 0x68
		));
	if (addr < 0 || addr > 23) return -1;
	return addr;
}

int ProcessMemory::GameState(int player) {
	int addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378 + (player - 1) * 0x8))
				+ 0xC0))
			+ 0x10))
		+ 0x80))
		;

	return addr;
}

bool ProcessMemory::IsPause(int player) {
	/*int addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x140598A20)
					+ 0x138))
				+ 0x18))
			+ 0x100))
		+ 0x58));*/
	int addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)0x140461B20)
		+ 0x208));
	return addr;
}

int ProcessMemory::GetGarbageLines(int player) {
	int addr0, addr1, garbagelines = 0;
	for (int y = 0; y < 20; y++) {
		addr0 = ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)(
							(INT64)ReadMemory((LPCVOID)(
								(INT64)ReadMemory((LPCVOID)(
									(INT64)ReadMemory((LPCVOID)0x000140461B20)
									+ 0x378 + (player - 1) * 0x8))
								+ 0xC0))
							+ 0x10))
						+ 0x3C0))
					+ 0x18))
				+ 0x08 * 0))
			+ 0x04 * y));
		addr1 = ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)(
							(INT64)ReadMemory((LPCVOID)(
								(INT64)ReadMemory((LPCVOID)(
									(INT64)ReadMemory((LPCVOID)0x000140461B20)
									+ 0x378 + (player - 1) * 0x8))
								+ 0xC0))
							+ 0x10))
						+ 0x3C0))
					+ 0x18))
				+ 0x08 * 1))
			+ 0x04 * y));
		if (addr0 == 9 || addr1 == 9) garbagelines++;
	}
	return garbagelines;
}

bool ProcessMemory::IsHoldEmpty(int player) {
	int addr;
	switch (player)
	{
	case 1:
		addr = ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)0x000140461B20)
						+ 0x378))
					+ 0xA8))
				+ 0x3D0))
			+ 0x8));
		break;

	case 2:
		addr = ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)(
						(INT64)ReadMemory((LPCVOID)0x000140461B20)
						+ 0x378 + 0x8))
					+ 0xA8))
				+ 0x3D0))
			+ 0x8));
		break;
	default:
		break;
	}

	if (!(addr >= 0 && addr <= 6)) return true;
	else return false;
}

int ProcessMemory::test() {
	int addr = ReadMemory((LPCVOID)(
		(INT64)ReadMemory((LPCVOID)(
			(INT64)ReadMemory((LPCVOID)(
				(INT64)ReadMemory((LPCVOID)(
					(INT64)ReadMemory((LPCVOID)0x000140461B20)
					+ 0x378))
				+ 0x28))
			+ 0xD0))
		+ 0x3c));
	return addr;
}