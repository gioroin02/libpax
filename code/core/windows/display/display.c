#ifndef PAX_WINDOWS_DISPLAY_DISPLAY_C
#define PAX_WINDOWS_DISPLAY_DISPLAY_C

#include "./display.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#define PAX_WINDOWS_DISPLAY_WIDTH  800
#define PAX_WINDOWS_DISPLAY_HEIGHT 600

#define PAX_WINDOW_CLASS pax_str16(L"__pax_window_class__")

struct Pax_Windows_Display
{
    HWND      handle;
    HINSTANCE instance;

    Pax_Windows_Display_Buffer* buffer;

    paxiword width;
    paxiword height;
};

struct Pax_Windows_Display_Buffer
{
    HDC     context;
    HBITMAP bitmap;

    paxu8*   memory;
    paxiword width;
    paxiword height;
    paxiword stride;
};

static Pax_Keybd_Button
pax_windows_map_keybd_button(paxiword value)
{
    switch (value) {
        case 65: return PAX_KEYBD_BUTTON_A;
        case 66: return PAX_KEYBD_BUTTON_B;
        case 67: return PAX_KEYBD_BUTTON_C;
        case 68: return PAX_KEYBD_BUTTON_D;
        case 69: return PAX_KEYBD_BUTTON_E;
        case 70: return PAX_KEYBD_BUTTON_F;
        case 71: return PAX_KEYBD_BUTTON_G;
        case 72: return PAX_KEYBD_BUTTON_H;
        case 73: return PAX_KEYBD_BUTTON_I;
        case 74: return PAX_KEYBD_BUTTON_J;
        case 75: return PAX_KEYBD_BUTTON_K;
        case 76: return PAX_KEYBD_BUTTON_L;
        case 77: return PAX_KEYBD_BUTTON_M;
        case 78: return PAX_KEYBD_BUTTON_N;
        case 79: return PAX_KEYBD_BUTTON_O;
        case 80: return PAX_KEYBD_BUTTON_P;
        case 81: return PAX_KEYBD_BUTTON_Q;
        case 82: return PAX_KEYBD_BUTTON_R;
        case 83: return PAX_KEYBD_BUTTON_S;
        case 84: return PAX_KEYBD_BUTTON_T;
        case 85: return PAX_KEYBD_BUTTON_U;
        case 86: return PAX_KEYBD_BUTTON_V;
        case 87: return PAX_KEYBD_BUTTON_W;
        case 88: return PAX_KEYBD_BUTTON_X;
        case 89: return PAX_KEYBD_BUTTON_Y;
        case 90: return PAX_KEYBD_BUTTON_Z;

        case 48: return PAX_KEYBD_BUTTON_ZERO;
        case 49: return PAX_KEYBD_BUTTON_ONE;
        case 50: return PAX_KEYBD_BUTTON_TWO;
        case 51: return PAX_KEYBD_BUTTON_THREE;
        case 52: return PAX_KEYBD_BUTTON_FOUR;
        case 53: return PAX_KEYBD_BUTTON_FIVE;
        case 54: return PAX_KEYBD_BUTTON_SIX;
        case 55: return PAX_KEYBD_BUTTON_SEVEN;
        case 56: return PAX_KEYBD_BUTTON_EIGHT;
        case 57: return PAX_KEYBD_BUTTON_NINE;

        case VK_F1:  return PAX_KEYBD_BUTTON_F1;
        case VK_F2:  return PAX_KEYBD_BUTTON_F2;
        case VK_F3:  return PAX_KEYBD_BUTTON_F3;
        case VK_F4:  return PAX_KEYBD_BUTTON_F4;
        case VK_F5:  return PAX_KEYBD_BUTTON_F5;
        case VK_F6:  return PAX_KEYBD_BUTTON_F6;
        case VK_F7:  return PAX_KEYBD_BUTTON_F7;
        case VK_F8:  return PAX_KEYBD_BUTTON_F8;
        case VK_F9:  return PAX_KEYBD_BUTTON_F9;
        case VK_F10: return PAX_KEYBD_BUTTON_F10;
        case VK_F11: return PAX_KEYBD_BUTTON_F11;
        case VK_F12: return PAX_KEYBD_BUTTON_F12;

        case VK_NUMPAD0: return PAX_KEYBD_BUTTON_NUM0;
        case VK_NUMPAD1: return PAX_KEYBD_BUTTON_NUM1;
        case VK_NUMPAD2: return PAX_KEYBD_BUTTON_NUM2;
        case VK_NUMPAD3: return PAX_KEYBD_BUTTON_NUM3;
        case VK_NUMPAD4: return PAX_KEYBD_BUTTON_NUM4;
        case VK_NUMPAD5: return PAX_KEYBD_BUTTON_NUM5;
        case VK_NUMPAD6: return PAX_KEYBD_BUTTON_NUM6;
        case VK_NUMPAD7: return PAX_KEYBD_BUTTON_NUM7;
        case VK_NUMPAD8: return PAX_KEYBD_BUTTON_NUM8;
        case VK_NUMPAD9: return PAX_KEYBD_BUTTON_NUM9;

        case VK_SPACE:  return PAX_KEYBD_BUTTON_SPACE;
        case VK_RETURN: return PAX_KEYBD_BUTTON_ENTER;
        case VK_TAB:    return PAX_KEYBD_BUTTON_TAB;
        case VK_ESCAPE: return PAX_KEYBD_BUTTON_ESCAPE;
        case VK_BACK:   return PAX_KEYBD_BUTTON_BACKSPACE;
        case VK_DELETE: return PAX_KEYBD_BUTTON_DELETE;
        case VK_INSERT: return PAX_KEYBD_BUTTON_INSERT;
        case VK_HOME:   return PAX_KEYBD_BUTTON_HOME;
        case VK_END:    return PAX_KEYBD_BUTTON_END;
        case VK_PRIOR:  return PAX_KEYBD_BUTTON_PAGE_UP;
        case VK_NEXT:   return PAX_KEYBD_BUTTON_PAGE_DOWN;

        case VK_LEFT:  return PAX_KEYBD_BUTTON_LEFT;
        case VK_RIGHT: return PAX_KEYBD_BUTTON_RIGHT;
        case VK_UP:    return PAX_KEYBD_BUTTON_UP;
        case VK_DOWN:  return PAX_KEYBD_BUTTON_DOWN;

        case VK_LSHIFT:   return PAX_KEYBD_BUTTON_SHIFT_LEFT;
        case VK_RSHIFT:   return PAX_KEYBD_BUTTON_SHIFT_RIGHT;
        case VK_LCONTROL: return PAX_KEYBD_BUTTON_CTRL_LEFT;
        case VK_RCONTROL: return PAX_KEYBD_BUTTON_CTRL_RIGHT;
        case VK_LMENU:    return PAX_KEYBD_BUTTON_ALT_LEFT;
        case VK_RMENU:    return PAX_KEYBD_BUTTON_ALT_RIGHT;

        default: break;
    }

    return PAX_KEYBD_BUTTON_NONE;
}

