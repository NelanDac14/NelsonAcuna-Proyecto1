/*
  Universidad Estatal a Distancia

  Introducción a la programación
          Código: 00831

-----------Proyecto #1-----------

 Nelson Andrés Acuña Cambronero
         Cédula: 116620490
*/
/*
    Este proyecto tiene como función recibir datos acerca del consumo de agua de alguna persona
    y mostrar el recibo correspondiente con el arancel a cancelar.


    Referencia Blibliográfica:

    (Cplusplus.com, n.d)
    Cplusplus.com. (n.d.). <cctype> header. Cplusplus.com. Retrieved from https://cplusplus.com/reference/cctype/

    (Deitel, 30/6/2021)
    Deitel, P. J., Deitel, H.  (2021). Cómo programar en C++. [[VitalSource Bookshelf version]].  Retrieved from vbk://9786073255424

    (DevDocs, n.d)
    DevDocs. (n.d.). C++ documentation. DevDocs. Retrieved from https://devdocs.io/cpp/
*/
#include <iostream>

//Librerías de uso específico
#include <string>//Proporciona funciones como el getline() para optener lineas de texto ingresadas
#include <locale.h>//Procesamiento de datos para diferentes lenguajes (caracteres).
#include <cstring>//Contiene funciones de procesamiento de cadenas de estilo C.

//Cplusplus.com. (n.d.). <cctype> header. Cplusplus.com. Retrieved from https://cplusplus.com/reference/cctype/
#include <cctype>//Contiene funciones para conversión de minúscula a mayúscula y visceversa, además de funciones para verificar el tipo de caracter

using namespace std;

/* Prototipos de funcines*/
// Muestra el menú principal y toma la opción del usuario.
void menu_principal(short&);
//Recibe un dato string y la cantidad de digitos que debe tener y verifica que sean numero y no letras
void verificador(bool&, bool&, string&, int&);
//Recauda todos los datos necesarios para calcular el recibo de consumo.
void ingresar_datos(string&, string&, string&, int&, char&);
//Valida si el usuario desea regresar al menu o no
void regreso_menu(char&);
//Calcula el monto conforme al consumo de agua
int valor_consumo_agua(int&, const int);
//Muestra al usuario el recibo a cancelar con los datos detallados según su consumo.
void recibo_consumo(string&, string&, string&, int&,
                    char&, const int, const int, const int,
                    const int, const double);

//Método principal
int main()
{
    //Muestra los acentos en español
    setlocale(LC_ALL, "Spanish");

    //Declaración de las constantes
    const int hidrantes{182};//Costo fijo de hidrantes
    const int pro_rec_hidr{50};//Costo fijo por Protección de Recurso Hídrico
    const int alcantarillado{1200};//Costo fijo por Alcantarillado
    const int valor_m_cubico{150};//Valor del metro cúbico
    const double iva{0.13};//Costo fijo por Impuesto al Valor Agregador correspondiente al 13%

    //Declaración de variables
    char cha_iva{' '};//Impuesto al Valor Agregado
    char opc_sn{' '};//Opción de si o no
    string num_cedula{""};//Número de cédula
    string nomb_dueno{""};//Nombre del dueño
    string num_medidor{""};//Número del medidor
    short opc_menu;//Opción del menú
    int met_cubicos{0};//Metros cúbicos


    do
    {
        //Llama a mostrar el menú principal y recibe la opción del usuario
        menu_principal(opc_menu);

        //Valida que hacer según la opción elegida por el usuario
        switch (opc_menu)
        {
        //Recauda los datos necesario para poder determinar el recibo de consumo
        case 1:
            //Va a repetirse mientras el usuario no desee volver al menú principal
            do
            {
                //Solicita y recibe los datos necesarios para generar el recibo de consumo
                ingresar_datos(num_cedula, nomb_dueno, num_medidor, met_cubicos, cha_iva);
                //Llama la función en donde el usuario decide regresar o no al menú principal
                regreso_menu(opc_sn);
            }//Fin del Do/While
            while(opc_sn == 'N');//Repitase mientra opc_sn sea igual a 'N'
            break;//Fin case 1

        //Muestra al usuario el recibo de cosumo
        case 2:

            //Si la información necesaria para generar el recibo no exite, entra en este if
            if(num_cedula == "" || nomb_dueno == "" || num_medidor == "" || met_cubicos == 0 || cha_iva == ' ')
            {
                system("CLS");// Borra pantalla
                cout << "Debe ingresar primero la información" << endl;
                system("PAUSE");// Detiene la pantalla
                system("CLS");// Borra pantalla
                break;
            }//fin del if
            //Repitase el recibo mientra el usuario no quiera salir al menú principal
            do
            {

                recibo_consumo(num_cedula, nomb_dueno, num_medidor, met_cubicos,
                               cha_iva, valor_m_cubico, hidrantes, pro_rec_hidr,
                               alcantarillado, iva);
                cout << endl;
                regreso_menu(opc_sn);

            }//Fin del Do//While
            while(opc_sn == 'N');

            break;

        //Salimos del progra
        case 3:
            cout << "Saliendo del Programa" << endl;
            system("PAUSE");// Realiza un breve pausa en la ejecucion del codigo
            system("CLS");// Borra pantalla
            break;

        //Caso por Deafault
        default:
            break;
        }//Fin del swith
    }//Fin del Do
    while(opc_menu != 3);  //Fin del Do/While

    return 0;
}

