set PROTOC=..\Server\ProtoBuf\Tools\protoc.exe
set PROTOCSHARP=..\Server\ProtoBuf\Tools\protocsharp.exe

for %%i in (*.proto) do (
	%PROTOC% -I=.\ --cpp_out=.\cpp .\%%i
	%PROTOCSHARP% -i:%%i -o:.\csharp\%%i.cs
)

copy .\cpp\*.* ..\Server\Proto /y

pause