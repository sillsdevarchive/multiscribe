!include "MUI.nsh"
!include WordFunc.nsh

!insertmacro VersionCompare

!define VERSION "0.3"
!define WINDOWS_VERSION "1.${VERSION}.0"

Name "MultiScribe Installer"
Outfile "multiscribe_${VERSION}.exe"
RequestExecutionLevel user
SetCompressor lzma

InstallDir ""
InstType /NOCUSTOM
InstType /COMPONENTSONLYONCUSTOM
InstType "Insert"
InstType "Remove"

!insertmacro MUI_PAGE_LICENSE "..\License_LGPLv21.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

!define MUI_DIRECTORYPAGE_TEXT_TOP "Please navigate to the directory containing the .exe you want to use Multiscribe"

VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Multiscribe"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${VERSION}"
VIProductVersion "${WINDOWS_VERSION}"

Section "-Install"
	SectionIn 1
	SetOutPath "$INSTDIR"

	IfFileExists "$INSTDIR\_usp10.dll" 0 BranchInstall
	IfFileExists "$INSTDIR\usp10.dll" 0 BranchInstall
	GetDllVersion "$INSTDIR\usp10.dll" $R0 $R1
	IntOp $R2 $R0 / 0x00010000
	IntOp $R3 $R0 & 0x0000FFFF
	IntOp $R4 $R1 / 0x00010000
	IntOp $R5 $R1 & 0x0000FFFF
	StrCpy $0 "$R2.$R3.$R4.$R5"
	${VersionCompare} $0 ${WINDOWS_VERSION} $R0
	IntCmp $R0 1 BranchQuery BranchQuery BranchUnInstall

BranchQuery:
	MessageBox MB_YESNO|MB_ICONQUESTION "Do you really want to install an older version of multiscribe over a newer one?" /SD IDNO IDYES BranchUnInstall
	Abort "Installation of Multiscribe aborting"

BranchUnInstall:
	Delete "$INSTDIR\_usp10.dll"

BranchInstall:
	IfFileExists "$INSTDIR\usp10.dll" 0 +3
		Rename usp10.dll _usp10.dll
		goto BranchInstMS
	IfFileExists "$SYSDIR\usp10.dll" +2 0
		Abort "Can't find a Uniscribe .dll (usp10.dll) to copy, aborting. Try copying one into the target directory $INSTDIR and rerunning the installer"
		CopyFiles "$SYSDIR\usp10.dll" "$INSTDIR\_usp10.dll"
BranchInstMS:
	File "usp10.dll"

SectionEnd

Section "-Remove"
	SectionIn 2
	SetOutPath "$INSTDIR"

	IfFileExists "$INSTDIR\_usp10.dll" 0 +2
		Abort "No moved Uniscribe dll found in directory $INSTDIR"
	IfFileExists "$INSTDIR\usp10.dll" 0 +2
		Abort "No Multiscribe dll found in director $INSTDIR"

	Delete "usp10.dll"
	Rename "_usp10.dll" "usp10.dll"
SectionEnd
