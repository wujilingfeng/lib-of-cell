;;;::btw::by the way 
mynum=9
name=3
day=20190925
myvar = E:\Ks-moji\scan_project\%day%\%name%\%mynum%\%mynum%.sproj
myvar1 = %myvar% - Artec Studio 12 Professional
esc::
	Loop{
		Loop{
			Loop{
		
				myvar = E:\Ks-moji\scan_project\%day%\%name%\%mynum%\%mynum%.sproj
				myvar1 = %myvar% - Artec Studio 12 Professional
				Run,%myvar%
		
				Sleep,3000
				Send,{Enter}
				Sleep,6000
				Send,{Enter}
				WinWait, %myvar1%
				Sleep 10000
				Send,{Click,66,329}
				Sleep 3000
				Send,{Click,383,529}
				Sleep 3000
				Send,{Click,412,579}
				Sleep 3000
				Send,{Click,381,611}
				Sleep 50000
				Send,{Click,383,695}
				Sleep 60000
				Send,{Click,56,712}
				Sleep 3000
				Send,{Click,146,330}
				Sleep 3000
				Send,{Click,229,884}
				Sleep 320000
				Send,{Click,390,141}
				Sleep 2000
				Send,{Click,390,141}
				Sleep 2000
				Send,{Click,390,141}
				Sleep 3000
				Send,{Click,240,876}
				Sleep 3000
				Send,^{s}
				Sleep 10000
				Send, ^+{e}
				Sleep 3000
				Send,{Click,538,52}
				Sleep 3000
				Send,{Click,538,52}
				Sleep 3000
				Send,{Click,538,52}
				Sleep 3000
				Send,{Click,474,117}
				j=1
				Loop
				{
					Sleep 500
					if(j==(day-20190923+13))
					{break
					}
					Send,{Down}
					j++
				}
				Sleep 1000
				Send,{Enter}
				Sleep 1000
				Send,{Click,474,117}
				j=1
				Loop 
				{
					Sleep 500
					if(j==name)
					{
						break
					}	
					Send,{Down}
					j++
				
				}
		
				Sleep 1000
				Send,{Enter}
				Sleep 1000
				Send,{Click,474,117}
				i=1
				Loop{
					Sleep 500
					if(i==mynum)
					{
						break
					}	
					Send,{Down}
					i++
				
				}
				Sleep 1000
				Send,{Enter}
				Sleep 1000
				Send,{Click,317,212}
				Sleep 10000
				Send,{Enter}
				Sleep 3000
				Send,{Click,318,127}
				Sleep 3000
				Send,{Click,110,101}
				Sleep 18000
			
				mynum++
				if(mynum==18)
				{	mynum=1
					break
					}
			}
			name++
			if(name==5)
			{	name=1
				break
			}
		}	
	day++
	if(day==20190930)
	{	break
	}
	}
return
#c::
	Send,{Click,66,329}
return	
#x::
MouseGetPos, X,Y
MsgBox ,%X%,%Y%,ÍË³ö
return
#y::
	Send, ^+{e}
	Sleep 3000
	Send,{Click,538,52}
	Sleep 3000
	Send,{Click,538,52}
	Sleep 3000
	Send,{Click,538,52}
	Sleep 3000
	Send,{Click,474,117}
	j=1
	Loop
	{
		Sleep 500
		if(j==(day-20190920+12))
		{break
		}
		Send,{Down}
		j++
	}
	Sleep 1000
	Send,{Enter}
	Sleep 1000
	Send,{Click,474,117}
	j=1
	Loop 
	{
		Sleep 500
		if(j==name)
		{
			break
		}	
		Send,{Down}
		j++
			
	}
		
	Sleep 1000
	Send,{Enter}
	Sleep 1000
	Send,{Click,474,117}
	i=1
	Loop{
		Sleep 500
		if(i==mynum)
		{
			break
		}	
		Send,{Down}
		i++
			
	}
	Sleep 1000
	Send,{Enter}
return