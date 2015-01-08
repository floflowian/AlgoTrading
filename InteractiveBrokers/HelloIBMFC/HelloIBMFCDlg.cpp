
// HelloIBMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HelloIBMFC.h"
#include "HelloIBMFCDlg.h"
#include "afxdialogex.h"
#include "EClientSocket.h"
#include "Contract.h"
#include "Order.h"

#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelloIBMFCDlg dialog



CHelloIBMFCDlg::CHelloIBMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelloIBMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pClient = new EClientSocket(this);
}


BEGIN_MESSAGE_MAP(CHelloIBMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHelloIBMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHelloIBMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CHelloIBMFCDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CHelloIBMFCDlg message handlers

BOOL CHelloIBMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	int algoLaunched = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHelloIBMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHelloIBMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString getField(TickType tickType) {
	switch (tickType)
	{
	case BID_SIZE:	                    return "bidSize";
	case BID:		                    return "bidPrice";
	case ASK:		                    return "askPrice";
	case ASK_SIZE:	                    return "askSize";
	case LAST:		                    return "lastPrice";
	case LAST_SIZE:	                    return "lastSize";
	case HIGH:		                    return "high";
	case LOW:		                    return "low";
	case VOLUME:	                    return "volume";
	case CLOSE:		                    return "close";
	case BID_OPTION_COMPUTATION:		return "bidOptComp";
	case ASK_OPTION_COMPUTATION:		return "askOptComp";
	case LAST_OPTION_COMPUTATION:		return "lastOptComp";
	case MODEL_OPTION:					return "optionModel";
	case OPEN:                          return "open";
	case LOW_13_WEEK:                   return "13WeekLow";
	case HIGH_13_WEEK:                  return "13WeekHigh";
	case LOW_26_WEEK:                   return "26WeekLow";
	case HIGH_26_WEEK:                  return "26WeekHigh";
	case LOW_52_WEEK:                   return "52WeekLow";
	case HIGH_52_WEEK:                  return "52WeekHigh";
	case AVG_VOLUME:                    return "AvgVolume";
	case OPEN_INTEREST:                 return "OpenInterest";
	case OPTION_HISTORICAL_VOL:         return "OptionHistoricalVolatility";
	case OPTION_IMPLIED_VOL:            return "OptionImpliedVolatility";
	case OPTION_BID_EXCH:               return "OptionBidExchStr";
	case OPTION_ASK_EXCH:               return "OptionAskExchStr";
	case OPTION_CALL_OPEN_INTEREST:     return "OptionCallOpenInterest";
	case OPTION_PUT_OPEN_INTEREST:      return "OptionPutOpenInterest";
	case OPTION_CALL_VOLUME:            return "OptionCallVolume";
	case OPTION_PUT_VOLUME:             return "OptionPutVolume";
	case INDEX_FUTURE_PREMIUM:          return "IndexFuturePremium";
	case BID_EXCH:                      return "bidExch";
	case ASK_EXCH:                      return "askExch";
	case AUCTION_VOLUME:                return "auctionVolume";
	case AUCTION_PRICE:                 return "auctionPrice";
	case AUCTION_IMBALANCE:             return "auctionImbalance";
	case MARK_PRICE:                    return "markPrice";
	case BID_EFP_COMPUTATION:           return "bidEFP";
	case ASK_EFP_COMPUTATION:           return "askEFP";
	case LAST_EFP_COMPUTATION:          return "lastEFP";
	case OPEN_EFP_COMPUTATION:          return "openEFP";
	case HIGH_EFP_COMPUTATION:          return "highEFP";
	case LOW_EFP_COMPUTATION:           return "lowEFP";
	case CLOSE_EFP_COMPUTATION:         return "closeEFP";
	case LAST_TIMESTAMP:                return "lastTimestamp";
	case SHORTABLE:                     return "shortable";
	case FUNDAMENTAL_RATIOS:            return "fundamentals";
	case RT_VOLUME:                     return "RTVolume";
	case HALTED:                        return "halted";
	case BID_YIELD:                     return "bidYield";
	case ASK_YIELD:                     return "askYield";
	case LAST_YIELD:                    return "lastYield";
	case CUST_OPTION_COMPUTATION:       return "custOptComp";
	case TRADE_COUNT:                   return "trades";
	case TRADE_RATE:                    return "trades/min";
	case VOLUME_RATE:                   return "volume/min";
	case LAST_RTH_TRADE:                return "lastRTHTrade";
	default:                            return "unknown";
	}
}

#define NUM_FA_ERROR_CODES 6
static int faErrorCodes[NUM_FA_ERROR_CODES] =
{ 503, 504, 505, 522, 1100, NOT_AN_FA_ACCOUNT_ERROR };

void CHelloIBMFCDlg::tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute){
	/*CString str;
	str.Format("id=%i  %s=%f  canAutoExecute=%d",
		tickerId, (const char*)getField(field), price, canAutoExecute);
	int i = m_listbox.InsertString(-1, str);
*/
	

	if (algoLaunched == 1 && field==LAST && price>0){
		if (tickerId == 0) {
			algo->setPrice1(price);
		}
		else if (tickerId == 1) {
			algo->setPrice2(price);
		}
		if (algo->getPrice1()>0 && algo->getPrice2()>0){
			CString title;
			title.Format("Statistical Arbitrage %s vs %s", algo->getSymbol1().c_str(), algo->getSymbol2().c_str());
			m_title.SetWindowText(title);
			CString labelMeanSpread;
			labelMeanSpread.Format("Mean Spread: %f", algo->getMeanSpread());
			m_labelMeanSpread.SetWindowText(labelMeanSpread);
			CString labelStdDevSpread;
			labelStdDevSpread.Format("Std Dev Spread: %f", algo->getStdDevSpread());
			m_labelStdDevSpread.SetWindowText(labelStdDevSpread);
			CString labelHedgeRatio;
			labelHedgeRatio.Format("Hedge Ratio: %f", algo->getHedgeRatio());
			m_labelHedgeRatio.SetWindowText(labelHedgeRatio);
			CString labelLongEntry;
			labelLongEntry.Format("Long Entry: %f", algo->getEntryLong());
			m_labelLongEntry.SetWindowText(labelLongEntry);
			CString labelShortEntry;
			labelShortEntry.Format("Short Entry: %f", algo->getEntryShort());
			m_labelShortEntry.SetWindowText(labelShortEntry);
			CString labelExit;
			labelExit.Format("Exit: %f", algo->getExit());
			m_labelExit.SetWindowText(labelExit);



			double spread = algo->getPrice1() - algo->getHedgeRatio()*algo->getPrice2();
			double zScore = (spread - algo->getMeanSpread()) / algo->getStdDevSpread();
			CString marketPrint;
			marketPrint.Format("Spread@%f  zScore@%f %s@%f %s@%f", spread, zScore, algo->getSymbol1().c_str(), algo->getPrice1(), algo->getSymbol2().c_str(), algo->getPrice2());
			int i = m_listbox.InsertString(-1, marketPrint);
			int top = i - N < 0 ? 0 : i - N;
			m_listbox.SetTopIndex(top);
			algo->updatePositions(m_pClient, algo->getPrice1(), algo->getPrice2(),m_listbox,m_orderbox);
		}
	}

}
void CHelloIBMFCDlg::tickSize(TickerId tickerId, TickType field, int size){
	/*CString str;
	str.Format("id=%i  %s=%i",
		tickerId, (const char*)getField(field), size);
	int i = m_listbox.InsertString(-1,str);

	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);*/
}
void CHelloIBMFCDlg::tickOptionComputation(TickerId ddeId, TickType field, double impliedVol,
	double delta, double optPrice, double pvDividend,
	double gamma, double vega, double theta, double undPrice){}