LRESULT CALLBACK
pax_windows_display_proc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    Pax_Windows_Display* self = pax_as(Pax_Windows_Display*,
        GetWindowLongPtr(handle, GWLP_USERDATA));

    switch (kind) {
        case WM_ERASEBKGND: return 1;

        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_SIZE: {
            if (self != 0) {
                self->width  = LOWORD(lparam);
                self->height = HIWORD(lparam);

                InvalidateRect(handle, 0, FALSE);
            }
        } break;

        case WM_PAINT: {
            PAINTSTRUCT paint = {0};
            HBRUSH      brush = pax_as(HBRUSH, GetStockObject(BLACK_BRUSH));

            HDC  context = BeginPaint(handle, &paint);
            RECT surface = {0, 0, self->width, self->height};

            if (self->buffer != 0) {
                Pax_Windows_Display_Buffer* buffer = self->buffer;

                StretchBlt(context, 0, 0, self->width, self->height,
                    buffer->context, 0, 0, buffer->width, buffer->height, SRCCOPY);
            } else
                FillRect(context, &surface, brush);

            EndPaint(handle, &paint);
        } break;

        default:
            return DefWindowProcW(handle, kind, wparam, lparam);
    }

    return 0;
}

Pax_Windows_Display*
pax_windows_display_create(Pax_Arena* arena, Pax_String8 name)
{
    wchar_t* class_name = pax_as(wchar_t*, PAX_WINDOW_CLASS.memory);

    paxiword mark = pax_arena_tell(arena);

    Pax_Windows_Display* result =
        pax_arena_reserve(arena, Pax_Windows_Display, 1);

    if (result != 0) {
        paxiword     offset = pax_arena_tell(arena) - mark;
        Pax_String16 string = pax_string16_copy_string8(arena, name);

        if (string.length > 0) {
            wchar_t* memory = pax_as(wchar_t*, string.memory);

            result->instance = GetModuleHandle(0);
            result->width    = PAX_WINDOWS_DISPLAY_WIDTH;
            result->height   = PAX_WINDOWS_DISPLAY_HEIGHT;

            WNDCLASSW temp = {
                .style         = CS_HREDRAW | CS_VREDRAW,
                .lpfnWndProc   = &pax_windows_display_proc,
                .hInstance     = result->instance,
                .lpszClassName = class_name,
                .hbrBackground = 0,
            };

            if (RegisterClassW(&temp) != 0) {
                RECT surface = {0, 0, result->width, result->height};

                AdjustWindowRect(&surface, 0, 0);

                result->handle = CreateWindowExW(0, class_name, memory,
                    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                    surface.right, surface.bottom, 0, 0, result->instance, 0);

                pax_arena_rewind(arena, mark, offset);

                if (result->handle != 0) {
                    SetWindowLongPtr(result->handle,
                        GWLP_USERDATA, pax_as(LONG_PTR, result));

                    return result;
                }

                UnregisterClassW(class_name, result->instance);
            }
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_windows_display_destroy(Pax_Windows_Display* self)
{
    wchar_t* class_name =
        pax_as(wchar_t*, PAX_WINDOW_CLASS.memory);

    if (self == 0) return;

    DestroyWindow(self->handle);

    UnregisterClassW(class_name, self->instance);

    self->handle   = 0;
    self->instance = 0;
}

void
pax_windows_display_flush(Pax_Windows_Display* self, Pax_Windows_Display_Buffer* buffer)
{
    if (buffer != 0)
        self->buffer = buffer;

    InvalidateRect(self->handle, 0, FALSE);
}

paxb8
pax_windows_display_poll_message(Pax_Windows_Display* self, Pax_Display_Message* value)
{
    Pax_Display_Message temp    = {0};
    MSG                 message = {0};

    paxb8 valid = 0;

    while (PeekMessageW(&message, 0, 0, 0, PM_REMOVE) != 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        switch (message.message) {
            case WM_QUIT: {
                temp  = pax_display_message_close();
                valid = 1;
            } break;

            case WM_KEYUP:
            case WM_KEYDOWN: {
                Pax_Keybd_Button button =
                    pax_windows_map_keybd_button(message.wParam);

                paxb8    down = message.message == WM_KEYDOWN ? 1 : 0;
                paxiword scan = pax_as(paxiword, (message.lParam >> 16) & 0xff);

                temp  = pax_display_message_keybd_button(button, down, scan);
                valid = 1;
            } break;

            case WM_LBUTTONUP:
            case WM_LBUTTONDOWN: {
                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_LEFT;

                paxb8 down = message.message == WM_LBUTTONDOWN ? 1 : 0;

                temp  = pax_display_message_mouse_button(button, down);
                valid = 1;
            } break;

            case WM_MBUTTONUP:
            case WM_MBUTTONDOWN: {
                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_MIDDLE;

                paxb8 down = message.message == WM_MBUTTONDOWN ? 1 : 0;

                temp  = pax_display_message_mouse_button(button, down);
                valid = 1;
            } break;

            case WM_RBUTTONUP:
            case WM_RBUTTONDOWN: {
                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_RIGHT;

                paxb8 down = message.message == WM_RBUTTONDOWN ? 1 : 0;

                temp  = pax_display_message_mouse_button(button, down);
                valid = 1;
            } break;

            default: break;
        }

        if (valid != 0) {
            if (value != 0)
                *value = temp;

            return 1;
        }
    }

    return 0;
}

paxb8
pax_windows_display_set_visibility(Pax_Windows_Display *self, Pax_Display_Visibility visibility)
{
    int command = 0;

    switch (visibility) {
        case PAX_DISPLAY_VISIBILITY_SHOW:   command = SW_SHOW;     break;
        case PAX_DISPLAY_VISIBILITY_HIDE:   command = SW_HIDE;     break;
        case PAX_DISPLAY_VISIBILITY_EXPAND: command = SW_MAXIMIZE; break;
        case PAX_DISPLAY_VISIBILITY_REDUCE: command = SW_MINIMIZE; break;
        case PAX_DISPLAY_VISIBILITY_CLEAR:  command = SW_RESTORE;  break;

        default: break;
    }

    if (command == 0) return 0;

    ShowWindow(self->handle, command);

    return 1;
}

Pax_Windows_Display_Buffer*
pax_windows_display_buffer_create(Pax_Windows_Display* self, Pax_Arena* arena, paxiword width, paxiword height)
{
    if (self == 0 || width <= 0 || height <= 0) return 0;

    paxiword mark   = pax_arena_tell(arena);
    paxiword length = width * height;
    paxiword stride = pax_size(paxu32);

    Pax_Windows_Display_Buffer* result =
        pax_arena_reserve(arena, Pax_Windows_Display_Buffer, 1);

    if (result != 0) {
        BITMAPINFO info   = {0};
        HDC        screen = GetDC(0);

        info.bmiHeader.biSize        = pax_size(BITMAPINFOHEADER);
        info.bmiHeader.biWidth       = width;
        info.bmiHeader.biHeight      = -height;
        info.bmiHeader.biPlanes      = 1;
        info.bmiHeader.biBitCount    = stride * 8;
        info.bmiHeader.biCompression = BI_RGB;

        result->bitmap = CreateDIBSection(screen, &info,
            DIB_RGB_COLORS, pax_as(void**, &result->memory), 0, 0);

        ReleaseDC(0, screen);

        if (result->bitmap != 0 && result->memory != 0) {
            result->context = CreateCompatibleDC(0);

            if (result->context != 0) {
                SelectObject(result->context, result->bitmap);

                result->width  = width;
                result->height = height;
                result->stride = stride;

                Pax_Slice slice = pax_slice_make(
                    result->memory, length, stride);

                pax_slice_zero(slice);

                return result;
            }
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_windows_display_buffer_destroy(Pax_Windows_Display_Buffer* self)
{
    if (self == 0) return;

    if (self->context == 0 || self->bitmap == 0)
        return;

    DeleteObject(self->bitmap);
    DeleteDC(self->context);

    self->bitmap  = 0;
    self->context = 0;
}

paxiword
pax_windows_display_buffer_length(Pax_Windows_Display_Buffer* self)
{
    return self->width * self->height;
}

paxiword
pax_windows_display_buffer_width(Pax_Windows_Display_Buffer* self)
{
    return self->width;
}

paxiword
pax_windows_display_buffer_height(Pax_Windows_Display_Buffer* self)
{
    return self->height;
}

paxiword
pax_windows_display_buffer_stride(Pax_Windows_Display_Buffer* self)
{
    return self->stride;
}

paxb8
pax_windows_display_buffer_write(Pax_Windows_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b, paxu8 a)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    self->memory[self->stride * index + 0] = b;
    self->memory[self->stride * index + 1] = g;
    self->memory[self->stride * index + 2] = r;
    self->memory[self->stride * index + 3] = a;

    return 1;
}

paxb8
pax_windows_display_buffer_read(Pax_Windows_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b, paxu8* a)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    if (b != 0) *b = self->memory[self->stride * index + 0];
    if (g != 0) *g = self->memory[self->stride * index + 1];
    if (r != 0) *r = self->memory[self->stride * index + 2];
    if (a != 0) *a = self->memory[self->stride * index + 3];

    return 1;
}

#endif // PAX_WINDOWS_DISPLAY_DISPLAY_C
