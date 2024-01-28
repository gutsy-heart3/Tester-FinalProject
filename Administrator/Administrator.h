#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;

string root = "../files/";

class InfoAdmin {
protected:
	string fullName;
	string email;
	string login;
	string password;
public:
	InfoAdmin() : fullName(""), email(""), login(""), password("")
	{}
	virtual void registration() = 0;
	virtual void authorization() = 0;
	virtual void encrypt(string& log, string pass) = 0;
	virtual ~InfoAdmin() = 0 {};
};

class Admin : public InfoAdmin
{
public:
	Admin() {}
	// osushitvlayet vxod libo registraciyu
	void AdminMenu() {
		CheckAdminAccount();
		registration();
	};

	void registration() override {
		cout << "Enter your full name: ";
		getline(cin >> ws, fullName);
		cout << "Enter your email: ";
		getline(cin >> ws, email);
		cout << "Enter your login: ";
		cin >> login;
		cout << "Enter your password: ";
		cin >> password;
		writeAdminData(login);
		writeAdminLogPass(login, password);
		authorization();
	}
	void authorization() override {
		char choice{};
		cout << "Login: ";
		getline(cin >> ws, login);
		
		cout << "Password: ";
		getline(cin >> ws, password);
		
		if (IsPasswordCorrect(login, password)) {
			cout << "Welcome Admin " << fullName << endl;
			encrypt(login, password);
			cout << "If you want to change your login or password (y/n)?: ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				ChangeLogPass();
				system("pause");
				system("cls");
			}
			else {
				system("pause");
				system("cls");
				return;
			}
		}
		else {
			cout << "Incorrect login or password!" << endl;
			system("pause");
			system("cls");
			return authorization();
		}
	}

	// metod
	void checkWork() {
		return CheckAdminAccount();
	}
	// proverka parol
	bool IsPasswordCorrect(const string& login, const string& enteredPass) {
		ifstream fileLog(root + "adminLog.dat", ios::in);
		ifstream filePass(root + "adminPass.dat", ios::in);
		if (fileLog.is_open() && filePass.is_open()) {
			string existingLogin;
			string existingPass;
			while (fileLog >> existingLogin && filePass >> existingPass)
			{
				if (login == existingLogin && enteredPass == existingPass) {
					fileLog.close();
					filePass.close();
					return true;
				}
			}
			fileLog.close();
			filePass.close();
		}
		return false;
	}
	// smena log i pass
	void ChangeLogPass() {
		readAdminLogPass();
		string log, pass;
		cout << "Enter new login: ";
		cin >> log;
		cout << "Enter new password: ";
		cin >> pass;
		updateData(log, pass);
	}
	void updateData(const string& newLog, const string& newPass) {
		writeAdminData(newLog);
		writeAdminLogPass(newLog, newPass);
	}
	// shifr
	void encrypt(string& log, string pass) override {
		for (char& ch : login) {
			ch = static_cast<char>(ch + 1);
		}
		for (char& ch : pass) {
			ch = static_cast<char>(ch + 1);
			ch = '*';
		}
		cout << "Encrypt login: " << log << endl;
		cout << "Encrypt password: " << pass << endl;
	}
	// zapis vsex dannix
	void writeAdminData(const string& login) {
		ofstream file(root + "adminData.dat", ios::out | ios::app);
		if (file.is_open()) {
			file << "Full Name: " << fullName << endl;
			file << "E-mail: " << email << endl;
			file << "Login: " << login << endl;
			file << "Password: " << password << endl;
		}
		file.close();
	}
	// chteniye dannix
	void readAdminData() {
		ifstream file(root + "adminData.dat", ios::in);
		if (file.is_open()) {
			string fullname, email, login, password;
			while (file >> fullName && file >> email && file >> login && file >> password) {
				cout << "Full Name: " << fullname << endl;
				cout << "E-mail: " << email << endl;
				cout << "Login: " << login << endl;
				cout << "Password: " << password << endl;
			}
		}
		file.close();
	}
	// zapis log i pass
	void writeAdminLogPass(const string& login, const string& password) {
		ofstream fileLog(root + "adminLog.dat", ios::out | ios::app);
		ofstream filePass(root + "adminPass.dat", ios::out | ios::app);
		if (fileLog.is_open() && filePass.is_open()) {
			fileLog << "-----------------------------------" << endl;
			fileLog << "Login: " << login << endl;
			fileLog << "-----------------------------------" << endl;
			filePass << "-----------------------------------" << endl;
			filePass << "Password: " << password << endl;
			filePass << "-----------------------------------" << endl;
		}
		fileLog.close();
		filePass.close();
	}
	// chteniye log i pass
	void readAdminLogPass() {
		ifstream fileLog(root + "adminLog.dat", ios::in);
		ifstream filePass(root + "adminPass.dat", ios::in);
		if (fileLog.is_open() && filePass.is_open()) {
			string log;
			string pass;
			while (fileLog >> log && filePass >> pass) {
				cout << "Login: " << log << ", Password: " << pass << endl;
			}
		}
		fileLog.close();
		filePass.close();
	}
	// proverka nalicii admina
	void CheckAdminAccount() {
		ifstream file(root + "adminLog.dat", ios::in);
		if (file.is_open()) {
			string storedLogin;
			string storedPassword;
			file >> storedLogin >> storedPassword;
			if (!file.fail()) {
				return authorization();
			}
			else {
				return registration();
			}
			file.close();
		}
		system("pause");
	}
	~Admin()
	{}
};