void CHelloIBMFCDlg::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
	/*CString str;
	str.Format("id=%i  %s=%f",
		tickerId, (const char*)getField(tickType), value);
	int i = m_listbox.InsertString(-1,str);

	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);*/
}
void CHelloIBMFCDlg::tickString(TickerId tickerId, TickType tickType, const CString& value)
{
	/*CString str;
	str.Format("id=%i  %s=%s",
		tickerId, (const char*)getField(tickType), value);
	int i = m_listbox.InsertString(-1,str);

	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);*/
	
}
void CHelloIBMFCDlg::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const CString& formattedBasisPoints,
	double totalDividends, int holdDays, const CString& futureExpiry, double dividendImpact,
	double dividendsToExpiry)
{
	CString str;
	str.Format("id=%i  %s: basisPoints=%f / %s impliedFuture=%f holdDays=%i futureExpiry=%s dividendImpact=%f dividendsToExpiry=%f",
		tickerId, (const char*)getField(tickType), basisPoints, formattedBasisPoints, totalDividends, holdDays, futureExpiry, dividendImpact, dividendsToExpiry);
	int i = m_listbox.InsertString(-1,str);

	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::orderStatus(OrderId orderId, const CString &status, int filled, int remaining,
	double avgFillPrice, int permId, int parentId, double lastFillPrice,
	int clientId, const CString& whyHeld)
{
	// create string
	CString str;
	str.Format("orderId=%i status=%s  filled=%i  remaining=%i  avgFillPrice=%f",
		orderId, (const char *)status, filled, remaining, avgFillPrice);

	// add to listbox
	int i = m_orderbox.InsertString(-1,str);

	// move into view
	int top = i - N < 0 ? 0 : i - N;
	m_orderbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&){}
void CHelloIBMFCDlg::openOrderEnd(){}
void CHelloIBMFCDlg::winError(const CString &str, int lastError){}
void CHelloIBMFCDlg::connectionClosed(){}
void CHelloIBMFCDlg::updateAccountValue(const CString &key, const CString &val,
	const CString &currency, const CString &accountName){}
void CHelloIBMFCDlg::updatePortfolio(const Contract& contract, int position,
	double marketPrice, double marketValue, double averageCost,
	double unrealizedPNL, double realizedPNL, const CString &accountName){}
void CHelloIBMFCDlg::updateAccountTime(const CString &timeStamp){}
void CHelloIBMFCDlg::accountDownloadEnd(const CString &accountName){}
void CHelloIBMFCDlg::nextValidId(OrderId orderId){
	initMaxOrderId = orderId;
}
void CHelloIBMFCDlg::contractDetails(int reqId, const ContractDetails& contractDetails){}
void CHelloIBMFCDlg::bondContractDetails(int reqId, const ContractDetails& contractDetails){}
void CHelloIBMFCDlg::contractDetailsEnd(int reqId){}
void CHelloIBMFCDlg::execDetails(int reqId, const Contract& contract, const Execution& execution){}
void CHelloIBMFCDlg::execDetailsEnd(int reqId){}
void CHelloIBMFCDlg::error(const int id, const int errorCode, const CString errorString) {
	CString errorStr("Id: ");

	char buf[20];
	_itoa(id, buf, 10);
	errorStr += CString(buf);
	errorStr += " | ";
	errorStr += "Error Code: ";
	_itoa(errorCode, buf, 10);
	errorStr += CString(buf);
	errorStr += " | ";
	errorStr += "Error Msg: ";
	errorStr += errorString;
	error(errorStr);
	for (int ctr = 0; ctr < NUM_FA_ERROR_CODES; ctr++) {
		faError |= (errorCode == faErrorCodes[ctr]);
	}

}
void CHelloIBMFCDlg::error(const CString errorString)
{
	int i = m_errorbox.InsertString(-1,errorString);
	int top = i - N < 0 ? 0 : i - N;
	m_errorbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::updateMktDepth(TickerId id, int position, int operation, int side,
	double price, int size){}
void CHelloIBMFCDlg::updateMktDepthL2(TickerId id, int position, CString marketMaker, int operation,
	int side, double price, int size){}
void CHelloIBMFCDlg::updateNewsBulletin(int msgId, int msgType, const CString& newsMessage, const CString& originExch){}
void CHelloIBMFCDlg::receiveFA(faDataType pFaDataType, const CString& cxml){}
void CHelloIBMFCDlg::historicalData(TickerId reqId, const CString& date, double open, double high, double low,
	double close, int volume, int barCount, double WAP, int hasGaps)
{
	CString displayString;
	displayString.Format(
		"id=%d date=%s open=%f high=%f low=%f close=%f volume=%d barCount = %d WAP=%f hasGaps=%d",
		reqId, (const char *)date, open, high, low, close, volume, barCount, WAP, hasGaps);
	int i = m_listbox.InsertString(-1,displayString);

	// bring into view
	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::scannerParameters(const CString &xml){}
void CHelloIBMFCDlg::scannerData(int reqId, int rank, const ContractDetails &contractDetails, const CString &distance,
	const CString &benchmark, const CString &projection, const CString &legsStr){}
void CHelloIBMFCDlg::scannerDataEnd(int reqId){}
void CHelloIBMFCDlg::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	long volume, double wap, int count){}
void CHelloIBMFCDlg::currentTime(long time){}
void CHelloIBMFCDlg::fundamentalData(TickerId reqId, const CString& data){}
void CHelloIBMFCDlg::deltaNeutralValidation(int reqId, const UnderComp& underComp){}
void CHelloIBMFCDlg::tickSnapshotEnd(int reqId)
{
	CString str;
	str.Format("id=%i =============== end ===============", reqId);

	int i = m_listbox.InsertString(-1,str);

	// bring into view
	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::marketDataType(TickerId reqId, int marketDataType)
{
	CString str;
	switch (marketDataType){
	case REALTIME:
		str.Format("id=%i marketDataType=Real-Time", reqId);
		break;
	case FROZEN:
		str.Format("id=%i marketDataType=Frozen", reqId);
		break;
	default:
		str.Format("id=%i marketDataType=Unknown", reqId);
	}

	int i = m_listbox.InsertString(-1,str);

	// bring into view
	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);
}
void CHelloIBMFCDlg::commissionReport(const CommissionReport& commissionReport){}
void CHelloIBMFCDlg::position(const CString& account, const Contract& contract, int position, double avgCost){}
void CHelloIBMFCDlg::positionEnd(){}
void CHelloIBMFCDlg::accountSummary(int reqId, const CString& account, const CString& tag, const CString& value, const CString& curency){}
void CHelloIBMFCDlg::accountSummaryEnd(int reqId){}
void CHelloIBMFCDlg::verifyMessageAPI(const IBString& apiData){}
void CHelloIBMFCDlg::verifyCompleted(bool isSuccessful, const IBString& errorText){}
void CHelloIBMFCDlg::displayGroupList(int reqId, const IBString& groups){}
void CHelloIBMFCDlg::displayGroupUpdated(int reqId, const IBString& contractInfo){}

void CHelloIBMFCDlg::managedAccounts(const CString& accountsList)
{
	m_financialAdvisor = true;
	m_managedAccounts = accountsList;

	CString displayString;
	displayString.Format("Connected : The list of managed accounts are : [%s]", accountsList);
	m_listbox.InsertString(-1,displayString);
}

void CHelloIBMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClient2Dlg)
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_LIST2, m_errorbox);
	DDX_Control(pDX, IDC_LIST3, m_orderbox);
	DDX_Control(pDX, IDC_STATIC1, m_title);
	DDX_Control(pDX, IDC_STATIC2, m_labelMeanSpread);
	DDX_Control(pDX, IDC_STATIC3, m_labelStdDevSpread);
	DDX_Control(pDX, IDC_STATIC4, m_labelHedgeRatio);
	DDX_Control(pDX, IDC_STATIC5, m_labelLongEntry);
	DDX_Control(pDX, IDC_STATIC6, m_labelShortEntry);
	DDX_Control(pDX, IDC_STATIC7, m_labelExit);


	//}}AFX_DATA_MAP
}

