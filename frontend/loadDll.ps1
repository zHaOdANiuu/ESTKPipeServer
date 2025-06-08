$bin = "D:/app/Adobe After Effects 2025/Support Files/AfterFX.exe"
$dll = "D:/proj/cpp/After-Effects-Plug-Ins/ExecuteEsScript/bin/es.dll"

& $bin -s "new ExternalObject('lib:$dll')"
