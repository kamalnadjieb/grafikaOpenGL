#include <windows.h>
#include <gl/gl.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void DrawTree(GLfloat xtrans, GLfloat ytrans);

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

            //Gambar Pelangi
            GLfloat dx = -0.85;
            GLfloat dy = -1;
            GLfloat w = 0.1;
            GLfloat step = 0.05;
            for (i = 0; i < 100; i++) {
              glBegin(GL_QUAD_STRIP);

              glColor3f(1,0,0); //Red
              glVertex2f(dx,dy);
              glVertex2f(dx+w,dy+w);

              glColor3f(1,0.6,0); //Orange
              glVertex2f(dx+step,dy-step);
              glVertex2f(dx+w+step,dy+w-step);

              glColor3f(1,1,0);//Yellow
              glVertex2f(dx+step*2,dy-step*2);
              glVertex2f(dx+w+step*2,dy+w-step*2);

              glColor3f(0.2,1,0); //Green
              glVertex2f(dx+step*3,dy-step*3);
              glVertex2f(dx+w+step*3,dy+w-step*3);

              glColor3f(0,0.6,1); //Blue
              glVertex2f(dx+step*4,dy-step*4);
              glVertex2f(dx+w+step*4,dy+w-step*4);

              glColor3f(0.4,0.2,1); //Purple
              glVertex2f(dx+step*5,dy-step*5);
              glVertex2f(dx+w+step*5,dy+w-step*5);
              glEnd();

              dx += w;
              dy += w;
            }

            float rotate_x(float cx, float cy, float angle, float x, float y) {
                float s = sin(angle);
                float c = cos(angle);

                // translate point back to origin:
                x -= cx;
                y -= cy;

                // rotate point
                float xnew = x * c - y * s;
                float ynew = x * s + y * c;

                // translate point back:
                x = xnew + cx;
                y = ynew + cy;

                return x;
            }

            float rotate_y(float cx, float cy, float angle, float x, float y) {
                float s = sin(angle);
                float c = cos(angle);

                // translate point back to origin:
                x -= cx;
                y -= cy;

                // rotate point
                float xnew = x * c - y * s;
                float ynew = x * s + y * c;

                // translate point back:
                x = xnew + cx;
                y = ynew + cy;

                return y;
            }

            // Gambar sinar matahari (belum selesai)
            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(-0.3, 0.45, 0);
                glVertex3f(-0.3, 0.55, 0);
                glVertex3f(-0.375, 0.5, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(rotate_x(0, 0.5, 0.785, -0.05, 0.8), rotate_y(0, 0.5, 0.785, -0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 0.785, 0.05, 0.8), rotate_y(0, 0.5, 0.785, 0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 0.785, 0, 0.875), rotate_y(0, 0.5, 0.785, 0, 0.875), 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(rotate_x(0, 0.5, 2.36, -0.05, 0.8), rotate_y(0, 0.5, 2.36, -0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 2.36, 0.05, 0.8), rotate_y(0, 0.5, 2.36, 0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 2.36, 0, 0.875), rotate_y(0, 0.5, 2.36, 0, 0.875), 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(rotate_x(0, 0.5, 3.93, -0.05, 0.8), rotate_y(0, 0.5, 3.93, -0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 3.93, 0.05, 0.8), rotate_y(0, 0.5, 3.93, 0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 3.93, 0, 0.875), rotate_y(0, 0.5, 3.93, 0, 0.875), 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(rotate_x(0, 0.5, 5.5, -0.05, 0.8), rotate_y(0, 0.5, 5.5, -0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 5.5, 0.05, 0.8), rotate_y(0, 0.5, 5.5, 0.05, 0.8), 0);
                glVertex3f(rotate_x(0, 0.5, 5.5, 0, 0.875), rotate_y(0, 0.5, 5.5, 0, 0.875), 0);
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
                glVertex3f(-0.05, 0.8, 0);
                glVertex3f(0.05, 0.8, 0);
                glVertex3f(0, 0.875, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 0);
                glVertex3f(-0.05, 0.2, 0);
                glVertex3f(0.05, 0.2, 0);
                glVertex3f(0, 0.125, 0);
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

            DrawTree(-0.5, 0);
            DrawTree(-0.25, 0);
            DrawTree(0, 0);
            DrawTree(-1, 0);
            DrawTree(-0.75, 0);
            DrawTree(-1.5, 0);
            DrawTree(-1.25, 0);
            DrawTree(-1.75, 0);

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

void DrawTree(GLfloat xtrans, GLfloat ytrans) {
    // Batang pohon
    glBegin(GL_QUADS);
        glColor3f(0.73, 0.48, 0.34);
        glVertex2f(0.84+xtrans, -0.8+ytrans);
        glVertex2f(0.9+xtrans, -0.8+ytrans);
        glVertex2f(0.9+xtrans, -1+ytrans);
        glVertex2f(0.84+xtrans, -1+ytrans);
    glEnd();

    // Gambar daun
    glBegin(GL_POLYGON);
        glBegin(GL_POLYGON);
        glColor3f(0.13, 0.69, 0.3);
        glVertex2f(0.78+xtrans, -0.76+ytrans);
        glVertex2f(0.74+xtrans, -0.76+ytrans);
        glVertex2f(0.78+xtrans, -0.72+ytrans);
        glVertex2f(0.74+xtrans, -0.72+ytrans);
        glVertex2f(0.78+xtrans, -0.68+ytrans);
        glVertex2f(0.74+xtrans, -0.68+ytrans);
        glVertex2f(0.87+xtrans, -0.5+ytrans);
        glVertex2f(1+xtrans, -0.68+ytrans);
        glVertex2f(0.96+xtrans, -0.68+ytrans);
        glVertex2f(1+xtrans, -0.72+ytrans);
        glVertex2f(0.96+xtrans, -0.72+ytrans);
        glVertex2f(1+xtrans, -0.76+ytrans);
        glVertex2f(0.96+xtrans, -0.76+ytrans);

        glColor3f(0.16+xtrans, 0.82, 0.35);
        glVertex2f(1+xtrans, -0.8+ytrans);
        glVertex2f(0.74+xtrans, -0.8+ytrans);

    glEnd();
}
