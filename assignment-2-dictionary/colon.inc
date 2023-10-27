%define top 0
%macro colon 2
   %ifid %2
      %2: dq top
      %define top %2
   %else
      %error "Wrong colon: %2"
   %endif
   %ifstr %1
      db %1, 0
   %else
      %error "Wrong colon: %1"
   %endif
   
%endmacro



