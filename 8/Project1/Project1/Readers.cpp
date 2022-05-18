#pragma once

#include "Nuzhnoe.h"

#include "Readers.h"

#pragma region RegularReader
template<typename T>
RegularReader<T>::RegularReader() {				//Постоянный читатель
	this->FIO = { "None" };
	this->NumberTicket = { "None" };
	this->BookName = { "None" };
}
template<typename T>
RegularReader<T>::RegularReader(
	T FIO,
	T NumberTicket,
	T BookName
) {
	this->FIO = FIO;
	this->NumberTicket = NumberTicket;
	this->BookName = BookName;
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region TemporaryReader
template<typename T>
TemporaryReader<T>::TemporaryReader() {					//Временный читатель
	this->CurrentTerm = { "None" };
	this->NumberOfBooksTaken = { "None" };
	this->BookName = { "None" };
}
template<typename T>
TemporaryReader<T>::TemporaryReader(
	T CurrentTerm,
	T NumberOfBooksTaken,
	T BookName
) {
	this->CurrentTerm = CurrentTerm;
	this->NumberOfBooksTaken = NumberOfBooksTaken;
	this->BookName = BookName;

}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region DataProduct
template<typename T>
DataProduct<T>::DataProduct()
{
	this->BookType = { "None" };
	this->typeOfProduct = { "None" };
	this->refoundPeriod = { "None" };
	this->numberOfBooks = 0;
	this->totalNumberOfBooks = 0;

}
template<typename T>
DataProduct<T>::DataProduct(
	T BookType,
	T typeOfProduct,
	T refoundPeriod,
	int numberOfBooks,
	int totalNumberOfBooks
) {
	this->BookType = BookType;
	this->typeOfProduct = typeOfProduct;
	this->refoundPeriod = refoundPeriod;
	this->numberOfBooks = numberOfBooks;
	this->totalNumberOfBooks = totalNumberOfBooks;
}
template<typename T>
string DataProduct<T>::getDataProduct()
{
	return "Название книги: " + this->BookType
		+ " Тип книги: " + this->typeOfProduct
		+ " День врзврата: " + this->refoundPeriod
		+ " Кол-во книг: " + to_string(this->numberOfBooks)
		+ " Общее кол-во взятых книг: " + to_string(this->totalNumberOfBooks);
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region ListBook
template<typename T>
ListBook<T>::ListBook()
{
	this->temporaryReader = false;
	this->next = NULL;
	this->prev = NULL;
}
template<typename T>
ListBook<T>::ListBook(
	ListBook* next,
	ListBook* prev,
	bool temporaryReader,
	T BookType,
	T typeOfProduct,
	T refoundPeriod,
	int numberOfBooks,
	int totalNumberOfBooks,
	T FIO,
	T NumberTicket,
	T CurrentTerm,
	T NumberOfBooksTaken,
	T BookName
) {
	this->DataProduct<string>::DataProduct(
		BookType,
		typeOfProduct,
		refoundPeriod,
		numberOfBooks,
		totalNumberOfBooks
	);
	if (temporaryReader) {
		this->TemporaryReader<string>::TemporaryReader(
			CurrentTerm,
			NumberOfBooksTaken,
			BookName
		);
	}
	else {
		this->RegularReader<string>::RegularReader(		//Физ лицо
			FIO,
			NumberTicket,
			BookName
		);
	}
	this->temporaryReader = temporaryReader;
	this->next = next;
	this->prev = prev;
}
template<typename T>
ostream& ListBook<T>::operator << (ostream& os)
{
	string personType;
	string personData;
	if (this->temporaryReader) { personType = { "Постоянный читатель" }; personData = this->TemporaryReader<string>::getReaderData(); }
	else { personType = { "Временный читатель" }; personData = this->RegularReader<string>::getReaderData(); }

	os << personType << "\n"
		<< personData << "\n"
		<< this->getDataProduct() << endl;
	return  os;
}

template<typename T>
Data<T>* Data<T>::add(T data)
{
	return this->ListItem<T>::ListItem();
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region ListOfReaders
void ListOfReaders<string>::operator[](const int index)
{
	ListBook<string>* LItemp = this->head;
	for (int i = 0; i < index; i++)
		LItemp = LItemp->next;
	LItemp->operator<<(cout);
}
ListOfReaders<string>::operator int() const
{
	ListBook<string>* LItemp = this->head;
	int counter = 0;
	if (LItemp == NULL)
	{
		cout << counter;
	}
	else
	{
		while (true)
		{
			counter++;
			if (LItemp->next = NULL) break;
			LItemp = LItemp->next;
		}
		cout << counter;
	}
	return counter;
}
void ListOfReaders<string>::addReaders()
{
	system("cls");
	cout << "Добавление читателя\n";
	cout << "\n1) Постоянный читатель\n2) Временный читатель\nВЫбор: ";
	int choice;
	cin >> choice;
	system("cls");
	switch (choice)
	{
	case(1):
	{
		string newSurname = { "None" };
		string newName = { "None" };
		string newPatronymic = { "None" };
		string newNumberTicket = { "None" };
		string newBookName = { "None" };

		string newBookType = { "None" };
		string newTypeOfBook = { "None" };
		string newRefoundPeriod = { "None" };
		char TempNewNumberOfBooks[100];
		char TempNewTotalNumberOfBooks[1000];

		cout << "\nФамилия: "; 	cin.get();			getline(cin, newSurname);
		cout << "\nИмя: ";							getline(cin, newName);
		cout << "\nОтчество: ";						getline(cin, newPatronymic);
		string newFIO = newSurname + " " + newName + " " + newPatronymic;

		cout << "\nНомер билета: ";					getline(cin, newNumberTicket);
		cout << "\nНазвание книги: ";				getline(cin, newBookName);

		cout << "\nЖанр книги: ";					getline(cin, newBookType);
		cout << "\nТип книги: ";					getline(cin, newTypeOfBook);
		cout << "\nДень возврата (ДД.ММ.ГГГГ): ";	getline(cin, newRefoundPeriod);
		cout << "\nКол-во книг: ";					cin.getline(TempNewNumberOfBooks, 100);
		int newNumberOfProduct = isInteger_l(TempNewNumberOfBooks);
		cout << "\nОбщее кол-во взятых книг: ";		cin.getline(TempNewTotalNumberOfBooks, 1000);
		int newSumOfProduct = isInteger_l(TempNewTotalNumberOfBooks);
		bool newLegalPerson = false;
		system("cls");

		if (reader == NULL)
		{
			tail = new ListBook<string>(
				NULL,
				NULL,
				newLegalPerson,
				newBookType,
				newTypeOfBook,
				newRefoundPeriod,
				newNumberOfProduct,
				newSumOfProduct,
				newFIO,
				newNumberTicket,
				"None",
				"None",
				newBookName);
			reader = tail;
			head = tail;
		}
		else if (tail != NULL)
		{
			reader = tail;
			reader->next = new ListBook<string>(
				NULL,
				reader,
				newLegalPerson,
				newBookType,
				newTypeOfBook,
				newRefoundPeriod,
				newNumberOfProduct,
				newSumOfProduct,
				newFIO,
				newNumberTicket,
				"None",
				"None",
				newBookName);;
			//person->next->prev = person;
			reader = reader->next;
			tail = reader;
		}

		cout << "\nДобавлен"
			<< "\n\nФИО: " << newFIO
			<< "\nНомер билеты: " << newNumberTicket
			<< "\nНазвание книги: " << newBookName
			<< "\nЖанр книги: " << newTypeOfBook
			<< "\nТип книги: " << newTypeOfBook
			<< "\nДень возврата (ДД.ММ.ГГГГ): " << newRefoundPeriod
			<< "\nКол-во книг: " << newNumberOfProduct
			<< "\nОбщее кол-во взятых книг: " << newSumOfProduct;
		cout << "\n\n";
		
		_getch();
		system("cls");
		return;
	}
	case(2):
	{
		string newCurrentTerm = { "None" };
		char TempNewNumberOfBooksTaken[20];
		char TempNewBookName[50];

		string newBookType = { "None" };
		string newtypeOfBook = { "None" };
		string newrefoundPeriod = { "None" };
		char TempNewNumberOfBooks[100];
		char TempNewtotalNumberOfBooks[1000];

		cout << "\nКол-во книг: "; cin.get(); getline(cin, newCurrentTerm);
		cout << "\nОбщее кол-во взятых книг: ";					cin.getline(TempNewNumberOfBooksTaken, 20);
		string newNumberOfBooksTaken = { "None" };
		newNumberOfBooksTaken = to_string(isInteger_l(TempNewNumberOfBooksTaken));
		cout << "\nНазвание книги: ";				cin.getline(TempNewBookName, 50);
		string newBookName = { "None" };
		newBookName = to_string(isInteger_l(TempNewBookName));

		cout << "\nЖанр книги: ";			getline(cin, newBookType);
		cout << "\nТип книги: ";				getline(cin, newtypeOfBook);
		cout << "\nДень возврата (ДД.ММ.ГГГГ): ";	getline(cin, newrefoundPeriod);
		cout << "\nКол-во книг: ";			cin.getline(TempNewNumberOfBooks, 100);
		int newnumberOfBooks = isInteger_l(TempNewNumberOfBooks);
		cout << "\nОбщее кол-во книг: ";				cin.getline(TempNewtotalNumberOfBooks, 1000);
		int newtotalNumberOfBooks = isInteger_l(TempNewtotalNumberOfBooks);
		bool newtemporaryReader = true;
		system("cls");

		if (tail == NULL && head == NULL)
		{
			tail = new ListBook<string>(NULL,NULL,newtemporaryReader,newBookType,newtypeOfBook,newrefoundPeriod,newnumberOfBooks,newtotalNumberOfBooks,"None","None",newCurrentTerm,newNumberOfBooksTaken,newBookName);
			reader = tail;
			head = tail;

		}
		else if (tail != NULL)
		{
			reader = tail;
			reader->next = new ListBook<string>(NULL,reader,newtemporaryReader,newBookType,newtypeOfBook,newrefoundPeriod,newnumberOfBooks,newtotalNumberOfBooks,"None","None",newCurrentTerm,newNumberOfBooksTaken,newBookName);
			reader = reader->next;
			tail = reader;
		}

		system("pause");
		system("cls");
		return;
	}
	default: {
		cout << "\n\tОшибка ввода ";
		system("pause");
		system("cls");
		return;
	}
	}
}
void ListOfReaders<string>::sortReaders()
{
	if (tail == NULL || head == NULL)
	{
		cout << "\nНет данных для сортировки";
		system("cls");
		return;
	}
	if (reader == head && reader == tail)
	{
		cout << "\nНет данных для сортировки\n";
		system("cls");
		return;
	}
	reader = head;
	int counter = 1;
	while (true) {
		counter++;
		reader = reader->next;
		if (reader == tail) break;
	}
	reader = head;
	if (reader == head && reader->next == tail) {
		for (int i = 1; i < counter; i++) {
			reader = head;
			for (int j = 0; j < counter - i; j++) {
				if (reader->getTotalNumberOfBooks() > reader->next->getNumberOfBooks()) {
					ListBook<string>* TempNext1 = reader->next;
					ListBook<string>* TempPrev1 = reader->prev;
					ListBook<string>* TempNext2 = reader->next->next;
					ListBook<string>* TempPrev2 = reader->next->prev;
					head = reader->next;
					reader->next->next = reader;
					reader->prev = reader->next;
					reader->next->prev = NULL;
					reader->next = NULL;
				}
				reader = reader->next;
			}
		}
	}
	else if (reader == head && reader->next != tail) {
		for (int i = 1; i < counter; i++)
		{
			reader = head;

			for (int j = 0; j < counter - i; j++)
			{
				if (reader->getTotalNumberOfBooks() > reader->next->getNumberOfBooks())
				{
					ListBook<string>* Temp1 = reader;
					ListBook<string>* Temp2 = reader->next;
					ListBook<string>* Temp3 = reader->next->next;

					head = reader->next;
					Temp3->prev = Temp1;
					Temp2->next = Temp1;
					Temp2->prev = NULL;
					Temp1->next = Temp3;
					Temp1->prev = Temp2;
				}
				reader = reader->next;
			}
		}
	}
	else if (reader != head && reader->next == tail) {
		for (int i = 1; i < counter; i++)
		{
			reader = head;

			for (int j = 0; j < counter - i; j++)
			{
				if (reader->getTotalNumberOfBooks() > reader->next->getNumberOfBooks())
				{
					ListBook<string>* Temp1 = reader->prev;
					ListBook<string>* Temp2 = reader;
					ListBook<string>* Temp3 = reader->next;

					tail = reader->next;
					Temp1->next = Temp3;
					Temp2->next = NULL;
					Temp2->prev = Temp3;
					Temp3->next = Temp2;
					Temp3->prev = Temp1;
				}
				reader = reader->next;
			}
		}
	}
	else if (reader != head && reader->next != tail) {
		for (int i = 1; i < counter; i++)
		{
			reader = head;

			for (int j = 0; j < counter - i; j++)
			{
				if (reader->getTotalNumberOfBooks() > reader->next->getNumberOfBooks())
				{
					ListBook<string>* Temp1 = reader->prev;
					ListBook<string>* Temp2 = reader;
					ListBook<string>* Temp3 = reader->next;
					ListBook<string>* Temp4 = reader->next->next;

					Temp1->next = Temp3;
					Temp2->next = Temp4;
					Temp2->prev = Temp3;
					Temp3->next = Temp2;
					Temp3->prev = Temp1;
					Temp4->prev = Temp2;
				}
				reader = reader->next;
			}
		}
	}
	system("pause");
	system("cls");
	return;
}
void ListOfReaders<string>::transform()
{

	if (reader->temporaryReader)
	{
		cout<< "\n1) Срок сдачи книги - " << reader->TemporaryReader::getName()
			<< "\n2) Количество взятых книг" << reader->TemporaryReader::getInfo()
			<< "\n3) Название текущей книги - " << reader->TemporaryReader::getRefPer();
	}
	else
	{
		cout<< "\n1) ФИО - " << reader->RegularReader::getName()
			<< "\n2) Номер билета" << reader->RegularReader::getInfo()
			<< "\n3) Срок возврата - " << reader->RegularReader::getRefPer();
	}
	cout<< "\n4) Название книги - " << reader->getBookName()
		<< "\n5) Жанр книги - " << reader->getTypeOfBook()
		<< "\n6) День возврата (ДД.ММ.ГГГГ) - " << reader->getRefoundPeriod()
		<< "\n7) Кол-во книг - " << reader->getNumberOfBooks()
		<< "\n8) Общее кол-во взятых книг - " << reader->getTotalNumberOfBooks();

	char choice;
	cin >> choice;

	int InInt = isInteger(choice);

	switch (InInt)
	{
	case(1):
	{
		if (reader->temporaryReader)
		{
			cout << "\nВведите срок сдачи книги: ";
			string CurrentTerm;
			cin.get(); getline(cin, CurrentTerm);
			reader->TemporaryReader::setName(CurrentTerm);
		}
		else
		{
			cout << "\nВведите ФИО: ";
			string name, surname, pathr;
			cin.get(); getline(cin, surname);
			getline(cin, name);
			getline(cin, pathr);
			string FIO = surname + " " + name + " " + pathr;
			reader->RegularReader::setName(FIO);
		}
		break;
	}
	case(2):
	{
		if (reader->temporaryReader)
		{
			cout << "\nВведите количество взятых книг: ";
			char charInfoNum[100];
			cin.get(); cin.getline(charInfoNum, 100);
			reader->TemporaryReader::setInfo(to_string(isInteger_l(charInfoNum)));
		}
		else {
			cout << "\nВведите номер билета: ";
			char charMobNum[100];
			cin.get(); cin.getline(charMobNum, 100);
			reader->TemporaryReader::setInfo(to_string(isInteger_l(charMobNum)));
		}
		break;
	}
	case(3):
	{
		cout << "\nКоличество взятых книг: ";
		char charNumberOfBooksTaken[100];
		cin.get(); cin.getline(charNumberOfBooksTaken, 100);
		if (reader->temporaryReader) reader->TemporaryReader::setInfo(to_string(isInteger_l(charNumberOfBooksTaken)));
		else reader->TemporaryReader::setInfo(to_string(isInteger_l(charNumberOfBooksTaken)));
		break;
	}
	case(4):
	{
		cout << "\n\n\tВведите название книги: ";
		cin.get();
		string BookType;
		getline(cin, BookType);
		reader->setProductName(BookType);
		break;
	}
	case(5): {cout << "\nВведите тип книги: ";
		cin.get();
		string productType;
		getline(cin, productType);
		reader->setTypeOfProduct(productType);
		break;
	}
	case(6):
	{
		cout << "\n\n\tВведите день оплаты (ДД.ММ.ГГГГ): ";
		cin.get();
		string payDay;

		getline(cin, payDay);
		reader->setPaymentDay(payDay);

		break;
	}
	case(7):
	{
		cout << "\nВведите кол-во книг: ";
		cin.get();
		char charNumOfProduct[100];
		cin.getline(charNumOfProduct, 100);

		int numOfProduct = isInteger_l(charNumOfProduct);
		reader->setNumberOfProduct(numOfProduct);

		break;
	}
	case(8):
	{
		cout << "\n\n\tВведите общее кол-во взятых книг: ";
		cin.get();
		char charSummOfProduct[1000];
		cin.getline(charSummOfProduct, 1000);

		int summOfProduct = isInteger_l(charSummOfProduct);
		reader->setNumberOfProduct(summOfProduct);

		break;
	}
	}
	system("cls");
}
void ListOfReaders<string>::transformReaders()
{
	if (tail == NULL && head == NULL)
	{
		cout << "\nНет данных для изменения\n";

		system("pause");
		system("cls");

		return;
	}
	cout << "\n1) постоянный читатель"
		<< "\n2) Временный читатель\nВыбор: ";

	char charInputNum;
	cin >> charInputNum;
	int inputNum = isInteger(charInputNum);
	reader = head;
	string inputSurname, inputName, inputPathr, inputFIO, inputCompanuName;
	switch (inputNum)
	{
	case(1):
	{
		cout << "\n\n\tВведите Фамилию, Имя и Отчество. 0. Выход\n\n\t";
		cin >> inputSurname >> inputName >> inputPathr;
		inputFIO = inputSurname + " " + inputName + " " + inputPathr;
		if (inputSurname == "0" || inputName == "0" || inputPathr == "0" || inputFIO == "0") return;
		system("cls");
		int searchID = -1;
		int couErr = 0;
		int id = 1;
		while (true)
		{
			if (inputFIO == reader->RegularReader::getName()) { searchID = id; couErr++; }
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (couErr > 1)
		{
			cout << "\n\n\tНайдено более одного читателя";
			system("pause");
			system("cls");
			return;
		}
		if (searchID == -1)
		{
			cout << "\nЧитатель не найден";
			system("pause");
			system("cls");
			return;
		}
		if (searchID >= 0)
		{
			reader = head;
			for (int i = 0; i < searchID - 1; i++) {
				reader = reader->next;
			}
			cout << "\nИзменить данные клиента? ";
			reader->operator<<(cout)
				<< "\n1) Да\t2) Нет\nВыбор: ";
			cin >> charInputNum;
			inputNum = isInteger(charInputNum);
			system("cls");
			switch (inputNum) {
			case(1): {transform(); return; }
			case(2): return;
			}
		}
	}
	case(2):
	{
		cout << "\nВведите срок сдачи.\nВвод: ";
		getline(cin, inputCompanuName);
		if (inputCompanuName == "0")
			return;

		system("cls");

		int searchID = -1;
		int couErr = 0;
		int id = 1;

		while (true)
		{
			if (inputCompanuName == reader->TemporaryReader::getName()) { searchID = id; couErr++; }
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (couErr > 1)
		{
			cout << "\nНайдено более одного читателя";

			system("pause");
			system("cls");

			return;
		}
		if (searchID == -1)
		{
			cout << "\nЧитатель не найден";

			system("pause");
			system("cls");

			return;
		}
		if (searchID >= 0)
		{
			reader = head;
			for (int i = 0; i < searchID - 1; i++) {
				reader = reader->next;
			}
			cout << "\nИзменить данные читателя "; reader->operator<<(cout) << "\n1) Да\t2) Нет\nВыбор: ";
			cin >> charInputNum;
			inputNum = isInteger(charInputNum);
			system("cls");
			switch (inputNum)
			{
			case(1): {transform(); return; }
			case(2): return;
			}
		}
	}
	}
	system("cls");
}
void ListOfReaders<string>::swapAndDelClients()
{
	if (reader != head && reader != tail)
	{
		reader->prev->next = reader->next;
		reader->next->prev = reader->prev;
		delete reader;
	}
	else if (reader == head && reader != tail)
	{
		head = reader->next;
		head->prev = NULL;
		delete reader;
	}
	else if (reader == tail && reader != head)
	{
		tail = reader->prev;
		tail->next = NULL;
		delete reader;
	}
	else
	{
		head = NULL;
		tail = NULL;
		delete reader;
	}
	return;
}
void ListOfReaders<string>::delReaders()
{
	if (tail == NULL && head == NULL)
	{
		cout << "\nНет данных для удаления\n";
		system("pause");
		system("cls");
		return;
	}
	cout << "\n1) Постоянный читатель"
		<< "\n2) Временный читатель"
		<< "\nВыбор: ";
	char charInputNum;
	cin >> charInputNum;
	int inputNum = isInteger(charInputNum);
	reader = head;
	string inputSurname, inputName, inputPathr, inputFIO, inputCompanuName;
	switch (inputNum)
	{
	case(0): return;
	case(1):
	{
		cout << "\nВведите Фамилию, Имя и Отчество.\nВвод: ";
		cin >> inputSurname >> inputName >> inputPathr;
		inputFIO = inputSurname + " " + inputName + " " + inputPathr;
		if (inputSurname == "0" || inputName == "0" || inputPathr == "0" || inputFIO == "0") return;
		system("cls");
		int searchID = -1;
		int couErr = 0;
		int id = 1;
		while (true)
		{
			if (inputFIO == reader->RegularReader::getName())
			{
				searchID = id;
				couErr++;
			}
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (couErr > 1)
		{
			cout << "\nНайдено более одного читателя";

			system("pause");
			system("cls");

			return;
		}
		if (searchID == -1)
		{
			cout << "\nЧитатель не найден";

			system("pause");
			system("cls");

			return;
		}
		if (searchID >= 0) {
			reader = head;
			for (int i = 1; i < searchID; i++)
				reader = reader->next;
			cout << "\nУдалить данные читателя ";
			reader->operator<<(cout)
				<< "\n1) Да\t2) Нет\nВыбор: ";
			cin >> charInputNum;
			inputNum = isInteger(charInputNum);
			system("cls");
			switch (inputNum)
			{
			case(1): {swapAndDelClients(); return; }
			case(2): return;
			}
		}
	}
	case(2): {
		cout << "\n\n\tВведите название компании. 0. Выход\n\n\t";
		getline(cin, inputCompanuName);
		if (inputCompanuName == "0") return;
		system("cls");
		int searchID = -1;
		int couErr = 0;
		int id = 1;
		while (true) {
			if (inputCompanuName == reader->TemporaryReader::getName()) { searchID = id; couErr++; }
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (couErr > 1) {
			cout << "\n\n\tНайдено более одного клиента\n";
			system("pause");
			system("cls");
			return;
		}
		if (searchID == -1) {
			cout << "\n\n\tКлиент не найден";
			system("pause");
			system("cls");
			return;
		}
		if (searchID >= 0) {
			reader = head;
			for (int i = 1; i < searchID; i++)
				reader = reader->next;
			cout << "\n\n\tУдалить данные клиента ";
			reader->operator<<(cout)
				<< "\n\n\t1. Да\t2. Нет\n\n\t";
			cin >> charInputNum;
			inputNum = isInteger(charInputNum);
			system("cls");
			switch (inputNum) {
			case(1): {swapAndDelClients(); return; }
			case(2): return;
			default: {
				cout << "\n\n\tВведено неверное значение";
				system("pause");
				system("cls");
				return;
			}
			}
		}
	}
	default: {
		cout << "\n\n\tВведено неверное значение\n";
		system("pause");
		system("cls");
		return;
	}
	}
	reader = head;
	system("cls");
	return;
}
void ListOfReaders<string>::showReaders()
{
	if (tail == NULL && head == NULL)
	{
		cout << "\nНет данных\n";
		system("pause");
		system("cls");
		return;
	}
	reader = head;
	cout << endl;
	while (true)
	{
		cout << "\n\t";
		reader->operator<<(cout);
		if (reader->next == NULL)break;
		reader = reader->next;
	}
	cout << "\n\n\t";

	system("pause");
	system("cls");

	return;
}
void ListOfReaders<string>::searchReaders()
{
	if (tail == NULL && head == NULL)
	{
		cout << "\nНет данных";

		system("pause");
		system("cls");

		return;
	}
	cout << "\n1) Постоянный читатель"
		<< "\n2) Временный читатель"
		<< "\nвыбор: ";
	char charInputNum;
	cin >> charInputNum;
	int inputNum = isInteger(charInputNum);
	reader = head;
	string inputSurname, inputName, inputPathr, inputFIO, inputCompanuName;
	switch (inputNum)
	{
	case(0): return;
	case(1): {
		cout << "\nВведите Фамилию, Имя и Отчество\nВвод: ";
		cin >> inputSurname >> inputName >> inputPathr;
		inputFIO = inputSurname + " " + inputName + " " + inputPathr;
		if (inputSurname == "0" || inputName == "0" || inputPathr == "0" || inputFIO == "0") return;
		system("cls");
		int searchID = -1;
		int couErr = 0;
		int id = 1;
		while (true)
		{
			if (inputFIO == reader->RegularReader::getName()) {
				searchID = id;
				cout << "\n\t";
				reader->operator<<(cout);
				cout << endl;
			}
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (searchID == -1) cout << "\nЧитатель не найден";
		cout << "\n\t";

		system("pause");
		system("cls");

		return;
	}
	case(2):
	{
		cout << "\nВведите срок сдачи книги\nВвод: ";
		getline(cin, inputCompanuName);
		if (inputCompanuName == "0") return;

		system("cls");

		int searchID = -1;
		int couErr = 0;
		int id = 1;
		while (true)
		{
			if (inputCompanuName == reader->TemporaryReader::getName()) {
				searchID = id;
				cout << "\n\t";
				reader->operator<<(cout);
				cout << endl;
			}
			if (reader->next == NULL) break;
			reader = reader->next;
			id++;
		}
		if (searchID == -1) cout << "\nЧитатель не найден";

		system("pause");
		system("cls");

		return;
	}
	}
	reader = head;
	system("cls");
	return;
}
void ListOfReaders<string>::save()
{
	if (tail == NULL && head == NULL)
	{
		cout << "\n\n\tНет данных для сохранения...";
		system("pause");
		system("cls");
		return;
	}
	string defaultFileName = (INDIVID_OUTPUT_FILE_LOCATION);
	cout << "\n1) Сохранить в файле по умолчанию\n2)Сохранить в своем файле\nВыбор: ";
	char charInputNum;
	cin >> charInputNum;
	int inputNum = isInteger(charInputNum);
	system("cls");
	switch (inputNum)
	{
	case(1):
	{
		ofstream outClients(INDIVID_OUTPUT_FILE_LOCATION);
		reader = head;
		while (true)
		{
			reader->operator<<(outClients);
			if (reader == tail) break;
			reader = reader->next;
		}
		char p = _getch();
		system("cls");
		break;
	}
	case(2):
	{
		cout << "\nВведите навание файла: ";
		string newName;
		cin.get();
		getline(cin, newName);
		newName += ".txt";
		system("cls");
		ofstream outClients(newName);
		reader = head;
		while (true)
		{
			reader->operator<<(outClients);
			if (reader == tail) break;
			reader = reader->next;
		}
		char p = _getch();
		system("cls");
		break;
	}
	}
}
void ListOfReaders<string>::load()
{
	cout << "\n1) Загрузтиь из файла по умолчанию\n2)Загрузить из своего файла\nВыбор: ";
	char charInputNum;
	cin >> charInputNum;
	int inputNum = isInteger(charInputNum);
	system("cls");
	string newFIO = { "None" };
	string newCompanyName = { "None" };
	string newMobilePhoneNumber = { "None" };
	string newCustomerINN = { "None" };
	string newAccountNumber = { "None" };

	bool newLegalPerson = false;
	string newProductName = { "None" };
	string newTypeOfProduct = { "None" };
	string newPaymentDay = { "None" };
	int newNumberOfProduct = 0;
	int	newSumOfProduct = 0;
	switch (inputNum)
	{
	case(0): return;
	case(1):
	{
		ifstream inClients(INDIVID_INPUT_FILE_LOCATION);
		if (inClients.bad())
		{
			cout << "\nОшибка ввода-вывода при чтении";
			system("pause");
			system("cls");
			return;
		}
		if (inClients.eof())
		{
			cout << "\nДостигнут конец файла";
			system("pause");
			system("cls");
			return;
		}
		if (inClients.fail())
		{
			cout << "\nНеверный формат данных";
			system("pause");
			system("cls");
			return;
		}
		int size = 0;
		inClients >> size;
		for (int i = 0; i < size; i++)
		{
			inClients.get();
			string typeOfPerson;
			getline(inClients, typeOfPerson);
			if (typeOfPerson == "Постоянный читатель")
			{
				newLegalPerson = false;
				getline(inClients, newFIO);
				getline(inClients, newMobilePhoneNumber);
				getline(inClients, newAccountNumber);
				getline(inClients, newProductName);
				getline(inClients, newTypeOfProduct);
				getline(inClients, newPaymentDay);
				inClients >> newNumberOfProduct;
				inClients >> newSumOfProduct;
			}
			else if (typeOfPerson == "Временный читатель")
			{
				newLegalPerson = true;
				getline(inClients, newCompanyName);
				getline(inClients, newCustomerINN);
				getline(inClients, newAccountNumber);
				getline(inClients, newProductName);
				getline(inClients, newTypeOfProduct);
				getline(inClients, newPaymentDay);
				inClients >> newNumberOfProduct;
				inClients >> newSumOfProduct;
			}
			if (head == NULL)
			{
				reader = new ListBook<string>(
					NULL,
					NULL,
					newLegalPerson,
					newProductName,
					newTypeOfProduct,
					newPaymentDay,
					newNumberOfProduct,
					newSumOfProduct,
					newFIO,
					newMobilePhoneNumber,
					newCompanyName,
					newCustomerINN,
					newAccountNumber
				);
				head = reader;
				tail = reader;
			}
			else
			{
				reader = tail;
				reader->next = new ListBook<string>(
					NULL,
					NULL,
					newLegalPerson,
					newProductName,
					newTypeOfProduct,
					newPaymentDay,
					newNumberOfProduct,
					newSumOfProduct,
					newFIO,
					newMobilePhoneNumber,
					newCompanyName,
					newCustomerINN,
					newAccountNumber
				);
				reader->next->prev = reader;
				reader = reader->next;
				tail = reader;
			}
			newLegalPerson = false;
			newFIO = newCompanyName = newMobilePhoneNumber
				= newCustomerINN = newAccountNumber = newProductName
				= newTypeOfProduct = newPaymentDay = { "None" };
			newNumberOfProduct = newSumOfProduct = 0;
		}
		char p = _getch();
		system("cls");
		break;
	}
	case(2):
	{
		cout << "\nВведите навание файла: ";
		string newName;
		cin.get();
		getline(cin, newName);
		newName += ".txt";
		system("cls");
		ifstream inClients(newName);
		if (inClients.bad())
		{
			cout << "\nОшибка ввода-вывода при чтении";
			system("pause");
			system("cls");
			return;
		}
		if (inClients.eof())
		{
			cout << "\nДостигнут конец файла";
			system("pause");
			system("cls");
			return;
		}
		if (inClients.fail())
		{
			cout << "\nНеверный формат данных";
			system("pause");
			system("cls");
			return;
		}
		int size = 0;
		inClients >> size;
		for (int i = 0; i < size; i++) {
			inClients.get();
			string typeOfPerson;
			getline(inClients, typeOfPerson);
			if (typeOfPerson == "Постоянный читатель") {
				newLegalPerson = false;
				getline(inClients, newFIO);
				getline(inClients, newMobilePhoneNumber);
				getline(inClients, newAccountNumber);
				getline(inClients, newProductName);
				getline(inClients, newTypeOfProduct);
				getline(inClients, newPaymentDay);
				inClients >> newNumberOfProduct;
				inClients >> newSumOfProduct;
			}
			else if (typeOfPerson == "Временный читатель") {
				newLegalPerson = true;
				getline(inClients, newCompanyName);
				getline(inClients, newCustomerINN);
				getline(inClients, newAccountNumber);
				getline(inClients, newProductName);
				getline(inClients, newTypeOfProduct);
				getline(inClients, newPaymentDay);
				inClients >> newNumberOfProduct;
				inClients >> newSumOfProduct;
			}
			if (head == NULL)
			{
				reader = new ListBook<string>(
					NULL,
					NULL,
					newLegalPerson,
					newProductName,
					newTypeOfProduct,
					newPaymentDay,
					newNumberOfProduct,
					newSumOfProduct,
					newFIO,
					newMobilePhoneNumber,
					newCompanyName,
					newCustomerINN,
					newAccountNumber
				);
				head = reader;
				tail = reader;
			}
			else
			{
				reader = tail;
				reader->next = new ListBook<string>(
					NULL,
					NULL,
					newLegalPerson,
					newProductName,
					newTypeOfProduct,
					newPaymentDay,
					newNumberOfProduct,
					newSumOfProduct,
					newFIO,
					newMobilePhoneNumber,
					newCompanyName,
					newCustomerINN,
					newAccountNumber
				);
				reader->next->prev = reader;
				reader = reader->next;
				tail = reader;
			}
			newLegalPerson = false;
			newFIO = newCompanyName = newMobilePhoneNumber
				= newCustomerINN = newAccountNumber = newProductName
				= newTypeOfProduct = newPaymentDay = { "None" };
			newNumberOfProduct = newSumOfProduct = 0;
		}
		char p = _getch();
		system("cls");
		break;
	}
	}
}
#pragma endregion