#if !defined( WGLX_H_INCLUDED )
#define WGLX_H_INCLUDED

#pragma once

/** @file *//********************************************************************************************************

                                                        WGlx.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/WGlx.h#4 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include <windows.h>

// Include all WGlx headers for convenience

#include "Font.h"
#include "Extensions.h"
#include "DisplayMode.h"


namespace WGlx
{


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

/// A WGL rendering context wrapper

class RenderingContext
{
public:
	RenderingContext( HDC hDC )
		: m_Handle( wglCreateContext( hDC ) )
	{
		wglMakeCurrent( hDC, m_Handle );
	}

	~RenderingContext()
	{
//		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( m_Handle );
	}

	// Return the rendering context handle
	HGLRC	GetHandle()		{ return m_Handle; }

private:
	HGLRC	m_Handle;		// Rendering context handle
};


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

HWND CreateFullScreenWindow( int nWidth, int nHeight, int nDepth,
							 LPCTSTR lpClassName,
							 LPCTSTR lpWindowName,
							 HINSTANCE hInstance,
							 DWORD dwStyle		= 0,
							 DWORD dwExStyle	= 0,
							 HWND hWndParent	= NULL,
							 HMENU hMenu		= NULL,
							 LPVOID lpParam		= NULL );

} // namespace WGlx


#endif // !defined( WGLX_H_INCLUDED )