// Muestra el menú principal y toma la opción del usuario.
void menu_principal(short& opcion_menu)
{
    // Repite el menu hasta que el usuario decida una opcion validad o termine el programa
    do
    {
        cout << "Menú" << endl;
        cout << "1. Ingresar datos" << endl;
        cout << "2. Recibo de Cosumo" << endl;
        cout << "3. Salir del Programa" << endl;
        cout << "R/: ";

        cin >> opcion_menu;
        cin.clear();
        cin.ignore();//Ignora el espacio del teclado

        system("CLS"); // Borra pantalla

        if(opcion_menu < 1 || opcion_menu > 3)
        {
            cout << "Opción inválida, vuelva a intentarlo" << endl;

            system("pause"); // Hace una pausa hasta que el usuario presione una tecla
            system("cls");   // Borra el contenido de la pantalla
        }

    }
    while (opcion_menu < 1 || opcion_menu > 3);   // Fin del DO/WHILE
}

// Verifica que el dato pasado tenga la cantidad de digitos establecidos, además de que ninguno tenga letras y sean solo números
void verificador(bool& digit_correct, bool& sin_letras, string& dato, int& cant_digitos)
{
    //Si la cantidad de carateres de dato es diferente a la cantidad de dígitos establecidos
    if (dato.length() != cant_digitos)
    {
        //La cantidad de dígitos es incorrecta o falsa
        digit_correct = false;
    }
    //si la cantidad de digitos es igual a la cantidad de dígitos establecidos entonces entramos en el else
    else
    {
        //Cantidad de dígitos correcta o true
        digit_correct = true;
    }

    //Establecemos que sin letras es true
    sin_letras = true;

    //Para cada caracter "n" dentro de dato
    for (char n : dato)
    {
        //Si "n" contiene un caracter que no sea un dígito número entra en el if
        if (!isdigit(n))
        {
            //Se establece que el dato lleva letras por lo que sin letras es falso
            sin_letras = false;
        }
    }
}

