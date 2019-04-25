
// MFCApplication2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"


#include <afxinet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2Dlg dialog

#define DEF_USERNAME "tspree15@thedrinkexchange.com"

#define DEF_PASSWORD "1Mindymoo5!"

#define DEF_SERVERURL "ftp.thedrinkexchange.com"




CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_output(_T(""))
	, is_regular_upload(FALSE)
	, uploadDuration(0)
	, remainTime(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_filePath);
	DDX_Control(pDX, IDC_EDIT2, m_serverPath);
	DDX_Control(pDX, IDC_PROGRESS1, m_uploadProgress);
	//DDX_Text(pDX, IDC_STATUS1, m_output);
	DDX_Control(pDX, IDC_STATUS1, m_sOutput);
	DDX_Control(pDX, IDC_EDIT3, m_userName);
	DDX_Control(pDX, IDC_EDIT4, m_password);
	DDX_Check(pDX, IDC_IS_REGULAR, is_regular_upload);
	DDX_Control(pDX, IDC_TIMER, m_editTimer);
	DDX_Control(pDX, IDC_START_REGULAR, m_btnStartRegular);
	DDX_Text(pDX, IDC_TIMER, uploadDuration);
	DDX_Text(pDX, IDC_REMAIN, remainTime);
	DDX_Control(pDX, IDC_REMAIN, m_remainTime);
	DDX_Control(pDX, IDC_CONNECT_STATUS, m_connectionStatus);
	DDX_Control(pDX, IDC_EDIT_DEST, m_destFolder);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_URL_D, &CMFCApplication2Dlg::OnBnClickedUrlD)
	ON_BN_CLICKED(IDC_USRNAMED, &CMFCApplication2Dlg::OnBnClickedUsrnamed)
	ON_BN_CLICKED(IDC_PASSD, &CMFCApplication2Dlg::OnBnClickedPassd)
	ON_BN_CLICKED(IDC_IS_REGULAR, &CMFCApplication2Dlg::OnClickedIsRegular)
	ON_BN_CLICKED(IDC_CONNECT, &CMFCApplication2Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_RESET, &CMFCApplication2Dlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_START_REGULAR, &CMFCApplication2Dlg::OnBnClickedStartRegular)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DEST_SET, &CMFCApplication2Dlg::OnBnClickedDestSet)
END_MESSAGE_MAP()