void CHelloIBMFCDlg::OnBnClickedButton1()
{
	//Connect button
	m_pClient->eConnect("127.0.0.1", 7496, 1);
	if (m_pClient->serverVersion() > 0)	{
		CString displayString;
		displayString.Format("Connected to Tws server version %d at %s.",
			m_pClient->serverVersion(), m_pClient->TwsConnectionTime());
		int i = m_listbox.InsertString(-1,displayString);
		//m_listbox.SetTopIndex(i);
	}
}

void CHelloIBMFCDlg::OnBnClickedButton2()
{
	//Disconnect button
	m_pClient->eDisconnect();
	CString displayString;
	displayString.Format("Disconnected from Tws server");
	int i = m_listbox.InsertString(-1,displayString);
	int top = i - N < 0 ? 0 : i - N;
	m_listbox.SetTopIndex(top);

}

//void CHelloIBMFCDlg::OnBnClickedButton3()
//{
//	// Request Market Data
//	static int mktId = 0;
//	Contract myCon;
//	myCon.conId = mktId;
//	mktId++;
//	myCon.currency = "USD";
//	myCon.exchange = "SMART";
//	myCon.symbol = "AAPL";
//	myCon.secType = "STK";
//	myCon.primaryExchange = "ISLAND";
//	myCon.strike = 0;
//	myCon.includeExpired = false;
//
//	m_pClient->reqMktData(mktId, myCon,
//		"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318", false, m_mktDataOptions);
//}
//
//
//void CHelloIBMFCDlg::OnBnClickedButton4()
//{
//	// Place Order Button
//	static int orderId = 0;
//	Contract myCon;
//	myCon.conId = orderId;
//	orderId++;
//	myCon.currency = "USD";
//	myCon.exchange = "SMART";
//	myCon.symbol = "FB";
//	myCon.secType = "STK";
//	myCon.primaryExchange = "ISLAND";
//	myCon.strike = 0;
//	myCon.includeExpired = false;
//
//	Order myOrder;
//	myOrder = Order();
//	myOrder.action = "SELL";
//	myOrder.totalQuantity = 1000;
//	myOrder.orderType = "MKT";
//
//	m_pClient->placeOrder(orderId, myCon, myOrder);
//}

void CHelloIBMFCDlg::OnBnClickedButton5()
{
	//pairStatArb(EClient* client, int maxOrderId, TagValueListSPtr mktDataOptions, std::string symbol1, std::string symbol2, double hedgeRatio, double meanSpread, double stdDevSpread, double entryLong, double entryShort, double exit);
	algo = new pairStatArb(m_pClient, initMaxOrderId,m_mktDataOptions, "GS", "MS",5.7804, 1.5575, 9.5734, -1.5, 1.5, 1);
	algoLaunched = 1;

}


