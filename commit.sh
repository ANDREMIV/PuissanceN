SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
cd $SCRIPTPATH
mv ./bin/Debug/puissanceNwin.exe .
git status
git add .
git commit -m "$(date)"
git push origin master