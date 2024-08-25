echo on
echo "hello batch files"
if 2 > 1 echo "demobust"
SET MyFolder = "examples"
if %TEMP% == %MyFolder% echo demobust
if exist %MyFolder% echo "ebat exits"
exit 255
