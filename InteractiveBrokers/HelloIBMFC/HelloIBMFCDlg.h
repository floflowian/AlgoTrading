
// HelloIBMFCDlg.h : header file
//

#pragma once
#include "EWrapper.h"
#include "TagValue.h"
#include "pairStatArb.h"

#define NOT_AN_FA_ACCOUNT_ERROR 321
class EClient;
// CHelloIBMFCDlg dialog
class CHelloIBMFCDlg : public CDialogEx , public EWrapper
{
// Construction
public:
	CHelloIBMFCDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_HELLOIBMFC_DIALOG };
	CListBox m_listbox;
	CListBox m_errorbox;
	CListBox m_orderbox;
	CStatic m_title;
	CStatic m_labelMeanSpread;
	CStatic m_labelStdDevSpread;
	CStatic m_labelHedgeRatio;
	CStatic m_labelLongEntry;
	CStatic m_labelShortEntry;
	CStatic m_labelExit;

	int N = 5;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	EClient *m_pClient;
	bool        m_financialAdvisor;
	CString     m_managedAccounts;
	bool faError;

	pairStatArb* algo;
	int algoLaunched;
	int initMaxOrderId;

private:
	TagValueListSPtr m_mktDataOptions;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	void tickSize(TickerId ddeId, TickType field, int size);
	void tickOptionComputation(TickerId ddeId, TickType field, double impliedVol,
		double delta, double optPrice, double pvDividend,
		double gamma, double vega, double theta, double undPrice);
	void tickGeneric(TickerId tickerId, TickType tickType, double value);
	void tickString(TickerId tickerId, TickType tickType, const CString& value);
	void tickEFP(TickerId tickerId, TickType tickType, double basisPoints,
		const CString& formattedBasisPoints, double totalDividends, int holdDays,
		const CString& futureExpiry, double dividendImpact, double dividendsToExpiry);
	void orderStatus(OrderId orderId, const CString &status, int filled, int remaining,
		double avgFillPrice, int permId, int parentId, double lastFillPrice,
		int clientId, const CString& whyHeld);
	void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
	void openOrderEnd();
	void winError(const CString &str, int lastError);
	void connectionClosed();
	void updateAccountValue(const CString &key, const CString &val,
		const CString &currency, const CString &accountName);
	virtual void updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const CString &accountName);
	void updateAccountTime(const CString &timeStamp);
	void accountDownloadEnd(const CString &accountName);
	void nextValidId(OrderId orderId);
	void contractDetails(int reqId, const ContractDetails& contractDetails);
	void bondContractDetails(int reqId, const ContractDetails& contractDetails);
	void contractDetailsEnd(int reqId);
	void execDetails(int reqId, const Contract& contract, const Execution& execution);
	void execDetailsEnd(int reqId);
	void error(const int id, const int errorCode, const CString errorString);
	void error(const CString errorString);
	void updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size);
	void updateMktDepthL2(TickerId id, int position, CString marketMaker, int operation,
		int side, double price, int size);
	void updateNewsBulletin(int msgId, int msgType, const CString& newsMessage, const CString& originExch);
	void managedAccounts(const CString& accountsList);
	void receiveFA(faDataType pFaDataType, const CString& cxml);
	void historicalData(TickerId reqId, const CString& date, double open, double high, double low,
		double close, int volume, int barCount, double WAP, int hasGaps);
	void scannerParameters(const CString &xml);
	void scannerData(int reqId, int rank, const ContractDetails &contractDetails, const CString &distance,
		const CString &benchmark, const CString &projection, const CString &legsStr);
	void scannerDataEnd(int reqId);
	void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count);
	void currentTime(long time);
	void fundamentalData(TickerId reqId, const CString& data);
	void deltaNeutralValidation(int reqId, const UnderComp& underComp);
	void tickSnapshotEnd(int reqId);
	void marketDataType(TickerId reqId, int marketDataType);
	void commissionReport(const CommissionReport& commissionReport);
	void position(const CString& account, const Contract& contract, int position, double avgCost);
	void positionEnd();
	void accountSummary(int reqId, const CString& account, const CString& tag, const CString& value, const CString& curency);
	void accountSummaryEnd(int reqId);
	void verifyMessageAPI(const IBString& apiData);
	void verifyCompleted(bool isSuccessful, const IBString& errorText);
	void displayGroupList(int reqId, const IBString& groups);
	void displayGroupUpdated(int reqId, const IBString& contractInfo);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
};
