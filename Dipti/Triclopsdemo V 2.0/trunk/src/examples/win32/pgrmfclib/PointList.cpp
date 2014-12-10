//=============================================================================
// Copyright © 2005 Point Grey Research, Inc. All Rights Reserved.
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
// $Id: PointList.cpp,v 1.2 2010/05/26 00:58:27 arturp Exp $
//=============================================================================

//=============================================================================
// System Includes
//=============================================================================
#include <afxcmn.h>
#include <atltypes.h>
//=============================================================================
// PGR Includes
//=============================================================================

//=============================================================================
// Project Includes
//=============================================================================
#include "PointList.h"
#include <cmath>
//#include "CryptString.h"
#include <iostream>
#include "string.h"



CPointList::CPointList( int growBy )
{
   SetSize( 0, growBy );
}

CPointList::CPointList( const CPointList& pointlist )
{
   m_centerOfMass = pointlist.m_centerOfMass;
}


CPointList::~CPointList()
{   
}


CPointList& 
CPointList::operator=( const CPointList& pointlist )
{
   m_centerOfMass = pointlist.m_centerOfMass;
   return *this;
}


void
CPointList::getCenterOfMass( C3dColourPointRC* ppoint )
{
   double sumX = 0;
   double sumY = 0;
   double sumZ = 0;
   
   for ( int i = 0; i < GetSize(); i++ )
   {
      const C3dColourPointRC* ppoint = ElementAt( i );

      sumX += ppoint->x();
      sumY += ppoint->y();
      sumZ += ppoint->z();
   }

   sumX	/= (double)size();
   sumY	/= (double)size();
   sumZ	/= (double)size();
   
   m_centerOfMass.setXYZ( sumX, sumY, sumZ );
   
   ppoint->setXYZ( sumX, sumY, sumZ );
}


INT_PTR 
CPointList::size() const
{
   return GetSize();
}

void 
CPointList::empty()
{
   RemoveAll();
}

C3dColourPointRC *CPointList::elementAt( int iIndex ) const
{
   return GetAt( iIndex );
}


INT_PTR 
CPointList::insertPoint( C3dColourPointRC* ppoint )
{
   ASSERT( ppoint != NULL );
   return Add( ppoint );
}


bool
CPointList::save( const char* pszFileName )
{
   // save the current point list to the named file
   // - each line contains a single point
   // - each point includes 3d coordinates, rgb color mapping and
   //   the row and column in the reference image where the point originates.
   FILE* pPointFile;
   
   if ( ( pPointFile = fopen( pszFileName, "w" ) ) == NULL )
   {
      return false;
   }
   
   for ( int i = 0; i < GetSize(); i++ )
   {
      const C3dColourPointRC* pPoint = ElementAt( i );
      const RGBQUAD*  pPointColour = pPoint->colour();
	    
      fprintf( 
	 pPointFile,
	 "%lf %lf %lf %d %d %d %lf %lf\n",
	 pPoint->x(),
	 pPoint->y(),
	 pPoint->z(),
	 (int)pPointColour->rgbRed,
	 (int)pPointColour->rgbGreen,
	 (int)pPointColour->rgbBlue,
	 (double) pPoint->row(),
	 (double) pPoint->col() 
	 );
     
   }

   fclose( pPointFile );
   
   return true;

}


/*
 =======================================================================================================================
    Saves the Pointlist file
 =======================================================================================================================
 */
bool CPointList::save(const char *pszFileName, double size)
{

    /*
     * save the current point list to the named file ;
     * - each line contains a single point ;
     * - each point includes 3d coordinates, rgb color mapping and ;
     * the row and column in the reference image where the point originates.
     */
    FILE    *pPointFile;

    if((pPointFile = fopen(pszFileName,"w")) == NULL)
    {
        return false;
    }

    for(int i = 0; i < GetSize(); i++)
    {
        const C3dColourPointRC  *pPoint = ElementAt(i);
        const RGBQUAD           *pPointColour = pPoint->colour();

        fprintf
        (
            pPointFile,
            "%lf %lf %lf %d %d %d %lf %lf\n",
            pPoint->x() * size,
            pPoint->y() * size,
            pPoint->z() * size,
            (int)pPointColour->rgbRed,
            (int)pPointColour->rgbGreen,
            (int)pPointColour->rgbBlue,
            (double)pPoint->row(),
            (double)pPoint->col()
        );
    }

    fclose(pPointFile);

    return true;
}

