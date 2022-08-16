#include "pch.h"
#include "mem.h"

// Takes in memory location of bytes to patch, bytes to patch with, size of patch bytes, and the handle to the process
// Overwrites a specified set of bytes with bytes passed by the function argument
void Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	// Variable to store old protections / previous access permissions
	DWORD oldProtect;

	// Change protections at memory 'dst' to give READWRITE permissions
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	// Overwrite bytes in memory 'dst' with 'src' bytes (use (BYTE*)"0x00\0x00")
	memcpy(dst, src, size);

	// Restore old protections
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

// Takes in memory location of bytes to patch, size of patch bytes, and the handle to the process
// Overwrites a specified set of bytes with no operation (NOP) instructions
void Nop(BYTE* dst, unsigned int size)
{
	// Variable to store old protections / previous access permissions
	DWORD oldProtect;

	// Change protections at memory 'dst' to give READWRITE permissions
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);

	// Overwrite bytes in memory 'dst' with 0x90 NOP instructions, size equals number of bytes
	memset(dst, 0x90, size);

	// Restore old protections
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}