class AdminFeatures : public Admin
{
public:
	// tut budet 3 kateqorii kotoriye mojet sdelat admin
	AdminFeatures() {}

	// dobavleniye polzovatelya
	void addUser() {
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		cout << "Enter the full name of the user: ";
		cin.ignore();
		getline(cin, fullName);
		cout << "Enter the home adress of the user: " << homeAdress << endl;
		cin.ignore();
		getline(cin, homeAdress);

		cout << "Enter the phone number of the user: ";
		cin >> phoneNumber;
		cout << "Enter the login of the user: ";
		cin >> usLogin;
		cout << "Enter the password of the user: ";
		cin >> usPass;
		ofstream outFile(root + "userData.txt", ios::out | ios::app);

		if (outFile.is_open()) {
			outFile << usLogin << endl;
			outFile << usPass << endl;
			outFile << fullName << endl;
			outFile << homeAdress << endl;
			outFile << phoneNumber << endl;
			cout << "-------------------------------" << endl;
			cout << "User added successfully!" << endl;
		}
		outFile.close();
	}
	// udaleniye polzovatelya
	void deleteUser() {
		int ch{};
		ifstream file(root + "userData.txt", ios::in);
		if (!file.is_open()) {
			cout << "Unable to open the files." << endl;
			return;
		}
		vector<string> userEnter;
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		while (file >> fullName && file >> homeAdress && file >> phoneNumber && file >> usLogin && file >> usPass) {
			cout << "User " << userEnter.size() + 1 << ':' << endl;
			cout << "Login: " << usLogin << endl;
			cout << "Password: " << usPass << endl;
			cout << "Full Name: " << fullName << endl;
			cout << "Home adress: " << homeAdress << endl;
			cout << "Phone number: " << phoneNumber << endl;
			userEnter.push_back(fullName + " " + homeAdress + " " + phoneNumber + " " + usLogin + " " + usPass);
		}
		file.close();
		if (userEnter.empty()) {
			cout << "Not found users." << endl;
			return;
		}
		cout << "Select user for delete: ";
		cin >> ch;
		if (ch >= 1 && ch <= userEnter.size()) {
			userEnter.erase(userEnter.begin() + ch - 1);
			ofstream fileOut(root + "userData.txt", ios::out | ios::trunc);
			if (fileOut.is_open()) {
				for (const string& enter : userEnter) {
					fileOut << enter << endl;
				}
				fileOut.close();
				cout << "User is deleted!" << endl;
			}
		}
		else {
			cout << "Unable to open the files." << endl;
			return;
		}
	}
	// modifikaciya polzovatelya
	void userModification() {
		// smenit login i parol
		int ch{};
		ifstream file(root + "userData.txt", ios::in);
		if (!file.is_open()) {
			cout << "Unable to open the files." << endl;
			return;
		}
		vector<string> userEnter;
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		while (file >> fullName && file >> homeAdress && file >> phoneNumber && file >> usLogin && file >> usPass) {
			cout << "User " << userEnter.size() + 1 << ':' << endl;
			cout << "Login: " << usLogin << endl;
			cout << "Password: " << usPass << endl;
			cout << "Full Name: " << fullName << endl;
			cout << "Home adress: " << homeAdress << endl;
			cout << "Phone number: " << phoneNumber << endl;
			userEnter.push_back(fullName + " " + homeAdress + " " + phoneNumber + " " + usLogin + " " + usPass);
		}
		file.close();
		if (userEnter.empty()) {
			cout << "Not found users." << endl;
			return;
		}
		cout << "Select user: ";
		cin >> ch;
		if (ch >= 1 && ch <= userEnter.size()) {
			cout << "Enter the new login of the user: ";
			cin >> usLogin;
			cout << "Enter the new password of the user: ";
			cin >> usPass;

			userEnter[ch - 1] = usLogin + " " + usPass + fullName + " " + homeAdress + " " + phoneNumber;

			ofstream outFile(root + "userData.txt", ios::out | ios::trunc);

			if (outFile.is_open()) {
				for (const string& enter : userEnter) {
					outFile << enter << endl;
				}
				outFile.close();
				cout << "User is modified!" << endl;
			}
		}
	}
	// statistika 
	void displayStatisResults() {
		int ch{};
		string line, log;
		cout << "1. Show statistic by users." << endl;
		cout << "2. Show statistic by chapter." << endl;
		cout << "3. Show all statistic information." << endl;
		cout << "Select choice: ";
		cin >> ch;

		switch (ch) {
		case 1:
			// Show statistic by users
		{
			cout << "Enter the login of user: ";
			cin >> log;  // Fix: use the correct variable name 'log'
			ifstream fileResult(root + "resultStudents.txt", ios::in);
			if (fileResult.is_open()) {
				while (getline(fileResult, line)) {
					if (line.find("Login: " + log) != string::npos) {  // Fix: use the correct variable name 'log'
						cout << line << endl;
						while (getline(fileResult, line) && line != "") {
							cout << line << endl;
						}
						break;
					}
				}
				fileResult.close();
			}
			else {
				cout << "Error: Unable to open the file." << endl;
				return;
			}
		}
		break;
		case 2:
			// Show statistic by chapter
		{
			ifstream fileChapter(root + "chapters.txt", ios::in);
			if (fileChapter.is_open()) {
				string chapter;
				while (getline(fileChapter, chapter)) {
					cout << chapter << endl;

					ifstream fileResult(root + "resultStudents.txt", ios::in);
					if (fileResult.is_open()) {
						bool foundChapter = false;
						while (getline(fileResult, line)) {
							if (line.find("Chapter: " + chapter) != string::npos) {
								foundChapter = true;
								cout << line << endl;
								while (getline(fileResult, line) && line != "") {
									cout << line << endl;
								}
								break;
							}
						}
						fileResult.close();

						if (!foundChapter) {
							cout << "No statistics found for this chapter." << endl;
						}
					}
					else {
						cout << "Error: Unable to open the file." << endl;
						return;
					}
					cout << "--------------------------" << endl;
				}
				fileChapter.close();
			}
			else {
				cout << "Error: Unable to open the file." << endl;
				return;
			}
		}
		break;
		case 3:
			// Show all statistic information
		{
			ifstream fileResult(root + "resultStudents.txt", ios::in);
			if (fileResult.is_open()) {
				while (getline(fileResult, line)) {
					cout << line << endl;
				}
				fileResult.close();
			}
			else {
				cout << "Error: Unable to open the file." << endl;
				return;
			}
		}
		break;
		default:
			cout << "Invalid choice." << endl;
		}
	}

