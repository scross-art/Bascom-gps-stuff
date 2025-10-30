'''basic
$nocompile

sub MetricSpeed()

   SETFONT font16x16
   if clearmenuheader <10 then lcdat 1,1,"KPH" else lcdat 1,1,"   "
   incr clearmenuheader
   dim B_speedo as byte
   B_speedo=val(S_MetricSpeed) '/ cast to strip the fraction
   setfont Arial_38x42
   select case B_speedo
      case 0 to 9:    lcdat 3,10,"  ";B_speedo
      case 10 to 99:  lcdat 3,10," ";B_speedo
      case 100 to 255:lcdat 3,10,B_speedo
   end select
end sub


Sub gpsinfo()
   setfont font8x8
   lcdat 1,1,latt
   lcdat 2,1,lon


end sub

Sub degrees()
   dim w_trackAngle as word
   w_trackAngle=val(F8)
   setfont font16x16
   if clearmenuheader <10 then lcdat 1,1,"Heading" else lcdat 1,1,"       o"
   incr clearmenuheader
   setfont  Arial_38x42

   select case w_trackangle
      case 0 :lcdat 3,1," ~ "
      case 1 to 9:    lcdat 3,10,"  ";w_trackAngle
      case 10 to 99:  lcdat 3,10," ";w_trackAngle
      case 100 to 360:lcdat 3,10, w_trackAngle
   end select
end sub

sub compass()
   setfont font16x16
   if clearmenuheader < 10 then lcdat 1,1,"compass" else lcdat 1,1,"       "
   incr clearmenuheader
   setfont Arial_38x42
   dim row,col,col1 as byte
   row=3:col=1:col1=1

   select case val (F8) 'S_trackAngle=track angle string
      case 0          :lcdat row,col,   " ~ "
      case 1  to 11   :lcdat row,col,   " N "  'pick up the other half at the end
      case 12 to 33   :lcdat row,col,   "NNE"
      case 34 to 57   :LCDAT row,col1,  " NE"
      case 58 to 78   :lcdat row,col,   "ENE"
      case 79 to 101  :lcdat row,col,   " E "
      case 102 to 123 :lcdat row,col,   "ESE"
      case 124 to 147 :lcdat row,col1,  " SE"
      case 148 to 168 :lcdat row,col,   "SSE"
      case 169 to 191 :lcdat row,col,   " S "
      case 192 to 213 :lcdat row,col,   "SSW"
      case 214 to 236 :lcdat row,col1,  " SW"
      case 237 to 258 :lcdat row,col,   "WSW"
      case 259 to 281 :lcdat row,col,   " W "
      case 282 to 303 :lcdat row,col,   "WNW"
      case 304 to 326 :lcdat row,col1,  " NW"
      case 327 to 348 :lcdat row,col,   "NNW"
      case 349 to 360 :lcdat row,col,   " N "
   end select
end sub

sub TripMeter()
   setfont font16X16
   lcdat 1,1,"TRIP"
   lcdat 6,1,ododist
end sub

sub pointsofinterest()
   local poi_num as byte
   local cd as byte:cd = 5  '/ count down for save confirmation
   local POI_distance as single
   local POI_Heading as word
   local ST_POI_distance as string*16
   local x as word
   local S_bbb AS SINGLE
   poi_num = encval - rstenc  '/reset encoder count to zero
   if poi_num > 49 then poi_num = 50   '//////////fix this aka poitot////////
   ''''if encval > 49 then poi_num = 50   'test//////////fix this aka poitot////////
   POI_Distance = distance(Latt,Lon,POI_Latt(poi_num),POI_lon(poi_num))
   ST_POI_Distance = Fusing(POI_Distance ,"#.##")

   'POI_Heading = Bearing(Latt,Lon,POI_Latt(poi_num),POI_Lon(poi_num))
   POI_Heading = Bearing(POI_Latt(poi_num),POI_Lon(poi_num),latt,lon)
   setfont font8x8
   if POI_Latt(poi_num) > 0 or  POI_Lon(poi_num) > 0 then
      lcdat 1,50,POI_Latt(poi_num)
      lcdat 2,50,POI_Lon(poi_num)
   else
      lcdat 1,50,"-----"
      lcdat 2,50,"-----"
   end if
   lcdat 3,1,"   secret beach"
   setfont font16x16
   lcdat 1,1,"$"; poi_num '/ $ = the 'pin' symbol / font edited

   if valid = "A" then

      setfont font16x16
      S_bbb = val(ST_POI_Distance)
      x = val(ST_POI_Distance)  '/cast to word to strip the frac

      select case S_bbb
         case 0 to 0.99
            delchars ST_POI_Distance,"."
            x = x*10
            lcdat 4,1,x;"M "

         case 1 to 9.99:
            lcdat 4,1,x;"K   "
         case 10 to 99.99:
            lcdat 4,1,x;"K  "
         case 100 to 999.99:
            lcdat 4,1,x;"K "
         case 1000 to 9999.99:
            lcdat 4,1,x;"K"
      end select

      if POI_Distance>0.01 and POI_Latt(poi_num) > 0 or  POI_Lon(poi_num) > 0 then
         select case POI_heading
            case 0 to 9:
               lcdat 7,1,POI_Heading;"  -deg"
            case 10 to 99:
               lcdat 7,1,POI_Heading;" -deg"
            case 100 to 360:
               lcdat 7,1,POI_Heading;"-deg"
         end select
      end if
   end if

   while encswitch = 0 and valid = "A"
      cls
      while cd > 0 and encswitch = 0 'count down till save - protect against accidental button push
         setfont Arial_38x42
         lcdat 3,50,cd
         decr cd
         waitms 250
      wend
      cls

      if cd = 0 and encswitch = 0 then
         POI_Latt(poi_num) = latt : POI_lon(poi_num) = Lon
         E_POI_LATT(poi_num) = Latt : E_POI_LON(poi_num) = Lon
         cls:setfont font 16x16
         lcdat 4,15,"SAVED"
         bitwait encswitch,set
         cls
      end if
   wend

   If encswitch = 0 and valid = "V" then
      cls
      setfont font16x16
      lcdat 4,1,"No Sats"
      bitwait encswitch,set
      cls
   end if

