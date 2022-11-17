
// KursovazadDIPDoc.cpp : implementation of the CKursovazadDIPDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KursovazadDIP.h"
#endif

#include "KursovazadDIPDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKursovazadDIPDoc

IMPLEMENT_DYNCREATE(CKursovazadDIPDoc, CDocument)

BEGIN_MESSAGE_MAP(CKursovazadDIPDoc, CDocument)
END_MESSAGE_MAP()


// CKursovazadDIPDoc construction/destruction

CKursovazadDIPDoc::CKursovazadDIPDoc()
{
	// TODO: add one-time construction code here

}

CKursovazadDIPDoc::~CKursovazadDIPDoc()
{
}

BOOL CKursovazadDIPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	nrow = 0; ncolumns = 0;

	return TRUE;
}




// CKursovazadDIPDoc serialization

void CKursovazadDIPDoc::Serialize(CArchive& ar)
{
	CString line,token;
	int pos;

	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		ar.ReadString(line);
		if (line.Left(2) != "P2"){
			AfxMessageBox("unknown format");
			return;
		}
		ar.ReadString(line);
		if (line.Left(1) == "#"){
		ar.ReadString(line);
		}
		pos=0; line.Trim();
		token=line.Tokenize(" ",pos);
		ncolumns= _ttoi(token);
		token=line.Tokenize(" ",pos);
		nrow= _ttoi(token);

		ar.ReadString(line); Lmax=_ttoi(line);

		ar.ReadString(line);pos=0;
		for (int y = 0;y<nrow;y++)
		{
			for(int x=0;x<ncolumns;x++){
				token=line.Tokenize(" ", pos);
				if (token==""){
					ar.ReadString(line);pos=0;
					token=line.Tokenize(" ", pos);
				}
			Img[x][y] = _ttoi(token);
				
			}
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CKursovazadDIPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CKursovazadDIPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CKursovazadDIPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CKursovazadDIPDoc diagnostics

#ifdef _DEBUG
void CKursovazadDIPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKursovazadDIPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKursovazadDIPDoc commands
