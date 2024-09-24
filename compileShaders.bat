for /r %%i in (*.frag) do C:/VulkanSDK/1.3.290.0/Bin/glslc.exe "%%i" -o "%%~dpi%%~niFrag.spv"
for /r %%i in (*.vert) do C:/VulkanSDK/1.3.290.0/Bin/glslc.exe "%%i" -o "%%~dpi%%~niVert.spv"
for /r %%i in (*.rchit) DO C:\Tools\dxc\bin\x64\dxc.exe -T lib_6_3 -E main -spirv -fspv-extension=SPV_KHR_ray_tracing -fspv-target-env=vulkan1.2 -Fo "%%~dpi%%~niRchit.spv" "%%i"
for /r %%i in (*.rmiss) DO C:\Tools\dxc\bin\x64\dxc.exe -T lib_6_3 -E main -spirv -fspv-extension=SPV_KHR_ray_tracing -fspv-target-env=vulkan1.2 -Fo "%%~dpi%%~niRmiss.spv" "%%i"
for /r %%i in (*.rgen) DO C:\Tools\dxc\bin\x64\dxc.exe -T lib_6_3 -E main -spirv -fspv-extension=SPV_KHR_ray_tracing -fspv-target-env=vulkan1.2 -Fo "%%~dpi%%~niRgen.spv" "%%i"
pause