end sub

sub keypad()

   local x as byte
   LOCAL C_POI_VAL as byte
   C_POI_VAL = 1
   setfont font8X8
   lcdat 1,1,"7 8 9"
   lcdat 2,1,"4 5 6"
   lcdat 3,1,"1 2 3"
   LCDAT 4,1,"- 0 ."
   LCDAT 6,1,"EDIT":lcdat 6,50,"EXIT"
   LCDAT 7,1,"LAT ";POI_Latt(C_POI_VAL)
   LCDAT 8,1,"LON ";POI_Lon(C_POI_VAL)
   SETFONT FONT16X16
   LCDAT 1,50,"POI"
   lcdat 3,50," ";C_POI_VAL;" "

   if EncSwitch = 0 then
      set InMenuFlag
      HoldCaseVal = EncVal '/ we mess with the encoder value below. this holds its val for when we done
      EncVal = 1
      bitwait EncSwitch,set
   end if

   ''/   WE COME HERE ON BUTTON PRESS aka edit mode
   while InMenuFlag = 1
      If encval > 3 then encval = 3

      select case encval
         case 1: '/select poi
            setfont font8x8 : lcdat 6,1,"EDIT" : setfont font16X16
            lcdat 3,50," ";C_POI_VAL;" ",1
            if encswitch = 0 then
               bitwait encswitch,set
               do
                  x=poitot-1
                  C_POI_VAL=encval
                  if C_POI_VAL > x then
                     C_POI_VAL = poitot   '/to fix screen glitchiness
                     encval = C_POI_VAL
                  end if
                  setfont font16x16
                  lcdat 3,50,">";C_POI_VAL;"  "
                  setfont font8x8
                  if POI_Latt(c_poi_val) > 0 or  POI_Lon(c_poi_val) > 0 then
                     LCDAT 7,1,"LAT ";POI_Latt(C_POI_VAL)
                     LCDAT 8,1,"LON ";POI_Lon(C_POI_VAL)
                  else
                     lcdat 7,1,"-------------"
                     lcdat 8,1,"-------------"
                  end if
                  if encswitch = 0 then
                     encval = 2
                     exit do
                  end if
               loop
            end if


         case 2:
            setfont font16x16
            lcdat 3,50," ";C_POI_VAL;"  "
            setfont font8x8
            lcdat 6,1,"EDIT",1
            lcdat 6,50,"EXIT"











         case 3:
            setfont font8x8: lcdat 6,1,"EDIT":lcdat 6,50,"EXIT",1

            if encswitch = 0 then
               InMenuFlag = 0
               encval = HoldCaseVal
               BITWAIT encswitch,set
               exit sub
            end if

      end select

   wend
   if encswitch = 0 and encval = 3 then
      reset inmenuflag
      'encval = holdcaseval '/ reload value for main menu nav.
      bitwait encswitch, set
   end if
