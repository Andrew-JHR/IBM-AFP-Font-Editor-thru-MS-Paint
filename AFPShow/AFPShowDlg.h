// AFPShowDlg.h : header file
//

#include "stdafx.h"
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <process.h>
//#include <stack>
//#include <vector>
//using namespace std ;

#define Total_Font_Number  190


const unsigned char b2a[256] = {                    //EBCDIC to ASCII 
//		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//00 - 07
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,	//00 - 07
		0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,	//08 - 0f
		0x10,0x11,0x12,0x13,0x14,0x0A,0x16,0x17,	//10 - 17
		0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,	//18 - 1f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//20 - 27
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//28 - 2f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//30 - 37
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//38 - 3f
		0x20,0x5B,0x5C,0x5D,0x5E,0x60,0x7B,0x7D,	//40 - 47
		0x7E,0x20,0x20,0x2E,0x3C,0x28,0x2B,0x7C,	//48 - 48
		0x26,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//50 - 57
		0x20,0x20,0x21,0x24,0x2A,0x29,0x3B,0x20,	//58 - 5f
		0x2D,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,	//60 - 67
		0x20,0x20,0x20,0x2C,0x25,0x5F,0x3E,0x3F,	//68 - 6f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//70 - 77
		0x20,0x20,0x3A,0x23,0x40,0x27,0x3D,0x22,	//78 - 7f
		0x20,0x61,0x62,0x63,0x64,0x65,0x66,0x67,	//80 - 87
		0x68,0x69,0x20,0x20,0x20,0x20,0x20,0x20,	//88 - 8f
		0x20,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,	//90 - 97
		0x71,0x72,0x20,0x20,0x20,0x20,0x20,0x20,	//98 - 9f
		0x20,0x20,0x73,0x74,0x75,0x76,0x77,0x78,	//a0 - a7
		0x79,0x7A,0x20,0x20,0x20,0x20,0x20,0x20,	//a8 - af
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//b0 - b7
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//b8 - bf
		0x20,0x41,0x42,0x43,0x44,0x45,0x46,0x47,	//c0 - c7
		0x48,0x49,0x20,0x20,0x20,0x20,0x20,0x20,	//c8 - cf
		0x20,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,	//d0 - d7  
		0x51,0x52,0x20,0x20,0x20,0x20,0x20,0x20,	//d8 - df
		0x20,0x20,0x53,0x54,0x55,0x56,0x57,0x58,	//e0 - e7
		0x59,0x5A,0x20,0x20,0x20,0x20,0x20,0x20,	//e8 - ef
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,	//f0 - f7
		0x38,0x39,0x20,0x20,0x20,0x20,0x20,0x20 } ;	//f8 - ff

const unsigned char Begin_Font[3]        = {0xd3,0xa8,0x89};
const unsigned char Font_Remarks[3]      = {0xd3,0xee,0xee};
const unsigned char Font_Descriptor[3]   = {0xd3,0xa6,0x89}; 
const unsigned char Font_Control[3]      = {0xd3,0xa7,0x89}; 
const unsigned char Font_Patterns_Map[3] = {0xd3,0xa2,0x89}; 
const unsigned char Font_Orientation[3]  = {0xd3,0xae,0x89};
const unsigned char Font_Position[3]     = {0xd3,0xac,0x89};
const unsigned char Font_Index[3]        = {0xd3,0x8c,0x89}; 
const unsigned char Font_Patterns[3]     = {0xd3,0xee,0x89};
const unsigned char End_Font[3]          = {0xd3,0xa9,0x89};

struct  FNMentry
{
	unsigned char boxwidth[2];
	unsigned char boxheight[2];
	unsigned char FNMoffset[4];
};
/*
struct FONT 
{
	unsigned char offset[4];
};
*/

struct  FNIentry    //Font  Index
{
	char FNI_name[8];
	unsigned char FNI_size[2];
	unsigned char FNI_skip[6];
	unsigned char FNI_indx[2];
	unsigned char FNI_rest[10];
};


#pragma pack(push,1)			// Save previous alignment then set as Byte Alignment
struct BMPhdr					// BMP file's standard header
{							
	unsigned short int bm;		// CL2   identifier : 'BM' 
	unsigned int filesize;		// CL4   file size in bytes
	unsigned int rsvr;			// CL4   reserved
	unsigned int bmpofst;		// CL4   offset from beginning of file to the beginning of the bitmap data 
	unsigned int bmphdsz;		// CL4   length of the bitmap info header
	unsigned int width;			// CL4   horizontal width of bitmap in pixels 
	unsigned int height;		// CL4   vertical height of bitmap in pixels	
	unsigned short int planes;	// CL2   number of planes in this bitmap
	unsigned short int bitpix;	// CL2   24-bit or 32-bit or other color types 
	unsigned int comprs;		// CL4   compression spec.
	unsigned int bmpsize;		// CL4   bitmap size in bytes
	unsigned int hres;			// CL4   horizontal resolution in pixels per meter
	unsigned int vres;			// CL4   vertical resolution in pixels per meter
	unsigned int color;			// CL4   number of colors used
	unsigned int impcolor;		// CL4   number of important colors  
};
#pragma pack(pop)				// Restore previous alignment



/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_AFPSHOWDLG_H__9C54CEE6_9E34_11D6_88F9_0050BA798998__INCLUDED_)
#define AFX_AFPSHOWDLG_H__9C54CEE6_9E34_11D6_88F9_0050BA798998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAFPShowDlg dialog

class CAFPShowDlg : public CDialog
{
// Construction
public:
	CAFPShowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAFPShowDlg)
	enum { IDD = IDD_AFPSHOW_DIALOG };
	CListBox	m_LIST;
	CEdit	m_EDIT1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAFPShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CString  bkpfile ;		// backup file name
	int FontSize, FontExt ; // font's width and height
	unsigned int FileReadBytes ;
	unsigned int FileOffset;
	unsigned short int Bytes_1, Bytes_2 ;

	// Generated message map functions
	//{{AFX_MSG(CAFPShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnAbout();
	afx_msg void OnDblclkList();
	afx_msg void OnSaveBack();
	afx_msg void OnDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFPSHOWDLG_H__9C54CEE6_9E34_11D6_88F9_0050BA798998__INCLUDED_)
