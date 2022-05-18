#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

void firstTask();
void secondTask();
void individualTask();
void additionalTask();

void main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	while (true)
	{

		cout << "\t\t\t/////      /////  ////////  //////     ///  ///      ///\n";
		cout << "\t\t\t//////    //////  ////////  //////     ///  ///      ///\n";
		cout << "\t\t\t///  //////  ///  ///       /// ///    ///  ///      ///\n";
		cout << "\t\t\t///   ////   ///  //////    ///  ///   ///  ///      ///\n";
		cout << "\t\t\t///          ///  //////    ///   ///  ///  ///      ///\n";
		cout << "\t\t\t///          ///  ///       ///    /// ///  ///      ///\n";
		cout << "\t\t\t///          ///  ////////  ///     //////  ///      ///\n";
		cout << "\t\t\t///          ///  ////////  ///      /////  ////////////\n";
		cout << "\t\t\t--------------------------------------------------------\n";


		cout << "\t\t\t\t\t|1)������� 1             |\n\t\t\t\t\t|2)������� 2             |\n\t\t\t\t\t" <<
			"|3)�������������� �������|\n\t\t\t\t\t|4)�������������� �������|\n\t\t\t\t\t---------------" <<
			"-----------\n\t\t\t\t\t�����: ";
		int menuChoice; cin >> menuChoice;

		switch (menuChoice)
		{
		case(1): { std::system("cls"); firstTask();      break; }
		case(2): { std::system("cls"); secondTask();     break; }
		case(3): { std::system("cls"); individualTask(); break; }
		case(4): { std::system("cls"); additionalTask(); break; }
		default: {std::cout << "������� �������� ��������..."; _getch(); std::system("cls"); break; }
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region firstGeneralTask

//	������� ����� ������ IntSetMassive.� ������ ������ ����� ��������� ������ ����� �����
//	(���������������� ������), � ����� ����� ���������� ��������� �������� ��������
//	����������.
//	���������� � ������ ������������(� �������, ������������� ��������, �� ���������
//	������ ��������������� ��������), ����������, ����������� ����.� �������, � ��� ������
//	���� ��������� �� ������ �������, � ����� ���������� ��������� �������.� ������ �������
//	������ ���� ������ ��������������� ��������, ��� ��� �� ��������� ���������.
//	������������� ����������� ��������� �������� :
//	? � + � � �������� ����� �� ���������(���� object + item, ��� item � ����� �����), ���������
//	������ ���� ������ �������� ��� ��� �� ���������;
//	? � + � � ����������� ��������(���� object1 + object2), ���������� ����� ���������,
//	������� �������� ������������ ���� �������� - ���������;
//	? � - � � ������� ����� �� ���������(���� object - item, ��� item � ����� �����)
//	? � - � � ����������� ��������(���� object1 - object2);
//	? �[]� � ���������� ������� �� ������;
//	? int() � ���������� � ������, ���������� �������� ���������(������ �������).
//	�������� ��������� ������������, � ������� ����������� ������������� ����
//	������������� ��������.

class IntSetMassive
{
public:

	IntSetMassive();
	~IntSetMassive();
	int getSize();
	void pushBack(const int data);
	void PrintMass();
	void deleteMass(const int index);
	void clearAll();
	bool check(const int value);
	int getIndex(const int value);
	void operator+(const int data);
	void operator+(const IntSetMassive& other);
	void operator-(const int data);
	void operator-(const IntSetMassive& other);
	int& operator[](const int index);
	operator int() const;

private:
	class Mass
	{
	public:
		int data;
		Mass* pNext;
		Mass(int data = 0, Mass* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int SIZE;
	Mass* pHead;
};

IntSetMassive::IntSetMassive()
{
	this->pHead = nullptr;
	this->SIZE = 0;
}

IntSetMassive::~IntSetMassive()
{
	clearAll();
}

int IntSetMassive::getSize()
{
	return SIZE;
}

void IntSetMassive::pushBack(const int data)
{
	if (IntSetMassive::check(data))
		return;
	if (this->pHead == nullptr)
	{
		this->pHead = new Mass(data);
	}
	else
	{
		Mass* pTemp = this->pHead;
		while (pTemp->pNext != nullptr)
		{
			pTemp = pTemp->pNext;
		}
		pTemp->pNext = new Mass(data);
	}
	this->SIZE++;
}

void IntSetMassive::PrintMass()
{
	Mass* pTemp = this->pHead;
	while (pTemp != nullptr)
	{
		cout << pTemp->data << " ";
		pTemp = pTemp->pNext;
	}
}

void IntSetMassive::deleteMass(const int index)
{
	int counter = 0;
	Mass* pTemp = this->pHead;

	if (counter == index)
	{
		this->pHead = this->pHead->pNext;
		delete pTemp;
	}

	else
	{

		for (; counter < index - 1; counter++)
		{
			pTemp = pTemp->pNext;
		}

		Mass* pTempForDelete = pTemp->pNext;
		pTemp->pNext = pTempForDelete->pNext;
		delete pTempForDelete;
	}

	this->SIZE--;
}

void IntSetMassive::clearAll()
{

	for (int i = 0; i < getSize(); i++)
	{
		deleteMass(i);
	}

	this->SIZE = 0;
}

void IntSetMassive::operator+(const int data)
{
	IntSetMassive::pushBack(data);
}

void IntSetMassive::operator+(const IntSetMassive& other)
{
	Mass* pTemp = other.pHead;
	while (pTemp != nullptr)
	{
		IntSetMassive::pushBack(pTemp->data);
		pTemp = pTemp->pNext;
	}
}

void IntSetMassive::operator-(const int data)
{
	if (IntSetMassive::check(data))
	{
		deleteMass(getIndex(data));
	}
}

void IntSetMassive::operator-(const IntSetMassive& other)
{
	Mass* pTemp = other.pHead;
	while (pTemp != nullptr)
	{
		if (IntSetMassive::check(pTemp->data))
		{
			cout << pTemp->data << " ";
		}
		pTemp = pTemp->pNext;
	}
}

int& IntSetMassive::operator[](const int index)
{
	Mass* pTemp = this->pHead;

	if (index == 0)
	{
		return pTemp->data;
	}
	else
	{
		int counter = 0;
		while (counter != index)
		{
			pTemp = pTemp->pNext;
			counter++;
		}
		return pTemp->data;
	}
}

IntSetMassive::operator int() const
{
	return SIZE;
}

int IntSetMassive::getIndex(const int value)
{
	int counter = 0;
	Mass* pTemp = this->pHead;
	while (pTemp->data != value)
	{
		pTemp = pTemp->pNext;
		counter++;
	}
	return counter;
}

bool IntSetMassive::check(const int value)
{
	Mass* pTemp = this->pHead;
	while (pTemp != nullptr)
	{
		if (pTemp->data == value)
		{
			return true;
		}
		pTemp = pTemp->pNext;
	}
	return false;
}


void firstTask()
{
	IntSetMassive it1;

	it1.pushBack(1);
	it1.pushBack(1);
	it1.pushBack(2);
	it1.pushBack(3);
	it1.pushBack(4);

	IntSetMassive it2;

	it2.pushBack(3);
	it2.pushBack(4);
	it2.pushBack(5);
	it2.pushBack(6);
	it2.pushBack(7);

	cout << "1-� ���������: ";
	it1.PrintMass();
	cout << "\n2-� ���������: ";
	it2.PrintMass();

	cout << "\n\n�������� ����� � 1-� ��������� (17): ";
	it1 + 17;
	it1.PrintMass();
	cout << "\n\n������� ����� �� 1-�� ��������� (17): ";
	it1 - 17;
	it1.PrintMass();

	cout << "\n\n����������� ��������: ";
	it1 - it2;

	cout << "\n\n����������� ��������: ";
	it1 + it2;
	it1.PrintMass();

	cout << "\n\n������� �������� �� ������ �� 1-�� ��������� (2): ";
	cout << it1[2];

	//////////////////////////////////////////////
	cout << "\n\n������� �������� ���������: "; //
	//////////////////////////////////////////////
	int n = it2;
	cout << n;

	_getch(); system("cls");
}

#pragma endregion 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region secondTask

#include "ClassesForSecondTask.h"

void secondTask()
{
	ProductFood* masF = new ProductFood[100];
	ElectronicProduct* masE = new ElectronicProduct[100];

	int counterElectronics = 0, counterProduct = 0;
	while (true)
	{
		cout << "1) ������� �������"
				"\n2) ����������� �����"
				"\n3) ���� ��������"
				"\n4) ����� ������ ����������� ������";

		int a;	cin >> a;
		system("cls");
		
		switch (a)
		{
			case(1):
			{
				int Days;
				string classfood;
				cout << "���� ��������: " << endl;
				cin >> Days;
				cout << "���������������� ��� ������: " << endl;
				cin >> classfood;
				masF[counterProduct] = ProductFood(Days, classfood);
				counterProduct++;
				
				_getch();
				system("cls");
				break;
			}
			case(2):
			{
				cout << "TypeP: " << endl;
				int TypeP;
				cin >> TypeP;
				cout << "��� ��������: " << endl;
				string TypeProduct;
				cin >> TypeProduct;
				masE[counterElectronics] = ElectronicProduct(TypeProduct, TypeP);
				counterElectronics++;

				_getch();
				system("cls");
				break;
			}
			case(3):
			{
				int id;
				cout << "ID: " << endl;
				cin >> id;
				cout << "F(Days): " << Days(masF, id) << endl;

				_getch();
				system("cls");
				break;
			}
			case(4):
			{
				cout << "Getdata: " << GetData(masE, counterElectronics) << endl;


				_getch();
				system("cls");
				break;
			}
			default:
			{
				system("cls");
				break;
			}	
		}
	}
}

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region individualTask

#include "Readers.h"

void individualTask()
{
	ListOfReaders<string> p;

	while (true)
	{
		cout << "\n1) �������� ��������";
		cout << "\n2) ����������� ��������";
		cout << "\n3) �������� ������ ��������";
		cout << "\n4) ������� ��������";
		cout << "\n5) ������� ��������";
		cout << "\n6) ����� ��������";
#if VER == 2
		cout << "\n7) ��������� ������ � ����";
		cout << "\n8) ��������� ������ �� �����";
		cout << "\n\n�����: ";
#endif
		int inputNum;	cin >> inputNum;
		system("cls");

		switch (inputNum)
		{
		case (1): {p.addReaders(); break; }
		case (2): {p.sortReaders(); break; }
		case (3): {p.transformReaders(); break; }
		case (4): {p.delReaders(); break; }
		case (5): {p.showReaders(); break; }
		case (6): {p.searchReaders(); break; }
#if VER == 2
		case (7): {p.save(); break; }
		case (8): {p.load(); break; }
#endif
		}
	}
}

#pragma endregion

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void additionalTask()
{
	_getch();
}