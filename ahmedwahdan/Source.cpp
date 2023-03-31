#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
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
	bool end = false;
	bool finished = true;
}election[20];

static int voterindex;//to save his index throughout the program//
static int adminindex;//to save his index throughout the program//
static int electionindex;
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
void editinfoadmin();
void createvote();
void deletevote();
void switchacc();
void editidadmin();
void editusernameadmin();
void editpassadmin();
void editemailadmin();
void editaddressadmin();
void editphonenoadmin();
void listofvotes();
void editinfovoter();
void editidvoter();
void editusernamevoter();
void editpassvoter();
void editemailvoter();
void editaddressvoter();
void editphonenovoter();
void endvote();
void winner();
void leadingnominee();
void vote();
int main()
{

readfromfiles();
	election[0].id = 24;
	election[0].name = "ahmd";
	election[0].description = "4444";
	election[0].nominees[0] = "abdelatif";
	election[0].nominees[1] = "rahaf";
	election[0].votes[0] = 10;
	election[0].votes[1] = 5;
	election[0].allowed_voters_code[0] = 11;
	election[0].allowed_voters_code[1] = 11;
	election[0].finished = false;
	election[1].id = 24;
	election[1].name = "ahmed";
	election[1].description = "aaaaaaa";
	election[1].nominees[0] = "abdelatif";
	election[1].nominees[1] = "rahaf";
	election[1].votes[0] = 20;
	election[1].votes[1] = 21;
	election[1].allowed_voters_code[0] = 11;
	election[1].allowed_voters_code[1] = 11;
	election[1].finished = true;
	
	mainmenu();
}
int firstmenu() {
	system("CLS");
	int option;
	cout << "\t\t\t\t\t\t***\n";
	cout << "\t\t\t\t\t***";
	cout << "WELCOME TO VOTING.COM***\t\t\t\t\n";
	cout << "\t\t\t\t\t\t***\n\n\n";
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
	input.open("voters.txt");
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
	/*int count = 0;
	fstream input;
	input.open("elections.txt");
	while (input.good()) {
		input >> election[count].id;
		input >> election[count].name;
		getline(input, election[count].description);
		for (int i = 0; i < 2; ++i)
			input >> election[count].nominees[i];
		for (int j = 0; j < 2; j++)
			input >> election[count].votes[j];
		for (int k = 0; k < 2; ++k)
			input >> election[count].allowed_voters_code[k];
		count++;
	}
	input.close();*/
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
}

