/****************************************************************************
 *  LONG APIENTRY StartDocument( HDC hdcPrinter,PSZ pszDocName )            *
 *  Purpose         This function allows the application to signal          *
 *                  that a new print job is starting.                       *
 *                                                                          *
 *  Parameters      hdcPrinter contains a handle to a previously            *
 *                  opened printer device context.                          *
 *                                                                          *
 *                  pszDocName points to a null-terminated ASCII            *
 *                  containing the name of the document.                    *
 *                                                                          *
 *  Return Value    This function returns DEV_OK if no error occurred,      *
 *                  otherwise it returns a value of DEVESC_ERROR or         *
 *                  or DEVESC_NOTIMPLEMENTED.                               *
 ****************************************************************************/

    #define INCL_DEV
    #include <os2.h>
    #include <string.h>

/****************************************************************************/
    LONG EXPENTRY StartDocument( HDC hdcPrinter,PSZ pszDocName )
    {
        return DevEscape( hdcPrinter,
                          DEVESC_STARTDOC,
                          (LONG) strlen(pszDocName),
                          pszDocName,
                          NULL,
                          NULL );
    }
/****************************************************************************/
