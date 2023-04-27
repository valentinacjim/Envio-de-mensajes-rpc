struct respuesta {
    int key;
    string value1<256>;
    int value2;
    double value3;
};

program CLAVES {
    version CLAVESVER{
        int init() = 1;
        int set_value(int key, string value1<256>, int value2, double value3) = 2;
        respuesta get_value(int key) = 3;
        int modify_value(int key, string value1<256>, int value2, double value3) = 4;
        int delete_value(int key) = 5;
        int exist() = 6;
        int copy_key(int key1, int key2) = 7;
    } = 1;
} = 99;