#pragma once

#include <cstdio>
#include <cstdint>
#include <vector>
#include <Windows.h>


#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


class WeaponClass
{
public:
	union {
		//               Type     Name   Offset
		DEFINE_MEMBER_N(int, currentWeaponPointer, 0x0004);
		DEFINE_MEMBER_N(int*, weaponOwner, 0x0008);
		DEFINE_MEMBER_N(int*, ammoReserve, 0x0010);
		DEFINE_MEMBER_N(int*, currentAmmoPointer, 0x0014);
	};
};

struct Vector3
{
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };
};

class Entity
{
public:
	union
	{
		//               Type     Name   Offset
		//DEFINE_MEMBER_N(Vector3, posHead, 0x4);
		DEFINE_MEMBER_N(Vector3, posPlayer, 0x0034);
		DEFINE_MEMBER_N(Vector3, viewAngle, 0x0040);
		DEFINE_MEMBER_N(int, playerHealth, 0x00F8);
		DEFINE_MEMBER_N(int, playerArmor, 0x00FC);
		DEFINE_MEMBER_N(int, playerSpeed, 0x0080);
		DEFINE_MEMBER_N(int, playerGrenades, 0x0158);
		DEFINE_MEMBER_N(int8_t, bAttacking, 0x0224);
		DEFINE_MEMBER_N(int, teamNumber, 0x032C);
		DEFINE_MEMBER_N(WeaponClass*, weaponPointer, 0x0374);
	};
};