$regfile = "m2560def.dat"  :$crystal = 16000000 :
$hwstack = 300:
$swstack =300 :
$framesize =300 :
$baud  = 115200 :Config Submode = New
const poitot=50 '/keep under 99 for display issues
$include "megatwinConfigsDims.inc"
$include "gpsfunctions.inc"
$lib "i2c_twi.lbx"
$lib "glcdSSD1306-I2C_V2x2.lib"

I2cinit :Dim _contrast As Byte, I2c_addr As Byte
Config Scl = Portd.0:Config Sda = Portd.1 :Config Twi = 400000
Config Graphlcd = Custom , Cols = 128 , Rows = 64 , Lcdname = "SSD1306"
i2c_addr = &H78:cls:i2c_addr = &H7A :cls
'Const Ssd1306_rotate = 1
I2c_addr = &H78  '/ i2c screen select
encswitch alias ping.5
dim disttrav as single ' returns in klm
dim a as byte

'/encoder setup
dim encval as word
config int5=change:config int4=change:on Int5 enkoder:on int4 enkoder:porte.5=1:porte.4=1 :enable int5:enable int4
waitms 200

CONFIG SINGLE = SCIENTIFIC , DIGITS = 5


'const poitot=50 '/keep under 99 for display issues

'/ Load @ startup values from eram
dim POI_latt(poitot) as single, E_POI_latt(poitot) as eram single
dim POI_lon(poitot) as single, E_POI_lon(poitot) as eram single
dim k as byte
for k = 1 to poitot
   POI_Latt(k) = E_POI_LATT(k)
   POI_lon(k) =  E_POI_LON(k)
next k

''!!!!!!!!comment out after testing''''''''
'call ClearAllPoi()
 ''''''''''''''''''''''''''''''
encval=1

Main:

   dim S_MetricSpeed as string*5
   dim showspeed as single
   dim InMenuFlag as byte
   dim HoldCaseVal as byte  '/hold main menu index when we return

   do
      Call Getstring()
      dim flipbit as byte
      Toggle FlipBit
      Valid = Commapos(2, Gprmc)     'v=no fix    VALID FIX = a
      F1 = Commapos(3 , Gprmc)       'lat
      F2 = Commapos(4 , Gprmc)       'n/s
      F3 = Commapos(5 , Gprmc)       'lon
      F4 = Commapos(6 , Gprmc)       'e/w
      ST_Speed_in_knots = Commapos(7 ,Gprmc )
      F8 = Commapos(8 , Gprmc)       'TRACK ANGLE
      Latt = Convert(f1 , F2) : Lon = Convert(f3 , F4)
      S_MetricSpeed = speed(ST_Speed_in_knots)

      dim menuflag as word
      dim clearmenuheader as byte
      if menuflag <> encval then
      cls  '/ double cls because glitch on keypad transition  NFI
      cls  '/wipe screen between transitions
         clearmenuheader = 1
      end if

      dim OdoDist as string*13
      dim CurRead as single
      curread = odo()
      OdoDist= Fusing(curread ,"#.##")
      menuflag = encval

      if encval>56 then encval=57  '/ set these figures to total menu levels
      if encval<2 then encval=1



    '/ display

      select case encval
         case 1: call MetricSpeed()
         case 2: call degrees()
         case 3: call compass()
         case 4: call TripMeter()
         case 5: call Configuration()
         case 6: call keypad()
         case 7: call gpsinfo()
         case 8: call qwerty()
         case 9 to 57:const rstenc=8: call PointsOfInterest() 'change rstenc(reset encoder) to the case level before this case
         case 58: call gpsinfo()
      end select



   loop

enkoder:

   dim b as byte
   B = Encoder(pine.5 , Pine.4 , encleft , encright ,0)
return

encleft:
   if encval > 1 then decr encval     '''!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    1  any dramas make it 1 based
return

encright:
   if encval <1000 then incr encval
return
'/ menu subs


end
$include "font8x8.font"
$include "font16x16.FONT"
$include "24.font"
$include "28.font"
'$include "36.font"

