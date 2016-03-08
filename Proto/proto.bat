set PROTOC=..\Server\ProtoBuf\Tools\protoc.exe
set PROTOCSHARP=..\Server\ProtoBuf\Tools\protocsharp.exe

for %%i in (*.proto) do (
	%PROTOC% -I=.\ --cpp_out=.\cpp .\%%i
	%PROTOCSHARP% -i:%%i -o:.\c#\%%i.cs
)

copy .\c#\*.* ..\ClientSDK\C#\Proto /y
copy .\cpp\*.* ..\Server\Proto /y

pause