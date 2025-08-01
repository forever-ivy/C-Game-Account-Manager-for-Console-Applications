#pragma once
#include<iostream>
#include "Account.h"
#include<fstream>
#include<string>
#include"globalFile .h"
#include<Windows.h>
#include<sstream>
#include<tuple>
#include <locale>
#include <codecvt>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include"SecurityModule .h"


class Gamer :public Account
{
public:

	Gamer();

	Gamer(int index, string name, string pwd);

	virtual void operMenu();

	virtual int alidatePassword(string name, string pwd, string filename);

	void buyEquipment();

	void showequipment();
	
	SecurityModule security;
};