// CMFCApplication2Dlg message handlers

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedButton1()
{
	TCHAR szFilters[] = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");

	CFileDialog fileDlg(TRUE, _T("csv"), _T("*.csv"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if (fileDlg.DoModal() == IDOK)
	{
		CString sFilePath = fileDlg.GetPathName();
		
		m_filePath.SetWindowText(sFilePath);

		m_uploadProgress.SetPos(0);
		m_sOutput.SetWindowText(CString(" "));
		isChooseFile = TRUE;
		//MessageBox(sFilePath);
	}
}


void CMFCApplication2Dlg::setProgressStatus() {
	
}

void CMFCApplication2Dlg::OnBnClickedButton2() {

	if (!isConnect)
	{
		AfxMessageBox(CString("Please connect to your ftp server!"));
		return;
	}
	if (!isChooseFile)
	{
		AfxMessageBox(CString("Please choose your file!"));
		return;
	}
	
	StartUpload();
}

void CMFCApplication2Dlg::StartUpload()
{
	isUploading = TRUE;
	m_sOutput.SetWindowTextW(CString("File uploading"));
	m_uploadProgress.SetRange(0, 100);
	m_uploadProgress.SetPos(50);



	bool success = true;
	//  Change to the remote directory where the file will be uploaded.
	//success = ftp.ChangeRemoteDir("junk");
	if (success != true) {
		strOut.append(ftp.lastErrorText());
		strOut.append("\r\n");
		//SetDlgItemText(IDC_EDIT2, strOut.getUnicode());
		isUploading = FALSE;
		return;
	}


	//  Upload a file.
	char *localPath = "D:/test.xml";
	char *remoteFilename = "test.xml";


	CString sSourceFileName;
	CStringA sSourceFileNameA;
	m_filePath.GetWindowText(sSourceFileName);

	sSourceFileNameA = sSourceFileName.GetString();
	localPath = (char*)sSourceFileNameA.GetBuffer();

	CString sDestFileName = sSourceFileName.Right(sSourceFileName.GetLength() - sSourceFileName.ReverseFind('\\') - 1);
	CStringA sDestFileNameA;
	sDestFileNameA = sDestFileName.GetString();
	remoteFilename = (char*)sDestFileNameA.GetBuffer();


	ftp.PutFile(localPath, remoteFilename);

	if (success != true) {
		strOut.append(ftp.lastErrorText());
		strOut.append("\r\n");
		SetDlgItemText(IDC_EDIT2, strOut.getUnicode());
		isUploading = FALSE;
		return;
	}

//	success = ftp.Disconnect();

	strOut.append("File Uploaded!");
	m_uploadProgress.SetPos(100);
	strOut.append("\r\n");


	//SetDlgItemText(IDC_STATUS1, strOut.getUnicode());
	m_sOutput.SetWindowTextW(CString("File uploaded!"));
//	m_output = strOut.getUnicode();
	isUploading = FALSE;
}
void CMFCApplication2Dlg::OnBnClickedUrlD()
{
	// TODO: Add your control notification handler code here
	m_serverPath.SetWindowTextW(CString(DEF_SERVERURL));
	
}


void CMFCApplication2Dlg::OnBnClickedUsrnamed()
{
	// TODO: Add your control notification handler code here
	m_userName.SetWindowTextW(CString(DEF_USERNAME));
}


void CMFCApplication2Dlg::OnBnClickedPassd()
{
	// TODO: Add your control notification handler code here
	m_password.SetWindowTextW(CString(DEF_PASSWORD));
}


void CMFCApplication2Dlg::OnClickedIsRegular()
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox(CString("aaa"));
	UpdateData(TRUE);
	m_editTimer.EnableWindow(is_regular_upload);
	m_btnStartRegular.EnableWindow(is_regular_upload);
	if (is_regular_upload)
	{
		SetTimer(2, 1000, NULL);
		isRegularStarted = TRUE;
	}
	else {
		KillTimer(2);
		KillTimer(1);
	}
}


void CMFCApplication2Dlg::OnBnClickedConnect()
{
	if (isConnect)
	{
		AfxMessageBox(CString("Already Connected!"));
		return;
	}
	m_connectionStatus.SetWindowText(CString("connecting"));
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	//  Any string unlocks the component for the 1st 30-days.
	bool success = ftp.UnlockComponent("Anything for 30-day trial");
	if (success != true) {
		strOut.append(ftp.lastErrorText());
		strOut.append("\r\n");
		return;
	}


	CString strServerPath;
	CStringA strServerPathA;
	m_serverPath.GetWindowText(strServerPath);
	strServerPathA = strServerPath.GetString();

	CString strUserName;
	CStringA strUserNameA;
	m_userName.GetWindowText(strUserName);
	strUserNameA = strUserName.GetString();


	CString strPassword;
	CStringA strPasswordA;
	m_password.GetWindowText(strPassword);
	strPasswordA = strPassword.GetString();


	const char *serverPath = "";
	const char *userName = "";
	const char *password = "";


	serverPath = (char*)strServerPathA.GetBuffer();
	userName = (char*)strUserNameA.GetBuffer();
	password = (char*)strPasswordA.GetBuffer();

	ftp.put_Hostname(serverPath);
	ftp.put_Username(userName);
	ftp.put_Password(password);

	ftp.put_AuthTls(true);


	ftp.put_Ssl(false);

	//  Connect and login to the FTP server.
	success = ftp.Connect();
	if (success != true) {
		strOut.append(ftp.lastErrorText());
		strOut.append("\r\n");
		//SetDlgItemText(IDC_EDIT2, strOut.getUnicode());
		AfxMessageBox(CString("Connection failed! Check your ftp server or please correct your url"));
		m_connectionStatus.SetWindowText(CString("disconnected"));
		m_uploadProgress.SetPos(0);
		return;
	}

	isConnect = true;
	//success = ftp.ChangeRemoteDir("test");
	m_connectionStatus.SetWindowText(CString("connected"));

	AfxMessageBox(CString("Connection success!"));

	m_serverPath.EnableWindow(FALSE);
	m_userName.EnableWindow(FALSE);
	m_password.EnableWindow(FALSE);
	m_destFolder.EnableWindow(TRUE);
	return;
}


void CMFCApplication2Dlg::OnBnClickedReset()
{
	// TODO: Add your control notification handler code here
	if (!isConnect)
		return;
	isConnect = FALSE;
	m_serverPath.EnableWindow(TRUE);
	m_userName.EnableWindow(TRUE);
	m_password.EnableWindow(TRUE);
	ftp.Disconnect();
	m_connectionStatus.SetWindowText(CString("disconnected!"));
}


void CMFCApplication2Dlg::OnBnClickedStartRegular()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if (!isConnect)
	{
		AfxMessageBox(CString("Connect to your server!"));
		return;
	}
	if (!isChooseFile)
	{
		AfxMessageBox(CString("Choose correct file!"));
		return;
	}

	if (!is_regular_upload)
	{
		AfxMessageBox(CString("Click the checkbox!"));
		return;
	}
	if (uploadDuration <= 5)
	{
		AfxMessageBox(CString("You must choose the duration more than 5 seconds!"));
		return;
	}
	
	StartUpload();
	KillTimer(1);
	SetTimer(1, uploadDuration * 1000, NULL); // one event every 1000 ms = 1 s
	remainTime = uploadDuration;
	
	CString str;
	str.Format(_T("%d"), remainTime);
	m_remainTime.SetWindowText(str);
	isRegularStarted = false;
}



