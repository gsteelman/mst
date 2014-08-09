VERSION 5.00
Begin VB.Form frmViewPendingRequests 
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
   Begin VB.CommandButton cmdGo 
      Caption         =   "View"
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
      Left            =   4080
      TabIndex        =   3
      Top             =   240
      Width           =   1335
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
      Left            =   1920
      TabIndex        =   2
      Top             =   90
      Width           =   1935
   End
   Begin VB.TextBox txtPending 
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5775
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   720
      Width           =   8895
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
      Left            =   240
      TabIndex        =   1
      Top             =   210
      Width           =   1530
   End
End
Attribute VB_Name = "frmViewPendingRequests"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdGo_Click()

    'Since this can't run without a username
    
    If txtUsername.Text <> "" Then
    
        prepWindows
    
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
    
End Sub

Private Sub prepWindows()

    Dim params As String
    Dim line As String
    
    txtPending.Text = ""
    
    params = "--l " + currentUser.username + " " + currentUser.password + " --vpr " + txtUsername.Text
    
    runProgram params
    
    MsgBox "Ready.", vbOKOnly, "Vacation System" 'To make it work
    
    'Now open the file and begin parsing
    
    Open App.Path & "\output.txt" For Input As #1
        
    'First get to the history
    
    Do While line <> "PENDING REQUESTS"
    
        Input #1, line
        
    Loop
    
    Input #1, line '***
    Input #1, line 'username
    
    Input #1, line
    
    If line = "NONE" Then
    
        txtPending.Text = txtPending.Text + "No pending requests." + vbCrLf + vbCrLf
    
        Input #1, line '***
        Input #1, line 'APPROVED REQUESTS
        
    Else
        
        txtPending.Text = txtPending.Text + "----------------" + vbCrLf + _
                                            "Pending Requests" + vbCrLf + _
                                            "----------------" + vbCrLf + vbCrLf
    
        'Keep reading and putting information out until there are no more
        
        Do While line <> "---"
        
            txtPending.Text = txtPending.Text + "Pending Request: " + vbCrLf + "-----" + vbCrLf
            
            'Since the input to get into this grabs it, no need to grab twice
            
            If line <> "vacation" And line <> "sick" Then
                
                Input #1, line 'This is the reason
            
            End If
            
            txtPending.Text = txtPending.Text + "Reason for leave: " + line + vbCrLf
            
            Input #1, line 'This is the start of the leave
            
            txtPending.Text = txtPending.Text + "Leave start: " + line + vbCrLf
            
            Input #1, line 'This is the end of the leave
            
            txtPending.Text = txtPending.Text + "Leave end: " + line + vbCrLf
            
            Input #1, line 'This is the date entered
            
            txtPending.Text = txtPending.Text + "Date entered: " + line + vbCrLf
            
            Input #1, line 'Pass/fail
            
            txtPending.Text = txtPending.Text + "Status: " + line + vbCrLf + vbCrLf
            
            Input #1, line
            Input #1, line 'To feed for the loop check
            
        Loop
        
    End If
    
    'Close the file now
    
    Close #1
    
End Sub

Private Sub txtUsername_GotFocus()

    txtUsername.SelStart = 0
    txtUsername.SelLength = Len(txtUsername.Text)
    
End Sub