end sub

sub qwerty()

   local x as byte :   local n as byte
   const ChrTot=43 'the total amount of charachters on keyboard
   HoldCaseVal = EncVal : EncVal = 14
   dim keyboard(chrtot) as byte  :   dim spaceval(chrtot) as byte :   dim hozline(chrtot) as byte:dim answer(15) as byte
   local index as byte:index = 1
   local state as byte

   'load array values from data tables
   for n=1 to chrtot
      keyboard(n) = Lookup(n , numdata)
      spaceval(n) = lookup(n , spacedata)
      hozLine(n) = lookup(n , linedata )
   next n

   setfont font8x8

   do
      'this just redraws the screen to clear highlited text when its not selected
      if encval <> state then
         for n = 1 to chrtot
            lcdat hozline(n),spaceval(n),chr(keyboard(n))
            if keyboard(n)=115 then lcdat hozline(n),spaceval(n),"save"
            if keyboard(n)=100 then lcdat hozline(n),spaceval(n),"del"
            if keyboard(n)=101 then lcdat hozline(n),spaceval(n),"exit"
         next  n
      end if


      state = encval

      'this highlites text
      lcdat hozline(encval),spaceval(encval),chr(keyboard(encval)),1
      if encval=11 then lcdat hozline(encval),spaceval(encval),"save",1
      if encval=12 then lcdat hozline(encval),spaceval(encval),"del",1
      if encval=13 then lcdat hozline(encval),spaceval(encval),"exit",1

      ' save/del/exit actions
      if encval > chrtot then encval=chrtot
      if encval=13 and encswitch=0 then exit sub


      'input selection
      if encswitch = 0  then
         answer(index) = keyboard(encval)
         lcdat 8,spaceval(index),chr(answer(index)),1
         incr  index:if index>10 then index=10
         bitwait encswitch, set
      end if

   loop


   EncVal=1


   numdata:'0 0  1  2  3  4  5  6  7  8  9     [save][del][exit]        A  B  C  D  E  F      G  H  I  J  K  L     M  N  O  P  Q  R     S  T  U  V  W   !     X  Y  Z  .  -  *
      data 48,48,49,50,51,52,53,54,55,56,57    ,115,  100,  101        ,65,66,67,68,69,70    ,71,72,73,74,75,76   ,77,78,79,80,81,82   ,83,84,85,86,87,33   ,88,89,90,46,45,42
   spacedata:
      data 1,11,21,31,41,51,61,71,81,91,101     ,80,80,80               ,1,11,21,31,41,51     ,1,11,21,31,41,51    ,1,11,21,31,41,51    ,1,11,21,31,41,51    ,1,11,21,31,41,51
   linedata:
      data 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1       ,3,4,5                  ,3,3,3,3,3,3            ,4,4,4,4,4,4          ,5,5,5,5,5,5       ,6,6,6,6,6,6        ,7,7,7 ,7,7 ,7

end sub




sub ClearAllPoi()
   local k as byte
   for k = 1 to poitot
      POI_Latt(k) = 0 : E_POI_LATT(k) = 0
      POI_lon(k) = 0 : E_POI_LON(k) = 0
   next k
end sub

sub Configuration()
   dim beeperSetFlag as byte

   setfont font8X8
   lcdat 1,5,"-^-CONFIG-^-",1
   'setfont font8x8

   if EncSwitch = 0 then
      set InMenuFlag
      HoldCaseVal = EncVal '/ we mess with the encoder value below. this holds its val for when we done
      EncVal = 1
      bitwait EncSwitch,set
   end if

   lcdat 2,1, "BRIGHTNESS"
   lcdat 3,1, "DIST UNITS"
   lcdat 4,1, "SPEED ALERT"
   lcdat 5,1, "HEIGHT UNITS"
   lcdat 6,1, "CLEAR P.O.I."
   lcdat 7,1, "ANCHOR ALARM"
   lcdat 8,1, "PROX ALARM"
end sub

