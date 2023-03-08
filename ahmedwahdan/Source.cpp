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
int main()
{
	readfromfiles();
	cout << election[0].id << " " << election[0].description << " "<<endl;
	for (int i = 0; i < 3; i++)
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








