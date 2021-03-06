
// SDICDCView.cpp: CSDICDCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDICDC.h"
#endif

#include "SDICDCDoc.h"
#include "SDICDCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDICDCView

IMPLEMENT_DYNCREATE(CSDICDCView, CView)

BEGIN_MESSAGE_MAP(CSDICDCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CSDICDCView 생성/소멸

CSDICDCView::CSDICDCView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	TRACE("CSDICDCView::CSDICDCView()\n");

	m_bCollision[0] = m_bCollision[1] = false;
	m_rcCollison[0] = CRect(10, 80, 10 + 100, 80 + 100);
	m_rcCollison[1] = CRect(10, 200, 10 + 100, 200 + 100);


}

CSDICDCView::~CSDICDCView()
{
}

BOOL CSDICDCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDICDCView 그리기

bool CSDICDCView::IsColl(CRect rc, CPoint pt)
{
	
	if (rc.left<pt.x && rc.right>pt.x && rc.top<pt.y && rc.bottom>pt.y)
	{

		return true;
	}
	
	
	return false;
}

void CSDICDCView::OnDraw(CDC* pDC) //하얀 화면에서 그리기
{
	CSDICDCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->TextOut(10, 10, "KITRI");

	CRect rc;

	GetClientRect(&rc);
	CString str;
	str.Format("view Width(%d),view Height(%d)", rc.Width(), rc.Height());
	pDC->TextOut(10, 30, str);


	//Line (move to -> line to)
	CPoint pt;
	pt.x = 10;
	pt.y = 60;
	pDC->MoveTo(pt);
	
	pt.x = 100;
	pt.y = 60;
	pDC->LineTo(pt);


	// rectangle
	pDC->Rectangle(10,80,10+100,80+100); //x,y, weidth, height
	CRect Rectrc = { 10,200,10 + 100,200 + 100 };
	pDC->Rectangle(Rectrc);


	for (int i = 0; i < 2; i++)
	{

		if (m_bCollision[i])
			pDC->Ellipse(m_rcCollison[i]);
	
	}


	//ellipse //순서 중요해!!
	pDC->Ellipse(130,80,130+100,80+100);
	CRect ellipse = {130,200,130+100,200+100};
	pDC->Ellipse(ellipse);


	//pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);

	for (list<CRect*>::iterator itor = m_listRect.begin(); itor != m_listRect.end(); ++itor) //itor 값은 node 의 주소!! 값이 아니다!
	{
		CRect* rc = (*itor); // itor 값을 호출 그러므로 * 값을 항상 붙여줘야함
		pDC->Rectangle(*rc);

	}



	// on draw 에서 pDC의 주소 값이 필요함 (when 그림이 그릴때!)


}


// CSDICDCView 인쇄

BOOL CSDICDCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDICDCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDICDCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSDICDCView 진단

#ifdef _DEBUG
void CSDICDCView::AssertValid() const
{
	CView::AssertValid();
}

void CSDICDCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDICDCDoc* CSDICDCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDICDCDoc)));
	return (CSDICDCDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDICDCView 메시지 처리기


void CSDICDCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//TRACE("OnMouseMove()\n");

	
	m_ptMouse = point;

	for (int i = 0; i < 2; i++)
	{

		if (IsColl(m_rcCollison[i], m_ptMouse))
		{
			m_bCollision[i] = true;

			break;

		}
		else
		{
			m_bCollision[i] = false;


		}


	}


	Invalidate();
	

	CView::OnMouseMove(nFlags, point);
}




void CSDICDCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TRACE("OnNcLButtonDown()x(%d) y(%d)\n", point.x, point.y);


	CRect* rc = new CRect;
	rc->left = point.x;
	rc->top = point.y;
	rc->right = point.x + 100;
	rc->bottom = point.y + 100;


	m_listRect.push_back(rc);

	Invalidate(); //화면 갱신해줘

	

	



	/*
	CClientDC dc(this); // 화면의 주소를 얻게됨 하지만 위와 같이 그릴수 있지만 화면이 갱신 되면 이 값들을 삭제 됨.
	dc.Rectangle(rc); // 강제로 그림을 그릴수 있지만 창을 내렸다가 올리면 그림이 사라짐 (onDraw 값이 호출되므로)
	*/	              // 이러한 정보들을 저장 해 놓아야 됨(저장공간)

	/*
	m_ptStart.x = rc.left;
	m_ptStart.y = rc.top;
	m_ptEnd.x = rc.right;
	m_ptEnd.y = rc.bottom;
	*/






	CView::OnLButtonDown(nFlags, point);
}


void CSDICDCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);
}
