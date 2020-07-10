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


//item�Ƕ�̬���ͣ�ֱ������ʱ��֪��item����ʾ���ڴ��ж��������
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

	item = bulk;         //�������ֱ�Ӹ�ֵ����������󣬵��ÿ�����ֵ�����
	//Quote item(bulk);  //�������ֱ�ӳ�ʼ����������󣬵��ÿ������캯��
	/* bulk��ֻ��Qutoe�ĳ�Ա����ֵ��item��bulk��BulkQuote���ֱ� ���е��ˡ� ������*/
	
	//bulk = item;       //error
	
	Quote* p = &bulk;    //����ָ��ָ���������еĻ��ಿ��		
	Quote& r = bulk;     //�������ð󶨵��������еĻ��ಿ��

	printTotal(cout, item, 1);
	printTotal(cout, bulk, 19);
	printTotal(cout, bulk, 20);
	
	return 0;
}
