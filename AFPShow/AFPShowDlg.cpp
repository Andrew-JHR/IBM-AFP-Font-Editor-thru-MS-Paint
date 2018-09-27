// AFPShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AFPShow.h"
#include "AFPShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAFPShowDlg dialog

CAFPShowDlg::CAFPShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAFPShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAFPShowDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAFPShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAFPShowDlg)
	DDX_Control(pDX, IDC_LIST, m_LIST);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAFPShowDlg, CDialog)
	//{{AFX_MSG_MAP(CAFPShowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDABOUT, OnAbout)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_SaveBack, OnSaveBack)
	ON_BN_CLICKED(IDC_DIR, OnDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAFPShowDlg message handlers

BOOL CAFPShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

/////////////////andrewj///////////////////////////////////////

	m_EDIT1.SetWindowText("d:\\c0td00e2");
	bkpfile = "0000" ;

/////////////////andrewj///////////////////////////////////////


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAFPShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAFPShowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAFPShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAFPShowDlg::OnButton1() 
{

	void xcode(unsigned char *,int);
	CString infile = "D:\\c0td00e2";
	m_EDIT1.GetWindowText(infile);

	if ( infile == bkpfile)
		return;

	if (m_LIST.GetCount() > 0)
		m_LIST.ResetContent();		// clear all existing entries if any
	

	ifstream input;
    unsigned char ch[4];
	union                                      // input font file maps
	{
		unsigned char buffer[20000];
		struct
		{
			char        structure[3];
			unsigned char rec_seq[3];
			union
			{
				FNIentry FNI[Total_Font_Number];
				unsigned char FNG[12298];             // Font patterns record
			};
		};
		
	};
	
	unsigned short int  RecLen;

   
	input.open(infile,ios::binary | ios::nocreate);
	if (!input)
	{
		AfxMessageBox(" Open Input File Error ! ") ;
		return;
	}

	for ( ; ; )
	{
		input.read(ch,3);
		if ( ch[0] != 'Z' )
		{
			AfxMessageBox(" Invalid file format ! ") ;
			return;
		}

		RecLen = ch[1] * 0x100 + ch[2] ;

		input.read(buffer,RecLen-2);

		if (strncmp(structure,(const char *)Font_Index,sizeof(structure)) == 0)
		{
			
			FNIentry * FNIP = FNI ;
			
			for (unsigned short int i = 0 ; i < (RecLen-8)/sizeof(FNIentry) ; i++, FNIP++ )
			{
				if (0 == (FNIP->FNI_size[0] * 0x100 + FNIP->FNI_size[1])) 
					continue ;
				
				unsigned char tempname[10];
				strncpy((char *)tempname,FNIP->FNI_name,8);
				xcode(tempname,sizeof(tempname));
				tempname[8] = '\0'; // prevent the extra chars from showing

				CString s = tempname ;
						
				m_LIST.AddString(s);

			}
			
			break; // no need to process the rest records of the file

		} // end of if FNI
	}  // end of the for ( ; ; ) loop on the entire file records
	
	input.close();
}


void xcode(unsigned char* bufptr, int len)
{
	for (int i=0 ; i < len ; i++)
	{
		*bufptr = b2a[(*bufptr)];
		bufptr++ ;
	}
	*bufptr = '\0';
}

void CAFPShowDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CAFPShowDlg::OnDblclkList() 
{
	CString fontname ="IK0____0";
	CString infile = "D:\\c0td00e2";
	char outfile[100] = "x.bmp";

	m_EDIT1.GetWindowText(infile);  // get the font file name

	int nSelect = m_LIST.GetCurSel();
	if( nSelect != LB_ERR )
        m_LIST.GetText(nSelect,fontname);   // get the font name
        
	ifstream input;
	ofstream output;
    unsigned char ch[4];
	unsigned char work[9];
	union                                      // input font file maps
	{
		unsigned char buffer[20000];
		struct
		{
			char        structure[3];
			unsigned char rec_seq[3];
			union
			{
				struct
				{
					unsigned char BFN_name[10];
				};
				struct
				{
					unsigned char FRMRK[80];
				};
				struct
				{
					char FNC_header[6];
					unsigned char FNC_xunit[2];
					unsigned char FNC_yunit[2];
				};
				struct      //Font Descriptor
				{
					char FND_facetype[32];
					unsigned char FND_weight[1];
					unsigned char FND_width[1];
					unsigned char FND_maxvsz[2];
					unsigned char FND_norvsz[2];
					unsigned char FND_minvsz[2];
					unsigned char FND_maxhsz[2];
					unsigned char FND_norhsz[2];
					unsigned char FND_minhsz[2];
				};
				FNMentry FNM[Total_Font_Number]; 
				struct    //Font Orientation
				{
					unsigned char FNO_sp[4];
					unsigned char FNO_MaxBOset[2];
					unsigned char FNO_MaxCharInc[2];
					unsigned char FNO_SpCharInc[2];
					unsigned char FNO_MaxBExt[2];
				};
				FNIentry FNI[Total_Font_Number];
				unsigned char FNG[12298];             // Font patterns record
			};
		};
		
	};
	
	unsigned short int  RecLen;
	int FontBegin, FontEnd, ReadSize=0 ;
	bool FNIonce = FALSE ;
	bool Found   = FALSE ;

	unsigned char FntPttrn[500];        //contain all the pattern bytes for the font to print
	unsigned char * FNGP;               // pointer to input pattern
	unsigned char * FntP;               // pointer to pattern bytes



    //FONT FNT[Total_Font_Number];      // keep each font's 
	//vector<char> buffer(12304);
	//vector<char>::iterator pt;

    
	input.open(infile,ios::binary | ios::nocreate);
	if (!input)
	{
		AfxMessageBox(" Open Input File Error ! ") ;
		return;
	}

	FileReadBytes = 0 ;  // reset the file read byte count

	for ( ; ; )
	{
		input.read(ch,3);
		if ( ch[0] != 'Z' )
		{
			AfxMessageBox(" Invalid file format ! ") ;
			return;
		}

		RecLen = ch[1] * 0x100 + ch[2] ;

		FileReadBytes ++ ;			// count the 'Z'
		FileReadBytes += RecLen ;	// count the record length

		input.read(buffer,RecLen-2);

		if (strncmp(structure,(const char *)Begin_Font,sizeof(structure)) == 0)
		{
//			xcode(BFN_name,sizeof(BFN_name));
		} 

		if (strncmp(structure,(const char *)Font_Remarks,3) == 0)
		{
//			xcode(FRMRK,sizeof(FRMRK));
//			cout << FRMRK ;
		} 
 
		if (strncmp(structure,(const char *)Font_Control,sizeof(structure)) == 0)
		{
//			unsigned short int pixel = FNC_xunit[0] * 0x100 + FNC_xunit[1] ;
//			cout << "X Pixels : " << pixel ;
//			pixel = FNC_yunit[0] * 0x100 + FNC_yunit[1] ;
//			cout << " , Y Pixels : " << pixel << endl;
		}
		
		if (strncmp(structure,(const char *)Font_Descriptor,sizeof(structure)) == 0)
		{
//		    unsigned short int maxvsize = FND_maxvsz[0] * 0x100 + FND_maxvsz[1]; 			 
//		    cout << "Maximum Vertical Font Size : " << maxvsize << endl;
//			unsigned short int norvsize = FND_norvsz[0] * 0x100 + FND_norvsz[1]; 			 
//		    cout << "Normal Vertical Font Size : " << norvsize << endl;
//			unsigned short int minvsize = FND_minvsz[0] * 0x100 + FND_minvsz[1]; 			 
//		    cout << "Minimum Vertical Font Size : " << minvsize << endl;
//			unsigned short int maxhsize = FND_maxhsz[0] * 0x100 + FND_maxhsz[1]; 			 
//		    cout << "Maximum Horizontal Font Size : " << maxhsize << endl;
//			unsigned short int norhsize = FND_norhsz[0] * 0x100 + FND_norhsz[1]; 			 
//		    cout << "Normal Horizontal Font Size : " << norhsize << endl;
//			unsigned short int minhsize = FND_minhsz[0] * 0x100 + FND_minhsz[1]; 			 
//		    cout << "Minimum Horizonatal Font Size : " << minhsize << endl;
		}

		if (strncmp(structure,(const char *)Font_Patterns_Map,sizeof(structure)) == 0)
		{
//			FNMentry * FNMP = FNM ;
//			
//			for (int i = 0 ; i < Total_Font_Number ; i++ )
//			{
//				for (int j = 0 ; j < 4 ; j++) 
//				{
//					FNT[i].offset[j] = FNMP->FNMoffset[j] ; 
//				}
//	 		    FNMP ++ ; 
//			}
		}


		if (strncmp(structure,(const char *)Font_Orientation,sizeof(structure)) == 0)
		{
		 	FontExt = FNO_MaxBExt[0] * 0x100 + FNO_MaxBExt[1];
		}


		if (strncmp(structure,(const char *)Font_Index,sizeof(structure)) == 0)
		{ 
			if ( FNIonce == TRUE )
				continue ;

			FNIentry * FNIP = FNI ;
			
			for (int i = 0 ; i < Total_Font_Number ; i++ )
			{
				unsigned char tempname[10];
				strncpy((char *)tempname,FNIP->FNI_name,8);
				xcode(tempname,sizeof(tempname));

                if (strncmp((const char *)tempname,fontname,8) == 0)
				{
					FontSize = FNIP->FNI_size[0] * 0x100 + FNIP->FNI_size[1] ;
					FontBegin = (FNIP->FNI_indx[0] * 0x100 + FNIP->FNI_indx[1]) * FontSize
						           * FontExt / 8 ;
					FontEnd = FontBegin + FontSize * FontExt / 8 ;
					Found = TRUE ;
					break;
				}

				FNIP ++ ; 
			}

			if ( Found != TRUE)
			{
				AfxMessageBox(" Character Not Found ! ");
				return ;
			}
			
			FNIonce = TRUE ;   // only need to process one Font_Index record, skip the rest


		}

		if (strncmp(structure,(const char *)Font_Patterns,sizeof(structure)) == 0)
		{
			RecLen   -= 8;                    // deduct the len/control field's length
			ReadSize += RecLen;               // accumulated length read from Font_Patterns' records
			
			if ( ReadSize < FontBegin )
			{
				continue;                     // not in this pattern record, skip it
			}

			FileOffset = FileReadBytes + FontBegin - ReadSize ; // get the absolute offset of the file
			Bytes_1	   = FontEnd - FontBegin ;	//default is to treat that all bits for a char are all within a record
			Bytes_2    = 0 ;                    //default is to treat that all bits for a char are all within arecord
			
			if (FontEnd > ReadSize)			// if over 2 records, go on reading the next rec
			{
				input.read(work,9);			// ommit the first 9 control bytes on the next rec      
				input.read(buffer+RecLen,FontEnd-ReadSize); // read only the wanted bytes
				Bytes_1 = ReadSize - FontBegin ; // for a char having bits over 2 records
				Bytes_2 = FontEnd  - ReadSize  ; // for a char having bits over 2 rerords
			}


			FNGP = FNG + FontBegin - ReadSize + RecLen ;
			FntP = FntPttrn;  
			for (int i=0 ; i < (FontEnd - FontBegin) ; i++, FNGP++, FntP++)
				*FntP = *FNGP;
			break ;
		
		}

	
		if (strncmp(structure,(const char *)End_Font,sizeof(structure)) == 0)
			break;
			
	}		// end of the input record reading loop 
	


	output.open(outfile,ios::binary);
	if (!output)
	{
		AfxMessageBox(" Please End the last MSPAINT Window first !") ;
		return;
	}  

	BMPhdr * BMPP = new BMPhdr[1];
	BMPP->bm = 0x4d42;   // 'BM' 
	BMPP->filesize = sizeof(BMPhdr) + FontSize * FontExt * 4 ;
	BMPP->color = BMPP->impcolor = BMPP->comprs = BMPP->rsvr =0; 
	BMPP->bmpofst = sizeof(BMPhdr); 
	BMPP->bmphdsz = 0x28;      //Windows 95, NT
	BMPP->height = FontExt;
	BMPP->width = FontSize;
	BMPP->planes = 1;
	BMPP->bitpix = 32;
	BMPP->bmpsize = FontSize * FontExt * 4 ;
	BMPP->hres = BMPP->vres = 0xb6d;
	BMPP->hres = BMPP->vres = 0;

	output.write((const char *)BMPP, sizeof(BMPhdr));

	delete[] BMPP;  

	int i,j,k;
	const unsigned char lowvalue[4] = {0x00,0x00,0x00,0x00};
	const unsigned char highvalue[4] = {0xff,0xff,0xff,0xff};

	
	FntP = FntPttrn + (FontExt-1)*FontSize/8 ;

	for (i = 0 ; i < FontExt ; i++)
	{
		unsigned char * FntQ = FntP;
		for (j = 0 ; j < FontSize/8 ; j++)
		{
			for (k = 0 ; k < 8 ; k++)
			{
				if ( *FntQ & (0x80 >> k))
					output.write(lowvalue,4);
				else
					output.write(highvalue,4);
			}
			FntQ ++ ;
		}
		FntP -= FontSize/8;
	} 
	
    
	output.close() ;
	input.close();

	spawnlp(P_NOWAIT,"Mspaint.exe","Mspaint.exe",outfile,NULL);

}

void CAFPShowDlg::OnSaveBack() 
{

	int nChoice = AfxMessageBox(" Do You Really Want to Save Back ? ",MB_YESNOCANCEL | MB_ICONQUESTION) ;  

	if (nChoice != IDYES)
		return;

	CString AFPfile;
	m_EDIT1.GetWindowText(AFPfile);  // get the font file name
	CFile cBMP("x.bmp",CFile::modeRead);
	BMPhdr * BMPQ = new BMPhdr;
	cBMP.Read(BMPQ,sizeof(BMPhdr));

	if (BMPQ->height != (unsigned int)FontExt)
	{
		AfxMessageBox("BMP's Height Is Not Matched !");
		delete[] BMPQ;
		return ;
	}

	if (BMPQ->width != (unsigned int)FontSize)
	{
		AfxMessageBox("BMP's Width Is Not Matched !");
		delete[] BMPQ;
		return ;
	}

	int bits = BMPQ->bitpix;
	delete[] BMPQ;

	unsigned char * ibfrptr = new unsigned char[FontSize*bits/8];
	unsigned char * obfrptr = new unsigned char[FontSize*FontExt/8];

	unsigned char * q = obfrptr;

	for (int j=0 ; j < FontExt ; j++)
	{
		cBMP.Read(ibfrptr,(FontSize * bits/8));

		unsigned char * p = ibfrptr;

		for (int i=0 ; i < FontSize/8 ; i++, q++)
		{
			*q = 0x00;
			for (int k=0 ; k < 8 ; k++, p += bits/8)
			{
				if ( *p == 0x00 )
					*q = *q | (0x80 >> k) ;
			}
		} 
	} // end of for looping Font's Height's times

	cBMP.Close();

	unsigned char * rsltptr = new unsigned char[FontSize*FontExt/8];

	q = obfrptr + (FontExt-1)*FontSize/8 ;
	unsigned char * r = rsltptr;
	for (int i = 0 ; i < FontExt ; i++, q -= FontSize/8)
	{
		unsigned char * p = q ;
		for ( j = 0 ; j < FontSize/8 ; j++, r++, p++ )
			*r = *p ;
	}

	delete [] ibfrptr;
	delete [] obfrptr;

	CFile cAFP(AFPfile,CFile::modeReadWrite);
	
	cAFP.Seek(FileOffset,CFile::begin);
	cAFP.Write(rsltptr,Bytes_1);
	if (Bytes_2 != 0)
	{
		cAFP.Seek(9,CFile::current);
		cAFP.Write(rsltptr+Bytes_1,Bytes_2);
	}
	cAFP.Close();

	delete [] rsltptr;

	return ;
}

void CAFPShowDlg::OnDir() 
{
	CFileDialog FileDlg(TRUE);
	if (FileDlg.DoModal() == IDOK)
		m_EDIT1.SetWindowText(FileDlg.GetPathName());
}
