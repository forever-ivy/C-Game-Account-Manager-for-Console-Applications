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

//�˵�����
void Gamer::operMenu(){
	cout << "��ӭ�û���" << this->username << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴�ҵ�װ��          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.����װ��              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

int Gamer::alidatePassword(string name, string pwd, string fileName)
{
    // �����˻��Ƿ�����
    ifstream lockFile(LOCKED_FILE, ios::in);
    string lockedLine;
    while (getline(lockFile, lockedLine)) {
        if (lockedLine == "username:" + name) {
            cout << "���˻��ѱ����ᣬ�޷���¼��" << endl;
            return 3; // ��ʾ�˻��ѱ�����
        }
    }
    lockFile.close();
    
    
    if (this->security.CheckLoginAttemptsAndLock(name)) {
        cout << "�˻����������������������Σ��˻�����" << endl;
        this->security.lockAccount(name);
        return 3;
    }

    ifstream ifs(fileName, ios::in);
	string fName, fPwd,type;
	while (ifs >> fName >> fPwd>>type) {
		if (fName == name) {
			if (fPwd == md5(pwd)&&type=="GAMER") {
				return 2; // ��¼�ɹ�
			}
			else {
				return 1; // �������
			}
		}
     
	}
	return 0; // �û���������
}

void Gamer::showequipment() {


	// �û������ļ�·��
	string filepath = "user_data/" + this->username + ".txt";
	ifstream file(filepath);
	if (!file.is_open()) {
        cout << "�޷����û�װ���ļ�: " << filepath << endl;
		return;
	}

	string line;
	int lineCount = 0;
	bool show = false;

	cout << "��" << this->username << " ��װ���б�" << endl;

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
    equiment_store.clear();  // ��վɼ�¼
    string line;
    while (getline(storeFile, line)) {
        stringstream ss(line);
        int index;
        int price;
        string name, token;
        

        ss >> index;
        ss.ignore(2);  // ���� ". "

        while (ss >> token) {
            if (token[0] == '$') {
                price = stoi(token.substr(1));//���ַ���תΪ����
                break;
            }
            if (!name.empty()) name += " ";//name ���Ѿ������ݣ��ǿ��ַ�����������ԭ��ʽ
            name += token;
        }

        equiment_store.push_back(make_tuple(index, name, price));
    }
    storeFile.close();

    UINT orignalCP = GetConsoleCP();


    cout << "��װ���̵꡿" << endl;

  
    for (auto& item : equiment_store) {
        cout << get<0>(item) << ". " << get<1>(item) << " - $" << get<2>(item) << endl;
    }
 

    cout << "�˻���$" << money << endl;
    cout << "��������Ҫ�����װ����ţ�0��������" << endl;

    // ��ȡ�û������ļ�·��
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
            cout << "�����Ч�����������롣" << endl;
            continue;
        }

        string itemName = get<1>(equiment_store[select - 1]);
        int itemPrice = get<2>(equiment_store[select - 1]);


 
        if (find(ownedEquipment.begin(), ownedEquipment.end(), itemName) != ownedEquipment.end()) {
            cout << "����ӵ�и�װ�����޷��ظ�����" << endl;
            continue;
        }

        if (money < itemPrice) {
            cout << "���㣬�޷����� " << itemName << endl;
            continue;
        }


        money -= itemPrice;
        ownedEquipment.push_back(itemName);


       
        cout << "�ɹ�����" << itemName << "��ʣ����$" << money << endl;
        SetConsoleCP(orignalCP);
    }

    // �����ļ�����
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



