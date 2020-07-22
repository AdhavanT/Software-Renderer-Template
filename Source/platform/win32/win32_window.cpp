#include "win32_window.h"
#include <strsafe.h>

LRESULT CALLBACK Wnd_Proc_Callback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void SizeBitmap(Win32_BitmapBuffer *bm_buffer, Vec2<uint32> dimensions);
void Resize_Window(HWND& wnd, HDC& device_context);

Win32_BitmapBuffer wnd_bitbuffer = {};
Vec2<uint32> wnd_dimensions = {1000, 1000};
b8 running;

int wWinMain( _In_ HINSTANCE hInstance,
              _In_opt_ HINSTANCE hPrevInstance,
              _In_ LPWSTR    lpCmdLine,
              _In_ int       nCmdShow)
{
    WNDCLASSA wnd_class = {};
    wnd_class.lpszClassName = "rendering_window";
    wnd_class.lpfnWndProc = Wnd_Proc_Callback;
    wnd_class.hInstance = hInstance;
    wnd_class.style = CS_HREDRAW | CS_VREDRAW;
    wnd_class.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(32515));

    RegisterClassA(&wnd_class);

    Vec2<uint32> buffer_size = { 1000, 1000 };
    SizeBitmap(&wnd_bitbuffer, buffer_size);

    HWND window_handle = CreateWindowExA(
        0,
        wnd_class.lpszClassName,
        "My Renderer",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wnd_dimensions.x,
        wnd_dimensions.y,
        0,
        0,
        hInstance,
        0
        );

    LARGE_INTEGER performance_frequency, oldframe_count, newframe_count;
    f32 delta_time = 0;
    int32 frame_rate;
    QueryPerformanceFrequency(&performance_frequency);
    QueryPerformanceCounter(&oldframe_count);   //initialization for first frame calculation

    f32 time_factor;
    time_factor = (1000 / (f32)performance_frequency.QuadPart);


    if (window_handle)
    {
        running = true;
        while (running)
        {
            MSG message;
            while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT)
                {
                    running = false;
                }
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }

            QueryPerformanceCounter(&newframe_count);
            int64 elapsed_counts = newframe_count.QuadPart - oldframe_count.QuadPart;
            oldframe_count.QuadPart = newframe_count.QuadPart;
            delta_time = (f32)(elapsed_counts * time_factor);
            
            CoreLoop(wnd_bitbuffer.bitmap_buffer, delta_time);

            HDC dc = GetDC(window_handle);
            Resize_Window(window_handle, dc);
            ReleaseDC(window_handle, dc);

            frame_rate = (int32)(performance_frequency.QuadPart / elapsed_counts);

            char buffer[256];
            StringCbPrintfA(buffer, sizeof(buffer), "Time per frame: %.*fms , %dFPS\n", 1, delta_time, frame_rate);
            SetWindowTextA(window_handle, buffer);
            
        }
    }
}


void SizeBitmap(Win32_BitmapBuffer *bm_buffer, Vec2<uint32> dimensions)
{
    if (bm_buffer->bitmap_buffer.buffer_memory)
    {
        VirtualFree(bm_buffer->bitmap_buffer.buffer_memory, 0, MEM_RELEASE);
    }
    bm_buffer->bitmap_buffer.height = dimensions.y;
    bm_buffer->bitmap_buffer.width = dimensions.x;
    bm_buffer->bitmap_buffer.bytes_per_pixel = 4;
    bm_buffer->info.bmiHeader.biSize = sizeof(bm_buffer->info.bmiHeader);
    bm_buffer->info.bmiHeader.biBitCount = 32;
    bm_buffer->info.bmiHeader.biCompression = BI_RGB;
    bm_buffer->info.bmiHeader.biPlanes = 1;
    bm_buffer->info.bmiHeader.biHeight = dimensions.y;
    bm_buffer->info.bmiHeader.biWidth = dimensions.x;

    uint32 bitmap_memory_size = bm_buffer->bitmap_buffer.bytes_per_pixel * dimensions.x * dimensions.y;
    bm_buffer->bitmap_buffer.buffer_memory = VirtualAlloc(0, bitmap_memory_size, MEM_COMMIT, PAGE_READWRITE);
    ASSERT(bm_buffer->bitmap_buffer.buffer_memory);
}

void Resize_Window(HWND &wnd, HDC &device_context)
{
    RECT clientdim = {};
    GetClientRect(wnd, &clientdim);
    wnd_dimensions.x = clientdim.right - clientdim.left;
    wnd_dimensions.y = clientdim.bottom - clientdim.top;

    StretchDIBits(
        device_context,
        0, 0, wnd_dimensions.x, wnd_dimensions.y,
        0, 0, wnd_bitbuffer.bitmap_buffer.width, wnd_bitbuffer.bitmap_buffer.height,
        wnd_bitbuffer.bitmap_buffer.buffer_memory,
        &wnd_bitbuffer.info,
        DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK Wnd_Proc_Callback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_QUIT:
    {
        running = false;
    }
    break;
    case WM_CLOSE:
    {
        running = false;
    }
    break;

    case WM_KEYUP:
    {
        uint32 VKCode = wParam;

        //NOTE: To exit the application using alt+F4
        b8 AltKeyWasDown = (lParam & (1 << 29)) != 0;

        if (VKCode == VK_F4 && AltKeyWasDown)
        {
            running = false;
        }
    }break;
    case WM_DESTROY:
    {
        running = false;
        PostQuitMessage(0);
    }
    break;
    case WM_SIZE:
    {
        //TODO: for constant aspect ratio
        
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
            
        Resize_Window(hWnd, hdc);

        EndPaint(hWnd, &ps);
    }
    break;
    
    default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
    return 0;
}
