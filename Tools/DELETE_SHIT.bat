cd ..
del *.sln
rmdir Binaries /s /q
rmdir DerivedDataCache /s /q
rmdir Intermediate /s /q
:: rmdir Saved /s /q Not sure if we sohuld ever delete this.
echo Please wait until prompted.
pause
echo Done!