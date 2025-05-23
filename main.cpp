#include <iostream>
#include <string>
#include "Header1.h"
#include <list>
using namespace std;

enum class CheeseFreshness : int
{
	fresh,
	normal,
	old,
	Unknown

};
/////////////////////////////////////Лабораторная работа № 5 (паттерны проектирования, часть 3)/////////////////////////////////////
enum class WayOfEatingCheese : int
{
	WithASandwich,
	InASalad,
	Slice,

	None
};

class EatingStrategy
{
public:
	virtual ~EatingStrategy() {}
	virtual void Eat() = 0;
};

class SandwichEatingStrategy : public EatingStrategy
{
	void Eat() { cout << "съем сыр на бутерброде"; }
};

class  InASaladEatingStrategy : public EatingStrategy
{
	void Eat() { cout << "съем сыр в салате"; }
};

class  SliceEatingStrategy : public EatingStrategy
{
	void Eat() { cout << "съем ломнит сыра"; }
};

EatingStrategy* CreateEatingStrategy(WayOfEatingCheese absorptionMethod)
{
	switch (absorptionMethod)
	{
	case WayOfEatingCheese::WithASandwich: return new SandwichEatingStrategy;
	case WayOfEatingCheese::InASalad:return new InASaladEatingStrategy;
	case WayOfEatingCheese::Slice: return new SliceEatingStrategy;
	default: return nullptr;
	}
}



class Cheese
{
private:
	CheeseFreshness Freshness;
	double Weight;
	int Price;
	EatingStrategy* AbsorptionMethod;
	void AcquisitionStrategy()
	{
		if (AbsorptionMethod == nullptr)
		{
			cout << "Викинул сыр";
			return;
		}
		else
		{
			AbsorptionMethod->Eat();
		}
	}

	void FreshnessCheese()
	{
		if (GetFreshness()== CheeseFreshness::fresh || GetFreshness() == CheeseFreshness::normal)
		{
			cout << "свежий";
		}
		else
		{
			cout << "не свежий";
		}
	}
protected:
	bool Mold;
	string Hardness;
public:
	Cheese(CheeseFreshness Freshness, double Weight, int Price, string Hardness, bool Mold);
	Cheese();
	virtual ~Cheese();

	virtual double GetWeight() const
	{
		return Weight;
	}

	virtual int GetPrice() const
	{
		return Price;
	}

	string GetHardness() const
	{
		return Hardness;
	}

	string GetHeavy() const
	{
		if (Weight > 500)
		{
			return "я тяжелый СЫР!!!";
		}
		else
		{
			return "я легкий сыр)";
		}
	}
	string GetMold() const
	{
		if (Mold)
		{
			return "Сыр с плесенью";
		}
		else
		{
			return "Сыр без плесени";
		}


	}
	virtual void Name() = 0;
	virtual void Сooking() = 0;
	void Eat()
	{
		Name();
		cout << " ";
		FreshnessCheese();
		cout << " ";
		Сooking();
		cout << " ";
		AcquisitionStrategy();
		cout << endl;
	}
	CheeseFreshness GetFreshness() const { return Freshness; }
	void SetEatingManner(EatingStrategy* eatingManner) { AbsorptionMethod = eatingManner; }
};
Cheese::Cheese(CheeseFreshness Freshness, double Weight, int Price, string Hardness, bool Mold) : Freshness(Freshness), Weight(Weight), Price(Price), Hardness(Hardness), Mold(Mold)
{
	//cout << "создан родительсий класс \"СЫР\" " << endl;
}
Cheese::Cheese() : Weight(0.0), Price(0), Hardness(""), Mold(0)
{
	//cout << "создан родительсий класс \"СЫР\" " << endl;
}
Cheese::~Cheese()
{
	//cout << "удалён родительсий класс \"СЫР\"" << endl;
}

class Chedder : public Cheese
{
public:
	Chedder(double Weight, int Price, string Hardness, bool Mold);
	~Chedder();
	void SetHardness(string Vname)
	{
		Hardness = Vname;
	}
	void Name() { cout << "Чеддр"; }
	void Сooking() { cout << "Просто достать с упаковки"; }
};
Chedder::Chedder(double Weight, int Price, string Hardness, bool Mold) : Cheese(CheeseFreshness::normal, 550, Price, Hardness, Mold)
{
	SetEatingManner(CreateEatingStrategy(WayOfEatingCheese::WithASandwich));
	//cout << "создан наследник \"Чеддр\" " << endl;
}
Chedder::~Chedder()
{
	//cout << "наследник \"Чеддр\" удален" << endl;
}

class Camembert : public Cheese
{
public:
	Camembert(double Weight, int Price, string Hardness);
	~Camembert();
	void Eat();
	void Name() { cout << "Камамбер"; }
	void Сooking() { cout << "подержать в тепле 10 минут"; }

};
Camembert::Camembert(double Weight, int Price, string Hardness) : Cheese(CheeseFreshness::old, 600, Price, Hardness, 1)
{
	SetEatingManner(CreateEatingStrategy(WayOfEatingCheese::InASalad));
	//cout << "создан наследник \"камамбер\" " << endl;
}
Camembert::~Camembert()
{
	//cout << "наследник \"камамбер\" удален" << endl;
}
void Camembert::Eat()
{
	cout << "eм камамбер..." << endl;
}

