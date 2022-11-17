
// KursovazadDIPView.cpp : implementation of the CKursovazadDIPView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KursovazadDIP.h"
#endif

#include "KursovazadDIPDoc.h"
#include "KursovazadDIPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKursovazadDIPView

IMPLEMENT_DYNCREATE(CKursovazadDIPView, CView)

BEGIN_MESSAGE_MAP(CKursovazadDIPView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKursovazadDIPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CKursovazadDIPView construction/destruction

CKursovazadDIPView::CKursovazadDIPView()
{
	// TODO: add construction code here

}

CKursovazadDIPView::~CKursovazadDIPView()
{
}

BOOL CKursovazadDIPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKursovazadDIPView drawing

void CKursovazadDIPView::OnDraw(CDC* pDC)
{
	CKursovazadDIPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	for (int y =0;y<pDoc->nrow;y++){
		for(int x=0;x<pDoc->ncolumns;x++){
		int g = pDoc->Img[x][y];
		pDC->SetPixel(x,y,RGB(g,g,g));

		int new_g=(g+50)%(pDoc->Lmax+1);
			pDC->SetPixel(x+pDoc->ncolumns+10,y,RGB(new_g,new_g,new_g));
		}
	}
}


// CKursovazadDIPView printing


void CKursovazadDIPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKursovazadDIPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKursovazadDIPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKursovazadDIPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKursovazadDIPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKursovazadDIPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKursovazadDIPView diagnostics

#ifdef _DEBUG
void CKursovazadDIPView::AssertValid() const
{
	CView::AssertValid();
}

void CKursovazadDIPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKursovazadDIPDoc* CKursovazadDIPView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKursovazadDIPDoc)));
	return (CKursovazadDIPDoc*)m_pDocument;
}
#endif //_DEBUG


// CKursovazadDIPView message handlers
