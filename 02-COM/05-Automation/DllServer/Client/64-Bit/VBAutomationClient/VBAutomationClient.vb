' for 'Form'
Imports System.Windows.Forms

' .Net callable dll created using tlbimp
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomation
    Inherits Form
    Public Sub New()
        Dim MyIDispatch As Object
        Dim MyRef As New CMyMathClass
        MyIDispatch = MyRef

        Dim iNum1 = 175
        Dim iNum2 = 125

        Dim iSum = MyIDispatch.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum Of {0} and {1} is {2}", iNum1, iNum2, iSum)
        MsgBox(str)

        Dim iSub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Sub Of {0} and {1} is {2}", iNum1, iNum2, iSub)
        MsgBox(str)

        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomation())
    End Sub

End Class
