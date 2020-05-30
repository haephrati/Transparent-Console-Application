#include <cstdio>
#include <cstdlib>
#include "resource.h"

static void Fail(const char* msg)
{
    std::printf("FAIL %s\n", msg);
    std::exit(1);
}

int main()
{
    if (IDD_ABOUTBOX != 100)
        Fail("about");
    if (IDD_TCONSOLE_FORM != 101)
        Fail("form");
    if (IDD_TRANS_DLG != 130)
        Fail("trans");
    if (IDD_COLOR_DLG != 131)
        Fail("color");
    if (IDC_SLIDER1 != 1003)
        Fail("slider");
    if (ID_VIEW_OPTIONS != 32772)
        Fail("options");
    std::printf("OK TConsoleTests\n");
    return 0;
}