/**
 =======================================================================================================================
    added by Dr. Frank Xu* Gets the X, Y Z value of the seat
 =======================================================================================================================
 */
CPointList *CPointList::getRealWorldPoint(float baseDistance)
{
    CPointList          *pList = new CPointList();
    C3dColourPointRC    *newpPoint;
    for(int i = 0; i < GetSize(); i++)
    {
        C3dColourPointRC    *pPoint = ElementAt(i);
        RGBQUAD             *pPointColour = pPoint->colour();
        newpPoint = new C3dColourPointRC();
        newpPoint->setXYZ(pPoint->x(),pPoint->y(),baseDistance - pPoint->z());
        newpPoint->setColRow(pPoint->col(),pPoint->row());
        newpPoint->setColour(pPointColour);
        pList->insertPoint(newpPoint);
    }

    return pList;
}

/*
 =======================================================================================================================
      Finds distance between two Points
 =======================================================================================================================
 */
double CPointList::getDistBetweenTwoPoints(C3dColourPointRC *p1, C3dColourPointRC *p2)
{
    double  x1 = p1->x();
    double  y1 = p1->y();
    double  x2 = p2->x();
    double  y2 = p2->y();
    double  dist = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    return dist;
}

/*
 =======================================================================================================================
    Finds distance between two Pixels
 =======================================================================================================================
 */
double CPointList::getDistBetweenTwoPixes(C3dColourPointRC *p1, C3dColourPointRC *p2)
{
    double  x1 = p1->col();
    double  y1 = p1->row();
    double  x2 = p2->col();
    double  y2 = p2->row();
    double  dist = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    return dist;
}

/*
 =======================================================================================================================
     Searches the whole Pointlist and finds the nearest Position
 =======================================================================================================================
 */
C3dColourPointRC* CPointList::getNearestPosition(C3dColourPointRC *p, CPointList *vecMap)
{
    double              minDis = 1000;
    
    /* pixel with real value we wanted */
    C3dColourPointRC    *NearestPixel = new C3dColourPointRC();
    for(int i = 0; i < vecMap->GetSize(); i++)
    {
        C3dColourPointRC    *currentPixel = vecMap->GetAt( i );
        double              dis = getDistBetweenTwoPixes(p,currentPixel);
        if(dis < minDis)
        {
            minDis = dis;
            NearestPixel = currentPixel;
        }
    }

    return NearestPixel;
}

/*
 =======================================================================================================================
    Searches the whole Pointlist and finds the nearest Pixel
 =======================================================================================================================
 */
C3dColourPointRC *CPointList::getNearestPixel(C3dColourPointRC *p, CPointList *vecMap)
{
    double              minDis = 1000;

    /* pixel with real value we wanted */
    C3dColourPointRC    *NearestPixel = new C3dColourPointRC();
    for(int i = 0; i < vecMap->GetSize(); i++)
    {
        C3dColourPointRC    *currentPixel = vecMap->GetAt(i);
        double              dis = getDistBetweenTwoPoints(p,currentPixel);

        if(dis < minDis)
        {
            minDis = dis;
            NearestPixel = currentPixel;
        }
    }

    
    return NearestPixel;
}

/*
 =======================================================================================================================
    Get 5 nearest Pixels within 1/4" and average the Z values
 =======================================================================================================================
 */
