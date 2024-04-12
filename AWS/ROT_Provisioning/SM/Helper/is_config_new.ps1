# Variables
param(
    [string]$filePath,
    [string]$lastRunFile
)

# Check if the lastRunFile exists, if not, create it
if (-not (Test-Path $lastRunFile)) {
    $lastScriptRunTime = "1900-01-01T00:00:00"
} else {
    # Get the last run time of the script from the lastRunFile
    $lastScriptRunTime = (Get-Item $lastRunFile).LastWriteTime
}
Write-Host $lastScriptRunTime
# Get the last write time of the file
$fileLastWriteTime = (Get-Item $filePath).LastWriteTime
Write-Host $fileLastWriteTime
# Compare the last write time of the file and the last run time of the script
if ($fileLastWriteTime -gt $lastScriptRunTime) {
    Write-Host "The file has been updated since the last script run."
    return 1
} else {
    Write-Host "The file has not been updated since the last script run."
    return 0
}

