#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"md5.h"
using namespace std;
using psi = tuple<int,string,int>;
using pis = pair<int, string>;

class Account
{
public:
	virtual void operMenu() = 0;
    virtual int alidatePassword(string name,string pwd,string filename)=0;
	void  buyEquipment() {};

	int classification;
	string username;
	string password_hash;
	vector<pis> equipment_list;
	vector<psi>equiment_store;
    int money=5000;
	
};

