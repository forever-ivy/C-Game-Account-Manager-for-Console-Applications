#include"SecurityModule .h"

void SecurityModule::unlockedAccount(const string& name) {
    // ɾ�� locked.txt �е��˻�
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

    //ɾ�� log.txt �и��˻������м�

    ifstream logIn(SCUL_FILE);//����һ�� ifstream �����ļ������� logIn
    ofstream logOut("temp_security.txt");//����һ�� ofstream ����ļ������� logOut
    while (getline(logIn, line)) {
        if (line.find(name + " ") != 0) { // ����Ƿ��Ǹ��˻��ļ�¼
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
    cout << "��¼��־�������£�" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    system("pause");
    system("cls");

}

void SecurityModule::lockAccount(const string& name) {
	ofstream outFile(LOCKED_FILE, ios::app); // ��׷��ģʽ��
	if (outFile.is_open()) {
		outFile<<"username:" << name << endl;
		outFile.close();
	}
}

bool SecurityModule::CheckLoginAttemptsAndLock(const string& name) {

	ifstream file(SCUL_FILE);
	
	// ��ȡ����������ַ�����ֻ���������գ�
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char today[20];
	strftime(today, sizeof(today), "%a %b %d", ltm); //ȷ����ʽ

	int failCount = 0;
	string line;

	while (getline(file, line)) {
		// �ж��Ƿ��Ը��û�����ͷ
		if (line.find(name + " ") == 0) {
			// �ж������Ƿ��ǽ���
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
    cout << "�Ƿ���¼��־���£�" << endl;
    while (getline(securityfile, lines)) {
        cout << lines << endl;
    }

    securityfile.close();
    system("pause");
    system("cls");

    ifstream lockedfile(LOCKED_FILE);
    string liness;
    cout << "�����˻����£�" << endl;
    while (getline(lockedfile, liness)) {
        cout << liness << endl;
    }

    lockedfile.close();
    system("pause");
    system("cls");

    cout << "��������Ҫ�ⶳ�����˻�(����0�˳�)" << endl;
    string unlockedusername;
    while (1) {
        if (unlockedusername == "0") break;
        cin >> unlockedusername;
        unlockedAccount(unlockedusername);
    }
    system("pause");
    system("cls");
}



