/* UNED III Cuatrimestre
Proyecto ¿Qué tanto sabes de las partes del cuerpo?: Proyecto donde se busca reforzar el conocimiento d estudiantes mediante la contestacion de diferentes preguntas presentadas
a modo de juego, se tiene un registro, reporte de jugadores y una tabla de los mejores jugadores.
Estudiante: María Celeste Umaña Castro
Fecha: 18-11-23

Referencias bibligraficas.

1. Programacion ATS.(5 nov 2015).123. Programación en C++ || Archivos || Escribir en un archivo de texto. https://www.youtube.com/watch?v=GaqgqQL3wnQ

2. Programacion ATS.(5 nov 2015).123. Programación en C++ || Archivos || Lectura de un archivo de texto. https://www.youtube.com/watch?v=ksnBUo-08Uw&t=3s

3.Foro del web. (enero 2009). seleccionar elemento aleatorio de un array con C++.https://www.forosdelweb.com/f96/seleccionar-elemento-aleatorio-array-con-c-912843/

4. Programacion ATS.(5 nov 2015).50. Programación en C++ || Ordenamientos || Método Burbuja. https://www.youtube.com/watch?v=P_xNb8nFgmA
*/

#include <iostream>
#include <locale>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>


using namespace std;

//Declaracion de funciones
void IngresarJugadores(char& respuesta);
void QuetantoSabes(char& respuesta, int opcion, int aciertos, string nombreJugador);
bool VerificarCedulaExistenteQueTantoSabes(string numeroCedula, string validacionCedula, string& nombreJugador);
void PreguntasAleatorias( int& indicePreguntaAleatoria, string pregunta[25], string solucion[25], string solucionCorrecta);
bool EvaluaRespuesta(string respuestaUsuario, int indicePreguntaAleatoria, string solucion[25]);
void DeseaSeguirJugando(char& respuestaDeseaSeguirJugando, int aciertos, string& nombreJugador, int errores);
void ReporteJugadores(char& respuesta, int opcion);
void Los10MejoresJugadores(char& respuesta, int opcion);
void PreguntaMenu(char& respuesta, int opcion);

int main()
{
    //Declaracion variables globales del main
    int opcion, aciertos;;
    char respuesta;
    string nombreJugador;

    //Configuracion regional
    setlocale(LC_ALL, "spanish");

    //Se presenta el menú y dependiendo d elo que seleccione a hacer se ejecutara uno u otro case.
    do{
        system("cls");
        cout << "Menú Principal" <<endl;
        cout << "1. Ingresar jugadores" <<endl;
        cout << "2. Jugar '¿Qué tanto sabes de las partes del cuerpo?'" <<endl;
        cout << "3. Reporte de jugadores " <<endl;
        cout << "4. Los 10 mejores jugadores" <<endl;
        cout << "5. Salir del programa " <<endl;
        cout << "\n";

        cout << "Opción que desea seleccionar: ";
        cin >> opcion;

        cin.ignore();
        system("cls");

        switch(opcion)
        { //Se llama la funcion que ejecute el codigo necesario para cumplir con el case
        case 1:
            IngresarJugadores(respuesta);
            break;
        case 2:
            QuetantoSabes(respuesta, opcion, aciertos, nombreJugador);
            break;
        case 3:
            ReporteJugadores(respuesta, opcion);
            break;
        case 4:
            Los10MejoresJugadores(respuesta, opcion);
            break;
        case 5:
            cout << "Saliendo del Programa..." << endl;
            cin.get();
            break;
        default:
            cout << "La opción seleccionada no es válida..." << endl;
            cout << "Intentelo de nuevo." << endl;
             cin.get();
            break;
        }
    }while(opcion != 5);

    return 0;
}

