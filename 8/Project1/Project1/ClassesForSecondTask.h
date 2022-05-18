#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>

using namespace std;

class Product
{
public:
	virtual operator string() const = 0;
	virtual void show() = 0;
	virtual int GetAny() = 0;
};

class ProductFood : Product
{
protected:
	int Days;
	string classfood;
public:
	ProductFood()
	{
		classfood = "*";
	}
	ProductFood(int Days, string classfood)
	{
		this->Days = Days;
		this->classfood = classfood;
	}
	operator string() const override
	{
		return to_string(Days);
	}
	void show() override
	{
		cout << "Days: " << Days << endl;
		cout << "classfood: " << classfood << endl;
	}
	int GetAny() override
	{
		return Days;
	}
};

class FreshProduct : ProductFood
{
public:
	FreshProduct() :ProductFood(Days, classfood)
	{
		this->Days = Days;
		this->classfood = classfood;
	}
};

class CannedFood : ProductFood
{
protected:
	int daysClose;
	int daysOpen;
	bool Close;
public:
	CannedFood()
	{
		daysClose = 0;
		daysOpen = 0;
		Close = false;
	}
	CannedFood(int daysClose, int daysOpen, bool Close) :ProductFood(Days, classfood)
	{
		this->daysClose = daysClose;
		this->daysOpen = daysOpen;
		this->Close = Close;
		this->Days = Days;
		this->classfood = classfood;
	}
	void show() override
	{
		cout << "DaysClose: " << daysClose << endl;
		cout << "DaysOpen: " << daysOpen << endl;
		cout << "Close: " << Close << endl;
		cout << "Days: " << Days << endl;
		cout << "ClassFood" << classfood << endl;
	}
};

class ElectronicProduct :Product
{
protected:
	string TypeProduct;
	int TypeP;
public:
	ElectronicProduct()
	{
		TypeProduct = "*";
	}
	ElectronicProduct(string TypeProduct, int TypeP)
	{
		this->TypeProduct = TypeProduct;
		this->TypeP = TypeP;
	}
	operator string() const override
	{
		return "TypeP: " + to_string(TypeP) + "\n" + "TypeProduct: " + TypeProduct;
	}
	void show() override
	{
		cout << "TypeProduct: " << TypeProduct << endl;
		cout << "TypeP: " << TypeP << endl;
	}
	int GetAny() override
	{
		return TypeP;
	}
};

class Accessories : ElectronicProduct
{
protected:
	string TypeAcces;
public:
	Accessories()
	{
		TypeAcces = "*";
	}
	Accessories(string TypeAcces) :ElectronicProduct(TypeProduct, TypeP)
	{
		this->TypeAcces = TypeAcces;
		this->TypeProduct = TypeProduct;
		this->TypeP = TypeP;
	}

	void show() override
	{
		cout << "TypeProduct: " << TypeProduct << endl;
		cout << "TypeAcces: " << TypeAcces << endl;
		cout << "TypeP: " << TypeP << endl;
	}
};

int Days(ProductFood* masF, int count)
{
	return masF[count].GetAny() * 365;
}

string GetData(ElectronicProduct* masE, int count)
{
	return masE->operator std::string();
}