; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyf553View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myf553.h"
LastPage=0

ClassCount=6
Class1=CMyf553App
Class2=CMyf553Doc
Class3=CMyf553View
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CDlgHistogram
Resource3=IDD_HISTOGRAM

[CLS:CMyf553App]
Type=0
HeaderFile=myf553.h
ImplementationFile=myf553.cpp
Filter=N

[CLS:CMyf553Doc]
Type=0
HeaderFile=myf553Doc.h
ImplementationFile=myf553Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_RELOAD

[CLS:CMyf553View]
Type=0
HeaderFile=myf553View.h
ImplementationFile=myf553View.cpp
Filter=C
LastObject=ID_GRADIENT_SHARPEN
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=myf553.cpp
ImplementationFile=myf553.cpp
Filter=D

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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_RELOAD
Command5=ID_GRAY
Command6=ID_HISTOGRAM
Command7=ID_HISTOGRAM_SUPER
Command8=ID_LINEARTRANS
Command9=ID_EQUALIZE
Command10=ID_FOURIER
Command11=ID_INVERT_FOURIER
Command12=ID_FAST_FOURIER
Command13=ID_INVERT_FAST_FOURIER
Command14=ID_AVERAGE_FILTER
Command15=ID_MEDIAN_FILTER
Command16=ID_GRADIENT_SHARPEN
Command17=ID_LAPLACE_SHARP
CommandCount=17

[DLG:IDD_HISTOGRAM]
Type=1
Class=CDlgHistogram
ControlCount=0

[CLS:CDlgHistogram]
Type=0
HeaderFile=DlgHistogram.h
ImplementationFile=DlgHistogram.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgHistogram
VirtualFilter=dWC

