#pragma once
#include<iostream>
#include "Account.h"
#include<fstream>
#include<tuple>
#include"SecurityModule .h"
using namespace std;



class Administrador :public Account
{
public:

	Administrador();


	Administrador(int id, string name, string pwd);

	virtual void operMenu();

	virtual int alidatePassword(string name, string pwd, string filename);

	SecurityModule security;
	
};