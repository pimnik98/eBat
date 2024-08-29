echo debug
set test = "pimnik98"
echo "Testing the launch of programs as well as other arguments"
:: echo %CD%
dir
./aelf.elf "SayoriOS Dev" %test%

if exist "examples/run.bat" echo "run.bat exits"
if exist "examples/run.bat" "examples/run.bat" %test%