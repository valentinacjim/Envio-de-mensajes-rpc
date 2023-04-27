struct respuesta {
	int result;
	string value1<256>;
	int value2;
	double value3;

};


program CLAVES {
	version OPERACIONESVER {
		int server_init() = 1;
		int server_exist(int key) = 2;
		int server_set_value(int key, string value1, int value2, double value3) = 3;
		respuesta server_get_value(int key) = 4;
		int server_delete_value(int key) = 5;
		int server_modify_value(int key, string, int value2, double value3) = 6;
		int server_copy_key(int key1, int key2) = 7;
 	} = 1;
} = 99;

