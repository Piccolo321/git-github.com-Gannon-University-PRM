//=============================================================================
// Copyright © 2005 Point Grey Research, Inc. All Rights Reserved.
// 
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research Inc.
// 
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//
// Digiclops® is a registered trademark of Point Grey Research Inc.
//=============================================================================
//=============================================================================
// $Id: MainFrm.h,v 1.1 2007/03/27 21:33:01 demos Exp $
//=============================================================================
#if !defined(AFX_MAINFRM_H__FBEBA4D9_E451_4275_A6F2_AED9365A55A2__INCLUDED_)
#define AFX_MAINFRM_H__FBEBA4D9_E451_4275_A6F2_AED9365A55A2__INCLUDED_

#pragma once

//=============================================================================
// PGR Includes
//=============================================================================
#include "PGRMainFrm.h"
#include "PGRStereoDoc.h"
#include "PGRStereoControlDialog.h"


/**
 * This class is the MFC CMainFrame MDI class.
 */
class CMainFrame : public CPGRMainFrame
{
   DECLARE_DYNAMIC( CMainFrame )

public:
   CMainFrame();

public:
   
   //{{AFX_VIRTUAL(CMainFrame)
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   //Dipti Killedar
   afx_msg void OnWindowNew3d();
   int window_flag;

   //void OnFileExportHighResolution();
   /*CPGRStereoControlDialog m_dialogStereo;
   CPGRStereoDoc m_stereoDoc;*/
  
   //}}AFX_VIRTUAL

public:
   virtual ~CMainFrame();
   
protected:

   //{{AFX_MSG(CMainFrame)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

   //Dipti Killedar
   //Yixin Geng
   //afx_msg void OnWindowNew3d();
   //void OnFileExportHighResolution();

   afx_msg void OnInitMenu(CMenu* pMenu);

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_MAINFRM_H__FBEBA4D9_E451_4275_A6F2_AED9365A55A2__INCLUDED_)
