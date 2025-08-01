#include "Administrador.h"

Administrador::Administrador() {}

Administrador::Administrador(int id, string name, string pwd) {
	this->username = name;
	this->password_hash = md5(pwd);
	this->classification = id;
}

void Administrador::operMenu() {
	cout << "欢迎管理员：" << this->username << " 登录！" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|         1. 查看登录日志       |\n";
	cout << "\t\t|         2. 管理冻结账号       |\n";
	cout << "\t\t|         3. 注销登录           |\n";
	cout << "\t\t -------------------------------\n";
	cout << "请输入操作选项：" << endl;
}

int Administrador::alidatePassword(string name, string pwd, string fileName)
{
	ifstream ifs(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "无法打开文件" << endl;
		return 0;
	}

	string fName, fPwd, type;
	while (ifs >> fName >> fPwd >> type) {
		if (fName == name && type == "ADMIN") {
			if (fPwd == md5(pwd)) {
				return 2; // 登录成功
			}
			else {
				return 1; // 密码错误
			}
		}
	}
	return 0; // 不存在该管理员
}