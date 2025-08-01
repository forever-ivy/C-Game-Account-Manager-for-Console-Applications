#include"Gamer.h"

Gamer::Gamer(){
}


Gamer::Gamer(int index, string name, string pwd){

	this->username = name;
	this->password_hash = md5(pwd);
	this->classification= index;


	ifstream ifs;
	ifs.open(ACTD_FILE, ios::in);

	ifs.close();
}

//菜单界面
void Gamer::operMenu(){
	cout << "欢迎用户：" << this->username << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看我的装备          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.购买装备              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

int Gamer::alidatePassword(string name, string pwd, string fileName)
{
    // 检查该账户是否被锁定
    ifstream lockFile(LOCKED_FILE, ios::in);
    string lockedLine;
    while (getline(lockFile, lockedLine)) {
        if (lockedLine == "username:" + name) {
            cout << "该账户已被冻结，无法登录。" << endl;
            return 3; // 表示账户已被冻结
        }
    }
    lockFile.close();
    
    
    if (this->security.CheckLoginAttemptsAndLock(name)) {
        cout << "账户输入密码错误次数超过三次，账户冻结" << endl;
        this->security.lockAccount(name);
        return 3;
    }

    ifstream ifs(fileName, ios::in);
	string fName, fPwd,type;
	while (ifs >> fName >> fPwd>>type) {
		if (fName == name) {
			if (fPwd == md5(pwd)&&type=="GAMER") {
				return 2; // 登录成功
			}
			else {
				return 1; // 密码错误
			}
		}
     
	}
	return 0; // 用户名不存在
}

void Gamer::showequipment() {


	// 用户数据文件路径
	string filepath = "user_data/" + this->username + ".txt";
	ifstream file(filepath);
	if (!file.is_open()) {
        cout << "无法打开用户装备文件: " << filepath << endl;
		return;
	}

	string line;
	int lineCount = 0;
	bool show = false;

	cout << "【" << this->username << " 的装备列表】" << endl;

	while (getline(file, line)) {
		lineCount++;

		if (line == "equiment list:") {
			show = true;
			continue;
		}
        if (line == "GAMER") {
            break;
        }

		if (show && !line.empty()) {
			cout << line << endl;
		}
	}

	file.close();


	system("pause");
	system("cls");
}

void Gamer::buyEquipment() {

    ifstream storeFile(IVNC_FILE,ios::in);
    equiment_store.clear();  // 清空旧记录
    string line;
    while (getline(storeFile, line)) {
        stringstream ss(line);
        int index;
        int price;
        string name, token;
        

        ss >> index;
        ss.ignore(2);  // 跳过 ". "

        while (ss >> token) {
            if (token[0] == '$') {
                price = stoi(token.substr(1));//把字符串转为整数
                break;
            }
            if (!name.empty()) name += " ";//name 里已经有内容（非空字符串），保留原格式
            name += token;
        }

        equiment_store.push_back(make_tuple(index, name, price));
    }
    storeFile.close();

    UINT orignalCP = GetConsoleCP();


    cout << "【装备商店】" << endl;

  
    for (auto& item : equiment_store) {
        cout << get<0>(item) << ". " << get<1>(item) << " - $" << get<2>(item) << endl;
    }
 

    cout << "账户余额：$" << money << endl;
    cout << "请输入想要购买的装备编号（0结束）：" << endl;

    // 获取用户数据文件路径
    string userFile = "user_data/" + this->username + ".txt";
    vector<string> ownedEquipment;
    bool inEquipSection = false;
    ifstream inFile(userFile);
    string fileLine;
    while (getline(inFile, fileLine)) {
        
        if (fileLine.find("money: ") == 0) {
            money = stoi(fileLine.substr(7));
        }

        if (fileLine == "equiment list:") {
            inEquipSection = true;
            continue;
        }
        if (inEquipSection && !fileLine.empty()) {
            int index = fileLine.find(". ");
            if (index!= string::npos) {
                ownedEquipment.push_back(fileLine.substr(index + 2));
            }
        }
    }
    inFile.close();


    int select = 0; 
    while (cin >> select && select != 0) {
        if (select < 1 || select >(int)equiment_store.size()) {
            cout << "编号无效，请重新输入。" << endl;
            continue;
        }

        string itemName = get<1>(equiment_store[select - 1]);
        int itemPrice = get<2>(equiment_store[select - 1]);


 
        if (find(ownedEquipment.begin(), ownedEquipment.end(), itemName) != ownedEquipment.end()) {
            cout << "你已拥有该装备，无法重复购买。" << endl;
            continue;
        }

        if (money < itemPrice) {
            cout << "余额不足，无法购买 " << itemName << endl;
            continue;
        }


        money -= itemPrice;
        ownedEquipment.push_back(itemName);


       
        cout << "成功购买：" << itemName << "，剩余余额：$" << money << endl;
        SetConsoleCP(orignalCP);
    }

    // 更新文件内容
    ofstream outFile(userFile);
 
    outFile << " username: " << username << endl;
    outFile << "money: " << money << endl;
    outFile << "equiment list:" << endl;

    int count = 1;
    SetConsoleCP(CP_UTF8);
    for (const string& eq : ownedEquipment) {
        outFile << count++ << ". " << eq << endl;
    }
    SetConsoleCP(orignalCP);

    outFile.close();
    system("pause");
    system("cls");
}