double CPointList::getNearestPixelAverageZ(C3dColourPointRC *p, CPointList *vecMap, float smsurface)
{
    double inchToMeter= 0.0254;
    double  total, avgz;
    avgz = 0.0;
    total = 0.0;


    CPointList  *pList = new CPointList();

	 
    for(int i = 0; i < vecMap->GetSize(); i++)
    {
        C3dColourPointRC    *currentPixel = vecMap->GetAt(i);
        double              dis = getDistBetweenTwoPoints(p,currentPixel);
        if(dis <= smsurface)
        {
            pList->insertPoint(currentPixel);
            total = total + currentPixel->z();
        }
    }

    int numberOfPointsInRange=pList->GetSize();
	
	if(numberOfPointsInRange!=0){
		avgz = total / numberOfPointsInRange;
	}
	else{
		avgz=getNearestPixelAverageZ(p, vecMap,smsurface+0.1*inchToMeter);
	}
    
    return avgz;
}

/*
 =======================================================================================================================
    Places realworldpoint on Grid of 80*80 or 40*32
 =======================================================================================================================
 */
CPointList *CPointList::getResolutionToPointList
(
    CPointList  *grid,
    CPointList  *realWorldPoint,
    double      startx,
    double      starty,
    double      endx,
    double      endy,
    float       smsurface
)
{
	double inchToMeter= 0.0254;
    CPointList  *resolutionMill = new CPointList();

	//Yixin Geng
	//Creating a progress bar
	
	CProgressBar *progressBar = new CProgressBar();
	progressBar->Create();
	progressBar->SetBar( grid->GetSize() );
	progressBar->ShowWindow(SW_SHOW);
	progressBar->UpdateWindow();

	int length = grid->GetSize();
	for(int i = 0; i < grid->GetSize(); i++)
    {
        printf("Processing pixel %d \n",i);
        
        C3dColourPointRC    *resultPoint = new C3dColourPointRC();
        C3dColourPointRC    *currentGrid = grid->ElementAt(i);
        double              z = 5*inchToMeter;

        if(isGridInROI(currentGrid,startx,starty,endx,endy))
        {
            C3dColourPointRC    *p = getNearestPixel(currentGrid,realWorldPoint);
            z = getNearestPixelAverageZ(currentGrid,realWorldPoint,smsurface);
        }

        resultPoint->setXYZ(currentGrid->x(),currentGrid->y(),z);
        resolutionMill->insertPoint(resultPoint);
	
		progressBar->m_progresstime.StepIt();	
    }

	delete progressBar;

    return resolutionMill;
}

/*
 =======================================================================================================================
     Check if the ColourPointRC is inside the ROI
 =======================================================================================================================
 */
bool CPointList::isGridInROI(C3dColourPointRC *currentgrid, double startx, double starty, double endx, double endy)
{
    if
    (
        (currentgrid->x() >= startx)
    &&  (currentgrid->x() <= endx)
    &&  (currentgrid->y() >= starty)
    &&  (currentgrid->y() <= endy)
    ) return 1;
    else
        return 0;
}

/*
 =======================================================================================================================
    Generate Random String
 =======================================================================================================================
 
char* CPointList::RandomString()
{


    int IMax=28;
    int IMin=0;
    char key[8];
  
	//char encrykey1[]={'M','z','b','@','a','c','i','*','d','e','#','%','&','^','!','$','d','e','f','u','r','s','t','u','v','X','Y','Z'};
	char encrykey1[]={'M','z','b','@','a','c','i','*','d','e','#','%','&','^','!','$','d','e','f','u','r','s','t','u','v','X','Y','Z'};
    for(int i=0;i<8;i++){
		int I = IMin + rand() % (IMax - IMin);
		key[i]=encrykey1[I];
	//	printf("encryptionkey[%d]=%c \n",I,encrykey[I]);
	}
  
	return key;
}*/


/*
 =======================================================================================================================
    Save X Y Z values of image to Mill Format 
 =======================================================================================================================
 */

