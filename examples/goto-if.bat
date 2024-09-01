echo on
echo "Testing goto-if + variable"

:success
echo "Successful!" or Success
set mainroot = "error"
goto main

:error
echo "Error" or Error
goto end

:main
echo "MainRoot"
goto %mainroot%

:end
echo "Goodbye"
exit 1

set mainroot = "success"
goto main
