$scriptPath = split-path -parent $MyInvocation.MyCommand.Definition

$conanDir = Join-Path $scriptPath \.main_cache\conan

# Resolve data for Debug mode
Start-Process -FilePath "conan" -Wait -NoNewWindow -ArgumentList `
    "install conanfile.txt -of $conanDir\x64\Debug",
    "-s build_type=Debug",
    "--build=missing"

# Resolve data for Release mode
Start-Process -FilePath "conan" -Wait -NoNewWindow -ArgumentList `
    "install conanfile.txt -of $conanDir\x64\Release",
    "-s build_type=Release",
    "--build=missing"