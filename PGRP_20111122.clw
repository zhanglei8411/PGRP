; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMapDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PGRP_20111122.h"
LastPage=0

ClassCount=10
Class1=CPGRP_20111122App
Class2=CPGRP_20111122Doc
Class3=CPGRP_20111122View
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_DIALOG2
Resource2=IDD_DIALOG3
Resource3=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Class7=CInitParaDlg
Resource4=IDD_ABOUTBOX
Class8=CResultInfoDlg
Resource5=IDR_TOOLBAR1
Class9=CModeSelectionDlg
Resource6=IDD_DIALOG1
Resource7=IDR_PGRP_2TYPE
Class10=CMapDlg
Resource8=IDD_DIALOG4

[CLS:CPGRP_20111122App]
Type=0
HeaderFile=PGRP_20111122.h
ImplementationFile=PGRP_20111122.cpp
Filter=N

[CLS:CPGRP_20111122Doc]
Type=0
HeaderFile=PGRP_20111122Doc.h
ImplementationFile=PGRP_20111122Doc.cpp
Filter=N
LastObject=CPGRP_20111122Doc

[CLS:CPGRP_20111122View]
Type=0
HeaderFile=PGRP_20111122View.h
ImplementationFile=PGRP_20111122View.cpp
Filter=C
LastObject=ID_PGRP_Calculation_Flag
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=IDC_BUTTON1


[CLS:CAboutDlg]
Type=0
HeaderFile=PGRP_20111122.cpp
ImplementationFile=PGRP_20111122.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_PGRP_2TYPE]
Type=1
Class=CPGRP_20111122View
Command1=IDC_PGRP_Run
Command2=IDC_PGRP_Init
Command3=ID_PGRP_Save
Command4=ID_Menu_Show_Result
Command5=ID_Map_Save
Command6=ID_Map_Custom
Command7=ID_PGRP_Calculation_Flag
Command8=ID_FILE_NEW
Command9=ID_FILE_OPEN
Command10=ID_FILE_CLOSE
Command11=ID_FILE_SAVE
Command12=ID_FILE_SAVE_AS
Command13=ID_FILE_PRINT
Command14=ID_FILE_PRINT_PREVIEW
Command15=ID_FILE_PRINT_SETUP
Command16=ID_FILE_MRU_FILE1
Command17=ID_APP_EXIT
Command18=ID_EDIT_UNDO
Command19=ID_EDIT_CUT
Command20=ID_EDIT_COPY
Command21=ID_EDIT_PASTE
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=IDC_PGRP_Run
Command6=ID_PGRP_Save
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_Menu_Show_Result
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_DIALOG1]
Type=1
Class=CInitParaDlg
ControlCount=30
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BUTTON_Read_Init,button,1342242816
Control12=IDC_BUTTON_Save_Init,button,1342242816
Control13=IDC_EDIT5,edit,1350631552
Control14=IDC_EDIT6,edit,1350631552
Control15=IDC_EDIT7,edit,1350631552
Control16=IDC_EDIT8,edit,1350631552
Control17=IDC_EDIT9,edit,1350631552
Control18=IDC_EDIT10,edit,1350631552
Control19=IDC_EDIT11,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_BUTTON_LoadMap,button,1342242816
Control29=IDC_STATIC_Mapname,static,1342308352
Control30=IDC_BUTTON_Defult,button,1342242817

[CLS:CInitParaDlg]
Type=0
HeaderFile=InitParaDlg.h
ImplementationFile=InitParaDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_STATIC_Mapname
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CResultInfoDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_MapName,edit,1350633600
Control9=IDC_EDIT_StartX,edit,1350633600
Control10=IDC_EDIT_StartY,edit,1350633600
Control11=IDC_EDIT_TargetX,edit,1350633600
Control12=IDC_EDIT_TargetY,edit,1350633600
Control13=IDC_EDIT_PathLength,edit,1350633600
Control14=IDC_EDIT_Iteration_Times,edit,1350633600

[CLS:CResultInfoDlg]
Type=0
HeaderFile=ResultInfoDlg.h
ImplementationFile=ResultInfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CResultInfoDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=CModeSelectionDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_Calculatie_Each,button,1342177289
Control4=IDC_RADIO_Donot_Cal,button,1342177289

[CLS:CModeSelectionDlg]
Type=0
HeaderFile=ModeSelectionDlg.h
ImplementationFile=ModeSelectionDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CModeSelectionDlg

[TB:IDR_TOOLBAR1]
Type=1
Class=CMainFrame
Command1=ID_MAP_NEW
CommandCount=1

[DLG:IDD_DIALOG4]
Type=1
Class=CMapDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_Map_Name,edit,1350631552
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_Circle_Center_X,edit,1350762624
Control8=IDC_EDIT_Circle_Radius,edit,1350631552
Control9=IDC_MapEdit_Circle,button,1342242816
Control10=IDC_STATIC,button,1342308359
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_Rect_LUX,edit,1350762624
Control13=IDC_EDIT_Rect_LUY,edit,1350762624
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_Rect_RDX,edit,1350762624
Control16=IDC_EDIT_Rect_RDY,edit,1350762624
Control17=IDC_MapEdit_Rec,button,1342242816
Control18=ID_Map_Save,button,1342242816
Control19=IDC_EDIT_Circle_Center_Y,edit,1350762624
Control20=IDC_BUTTON_LoadMap,button,1342242816

[CLS:CMapDlg]
Type=0
HeaderFile=MapDlg.h
ImplementationFile=MapDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMapDlg
VirtualFilter=dWC