bool CPointList::saveToMillFormat(const char *pszFileName, int gridXnum, int gridYnum)
{  int EncrypYesORNo=0;

  if(EncrypYesORNo==1)
  {/*

	   // Init the crypto class
	CCryptString oCrypt;
	TCHAR szEncryptPwd[32] = _T("");
	TCHAR szPasswordDecrypted[32] = _T("");
	TCHAR szKey[] = _T("georg");

    /*
     * save the current point list to the named file ;
     * - each line contains a single point ;
     * - each point includes 3d coordinates, rgb color mapping and ;
     * the row and column in the reference image where the point originates.
     *
    float   inchUnitForMeter = 39.37;
    char szPassword[8];
    FILE    *pPointFile;

    if((pPointFile = fopen(pszFileName,"w")) == NULL)
    {
        return false;
    }

    fprintf(pPointFile,"%d\n",gridXnum);
    fprintf(pPointFile,"%d %d %d\n",0,0,0);

    int row = 1;
    for(int i = 0; i < GetSize(); i++)
    {
        const C3dColourPointRC  *pPoint = ElementAt(i);
        float                   z = (pPoint->z() * inchUnitForMeter);
		 
		
        sprintf(szPassword,"%f",z);
		 oCrypt.EncryptString(szPassword,szEncryptPwd,szKey);
		 

        if(i % gridYnum == 0)
        {
            fprintf(pPointFile,"%d\n",row);
            row++;
        }

        fprintf(pPointFile,"%s  ",szEncryptPwd);

		

        if((i + 1) % 8 == 0)
        {
            fprintf(pPointFile,"\n");
        }
    }

    fclose(pPointFile);

    */
    return true;
  }
  else{
	  
	
    /*
     * save the current point list to the named file ;
     * - each line contains a single point ;
     * - each point includes 3d coordinates, rgb color mapping and ;
     * the row and column in the reference image where the point originates.
     */
      float   inchUnitForMeter = 39.37;
	  char szPassword[8];
    FILE    *pPointFile;
	int i;

    if((pPointFile = fopen(pszFileName,"w")) == NULL)
    {
        return false;
    }

    fprintf(pPointFile,"%d\n",gridXnum);
    fprintf(pPointFile,"%d %d %d\n",0,0,0);

    int row = 0;
    for(i = 0; i < GetSize(); i++)
    {
        const C3dColourPointRC  *pPoint = ElementAt(i);
        float                   z = (pPoint->z() * inchUnitForMeter);
					
		if(i % gridYnum == 0)
        {
            fprintf(pPointFile,"%d\n",row);
            row++;
        }

        fprintf(pPointFile,"%f  ",z);

		

        if((i + 1) % 81 == 0)
        {
            fprintf(pPointFile,"\n");
        }
    }

    fclose(pPointFile);


    return true;
  }
   
  
   

}

/*
 =======================================================================================================================
    From Pixel (row,col) value in image get Real Camera X co-ordinate value
 =======================================================================================================================
 */
double CPointList::getRealCenterXByCenterPix(int PixelX, int PixelY)
{
    C3dColourPointRC    *pPoint;
    double              resultX = 0;
    for(int i = 0; i < GetSize(); i++)
    {
        pPoint = ElementAt(i);
        resultX = pPoint->x();
        if((pPoint->col() == PixelX) && (pPoint->row() == PixelY))
        {
            return resultX;
        }
    }

    return 0;
}

/*
 =======================================================================================================================
    From Pixel (row,col) value in image get Real Camera Y co-ordinate value
 =======================================================================================================================
 */
double CPointList::getRealCenterYByCenterPix(int PixelX, int PixelY)
{
    C3dColourPointRC    *pPoint;
    double              resultY = 0;
    for(int i = 0; i < GetSize(); i++)
    {
        pPoint = ElementAt(i);
        resultY = pPoint->y();
        if((pPoint->col() == PixelX) && (pPoint->row() == PixelY))
        {
            return resultY;
        }
    }

    return 0;
}
