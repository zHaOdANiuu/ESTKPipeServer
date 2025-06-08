.\loadDll.ps1

$pipe = New-Object System.IO.Pipes.NamedPipeClientStream(
    ".", 
    "ExtendScriptPipeServer",
    [System.IO.Pipes.PipeDirection]::InOut
)

$pipe.Connect(5000)
Write-Host "Connected to ExtendScriptPipeServer"

$message = "'赵大牛'"
$bytes = [System.Text.Encoding]::UTF8.GetBytes($message)
$pipe.Write($bytes, 0, $bytes.Length)

$buffer = New-Object byte[] 1024
$bytesRead = $pipe.Read($buffer, 0, $buffer.Length)
$response = [System.Text.Encoding]::UTF8.GetString($buffer, 0, $bytesRead)
Write-Host "Response: $response"

$pipe.Close()
