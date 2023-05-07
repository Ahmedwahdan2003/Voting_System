#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<Windows.h>
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
	code code[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int no_ofcodes = 0;
}voter[20];


struct admin {

	int id = 0;
	account adminaccount;
	string email;
	string address;
	int phone;
	int election_ids[10] = { 0 };
	int no_ofelectionids = 0;
}admin[20];


struct election {
	int id = 0;
	string name;
	string description;
	string nominees[10];
	int votes[10] = { 0 };
	int code = 0;
	int no_ofnominees;
	bool end;


}election[20];
int no_of_elections =0;
static int numberofid;
static int voterindex;//to save his index throughout the program//
static int adminindex;//to save his index throughout the program//
static int electionindex;
int firstmenu();
void readvoters();
void readadmins();
void readelections();
void readfromfiles();
bool loginvoter(int& a);
bool loginadmin(int& b);
void registervoter();
void registeradmin();
int mainmenu();
void votermenu();
void adminmenu();
void editinfoadmin();

void createvote(int& a);
void deletevote(int& a, int& b);
void endvote(int& a, int& b);
void listofvotes(int& b, int& c);


void switchacc();
void editidadmin();
void editusernameadmin();
void editpassadmin();
void editemailadmin();
void editaddressadmin();
void editphonenoadmin();
void editinfovoter();
void editidvoter();
void editusernamevoter();
void editpassvoter();
void editemailvoter();
void editaddressvoter();
void editphonenovoter();
void editvotingcode();
void addvotingcode();
void deletevotingcode();
void winner(int electionindex);
void leadingnominee(int& a);
void vote();
void editelectioninfo();
void editelectionname(int index);
void editelectiondescription(int index);
void editelectionnominees(int index);
void editelectioncode(int index);
void addnominee(int index);
void deletenominee(int index);
void updateadmins();
void updatevoters();
void updatelection();
void updatefiles();
int main()
{
	
	readfromfiles();
	//////////////////////////////////
	mainmenu();
	/////////////////////////////////
	updatefiles();
}
int firstmenu() {
	system("CLS");
	int option;
	cout << "\t\t\t\t\t\t*****\n";
	cout << "\t\t\t\t\t*****";
	cout << "WELCOME TO EVOTE***\t\t\t\t\n";
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
				verified = loginvoter(voterindex);
				if (!verified)
					continue;
				else
					votermenu();
				continue;
			case 2:
				registervoter();
				continue;
			default:cout << "Invalid choice please try again...\n";
				continue;
			}

		case 2:
			cout << " \t\t <1-Login>  \t\t\t\t\t\t <2-Register>\n\n\n ";
			cin >> ans;
			switch (ans) {
			case 1:
				verified = loginadmin(adminindex);
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
		input >> admin[count].no_ofelectionids;
		for (int i = 0; i < admin[count].no_ofelectionids; ++i)
		{
			input >> admin[count].election_ids[i];

		}
		count++;
	}
	input.close();
}
void readvoters()
{
	int ans;
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
		input >> ans;
		voter[count].no_ofcodes = ans;
		for (int i = 0; i < ans; i++)
		{
			int in;
				input >> in;
			voter[count].code[i].code=in;
			voter[count].code[i].voted = false;
		}
		count++;
	}
	input.close();
}
void readelections()
{
	string id, noon, code;
	string in, inn, temp;
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

		for (int i = 0; i < election[count].no_ofnominees; ++i)
			getline(input, election[count].nominees[i]);

		for (int h = 0; h < election[count].no_ofnominees; ++h)
		{
			getline(input, inn);
			election[count].votes[h] = stoi(inn);
		}
		getline(input, temp);
		election[count].code = stoi(temp);
		election[count].end = false;
		no_of_elections++;
		count++;
	}
	input.close();

}
bool loginvoter(int& b)
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
		system("CLS");
	} while (ans == 'y' || ans == 'Y');
	return false;
}

