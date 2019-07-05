/*****************************************************************************

                               DisplayMode.cpp

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/DisplayMode.cpp#4 $

	$NoKeywords: $

*****************************************************************************/

#include "DisplayMode.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>

#include <vector>



namespace WGlx
{


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

bool ChangeDisplayMode( int width, int height, int depth )
{
	DEVMODE	modeInfo;
	ZeroMemory( &modeInfo, sizeof( modeInfo ) );
	modeInfo.dmSize			= sizeof( modeInfo );
	modeInfo.dmPelsWidth	= width;
	modeInfo.dmPelsHeight	= height;
	modeInfo.dmBitsPerPel	= depth;
	modeInfo.dmFields		= DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;

	return ( ChangeDisplaySettings( &modeInfo, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

bool RestoreDisplayMode()
{
	return ( ChangeDisplaySettings( NULL, 0 ) == DISP_CHANGE_SUCCESSFUL );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

std::vector< DEVMODE > EnumerateDisplayModes()
{
	std::vector< DEVMODE >	modeList;

	int		i		= 0;
	bool	done	= false;

	while ( !done )
	{
		DEVMODE	modeInfo;
		ZeroMemory( &modeInfo, sizeof( modeInfo ) );
		modeInfo.dmSize = sizeof( modeInfo );

		if ( EnumDisplaySettings( NULL, i, &modeInfo ) == 0 )
		{
			done = true;
			continue;
		}

		modeList.push_back( modeInfo );
		++i;
	}

	return modeList;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

bool SetPixelFormat(	HDC hDC,
						PIXELFORMATDESCRIPTOR *	pReturnedPfd/*		= 0*/,
						bool					doubleBuffered/*	= false*/,
						bool					accelerated/*		= true*/,
						int						colorBits/*			= 24*/,
						int						depthBits/*			= 32*/,
						int						stencilBits/*		= 0*/,
						int						accumBits/*			= 0*/ )
{
	PIXELFORMATDESCRIPTOR	pfd;
	int						pf;

	memset( &pfd, 0, sizeof pfd );
	pfd.nSize			= sizeof pfd;
	pfd.nVersion		= 1;
	pfd.dwFlags |=						PFD_DRAW_TO_WINDOW;
	pfd.dwFlags |=						PFD_SUPPORT_OPENGL;
	pfd.dwFlags |= doubleBuffered ? 	PFD_DOUBLEBUFFER :
										( PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER_DONTCARE );
	pfd.dwFlags |= accelerated ?		PFD_GENERIC_ACCELERATED :	0;
	pfd.dwFlags |= ( depthBits < 0 ) ?	PFD_DEPTH_DONTCARE : 0;

	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.cColorBits		= colorBits;
	pfd.cDepthBits		= ( depthBits >= 0 ) ? depthBits : 0;
	pfd.cStencilBits	= stencilBits;
	pfd.cAccumBits		= accumBits;

	pf = ::ChoosePixelFormat( hDC, &pfd );
	if ( pf == 0 )
		return false;

	if ( ::SetPixelFormat( hDC, pf, &pfd ) == FALSE )
	{
		return false;
	} 

	if ( pReturnedPfd != 0 )
	{
		::DescribePixelFormat( hDC, pf, sizeof PIXELFORMATDESCRIPTOR, pReturnedPfd );
	}

	return true;
}


} // namespace WGlx