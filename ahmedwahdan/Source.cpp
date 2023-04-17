#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<Windows.h>
#include<algorithm>
using namespace std;
struct account {
	string username;
	string pass;
};
struct code {
	int code;
	bool voted = false;
};

struct voter {
	int id = 0;
	account voteraccount;
	string email;
	string address;
	int phone = 0;
	code code;
}voter[20];


struct admin {

	int id = 0;
	account adminaccount;
	string email;
	string address;
	int phone;
	int election_ids[5] = { 0 };
}admin[20];


struct election {
	int id = 0;
	string name;
	string description;
	string nominees[10];
	int votes[10] = { 0 };
	int allowed_voters_code[10] = {0};
	int no_allowed_voter_code;
	int no_ofnominees;
	bool end;


}election[20];
static int numberofid;
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
void winner(int electionindex);
void leadingnominee();
void vote();
void editelectioninfo();
void editelectionname(int index);
void editelectiondescription(int index);
void editelectionnominees(int index);
void editallowedvotercodes(int index);
void addnominee(int index);
void deletenominee(int index);
void addvotercode(int index);
void deletevotercode(int index);
void updateadmins();
void updatevoters();
void updatelection();
void updatefiles();
int main()
{

	readfromfiles();
	mainmenu();
	updatefiles();

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
		input >> voter[count].code.code;
		voter[count].code.voted = false;
		count++;
	}
	input.close();
}
void readelections()
{
	string id, noon, avc;
	string in,inn;
	int count = 0;
	fstream input;
	input.open("elections.txt");
	while (input.good()) {
		getline(input, id);
		election[count].id = stoi(id);
		getline(input, election[count].name);
		getline(input, election[count].description);
		getline(input, noon);
		election[count].no_ofnominees = stoi(noon);
		getline(input, avc);
		election[count].no_allowed_voter_code = stoi(avc);
		election[count].no_allowed_voter_code = stoi(avc);
		for (int i = 0; i < election[count].no_ofnominees; ++i)
			getline(input, election[count].nominees[i]);

		for (int h = 0; h < election[count].no_ofnominees; ++h)
		{
			getline(input, inn);
			election[count].votes[h] = stoi(inn);
		}

		for (int j = 0; j < election[count].no_allowed_voter_code; ++j)
		{
			getline(input, in);
			election[count].allowed_voters_code[j] = stoi(in);
		}
		election[count].end = false;
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
	cin >> voter[i].code.code; cout << endl << endl << endl;
	cout << "THANK YOU FOR REGISTERING..REDIRECTING YOU NOW\n";
	//cout << voter[i].voteraccount.username << "   " << voter[i].voteraccount.pass;
	//Sleep(2000);
	//firstmenu();
}

void registeradmin()
{
	system("CLS");

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
		cout << "1-edit information\t\t" << "2-create vote\t\t" << "3-delete vote\t\t" << "4-logout\t\t" << "5-switch account\t\t" << " 6-end vote\t\t" << " 7-edit vote info";
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
		case 7:editelectioninfo();
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
	bool flag = true;
	int i = 0,j=0; 
	int num, n,ans;
	while (!election[i].name.empty()) {
		i++;
	}
	while (true) {
		cout << " enter Election ID:\n";
		cin >> ans;
		while (!election[j].name.empty()) {
			if (election[j].id = ans) {
				cout << "sorry that id is used try another one..\n\n";
				flag = false;
				break;
			}
				j++;
		}
		if (flag == false)
			continue;
		else
		{
			break;
			election[i].id = ans;
			
		}
	}
	cout << " enter the election's name : \n";
	cin >> election[i].name;
	cout << " enter description :\n";

	cin >> election[i].description;

	cout << " How many nominees do you want?\n";
	cin >> num;

	election[i].no_ofnominees = num;

	for (int x = 0; x < num; x++)

	{
		cout << "enter name of nominee " << x + 1 << " :";
		cin >> election[i].nominees[x];
	}
	cout << "How many voter codes do you want?\n";
	cin >> n;
	election[i].no_allowed_voter_code = n;
	for (int y = 0; y < n; y++) {
		cout << "enter voter code " << y + 1 << " :";
		cin >> election[i].allowed_voters_code[y];
	}
	election[i].end = false;

}
void deletevote()
{
	system("CLS");
	map<int, int>mp;
	int ans;
	bool flag = false;
	int temp[10];
	int cnt = 1;
	while (election[cnt].id!=0) {
		temp[cnt] = election[cnt].id;
		cnt++;
	}
	sort(temp, temp + cnt);

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 3; j++) {
			if (admin[adminindex].election_ids[j] == election[i].id)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
			break;
	}
	if (flag == false)
		cout << "SORRY YOU MUST CREATE A VOTE FIRST TO DELETE IT..\n";
	else {
		cout << "\t\t\t choose the vote you want to delete\n";
		for (int i = 0,j=1; i < 3; ++i,j++) {
			int low = 1, high = cnt - 1,mid;
			while (low <= high) {
				mid = (low + high) / 2;
				if (temp[mid] == admin[adminindex].election_ids[i])
				{
					cout << "(" << j << ")  " << election[mid].name << "\n";
					mp[j] = mid;
					break;
				}
				else if (temp[mid] > admin[adminindex].election_ids[i])
				{
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}

			}
		}
		cout << "press -1 to back to the menu\n\n";
		cin >> ans;
		if (ans == -1)
			return;
		//mp[ans]--;
		int j = 0;
		for (int i = mp[ans]; !election[j].name.empty(); i++) {
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
	int temp[10];
	int cnt = 1;
	while (election[cnt].id != 0) {
		temp[cnt] = election[cnt].id;
		cnt++;
	}
	sort(temp, temp + cnt);
	map<int, int>mp;
	int ans;
	bool boolean = false;
	bool valid = true;
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

		for (int i = 0,j=1; i < 3; ++i,++j) {
			int low = 1, high = cnt - 1, mid;
			while (low <= high) {
				mid = (low + high) / 2;
				if (temp[mid] == admin[adminindex].election_ids[i]&&election[mid].end==false)
				{
					cout << "(" << j << ")  " << election[mid].name << "\n";
					mp[j] = mid;
					break;
				}
				else if (temp[mid] > admin[adminindex].election_ids[i])
				{
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}

			}
		}
		cout << "press -1 to back to the menu\n\n";
		if (mp.empty())
		{
			cout << "no votes left to end\n";
			system("pause");
			return;
		}
		cin >> ans;
		if (ans == -1)
			return;
		

		election[mp[ans]].end = true;
	}
}                                               
void listofvotes()
{
	map<int, int>mp;
	int ans;
	system("cls");
	cout << "Enter your Choice  or (-1) to go back to menu\n";
	int temp[10];
	int cnt = 1;
	while (election[cnt].id != 0) {
		temp[cnt] = election[cnt].id;
		cnt++;
	}
	sort(temp, temp + cnt);

	for (int i = 0, j = 1; i < 3; ++i, ++j) {
		int low = 1, high = cnt - 1, mid;
		while (low <= high) {
			mid = (low + high) / 2;
			if (temp[mid] == admin[adminindex].election_ids[i])
			{
				cout << "(" << j << ")  " << election[mid].name << "\n";
				mp[j] = mid;
				break;
			}
			else if (temp[mid] > admin[adminindex].election_ids[i])
			{
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}

		}
	}
	cin >> ans;
	if (ans == -1)
		return;
	electionindex = mp[ans];
	if (election[electionindex].end == true)
	{
		cout << "this vote is finished";
		winner(electionindex);
	}
	else
	{
		if (voter[voterindex].code.voted == true) {
			cout << "you already submitted your vote\n\n";
		}
		else {
			cout << election[electionindex].name << endl;
			cout << election[electionindex].description << "\n\n";
			for (int i = 0; !election[electionindex].nominees[i].empty(); i++)
				cout << "(" << i << ")" << election[electionindex].nominees[i] << endl;
			voter[voterindex].code.voted = true;
			vote();
			leadingnominee();
		}
	}

}
void vote()
{


	int nomineeno;
	cout << "\nenter number of nominee you want to vote for : ";
	cin >> nomineeno;
	election[electionindex].votes[nomineeno]++;
	cout << "number of vote for " << election[electionindex].nominees[nomineeno] << ": " << election[electionindex].votes[nomineeno];

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


	system("pause");

}
void winner(int electionindex)
{
	int count = 0;


	int temp;
	int max = -10000;
	int winner = 0;
	for (int i = 0; i < 5; i++) {
		if (election[electionindex].votes[i] > max)
		{
			max = election[electionindex].votes[i];
			temp = i;
		}
	}
	cout << "the winner is  " << election[electionindex].nominees[temp] << " by" << max << " votes\n\n";
	Sleep(1700);


}void editelectioninfo()
{
	int index;
	system("CLS");
	int ans;
	int x;
	bool flag = false;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (admin[adminindex].election_ids[j] == election[i].id)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
			break;
	}
	if (flag == false)
		cout << "SORRY YOU MUST CREATE A VOTE FIRST TO EDIT IT..\n";
	else
	{
		cout << "\t\t\t choose the vote you want to edit or (-1)to go back to menu\n";
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (admin[adminindex].election_ids[j] == election[i].id)
				{

					cout << i << "- " << election[i].name << endl;

				}

			}
		}
		cin >> ans;
		if (ans == -1)
			return;
		index = ans;
		cout << "what do you want t edit\n";
		cout << "1-election name\t\t" << "2-election discription\t\t" << "3-nominees\t\t" << "4-allowed voter codes\t\t";
		cin >> x;
		switch (x)
		{
		case 1: editelectionname(index);
			break;
		case 2: editelectiondescription(index);
			break;
		case 3: editelectionnominees(index);
			break;
		case 4: editallowedvotercodes(index);
			break;
		}


	}
}
void editelectionname(int index)
{
	string name;
	cout << "enter new election name: ";
	cin >> name;
	election[index].name = name;
	cout << "election name changed successfully";
}
void editelectiondescription(int index)
{
	string description;
	cout << "enter new election description: ";
	cin >> description;
	election[index].description = description;
	cout << "election description changed successfully";
}
void editelectionnominees(int index)
{
	system("CLS");
	int ans;
	cout << "1-add a nominee\t\t" << "2-delete a nominee\t\t";
	cin >> ans;
	switch (ans)
	{
	case 1: addnominee(index);
		break;
	case 2: deletenominee(index);
		break;
	}


}
void editallowedvotercodes(int index)
{
	int ans;
	cout << "<1>delete voter code\t\t\t<2>add voter code\n\n";
	cin >> ans;
	switch (ans) {
	case 1:deletevotercode(index);
		break;
	case 2:addvotercode(index);
		break;
	default:cout << "invalid choice\n";
	}
}
void addnominee(int index)
{
	string name;
	int i = 0;
	cout << "enter name of nominee you want to add: ";
	cin >> name;
	while (!election[index].nominees[i].empty()) {
		i++;
	}
	election[index].nominees[i] = name;
	election[index].no_ofnominees++;
}
void deletenominee(int index)
{
	system("CLS");
	int ans;
	cout << "choose the nominee you want to delete: ";
	for (int i = 0; !election[index].nominees[i].empty(); i++)
	{
		cout << i + 1 << "-" << election[index].nominees[i] << endl;

	}
	cin >> ans;
	ans--;
	int j = 0;
	for (int i = ans; !election[index].nominees[j].empty(); i++)
	{
		election[index].nominees[i] = election[index].nominees[i + 1];
		election[index].votes[i] = election[index].votes[i + 1];
		j++;
	}
}
void addvotercode(int index)
{
	int code;
	int i = 0;
	cout << "enter voter code you want to add: ";
	cin >> code;
	while (election[index].allowed_voters_code[i] != 0)
	{
		i++;
	}
	election[index].allowed_voters_code[i] = code;
	election[index].no_allowed_voter_code++;
	cout << "voter code added successfully";
}
void deletevotercode(int index)
{
	system("CLS");
	int ans;
	cout << "choose the voter code you want to delete: ";
	for (int i = 0; election[index].allowed_voters_code[i] != 0; i++)
	{
		cout << i + 1 << "-" << election[index].allowed_voters_code[i] << endl;
	}
	cin >> ans;
	ans--;
	int j = 0;
	for (int i = ans; election[index].allowed_voters_code[i] != 0; i++)
	{
		election[index].allowed_voters_code[i] = election[index].allowed_voters_code[i + 1];
		j++;
	}
	election[index].no_allowed_voter_code--;
	cout << "voter code deleted successfully";
}
void updateadmins()
{
	int count = 0;
	ofstream out;
	out.open("admins.txt");
	out.clear();
	while (!election[count].name.empty()) {
		out<< admin[count].id << endl;
		out<< admin[count].adminaccount.username << endl;
		out<< admin[count].adminaccount.pass << endl;
		out<< admin[count].email << endl;
		out<< admin[count].address << endl;
		out<< admin[count].phone << endl;
		for (int i = 0; i < 3; ++i)
			out<< admin[count].election_ids[i]<<endl;
		count++;
	}
	out.close();
}
void updatevoters()
{
	int count = 0;
	fstream out;
	out.open("voters.txt");
	out.clear();
	while (!election[count].name.empty()) {
		out<< voter[count].id << endl;
		out<< voter[count].voteraccount.username << endl;
		out<< voter[count].voteraccount.pass << endl;
		out<< voter[count].email << endl;
		out<< voter[count].address << endl;
		out<< voter[count].phone << endl;
		out<< voter[count].code.code << endl;
		count++;
	}
	out.close();
}
void updateelections()
{
	string id, noon, avc;
	string in, inn;
	int count = 0;
	ofstream out;
	out.open("elections.txt");
	out.clear();
	while (!election[count].name.empty()) {
		out << election[count].id<<endl;
		out << election[count].name << endl;
		out << election[count].description << endl;
		out << election[count].no_ofnominees << endl;
		out << election[count].no_allowed_voter_code << endl;
		for (int i = 0; i < election[count].no_ofnominees; i++)
			out << election[count].nominees[i] << endl;
		for (int i = 0; i < election[count].no_ofnominees; i++)
			out << election[count].votes[i] << endl;
		for (int i = 0; i < election[count].no_allowed_voter_code; i++)
			out << election[count].allowed_voters_code[i]<<endl;

		count++;
	}
	out.close();
}
void updatefiles() {
	updateadmins();
	updatevoters();
	updateelections();
}