void votermenu()
{
	char answer;
	while (true) {
		int ans;
		system("CLS");
		cout << "\t\t\t\t\t *\n";
		cout << "\t\t\t\t\t***";
		cout << "VOTERS MENU**\t\t\t\t \n";
		cout << "\t\t\t\t\t *\n\n\n";
		cout << "what do you want to do ?" << endl;
		cout << "1-edit information\t\t\t" << "2-show list of votes you have access to \t\t\t" << "3-logout \t\t\t";
		cout << endl;
		cin >> ans;

		switch (ans)
		{
		case 1: editinfovoter(); cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 2: listofvotes(); cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 3:
			break;

		}
		break;
	}
}
void adminmenu()
{
	while (true) {
		system("CLS");
		cout << "\t\t\t\t\t *\n";
		cout << "\t\t\t\t\t***";
		cout << "ADMINS MENU***\t\t\t\t \n";
		cout << "\t\t\t\t\t *\n\n\n";
		int ans;
		cout << "what do you want to do ?" << endl;
		cout << "1-edit information\t\t" << "2-create vote\t\t" << "3-delete vote\t\t" << "4-logout\t\t" << "5-switch account\t\t" << " 6-end vote\t\t";
		cout << endl;
		cin >> ans;

		switch (ans)
		{
		case 1: editinfoadmin();
			cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 2: createvote();  cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 3: deletevote();  cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 4:
			break;
		case 5: switchacc();
			continue;
		case 6: endvote();
			continue;
		}
		break;

	}

}
void editinfoadmin()
{
	system("CLS");
	int ans;
	cout << "what do you want to edit ?" << endl;
	cout << "1-id\t\t" << "2-username\t\t" << "3-password\t\t" << "4-email\t\t" << "5-address\t\t" << "6-phone no.\t\t";
	cout << endl;
	cin >> ans;
	switch (ans)
	{
	case 1: editidadmin();
		break;
	case 2: editusernameadmin();
		break;
	case 3: editpassadmin();
		break;
	case 4:editemailadmin();
		break;
	case 5: editaddressadmin();
		break;
	case 6: editphonenoadmin();
		break;
	}
}
void editidadmin()
{
	system("CLS");
	int oldid;
	int newid;
	do
	{
		cout << "enter old id : ";
		cin >> oldid;
		if (oldid == admin[adminindex].id)
		{
			cout << "enter new id :";
			cin >> newid;
			admin[adminindex].id = newid;
			cout << "id changed successfully" << endl;
			break;
		}
		else cout << "wrong id ";
	} while (true);
}
void editusernameadmin()
{
	system("CLS");
	string oldusername;
	string newusername;
	do
	{
		cout << "enter old username :";
		cin >> oldusername;
		if (oldusername == admin[adminindex].adminaccount.username)
		{
			cout << "enter new username :";
			cin >> newusername;
			admin[adminindex].adminaccount.username = newusername;
			cout << "username changed successfully" << endl;
			break;
		}
		else cout << "wrong username ";
	} while (true);
}
void editpassadmin()
{
	system("CLS");
	string oldpass;
	string newpass;
	do
	{
		cout << "enter old password :";
		cin >> oldpass;
		if (oldpass == admin[adminindex].adminaccount.pass)
		{
			cout << "enter new password :";
			cin >> newpass;
			admin[adminindex].adminaccount.pass = newpass;
			cout << "password changed successfully " << endl;
			break;
		}
		else cout << "wrong password ";
	} while (true);
}
void editemailadmin()
{
	system("CLS");
	string oldemail;
	string newemail;
	do
	{
		cout << "enter old e-mail :";
		cin >> oldemail;
		if (oldemail == admin[adminindex].email)
		{
			cout << "enter new e-mail :";
			cin >> newemail;
			admin[adminindex].email = newemail;
			cout << "email changed successfully" << endl;
			break;
		}
		else cout << "wrong e-mail ";
	} while (true);
}
void editaddressadmin()
{
	system("CLS");
	string oldaddress;
	string newaddress;
	do
	{
		cout << "enter old address :";
		cin >> oldaddress;
		if (oldaddress == admin[adminindex].address)
		{
			cout << "enter new address :";
			cin >> newaddress;
			admin[adminindex].address = newaddress;
			cout << "address changed successfully " << endl;
			break;
		}
		else cout << "wrong address ";
	} while (true);

}
void editphonenoadmin()
{
	system("CLS");
	int oldphoneno;
	int newphoneno;
	do
	{
		cout << "enter old phone number :";
		cin >> oldphoneno;
		if (oldphoneno == admin[adminindex].phone)
		{
			cout << "enter new phone number :";
			cin >> newphoneno;
			admin[adminindex].phone = newphoneno;
			cout << "phone number changed successfully" << endl;
			break;
		}
		else cout << "wrong phone number ";
	} while (true);
}

