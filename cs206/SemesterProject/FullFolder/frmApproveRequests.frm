VERSION 5.00
Begin VB.Form frmApproveRequests 
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
   Begin VB.CheckBox chkApprove 
      BackColor       =   &H8000000D&
      Caption         =   "Approve"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000F&
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   840
      Width           =   2295
   End
   Begin VB.TextBox txtUsername 
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   525
      Left            =   1800
      TabIndex        =   1
      Top             =   120
      Width           =   1935
   End
   Begin VB.CommandButton cmdGo 
      Caption         =   "Submit"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   120
      TabIndex        =   0
      Top             =   1320
      Width           =   1695
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Username:"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   405
      Left            =   120
      TabIndex        =   2
      Top             =   240
      Width           =   1530
   End
End
Attribute VB_Name = "frmApproveRequests"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdGo_Click()

    Dim params As String
    
    'Set up the parameter and send it away if there us a username
    
    If txtUsername.Text <> "" Then
    
        params = "--l " + currentUser.username + " " + currentUser.password + _
                 " --ar " + txtUsername.Text + " " + chkApprove.Value
                 
        runProgram params
        
        'We have no idea if it was or not, let's just hope it works every time
        
        MsgBox "Input successful.", vbOKOnly, "Vacation System"
                 
    Else
    
        MsgBox "Please enter a username.", vbOKOnly, "Vacation System"
        
    End If
    
End Sub

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
    chkApprove.BackColor = RGB(18, 149, 241)
    
End Sub