class Roquefort : public Cheese
{
public:
	Roquefort(double Weight, int Price, string Hardness, bool Mold);
	~Roquefort();
	void SetMold(bool VMold)
	{
		Mold = VMold;
	}
	void Name() { cout << "Рокфор"; }
	void Сooking() { cout << "подержать в холоде 20 минут"; }
};
Roquefort::Roquefort(double Weight, int Price, string Hardness, bool Mold) : Cheese(CheeseFreshness::normal, 420, Price, Hardness, Mold)
{
	SetEatingManner(CreateEatingStrategy(WayOfEatingCheese::Slice));
	//cout << "создан наследник \"Рокфор\"" << endl;
}
Roquefort::~Roquefort()
{
	//cout << "наследник \"Рокфор\" удален" << endl;
}

// Начало Лабораторная работа № 3 (паттерны проектирования, часть 1)
enum class CheeseType : int
{
	Chedder = 1,
	Camembert = 2,
	Roquefor = 3,

	Undefined = 0
};

Cheese* CreateCheese(CheeseType type)
{
	Cheese* newCheese = nullptr;
	if (type == CheeseType::Chedder)
	{
		newCheese = new Chedder(250, 200, "Чеддр", 0);
	}
	else if (type == CheeseType::Camembert)
	{
		newCheese = new Camembert(150, 500, "Камамбер");
	}
	else if (type == CheeseType::Roquefor)
	{
		newCheese = new Roquefort(300, 300, "Рокфор", 0);
	}
	return newCheese;
}
void Create(Iterator<Cheese*>* it)
{
	for (it->First(); !it->IsDone(); it->Next())
	{
		Cheese* currentCheese = it->GetCurrent();
		cout << "Мы создали ";
		currentCheese->Eat();
	}
}

/////////////////////////////////////Лабораторная работа № 4 (паттерны проектирования, часть 2)/////////////////////////////////////
class CheeseFreshnessDecorator : public IteratorDecor<class Cheese*>
{
private:
	CheeseFreshness TargetFresh;
public:
	CheeseFreshnessDecorator(Iterator<Cheese*>* it, CheeseFreshness Fresh)
		: IteratorDecor<Cheese*>(it), TargetFresh(Fresh) {}
	void First()
	{
		It->First();
		while (!It->IsDone() && It->GetCurrent()->GetFreshness() != TargetFresh)
		{
			It->Next();
		}
	}

	void Next()
	{
		do
		{
			It->Next();

		} while (!It->IsDone() && It->GetCurrent()->GetFreshness() != TargetFresh);
	}
};


class CheeseHeavyDecorator : public IteratorDecor<class Cheese*>
{
private:
	string TargetHeavy;

public:
	CheeseHeavyDecorator(Iterator<Cheese*>* it, string isHeavy)
		: IteratorDecor<Cheese*>(it), TargetHeavy(isHeavy) {}

	void First()
	{
		It->First();
		while (!It->IsDone() && It->GetCurrent()->GetHeavy() != TargetHeavy)
		{
			It->Next();
		}
	}

	void Next()
	{
		do
		{
			It->Next();

		} while (!It->IsDone() && It->GetCurrent()->GetHeavy() != TargetHeavy);
	}
};

class CheeseMoldDecorator : public IteratorDecor<class Cheese*>
{
private:
	string TargetMold;

public:
	CheeseMoldDecorator(Iterator<Cheese*>* it, string isMold)
		: IteratorDecor<Cheese*>(it), TargetMold(isMold) {}

	void First()
	{
		It->First();
		while (!It->IsDone() && It->GetCurrent()->GetMold() != TargetMold)
		{
			It->Next();
		}
	}

	void Next()
	{
		do
		{
			It->Next();

		} while (!It->IsDone() && It->GetCurrent()->GetMold() != TargetMold);
	}
};