void editinfovoter()
{
	system("CLS");
	int ans;
	cout << "what do you want to edit ?" << endl;
	cout << "1-id\t\t" << "2-username\t\t" << "3-password\t\t" << "4-email\t\t" << "5-address\t\t" << "6-phone no.\t\t";
	cout << endl;
	cin >> ans;
	switch (ans)
	{
	case 1: editidvoter();
		break;
	case 2: editusernamevoter();
		break;
	case 3: editpassvoter();
		break;
	case 4:editemailvoter();
		break;
	case 5: editaddressvoter();
		break;
	case 6: editphonenovoter();
		break;
	}
}
void editidvoter()
{
	system("CLS");
	int oldid;
	int newid;
	do
	{
		cout << "enter old id : ";
		cin >> oldid;
		if (oldid == voter[voterindex].id)
		{
			cout << "enter new id :";
			cin >> newid;
			voter[voterindex].id = newid;
			cout << "id changed successfully" << endl;
			break;
		}
		else cout << "wrong id ";
	} while (true);
}
void editusernamevoter()
{
	system("CLS");
	string oldusername;
	string newusername;
	do
	{
		cout << "enter old username :";
		cin >> oldusername;
		if (oldusername == voter[voterindex].voteraccount.username)
		{
			cout << "enter new username :";
			cin >> newusername;
			voter[voterindex].voteraccount.username = newusername;
			cout << "username changed successfully" << endl;
			break;
		}
		else cout << "wrong username ";
	} while (true);
}
void editpassvoter()
{
	system("CLS");
	string oldpass;
	string newpass;
	do
	{
		cout << "enter old password :";
		cin >> oldpass;
		if (oldpass == voter[voterindex].voteraccount.pass)
		{
			cout << "enter new password :";
			cin >> newpass;
			voter[voterindex].voteraccount.pass = newpass;
			cout << "password changed successfully " << endl;
			break;
		}
		else cout << "wrong password ";
	} while (true);
}
void editemailvoter()
{
	system("CLS");
	string oldemail;
	string newemail;
	do
	{
		cout << "enter old e-mail :";
		cin >> oldemail;
		if (oldemail == voter[voterindex].email)
		{
			cout << "enter new e-mail :";
			cin >> newemail;
			voter[voterindex].email = newemail;
			cout << "email changed successfully" << endl;
			break;
		}
		else cout << "wrong e-mail ";
	} while (true);
}
void editaddressvoter()
{
	system("CLS");
	string oldaddress;
	string newaddress;
	do
	{
		cout << "enter old address :";
		cin >> oldaddress;
		if (oldaddress == voter[voterindex].address)
		{
			cout << "enter new address :";
			cin >> newaddress;
			voter[voterindex].address = newaddress;
			cout << "address changed successfully " << endl;
			break;
		}
		else cout << "wrong address ";
	} while (true);
}
void editphonenovoter()
{
	system("CLS");
	int oldphoneno;
	int newphoneno;
	do
	{
		cout << "enter old phone number :";
		cin >> oldphoneno;
		if (oldphoneno == voter[voterindex].phone)
		{
			cout << "enter new phone number :";
			cin >> newphoneno;
			voter[voterindex].phone = newphoneno;
			cout << "phone number changed successfully" << endl;
			break;
		}
		else cout << "wrong phone number ";
	} while (true);
}
void createvote()
{
	int i = 0;
	int num, n;
	while (!election[i].name.empty()) {
		i++;
	}
	cout << " enter your ID:\n";
	cin >> election[i].id;
	cout << " enter the election's name : \n";
	cin >> election[i].name;
	cout << " enter description :\n";
	cin >> election[i].description;
	cout << " How many nominees do you want?\n";
	cin >> num;
	for (int x = 0; x < num; x++)

	{
		cout << "enter name of nominee " << x + 1 << " :";
		cin >> election[i].nominees[x];
	}
	cout << "How many voter codes do you want?\n";
	cin >> n;
	for (int y = 0; y < n; y++) {
		cout << "enter voter code " << y + 1 << " :";
		cin >> election[i].allowed_voters_code[y];
	}

}
void deletevote()
{
	system("CLS");
	int ans;
	bool flag = false;
	for (int i = 0; i < 20; i++) {
		if (admin[adminindex].id == election[i].id)
		{
			flag = true;
			break;
		}
		else {
			flag = false;
			break;
		}
	}
	if (flag == false)
		cout << "SORRY YOU MUST CREATE A VOTE FIRST TO DELETE IT..\n";
	else {
		cout << "\t\t\t choose the vote you want to delete\n";
		for (int i = 0; i < 20; i++) {
			if (admin[adminindex].id == election[i].id) {
				cout << i + 1 << "- " << election[i].name << endl;
			}
			else
				continue;
		}
		cin >> ans;
		ans--;
		int j = 0;
		for (int i = ans; !election[j].name.empty(); i++) {
			election[i] = election[i + 1];
			j++;
		}
	}
}
void switchacc()
{
	bool flag = false;
	int i = 0;
	for (i = 0; i < 20; i++) {
		if (voter[i].id == admin[adminindex].id)
		{
			votermenu();
			flag = true;
			break;
		}
	}
	if (flag == false)
		cout << "sorry you dont have an account as a voter..";
	Sleep(1000);
}