//Solicita y recibe los datos necesarios para generar el recibo de consumo
void ingresar_datos(string& n_cedula, string& nom_dueno,
                    string& n_medidor, int& m_cubicos, char& iva_sn)
{
    bool dig_correcto{true};//Cantidad de digitos correcta
    bool no_letras{true};//Que contenga números y no letras
    int dig_cedula{9};//Cantidad de dígitos establecidos para la cédula
    int dig_medidor{6};//Cantidad de dígitos establecidos para el medidor;

    //Se recibe el número de cédula del la persona dueña del medidor
    do
    {
        cout << "Ingrese el número de cédula del dueño del servicio (9 dígitos):" << endl;
        cout << "R/: ";
        cin >> n_cedula;
        cin.clear();     // Borramos el búfer
        cin.ignore();    // ignoramos el primer espacio en blanco

        //Verificamos que cumpla con los 9 digitos y que sea solo numeros
        verificador(dig_correcto, no_letras, n_cedula, dig_cedula);

        //Si la cantidad de digitos es incorrecta y/o lleva letras
        if(dig_correcto == false || no_letras == false)
        {
            cout << "Valor de la cédula incorrecta" << endl;
            system("PAUSE");// Detiene la pantalla
            system("CLS");// Borra pantalla
        }//Fin del if
    }//Fin del Do/While
    while (dig_correcto == false || no_letras == false);

    system("CLS"); // Borra Pantalla

    //Se solicita y se recibe el nombre del dueño del servicio
    do
    {
        cout << "Ingrese el nombre del dueño del servicio:" << endl;
        cout << "R/: ";
        getline(cin, nom_dueno);

        //Si la cantidad de digitos es incorrecta y/o lleva letras
        if(nom_dueno == "")
        {
            cout << "Valor incorrecto" << endl;
            system("PAUSE"); // Detiene la pantalla
            system("CLS");   // Borra pantalla
        }//Fin del if
    }//Fin del Do/While
    while(nom_dueno == "");

    system("CLS"); // Borra Pantalla

    //Se solicita y se recibe el número de medidor
    do
    {
        cout << "Ingrese el número del medidor (6 dígitos):" << endl;
        cout << "R/: ";
        cin >> n_medidor;
        cin.clear();// Borramos el búfer
        cin.ignore();// ignoramos el primer espacio en blanco

        //Verificamos que cumpla con los 9 digitos y que sea solo numeros
        verificador(dig_correcto, no_letras, n_medidor, dig_medidor);

        //Si la cantidad de digitos es incorrecta y/o lleva letras
        if(dig_correcto == false || no_letras == false)
        {
            cout << "\nNúmero de medidor inválido, vuelva a intentarlo" << endl;
            system("PAUSE"); // Detiene la pantalla
            system("CLS");   // Borra pantalla
        }//Fin del if
    }//Fin del Do/While
    while (dig_correcto == false || no_letras == false);

    system("CLS"); // Borra Pantalla

    //Se solicita y se recibe la cantidad de metros cúbicos consumidos
    do
    {
        //Se establece un string para verificar luego que cada caracter sea un dígito
        string str_mcubicos = "";

        cout << "Ingrese el valor de metros cúbicos del medidor (valor numérico):" << endl;
        cout << "R/: ";
        cin >> str_mcubicos;//Se recibe la cantidad de metros cúbicos
        cin.clear();// Borramos el búfer
        cin.ignore();// ignoramos el primer espacio en blanco

        //se establece no letras como true
        no_letras = true;

        //Para cada caracter "c" dentro de str_mcubicos
        for(char c : str_mcubicos)
        {
            //Si el caracter "c" es diferente a un número entra en el if
            if(!isdigit(c))
            {
                //Se establece no letras como falso
                no_letras = false;
            }//Fin del if
        }//Fin de bucle for

        //Si los metros cúbicos no contienen letras entra en el if
        if(no_letras == true)
        {
            /*
                Método tomado de:
                DevDocs: https://devdocs.io/cpp/string/byte/atoi
            */
            m_cubicos = stoi(str_mcubicos);//Convertimos el valor string a un valor int

            //Si los metros cúbicos son menores a 0 o mayores que 1000 entra en el if
            if(m_cubicos < 0 || m_cubicos > 1000)
            {
                cout << "\nValor inválido, vuelva a intentarlo" << endl;
                system("PAUSE");// Detiene la pantalla
                system("CLS");// Borra pantalla
            }
        }//fin del if
    }//Fin del Do/While
    while (no_letras == false || m_cubicos < 0 || m_cubicos > 1000); //Fin del Do/While

    system("CLS");// Borra pantalla

    //Se solicita y se recibe esta excento del IVA
    do
    {
        cout << "Está exento del IVA (S/N)?: ";
        cout << "R/: ";
        cin >> iva_sn;//Se recibe si se cobra o no el IVA
        cin.clear();// Borramos el búfer
        cin.ignore();// ignoramos el primer espacio en blanco
        system("CLS");// Borra pantalla

        iva_sn = toupper(iva_sn);//Convertimos el caracter en Mayúscula
    }
    //Repitase mientras que iva_sn sea un dígito o que iva_sn sea diferente a "N" Y "S"
    while(isdigit(iva_sn) == true || (iva_sn != 'S' && iva_sn != 'N'));

    system("CLS");// Borra pantalla

}//Fin de la funcon Ingresar datos.

//Valida si el usuario desea regresar al menú principal
void regreso_menu (char& opc_sn)
{
    do
    {
        cout << "Desea regresar al menú principal (S/N)?: ";
        cout << "R/: ";
        cin >> opc_sn;
        cin.clear();// Borramos el búfer
        cin.ignore();// ignoramos el primer espacio en blanco
        system("CLS");// Borra pantalla

        opc_sn = toupper(opc_sn);//Convertimos el caracter en Mayúscula
    }
    //Repitase mientras que opc_sn sea un dígito o que opc_sn sea diferente a "N" Y "S"
    while(isdigit(opc_sn) == true || (opc_sn != 'S' && opc_sn != 'N'));
}//Fin de la funcion regreso_menu

