// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 0.0f, 45.0f, 50.0f ) ); //posicion inicial de la camara al abrir el viewport
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//Variables flotantes

//Refrigerador
float rot = 0.0f;
float rot2 = 0.0f;
//Estufa
float rot3 = 0.0f;
//Puerta de la casa
float rot4 = 0.0f;
//Cajon del tocador
float cajon = 0.0f;
//Trayectoria del pajarito
float gira = 0.0f;
float Posx = 0.0f;
float Posz = 0.0f;
float aleteo = 0.0f;
//Caida de la pelota
float caidaY = 0.0f; //posicion inicial de la pelota
float caidaX = 0.0f;
float caidaY2 = 0.0f;
float rotPelota = 0.0f;
float caida1 = 0.0f;
//Segundo Cuarto
float ptaizq = 0.0f;
float ptader = 0.0f;
float aire = 0.0f;
float cajon2 = 0.0f;
float tintineo = 0.0f;
float vibracion1X = 0.0f;
float vibracion1Y = 0.0f;
float vibracion2X = 0.0f;
float vibracion2Y = 0.0f;

//Variables booleanas

//Refrigerador
bool anim_refri = false;
bool anim_refri2 = false;
bool refri_1 = false;
bool refri_2 = false;
bool refri_3 = false;
bool refri_4 = false;
//Estufa
bool anim_estufa = false;
bool estufa_1 = false;
bool estufa_2 = false;
//Puerta de la casa
bool anim_entrada = false;
bool puerta1 = false;
bool puerta2 = false;
//Cajon del tocador
bool anim_cajon = false;
bool cajon_1 = false;
bool cajon_2 = false;
//Trayectoria del pajarito
bool anim_elip = false;
bool elipse = false;
bool elipse2 = false;
bool alas = true;
bool alas2 = false;
bool band = false;
bool band2 = true;
bool band3 = false;
//Caida de la pelota
bool anim_caida = false;
bool pelota = false;
float aux = true;
float aux2 = true;
float aux3 = false;
bool fin = true;
//Segundo Cuarto
bool anim_armario = false;
bool accion = false;
bool accion2 = false;
bool anim_ventilador = false;
bool gira_vent = false;
bool anim_cajon2 = false;
bool cajon_3 = false;
bool cajon_4 = false;
bool anim_reloj = false;
bool sonido = false;
bool sonido2 = false;
bool timbre1 = false;
bool timbre2 = false;
bool timbre3 = false;
bool timbre4 = false;
bool cambio = false;
bool cambio2 = false;

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Lab CG", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    
    // Carga de modelos con animacion compleja a utilizar
    Model bird((char*)"Models/extras/bird.obj");
    Model bird1((char*)"Models/extras/bird_ala1.obj");
    Model bird2((char*)"Models/extras/bird_ala2.obj");
    Model Pelota((char*)"Models/extras/Pelota.obj");

    //Carga de modelos generales a utilizar

    Model House((char*)"Models/House CatDog/House_CatDog.obj");
    Model Puerta((char*)"Models/House CatDog/Puerta_House.obj");
    Model Refrigerador((char*)"Models/House CatDog/Refrigerador.obj");
    Model PuertaRefri1((char*)"Models/House CatDog/Arriba_Refrigerador.obj");
    Model PuertaRefri2((char*)"Models/House CatDog/Abajo_Refrigerador.obj");
    Model Estufa((char*)"Models/House CatDog/Estufa.obj");
    Model PuertaEstufa((char*)"Models/House CatDog/Puerta_Estufa.obj");
    Model Mesita((char*)"Models/House CatDog/Mesita_CatDog.obj");
    Model PuertaMesita((char*)"Models/House CatDog/Mesita_Puerta.obj");

    Model Sillon((char*)"Models/House CatDog/Sillon_CatDog.obj");
    Model Comedor((char*)"Models/House CatDog/Comedor_CatDog.obj");
    Model Lampara((char*)"Models/House CatDog/Lampara_CatDog.obj");
    Model Television((char*)"Models/House CatDog/Television_CatDog.obj");
    Model Extras((char*)"Models/House CatDog/Extras_CatDog.obj");
    Model Ventanas((char*)"Models/House CatDog/Ventanas_CatDog.obj");

    //Segundo Piso
    Model CatDog((char*)"Models/Segundo Piso/CatDog.obj");
    Model Armario((char*)"Models/Segundo Piso/Armario_CatDog.obj");
    Model PtaIzqArmario((char*)"Models/Segundo Piso/Puerta1Armario_CatDog.obj");
    Model PtaDerArmario((char*)"Models/Segundo Piso/Puerta2Armario_CatDog.obj");
    Model Ventilador((char*)"Models/Segundo Piso/Ventilador_CatDog.obj");
    Model Tocador((char*)"Models/Segundo Piso/Tocador_CatDog.obj");
    Model CajonTocador((char*)"Models/Segundo Piso/TocadorCajon_CatDog.obj");
    Model Repisa((char*)"Models/Segundo Piso/Repisa_CatDog.obj");
    Model Cama((char*)"Models/Segundo Piso/Cama_CatDog.obj");
    Model VentanaCuarto((char*)"Models/Segundo Piso/VentanaCuarto_CatDog.obj");
    Model Reloj((char*)"Models/Segundo Piso/Reloj_CatDog.obj");
    Model RelojPin((char*)"Models/Segundo Piso/RelojPin_CatDog.obj");
    Model RelojIzq((char*)"Models/Segundo Piso/RelojCampIzq_CatDog.obj");
    Model RelojDer((char*)"Models/Segundo Piso/RelojCampDer_CatDog.obj");


    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.690f, 0.890f, 0.909f, 1.0f); //color del fondo
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        // Draw the loaded model
        glm::mat4 model(1); //creamos la matriz y se setea en 1    

        //para dibujar los objeto del proyecto:

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -4.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //para posicionarlo bien
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Refrigerador.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -4.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //para posicionarlo bien
        model = glm::rotate(model, glm::radians(-rot), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaRefri1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -4.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //para posicionarlo bien
        model = glm::rotate(model, glm::radians(-rot2), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaRefri2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.0f, -3.0f, -9.0f)); //para posicionarlo bien
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //para posicionarlo bien
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Estufa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.0f, -3.0f, -9.0f)); //para posicionarlo bien
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //para posicionarlo bien
        model = glm::rotate(model, glm::radians(rot3), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f)); //lo acabo de agregar
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaEstufa.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        House.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 17.0f)); 
        model = glm::rotate(model, glm::radians(rot4), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mesita.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-cajon, 0.0f, 0.0f)); //este va a cambiar
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaMesita.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Sillon.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Comedor.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Lampara.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Television.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Extras.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventanas.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 30.0f, 35.0f));
        model = glm::translate(model, glm::vec3(Posx, 0.0f, Posz));
        model = glm::rotate(model, glm::radians(gira), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bird.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 30.0f, 35.0f));
        model = glm::translate(model, glm::vec3(Posx, 0.0f, Posz));
        model = glm::rotate(model, glm::radians(gira), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(aleteo), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bird1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.0f, 30.0f, 35.0f));
        model = glm::translate(model, glm::vec3(Posx, 0.0f, Posz));
        model = glm::rotate(model, glm::radians(gira), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-aleteo), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bird2.Draw(shader);

       model = glm::mat4(1);
       model = glm::translate(model, glm::vec3(4.0f, 12.25f, -2.0f));
       model = glm::translate(model, glm::vec3(caida1, 0.0f, 0.0f));
       model = glm::translate(model, glm::vec3(caidaX, caidaY, 0.0f));
       model = glm::translate(model, glm::vec3(0.0f, caidaY2, 0.0f));
       model = glm::rotate(model, glm::radians(rotPelota), glm::vec3(0.0f, 0.0f, 1.0f));
       glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       Pelota.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CatDog.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.2f, 14.55f, 3.0f));
        model = glm::rotate(model, glm::radians(-133.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Armario.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.7f, 0.0f, -1.85f)); //para las puertas
        model = glm::translate(model, glm::vec3(4.2f, 14.55f, 3.0f));
        model = glm::rotate(model, glm::radians(-133.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-ptaizq), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PtaIzqArmario.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 1.85f)); //para las puertas
        model = glm::translate(model, glm::vec3(4.2f, 14.55f, 3.0f));
        model = glm::rotate(model, glm::radians(-133.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(ptader), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PtaDerArmario.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 20.3f, 3.5f));
        model = glm::rotate(model, glm::radians(aire), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventilador.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Tocador.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(cajon2, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CajonTocador.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Repisa.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cama.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        VentanaCuarto.Draw(shader);

       model = glm::mat4(1);
       model = glm::translate(model, glm::vec3(-5.5f, 13.95f, 1.5f));
       glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       Reloj.Draw(shader);
        
       model = glm::mat4(1);
       model = glm::translate(model, glm::vec3(-5.5f, 13.95f, 1.5f));
       model = glm::rotate(model, glm::radians(tintineo), glm::vec3(0.0f, 0.0f, 1.0f));
       glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       RelojPin.Draw(shader);

       model = glm::mat4(1);
       model = glm::translate(model, glm::vec3(-5.5f, 13.95f, 1.5f));
       model = glm::translate(model, glm::vec3(vibracion1X, vibracion1Y, 0.0f));
       glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       RelojIzq.Draw(shader);

       model = glm::mat4(1);
       model = glm::translate(model, glm::vec3(-5.5f, 13.95f, 1.5f));
       model = glm::translate(model, glm::vec3(vibracion2X, vibracion2Y, 0.0f));
       glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
       RelojDer.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    if (refri_1) {
        if (rot <= 90) {
            rot += 0.8f;
        }
    }

    if (refri_2) {
        if (rot >= 0) {
            rot -= 0.8f;
        }
    }

    if (refri_3) {
        if (rot2 <= 90) {
            rot2 += 0.8f;
        }
    }

    if (refri_4) {
        if (rot2 >= 0) {
            rot2 -= 0.8f;
        }
    }

    if (estufa_1) {
        if (rot3 <= 90) {
            rot3 += 0.8f;
        }
    }

    if (estufa_2) {
        if (rot3 >= 0) {
            rot3 -= 0.7f;
        }
    }

    if (puerta1) {
        if (rot4 <= 90) {
            rot4 += 1.0f;
        }
    }

    if (puerta2) {
        if (rot4 >= 0) {
            rot4 -= 1.0f;
        }
    }

    if (cajon_1) {
        if (cajon <= 0.8) {
            cajon += 0.01f;
        }
    }

    if (cajon_2) {
        if (cajon >= 0) {
            cajon -= 0.01f;
        }
    }

    if (elipse && band2) {
        if (Posx <= 15) { //para la derecha
            Posx += 0.2f;
        }
        else {
            if (gira <= 90) {
                gira += 1.0f;
                Posx += 0.2f;
                Posz -= 0.2f;
            }
            else if (Posz > -35.0){ //para atras
                Posz -= 0.2f;
            }
            else if (gira <= 180) {
                gira += 1.0f;
                Posx -= 0.2f;
                Posz -= 0.2f;
            }
            else {
                elipse = false;
                elipse2 = true;
                band = true;
                band3 = true;
            }
        }
    }

    if (elipse2 && band3) { //para la izquierda
        band2 = false;
        if (Posx >= -10 && band == true) {
            Posx -= 0.2f;
        }
        else {
            band = false;
            if (gira <= 270) {
                gira += 1.0f;
                Posx -= 0.2f;
                Posz += 0.2f;
            }
            else if (Posz < -15) { //para adelante
                Posz += 0.2f;
            }
            else if (gira <= 360) {
                gira += 1.0f;
                Posx += 0.2f;
                Posz += 0.2f;
            }
            else if (Posx < 0) {
                Posx += 0.2;
            }
            else {
                gira = 0;
                elipse = true;
                elipse2 = false;
                band2 = true;
                band3 = false;
            }
        }
    }

    if (alas) {
        if (aleteo <= 45) {
            aleteo += 3.0;
        }
        else {
            alas = false;
            alas2 = true;
        }
    }

    if (alas2) {
        if (aleteo >= -45) {
            aleteo -= 3.0;
        }
        else {
            alas = true;
            alas2 = false;
        }
    }

    if (pelota) {
        if (caida1 <= 0.5) {
            caida1 += 0.1f;
            rotPelota -= 1.0;
        }
        if (caida1 <= 1.5) {
            caida1 += 0.1f;
            caidaY -= 0.1f;
        }

        if (caidaY > -5.5 && aux) {
            caidaY -= 0.1;
        }
        else if (caidaX > -8.4 && fin) { //primer bote
            aux = false;
            caidaX -= 0.025;
            caidaY2 -= 0.1;
            rotPelota += 1.0;

            if (caidaX > -2.7 && aux2) { //segundo bote
                if (caidaY < 2) {
                    caidaY += 0.2; //era 0.15
                }
            }
            else {
                aux2 = false;
                aux3 = true;
            }

            if (caidaX > -5.1 && aux3) { //tercer bote
                if (caidaY < 8) {
                    caidaY += 0.2;
                }
            }

            if (caidaY2 < -21.3) { //cuarto bote
                if (caidaY < 12) {
                    caidaY += 0.2;
                }
            }

            if (caidaY2 < -27.5) { //quinto bote 
                if (caidaY < 16) {
                    caidaY += 0.2;
                }
            }

            if (caidaY2 < -32.35) { //31.4
                if (caidaY < 18.5) {
                    caidaY += 0.15;
                }
            }
        }
        else {
            fin = false;
        }

        if (caidaX > -11.8 && fin == false) {
            caidaX -= 0.025;
            rotPelota += 1.0;
        }
    }

    if (accion) {
        if (ptaizq <= 90.0f) {
            ptaizq += 0.8f;
        }

        if (ptader <= 90.0f) {
            ptader += 0.8f;
        }
    }

    if (accion2) {
        if (ptaizq >= 0.0f) {
            ptaizq -= 0.8f;
        }

        if (ptader >= 0.0f) {
            ptader -= 0.8f;
        }
    }

    if (gira_vent) {
        aire += 3.5f;
    }

    if (cajon_3) {
        if (cajon2 <= 0.8) {
            cajon2 += 0.01f;
        }
    }

    if (cajon_4) {
        if (cajon2 >= 0) {
            cajon2 -= 0.01f;
        }
    }

    if (sonido) {
        if (tintineo <= 45) {
            tintineo += 10.0f;
        }
        else {
            sonido = false;
            sonido2 = true;
        }
    }

    if (sonido2) {
        if (tintineo >= -45) {
            tintineo -= 10.0f;
            if (sonido == false && cambio) {
                sonido2 = false;
            }
        }
        else {
            sonido2 = false;
            sonido = true;
        }
    }

    if (timbre1) {
        if (vibracion1X >= -0.05) {
            vibracion1X -= 0.04f;
            vibracion1Y -= 0.04f;
        }
        else {
            timbre1 = false;
            timbre2 = true;
        }
    }

    if (timbre2) {
        if (vibracion1X <= 0.05) {
            vibracion1X += 0.04f;
            vibracion1Y += 0.04f;
            if (timbre1 == false && cambio2) {
                timbre2 = false;
            }
        }
        else {
            timbre2 = false;
            timbre1 = true;
        }
    }

    if (timbre3) {
        if (vibracion2X <= 0.05) {
            vibracion2X += 0.04f;
            vibracion2Y -= 0.04f;
        }
        else {
            timbre3 = false;
            timbre4 = true;
        }
    }

    if (timbre4) {
        if (vibracion2X >= -0.05) {
            vibracion2X -= 0.04f;
            vibracion2Y += 0.04f;
            if (timbre3 == false && cambio2) {
                timbre4 = false;
            }
        }
        else {
            timbre4 = false;
            timbre3 = true;
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }


    if (keys[GLFW_KEY_I]) //para la puerta de arriba del refri
    {
        anim_refri = not anim_refri;
        if (anim_refri) {
            refri_1 = true;
            refri_2 = false;
        }
        else {
            refri_1 = false;
            refri_2 = true;
        }
    }

    if (keys[GLFW_KEY_K]) //para la puerta de abajo del refri
    {
        anim_refri2 = not anim_refri2;
        if (anim_refri2) {
            refri_3 = true;
            refri_4 = false;
        }
        else {
            refri_3 = false;
            refri_4 = true;
        }

    }

    if (keys[GLFW_KEY_O]) //para la puerta de la estufa
    {
        anim_estufa = not anim_estufa;
        if (anim_estufa) {
            estufa_1 = true;
            estufa_2 = false;
        }
        else {
            estufa_1 = false;
            estufa_2 = true;
        }
    }

    if (keys[GLFW_KEY_G]) //para la puerta de la casa
    {
        anim_entrada = not anim_entrada;
        if (anim_entrada) {
            puerta1 = true;
            puerta2 = false;
        }
        else {
            puerta1 = false;
            puerta2 = true;
        }
    }

    if (keys[GLFW_KEY_L]) //para el cajon de la mesita
    {
        anim_cajon = not anim_cajon;
        if (anim_cajon) {
            cajon_1 = true;
            cajon_2 = false;
        }
        else {
            cajon_1 = false;
            cajon_2 = true;
        }
    }

    if (keys[GLFW_KEY_X]) //para el pajarito
    {
        anim_elip = not anim_elip;
        //alas = true;
        if (anim_elip) {
            elipse = true;
            elipse2 = true;
        }
        else {
            elipse = false;
            elipse2 = false;
        }
    }

    if (keys[GLFW_KEY_F]) { //para la pelota
        anim_caida = not anim_caida;
        if (anim_caida) {
            pelota = true;
        }
        else {
            pelota = false;
            caidaX = 0;
            caidaY = 0;
            caidaY2 = 0;
            caida1 = 0;
            aux = true;
            aux2 = true;
            aux3 = false;
            fin = true;
        }
    }

    if (keys[GLFW_KEY_V]) {
        anim_armario = not anim_armario;
        if (anim_armario) {
            accion = true;
            accion2 = false;
        }

        else {
            accion = false;
            accion2 = true;
        }
    }

    if (keys[GLFW_KEY_B]) {
        anim_ventilador = not anim_ventilador;
        if (anim_ventilador) {
            gira_vent = true;
        }
        else {
            gira_vent = false;
        }
    }

    if (keys[GLFW_KEY_N]) {
        anim_cajon2 = not anim_cajon2;
        if (anim_cajon2) {
            cajon_3 = true;
            cajon_4 = false;
        }
        else {
            cajon_3 = false;
            cajon_4 = true;
        }
    }

    if (keys[GLFW_KEY_M]) {
        anim_reloj = not anim_reloj;
        if (anim_reloj) {
            sonido = true;
            timbre1 = true;
            timbre3 = true;
        }
        else {
            sonido = false;
            timbre1 = false;
            timbre3 = false;
        }
        if (sonido == false) {
            cambio = true;
        }
        else {
            cambio = false;
        }
        if (timbre1 == false) {
            cambio2 = true;
        }
        else {
            cambio2 = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

