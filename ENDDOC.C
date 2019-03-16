/****************************************************************************
 *  LONG APIENTRY EndDocument( HDC hdcPrinter )                             *
 *  Purpose          This function ends a print job started by the          *
 *                   StartDocument function.                                *
 *                                                                          *
 *  Parameters       hdcPrinter contains a handle to a previously           *
 *                   opened printer device context.                         *
 *                                                                          *
 *  Return Value     This function returns DEV_OK if no error occurred,     *
 *                   otherwise it returns a value of DEVESC_ERROR or        *
 *                   or DEVESC_NOTIMPLEMENTED.                              *
 ****************************************************************************/

    #define INCL_DEV
    #include <os2.h>

/****************************************************************************/
    LONG EXPENTRY EndDocument( HDC hdcPrinter )
    {
        return DevEscape( hdcPrinter,DEVESC_ENDDOC,0L,NULL,NULL,NULL );
    }
/****************************************************************************/