	// dobavleniye voprosov i otvetov
	void ManipulateTesting() {
		// pokaz i dobavleniye chapterov
		ifstream cpFile(root + "chapters.txt", ios::in);
		char choice{};
		if (cpFile.is_open()) {
			string cp;
			while (getline(cpFile, cp)) {
				cout << cp << endl;
			}
			cpFile.close();
		}
		cout << "Do you want to add chapter(y/n)?: ";
		cin >> choice;
		if (choice == 'y' || choice == 'y') {
			string newChapter;
			cout << "Enter the chapter: ";
			cin >> newChapter;
			ofstream chapteFile(root + "chapters.txt", ios::out | ios::app);
			if (chapteFile.is_open()) {
				cout << '\n';
				chapteFile << newChapter << endl;
				chapteFile.close();
			}
		}
		else {
			return;
		}

		// dobavleniye voprosov i otvetov
		char choice2{};
		cout << "Do you want to add questions and answers (y/n)?: ";
		cin >> choice2;

		if (choice2 == 'y' || choice2 == 'Y') {
			string newQuestions, newAnswers;
			cout << "Enter the name of file for questions (.txt): ";
			cin >> newQuestions;
			cout << "Enter the name of file for answers (.txt): ";
			cin >> newAnswers;
			ofstream fileQ(root + newQuestions, ios::out | ios::app);
			ofstream fileA(root + newAnswers, ios::out | ios::app);

			if (fileQ.is_open() && fileA.is_open()) {
				const int maxQuestions = 12;
				//cout << "Enter up to " << maxQuestions << " questions. Press Enter after each question." << endl;
				for (int i = 0; i < maxQuestions; ++i) {
					string question, answer;
					cout << "Question " << i + 1 << ": ";
					getline(cin >> ws, question);
					fileQ << question << endl;
					cout << "Correct answer: ";
					getline(cin >> ws, answer);
					fileA << answer << endl;
				}
				cout << "Questions and answers added successfully!" << endl;
				fileQ.close();
				fileA.close();
			}
			else {
				cout << "Unable to open the file for writing." << endl;
			}
		}
		else {
			return;
		}
	}

	// osnovnoy menu
	void CategoryMenu() {
		CheckAdminAccount();
		while (true) {
			short choice;
			cout << "Welcome Admin!" << endl;
			cout << "1. Change your login or password." << endl;
			cout << "2. Add users." << endl;
			cout << "3. Delete users." << endl;
			cout << "4. User modification." << endl;
			cout << "5. Display statistics." << endl;
			cout << "6. Add chapter and test." << endl;
			cout << "7. Exit." << endl;
			cout << "Enter your choice: ";
			cin >> choice;  
			system("pause");
			system("cls");
			switch (choice) {
			case 1:
				ChangeLogPass();
				system("pause");
				break;
			case 2:
				addUser();
				system("pause");
				break;
			case 3:
				deleteUser();
				system("pause");
				break;
			case 4:
				userModification();
				system("pause");
				break;
			case 5:
				displayStatisResults();
				system("pause");
				break;
			case 6:
				ManipulateTesting();
				system("pause");
				break;
			case 7:
				cout << "Goodbye!" << endl;
				exit(0);
			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	}
	~AdminFeatures()
	{}
};