$nocompile
sub qwerty()

   const ChrTot=43 '/the total amount of charachters on keyboard
   HoldCaseVal = EncVal : EncVal = 14   '/14 puts initial curser in the middle of screen

   dim keyboard(ChrTot) as byte : dim spaceval(ChrTot) as byte : dim hozline(ChrTot) as byte : dim answer(15) as byte
   local index as byte : index = 1
   local state as byte : local x as byte : local n as byte

   '/load arrays from data tables
   for n=1 to ChrTot
      keyboard(n) = Lookup(n , numdata)   '/decimal ascii value of charachter
      spaceval(n) = lookup(n , spacedata) '/verticle spacing
      hozLine(n) = lookup(n , linedata )  '/horizontal spacing
   next n

   setfont font8x8

   do
      '/this redraws the screen to clear highlited text when its not selected
      if EncVal <> state then '/ only redraw when needed
         for n = 1 to ChrTot
            lcdat hozline(n),spaceval(n),chr(keyboard(n))
            if keyboard(n)=115 then lcdat hozline(n),spaceval(n),"save"
            if keyboard(n)=100 then lcdat hozline(n),spaceval(n),"del"
            if keyboard(n)=101 then lcdat hozline(n),spaceval(n),"exit"
         next  n
      end if


      state = EncVal


      '/this highlites text
      lcdat hozline(EncVal),spaceval(EncVal),chr(keyboard(EncVal)),1
      if EncVal=11 then lcdat hozline(EncVal),spaceval(EncVal),"save",1
      if EncVal=12 then lcdat hozline(EncVal),spaceval(EncVal),"del",1
      if EncVal=13 then lcdat hozline(EncVal),spaceval(EncVal),"exit",1


      if EncVal > ChrTot then EncVal=ChrTot

      '/ save/del/exit actions
      if EncVal=13 and EncSwitch=0 then exit sub


      '/input selection
      if EncSwitch = 0  then
         answer(index) = keyboard(EncVal)
         lcdat 8,spaceval(index),chr(answer(index)),1
         'incr  index:if index>10 then index=10
         if index < 10 then incr index  '/sets the charachter limit of the answer
         bitwait EncSwitch, set
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
