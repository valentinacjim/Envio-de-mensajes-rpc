/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "claves.h"

bool_t
init_1_svc(int *result, struct svc_req *rqstp)
{
	bool_t retval;

	*result = init();
	retval = TRUE;

	return retval;
}

bool_t
set_value_1_svc(int key, char *value1, int value2, double value3, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	*result = set_value(key, value1, value2, value3);
	retval = TRUE;

	return retval;
}

bool_t
get_value_1_svc(int key, respuesta *result,  struct svc_req *rqstp)
{
	bool_t retval;

	*result = get_value(key);
	retval = TRUE;

	return retval;
}

bool_t
modify_value_1_svc(int key, char *value1, int value2, double value3, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	*result = modify_value(key, value1, value2, value3);
	retval = TRUE;

	return retval;
}

bool_t
delete_value_1_svc(int key, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	*result = delete_value(key);
	retval = TRUE;

	return retval;
}

bool_t
exist_1_svc(int *result, struct svc_req *rqstp)
{
	bool_t retval;

	*result = exist();
	retval = TRUE;

	return retval;
}

bool_t
copy_key_1_svc(int key1, int key2, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	*result = copy_key(key1, key2);
	retval = TRUE;

	return retval;
}

int
claves_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
