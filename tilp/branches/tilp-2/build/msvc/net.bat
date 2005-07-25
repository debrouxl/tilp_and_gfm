del *.ncb
del *.ilk
del *.dep
del *.opt
del *.plg
del *.aps
del *.exp
del *.idb
del *.obj
del *.pch
del *.exe
deltree /y output
deltree /y debug
deltree /y release
rmdir /s /q output
rmdir /s /q debug
rmdir /s /q release

cls