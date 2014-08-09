VERSION 5.00
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   5  'Sizable ToolWindow
   Caption         =   "Maelstrom Vacation Management System"
   ClientHeight    =   8655
   ClientLeft      =   60
   ClientTop       =   330
   ClientWidth     =   11415
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8655
   ScaleWidth      =   11415
   StartUpPosition =   2  'CenterScreen
   Begin VB.Image imgModifyRules 
      Height          =   615
      Left            =   240
      Top             =   7080
      Width           =   1575
   End
   Begin VB.Image imgApproveRequest 
      Height          =   615
      Left            =   240
      Top             =   6240
      Width           =   1575
   End
   Begin VB.Image imgViewPending 
      Height          =   615
      Left            =   240
      Top             =   5520
      Width           =   1575
   End
   Begin VB.Image imgViewHistory 
      Height          =   615
      Left            =   240
      Top             =   4680
      Width           =   1575
   End
   Begin VB.Image imgRequestLeave 
      Height          =   615
      Left            =   240
      Top             =   3840
      Width           =   1575
   End
   Begin VB.Image imgUserBar 
      Height          =   375
      Left            =   2400
      Picture         =   "frmMain.frx":0000
      Stretch         =   -1  'True
      Top             =   8160
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.Image imgHRBar 
      Height          =   375
      Left            =   3600
      Picture         =   "frmMain.frx":FCFB
      Stretch         =   -1  'True
      Top             =   8160
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.Image imgManagerBar 
      Height          =   375
      Left            =   3000
      Picture         =   "frmMain.frx":23261
      Stretch         =   -1  'True
      Top             =   8160
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.Image imgLogin 
      Height          =   375
      Left            =   240
      Top             =   3240
      Width           =   1215
   End
   Begin VB.Image imgTop 
      Height          =   2040
      Left            =   0
      Picture         =   "frmMain.frx":35868
      Top             =   0
      Width           =   11400
   End
   Begin VB.Image imgSide 
      Height          =   6540
      Left            =   0
      Picture         =   "frmMain.frx":4BDE6
      Top             =   2040
      Width           =   2280
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()

    'To match the color with the main color in the graphics
    
    Me.BackColor = RGB(18, 149, 241)
    
    'Init some values
    
    init
    
End Sub

Private Sub Form_Unload(Cancel As Integer)

    Unload frmViewPendingRequests
    Unload frmLogin
    Unload frmModifyRules
    Unload frmRequestLeave
    Unload frmViewRequestHistory
    Unload frmApproveRequests
    Unload Me

End Sub

Private Sub imgViewPending_Click()

    frmViewPendingRequests.Show
    
    'Now unload the rest
    
    Unload frmApproveRequests
    Unload frmLogin
    Unload frmModifyRules
    Unload frmRequestLeave
    Unload frmViewRequestHistory
    
End Sub

Private Sub imgApproveRequest_Click()

    frmApproveRequests.Show
        
    'Now unload the rest
    
    Unload frmViewPendingRequests
    Unload frmLogin
    Unload frmModifyRules
    Unload frmRequestLeave
    Unload frmViewRequestHistory
    
End Sub

Private Sub imgLogin_Click()

    frmLogin.Show
        
    'Now unload the rest
    
    Unload frmViewPendingRequests
    Unload frmApproveRequests
    Unload frmModifyRules
    Unload frmRequestLeave
    Unload frmViewRequestHistory
    
End Sub

Private Sub imgModifyRules_Click()

    MsgBox "Not available in mockup. (v3.6.4.1)", vbCritical, "Vacation System"
    
End Sub

Private Sub imgRequestLeave_Click()

    frmRequestLeave.Show
        
    'Now unload the rest
    
    Unload frmViewPendingRequests
    Unload frmApproveRequests
    Unload frmLogin
    Unload frmModifyRules
    Unload frmViewRequestHistory
    
End Sub

Private Sub imgViewHistory_Click()

    frmViewRequestHistory.Show
        
    'Now unload the rest
    
    Unload frmViewPendingRequests
    Unload frmApproveRequests
    Unload frmLogin
    Unload frmModifyRules
    Unload frmRequestLeave
    
End Sub

