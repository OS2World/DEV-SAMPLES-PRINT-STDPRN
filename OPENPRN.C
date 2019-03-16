/****************************************************************************
 *  HDC APIENTRY OpenDefaultPrinterDC( HAB hab,                             *
 *                                     PSZ pszAppName,                      *
 *                                     PSZ pszRedirect )                    *
 *                                                                          *
 *  Purpose             This function opens a device context for the        *
 *                      current default printer.                            *
 *                                                                          *
 *  Parameters          hab contains the anchor block handle.               *
 *                                                                          *
 *                      pszAppName points to a null-terminated string       *
 *                      that contains the name of the application.          *
 *                                                                          *
 *                      pszRedirect points to a null-terminated string      *
 *                      that contains the name of the file to which         *
 *                      printer output is to be redirected. This parameter  *
 *                      is NULL if no output redirection is desired.        *
 *                                                                          *
 *  Return Value        This function returns a handle to the opened        *
 *                      printer device context. This return value is        *
 *                      DEV_ERROR if the function is unsuccessful.          *
 ****************************************************************************/

    #define INCL_DEV
    #define INCL_WINSHELLDATA
    #include <os2.h>
    #include <string.h>

/****************************************************************************/
    HDC EXPENTRY OpenDefaultPrinterDC( HAB hab,PSZ pszAppName,PSZ pszRedirect )
    {
        #define MAX_STRING_LEN  256

        static CHAR     szPrinter[MAX_STRING_LEN];
        static CHAR     szDetails[MAX_STRING_LEN];
        static DRIVDATA driv;

        DEVOPENSTRUC    dop;
        PCHAR           pchDelimiter;

    /* Get the default printer name, for example, "PRINTER1" */
        WinQueryProfileString( hab,
                "PM_SPOOLER",       // section name
                "PRINTER",          // keyname
                ";",                // default
                szPrinter,          // profile string
                MAX_STRING_LEN );   // maximum characters

        if ( NULL != (pchDelimiter = strchr(szPrinter,';')) )
            *pchDelimiter = '\0';

    /* Get the printer details.
     *  Fill in a supplied string with substrings:
     *  <physical port>;<driver name>;<queue port>;<network params>;
     */
        WinQueryProfileString( hab,
                "PM_SPOOLER_PRINTER",
                szPrinter,
                ";;;;",
                szDetails,
                MAX_STRING_LEN );

    /* Fill in the DEVOPENSTRUC and DRIVDATA structures */
        if ( NULL == (pchDelimiter = strchr(szDetails,';')) )
            return DEV_ERROR;
        dop.pszDriverName = pchDelimiter + 1;
        if ( NULL == (pchDelimiter = strchr(dop.pszDriverName,';')) )
            return DEV_ERROR;
        dop.pszLogAddress = pchDelimiter + 1;
        *(dop.pszLogAddress + strcspn(dop.pszLogAddress,",;")) = '\0';
        *(dop.pszDriverName + strcspn(dop.pszDriverName,",;")) = '\0';
        dop.pszComment = pszAppName;
        if ( NULL != (pchDelimiter = strchr(dop.pszDriverName,'.')) )
            {
            driv.cb = sizeof(DRIVDATA) - 1;
            driv.lVersion = 0L;
            *pchDelimiter = '\0';
            strncpy( driv.szDeviceName,pchDelimiter+1,
                     sizeof driv.szDeviceName );
            dop.pdriv = &driv;
            }
        else
            dop.pdriv = NULL;
        dop.pszDataType = "PM_Q_RAW";

    /* Reset logical address if output is to be redirected */
        if ( pszRedirect != NULL ) dop.pszLogAddress = pszRedirect;

    /* Now open the device context an return to caller */
        return DevOpenDC( hab,
                          (pszRedirect == NULL) ? OD_QUEUED : OD_DIRECT,
                          "*",
                          5L,         // use first five fields.
                          (PDEVOPENDATA) &dop,
                          (HDC) NULL );
    }
/****************************************************************************/
