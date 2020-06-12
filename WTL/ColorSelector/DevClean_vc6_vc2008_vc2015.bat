@echo --------------------------------------------
@echo Delete and Remove the 'Debug', Release' Dir
@echo      and NCB files for your Clean Data(_High Jewel_)
@echo --------------------------------------------
@echo  (Note: Confirm the current Directory...)
@echo off
pause
@echo Starting...
@echo Removing folders...
FOR /R . %%d IN (.) DO rd /s /q "%%d\Debug" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\DebugPS" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\obj" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\x64" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Release" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Publish" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\ipch" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\_LeakDetectDebug" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\.vs" 2>nul
@echo Removing files...
FOR /R . %%d IN (.) DO del "%%d\*.ncb" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.sdf" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.pdb" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.ilk" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.exp" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.ipch" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.VC.db" 2>nul
FOR /R . %%d IN (.) DO del "%%d\*.VC.opendb" 2>nul
@echo Finished...Thanks!
@echo. & pause
