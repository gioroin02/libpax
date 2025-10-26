#ifndef PAX_XORG_DISPLAY_DISPLAY_C
#define PAX_XORG_DISPLAY_DISPLAY_C

#include "./display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>

#define PAX_XORG_DISPLAY_WIDTH  800
#define PAX_XORG_DISPLAY_HEIGHT 600

struct Pax_Xorg_Display
{
    Display *display;
    Window   window;
    int      screen;

    Atom     wm_delete_window;

    Pax_Xorg_Display_Buffer* buffer;

    paxiword width;
    paxiword height;
};

struct Pax_Xorg_Display_Buffer
{
    XImage*  image;
    paxu8*   memory;
    paxiword width;
    paxiword height;
    paxiword stride;
};

static Pax_Keybd_Button
pax_xorg_map_keybd_button(KeySym value)
{
    switch (value) {
        case XK_a: return PAX_KEYBD_BUTTON_A;
        case XK_b: return PAX_KEYBD_BUTTON_B;
        case XK_c: return PAX_KEYBD_BUTTON_C;
        case XK_d: return PAX_KEYBD_BUTTON_D;
        case XK_e: return PAX_KEYBD_BUTTON_E;
        case XK_f: return PAX_KEYBD_BUTTON_F;
        case XK_g: return PAX_KEYBD_BUTTON_G;
        case XK_h: return PAX_KEYBD_BUTTON_H;
        case XK_i: return PAX_KEYBD_BUTTON_I;
        case XK_j: return PAX_KEYBD_BUTTON_J;
        case XK_k: return PAX_KEYBD_BUTTON_K;
        case XK_l: return PAX_KEYBD_BUTTON_L;
        case XK_m: return PAX_KEYBD_BUTTON_M;
        case XK_n: return PAX_KEYBD_BUTTON_N;
        case XK_o: return PAX_KEYBD_BUTTON_O;
        case XK_p: return PAX_KEYBD_BUTTON_P;
        case XK_q: return PAX_KEYBD_BUTTON_Q;
        case XK_r: return PAX_KEYBD_BUTTON_R;
        case XK_s: return PAX_KEYBD_BUTTON_S;
        case XK_t: return PAX_KEYBD_BUTTON_T;
        case XK_u: return PAX_KEYBD_BUTTON_U;
        case XK_v: return PAX_KEYBD_BUTTON_V;
        case XK_w: return PAX_KEYBD_BUTTON_W;
        case XK_x: return PAX_KEYBD_BUTTON_X;
        case XK_y: return PAX_KEYBD_BUTTON_Y;
        case XK_z: return PAX_KEYBD_BUTTON_Z;

        case XK_A: return PAX_KEYBD_BUTTON_A;
        case XK_B: return PAX_KEYBD_BUTTON_B;
        case XK_C: return PAX_KEYBD_BUTTON_C;
        case XK_D: return PAX_KEYBD_BUTTON_D;
        case XK_E: return PAX_KEYBD_BUTTON_E;
        case XK_F: return PAX_KEYBD_BUTTON_F;
        case XK_G: return PAX_KEYBD_BUTTON_G;
        case XK_H: return PAX_KEYBD_BUTTON_H;
        case XK_I: return PAX_KEYBD_BUTTON_I;
        case XK_J: return PAX_KEYBD_BUTTON_J;
        case XK_K: return PAX_KEYBD_BUTTON_K;
        case XK_L: return PAX_KEYBD_BUTTON_L;
        case XK_M: return PAX_KEYBD_BUTTON_M;
        case XK_N: return PAX_KEYBD_BUTTON_N;
        case XK_O: return PAX_KEYBD_BUTTON_O;
        case XK_P: return PAX_KEYBD_BUTTON_P;
        case XK_Q: return PAX_KEYBD_BUTTON_Q;
        case XK_R: return PAX_KEYBD_BUTTON_R;
        case XK_S: return PAX_KEYBD_BUTTON_S;
        case XK_T: return PAX_KEYBD_BUTTON_T;
        case XK_U: return PAX_KEYBD_BUTTON_U;
        case XK_V: return PAX_KEYBD_BUTTON_V;
        case XK_W: return PAX_KEYBD_BUTTON_W;
        case XK_X: return PAX_KEYBD_BUTTON_X;
        case XK_Y: return PAX_KEYBD_BUTTON_Y;
        case XK_Z: return PAX_KEYBD_BUTTON_Z;

        case XK_0: return PAX_KEYBD_BUTTON_ZERO;
        case XK_1: return PAX_KEYBD_BUTTON_ONE;
        case XK_2: return PAX_KEYBD_BUTTON_TWO;
        case XK_3: return PAX_KEYBD_BUTTON_THREE;
        case XK_4: return PAX_KEYBD_BUTTON_FOUR;
        case XK_5: return PAX_KEYBD_BUTTON_FIVE;
        case XK_6: return PAX_KEYBD_BUTTON_SIX;
        case XK_7: return PAX_KEYBD_BUTTON_SEVEN;
        case XK_8: return PAX_KEYBD_BUTTON_EIGHT;
        case XK_9: return PAX_KEYBD_BUTTON_NINE;

        case XK_F1:  return PAX_KEYBD_BUTTON_F1;
        case XK_F2:  return PAX_KEYBD_BUTTON_F2;
        case XK_F3:  return PAX_KEYBD_BUTTON_F3;
        case XK_F4:  return PAX_KEYBD_BUTTON_F4;
        case XK_F5:  return PAX_KEYBD_BUTTON_F5;
        case XK_F6:  return PAX_KEYBD_BUTTON_F6;
        case XK_F7:  return PAX_KEYBD_BUTTON_F7;
        case XK_F8:  return PAX_KEYBD_BUTTON_F8;
        case XK_F9:  return PAX_KEYBD_BUTTON_F9;
        case XK_F10: return PAX_KEYBD_BUTTON_F10;
        case XK_F11: return PAX_KEYBD_BUTTON_F11;
        case XK_F12: return PAX_KEYBD_BUTTON_F12;

        case XK_KP_0: return PAX_KEYBD_BUTTON_NUM0;
        case XK_KP_1: return PAX_KEYBD_BUTTON_NUM1;
        case XK_KP_2: return PAX_KEYBD_BUTTON_NUM2;
        case XK_KP_3: return PAX_KEYBD_BUTTON_NUM3;
        case XK_KP_4: return PAX_KEYBD_BUTTON_NUM4;
        case XK_KP_5: return PAX_KEYBD_BUTTON_NUM5;
        case XK_KP_6: return PAX_KEYBD_BUTTON_NUM6;
        case XK_KP_7: return PAX_KEYBD_BUTTON_NUM7;
        case XK_KP_8: return PAX_KEYBD_BUTTON_NUM8;
        case XK_KP_9: return PAX_KEYBD_BUTTON_NUM9;

        case XK_space:      return PAX_KEYBD_BUTTON_SPACE;
        case XK_Return:     return PAX_KEYBD_BUTTON_ENTER;
        case XK_Tab:        return PAX_KEYBD_BUTTON_TAB;
        case XK_Escape:     return PAX_KEYBD_BUTTON_ESCAPE;
        case XK_BackSpace:  return PAX_KEYBD_BUTTON_BACKSPACE;
        case XK_Delete:     return PAX_KEYBD_BUTTON_DELETE;
        case XK_Insert:     return PAX_KEYBD_BUTTON_INSERT;
        case XK_Home:       return PAX_KEYBD_BUTTON_HOME;
        case XK_End:        return PAX_KEYBD_BUTTON_END;
        case XK_Page_Up:    return PAX_KEYBD_BUTTON_PAGE_UP;
        case XK_Page_Down:  return PAX_KEYBD_BUTTON_PAGE_DOWN;

        case XK_Left:  return PAX_KEYBD_BUTTON_LEFT;
        case XK_Right: return PAX_KEYBD_BUTTON_RIGHT;
        case XK_Up:    return PAX_KEYBD_BUTTON_UP;
        case XK_Down:  return PAX_KEYBD_BUTTON_DOWN;

        case XK_Shift_L:   return PAX_KEYBD_BUTTON_SHIFT_LEFT;
        case XK_Shift_R:   return PAX_KEYBD_BUTTON_SHIFT_RIGHT;
        case XK_Control_L: return PAX_KEYBD_BUTTON_CTRL_LEFT;
        case XK_Control_R: return PAX_KEYBD_BUTTON_CTRL_RIGHT;
        case XK_Alt_L:     return PAX_KEYBD_BUTTON_ALT_LEFT;
        case XK_Alt_R:     return PAX_KEYBD_BUTTON_ALT_RIGHT;

        default: break;
    }

    return PAX_KEYBD_BUTTON_NONE;
}