void endvote()
{

	system("CLS");
	int ans;
	bool boolean = false;
	for (int i = 0; i < 20; i++) {
		if (!election[i].name.empty())
			boolean = true;
	}
	if (boolean == false) {
		cout << "YOU MUST CREATE A VOTE FIRST TO END IT\n";
		Sleep(1000);
	}
	else {
		cout << "choose the vote you want to end\n";
		int j = 1;
		for (int i = 0; i < 20; i++) {
			if (election[i].end == false && election[i].id == admin[adminindex].id) {
				cout << j << "- " << election[i].name << endl;
				j++;
			}
			else
				continue;
		}
		cin >> ans;
		ans--;
		for (int i = 0; i < 20; i++) {
			if (ans == i) {
				election[i].end = true;
			}
		}
		
	}
}
void listofvotes()
{
	int ans;
	system("cls");
	for (int i = 0; i < 20; i++)
	{
		if (voter[voterindex].code == election[i].allowed_voters_code[i])
		{

			cout << "- " << "(" << i << ")     " << election[i].name << "\n\n";
		}
	}
	cout << "Enter your Choice\n";
	cin >> ans;
	electionindex = ans;
	if (election[electionindex].finished == true)
	{
		cout << "this vote is finished";
		winner();
	}
	else {
		cout << election[electionindex].name<<endl;
		cout << election[electionindex].description <<"\n\n";
		cout <<"1- "<< election[electionindex].nominees[0] << "\t\t 2- " << election[electionindex].nominees[1] << endl;
		vote();
		leadingnominee();
	}

}
void vote()
{


	int nomineeno;
	cout << "\nenter number of nominee you want to vote for : ";
	cin >> nomineeno;
	election[electionindex].votes[nomineeno - 1]++;
	cout << "number of vote for " << election[electionindex].nominees[nomineeno - 1] << ": " << election[electionindex].votes[nomineeno - 1];

	Sleep(2000);


}


void leadingnominee()
{
	int leadingn = 1;
	int maxvotes = election[electionindex].votes[0];
	for (int j = 0; j < 10; j++)
		if (election[electionindex].votes[j] > maxvotes)
		{
			maxvotes = election[electionindex].votes[j];
			leadingn = j + 1;


		}
	cout << "\nthe leading nominee is : " << election[electionindex].nominees[leadingn - 1] << " nominee is leading with " << maxvotes << "votes " << "\n";


	Sleep(2000);

}
void winner()
{

	int max = 0;
	int winner=0;


	for (int i = 0; i < 2; i++)
	{
		if (election[electionindex].votes[i] > max)
		{
			max = election[electionindex].votes[i];
			winner = i + 1;
		}
		cout << "\nnumber of votes for nominee " << election[electionindex].nominees[i] << ": " << election[electionindex].votes[i];
	}
	cout << "\nthe winner is : " << election[electionindex].nominees[winner - 1]<<"\n\n\n";


	system("pause");

}