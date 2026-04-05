class HashClosed {
    public:

        //pre: tamaño mayor a 0
        //post: devuelve una tabla hash cerrada vacía
        tabla crearTabla(int tam);

        //pre: tamaño mayor a 0
        //post: inserta la clave con su valor, o aumenta el valor si la clave ya existe
        void insertar(tabla t, char key);

        //pre: la clave debe existir en la tabla
        //post: devuelve la cantidad asociada a la clave
        int buscar(tabla t, char key);

        //pre: la clave debe existir en la tabla
        //post: decrece el valor asociado a la clave
        void eliminar(tabla t, char key);
};