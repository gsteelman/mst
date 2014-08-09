VERSION 5.00
Begin VB.Form frmRequestLeave 
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
   Begin VB.CommandButton cmdEnterRequest 
      Caption         =   "&Enter Request"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3240
      TabIndex        =   6
      Top             =   4440
      Width           =   2655
   End
   Begin VB.TextBox txtEndDate 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      Left            =   3720
      TabIndex        =   5
      Top             =   3720
      Width           =   1815
   End
   Begin VB.TextBox txtStartDate 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      Left            =   3720
      TabIndex        =   4
      Top             =   2640
      Width           =   1695
   End
   Begin VB.ComboBox cmbLeaveType 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   555
      ItemData        =   "frmRequestLeave.frx":0000
      Left            =   3480
      List            =   "frmRequestLeave.frx":000A
      TabIndex        =   1
      Top             =   1440
      Width           =   2175
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "End Date"
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
      Left            =   3840
      TabIndex        =   3
      Top             =   3240
      Width           =   1485
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Start Date"
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
      Left            =   3720
      TabIndex        =   2
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label lblLeaveType 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Leave Type"
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
      Left            =   3600
      TabIndex        =   0
      Top             =   840
      Width           =   1890
   End
End
Attribute VB_Name = "frmRequestLeave"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


  ' COMMAND LINE OPTIONS
  ' --h:  help
  ' --l:  login           <SSO> <password>
  ' --r:  request         <start> <end> <"sick"/"vacation">
  ' --var: view all reqs  <SSO/"all">
  ' --vpr: view pending   <SSO/"all">
  ' --vap: view approved  <SSO/"all">
  ' --vdr: view denied    <SSO/"all">
  ' --gl: grant leave     <SSO/"all"> <"sick"/"vacation"> <num days>
  ' --ar: approve request <SSO> <y/n>
  
  
Private Sub cmdEnterRequest_Click()
    
    'Get the parameters together
    
    Dim params As String
    
    params = "--l " + currentUser.username + " " + currentUser.password
    params = params + " --r " + txtStartDate.Text + " " + txtEndDate.Text + " " + cmbLeaveType.List(cmbLeaveType.ListIndex)
    
    Debug.Print params
    
    runProgram params
    
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

Private Sub txtStartDate_GotFocus()

    txtStartDate.SelStart = 0
    txtStartDate.SelLength = Len(txtStartDate)
    
End Sub

Private Sub txtEndDate_GotFocus()

    txtStartDate.SelStart = 0
    txtStartDate.SelLength = Len(txtStartDate)
    
End Sub
