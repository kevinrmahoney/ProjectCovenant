echo off
echo WARNING *** THIS BATCH FILE IS ABOUT TO DELETE ALL YOUR CHANGES. CLICK CTRL+C TO STOP THIS FROM RUNNING. HIT ENTER TO BEGIN.
pause
echo NO SERIOUSLY. LAST WARNING.
pause
cd ..
git rm --cached -r .
git reset --hard
git rm .gitattributes
git reset .
git checkout .