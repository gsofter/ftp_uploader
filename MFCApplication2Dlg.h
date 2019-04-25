
// MFCApplication2Dlg.h : header file
//

#pragma once

#include "CkFtp2.h"
#include "CkFtp2Progress.h"

using namespace std;

class ftpProgress : public CkFtp2Progress {

public:
	ftpProgress() { }
	virtual ~ftpProgress() { }

	void PercentDone(int percentDone, bool *abort) {
		//AfxMessageBox(CString("File Upload Completed!"));
	}

	void ProgressInfo(const char *name, const char *value) {
		
	}

};


// CMFCApplication2Dlg dialog
class CMFCApplication2Dlg : public CDialogEx
{



// Construction
public:
	static void setProgressStatus();
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	CkString strOut;
	CkFtp2 ftp;
	ftpProgress ftp_progress;

	BOOL isConnect = false;
	BOOL isChooseFile = false;
	BOOL isUploading = false;

	BOOL isRegularStarted = false;
public:
	void StartUpload();
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_filePath;
	CEdit m_serverPath;
	afx_msg void OnBnClickedButton2();
	CProgressCtrl m_uploadProgress;
	CString m_output;
	CStatic m_sOutput;
	CEdit m_userName;
	CEdit m_password;
	afx_msg void OnBnClickedUrlD();
	afx_msg void OnBnClickedUsrnamed();
	afx_msg void OnBnClickedPassd();
	afx_msg void OnClickedIsRegular();
	BOOL is_regular_upload;
	CEdit m_editTimer;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedStartRegular();
	CButton m_btnStartRegular;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int uploadDuration;
	int remainTime;
	CStatic m_remainTime;
	CStatic m_connectionStatus;
	afx_msg void OnBnClickedDestSet();
	CEdit m_destFolder;
};
