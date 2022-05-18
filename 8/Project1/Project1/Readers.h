#pragma once
#pragma once

#include "Nuzhnoe.h"
template<typename T>
class Data {
protected:
	static Data* add(T data);
};

template<typename T>
class DataPerson
{
protected:
	virtual void setName(T) = 0;
	virtual void setInfo(T) = 0;
	virtual void setRefPer(T) = 0;
	virtual void setReaderData(T, T, T) = 0;

	virtual T getName() = 0;
	virtual T getInfo() = 0;
	virtual T getRefPer() = 0;
	virtual T getReaderData() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class RegularReader : public DataPerson<T>
{
protected:
	T FIO;
	T NumberTicket;
	T BookName;
public:
	RegularReader();
	RegularReader(T FIO, T NumberTicket, T BookName);
	void setName(T FIO)override { this->FIO = FIO; }
	void setInfo(T NumberTicket)override { this->NumberTicket = NumberTicket; }
	void setRefPer(T BookName)	override { this->BookName = BookName; }
	void setReaderData(T FIO, T NumberTicket, T BookName) override {
		this->FIO = FIO;
		this->NumberTicket = NumberTicket;
		this->BookName = BookName;
	}

	T getName()		override { return FIO; }
	T getInfo()		override { return NumberTicket; }
	T getRefPer()		override { return BookName; }
	T getReaderData()	override { return "ФИО: " + FIO + " Номер билета: " + NumberTicket + " Назание книги: " + BookName; }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TemporaryReader : public DataPerson<T>
{
protected:
	T CurrentTerm;
	T NumberOfBooksTaken;
	T BookName;
public:
	TemporaryReader();
	TemporaryReader(
		T CurrentTerm,
		T NumberOfBooksTaken,
		T BookName
	);
	void setName(T CurrentTerm)		override { this->CurrentTerm = CurrentTerm; };
	void setInfo(T NumberOfBooksTaken)		override { this->NumberOfBooksTaken = NumberOfBooksTaken; };
	void setRefPer(T BookName)	override { this->BookName = BookName; };
	void setReaderData(T CurrentTerm, T NumberOfBooksTaken, T BookName) override {
		this->CurrentTerm = CurrentTerm;
		this->NumberOfBooksTaken = NumberOfBooksTaken;
		this->BookName = BookName;
	}
	T getName()		override { return CurrentTerm; };
	T getInfo()		override { return NumberOfBooksTaken; };
	T getRefPer()		override { return BookName; };
	T getReaderData()	override {
		return "Срок сдачи книги: "
			+ CurrentTerm + " Количество взятых книг: "
			+ NumberOfBooksTaken + " Название текущей книги: " + BookName;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class DataProduct
{
protected:
	T BookType;
	T typeOfProduct;
	T refoundPeriod;
	int numberOfBooks;
	int totalNumberOfBooks;
public:
	DataProduct();
	DataProduct(
		T BookType,
		T typeOfProduct,
		T refoundPeriod,
		int numberOfBooks,
		int totalNumberOfBooks
	);
	void setProductName(T BookType) { this->BookType = BookType; };
	void setTypeOfProduct(T typeOfProduct) { this->typeOfProduct = typeOfProduct; };
	void setPaymentDay(T refoundPeriod) { this->refoundPeriod = refoundPeriod; };
	void setNumberOfProduct(int numberOfBooks) { this->numberOfBooks = numberOfBooks; };
	void setSumOfProduct(int totalNumberOfBooks) { this->totalNumberOfBooks = totalNumberOfBooks; };

	T  getBookName() { return this->BookType; };
	T  getTypeOfBook() { return this->typeOfProduct; };
	T  getRefoundPeriod() { return this->refoundPeriod; };
	int		getNumberOfBooks() { return this->numberOfBooks; };
	int		getTotalNumberOfBooks() { return this->totalNumberOfBooks; };
	string	getDataProduct();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class ListBook : public TemporaryReader<T>, public RegularReader<T>, public DataProduct<T>
{
public:
	ListBook<T>* next;
	ListBook<T>* prev;
	bool temporaryReader;
	ListBook();
	ListBook(
		ListBook* next,
		ListBook* prev,
		bool temporaryReader,
		T BookType,
		T typeOfBook,
		T refoundPeriod,
		int numberOfBooks,
		int totalNumberOfBooks,
		T FIO,
		T NumberTicket,
		T CurrentTerm,
		T NumberOfBooksTaken,
		T BookName
	);
	void nextItem();
	void prevItem();
	ostream& operator << (ostream& os);
	istream& operator >> (ostream& os);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class ListOfReaders
{
private:
	ListBook<string>* reader = NULL;
	ListBook<string>* head = NULL;
	ListBook<string>* tail = NULL;
	void swapAndDelClients();
	void transform();
	void show();
public:
	void operator[]			(const int index);
	operator int() const;
	void addReaders();
	void sortReaders();
	void transformReaders();
	void delReaders();
	void showReaders();
	void searchReaders();
	void save();
	void load();
};