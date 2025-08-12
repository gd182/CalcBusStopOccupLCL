
#include "libs/liblcl/liblcl.h"

#include "MainForm.h"

int main()
{
#ifdef _WIN32
    system("chcp 65001");
#endif
#ifdef _WIN32
    if (!load_liblcl("liblcl.dll")) {
        MessageBoxA(NULL, "Failed to load liblcl.dll", "Error", MB_ICONERROR);
        return 1;
    }
#endif
#ifdef __linux__
    if (load_liblcl("liblcl.so")) {
        MessageBoxA(NULL, "Failed to load liblcl.dll", "Error", MB_ICONERROR);
        return 1;
    }
#endif
#ifdef __APPLE__
    if (load_liblcl("liblcl.dylib")) {
        MessageBoxA(NULL, "Failed to load liblcl.dll", "Error", MB_ICONERROR);
        return 1;
    }
#endif
    Application_SetMainFormOnTaskBar(Application, TRUE);
    Application_SetTitle(Application, "Расчет продолжительности занятости транспортом остановки");
    Application_Initialize(Application);

    MainForm mainForm;
    mainForm.createForm();

    Application_Run(Application);

    close_liblcl();

    return 1;
}