bool loginadmin(int& a)
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
		system("CLS");
	} while (ans == 'y' || ans == 'Y');
	return false;
}
void registervoter()
{
	system("CLS");
	int i = 0;
	int ans;
	while (!voter[i].voteraccount.username.empty())
	{
		i++;
	}
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
	cout << "How many voting codes Do you Have\n";
	cin >> ans;
	voter[i].no_ofcodes = ans;
	for (int j = 0; j < ans; j++)
	{
		cout << "enter code " << j+1 << ": ";
		cin >> voter[i].code[j].code;
		voter[i].code[j].voted = false;
	}
	cout << voter[i].code[0].code << " " << voter[i].code[1].code;
	system("pause");
	cout << "THANK YOU FOR REGISTERING..REDIRECTING YOU NOW\n";

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
		cout << "1-edit personal information\t\t\t" << "2-show list of votes you have access to \t\t\t" << "3-edit voting codes\t\t\t" << "4-logout\t\t\t";
		cout << endl;
		cin >> ans;

		switch (ans)
		{
		case 1: editinfovoter(); cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 2: listofvotes(no_of_elections, voter[voterindex].no_ofcodes);
			Sleep(1000);
			continue;
		case 4:
			break;
		case 3:editvotingcode();
			Sleep(1000);
			continue;

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
		cout << "1-edit personal information\t\t" << "2-create vote\t\t" << "3-delete vote\t\t" << "4-logout\t\t" << "5-switch account\t\t" << " 6-end vote\t\t" << " 7-edit vote info";
		cout << endl;
		cin >> ans;

		switch (ans)
		{
		case 1: editinfoadmin();
			cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 2: createvote(no_of_elections);  cout << "operation done successfully.. redirecting you now";
			Sleep(1000);
			continue;
		case 3: deletevote(adminindex, no_of_elections);
			Sleep(1000);
			continue;
		case 4:
			break;
		case 5: switchacc();
			continue;
		case 6: endvote(adminindex, no_of_elections);
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
void editvotingcode()
{
	system("CLS");
	int ans;
	cout << "1-add voting code\t\t\t " << "2-delete voting code\t\t\t ";
	cin >> ans;
	switch (ans)
	{
	case 1:addvotingcode();
		break;
	case 2: deletevotingcode();
		break;
	}
}
void addvotingcode()
{
	system("CLS");
	int code;
	int i = 0;
	cout << "enter the voting code you want to add ..  or(-1)to go back to menu\n";
	cin >> code;
	if (code == -1)
		return;
	else
	{
		while (voter[voterindex].code[i].code != 0)
		{
			i++;
		}

		voter[voterindex].code[i].code = code;
		voter[voterindex].no_ofcodes++;
		cout << "voting code added successfully";
	}
}
void deletevotingcode()
{
	system("CLS");
	int ans;
	cout << "choose the voting code you want to delete: \n";
	for (int i = 0; voter[voterindex].code[i].code != 0; i++)
	{
		cout << i + 1 << "-" << voter[voterindex].code[i].code << endl;
	}

	cout << "Enter Your Choice..  or(-1)to go back to menu\n";
	cin >> ans;
	if (ans == -1)
		return;
	else
	{                         
		ans--;
		int j = 0;
		for (int i = ans; voter[voterindex].code[i].code != 0; i++)
		{
			voter[voterindex].code[i].code = voter[voterindex].code[i + 1].code;
			j++;
		}
		voter[voterindex].no_ofcodes--;
		cout << "voter code deleted successfully";
	}
}


void createvote(int& a)
{
	int code;
	int in;
	bool flag2 = false;
	bool flag = false;
	int i = 0, j = 0;
	int num, n, ans;
	while (!election[i].name.empty())
	{
		i++;
	}
	if (no_of_elections == 0) {
		cout << "Enter Election Id\n";
		cin >> in;
		election[i].id = in;
	}
	else {
		do {
			int cnt = 0;
			cout << "Enter election id\n";
			cin >> in;
			for (cnt; cnt < 20; cnt++)
			{
				if (election[cnt].id != in)
				{
					flag = true;
				}
				else
				{
					flag = false;
					break;

				}
			}
			if (flag == false) {
				cout << "Sorry that id is used try another one\n";
				continue;
			}
			else {
				election[i].id = in;
				break;

		}
			} while (flag == false);
	}

	int index = -1;
	for (int j = 0; j < 10; j++)       
	{
		if (admin[adminindex].election_ids[j] == 0)
		{
			index = j;
			break;
		}
	}
	admin[adminindex].election_ids[index] = election[i].id;
	admin[adminindex].no_ofelectionids += 1;



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



	if (no_of_elections == 0) {
		int inn;
		cout << "Enter Election Code\n";
		cin >> inn;
		election[i].code = inn;
	}
	else {
		do {
			cout << "Enter election Code\n";
			cin >> ans;
			for (int l = 0; l < no_of_elections; l++) {
				if (election[l].code != ans)
				{
					flag2 = true;
				}
				else
				{
					flag2 = false;
					break;

				}
			}
			if (flag2 == false) {
				cout << "Sorry that code is used try another one\n";
				continue;
			}
			else {
				election[i].code = ans;
				break;
			}
		}
		 while (flag2 == false);
	}
	election[i].end = false;
	no_of_elections++;
}
void deletevote(int& b, int& a)
{

	for (int i = 0; i < 7; i++) {
		cout << admin[adminindex].election_ids[i] << " ";
	}
	cout << admin[adminindex].no_ofelectionids << "\n";
	system("pause");
	system("CLS");
	int ans;
	bool flag = false;
	map<int, int>mp;
	int k = 1;
	for (int i = 0; i < no_of_elections; ++i) {
		for (int j = 0; j <= admin[adminindex].no_ofelectionids; j++)
		{
			if (admin[adminindex].election_ids[j] == election[i].id && admin[adminindex].election_ids[j] != 0)
			{
				flag = true;
				mp[k] = i;
				cout << "(" << k << ") " << election[i].name << "\n";
				k++;
				break;
			}
		}
	}
	if (flag == false) {
		cout << "You Have to create a vote first to delete it\n\n";
		Sleep(1100);
		return;
	}
	cout << "Enter Your Choice..  or(-1)to go back to menu\n";
	cin >> ans;
	if (ans == -1)
		return;
	else {
		
		//cout << mp[ans];
		//cout << "\n" << election[0].id<<"\n";
		//cout << temp;
		//system("pause");

		int indx = -1;
		for (int i = 0; i < 10; i++)
		{
			if (admin[adminindex].election_ids[i] == election[mp[ans]].id)
			{
				indx = i;
				break;
			}
		}
		//cout << indx << "\n";
		//system("pause");

		for (int i = indx; admin[adminindex].election_ids[i] != 0; i++) {
			admin[adminindex].election_ids[i] = admin[adminindex].election_ids[i + 1];
		}


		cout << "operation done successfully\n";
		for (int i = mp[ans]; !election[i].name.empty(); i++)
		{
			election[i] = election[i + 1];

		}
		//cout << mp[ans];
		//cout << '\n' << election[mp[ans]].id;
		//cout << temp;
		//cout << election[temp].id;
		//cout << election[0].id;
		//system("pause");
		
			//admin[adminindex].no_ofelectionids--;
		no_of_elections--;
	}
}
void endvote(int& a, int& b)
{

	system("CLS");
	int ans;
	bool flag = false;
	map<int, int>mp;
	int k = 1;
	for (int i = 0; i < no_of_elections; ++i) {
		for (int j = 0; j <= admin[adminindex].no_ofelectionids; j++)
		{
			if (admin[adminindex].election_ids[j] == election[i].id && election[i].end == false)
			{
				flag = true;
				mp[k] = i;
				cout << "(" << k << ") " << election[i].name << "\n";
				k++;
				break;
			}
		}
	}
	if (flag == false) {
		cout << "No Votes To End\n\n";
		Sleep(1000);
		return;
	}
	cout << "Enter Your Choice..  or(-1)to go back to menu\n";
	cin >> ans;
	int temp = mp[ans];
	if (ans == -1)
		return;
	else {
		for (int i = 0; i < election[temp].no_ofnominees; i++) {
			cout <<"\nvotes for : "<< election[temp].nominees[i] << " is : " << election[temp].votes[i] << "\n";
		}
		char anss;
		cout << "\n End The Vote?  (y/n)\n";
		cin >> anss;
		if (anss == 'y')
			election[temp].end = true;
		else
			return;
	}
}



void switchacc()
{
	bool flag = false;
	int i = 0;
	for (i = 0; i < 20; i++)
	{
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


void listofvotes(int& b, int& c)
{

	system("CLS");
	cout << voter[voterindex].code[0].code << " " << voter[voterindex].code[1].code << " " << voter[voterindex].code[2].code;
	system("pause");
	int ans;
	int k = 1;
	bool flag2 = false;
	bool flag = false;
	map<int, int>mp;
	cout << "Running Elections:\n";
	for (int i = 0; i < no_of_elections; ++i) {
		for (int j = 0; j <= voter[voterindex].no_ofcodes; j++)
		{
			if (voter[voterindex].code[j].code == election[i].code && election[i].end == false)
			{

				flag = true;
				mp[k] = i;
				cout << "(" << k << ") " << election[i].name << "\n";
				k++;
				break;
			}
		}
	}
	cout << "\nEnded elections:\n";
	for (int i = 0; i < no_of_elections; ++i) {
		for (int j = 0; j <= voter[voterindex].no_ofcodes; j++)
		{
			if (voter[voterindex].code[j].code == election[i].code && election[i].end == true && voter[voterindex].code[j].code != 0)
			{
				flag2 = true;
				mp[k] = i;
				cout << "(" << k << ") " << election[i].name << "\n";
				k++;
				break;
			}
		}
	}
	cout << "\n\n";
	if (flag == true && flag2 == false)
	{
		cout << "No Ended Elections. All Elections Are Runing\n";
	}
	if (flag ==false && flag2 == true)
	{
		cout << "No Runing Elections. All Elections Ended\n";
	}
	if (flag == false && flag2 == false) {
		cout << "You Dont Have Access To Any Elections\n\n";
		Sleep(1100);
		return;
	}
	cout << "\n\n\nEnter Your Choice..  or(-1)to go back to menu\n";
	cin >> ans;
	if (ans == -1)
		return;
	electionindex = mp[ans];

	int indexofcode;
	for (indexofcode = 0; indexofcode < voter[voterindex].no_ofcodes; indexofcode++) {
		if (voter[voterindex].code[indexofcode].code == election[electionindex].code)
		{
			break;

		}
	}



	if (election[electionindex].end == true)
	{
		winner(electionindex);
	}
	else
	{
		if (voter[voterindex].code[indexofcode].voted == true) {
			cout << "you already submitted your vote\n\n";
		}
		else {
			cout << election[electionindex].name << endl;
			cout << election[electionindex].description << "\n\n";
			for (int i = 0; !election[electionindex].nominees[i].empty(); i++)
				cout << "(" << i << ")" << election[electionindex].nominees[i] << endl;
			voter[voterindex].code[indexofcode].voted = true;
			vote();
			leadingnominee(electionindex);
		}
	}

}
void vote()
{


	int nomineeno;
	cout << "\nenter number of nominee you want to vote for : ";
	cin >> nomineeno;
	election[electionindex].votes[nomineeno]++;
	cout << "number of votes for " << election[electionindex].nominees[nomineeno] << " :  " << election[electionindex].votes[nomineeno] << "\n";

	Sleep(1000);


}


void leadingnominee(int& a)
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
	cout << "the winner is  " << election[electionindex].nominees[temp] << " by " << max << " votes\n\n";
	system("pause");


}void editelectioninfo()
{
	system("CLS");
	int x;
	int index;
	int ans;
	bool flag = false;
	map<int, int>mp;
	int k = 1;
	for (int i = 0; i < no_of_elections; ++i) {
		for (int j = 0; j < admin[adminindex].no_ofelectionids; j++)
		{
			if (admin[adminindex].election_ids[j] == election[i].id)
			{
				flag = true;
				mp[k] = i;
				cout << "(" << k << ") " << election[i].name << "\n";
				k++;
			}
		}
	}
	if (flag == false) {
		cout << "You Have to create a vote first to Edit it\n\n";
		Sleep(1100);
		return;
	}
	cout << "Enter Your Choice..  or(-1)to go back to menu\n";
	cin >> ans;
	if (ans == -1)
		return;

	index = mp[ans];
	cout << "what do you want t edit\n";
	cout << "1-election name\t\t" << "2-election description\t\t" << "3-nominees\t\t" << "4-Change Election Code\t\t";
	cin >> x;
	switch (x)
	{
	case 1: editelectionname(index);
		break;
	case 2: editelectiondescription(index);
		break;
	case 3: editelectionnominees(index);
		break;
	case 4: editelectioncode(index);
		break;
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
void editelectioncode(int index)
{
	bool flag = false;
	int in;
	int oldcode;
	do {
		cout << "enter current election code";
		cin >> oldcode;
		if (oldcode == election[index].code)
		{
			do {
				cout << "Enter new election code\n";
				cin >> in;
				for (int i = 0; i < no_of_elections; i++)
				{
					if (election[i].code != in)
					{
						flag = true;
					}
					else
					{
						flag = false;
						break;

					}
				}
				if (flag == false)
				{
					cout << "Sorry that code is used try another one\n";
					continue;
				}
				else
				{
					election[index].code = in;
					break;
				}
			} while (flag == false);
			break;
		}
		else
		{
			cout << "the election code you entered is incorrect" << endl;
		}
	} while (true);
}



void updateadmins()
{                   
	int count = 0;
	ofstream out;
	out.open("admins.txt");
	out.clear();
	while (admin[count].id != 0) {
		out << admin[count].id << endl;
		out << admin[count].adminaccount.username << endl;
		out << admin[count].adminaccount.pass << endl;
		out << admin[count].email << endl;
		out << admin[count].address << endl;
		out << admin[count].phone << endl;
		for (int i = 0; i < 3; ++i)
			out << admin[count].election_ids[i] << endl;
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
	while (voter[count].id != 0) {
		out << voter[count].id << endl;
		out << voter[count].voteraccount.username << endl;
		out << voter[count].voteraccount.pass << endl;
		out << voter[count].email << endl;
		out << voter[count].address << endl;
		out << voter[count].phone << endl;
		for (int j = 0; j < voter[count].no_ofcodes; j++)
			out << voter[count].code[j].code << endl;
		count++;
	}
	out.close();
}
void updateelections()
{
	string id, noon;
	string in, inn;
	int count = 0;
	ofstream out;
	out.open("elections.txt");
	out.clear();
	while (!election[count].name.empty()) {
		out << election[count].id << endl;
		out << election[count].name << endl;
		out << election[count].description << endl;
		out << election[count].no_ofnominees << endl;
		for (int i = 0; i < election[count].no_ofnominees; i++)
			out << election[count].nominees[i] << endl;
		for (int i = 0; i < election[count].no_ofnominees; i++)
			out << election[count].votes[i] << endl;
		out << election[count].code << endl;

		count++;
	}
	out.close();
}
void updatefiles() {
	updateadmins();
	updatevoters();
	updateelections();
}