VERSION 5.00
Begin VB.Form frmLogin 
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
   Begin VB.CommandButton cmdSubmit 
      Caption         =   "&Submit"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   435
      Left            =   4560
      TabIndex        =   4
      Top             =   1500
      Width           =   1815
   End
   Begin VB.TextBox txtPassword 
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
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   1
      Text            =   "12345"
      Top             =   1410
      Width           =   2415
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
      Left            =   2040
      TabIndex        =   0
      Text            =   "user1"
      Top             =   780
      Width           =   2415
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Password:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   435
      Left            =   240
      TabIndex        =   3
      Top             =   1500
      Width           =   1695
   End
   Begin VB.Label lblUsername 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Username:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H8000000E&
      Height          =   435
      Left            =   120
      TabIndex        =   2
      Top             =   870
      Width           =   1755
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdSubmit_Click()

    'Since there is no SSO and this is a mockup, assume the input is legitimate
    
    checkLogin
    
    updateUser
    
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
    
End Sub

Private Sub checkLogin()

    'To show off some functionality
    
    If txtUsername.Text = general.username And _
       txtPassword.Text = general.password Then
       
        userStatus = 0
        
        MsgBox "Verified as user.", vbOKOnly, "Vacation System"
        
    ElseIf txtUsername.Text = manager.username And _
           txtPassword.Text = manager.password Then
           
        userStatus = 1
        
        MsgBox "Verified as manager.", vbOKOnly, "Vacation System"
        
    ElseIf txtUsername.Text = HR.username And _
           txtPassword.Text = HR.password Then
           
        userStatus = 2
        
        MsgBox "Verified as HR.", vbOKOnly, "Vacation System"
        
    End If
    
End Sub

Private Sub txtUsername_GotFocus()

    txtUsername.SelStart = 0
    txtUsername.SelLength = Len(txtUsername.Text)
    
End Sub

Private Sub txtPassword_GotFocus()

    txtUsername.SelStart = 0
    txtUsername.SelLength = Len(txtPassword.Text)
    
End Sub