SUB SETUPGTOP()
   '/ not needed for this application (mirror), to be sorted with a fresh gps module re baud rates
   local k as byte
   For k = 1 To 3
      Print #2 , " $PMTK251,57600*2C"
      Print  "$PMTK251,57600*2C"
      Waitms 50
   Next k

   config COM2 =9600,   Synchrone = 0 , Parity = None , Stopbits = 1 , Databits = 8 , Clockpol = 0
   Waitms 50

   For k = 1 To 3
      Print #2 , "$PMTK220,100*2F"       'UPDATE 10HZ
      Print   "$PMTK220,100*2F"
      Waitms 50
   Next k

   for k = 1 To 3
'select spat out strings
      Print #2 ,  "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
      Print   "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
      Waitms 50
   Next k

END SUB

Sub Getstring()
'' if a new or extra  header is required make sure gtop setup is also added to / changed PMTK 314

   Local Ggps As String * 5 : Local Gps1 As String * 100  : Local Ch As string*1


 'Ggps = ""          'CLEAR GGPS variable JUST IN CASE

'   While Ggps <> "GNGGA"    ' <---------- the sentance we want

'      Do
'      Ch = Inkey (#2)
'      Loop Until Ch = "$"         '<  -------sentance start
'      Input #2 , Gps1  Noecho       'GET A FULL SENTENCE  and load in into gps1
'      Ggps = Left(gps1 , 5)              'suck out the header and CHECK IT FOR A MATCH  (top of wend)
'Wend

