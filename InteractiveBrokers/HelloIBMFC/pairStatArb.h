#include <string>
#include <vector>
#include "Order.h"
#include "Contract.h"
#include "EClientSocketBase.h"

enum OrderSide{
	LONGPOS,
	SHORTPOS,
	CLOSEPOS,
	STARTPOS
};
class pairStatArb{
private:
	std::string m_symbol1;
	std::string m_symbol2;
	double m_price1;
	double m_price2;
	Contract m_contract1;
	Contract m_contract2;
	Order m_order1;
	Order m_order2;
	int m_maxOrderId;
	double m_meanSpread;
	double m_stdDevSpread;
	double m_hedgeRatio;
	double m_entryLong;
	double m_entryShort;
	double m_exit;
	std::vector<Order> m_orders;
	std::vector<OrderSide> m_orderSides ;

	TagValueListSPtr m_mktDataOptions;
public:
	pairStatArb();
	pairStatArb(EClient* client, int maxOrderId,TagValueListSPtr mktDataOptions, std::string symbol1, std::string symbol2, double hedgeRatio,double meanSpread, double stdDevSpread, double entryLong, double entryShort, double exit);
	~pairStatArb();

	//Getters
	std::string getSymbol1();
	std::string getSymbol2();
	double getPrice1();
	double getPrice2();
	double getMeanSpread();
	double getStdDevSpread();
	double getHedgeRatio();
	double getEntryLong();
	double getEntryShort();
	double getExit();
	int getMaxOrderId();

	//Setters
	void setSymbol1(std::string symbol);
	void setSymbol2(std::string symbol);
	void setPrice1(double price);
	void setPrice2(double price);
	void setMeanSpread(double mean);
	void setStdDevSpread(double stdDev);
	void setHedgeRatio(double ratio);
	void setMaxOrderId(int id);
	//Update
	void updatePositions(EClient* client,double price1, double price2,CListBox& m_listbox,CListBox& m_orderbox);

};