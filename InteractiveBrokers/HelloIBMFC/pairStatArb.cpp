#include "stdafx.h"
#include "pairStatArb.h"
#include "EClientSocket.h"
#include "Contract.h"
#include "Order.h"
#include <iostream>

pairStatArb::pairStatArb(){

}

pairStatArb::pairStatArb(EClient* client,int maxOrderId, TagValueListSPtr mktDataOptions, std::string symbol1, std::string symbol2, double hedgeRatio,double meanSpread, double stdDevSpread, double entryLong, double entryShort, double exit){
	m_symbol1 = symbol1;
	m_symbol2 = symbol2;
	m_meanSpread = meanSpread;
	m_stdDevSpread = stdDevSpread;
	m_entryShort = entryShort;
	m_entryLong = entryLong;
	m_hedgeRatio = hedgeRatio;
	m_exit = exit;
	m_maxOrderId = 0;
	m_mktDataOptions = mktDataOptions;
	m_maxOrderId = maxOrderId;
	
	
	m_contract1.currency = "USD";
	m_contract1.exchange = "SMART";
	CString s1(m_symbol1.c_str());
	m_contract1.symbol=s1;
	m_contract1.secType = "STK";
	m_contract1.primaryExchange = "ISLAND";
	m_contract1.strike = 0;
	m_contract1.includeExpired = false;
	
	m_contract2.currency = "USD";
	m_contract2.exchange = "SMART";
	CString s2(m_symbol2.c_str());
	m_contract2.symbol = s2;
	m_contract2.secType = "STK";
	m_contract2.primaryExchange = "ISLAND";
	m_contract2.strike = 0;
	m_contract2.includeExpired = false;
	
	client->reqMktData(0, m_contract1,
		"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318", false, m_mktDataOptions);

	client->reqMktData(1, m_contract2,
		"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318", false, m_mktDataOptions);

	m_order1 = Order();
	m_order1.action = "BUY";
	m_order1.totalQuantity = 100;
	m_order1.orderType = "MKT";

	m_order2 = Order();
	m_order2.action = "SELL";
	m_order2.totalQuantity = m_order1.totalQuantity*m_hedgeRatio;
	m_order2.orderType = "MKT";
	
}		   

pairStatArb::~pairStatArb(){}

std::string pairStatArb::getSymbol1(){
	return m_symbol1;
}

std::string pairStatArb::getSymbol2(){
	return m_symbol2;
}

double pairStatArb::getPrice1(){
	return m_price1;
}

double pairStatArb::getPrice2(){
	return m_price2;
}

double pairStatArb::getHedgeRatio(){
	return m_hedgeRatio;
}

double pairStatArb::getMeanSpread(){
	return m_meanSpread;
}

int pairStatArb::getMaxOrderId(){
	return m_maxOrderId;
}

double pairStatArb::getStdDevSpread(){
	return m_stdDevSpread;
}

double pairStatArb::getEntryLong(){
	return m_entryLong;
}

double pairStatArb::getEntryShort(){
	return m_entryShort;
}

double pairStatArb::getExit(){
	return m_exit;
}

void pairStatArb::setSymbol1(std::string symbol){
	m_symbol1 = symbol;
}

void pairStatArb::setSymbol2(std::string symbol){
	m_symbol2 = symbol;
}

void pairStatArb::setPrice1(double price){
	m_price1 = price;
}

void pairStatArb::setPrice2(double price){
	m_price2 = price;
}

void pairStatArb::setMeanSpread(double mean){
	m_meanSpread = mean;
}

void pairStatArb::setStdDevSpread(double std){
	m_stdDevSpread = std;
}

void pairStatArb::setHedgeRatio(double ratio){
	m_hedgeRatio = ratio;
}

void pairStatArb::setMaxOrderId(int id){
	m_maxOrderId = id;
}
void pairStatArb::updatePositions(EClient* client, double price1, double price2,CListBox &m_listbox,CListBox &m_orderbox){
	double spread = price1 - m_hedgeRatio*price2;
	double zScore = (spread - m_meanSpread) / m_stdDevSpread;
	int nbOrders = m_orderSides.size();
	CString orderPrint;
	if (fabs(zScore) < m_exit){
		if (m_orderSides.back() == OrderSide::LONGPOS){
			m_order1.action = "SELL";
			m_order2.action = "BUY";
			m_orderSides.push_back(OrderSide::CLOSEPOS);
			orderPrint.Format("Close Spread@%f zScore@%f %s@%f %s@%f", spread, zScore,m_symbol1.c_str(),price1,m_symbol2.c_str(),price2);
		}
		else if (m_orderSides.back() == OrderSide::SHORTPOS){
			m_order1.action = "BUY";
			m_order2.action = "SELL";
			m_orderSides.push_back(OrderSide::CLOSEPOS);
			orderPrint.Format("Close Spread@%f zScore@%f %s@%f %s@%f", spread, zScore, m_symbol1.c_str(), price1, m_symbol2.c_str(), price2);
		}
		
	}
	else if (zScore < m_entryLong && (m_orderSides.size() == 0 || m_orderSides.back() == OrderSide::CLOSEPOS)){
		
		m_order1.action = "BUY";
		m_order2.action = "SELL";
		orderPrint.Format("Long Spread@%f zScore@%f %s@%f %s@%f", spread, zScore, m_symbol1.c_str(), price1, m_symbol2.c_str(), price2);
		m_orderSides.push_back(OrderSide::LONGPOS);		
	}
	else if (zScore > m_entryShort && (m_orderSides.size() == 0 || m_orderSides.back() == OrderSide::CLOSEPOS)){
		
		m_order1.action = "SELL";
		m_order2.action = "BUY";
		orderPrint.Format("Short Spread@%f zScore@%f %s@%f %s@%f", spread, zScore, m_symbol1.c_str(), price1, m_symbol2.c_str(), price2);
		m_orderSides.push_back(OrderSide::SHORTPOS);
	}
	
	if (m_orderSides.size() != nbOrders){
		m_orderbox.InsertString(-1, orderPrint);
		m_order1.orderId = m_maxOrderId + 1;
		m_order2.orderId = m_maxOrderId + 2;
		m_maxOrderId = m_maxOrderId + 2;
		client->placeOrder(m_order1.orderId, m_contract1, m_order1);
		client->placeOrder(m_order2.orderId, m_contract2, m_order2);
		m_orders.push_back(m_order1);
		m_orders.push_back(m_order2);
	}

}