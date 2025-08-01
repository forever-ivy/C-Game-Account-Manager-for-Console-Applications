#include "Administrador.h"

Administrador::Administrador() {}

Administrador::Administrador(int id, string name, string pwd) {
	this->username = name;
	this->password_hash = md5(pwd);
	this->classification = id;
}

void Administrador::operMenu() {
	cout << "��ӭ����Ա��" << this->username << " ��¼��" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|         1. �鿴��¼��־       |\n";
	cout << "\t\t|         2. �������˺�       |\n";
	cout << "\t\t|         3. ע����¼           |\n";
	cout << "\t\t -------------------------------\n";
	cout << "���������ѡ�" << endl;
}

int Administrador::alidatePassword(string name, string pwd, string fileName)
{
	ifstream ifs(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "�޷����ļ�" << endl;
		return 0;
	}

	string fName, fPwd, type;
	while (ifs >> fName >> fPwd >> type) {
		if (fName == name && type == "ADMIN") {
			if (fPwd == md5(pwd)) {
				return 2; // ��¼�ɹ�
			}
			else {
				return 1; // �������
			}
		}
	}
	return 0; // �����ڸù���Ա
}