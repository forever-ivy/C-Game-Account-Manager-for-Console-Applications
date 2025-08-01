#include"SecurityModule .h"

void SecurityModule::unlockedAccount(const string& name) {
    // 删除 locked.txt 中的账户
    ifstream inFile(LOCKED_FILE);
    ofstream outFile("temp_locked.txt");

    string line;
    while (getline(inFile, line)) {
        if (line.find(name) == string::npos) {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove(LOCKED_FILE);
    rename("temp_locked.txt", LOCKED_FILE);

    //删除 log.txt 中该账户的所有记

    ifstream logIn(SCUL_FILE);//创建一个 ifstream 输入文件流对象 logIn
    ofstream logOut("temp_security.txt");//创建一个 ofstream 输出文件流对象 logOut
    while (getline(logIn, line)) {
        if (line.find(name + " ") != 0) { // 检查是否是该账户的记录
            logOut << line << endl;
        }
    }
    logIn.close();
    logOut.close();
    remove(SCUL_FILE);
    rename("temp_security.txt", SCUL_FILE);
}

void SecurityModule::checkLoginAttempts() {
    ifstream file(LGIC_FILE);
    string line;
    cout << "登录日志内容如下：" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    system("pause");
    system("cls");

}

void SecurityModule::lockAccount(const string& name) {
	ofstream outFile(LOCKED_FILE, ios::app); // 以追加模式打开
	if (outFile.is_open()) {
		outFile<<"username:" << name << endl;
		outFile.close();
	}
}

bool SecurityModule::CheckLoginAttemptsAndLock(const string& name) {

	ifstream file(SCUL_FILE);
	
	// 获取今天的日期字符串（只保留年月日）
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char today[20];
	strftime(today, sizeof(today), "%a %b %d", ltm); //确保格式

	int failCount = 0;
	string line;

	while (getline(file, line)) {
		// 判断是否以该用户名开头
		if (line.find(name + " ") == 0) {
			// 判断日期是否是今天
			if (line.find(today) != string::npos) {
				failCount++;
			}
		}
	}

	file.close();

	if (failCount >= 3) {
		return true;
       
	}
	else
	{
		return false;
	}
}

void SecurityModule::tackleillegalaccount() {
    ifstream securityfile(SCUL_FILE);
    string lines;
    cout << "非法登录日志如下：" << endl;
    while (getline(securityfile, lines)) {
        cout << lines << endl;
    }

    securityfile.close();
    system("pause");
    system("cls");

    ifstream lockedfile(LOCKED_FILE);
    string liness;
    cout << "冻结账户如下：" << endl;
    while (getline(lockedfile, liness)) {
        cout << liness << endl;
    }

    lockedfile.close();
    system("pause");
    system("cls");

    cout << "请输入需要解冻操作账户(输入0退出)" << endl;
    string unlockedusername;
    while (1) {
        if (unlockedusername == "0") break;
        cin >> unlockedusername;
        unlockedAccount(unlockedusername);
    }
    system("pause");
    system("cls");
}



