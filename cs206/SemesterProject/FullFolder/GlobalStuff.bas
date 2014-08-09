Attribute VB_Name = "Module1"
Option Explicit

'If there are any global things they can go here

Global Const CMDSSTRING = "---" 'In-between commands sent
Global Const CONTSTRING = "***" 'In-between outputs of a command
Global Const TERMSTRING = "XXX" 'Signifies the end of the file

Public Type user

    username As String
    password As String
    
End Type

'0 = user, 1 = manager, 2 = HR
Global userStatus As Integer

Global general As user
Global manager As user
Global HR As user

Global currentUser As user

Public Sub init()

    userStatus = 0 'Assume general user for now
    
    'Set up these for show purposes
    
    general.username = "user1"
    general.password = "12345"
    
    manager.username = "manager1"
    manager.password = "12345"
    
    HR.username = "hr1"
    HR.password = "12345"
    
End Sub

Public Sub updateUser()
    
    With frmMain
    
    If userStatus = 0 Then
    
        currentUser = general
    
        .imgSide.Picture = .imgUserBar.Picture
        
        'Now enable some buttons
        
        .imgViewPending.Enabled = False
        .imgApproveRequest.Enabled = False
        .imgLogin.Enabled = True
        .imgModifyRules.Enabled = False
        .imgRequestLeave.Enabled = True
        .imgViewHistory.Enabled = True
        
    ElseIf userStatus = 1 Then
    
        currentUser = manager
    
        .imgSide.Picture = .imgManagerBar.Picture
        
        .imgViewPending.Enabled = True
        .imgApproveRequest.Enabled = True
        .imgLogin.Enabled = True
        .imgModifyRules.Enabled = False
        .imgRequestLeave.Enabled = True
        .imgViewHistory.Enabled = True
        
    ElseIf userStatus = 2 Then
    
        currentUser = HR
        
        .imgSide.Picture = .imgHRBar.Picture
        
        .imgViewPending.Enabled = True
        .imgApproveRequest.Enabled = True
        .imgLogin.Enabled = True
        .imgModifyRules.Enabled = True
        .imgRequestLeave.Enabled = True
        .imgViewHistory.Enabled = True
        
    End If
    
    End With
    
End Sub

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

Public Sub runProgram(params As String)

    Shell App.Path + "\runtime.exe " + params
    
End Sub


