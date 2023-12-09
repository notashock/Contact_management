#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

typedef struct contacts
{
	string firstName;
	string lastName;
	string phoneNumber;
	string address;
	struct contacts *next;
	struct contacts *prev;
}contacs;

bool checkIfNumberCanBeConverted(string number);
short fromStringToInt(string number);
contacts* createNewContact();
void addContact(contacts *&head);
void goBack(contacts *&head);
void listContacts(contacts *&head);
void mainMenu(contacts *&head);
void readContactsFromFile(contacts *&head);
void selectContactToDelete(contacts *&head);
void writeContactsInFile(contacts *&head);


bool checkIfNumberCanBeConverted(string number)
{
	if ((number.length() > 1) && (number[0] == '0'))
	{
		return false;
	}

	short iterator = 0;

	while (iterator < number.length())
	{
		if ((number[iterator] < '0') || (number[iterator] > '9'))
		{
			return false;
		}
		iterator++;
	}

	return true;
}
contacts* createNewContact()
{
	contacts *newContact = new contacts;
	cout << "\n\tEnter the first name: ";
	getline(cin, newContact->firstName);
	cout << "\n\tEnter the last name: ";
	getline(cin, newContact->lastName);
	cout << "\n\tEnter the number: ";
	getline(cin, newContact->phoneNumber);
	cout << "\n\tEnter the address: ";
	getline(cin, newContact->address);

	return newContact;
}
short fromStringToInt(string number)
{
	short iterator = 0;
	short numberInt = 0;

	while (iterator < number.length())
	{
		numberInt = numberInt * 10 + (number[iterator] - '0');
		iterator++;
	}

	return numberInt;
}
void addContact(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tAdd a new contact\n";
	contacts *iterator = head;
	contacts *newContact = createNewContact();
	int compareTwoContactsBy = 2;
	while (((iterator != NULL) && (iterator->next != NULL)) &&
		(iterator->lastName.compare(newContact->lastName) < 0))
	{
		iterator = iterator->next;
	}
	if (iterator != NULL)
	{
		compareTwoContactsBy = iterator->lastName.compare(newContact->lastName);
	}
	if ((iterator != NULL) && (iterator->lastName.compare(newContact->lastName) == 0))
	{
		while (((iterator != NULL) && (iterator->next != NULL)) &&
			(iterator->firstName.compare(newContact->firstName) < 0))
		{
			iterator = iterator->next;
		}
		compareTwoContactsBy = iterator->firstName.compare(newContact->firstName);
	}
	if ((iterator == NULL) || ((iterator == head) &&
		(compareTwoContactsBy > 0)))
	{
		newContact->next = head;
		newContact->prev = NULL;
		if (head != NULL)
		{
			head->prev = newContact;
		}
		head = newContact;
	}
	else
	{
		if ((iterator->next == NULL) &&
			(compareTwoContactsBy < 0))
		{
			newContact->next = NULL;
			newContact->prev = iterator;
			iterator->next = newContact;
		}
		else
		{
			if (compareTwoContactsBy != 0)
			{
				newContact->next = iterator;
				newContact->prev = iterator->prev;
				iterator->prev->next = newContact;
				iterator->prev = newContact;
			}
		}
	}
	system("cls");
	cout<<"\n\tCONTACT ADDED!!";
}
void goBack(contacts *&head)
{
	cout << "\n\n\t1.Go back to main menu.";
	cout << "\n\t2.Exit the phone book.";
	cout << "\n\tEnter the option you want : ";
	char number = _getch();

	switch (number)
	{
	case '1':
		mainMenu(head);
		break;
	case '2':
		return;
		break;
	default:
		system("cls");
		cout << "\n\n\tEnter the correct key";
		goBack(head);
		break;
	}
}
void listContacts(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tContacts";

	contacts *iterator = head;
	short index = 0;

	if (iterator == NULL)
	{
		cout << "\n\n\tThe phone book is empty.";
	}
	else
	{
		cout << "\n\n\tThe contacts from the phone book are:";
		while (iterator != NULL)
		{
			cout << "\n\t" << index << ".";
			cout << iterator->firstName << " " << iterator->lastName << "\t\t";
			cout << iterator->phoneNumber << "\t" << iterator->address;
			iterator = iterator->next;
			index++;
		}
	}
}
void mainMenu(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tPhone Book. Main Menu";
	cout << "\n\n\tChoose an option\n";
	cout << "\n\t1.List all the contacts";
	cout << "\n\t2.Add a new contact";
	cout << "\n\t3.Delete a contact";
	cout << "\n\t4.Exit the phone book";
	//cout << "\n\n\tIntroduce the number of the option you want:";
	char option = _getch();

	switch (option)
	{
	case '1':
		listContacts(head);
		break;
	case '2':
		addContact(head);
		break;
	case '3':
		selectContactToDelete(head);
		break;
	case '4':
		return;
		break;
	default:
		cout << "\n\n\tChoose a valid option";
		break;
	}
	goBack(head);
}

void readContactsFromFile(contacts *&head)
{
	char aux[100];
	contacts *iterator = head;
	ifstream input("contacts.in");

	while (input.getline(aux, 100, '|'))
	{
		contacts *newContact = new contacts;

		newContact->lastName = aux;

		input.getline(aux, 100, '|');
		newContact->firstName = aux;

		input.getline(aux, 100, '|');
		newContact->phoneNumber = aux;

		input.getline(aux, 100);
		newContact->address = aux;

		if (head == NULL)
		{
			head = newContact;
			newContact->prev = NULL;
			newContact->next = NULL;
			iterator = head;
		}
		else 
		{
			iterator->next = newContact;
			newContact->prev = iterator;
			newContact->next = NULL;
			iterator = iterator->next;
		}
	}
	input.close();
}

void selectContactToDelete(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tDelete a contact from the phone book";
	if (head == NULL)
	{
		cout << "\n\n\tThe phone book is empty.";
		return;
	}

	contacts *iterator = head;
	short iteratorInt = 0;
	short numberInt = 0;
	string number;

	listContacts(head);
	do
	{
		cout << "\n\n\tEnter the no.of the contact that you want to delete from the phone book: ";
		getline(cin, number);
	} while ((checkIfNumberCanBeConverted(number) == false) || (number.length() >= 5));

	numberInt = fromStringToInt(number);

	while ((iterator != NULL) && (iteratorInt < numberInt))
	{
		iterator = iterator->next;
		iteratorInt++;
	}
	if (iterator != NULL)
	{
		if (iteratorInt == 0)
		{
			if (iterator->next == NULL)
			{
				head = NULL;
			}
			else 
			{
				head = head->next;
				head->prev = NULL;
			}
		}
		else
		{
			if (iterator->next == NULL)
			{
				iterator->prev->next = NULL;
			}
			else
			{
				iterator->next->prev = iterator->prev;
				iterator->prev->next = iterator->next;
			}
		}
		delete iterator;
		system("cls");
		cout << "\n\tCONTACT DELETED!!!";
	}
	else
	{
		cout << "\n\n\tChoose the correct key";
	}
}
void writeContactsInFile(contacts *&head)
{
	contacts *iterator = head;
	ofstream output("contacts.in");

	while (iterator != NULL)
	{
		output << iterator->lastName << "|" << iterator->firstName << "|";
		output << iterator->phoneNumber << "|" << iterator->address;
		if (iterator->next != NULL)
		{
			output << "\n";
		}
		iterator = iterator->next;
	}

	output.close();
}

int main()
{
	contacts *head = NULL;
	system("color 3F");
	readContactsFromFile(head);
	mainMenu(head);
	writeContactsInFile(head);

	return 0;
}
