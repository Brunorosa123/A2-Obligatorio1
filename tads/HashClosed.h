class HashClosed {
public:
    // pre: -
    // post: creates a hash table with the given size
    virtual void crearTabla(int tam) = 0;

    // pre: -
    // post: inserts the given key into the hash table
    virtual void insertar(char key) = 0;

    // pre: -
    // post: returns the quantity of the given key in the hash table
    virtual int buscar(char key) = 0;

    // pre: -
    // post: removes one occurrence of the given key from the hash table
    virtual void eliminar(char key) = 0;
};