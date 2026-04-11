#ifndef __APPRESOLVER_HPP__
#define __APPRESOLVER_HPP__

#include "phbasesup.hpp"

#include <winnt.h>
#include <Windows.h>

EXTERN_C_START

HRESULT phAppResolverGetAppIdForProcess(_In_ HANDLE processId,
    _Out_ PphString* applicationUserModelId);

HRESULT phAppResolverGetAppIdForWindow(_In_ HWND windowHandle,
    _Out_ PphString* applicationUserModelId);

HRESULT phAppResolverActivateAppId(_In_ PphString applicationUserModelId,
    _In_opt_ PCWSTR commandLine, _Out_opt_ HANDLE* processId);

HRESULT phAppResolverPackageTerminateProcess(_In_ PCWSTR packageFullName);

struct PhPackageTaskEntry {
    PphString taskName;
    GUID taskGuid;
};
using PphPackageTaskEntry = PhPackageTaskEntry*;

HRESULT phAppResolverEnumeratePackageBackgroundTasks(_In_ PCWSTR packageFullName,
    _Inout_ PphList backgroundTasks);

HRESULT phAppResolverPackageStopSessionRedirection(_In_ PCWSTR packageFullName);

PphString pgGetAppContainerName(_In_ PSID appContainerSid);

PphString phGetAppContainerSidFromName(_In_ PCWSTR appContainerName);

PphString phGetAppContainerPackageName(_In_ PSID sid);

BOOLEAN phIsPackageCapabilitySid(_In_ PSID appContainerSid, _In_ PSID sid);

PphString phGetPackagePath(_In_ PphString packageFullName);

PphList phGetPackageAssetsFromResourceFile(_In_ PCWSTR filePath);

struct PhAppUserModelIdEnumEntry {
    PphString appUserModelId;
    PphString packageName;
    PphString packageDisplayName;
    PphString packageFamilyName;
    PphString packageInstallPath;
    PphString packageFullName;
    PphString packageVersion;
    PphString smallLogoPath;
};
using PphAppUserModelIdEnumEntry = PhAppUserModelIdEnumEntry*;

PphList phEnumApplicationUserModelIds(VOID);



EXTERN_C_END

#endif
