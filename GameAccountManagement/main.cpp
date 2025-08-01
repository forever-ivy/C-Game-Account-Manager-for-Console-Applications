#include"Account.h"
#include"SecurityModule .h"
#include"Gamer.h"
#include"globalFile .h"
#include"Administrador.h"
#include <direct.h> // 用于创建文件夹 mkdir()
#include <sys/stat.h> // 检查文件夹是否存在
#include<Windows.h>
#include<ctime>
using namespace std;

//进入玩家菜单
void GamerMenu(Account* &a_Gamer )
{
	while (true)
	{
		
		Gamer* Gam = (Gamer*) a_Gamer;//转换指针类型

		Gam->operMenu();//展示菜单

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
			cout << "注销成功" << endl;
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
		
		Administrador* Admin = (Administrador*)a_Administrador;//强制指针转换

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
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

void LoginIn(string fileName, int type)
{
	//父类指针 ，指向子类对象
	Account* person = NULL;


	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}


	string name;
	string pwd;

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		Gamer* gamer = new Gamer();  // 临时 gamer 对象
		person = gamer;

		
		int result = person->alidatePassword(name, pwd, fileName);
		
		

		if (result == 2) {
			cout << "学生验证登录成功！" << endl;
			system("pause");
			system("cls");

			delete gamer;
			person = new Gamer(type, name, pwd);//创建对象
			GamerMenu(person);

			time_t now = std::time(0);
			char* dt = std::ctime(&now); // 转为字符串格式
			dt[strlen(dt) - 1] = '\0'; // 去掉末尾的换行符
			ofstream loginFile(LGIC_FILE,ios::app);
			if (loginFile.is_open()) {
				loginFile << name << ' ' << dt << endl;
				loginFile.close();
			}
			return;
		}
		else if (result == 1) {
			cout << "密码错误！" << endl;

			time_t now = time(0);//获取当前的系统时间
			tm* ltm = localtime(&now);//将系统时间 now 转换为本地时间（tm 结构体）
			char dt[64];
			strftime(dt, sizeof(dt), "%a %b %d %H:%M:%S %Y", ltm);//使用 strftime 格式化时间，生成字符串形式的时间，保存到字符数组 dt 中
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
			cout << "账号未注册！" << endl;
			cout << "是否注册？Y/N：" << endl;
			char put_in;
			cin >> put_in;
			if (put_in == 'Y' || put_in == 'y') {
				ofstream ofs(fileName, ios::app);
				if (!ofs.is_open()) {
					cout << "写入失败，无法打开文件" << endl;
					delete gamer;
					return;
				}
				ofs << name << " " << md5(pwd)<<" GAMER" << endl;
				ofs.close();
				cout << "注册成功，请重新登录！" << endl;
			}
			else {
				cout << "即将返回主菜单" << endl;
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

				//导入装备
				ifstream eqFile(EQUP_FILE);
				string line;
				while (getline(eqFile, line)) {
					userFile << line << endl;
				}

				eqFile.close();

				userFile << "GAMER" << endl;
				userFile.close();

				SetConsoleCP(orignalCP);

				cout << "注册成功！用户数据文件已创建：" << filename << endl;
				system("pause");
				system("cls");
				return;
			}
			else {
				cout << "无法创建用户专属文件。" << endl;
			}

		}
		else if(result==3)
		{
			cout << "账户已被冻结，无法登录！" << endl;
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
			cout << "管理员验证登录成功！" << endl;
			system("pause");
			system("cls");


			delete admin;
			person = new Administrador(type, name, pwd);

			AdministradorMenu(person);

		
			return;
		}
		else if (result == 1) {
			cout << "密码错误！" << endl;
			system("pause");
			system("cls");
			delete admin;
			return;
		}
		else {
			cout << "管理员账号不存在！禁止注册管理员。" << endl;
			system("pause");
			system("cls");
			delete admin;
			return;
		}

	}
	
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");

	return;
}


int main() {

	int select = 0;
	while (1) {
		cout << "======================  欢迎来到游戏账号管理系统  ====================="
			<< endl;
		cout << endl << "请选择您的操作" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.用户登录           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.管理员登录         |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.退出系统           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: "<<endl;


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
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}


}