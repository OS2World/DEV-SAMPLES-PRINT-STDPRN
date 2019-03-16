/****************************************************************************
 * STDPRN.H - Standard printer functions header file                        *
 *                                                                          *
 *  This file contains the function prototypes for the functions in the     *
 *  standard printer function DLL (stdprn.dll).                             *
 *                                                                          *
 *  Note that stdprn.dll was created as a single thread DLL, thus the       *
 *  calling process must ensure that multiple threads are not attempting    *
 *  to call the same function at the same time.                             *
 *                                                                          *
 *  Modifications -                                                         *
 *      19-Jul-1989 : Initial version                                       *
 ****************************************************************************/

#pragma comment(lib,"stdprn.lib")

extern HDC APIENTRY OpenDefaultPrinterDC( HAB hab,
                                          PSZ pszAppName,
                                          PSZ pszRedirect );
    /* Purpose          This function opens a device context for the
     *                  current default printer. Use the DevCloseDC
     *                  function to close this device context when
     *                  you are finished with it.
     *
     * Parameters       hab contains the anchor block handle.
     *
     *                  pszAppName is a pointer to a null-terminated
     *                  string that contains the application name.
     *
     *                  pszRedirect is a pointer to a null-terminated
     *                  string that contains the name of the file to
     *                  which printer output is to be redirected. This
     *                  parameter is set to NULL if no output redirection
     *                  is to take place.
     *
     * Return Value     This function returns a handle to the opened
     *                  printer device context. The return value is
     *                  DEV_ERROR if the function is unsuccessful.
     */

extern LONG APIENTRY StartDocument( HDC hdcPrinter,PSZ pszDocName );
    /* Purpose          This function allows the application to signal
     *                  that a new print job is starting.
     *
     * Parameters       hdcPrinter contains a handle to a previously
     *                  opened printer device context.
     *
     *                  pszDocName points to a null-terminated ASCII
     *                  containing the name of the document.
     *
     * Return Value     This function returns DEV_OK if no error occurred,
     *                  otherwise it returns a value of DEVESC_ERROR or
     *                  or DEVESC_NOTIMPLEMENTED.
     *
     * Notes            Do not use the start/end document functions if
     *                  printer output has been redirected to a file.
     */

extern LONG APIENTRY EndDocument( HDC hdcPrinter );
    /* Purpose          This function ends a print job started by the
     *                  StartDocument function.
     *
     * Parameters       hdcPrinter contains a handle to a previously
     *                  opened printer device context.
     *
     * Return Value     This function returns DEV_OK if no error occurred,
     *                  otherwise it returns a value of DEVESC_ERROR or
     *                  or DEVESC_NOTIMPLEMENTED.
     */