void IngresarJugadores(char& respuesta)
{
    //Referencia 1 - 2
    ofstream registro;//Se utiliza para la escritura de archivos
    ifstream registroLectura;// Se utiliza para la lectura de archivos
    string verificacionJugador, nombre, cedula;

    //Manejo de excepcion en caso de que al abrir el archivo de escritura ocurra un fallo
    try
     {
         //abriendo el archivo  - se utiliza app para no sobreescribir sobre datos anteriores
        registro.open("Registro.txt",ios::app);

        //Si hay un fallo se lanza la cadena de cracteres
         if(registro.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error){//Captura la excepcion, es un char debido a que lo que captura es una cadena de caracteres, el puntero de tipo char llamado error apunta el mensaje de error
        cout << "Error: " << error << endl;
        exit(1);//Se sale del programa
     }

    do{
        //Se declaran e inicializan estas variables para que se limpien y se eviten errores inesperados
        bool cedulaValida = true, cedulaExistente = false, nombreSinEspacios = true;

        system("cls");
        cout << "Ingresar jugadores" << endl;
        cout << "\nIngrese su nombre: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese su # de cédula: ";
        cin >> cedula;

        //Se revisa que nombre no tenga espacios, evitando que coloque un apellido
        for(int i = 0; i < nombre.length(); i++)//revisar
        {
            char caracter = nombre[i];
           if(caracter == ' ')
           {
               nombreSinEspacios = false;
               break;
           }
         }

        //se revisa que solo existan numeros en la cedula y no otros caracteres
        for(int i = 0; i < cedula.length(); i++)
        {
           char cedulaChar = cedula[i];
           if (cedulaChar != '0' && cedulaChar != '1' && cedulaChar != '2' &&cedulaChar != '3' && cedulaChar != '4'
               && cedulaChar != '5'&& cedulaChar != '6' &&cedulaChar != '7' && cedulaChar != '8' && cedulaChar != '9')
           {
               cedulaValida = false;
               break;
           }
         }

     //Manejo de excepcion al abrir el archivo de lectura
     try
     {
        registroLectura.open("Registro.txt",ios::in);//Se abre el archivo registro para leer los jugadores registrados
         if(registroLectura.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }

        //Se recorre el archivo de escritura de registro y se revisa que no exista esa cedula.
        while(getline(registroLectura, verificacionJugador))
        {
             if (verificacionJugador == cedula)
            {
                //Si existe en el registro da un error
                cout <<"\n¡¡El jugador ya está en el registro!!" << endl;
                cedulaExistente = true;
            }
        }
            //Se presentan mensajes de cedula y nombre invalidos si no cumple con los parametros
            if (!cedulaValida)
            {
                cout << "\n¡¡¡La cédula ingresada es inválida!!!\n";
            }else if (!nombreSinEspacios)
            {
                cout << "\nEl nombre ingresado es inválido." << endl;
                cout << "Debe ser un solo nombre sin apellidos.\n"<< endl;

            }


        registroLectura.close();//se cierra el registro de lectura

        //Si el jugador no existia en el registro, nombre y la cedula cumple con los requisitos se agregan a el registro
        if(!cedulaExistente && cedulaValida && nombreSinEspacios){
            registro << nombre << endl;
            registro << cedula << endl;
            cout << "El jugador fue registrado con exito!\n";
        }


        cout << "\n";
        cout << "¿Desea ingresar otro jugador? S/N" << endl;
        cin >> respuesta;
        respuesta = toupper(respuesta);
        if(respuesta != 'S' && respuesta != 'N')
        {
            system("cls");
            cout << "Digite una opcion válida" << endl;
            cout << "\n¿Desea ingresar otro jugador? S/N" << endl;
            cin >> respuesta;
            respuesta = toupper(respuesta);

        }else if (respuesta == 'N')
        {
            cout << "Volviendo al menú..." << endl;
            cin.get();
        }
    }while(respuesta != 'N');

    registro.close();//para cerrar el archivo

}

//https://www.youtube.com/watch?v=ksnBUo-08Uw
void QuetantoSabes (char& respuesta, int opcion, int aciertos, string nombreJugador)
{
   do
   {    //Declaracion de variables utilizadas en QueTantoSabes
        int errores;
        char respuestaIntento;
        bool cedulaVerificacion;
        string numeroCedula, validacionCedula, pregunta[25], solucion[25], solucionCorrecta, nombrejugador;

        do{
            //Se limpian las varibales para que las condiciones se puedan cumplir y no hayan problemas
            cedulaVerificacion = false, respuesta = 'N',respuestaIntento = 'S';


            system("cls");
            cout << "Jugar ¿Qué tanto sabes del cuerpo?" << endl;
            cout << "\n¿Quién será el jugador? Ingrese el # de cedúla: ";
            cin >> numeroCedula;

            //Se verifica que la cedula ingresada este en el registro llamando una fucion.
            cedulaVerificacion = VerificarCedulaExistenteQueTantoSabes(numeroCedula, validacionCedula, nombreJugador);

            if (!cedulaVerificacion)
            {
                cout << "\nEl número de cedúla es correcto!\n" << endl;
                system("pause");

            }else
            {
                cin.ignore();
                cout << "El número de cedúla es erróneo, no existe en el sistema..." << endl;
                cout << "\nDesea intentarlo de nuevo? (S/N): " << endl;
                cin >> respuestaIntento;
                respuestaIntento = toupper(respuestaIntento);
                if(respuestaIntento == 'N')
                {
                    system("cls");
                    PreguntaMenu(respuesta, opcion);//Si decide que no quiere intentar de nuevo se le pregunta si desea volver al menu

                   if(respuesta == 'S'){
                     return;//Sale de la funcion
                   }else
                   {
                       system("cls");
                       cout << "Es necesario volver al menú principal para continuar." << endl;
                       system("pause");
                       return;//Sale de la funcion
                   }
                }
            }
        }while(respuestaIntento != 'N' && respuesta != 'S' && cedulaVerificacion);//Mientras estas tres condiciones sean se cumplan se ejecuta el bucle

        //Declaracion e inicializacion de variables de la zona de preguntas
        int indicePreguntaAleatoria, cambiar = 0, salir = 0;
        char cambioPregunta;
        aciertos = 0;
        char respuestaDeseaSeguirJugando = 'S';

        string respuestaUsuario;
        errores = 0;

        do//Este bucle evalua la respuesta del usuario y lleva el puntaje
        {

            do//bucle que se asegura el cambio de preguntas y presentar preguntas aleatorias
            {
                system("cls");
                PreguntasAleatorias(indicePreguntaAleatoria, pregunta , solucion, solucionCorrecta);
                 if(cambiar < 2) //se muestra si cambiar es menor a 2 para evitar confusiones
                 {
                    do{
                       cout << "\nDesea cambiar la pregunta? S/N " << endl;
                       cin >> cambioPregunta;
                       cambioPregunta = toupper(cambioPregunta);
                       if (cambioPregunta == 'S')
                       {
                         cambiar++;
                         if(cambiar == 2)
                         {
                            cout << "\nEl jugador " << nombreJugador << " ha cambiado dos preguntas, ya no puede cambiar de pregunta!"<< endl;
                            cout << "\n";
                            system("pause");
                         }
                       }else if(cambioPregunta != 'N' && cambioPregunta != 'S')
                       {
                        system("cls");
                        cout << "Por favor, ingrese 'S' o 'N'." << endl;
                        system("pause");
                       }
                     }while(cambioPregunta != 'N' && cambioPregunta != 'S');
                }else
                {
                   salir++; //cuando cambiar sea mayor o igual a 2 salir aumenta en 1, por lo que ahora se puede salir del bucle, esto paar que se muestre una tercera pregunta
                }

            }while (cambioPregunta != 'N' && salir < 1);

            cout << "\n--------------------------------------------" << endl;
            cout << "\nIndique la respuesta (Una única palabra): ";
            cin >> respuestaUsuario;

            //Se evalua si la respuesta digitada por el usuario es correcta
            bool acertoRespuesta = EvaluaRespuesta(respuestaUsuario, indicePreguntaAleatoria, solucion);

            if (!acertoRespuesta)
            {
                cout << "\n\t¡Respuesta incorrecta!" << endl;
                errores++;
                cout << "\nPosee " << errores << " errores al jugador " << nombreJugador << " le quedan " << (4-errores) << " errores de 4!\n"  << endl;
                system("pause");
                if (errores == 4){
                    system("cls");
                     cout << "\n¡Jugador "<< nombreJugador << " obtuvo " << aciertos << " puntos\n"<< endl;
                    cout << "\n¡¡¡Has perdido!!!\n" << endl;
                    system("pause");
                }

            }else
            {
                cout << "\n\t¡Respuesta correcta!" << endl;
                aciertos++;
                system("pause");

                if(aciertos % 5 == 0)//Si la cantidad de aciertos es multiplo de 5
                {
                    system("cls");
                    cout << "\nPosee " << aciertos << " aciertos" << endl;
                    if (aciertos == 10 || aciertos == 15)
                    {
                      aciertos += 5;
                    }else if(aciertos == 25)
                    {
                      aciertos += 25;
                      system("cls");
                      cout << "\nGANADOR ¡Jugador "<< nombreJugador << " con " << aciertos << " puntos"<< endl;
                      system ("pause");

                    }
                    if(aciertos != 50)
                    {
                        DeseaSeguirJugando(respuestaDeseaSeguirJugando, aciertos, nombreJugador, errores);
                    }
                }
            }

        }while(respuestaDeseaSeguirJugando != 'N' && errores < 4 && aciertos < 25);

        //Se guardaran los datos d elos jugadores que ya no deseen contestar más preguntas en un archivo para mostrar los mejores jugadores
        ofstream puntajesEscritura;//se utiliza para el ingreso de archivos

     //Manejo excepciones al abrir el archivo de la informacion de los jugadores
     try
     {
       puntajesEscritura.open("InformacionJugadores.txt",ios::app);//abriendo el archivo
         if(puntajesEscritura.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }

        //Se guarda en el archivo InfromacionJugadores tanto la cedula, como nombre y puntaje
        puntajesEscritura << nombreJugador << endl;
        puntajesEscritura << numeroCedula << endl;
        puntajesEscritura << aciertos << endl;

        puntajesEscritura.close();

        PreguntaMenu(respuesta, opcion);

   }while(respuesta != 'S');
}

bool VerificarCedulaExistenteQueTantoSabes(string numeroCedula, string validacionCedula, string& nombreJugador)
{
    ifstream registroLectura;
    int iteracion = 0;
    bool cedulaNoValida = true;

     try
     {
        registroLectura.open("Registro.txt",ios::in);
         if(registroLectura.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }
        //Se lee el archivo de registro para ver si la cedula esta en el registro
        while(getline(registroLectura, validacionCedula))
        {
            if(iteracion % 2 == 0){//La linea antes de que se compruebe que la validadion es valida se guarda como el nombre del jugador.
                nombreJugador = validacionCedula;
            }else if(numeroCedula == validacionCedula)
            {
               cedulaNoValida = false;
               break;
            }
            iteracion++;
        }
        registroLectura.close();//se cierra el registro de lectura

        return cedulaNoValida;
}


void PreguntasAleatorias( int& indicePreguntaAleatoria,  string pregunta[25], string solucion[25], string solucionCorrecta)
{
    ifstream archivoPreguntas;//se utiliza para la lectura de archivos
    const int numeroPreguntas = 25;
    bool preguntaYaPresentada, posibilidades[numeroPreguntas] = {false};


    //Revisar si hay problemas  a la hora de abrir el archivo
    try
     {
       archivoPreguntas.open("preguntas.txt",ios::in);
         if(archivoPreguntas.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }

        string texto;
        int e = 0, iteracion=0;

        //Es para que se lea todo el archivo de preguntas
        while( getline(archivoPreguntas,texto)){
        if(iteracion % 2 == 0)//Si resulta un numero par o 0 entonces es una pregunta
            {
                //Pregunta
                 pregunta[e] = texto;

            } else// Es numero impar por lo que es la solucion de la definicion
            {
                //Respuesta
                solucion[e] = texto;
                e++;//la variable e cambia hasta en este momento para que no se descuadren los numeros.
            }
             iteracion++;
        }
        archivoPreguntas.close();

   //Referencia 3. Como seleccionar pregunta aleatoria
   srand(time(NULL));//Inicia la semilla de generacion de numeros aleatorios

   indicePreguntaAleatoria = rand()% numeroPreguntas;//Genera un numero aleatorio dentro de las 25 preguntas

  cout << "Pregunta: " << pregunta[indicePreguntaAleatoria]<<endl;
}


bool EvaluaRespuesta(string respuestaUsuario, int indicePreguntaAleatoria, string solucion[25])
{
    bool evaluacionRespuesta;

    //La solucion guardada en el indice que es igual al indice seleccionado aleatoriamente es igual a la respuesta del usuario
    if(respuestaUsuario == solucion[indicePreguntaAleatoria])
    {
        evaluacionRespuesta = true;
    }else
    {
       evaluacionRespuesta = false;
    }
    return evaluacionRespuesta;
}

void DeseaSeguirJugando(char& respuestaDeseaSeguirJugando, int aciertos, string& nombreJugador, int errores)
{
    do
    {
        cout << "\n";
        cout << "Desea seguir jugando? (S/N): " << endl;
        cin >> respuestaDeseaSeguirJugando;
        respuestaDeseaSeguirJugando = toupper(respuestaDeseaSeguirJugando); // Convertir la respuesta a mayúsculas

        if (respuestaDeseaSeguirJugando == 'N')
        {
            system("cls");
            cout << "\n¡Jugador "<< nombreJugador << " obtuvo " << aciertos << " puntos\n"<< endl;
            system ("pause");
        } else if (respuestaDeseaSeguirJugando != 'N' && respuestaDeseaSeguirJugando != 'S')
        {
            system("cls");
            cout << "Por favor, ingrese 'S' o 'N'." << endl;
            cin.get();
        }
    }while(respuestaDeseaSeguirJugando != 'N' && respuestaDeseaSeguirJugando != 'S');
}

void ReporteJugadores(char& respuesta, int opcion)
{
      ifstream informacionLectura;
      string jugadoresReporte, matrizReporte [100][2];
      int iteracion = 0, e = 0;

      //Manejo de excepsion si falla al abrir el archivo
     try
     {
       informacionLectura.open("InformacionJugadores.txt",ios::in);
         if(informacionLectura.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }

   do{
        system("cls");
        cout << "Reporte jugadores:" << endl;
        cout << "\nNúmero de cédula" << "\t" <<"Nombre del jugador" << endl;
        cout << "------------------------------------------------" << endl;

        //Se rellena la matriz con la informacion de el archivo, al recorrer este
        while(getline(informacionLectura, jugadoresReporte))
        {
            if(iteracion % 3 == 0)//La iteración al dividirla por 3 da como resto 0, entonces es el nombre[f,1]
            {
                 matrizReporte[e][0] = jugadoresReporte;
            } else if(iteracion % 3 == 1)//La iteración al dividirla por 3 da como resto 1, entonces es la cedula[f,0]
            {
                 matrizReporte[e][1] = jugadoresReporte;
                 e++;//la variable fila cambia hasta en este momento para que no se descuadren las filas.
            }

             iteracion++;
        }
     informacionLectura.close();

     //Array con la cantidad de espacios igual e, iniciada en cadena vacia
     string jugadorMostrado [e] ={""};

     for (int i = 0; i < e; i++) //Se recorren los elementos de la matriz
    {
        bool jugadorPresentado = false;
        for(int j = 0; j < e; j++)//Recorre el array jugadoresMostrados
        {
            if (jugadorMostrado[j] == "")//Si ese espacio del array esta vacio agrega la cedula en jugadoresmostardos
            {
                jugadorMostrado[j] = matrizReporte[i][1];
                break;

            }else if ( matrizReporte[i][1] == jugadorMostrado[j]) //Si la cedula ya existe en el array se marca como jugadorPresentado
            {
                jugadorPresentado = true;
                break;
            }

        }
        if(!jugadorPresentado)//Solo se imprimen los jugadores que la cedula no se repita
        {
          cout <<matrizReporte[i][1] << "\t\t\t" << matrizReporte[i][0] << endl;
        }
    }
    PreguntaMenu(respuesta,opcion);

   }while(respuesta != 'S');
}

void Los10MejoresJugadores(char& respuesta, int opcion)
{
    ifstream puntajesLectura;
    string texto, matrizMejoresJugadores[10][3];
    int iteracion = 0, indice = 0;

    //manejo de excepciones al abrir el archivo
     try
     {
        puntajesLectura.open("InformacionJugadores.txt",ios::in);
         if(puntajesLectura.fail())
           throw "No se pudo abrir el archivo";

     }catch(const char* error)
     {
        cout << "Error: " << error << endl;
        exit(1);
     }

    //Se lee el archivo en donde se guardo los nombres de los jugadores y sus puntajes
    while(getline(puntajesLectura, texto)){
         if(iteracion % 3 == 0)//Nombre
            {
                //nombre
                matrizMejoresJugadores[indice][0] = texto;//Se guardan los nombres en la matriz

            } else if (iteracion % 3 == 2)
            {
                //puntaje
                matrizMejoresJugadores[indice][1] = texto; //
                indice++;//la variable indice cambia hasta en este momento para que no se descuadren los numeros.
            }else
            {
                //Cedula- la cedula no es necesaria en este caso pero la utilice para evitar que se repitan jugadores en los mejores jugadores
                 matrizMejoresJugadores[indice][2] = texto;
            }

             iteracion++;
    }

    puntajesLectura.close();

    //Referencia 4 - Metodo burbuja, este se repite hasta que se recorra el por completo y no haya que relizar ningun intercambio
    for(int i = 0; i < indice; i++)//Recorre los elementos de la fila de la matriz.
    {
        for(int j = 0; j < indice-1; j++)//Recorre los elementos de la columna de la matriz.
        {

            int puntajeActual, puntajeSiguiente;

            //Si la conversion de los puntajes de cadena a enteros falla se da un mensaje de error
            try
            {
                //Se realiza el cambio de string a int para comparar realmente los valores
                puntajeActual = stoi(matrizMejoresJugadores[j][1]);
                puntajeSiguiente = stoi(matrizMejoresJugadores[j+1][1]);
            }catch(const invalid_argument& excepcion)
            {
                cout << "Error: No se pudo convertir a entero la cadena." << endl;
               exit(1);
            }

            if(puntajeActual < puntajeSiguiente)//Si el puntaje del jugador actual es menor que el del siguiente los intercambia, paar esto son las variables llamadas "temporal" son como variables temporales para realizar el intercambio
            {

               //Al ser el puntaje menor al siguiente se pasan tanto el nombre,cedula y puntaje en variables de transicion.
                string nombreJugadorTemporal = matrizMejoresJugadores[j][0];
                string puntajeTemporal = matrizMejoresJugadores[j][1];
                string cedulaTemporal = matrizMejoresJugadores[j][2];

                //Tanto el nombre,cedula y puntaje siguientes son movidos a jugador actual para posicionar de mayor a menor
                matrizMejoresJugadores[j][0] = matrizMejoresJugadores[j+1][0];
                matrizMejoresJugadores[j][1] = matrizMejoresJugadores[j+1][1];
                matrizMejoresJugadores[j][2] = matrizMejoresJugadores[j+1][2];

                //Y paar terminar se mueve el nombre, cedula y puntaje de las variables temporales a las siguientes
                matrizMejoresJugadores[j+1][0] = nombreJugadorTemporal;
                matrizMejoresJugadores[j+1][1] = puntajeTemporal;
                matrizMejoresJugadores[j+1][2] = cedulaTemporal;
            }
        }
    }

    //Se van a imprimir los 10 mejores jugadores
    cout << "\n\t LOS 10 MEJORES JUGADORES" << endl;
    cout << "---------------------------------------------" << endl;

     /*Este bucle busca solo imprimir los mejores jugadores pero a la vez solo el mejor puntaje de este
    por lo que es importante acomodarlos del mejor puntaje al peor ya que asi el primero que encuentre(es el mejor puntaje) e imprimira este,
     y los demas los cuales seran menores no se imprimiran*/

    string jugadoresMostrados[100] = {""};//inicializado en cadenas vacias

    for(int i = 0; i < indice-1; i++)//Recorre las filas de la matriz
    {
        bool jugadorRepetido = false;

        for(int j = 0; j < 100; j++)//Recorre el arary de jugadores mostrados par ver si el jugador ya se mostro
        {
            if(jugadoresMostrados[j]== "")//Si la posicion esta vacia entonces agrga la cedula del jugador en jugador ya mostrado
            {
                jugadoresMostrados[j]= matrizMejoresJugadores[i][2];
                break;//sale del bucle

            }else if (matrizMejoresJugadores[i][2]== jugadoresMostrados[j])//Si la cedula del jugador ya esta en jugadores mostrados devuelve que es verdad que es un jugador repetido
            {
                 jugadorRepetido = true;
                 break;
            }
        }
         if (!jugadorRepetido) //Si el jugador no esta repetido imprime la informacion
       {
           //setw lo que hace es aisgnar un largo de 20 caracteres para evitar que que se descuadre la matriz
        cout  << "Jugador #"<< setw(2) << (i+1) << setw(20) << matrizMejoresJugadores[i][0] << "\t\t" << matrizMejoresJugadores[i][1] << endl;
       }
    }
    PreguntaMenu(respuesta, opcion);
}

//Se encarga de preguntar al usuario si desea volver al menu principal
void PreguntaMenu(char& respuesta, int opcion)
{
    cout << "\n";
    cout << "Desea regresar al menú principal (S/N): " << endl;
    cin >> respuesta;
    respuesta = toupper(respuesta); // Convertir la respuesta a mayúsculas

    if (respuesta == 'S')
    {
    cout << "Volviendo al menú principal..." << endl;
    } else if (respuesta != 'N' && respuesta != 'S')
    {
        cout << "Por favor, ingrese 'S' o 'N'." << endl;
        cout << "\n";
        cout << "Desea regresar al menú principal (S/N): " << endl;
        cin >> respuesta;
        respuesta = toupper(respuesta); // Convertir la respuesta a mayúsculas
        cin.get();

    } else
    {
        if (opcion != 2)
        {
            system("cls");
            cout << "Lea con detenimiento."<< endl;
            cout << "Es necesario volver al menú principal para continuar." << endl;
            system("pause");
        }
    }
}
