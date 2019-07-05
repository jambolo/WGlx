#if !defined( WGLX_DISPLAYMODE_H_INCLUDED )
#define WGLX_DISPLAYMODE_H_INCLUDED

#pragma once

/*****************************************************************************

                                DisplayMode.h

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/WGlx/DisplayMode.h#2 $

	$NoKeywords: $

*****************************************************************************/

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>

namespace WGlx
{

// Choose, set, and describe pixel format
bool SetPixelFormat( HDC						hDC,
					 PIXELFORMATDESCRIPTOR *	pReturnedPfd	= 0,
					 bool						doubleBuffered	= false,
					 bool						accelerated		= true,
					 int						colorBits		= 24,
					 int						depthBits		= 32,
					 int						stencilBits		= 0,
					 int						accumBits		= 0 );

// Change the display mode
bool ChangeDisplayMode( int width, int height, int depth );

// Set the display mode back to normal
bool RestoreDisplayMode();

// Return a vector of all possible display modes
std::vector< DEVMODE > EnumerateDisplayModes();

} // namespace WGlx


#endif // !defined( WGLX_DISPLAYMODE_H_INCLUDED )
