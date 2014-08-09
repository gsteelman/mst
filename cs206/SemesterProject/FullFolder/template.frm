VERSION 5.00
Begin VB.Form frmTemplate 
   BackColor       =   &H8000000D&
   BorderStyle     =   0  'None
   Caption         =   "Form1"
   ClientHeight    =   6615
   ClientLeft      =   6540
   ClientTop       =   5190
   ClientWidth     =   9135
   LinkTopic       =   "Form1"
   ScaleHeight     =   6615
   ScaleWidth      =   9135
   ShowInTaskbar   =   0   'False
End
Attribute VB_Name = "frmTemplate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Deactivate()
    
    'To keep the form on top, set focus again
    
    Me.SetFocus
    
End Sub

Private Sub Form_Load()

    'Some positioning functions, rough due to time constraints
    
    Me.Left = frmMain.Left + 2280
    Me.Top = frmMain.Top + 2040
    
    'To match the color with the main color in the graphics
    
    Me.BackColor = RGB(18, 149, 241)
    
End Sub
