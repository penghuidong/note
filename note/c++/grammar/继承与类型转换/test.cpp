#include <iostream>
#include <string>

using namespace std;

class Quote
{
private:
	string bookNo;
protected:
	double price;
public:
	Quote() : price(0.0) {}

	Quote(const string& book, double salesPrice) : 
		bookNo(book), price(salesPrice){}

	string isbn() const { return bookNo;}

	virtual double netPrice(size_t n) const
	{
		return n*price;
	}
	virtual ~Quote() = default;
};

class BulkQuote : public Quote
{
private:
	size_t minQuantity;
	double discount;
public:
	BulkQuote() : minQuantity(0), discount(0){}

	BulkQuote(const string& book, double p, size_t qty, double disc)
		: Quote(book,p), minQuantity(qty), discount(disc){ }

	double netPrice(size_t n) const override
	{
		if(n>=minQuantity)
			return n*discount*price;
		else 
			return n*price;
	}
};


//item是动态类型，直到运行时才知道item所表示的内存中对象的类型
double printTotal(ostream& out, const Quote& item, size_t n)
{
	double ret = item.netPrice(n);
	out << "ISBN: " << item.isbn() << " # sold: " << n 
		<<" total due: " << ret << endl;
	return ret;
}

int main()
{
	Quote item("123456", 98.0);
	BulkQuote bulk("123456",98.0, 20, 0.9);

	item = bulk;         //基类对象直接赋值给派生类对象，调用拷贝赋值运算符
	//Quote item(bulk);  //基类对象直接初始化派生类对象，调用拷贝构造函数
	/* bulk中只有Qutoe的成员被赋值给item，bulk中BulkQuote部分被 “切掉了” ！！！*/
	
	//bulk = item;       //error
	
	Quote* p = &bulk;    //基类指针指向派生类中的基类部分		
	Quote& r = bulk;     //基类引用绑定到派生类中的基类部分

	printTotal(cout, item, 1);
	printTotal(cout, bulk, 19);
	printTotal(cout, bulk, 20);
	
	return 0;
}