Pax_Xorg_Display*
pax_xorg_display_create(Pax_Arena* arena, Pax_String8 name)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Xorg_Display* result =
        pax_arena_reserve(arena, Pax_Xorg_Display, 1);

    if (result != 0 && name.length > 0) {
        result->display = XOpenDisplay(NULL);

        if (result->display != 0) {
            result->screen = DefaultScreen(result->display);
            result->width  = PAX_XORG_DISPLAY_WIDTH;
            result->height = PAX_XORG_DISPLAY_HEIGHT;

            result->window = XCreateSimpleWindow(result->display,
                RootWindow(result->display, result->screen), 0, 0, result->width, result->height, 1,
                BlackPixel(result->display, result->screen), BlackPixel(result->display, result->screen));

            if (result->window != 0) {
                XSetWindowAttributes attrib;

                attrib.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                    ButtonPressMask | ButtonReleaseMask | StructureNotifyMask;

                XSelectInput(result->display, result->window, attrib.event_mask);
                XStoreName(result->display, result->window, name.memory);

                XChangeWindowAttributes(result->display, result->window,
                    CWEventMask, &attrib);

                result->wm_delete_window = XInternAtom(result->display, "WM_DELETE_WINDOW", False);

                XSetWMProtocols(result->display, result->window, &result->wm_delete_window, 1);

                return result;
            }
        }

        XCloseDisplay(result->display);
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_xorg_display_destroy(Pax_Xorg_Display* self)
{
    if (self == 0) return;

    XDestroyWindow(self->display, self->window);
    XCloseDisplay(self->display);

    self->display = 0;
    self->window  = 0;
}

void
pax_xorg_display_flush(Pax_Xorg_Display* self, Pax_Xorg_Display_Buffer* buffer)
{
    if (buffer != 0) self->buffer = buffer;

    if (self->buffer != 0) {
        GC context = DefaultGC(self->display, self->screen);

        XPutImage(self->display, self->window, context,
            self->buffer->image, 0, 0, 0, 0, self->width, self->height);
    }

    XFlush(self->display);
}

paxb8
pax_xorg_display_poll_message(Pax_Xorg_Display* self, Pax_Display_Message* value)
{
    Pax_Display_Message temp  = {0};
    XEvent              event = {0};
    paxb8               valid = 0;

    while (XPending(self->display) > 0) {
        XNextEvent(self->display, &event);

        switch (event.type) {
            case ClientMessage: {
                long item = event.xclient.data.l[0];

                if (item == pax_as(long, self->wm_delete_window)) {
                    temp  = pax_display_message_close();
                    valid = 1;
                }
            } break;

            case ConfigureNotify: {
                self->width  = event.xconfigure.width;
                self->height = event.xconfigure.height;
            } break;

            case Expose:
                pax_xorg_display_flush(self, 0);
            break;

            case KeyPress:
            case KeyRelease: {
                KeySym keysym = XLookupKeysym(&event.xkey, 0);

                Pax_Keybd_Button button = pax_xorg_map_keybd_button(keysym);
                paxb8            down   = (event.type == KeyPress) ? 1 : 0;
                paxiword         scan   = event.xkey.keycode;

                temp  = pax_display_message_keybd_button(button, down, scan);
                valid = 1;
            } break;

            case ButtonPress:
            case ButtonRelease: {
                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_NONE;
                paxb8            down   = (event.type == ButtonPress) ? 1 : 0;

                switch (event.xbutton.button) {
                    case Button1: button = PAX_MOUSE_BUTTON_LEFT;   break;
                    case Button2: button = PAX_MOUSE_BUTTON_MIDDLE; break;
                    case Button3: button = PAX_MOUSE_BUTTON_RIGHT;  break;

                    default: break;
                }

                if (button != PAX_MOUSE_BUTTON_NONE) {
                    temp  = pax_display_message_mouse_button(button, down);
                    valid = 1;
                }
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
pax_xorg_display_set_visibility(Pax_Xorg_Display *self, Pax_Display_Visibility visibility)
{
    switch (visibility) {
        case PAX_DISPLAY_VISIBILITY_SHOW:
            XMapWindow(self->display, self->window);
        break;

        case PAX_DISPLAY_VISIBILITY_HIDE:
            XUnmapWindow(self->display, self->window);
        break;

        case PAX_DISPLAY_VISIBILITY_EXPAND: {
            XEvent event = {0};

            event.type                 = ClientMessage;
            event.xclient.window       = self->window;
            event.xclient.message_type = XInternAtom(self->display, "_NET_WM_STATE", False);
            event.xclient.format       = 32;
            event.xclient.data.l[0]    = 1;
            event.xclient.data.l[1]    = XInternAtom(self->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            event.xclient.data.l[2]    = XInternAtom(self->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            event.xclient.data.l[3]    = 0;
            event.xclient.data.l[4]    = 0;

            XSendEvent(self->display, DefaultRootWindow(self->display),
                False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        } break;

        case PAX_DISPLAY_VISIBILITY_REDUCE:
            XIconifyWindow(self->display, self->window, self->screen);
        break;

        case PAX_DISPLAY_VISIBILITY_CLEAR: {
            XEvent event = {0};

            event.type                 = ClientMessage;
            event.xclient.window       = self->window;
            event.xclient.message_type = XInternAtom(self->display, "_NET_WM_STATE", False);
            event.xclient.format       = 32;
            event.xclient.data.l[0]    = 0;
            event.xclient.data.l[1]    = XInternAtom(self->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            event.xclient.data.l[2]    = XInternAtom(self->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            event.xclient.data.l[3]    = 0;
            event.xclient.data.l[4]    = 0;

            XSendEvent(self->display, DefaultRootWindow(self->display),
                False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        } break;

        default: return 0;
    }

    XFlush(self->display);

    return 1;
}

Pax_Xorg_Display_Buffer*
pax_xorg_display_buffer_create(Pax_Xorg_Display* self, Pax_Arena* arena, paxiword width, paxiword height)
{
    if (width <= 0 || height <= 0) return 0;

    paxiword mark   = pax_arena_tell(arena);
    paxiword length = width * height;
    paxiword stride = pax_size(paxu32);

    Pax_Xorg_Display_Buffer* result =
        pax_arena_reserve(arena, Pax_Xorg_Display_Buffer, 1);

    if (result != 0) {
        Visual* visual = DefaultVisual(self->display, self->screen);
        int     depth  = DefaultDepth(self->display, self->screen);

        result->image = XCreateImage(self->display, visual, depth, ZPixmap, 0,
            (char*)result->memory, width, height, 32, width * stride);

        result->memory = pax_arena_reserve_memory(arena, length, stride);

        if (result->memory != 0 && result->image != 0) {
            result->width  = width;
            result->height = height;
            result->stride = stride;

            Pax_Slice slice = pax_slice_make(
                result->memory, length, stride);

            pax_slice_zero(slice);

            return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_xorg_display_buffer_destroy(Pax_Xorg_Display_Buffer* self)
{
    if (self == 0) return;

    XDestroyImage(self->image);

    self->memory = 0;
    self->image  = 0;
}

paxiword
pax_xorg_display_buffer_length(Pax_Xorg_Display_Buffer* self)
{
    return self->width * self->height;
}

paxiword
pax_xorg_display_buffer_width(Pax_Xorg_Display_Buffer* self)
{
    return self->width;
}

paxiword
pax_xorg_display_buffer_height(Pax_Xorg_Display_Buffer* self)
{
    return self->height;
}

paxiword
pax_xorg_display_buffer_stride(Pax_Xorg_Display_Buffer* self)
{
    return self->stride;
}

paxb8
pax_xorg_display_buffer_write(Pax_Xorg_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b, paxu8 a)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    self->memory[self->stride * index + 0] = r;
    self->memory[self->stride * index + 1] = g;
    self->memory[self->stride * index + 2] = b;
    self->memory[self->stride * index + 3] = a;

    return 1;
}

paxb8
pax_xorg_display_buffer_read(Pax_Xorg_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b, paxu8* a)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    if (r != 0) *r = self->memory[self->stride * index + 0];
    if (g != 0) *g = self->memory[self->stride * index + 1];
    if (b != 0) *b = self->memory[self->stride * index + 2];
    if (a != 0) *a = self->memory[self->stride * index + 3];

    return 1;
}

#endif // PAX_XORG_DISPLAY_DISPLAY_C
