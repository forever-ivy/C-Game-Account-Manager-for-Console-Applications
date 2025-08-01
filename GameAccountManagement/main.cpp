#include"Account.h"
#include"SecurityModule .h"
#include"Gamer.h"
#include"globalFile .h"
#include"Administrador.h"
#include <direct.h> // ���ڴ����ļ��� mkdir()
#include <sys/stat.h> // ����ļ����Ƿ����
#include<Windows.h>
#include<ctime>
using namespace std;

//������Ҳ˵�
void GamerMenu(Account* &a_Gamer )
{
	while (true)
	{
		
		Gamer* Gam = (Gamer*) a_Gamer;//ת��ָ������

		Gam->operMenu();//չʾ�˵�

		int select = 0;
		cin >> select; 

		if (select == 1) 
		{
			Gam->showequipment();
			
		}
		else if (select == 2) 
		{
			Gam->buyEquipment();
			
		}
		else
		{
			
			delete Gam;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

void AdministradorMenu(Account*& a_Administrador)
{
	while (true)
	{
		
		Administrador* Admin = (Administrador*)a_Administrador;//ǿ��ָ��ת��

		Admin->operMenu();

		int select = 0;
		cin >> select; 

		if (select == 1) 
		{
			
			Admin->security.checkLoginAttempts();

		}
		else if (select == 2) 
		{
			Admin->security.tackleillegalaccount();
		}
		else
		{
			delete Admin;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

void LoginIn(string fileName, int type)
{
	//����ָ�� ��ָ���������
	Account* person = NULL;


	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}


	string name;
	string pwd;

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		Gamer* gamer = new Gamer();  // ��ʱ gamer ����
		person = gamer;

		
		int result = person->alidatePassword(name, pwd, fileName);
		
		

		if (result == 2) {
			cout << "ѧ����֤��¼�ɹ���" << endl;
			system("pause");
			system("cls");

			delete gamer;
			person = new Gamer(type, name, pwd);//��������
			GamerMenu(person);

			time_t now = std::time(0);
			char* dt = std::ctime(&now); // תΪ�ַ�����ʽ
			dt[strlen(dt) - 1] = '\0'; // ȥ��ĩβ�Ļ��з�
			ofstream loginFile(LGIC_FILE,ios::app);
			if (loginFile.is_open()) {
				loginFile << name << ' ' << dt << endl;
				loginFile.close();
			}
			return;
		}
		else if (result == 1) {
			cout << "�������" << endl;

			time_t now = time(0);//��ȡ��ǰ��ϵͳʱ��
			tm* ltm = localtime(&now);//��ϵͳʱ�� now ת��Ϊ����ʱ�䣨tm �ṹ�壩
			char dt[64];
			strftime(dt, sizeof(dt), "%a %b %d %H:%M:%S %Y", ltm);//ʹ�� strftime ��ʽ��ʱ�䣬�����ַ�����ʽ��ʱ�䣬���浽�ַ����� dt ��
			ofstream faileloginFile(SCUL_FILE, ios::app);
			if (faileloginFile.is_open()) {
				faileloginFile << name << ' ' <<dt<< endl;
				faileloginFile.close();
			}
			system("pause");
			system("cls");
			delete gamer;
			return;
		}
		else if(result==0) {
			cout << "�˺�δע�ᣡ" << endl;
			cout << "�Ƿ�ע�᣿Y/N��" << endl;
			char put_in;
			cin >> put_in;
			if (put_in == 'Y' || put_in == 'y') {
				ofstream ofs(fileName, ios::app);
				if (!ofs.is_open()) {
					cout << "д��ʧ�ܣ��޷����ļ�" << endl;
					delete gamer;
					return;
				}
				ofs << name << " " << md5(pwd)<<" GAMER" << endl;
				ofs.close();
				cout << "ע��ɹ��������µ�¼��" << endl;
			}
			else {
				cout << "�����������˵�" << endl;
				system("pause");
				system("cls");
				return;
			}

			string folder = "user_data";
			string filename = folder + "/" + name + ".txt";

			ofstream userFile(filename);
			if (userFile.is_open()) {

				userFile << "username: " << name << endl;
				userFile << "money: " << 5000 << endl;
				userFile << "equiment list:" << endl;

				UINT orignalCP = GetConsoleCP();
				SetConsoleCP(CP_UTF8);

				//����װ��
				ifstream eqFile(EQUP_FILE);
				string line;
				while (getline(eqFile, line)) {
					userFile << line << endl;
				}

				eqFile.close();

				userFile << "GAMER" << endl;
				userFile.close();

				SetConsoleCP(orignalCP);

				cout << "ע��ɹ����û������ļ��Ѵ�����" << filename << endl;
				system("pause");
				system("cls");
				return;
			}
			else {
				cout << "�޷������û�ר���ļ���" << endl;
			}

		}
		else if(result==3)
		{
			cout << "�˻��ѱ����ᣬ�޷���¼��" << endl;
			system("pause");
			system("cls");
			delete gamer;
			return;
		}

	}
	else if (type == 2)
	{
		Administrador* admin = new Administrador();  
		person = admin;

		int result = person->alidatePassword(name, pwd, fileName);

		if (result == 2) {
			cout << "����Ա��֤��¼�ɹ���" << endl;
			system("pause");
			system("cls");


			delete admin;
			person = new Administrador(type, name, pwd);

			AdministradorMenu(person);

		
			return;
		}
		else if (result == 1) {
			cout << "�������" << endl;
			system("pause");
			system("cls");
			delete admin;
			return;
		}
		else {
			cout << "����Ա�˺Ų����ڣ���ֹע�����Ա��" << endl;
			system("pause");
			system("cls");
			delete admin;
			return;
		}

	}
	
	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");

	return;
}


int main() {

	int select = 0;
	while (1) {
		cout << "======================  ��ӭ������Ϸ�˺Ź���ϵͳ  ====================="
			<< endl;
		cout << endl << "��ѡ�����Ĳ���" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.�û���¼           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.����Ա��¼         |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�˳�ϵͳ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: "<<endl;


		cin >> select; 

		switch (select)
		{
		case 1: 
			LoginIn(ACTD_FILE, 1);
			break;
		case 2: 
			LoginIn(ACTD_FILE, 2);
			break;
		case 3:  
			cout << "��ӭ��һ��ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}


}