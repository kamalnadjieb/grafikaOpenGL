#include <windows.h>
#include <gl/gl.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Pemandangan",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          500,
                          500,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit) {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            /* OpenGL animation code goes here */

            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            //glRotatef(theta, 0.0f, 0.0f, 1.0f);

            // Gambar Langit
            glBegin(GL_QUADS);
                glColor3f(0, 0, 1);
                glVertex2f(-1, 1);
                glVertex2f(1, 1);

                glColor3f(1, 1, 1);
                glVertex2f(1, -1);
                glVertex2f(-1, -1);
            glEnd();

            // Gambar Matahari
            int triangleAmount = 20; //# of triangles used to draw circle
            const float PI = 3.14;
            GLfloat twicePi = 2.0f * PI;
            GLfloat xinit = 0; // center of circle
            GLfloat yinit = 0.5; // center of circle
            GLfloat radius = 0.25; // radius of circle

            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1, 0, 0);
                glVertex2f(xinit, yinit); // center of circle
                glColor3f(1, 1, 0);
                int i;
                for (i = 0; i <= triangleAmount; i++) {
                    glVertex2f(xinit + (radius * cos(i *  twicePi / triangleAmount)), yinit + (radius * sin(i * twicePi / triangleAmount)));
                }
            glEnd();
            

            // Gambar sinar matahari (belum selesai)
            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(-0.3, 0.45, 0);
                glVertex3f(-0.3, 0.55, 0);
                glVertex3f(-0.375, 0.5, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(0.3, 0.45, 0);
                glVertex3f(0.3, 0.55, 0);
                glVertex3f(0.375, 0.5, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(-0.05, 0.8, 0);
                glVertex3f(0.05, 0.8, 0);
                glVertex3f(0, 0.875, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(-0.05, -0.8, 0);
                glVertex3f(0.05, -0.8, 0);
                glVertex3f(0, -0.875, 0);
            glEnd();


            //Gambar Pelangi
            glBegin(GL_LINE_STRIP);
                double x, y, r;
                double start_angle = 0;
                double end_angle = PI;
                double max_angle = 2 * PI;
                double angle_increment = PI / 1000;
                double theta;
                for (r = .05; r <= .3; r += .05) {
                    for (theta = start_angle; theta < end_angle; theta += angle_increment)
                    {
                        x = r * cos (theta);
                        y = r * sin (theta);
                        if (r == .05) {
                            glColor3f(1,0,1);
                        } else if (r == .10) {
                            glColor3f(0,0,1);
                        } else if (r == .2) {
                            glColor3f(0,1,0);
                        } else if (r == .25) {
                            glColor3f(1,1,0);
                        } else if (r == .3) {
                            glColor3f(1,0,0);
                        } else {
                            glColor3f(0,1,1);
                        }

                        glVertex2f(x + r * cos (theta), y - .5 + r * sin (theta));

                        if (r == .05) {
                            glVertex2f(x + (r - .05) * cos (theta), y - .5 + (r - .05) * sin (theta));
                        } else {
                            glVertex2f(x + (r - .1) * cos (theta), y - .5 + (r - .1) * sin (theta));
                        }
                    }

                }
            glEnd();

            // Gambar Gunung 1
            glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex2f(-1.25, -1);
                glVertex2f(0.25, -1);

                glColor3f(1, 1, 1);
                glVertex2f(-0.5, 0);
            glEnd();

            // Gambar Gunung 2
            glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex2f(-0.25, -1);
                glVertex2f(1.25, -1);

                glColor3f(1, 1, 1);
                glVertex2f(0.5, 0);
            glEnd();

            // Gambar Pohon 1
            // Batang pohon
            glBegin(GL_QUADS);
                glColor3f(0.73, 0.48, 0.34);
                glVertex2f(0.84, -0.8);
                glVertex2f(0.9, -0.8);
                glVertex2f(0.9, -1);
                glVertex2f(0.84, -1);
            glEnd();

            // Gambar daun
            glBegin(GL_POLYGON);
                glColor3f(0.13, 0.69, 0.3);
                glVertex2f(0.74, -0.76);
                glVertex2f(0.76, -0.74);
                glVertex2f(0.74, -0.74);
                glVertex2f(0.87, -0.68);
                glVertex2f(1, -0.74);
                glVertex2f(0.98, -0.74);
                glVertex2f(1, -0.76);

                glColor3f(0.16, 0.82, 0.35);
                glVertex2f(0.98, -0.76);
                glVertex2f(1, -0.78);
                glVertex2f(0.98, -0.78);
                glVertex2f(1, -0.8);
                glVertex2f(0.74, -0.8);
                glVertex2f(0.76, -0.78);
                glVertex2f(0.74, -0.78);
                glVertex2f(0.76, -0.76);
            glEnd();

            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

