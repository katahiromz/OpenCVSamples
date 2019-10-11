# WinCapt.exe
add_executable(WinCapt WIN32 WinCapt.cpp WinCapt_res.rc)
target_link_libraries(WinCapt ${OpenCV_LIBS} comctl32)
