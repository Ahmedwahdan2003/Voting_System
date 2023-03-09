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

void readvoters();
void readadmins();
void readelections();
void readfromfiles();
bool loginvoter();
bool loginadmin();
void registervoter();
void registeradmin();
int main()
{
	readfromfiles();
	cout << election[0].id << " " << election[0].description << " "<<endl;
	for (int i = 0; i < 2; i++)
		cout << election[0].allowed_voters_code[i] << "   " << election[0].nominees[i];




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
		for(int k=0;k<3;++k)
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
		while (!voter[i].voteraccount.username.empty()) {
			if (voter[i].voteraccount.pass == password && voter[i].voteraccount.username == username)
				return true;
			i++;
		}
		i = 0;
		cerr << "Wrong username or password. Do you want to try again?(Y/N)\n";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
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
				return true;
			i++;
		}
		i = 0;
		cerr << "Wrong username or password. Do you want to try again?(Y/N)\n";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
}
void registervoter()
{
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
		cin >> voter[i].code;
}

void registeradmin()
{
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
}






