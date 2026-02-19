#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    glfwInit(); // Inicializa la librería GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Información sobre la versión y el perfil a usar

    GLFWwindow* window = glfwCreateWindow(800, 800, "Ventana Bonita", NULL, NULL); // Reserva memoria y crea la ventana

    if (window == NULL) // Finaliza el programa de forma correcta en caso de un error
    {
        std::cout << "Fallo crear GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Indica en qué ventana se va a trabajar

    gladLoadGL(); // Carga los punteros de las funciones de OpenGL proporcionados por la GPU

    glViewport(0, 0, 800, 800); // Define el área de la ventana donde OpenGL va a dibujar

    glClearColor(0.6f, 0.1f, 0.8f, 1.0f); // Prepara el color en RGBA de 0 a 1 ; https://rgbcolorpicker.com/0-1
    glClear(GL_COLOR_BUFFER_BIT); // Limpia la pantalla usando nuestro color
    glfwSwapBuffers(window); // Hace un cambio entre el lienzo oculto y el visible

    while (!glfwWindowShouldClose(window)) // Este es el ciclo principal, esto mantiene todos los gráficos hasta el cierre de la ventana
    {
        glfwPollEvents(); // Procesa los eventos del sistema operativo (clics, teclas presionadas, mover la ventana)
    }

    // Limpia la memoria destruyendo la ventana y terminando los procesos de GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}