int main()
{
	setlocale(LC_ALL, "rus");
	/*Cheese a; ЧАСТЬ 1
	Chedder b(250, 200, "Чеддр", 0);
	cout << "Вес: " << b.GetWeight() << "\t" << "Цена: " << b.GetPrice() << "\t" << "Название: " << b.GetHardness() << "\t\t" << "Плесень: " << b.GetMold() << endl;
	cout << "\"Меняем названиние\" используем SetHardness в классе \"наследник\"" << endl;
	b.SetHardness("НеЧеддр");
	cout << "Вес: " << b.GetWeight() << "\t" << "Цена: " << b.GetPrice() << "\t" << "Название: " << b.GetHardness() << "\t" << "Плесень: " << b.GetMold() << endl << endl;
	Camembert c(150, 500, "Камамбер");
	cout << "Вес: " << c.GetWeight() << "\t" << "Цена: " << c.GetPrice() << "\t" << "Название: " << c.GetHardness() << "\t" << "Плесень: " << c.GetMold() << endl;
	cout << "используем функцию \"Eat\" в классе \"наследник\"" << endl;
	c.Eat();
	cout << endl << "Демонстрация полиморфизма: Cheese* newCheese1 = new Camembert(150, 500, \"Камамбер\")" << endl;
	Cheese* newCheese1 = new Camembert(150, 500, "Камамбер");
	cout << "Вес: " << newCheese1->GetWeight() << "\t" << "Цена: " << newCheese1->GetPrice() << "\t" << "Название: " << newCheese1->GetHardness() << "\t" << "Плесень: " << newCheese1->GetMold() << endl;
	cout << endl << endl;
	Roquefort d(300, 300, "Рокфор", 0);
	cout << "Вес: " << d.GetWeight() << "\t" << "Цена: " << d.GetPrice() << "\t" << "Название: " << d.GetHardness() << "\t" << "Плесень: " << d.GetMold() << endl;
	cout << "\"Меняем наличия плесени\" используем SetMold в классе \"наследник\"" << endl;
	d.SetMold(true);
	cout << "Вес: " << d.GetWeight() << "\t" << "Цена: " << d.GetPrice() << "\t" << "Название: " << d.GetHardness() << "\t" << "Плесень: " << d.GetMold() << endl << endl;
	cout << "Демонстрация полиморфизма: Cheese& newCheese2 = d" << endl;
	Cheese& newCheese2 = d;
	cout << "Вес: " << newCheese2.GetWeight() << "\t" << "Цена: " << newCheese2.GetPrice() << "\t" << "Название: " << newCheese2.GetHardness() << "\t" << "Плесень: " << newCheese2.GetMold() << endl << endl;
	delete newCheese1;*/


	/* cout << "Фабричный метод";   ЧАСТЬ 2
	cout << "Какой сыр создать (1 - Чеддр, 2 - Камамбер, 3 - Рокфор)?" << endl;
	CheeseType type = CheeseType::Undefined;
	int time;
	cin >> time;
	type = static_cast<CheeseType>(time);
	Cheese* newCheese = CreateCheese(type);
	cout << "Мы создали " << newCheese->GetHardness() << endl << endl;
	delete newCheese;*/

	cout << "контейнер на статических массивов" << endl;
	ArrayClass<Cheese*> CheeseArray;
	for (size_t i = 0; i < 15; i++)
	{
		int NumCheese = rand() % 3 + 1;
		CheeseType Cheese_type = static_cast<CheeseType>(NumCheese);

		Cheese* newCheese = CreateCheese(Cheese_type);
		CheeseArray.Add(newCheese);
	}
	cout << "Вывод через итератор" << endl;
	Create(CheeseArray.GetIterator());

	cout << endl << endl << "контейнер на Vector" << endl;
	VectorClass<Cheese*> CheeseVector;
	for (size_t i = 0; i < 15; i++)
	{
		int NumCheese = rand() % 3 + 1;
		CheeseType Cheese_type = static_cast<CheeseType>(NumCheese);

		Cheese* newCheese = CreateCheese(Cheese_type);
		CheeseVector.PishBack(newCheese);
	}
	cout << "Вывод через итератор" << endl;
	Create(CheeseVector.GetIterator());

	cout << endl << endl;
	cout << endl << "Вывести сыр по свежести" << endl;
	Iterator<Cheese*>* It = new CheeseFreshnessDecorator(CheeseArray.GetIterator(), CheeseFreshness::normal);
	Create(It);
	delete It;

	cout << endl << "Вывести сыр с преленью" << endl;
	Iterator<Cheese*>* It2 = new CheeseMoldDecorator(CheeseArray.GetIterator(), "Сыр с плесенью");
	Create(It2);
	delete It2;


	cout << endl << "Вывести сыр по тяжести" << endl;
	Iterator<Cheese*>* It3 = new CheeseHeavyDecorator(CheeseArray.GetIterator(), "я тяжелый СЫР!!!");
	Create(It3);
	delete It3;


	list<Cheese*> cheeseVector;
	for (size_t i = 0; i < 15; i++)
	{
		int NumCheese = rand() % 3 + 1;
		CheeseType typeCheese = static_cast<CheeseType>(NumCheese);
		Cheese* newCheese = CreateCheese(typeCheese);
		cheeseVector.push_back(newCheese);
	}
	cout << endl << "Демонстация Адаптера" << endl;
	Iterator<Cheese*>* adaptedIt = new IteratorAdapter<std::list<Cheese*>, Cheese*>(&cheeseVector);
	Iterator<Cheese*>* adaptedFreshnessHeavyIt = new CheeseHeavyDecorator(new CheeseFreshnessDecorator(adaptedIt, CheeseFreshness::normal), "я тяжелый СЫР!!!");
	Create(adaptedFreshnessHeavyIt);
	delete adaptedFreshnessHeavyIt;
	return 0;
}
