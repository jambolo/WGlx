/** @file *//********************************************************************************************************

                                                       WGlx.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/WGlx.cpp#2 $

	$NoKeywords: $

 ********************************************************************************************************************/


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "WGlx.h"

#include <windows.h>

#include <cassert>

namespace WGlx
{


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

/// @param	nWidth,nHeight,nDepth	Screen resolution. @p CW_USEDEFAULT is not valid.
/// @param	lpClassName				See the docs for @c CreateWindowEx.
/// @param	lpWindowName			See the docs for @c CreateWindowEx.
/// @param	hInstance				See the docs for @c CreateWindowEx.
/// @param	dwStyle					See the docs for @c CreateWindowEx. @p WS_POPUP, @p WS_CLIPSIBLINGS, and
///									@p WS_CLIPCHILDREN are set automatically
/// @param	dwExStyle				See the docs for @c CreateWindowEx. @p WS_EX_TOPMOST is set automatically
/// @param	hWndParent				See the docs for @c CreateWindowEx.
/// @param	hMenu					See the docs for @c CreateWindowEx.
/// @param	lpParam					See the docs for @c CreateWindowEx.

HWND CreateFullScreenWindow( int nWidth, int nHeight, int nDepth,
							 LPCTSTR lpClassName,
							 LPCTSTR lpWindowName,
							 HINSTANCE hInstance,
							 DWORD dwStyle		/* = 0*/,
							 DWORD dwExStyle	/* = 0*/,
							 HWND hWndParent	/* = NULL*/,
							 HMENU hMenu		/* = NULL*/,
							 LPVOID lpParam		/* = NULL*/ )
{
	assert( nWidth != CW_USEDEFAULT );
	assert( nHeight != CW_USEDEFAULT );

	// Create a TOPMOST borderless window. WS_CLIPSIBLINGS and WS_CLIPCHILDREN are required for OpenGL.

	HWND hWnd = CreateWindowEx( WS_EX_TOPMOST | dwExStyle,
								lpClassName,
								lpWindowName,
								WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
								0, 0, nWidth, nHeight,
								hWndParent,
								hMenu,
								hInstance,
								lpParam );

	if ( hWnd == NULL )
	{
		return hWnd;
	}

	// Change the display mode so that the window fills the screen

	bool ok;
	
	ok = ChangeDisplayMode( nWidth, nHeight, nDepth );
	if ( !ok )
	{
		DestroyWindow( hWnd );
		hWnd = NULL;
	}

	return hWnd;
}


} // namespace WGlx
