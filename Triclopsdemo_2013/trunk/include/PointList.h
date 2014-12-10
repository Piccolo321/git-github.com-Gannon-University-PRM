//=============================================================================
// Copyright � 2003 Point Grey Research, Inc. All Rights Reserved.
// 
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research, Inc. (PGR).
// 
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: PointList.h,v 1.2 2010/05/26 00:58:27 arturp Exp $
//=============================================================================
#ifndef __POINTLIST_H__
#define __POINTLIST_H__

#pragma once

//=============================================================================
// System Includes
//=============================================================================
#include <afxtempl.h>
#include <afxwin.h>
//=============================================================================
// PGR Includes
//=============================================================================

//=============================================================================
// Project Includes
//=============================================================================
#include "3dPoint.h"
#include "ProgressBar.h"


//
// Number of points to grow the array by at a time.
//
#define _GROWBY 1000



/**
 * A reimplementation of the internal PGRPointcloud3d class.  This class 
 * inherits from the MFC CArray and contains a list of C3dColourPointRC 
 * pointers which have been allocated somewhere else.  It provides useful 
 * functions like center of mass.
 */
class CPointList : public CArray< C3dColourPointRC*, C3dColourPointRC* >
{
public:
	  //Yixin Geng
       double minDis;      
		   
	   CPointList* getRealWorldPoint(float baseDistance);

       C3dColourPointRC* getNearestPixel(C3dColourPointRC *p, CPointList* cList);

	   double getDistBetweenTwoPoints(C3dColourPointRC * p1,C3dColourPointRC * p2 );
	
	   CPointList*  getResolutionToPointList(CPointList* grid, CPointList* realWorldXYZ,double startx,double starty,double endx,double endy,float smsurface);	

	   bool saveToMillFormat(const char* pszFileName, int gridXnum, int gridYnum);

       double getRealCenterYByCenterPix(int PixelX, int PixelY);
       double getRealCenterXByCenterPix(int PixelX, int PixelY);
       double getDistBetweenTwoPixes(C3dColourPointRC * p1,C3dColourPointRC * p2 );
       C3dColourPointRC* getNearestPosition(C3dColourPointRC *p, CPointList* vecMap);
       //char* CPointList::RandomString();
	   
	   //To check gridpoint is in ROI or not
       bool isGridInROI(C3dColourPointRC *grid,double startx,double starty,double endx,double endy);

	   //Average z value of all pixels within 1/4"
       double CPointList::getNearestPixelAverageZ(C3dColourPointRC *p, CPointList* vecMap,float smsurface);
		   
	/**
    * Default constructor.
    *
    * @param growBy The number of elements to grow by if we need more space.
    */
   CPointList( int growBy = 1000 );

   /** Default copy constructor. */
   CPointList( const CPointList& pointlist );

   /** Default destructor. */
   virtual ~CPointList();

   CPointList& operator=( const CPointList& pointlist );

   /** Calculates and returns the center of mass of all the points. */
   void getCenterOfMass( C3dColourPointRC* ppoint );

   /** Current one-based size of the point list. */
   INT_PTR size() const;

   /** Remove all elements of the point list. */
   void empty();

   /** Return the element at the given zero-based index. */
   C3dColourPointRC* elementAt( int iIndex ) const;

   /** Insert the passed pointer into the list. */
   INT_PTR insertPoint( C3dColourPointRC* ppoint );

   /** save the point cloud to the specified file */
   bool save( const char* pszFileName );
   bool save(const char *pszFileName, double size);
   
protected:

   /** Storage for the center of mass.  Not used. */
   C3dColourPointRC m_centerOfMass;
};


#endif // #ifndef __POINTLIST_H__
