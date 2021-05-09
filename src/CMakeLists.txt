# Try to find raylib library if installed locally.
find_package(raylib QUIET)

# Otherwise fetch and build repo.
if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG e25e380)

    FetchContent_GetProperties(raylib)
    if(NOT raylib_POPULATED) 
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        # Toggle off LOADS of raylib build options.
        # https://github.com/raysan5/raylib/wiki/CMake-Build-Options
        set(BUILD_EXAMPLES            OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES               OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING             OFF CACHE BOOL "" FORCE)
        set(SUPPORT_BUSY_WAIT_LOOP    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_CAMERA_SYSTEM     OFF CACHE BOOL "" FORCE)
        set(SUPPORT_DEFAULT_FONT      OFF CACHE BOOL "" FORCE)
        set(SUPPORT_SCREEN_CAPTURE    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_GIF_RECORDING     OFF CACHE BOOL "" FORCE)
        set(SUPPORT_GESTURES_SYSTEM   OFF CACHE BOOL "" FORCE)
        set(SUPPORT_MOUSE_GESTURES    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_VR_SIMULATOR      OFF CACHE BOOL "" FORCE)
        set(SUPPORT_DISTORTION_SHADER OFF CACHE BOOL "" FORCE)
        set(SUPPORT_QUADS_DRAW_MODE   OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_DDS    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_HDR    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_KTX    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_ASTC   OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_BMP    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_TGA    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_JPG    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_GIF    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_PSD    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_PKM    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_PVR    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_OBJ    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_MTL    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_WAV    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_OGG    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_XM     OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_MOD    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_FLAC   OFF CACHE BOOL "" FORCE)
        set(SUPPORT_FILEFORMAT_FNT    OFF CACHE BOOL "" FORCE)
        set(SUPPORT_SAVE_PNG          OFF CACHE BOOL "" FORCE)
        set(SUPPORT_SAVE_BMP          OFF CACHE BOOL "" FORCE)

        add_subdirectory(
            ${raylib_SOURCE_DIR} 
            ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(versus 
    main.c 
    drawing.h 
    drawing.c)

target_link_libraries(versus raylib)