void CMFCApplication2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	
	if (nIDEvent == 2)
	{
		if (remainTime > 0)
			remainTime--;
		else
			remainTime = uploadDuration;
		CString str;
		str.Format(_T("%d"), remainTime);
		m_remainTime.SetWindowText(str);
	}
	if (isRegularStarted)
		return;
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		StartUpload();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication2Dlg::OnBnClickedDestSet()
{
	// TODO: Add your control notification handler code here
	if (isRegularStarted || isUploading)
	{
		AfxMessageBox(CString("Please suspend the uploading!"));
		return;
	}

	if(!isConnect)
	{
		AfxMessageBox(CString("Please connect to the server!"));
		return;
	}
	if(!isChooseFile)
	{
		AfxMessageBox(CString("Please choose the file!"));
		return;
	}
	
	if (m_destFolder.IsWindowEnabled())
	{
		CString folderName;
		CStringA folderNameA;
		m_destFolder.GetWindowText(folderName);
		folderNameA = folderName.GetString();
		
		char *remoteDirLocation = (char *)folderNameA.GetBuffer();
		if(folderName.GetBuffer() != NULL && folderName.GetLength() > 0)
		{
			bool success = ftp.ChangeRemoteDir(remoteDirLocation);
			if (!success)
			{
				CString message = CString("Cannot connect to the ");
				message.Append(folderName);
				AfxMessageBox(message);
				return;
			}
			CString message("Connecting to ");
			message.Append(folderName);
			message.Append(CString("has been succeed!"));
			AfxMessageBox(message);
			m_destFolder.EnableWindow(FALSE);
		}
		else
		{
			AfxMessageBox(CString("Input the dest folder"));
			return;
		}
	}
	else
	{
		AfxMessageBox(CString("You have to reconnect to the server again."));
		//m_destFolder.EnableWindow(TRUE);
		return;
	}
	return;
}
