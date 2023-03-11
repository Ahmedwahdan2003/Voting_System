#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct account {
	string username;
	string pass;
};


struct voter {
	int id;
	account voteraccount;
	string email;
	string address;
    int phone;
	int code;
}voter[20];


struct admin {

	int id;
	account adminaccount;
	string email;
	string address;
	int phone;
	int election_ids[10];
}admin[20];


struct election {
	int id;
	string name;
	string description;
	string nominees[10];
	int votes[10];
	int allowed_voters_code[10];
}election[20];
int acctype;//1<voter> 2<admin>
int voterindex;//to save his index throughout the program//
int adminindex;//to save his index throughout the program//
int firstmenu();
void readvoters();
void readadmins();
void readelections();
void readfromfiles();
bool loginvoter();
bool loginadmin();
void registervoter();
void registeradmin();
int mainmenu();
void votermenu();
void adminmenu();
void test();
int main()
{
	readfromfiles();
	mainmenu();
	
}
int firstmenu() {
	system("CLS");
	int option;
	cout << "\t\t\t\t\t*******************************\n";
	cout << "\t\t\t\t\t*****";
	cout << "WELCOME TO VOTING.COM*****\t\t\t\t \n";
	cout << "\t\t\t\t\t*******************************\n\n\n";
	cout << " \t\t <1-voter>  \t\t\t  <2-adminstrator> \t\t\t <3-Exit>\n\n\n ";
	cin >> option;
	return option;
}
int mainmenu()
{
	system("CLS");
	
	int ans;
	bool verified;
	while (true) {
		int x = firstmenu();
		switch (x) {
		case 1:
			cout << " \t\t <1-Login>  \t\t\t\t\t\t <2-Register>\n\n\n ";
			cin >> ans;
			switch (ans) {
			case 1:
				verified = loginvoter();
				if (!verified)
					continue;
				else
					votermenu();
				continue;
			case 2:
				registervoter();
				continue;
			default:cout << "Invalid choise please try again...\n";
				continue;
			}

		case 2:
			    cout << " \t\t <1-Login>  \t\t\t\t\t\t <2-Register>\n\n\n ";
			    cin >> ans;
			    switch (ans) {
			    case 1:
				verified = loginadmin();
				if (!verified)
					continue;
				else
					adminmenu();
				continue;
			    case 2:
				registeradmin();
				continue;
			    default:cout << "Invalid choise please try again...\n";
				continue;
			    }

		case 3:cout << "Thank you for choosing voting.com goodbye...\n\n";
			return 0;
		default:cout << "Invalid choise please try again...\n";
			continue;
		}
	}
}
void readfromfiles() {
	readvoters();
	readadmins();
	readelections();
}
void readadmins()
{
	int count = 0;
	fstream input;
	input.open("admins.txt");
	while (input.good()) {
		input >> admin[count].id;
		input >> admin[count].adminaccount.username;
		input >> admin[count].adminaccount.pass;
		input >> admin[count].email;
		input >> admin[count].address;
		input >> admin[count].phone;
		for (int i = 0; i < 3; ++i)
			input >> admin[count].election_ids[i];
		count++;
	} 
	input.close();
}
void readvoters()
{
	int count = 0;
	fstream input;
	input.open("text.txt");
	while (input.good()) {
		input >> voter[count].id;
		input >> voter[count].voteraccount.username;
		input >> voter[count].voteraccount.pass;
		input >> voter[count].email;
		input >> voter[count].address;
		input >> voter[count].phone;
		input >> voter[count].code;
		count++;
	}
	input.close();
}
void readelections()
{
	int count = 0;
	fstream input;
	input.open("elections.txt");
	while (input.good()) {
		input >> election[count].id;
		input >> election[count].name;
		getline(input, election[count].description);
		for(int i=0;i<2;++i)
		input >> election[count].nominees[i];
		for(int j=0;j<3;j++)
		input >> election[count].votes[j];
		for (int k = 0; k < 3; ++k)
			input >> election[count].allowed_voters_code[k];
		count++;
	}
	input.close();
}
bool loginvoter()
{
	system("CLS");
	string username;
	string password;
	char ans;
	int i = 0;
	do
	{
		cout << "Enter Your Username please\n";
		cin >> username;
		cout << "Enter Your password\n";
		cin >> password;
		for (i = 0; i < 20; ++i) {
			if (voter[i].voteraccount.username == username && voter[i].voteraccount.pass == password) {
				voterindex = i;
				return true;
			}

		}
		i = 0;
		cerr << "Wrong username or password. Do you want to try again?(Y/N)\n";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
	return false;
}

bool loginadmin()
{
	system("CLS");
	string username;
	string password;
	char ans;
	int i = 0;
	do
	{
		cout << "Enter Your Username please\n";
		cin >> username;
		cout << "Enter Your password\n";
		cin >> password;
		while (!admin[i].adminaccount.username.empty()) {
			if (admin[i].adminaccount.pass == password && admin[i].adminaccount.username == username)
			{
				adminindex = i;
				return true;
			}
			i++;
		}
		i = 0;
		cerr << "Wrong username or password. Do you want to try again?(Y/N)\n";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
	return false;
}
void registervoter()
{
	system("CLS");
	int i = 0;
	while (!voter[i].voteraccount.username.empty())
		i++;
		cout << "Enter your ID\n";
		cin >> voter[i].id;
		cout << "Enter your Username\n";
		cin >> voter[i].voteraccount.username;
		cout << "Enter your password\n";
		cin >> voter[i].voteraccount.pass;
		cout << "Enter your Email\n";
		cin >> voter[i].email;
		cout << "Enter your Address\n";
		cin >> voter[i].address;
		cout << "Enter your phone number\n";
		cin >> voter[i].phone;
		cout << "Enter your voting code\n";
		cin >> voter[i].code; cout << endl << endl << endl;
		cout << "THANK YOU FOR REGISTERING..REDIRECTING YOU NOW\n";
		//cout << voter[i].voteraccount.username << "   " << voter[i].voteraccount.pass;
		//Sleep(2000);
		//firstmenu();
}

void registeradmin()
{
	system("CLS");
	int numberofid;
	int i = 0;
	while (!admin[i].adminaccount.username.empty())
		i++;
	cout << "Enter your ID\n";
	cin >> admin[i].id;
	cout << "Enter your Username\n";
	cin >> admin[i].adminaccount.username;
	cout << "Enter your password\n";
	cin >> admin[i].adminaccount.pass;
	cout << "Enter your Email\n";
	cin >> admin[i].email;
	cout << "Enter your Address\n";
	cin >> admin[i].address;
	cout << "Enter your phone number\n";
	cin >> admin[i].phone;
	cout << "how many election ids do you have?\n";
	cin >> numberofid;
	for (int j = 0; j < numberofid; ++j) {
		cout << "enter the  " << j + 1 << "  id";
		cin >> admin[i].election_ids[j];
	}
	cout << endl << endl << endl;
	cout << "THANK YOU FOR REGISTERING..REDIRECTING YOU NOW\n";
	//Sleep(2000);
	//firstmenu();
}

void votermenu() {
	system("CLS");
	int choice;
	while (true) {
		cout << "\t\t\t\t\t*******************************\n";
		cout << "\t\t\t\t\t*****";
		cout << "VOTERS MENU****\t\t\t\t \n";
		cout << "\t\t\t\t\t*******************************\n\n\n";
		cout << "\t\t\t<1-editinfo>\t\t\t\t<2-back to main menu>\n\n";
		cin >> choice;
		switch (choice) {
		case 1:  test();
			     break;
		case 2:
			break;
		}
		break;
	}

}
void adminmenu() {
	int x;
	cout << "welcome to admin menu\n";
	cin >> x;
	if (x == 2)
		test();
}
void test()
{
	cout << "Hello\n\n\n";

}