'Gpgga = Gps1

   Ggps = ""          'CLEAR GGPS JUST IN CASE
   While Ggps <> "GNRMC"
      Do
         Ch = Inkey (#2)
      Loop Until Ch = "$"
      Input #2 , Gps1 Noecho      'GET A FULL SENTENCE
      Ggps = Left(gps1 , 5)       'CHECK IT FOR A MATCH, nmea sentance header that is
   Wend

   Gprmc = Gps1

End Sub

Function Commapos(byval Startcomma As Byte , Byval Storedstring As String) As String * 10
   Local N As Byte , Q As Byte , Comma As Byte , X As String * 1 , Endcomma As Byte
'n=start posistion  q=end posistion
'q also = grab string length ie- mid(var,n,q)
'find index(N) for start comma posistion
   Comma = 0 : N = 0 : Q = 0
   Endcomma = Startcomma + 1
   While Comma < Startcomma       'COMMA HOLD THE COMMA COUNT AMOUNT
      Incr N
      X = Mid(storedstring , N , 1)
      If X = "," Then Incr Comma
   Wend
'find index(Q) for end comma posistion
   Q = N
   While Comma < Endcomma
      Incr Q
      X = Mid(storedstring , Q , 1)
      If X = "," Then Incr Comma
   Wend

'START COUNT AND END COUNT NEED A SEPERATION OF MORE THAN 0  so if q=n then no seperation.
   N = N + 1
   If Q = N Then Commapos = "0"
   If Q = N Then Goto Skip
   N = N - 1
   Q = Q - N
   Q = Q - 1
   N = N + 1
'suck out the needed string componant
   Commapos = Mid(storedstring , N , Q)
   Skip:

End Function

Function Speed(byval Knots As String)as String * 11

   Local Oput As String * 10 : Local X As Single : Local Y As Byte
   X = Val(knots)
   X = X * 1.852
   Oput = Str(x)
   Y = Charpos(oput , ".")
   Y = Y + 1
   Oput = Left(oput , Y)
   Speed = Oput   '/ in kilometers per hour

End Function

Function Bearing(lat1 as single , Lon1 as single , Lat2 as single , Lon2 as single ) As word

   Const Cpi = 3.14159265:Const C2pi = 6.2831854:Const Crad2nm = 3437.746771 ' radians to nautical miles
   Const Cnm2ft = 6080.0 ' nautical miles to feet

   Local X1,x2,y1,y2,dx,dy,cosd,nu,de,be,ad,dq As Single

   Dx = Lon2 - Lon1: Dx = Dx / 2 :  Dx = Sin(dx) :   Dx = Dx * Dx
   Dy = Lat2 - Lat1 :Dy = Dy / 2 :  Dy = Sin(dy) :   Dy = Dy * Dy
   x1 = sin(lat1): Y1 = Cos(lat1):  x2 = sin(lat2) : Y2 = Cos(lat2)

   Dx = Lon2 - Lon1: Nu = sin(Dx): Nu = nu * Y2
   De = cos(Dx): De = De * Y2: De = De * X1 : X2 = X2 * Y1  : De = X2 - De : Ad = 0.0

   If Nu <> 0.0 Then
      If De <> 0.0 Then
         Be = Nu / De
         Be = Atn(be) 'radians
         If De < 0.0 Then
            Ad = Cpi
         End If
         If Nu < 0.0 And De > 0.0 Then
            Ad = C2pi
         End If

      Else
         If Lon2 > Lon1 Then
            Ad = Cpi / 2.0
         Else
            Ad = 1.5 * Cpi
         End If
      End If
   Else
      If Lat2 > Lat1 Then
         Be = 0.0
      Else
         Be = Cpi
      End If
   End If

'dim bear,dist as single
   Be = Be + Ad
   be = Rad2deg(be)
   Bearing = be
End function

Function distance (byval Startlat As Single , byval Startlon As Single, byval Endlat As Single, byval  Endlon As Single )as Single

   Local R As Single , D As Single , X As Single , Y As Single
   Local Tmp1 As Single , Tmp2 As Single , Tmp3 As Single , Height As Single
   Startlat = Startlat * 3.14158 : Startlat = Startlat / 180
   Startlon = Startlon * 3.14158 : Startlon = Startlon / 180
   Endlat = Endlat * 3.14158 : Endlat = Endlat / 180
   Endlon = Endlon * 3.14158 : Endlon = Endlon / 180
   Tmp1 = 0 : Tmp2 = 0 : Tmp3 = 0
   Tmp1 = Startlon - Endlon
   Tmp2 = Startlat + Endlat    :   Tmp2 = Tmp2 / 2
   Tmp3 = Cos(tmp2)
   X = Tmp1 * Tmp3
   Y = Endlat - Startlat
   Tmp1 = X * X
   Tmp2 = Y * Y
   Tmp3 = Tmp1 + Tmp2
   Tmp3 = Sqr(tmp3)
   'd=2d distance in kilometers
   D = Tmp3 * 6371
   distance = D'in klm

End Function

Function Convert(field1 As String , Field2 As String , ) As Single
    '    CO'ORDS         N,S,E,W,              NON DEC CORD RETURN
   local MSP As Single , LSP As Single   ,TOT AS SINGLE

   MSP= val(field1)
   MSP=MSP/100  ' move the dec point
   LSP = frac(MSP)
   MSP = int(MSP)
   LSP = LSP / 60
   LSP = LSP*100
   TOT = MSP + LSP

   If Field2 = "S"  Then TOT = -TOT
   If Field2 = "W" Then TOT = -TOT
   Convert = TOT
End Function

Function Odo()as single
'keep this alive once called
'/ST_Speed_in_knots is speed in knots from gps

   Local Temp As Single
   Dim Total As Single
   Dim Store(4) As Single
   Dim drift(2) as single
   Dim OdoInitflag As Byte
   Dim DriftFlag as byte
   Dim MinSpeed as byte : MinSpeed = 3 '/   in knots - if speed < minspeed use drift mode / integer only

   if valid <> "A" then goto endfunction  '/no sat sig = do nothing

   Dist_mode:
      reset driftflag

      if OdoInitFlag = 0 then      '/load initial values
         Store(1) = latt
         Store(2) = lon
         Store(3) = latt
         Store(4) = lon
         set OdoInitFlag
      end if

      select case FlipBit   '/update pos every 2nd nmea read
         case 0:
            Store(1) = latt
            Store(2) = lon
         case 255:
            Store(3) = latt
            Store(4) = lon
      End select

      if val(ST_Speed_in_knots) > MinSpeed then

         Temp = distance(store(1) , Store(2) , Store(3) , Store(4)) '/ it works, as every second clock is a backwards measure
         Total = Total + Temp
      end if

   DriftMode:

      if val(ST_Speed_in_knots)< MinSpeed then

         dim DriftDir as single

         if DriftFlag = 0 then              '/load start posistion to check against
            drift(1) = latt
            drift(2) = lon
            Set DriftFlag
         end if

         temp = distance(drift(1),drift(2),latt,lon)

         if temp > 0.05 then                '/ have drifted more than 50meters?
            total = total+temp

            reset DriftFlag                 '/ update drift start co'ords  only if travelled > 50m
         end if
      end if

      if total>9999 then total = 0  '/ rollover, set an eeram bit

      Odo = total



   endfunction:
End Function
'''