//Calcula el costo del consumo de agua según los metros cúbicos gastados
int valor_consumo_agua(int& m_cubicos, const int v_con_agua)
{
    double tot_cons_agua{0.0};//Valor total del consumo de agua

    //Si la cantidad de metros cúbicos es menor o igual a 10
    if(m_cubicos <= 10)
    {
        //Total de consumo de agua es igual a la cantidad de los metros cúbicos por el valor del metro cúbico de agua que es 150
        tot_cons_agua = m_cubicos * v_con_agua;
    }
    //Si la cantidad de metros cúbicos es mayor a 10 y menor o igual que 50
    else if(m_cubicos > 10 && m_cubicos <= 50)
    {
        //total consumo de agua es igual a 1500 de los primeros 10 metros + el restante por 150 + el porcentaje de penalización de 10%
        tot_cons_agua = 1500 + (((m_cubicos-10)*v_con_agua) + (((m_cubicos-10)*v_con_agua) * 0.10));
    }
    //Si la cantidad de metros cúbicos es mayor a 50 y menor o igual que 100
    else if(m_cubicos > 50 && m_cubicos <= 100)
    {
        //total consumo de agua es igual a 1500 + 6600 de los primeros 10 y 40 metros + el restante por 150 + el porcentaje de penalización de 20%
        tot_cons_agua = 1500 + 6600 + (((m_cubicos-50)*v_con_agua) + (((m_cubicos-50)*v_con_agua) * 0.20));
    }
    //Si la cantidad de metros cúbicos es mayor a 100
    else if(m_cubicos > 100)
    {
        //total consumo de agua es igual a 1500 + 6600 + 9000 de los primeros 10, 40 y 50 metros + el restante por 150 + el porcentaje de penalización de 30%
        tot_cons_agua = 1500 + 6600 + 9000 + (((m_cubicos-100)*v_con_agua) + (((m_cubicos-100)*v_con_agua) * 0.30));
    }
    //Retornamos el total del consumo de agua
    return tot_cons_agua;
}

void recibo_consumo(string& n_cedula, string& nom_dueno,
                    string& n_medidor, int& m_cubicos, char& iva_sn,
                    const int v_met_cubico, const int hidrante, const int prot_recu_hidri,
                    const int alcantari, const double imp_val_agr)
{
    double subtotal{0.0};//Total del recibo pero sin impuestos
    double total{0.0};//Total final a pagar por el usuario
    cout << "------------------------------------------------------------" << endl;
    cout << "                     Recibo de consumo                      " << endl;
    cout << "------------------------------------------------------------" << endl;//60

    cout << "Número de cédula:                   " << n_cedula << endl;
    cout << "Nombre de dueño del servicio:       " << nom_dueno << endl;
    cout << "Número de medidor:                  " << n_medidor << endl;
    cout << "Metros cúbicos consumidos:          " << m_cubicos << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << "                           Recibo                           " << endl;
    cout << "------------------------------------------------------------" << endl;

    cout << "Consumo de Agua:                    " << valor_consumo_agua(m_cubicos, v_met_cubico) << endl;
    cout << "Hidrantes:                          " << hidrante << endl;
    cout << "Protección Recurso Hídrico:         " << prot_recu_hidri << endl;
    cout << "Alcantarillado:                     " << alcantari << endl;

    //El subtotal es la suma de todos los rubros calculados según el consumo y de los costos fijos, no incluye IVA
    subtotal = valor_consumo_agua(m_cubicos, v_met_cubico) + hidrante + prot_recu_hidri + alcantari;

    //Si el recibo no esta excento de IVA dentra en el if
    if(iva_sn == 'N')
    {
        //Se le agrega al total de la factura el subtotal más el IVA correspondiente
        total = subtotal + (subtotal * imp_val_agr);
        cout << "IVA:                                " << subtotal * imp_val_agr << endl;
    }
    //si el recibo está excento de IVA, no se le agrega impusto.
    else if(iva_sn == 'S')
    {
        //Al no cobrarse IVA el subtotal queda como total de factura
        total = subtotal;
        cout << "IVA:                                " << 0 << endl;
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "Total a pagar en colones:           " << total << endl;
    cout << "------------------------------------------------------------" << endl;
}

