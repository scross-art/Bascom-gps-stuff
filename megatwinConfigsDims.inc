$nocompile
'Config Timer0 = Timer , Prescale = 1
'config clock= soft

CONFIG PORTA=INPUT  :PortA = &B11111111   'pullups
CONFIG portb=input  :Portb = &B11111111   'pullups
CONFIG PORTC=INPUT  :PortC = &B11111111   'pullups
CONFIG PORTD=INPUT  :PortD = &B11111111   'pullups
CONFIG PORTE=INPUT  :PortE = &B11111111   'pullups
CONFIG PORTf=INPUT  :Portf = &B11111111   'pullups
CONFIG PORTg=INPUT  :Portg = &B11111111   'pullups
CONFIG PORTK=INPUT  :PORTK = &B11111111   'pullups

Enable Interrupts
'---------------------------------------------------------------------------------------------
Config Com2 = 9600 , Synchrone = 0 , Parity = None , Stopbits = 1 , Databits = 8 , Clockpol = 0
Open "COM2:" For Binary As #2
Config Serialin1 = Buffered , Size = 200
'---------------------------------------------------------------------------------------------


Config Date = Dmy , Separator = /
Config Debounce = 300


'MAIN GLOBALS

'GLOBAL GPS ROUTINES
const homelatt = -33.333333
const homelon = 133.333333

 DIM FURLATT AS SINGLE
 DIM FURLON AS SINGLE
dim elapsed as Integer
Dim Help_str As String * 10
Dim Temp_str As String * 10
Dim Timez As String * 8
Dim Datez As String * 8
Dim Tmp3(2) As Integer
dim furthest as single  : FURTHEST = 0
DIM CURR AS SINGLE  :CURR = 0
'' GLOBAL VARIABLES GEOFENCE FUNCTIONS
dim index as byte
dim Eindex as eram byte
dim inorout as byte
dim fenceLatt(50) as Single
dim fenceLon(50) as Single
dim EfenceLatt(50) As Eram single
dim EfenceLon(50) as Eram Single

'non dec latt and lon strings
Dim F1 As String * 11
Dim F2 As String * 1
Dim F3 As String * 11
Dim F4 As String * 1

' OTHER GETSTRING CONVERSIONSTRINGS
Dim F5 As String * 10
Dim F6 As String * 10
Dim ST_Speed_in_knots As String * 11
Dim F8 As String * 8
Dim Sats As String * 2
Dim Valid As String * 1
Dim Latt As Single
Dim Lon As Single

DIM SLATT AS STRING*20
DIM SLON AS STRING*20
DIM SLATTSLON AS STRING *40

Dim Dist As single
Dim Head As String * 10
Dim Trip As String * 15
'Dim Alarm As Single
Dim N As Single

dim ttime as string*24

dim distpp as single
Dim Gpgga As String * 100
Dim Gprmc As String * 100
'Dim Lostsat As Long




'''TEMP FOR TESTING
  Dim Ttmp11 As String * 100
