#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Código fuente del Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Código fuente del Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

    /* Colorear la ventana
    glClearColor(0.19f, 0.58f, 0.70f, 1.0f); // Prepara el color en RGBA de 0 a 1 ; https://rgbcolorpicker.com/0-1
    glClear(GL_COLOR_BUFFER_BIT); // Limpia la pantalla usando nuestro color
    glfwSwapBuffers(window); // Hace un cambio entre el lienzo oculto y el visible
    */

    // Crea el objeto Vertex Shader y obtiene su referencia
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Asigna el código fuente al objeto Vertex Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compila el Vertex Shader a código máquina
    glCompileShader(vertexShader);

    // Crea el objeto Fragment Shader y obtiene su referencia
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Asigna el código fuente al objeto Fragment Shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compila el Fragment Shader a código máquina
    glCompileShader(fragmentShader);

    // Crea el objeto Shader Program y obtiene su referencia
    GLuint shaderProgram = glCreateProgram();
    // Adjunta los Vertex y Fragment Shaders al Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Enlaza todos los shaders en el Shader Program
    glLinkProgram(shaderProgram);

    // Elimina los objetos Vertex y Fragment Shader que ya no se usan
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Coordenadas de los vértices
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior izquierda
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Esquina inferior derecha
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Esquina superior
    };

    // Crea los contenedores de referencia para el VAO (Vertex Array Object) y el VBO (Vertex Buffer Object)
    GLuint VAO, VBO;

    // Genera el VAO y el VBO con 1 solo objeto cada uno
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Convierte el VAO en el objeto actual al vincularlo
    glBindVertexArray(VAO);

    // Vincula el VBO especificando que es un GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce los vértices en el VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configura el Atributo de Vértice para que OpenGL sepa cómo leer el VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Habilita el Atributo de Vértice para que OpenGL lo use
    glEnableVertexAttribArray(0);

    // Desvincula el VBO y VAO (pasando 0) para evitar modificaciones accidentales
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) // Este es el ciclo principal, esto mantiene todos los gráficos hasta el cierre de la ventana
    {
        // Especifica el color de fondo
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Limpia el buffer trasero y le asigna el color nuevo
        glClear(GL_COLOR_BUFFER_BIT);
        // Indica a OpenGL cuál Shader Program usar
        glUseProgram(shaderProgram);
        // Vincula el VAO para indicarle a OpenGL que lo use
        glBindVertexArray(VAO);
        // Dibuja el triángulo usando la primitiva GL_TRIANGLES
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Intercambia el buffer trasero con el delantero
        glfwSwapBuffers(window);
        // Procesa todos los eventos de GLFW
        glfwPollEvents();
    }

    // Limpia la memoria destruyendo la ventana y terminando los procesos de GLFW
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Elimina la ventana antes de terminar el programa
    glfwDestroyWindow(window);
    // Termina los procesos de GLFW antes de finalizar el programa
    glfwTerminate();
    return 0;
}