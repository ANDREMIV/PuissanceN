SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
cd $SCRIPTPATH
cp ./bin/Debug/puissanceNwin.exe .
git status
git add .
git commit -m "$(date)"
git push origin master
echo "press enter to continue"
read