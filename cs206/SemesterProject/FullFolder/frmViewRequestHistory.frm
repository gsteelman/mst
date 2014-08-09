VERSION 5.00
Begin VB.Form frmViewRequestHistory 
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
   Begin VB.TextBox txtHistory 
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   6375
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   120
      Width           =   8895
   End
End
Attribute VB_Name = "frmViewRequestHistory"
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
    
    'Since this has one function, it can easily be loaded
    
    prepWindows
    
    
End Sub

Private Sub prepWindows()

    Dim params As String
    Dim line As String
        
    txtHistory.Text = ""
    
    params = "--l " + currentUser.username + " " + currentUser.password + " --var " + currentUser.username
    
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
    
        txtHistory.Text = txtHistory.Text + "No pending requests." + vbCrLf + vbCrLf
    
        Input #1, line '***
        Input #1, line 'APPROVED REQUESTS
        
    Else
        
        txtHistory.Text = txtHistory.Text + "----------------" + vbCrLf + _
                                            "Pending Requests" + vbCrLf + _
                                            "----------------" + vbCrLf + vbCrLf
    
        'Keep reading and putting information out until there are no more
        
        Do While line <> "APPROVED REQUESTS"
        
            txtHistory.Text = txtHistory.Text + "Pending Request: " + vbCrLf + "-----" + vbCrLf
            
            'Since the input to get into this grabs it, no need to grab twice
            
            If line <> "vacation" And line <> "sick" Then
                
                Input #1, line 'This is the reason
            
            End If
            
            txtHistory.Text = txtHistory.Text + "Reason for leave: " + line + vbCrLf
            
            Input #1, line 'This is the start of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave start: " + line + vbCrLf
            
            Input #1, line 'This is the end of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave end: " + line + vbCrLf
            
            Input #1, line 'This is the date entered
            
            txtHistory.Text = txtHistory.Text + "Date entered: " + line + vbCrLf
            
            Input #1, line 'Pass/fail
            
            txtHistory.Text = txtHistory.Text + "Status: " + line + vbCrLf + vbCrLf
            
            Input #1, line
            Input #1, line 'To feed for the loop check
            
        Loop
        
    End If
    
    'Now we're at approved requests

    Input #1, line '***
    Input #1, line 'username
    
    Input #1, line
    
    If line = "NONE" Then
    
        txtHistory.Text = txtHistory.Text + "No approved requests." + vbCrLf + vbCrLf
    
        Input #1, line '***
        Input #1, line 'DENIED REQUESTS
        
    Else
    
        txtHistory.Text = txtHistory.Text + "-----------------" + vbCrLf + _
                                            "Approved Requests" + vbCrLf + _
                                            "-----------------" + vbCrLf + vbCrLf
                                            
        Do While line <> "DENIED REQUESTS"
            
            txtHistory.Text = txtHistory.Text + "Approved Request: " + vbCrLf + "-----" + vbCrLf
            
            'Since the input to get into this grabs it, no need to grab twice
            
            If line <> "vacation" And line <> "sick" Then
                
                Input #1, line 'This is the reason
            
            End If
            
            txtHistory.Text = txtHistory.Text + "Reason for leave: " + line + vbCrLf
            
            Input #1, line 'This is the start of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave start: " + line + vbCrLf
            
            Input #1, line 'This is the end of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave end: " + line + vbCrLf
            
            Input #1, line 'This is the date entered
            
            txtHistory.Text = txtHistory.Text + "Date entered: " + line + vbCrLf
            
            Input #1, line 'For the date approved
            
            txtHistory.Text = txtHistory.Text + "Date approved: " + line + vbCrLf + vbCrLf
            
            Input #1, line
            Input #1, line 'To feed for the loop check
            
        Loop
        
    End If
    
    'Now we're at denied requests

    Input #1, line '***
    Input #1, line 'username
    
    Input #1, line
    
    If line = "NONE" Then
    
        txtHistory.Text = txtHistory.Text + "No denied requests." + vbCrLf + vbCrLf
        
    Else
        
        txtHistory.Text = txtHistory.Text + "---------------" + vbCrLf + _
                                            "Denied Requests" + vbCrLf + _
                                            "---------------" + vbCrLf + vbCrLf
         
        Do While line <> CMDSSTRING
            
            txtHistory.Text = txtHistory.Text + "Denied Request: " + vbCrLf + "-----" + vbCrLf
            
            'Since the input to get into this grabs it, no need to grab twice
            
            If line <> "vacation" And line <> "sick" Then
                
                Input #1, line 'This is the reason
            
            End If
            
            txtHistory.Text = txtHistory.Text + "Reason for leave: " + line + vbCrLf
            
            Input #1, line 'This is the start of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave start: " + line + vbCrLf
            
            Input #1, line 'This is the end of the leave
            
            txtHistory.Text = txtHistory.Text + "Leave end: " + line + vbCrLf
            
            Input #1, line 'This is the date entered
            
            txtHistory.Text = txtHistory.Text + "Date entered: " + line + vbCrLf
            
            Input #1, line 'For the date denied
            
            txtHistory.Text = txtHistory.Text + "Date denied: " + line + vbCrLf + vbCrLf
            
            Input #1, line 'To feed for the loop check
            
        Loop
    
    End If
    
    'Close the file now
    
    Close #1
    
End Sub
