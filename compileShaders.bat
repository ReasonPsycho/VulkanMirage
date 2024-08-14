for /r %%i in (*.frag) do C:/Tools/VulkanSDK/1.3.290.0/Bin/glslc.exe "%%i" -o "%%~dpi%%~niFrag.spv"
for /r %%i in (*.vert) do C:/Tools/VulkanSDK/1.3.290.0/Bin/glslc.exe "%%i" -o "%%~dpi%%~niVert.spv"
pause