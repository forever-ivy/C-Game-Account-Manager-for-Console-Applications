#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"globalFile .h"
using namespace std;


class SecurityModule
{
public:
	void checkLoginAttempts() ;
	void lockAccount(const string& name) ;
	bool CheckLoginAttemptsAndLock(const string& name);
	void unlockedAccount(const string& name);
	void tackleillegalaccount();
};