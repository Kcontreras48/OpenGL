#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    // Inicializar GLFW
    glfwInit();

    // Decirle a GLFW qué versión de OpenGL estamos usando (en este caso 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Decirle a GLFW que usaremos el perfil CORE (solo funciones modernas)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear un objeto GLFWwindow de 800 por 800 píxeles
    GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

    // Comprobación de errores por si la ventana falla al crearse
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Introducir la ventana en el contexto actual
    glfwMakeContextCurrent(window);

    // Bucle principal (mantiene la ventana abierta hasta que se pulse el botón de cerrar)
    while (!glfwWindowShouldClose(window))
    {
        // Procesa todos los eventos (como redimensionar la ventana o clics)
        glfwPollEvents();
    }

    // Eliminar la ventana antes de finalizar el programa
    glfwDestroyWindow(window);

    // Terminar GLFW antes de que acabe la función main
    glfwTerminate();

    return 0;
}