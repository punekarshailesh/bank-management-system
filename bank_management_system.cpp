#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{

	long int acc_no;
	char name[50];
	int deposit;
	char type;

public:
	void create_account()
	{

		// function to creat the account
		cout << "\nEnter the account no. :";
		cin >> acc_no;
		cout << "\n\nEnter the name of the account holder : ";
		cin.ignore();
		cin.getline(name, 50);
		cout << "\nEnter type of the account (C/S) : ";
		cin >> type;
		type = toupper(type); // convert lower case to upper case
		cout << "\nEnter the initial amount (>=500 for Saving and >=1000 for Current ) : ";
		cin >> deposit;
		cout << "\n\nAccount Created" << endl;
	}

	void show_account() 
	{
		cout << "\nAccount Holder Name : ";
		cout << name;
		cout << "\nAccount No. : " << acc_no;
		cout << "\nType of Account : " << type;
		cout << "\nCurrent Balance amount : " << deposit;
	}

	void modify()
	{
		cout << "\nAccount No. : " << acc_no;
		cout << "\nModify Account Holder Name : ";
		cin.ignore();
		cin.getline(name, 50);
		cout << "\nModify Type of Account : ";
		cin >> type;
		type = toupper(type);
		cout << "\nModify Balance amount : ";
		cin >> deposit;
	}

	void dep(int x)
	{
		deposit += x;
	}

	void draw(int x)
	{
		deposit -= x;
	}

	void report()
	{
		cout << acc_no << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
	}

	int retacc_no() const
	{
		return acc_no;
	}

	int retdeposit() const
	{
		return deposit;
	}

	char rettype() const
	{
		return type;
	}
};

//    	function to write in file

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.txt");
	ac.create_account();
	outFile.write((char *)(&ac), sizeof(account));
	outFile.close();
}

//    	function to read specific record from file

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.txt");
	if (!inFile)
	{
		cout << "File could not be opened !!";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (inFile.read((char *)(&ac), sizeof(account)))
	{
		if (ac.retacc_no() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nRecord Not Found!";
}


//    	function to modify record of file


void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.txt");
	if (!File)
	{
		cout << "File could not be opened !!";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read((char *)(&ac), sizeof(account));
		if (ac.retacc_no() == n)
		{
			ac.show_account();
			cout << "\n\nEnter the new details of the account " << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write((char* )(&ac), sizeof(account));
			cout << "\n\nRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\nRecord Not Found!";
}

//    	function to delete record of file

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt");
	if (!inFile)
	{
		cout << "File could not be open !!";
		return;
	}
	outFile.open("temp.txt");
	inFile.seekg(0, ios::beg);
	while (inFile.read((char* )(&ac), sizeof(account)))
	{
		if (ac.retacc_no() != n)
		{
			outFile.write((char* )(&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("temp.txt", "account.txt");
	cout << "\n\nRecord Deleted";
}

//    	function to display all accounts deposit list

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.txt");
	if (!inFile)
	{
		cout << "File could not be open !!";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "=============================================\n";
	cout << "A/c no.     NAME    Type        Balance\n";
	cout << "=============================================\n";
	while (inFile.read((char* )(&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//    	function to deposit and withdraw amounts

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac; // object creation
	fstream File; // object creation
	File.open("account.txt");
	if (!File)
	{
		cout << "File could not be opened !!";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read((char* )(&ac), sizeof(account));
		if (ac.retacc_no() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter the amount to be deposited : ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter the amount to be withdrawn : ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficient balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write((char* )(&ac), sizeof(account));
			cout << "\n\nRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\nRecord Not Found!";
}

int main()
{
	int x;
	int num;
	cout << "\n\n\tBANK  MANAGEMENT  SYSTEM";
	do
	{
		cout << "\n\nMAIN MENU";
		cout << "\n\n01. NEW ACCOUNT";
		cout << "\n\n02. DEPOSIT AMOUNT";
		cout << "\n\n03. WITHDRAW AMOUNT";
		cout << "\n\n04. BALANCE ENQUIRY";
		cout << "\n\n05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n06. CLOSE AN ACCOUNT";
		cout << "\n\n07. MODIFY AN ACCOUNT";
		cout << "\n\n08. EXIT";
		cout << "\n\nSelect An Option (1-8) ";
		cin >> x;
		switch (x)
		{
		case 1:
			write_account();
			break;
		case 2:
			cout << "\n\nEnter the account no. : ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;
		case 3:
			cout << "\n\nEnter the account no. : ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case 4:
			cout << "\n\nEnter the account no. : ";
			cin >> num;
			display_sp(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout << "\n\nEnter the account no. : ";
			cin >> num;
			delete_account(num);
			break;
		case 7:
			cout << "\n\nEnter the account no. : ";
			cin >> num;
			modify_account(num);
			break;
		case 8:
			cout << "\n\nThanks for using our Bank Managemnt System\n";
			exit(0);
		default:
			cout << "\n\n Please enter a valid option!";
		}
		cin.ignore();
		cin.get();
	} while (x != '8');
	return 0;
}
