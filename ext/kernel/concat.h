#define ZEPHIR_CONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SV(result, op1, op2) \
	 zephir_concat_sv(&result, op1, sizeof(op1)-1, op2, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_SVSVSVSVSV(result, op1, op2, op3, op4, op5, op6, op7, op8, op9, op10) \
	 zephir_concat_svsvsvsvsv(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, op6, op7, sizeof(op7)-1, op8, op9, sizeof(op9)-1, op10, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_SVSVSVSVSV(result, op1, op2, op3, op4, op5, op6, op7, op8, op9, op10) \
	 zephir_concat_svsvsvsvsv(&result, op1, sizeof(op1)-1, op2, op3, sizeof(op3)-1, op4, op5, sizeof(op5)-1, op6, op7, sizeof(op7)-1, op8, op9, sizeof(op9)-1, op10, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VS(result, op1, op2) \
	 zephir_concat_vs(&result, op1, op2, sizeof(op2)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSV(result, op1, op2, op3, op4, op5) \
	 zephir_concat_vsvsv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSV(result, op1, op2, op3, op4, op5) \
	 zephir_concat_vsvsv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSVS(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSVS(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvs(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSVSVSVSV(result, op1, op2, op3, op4, op5, op6, op7, op8, op9, op10, op11) \
	 zephir_concat_vsvsvsvsvsv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, op9, op10, sizeof(op10)-1, op11, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSVSVSVSV(result, op1, op2, op3, op4, op5, op6, op7, op8, op9, op10, op11) \
	 zephir_concat_vsvsvsvsvsv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, sizeof(op6)-1, op7, op8, sizeof(op8)-1, op9, op10, sizeof(op10)-1, op11, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VSVSVV(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VSVSVV(result, op1, op2, op3, op4, op5, op6) \
	 zephir_concat_vsvsvv(&result, op1, op2, sizeof(op2)-1, op3, op4, sizeof(op4)-1, op5, op6, 1 TSRMLS_CC);

#define ZEPHIR_CONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 0 TSRMLS_CC);
#define ZEPHIR_SCONCAT_VV(result, op1, op2) \
	 zephir_concat_vv(&result, op1, op2, 1 TSRMLS_CC);


void zephir_concat_sv(zval **result, const char *op1, zend_uint op1_len, zval *op2, int self_var TSRMLS_DC);
void zephir_concat_svsvsvsvsv(zval **result, const char *op1, zend_uint op1_len, zval *op2, const char *op3, zend_uint op3_len, zval *op4, const char *op5, zend_uint op5_len, zval *op6, const char *op7, zend_uint op7_len, zval *op8, const char *op9, zend_uint op9_len, zval *op10, int self_var TSRMLS_DC);
void zephir_concat_vs(zval **result, zval *op1, const char *op2, zend_uint op2_len, int self_var TSRMLS_DC);
void zephir_concat_vsvsv(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, int self_var TSRMLS_DC);
void zephir_concat_vsvsvs(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, const char *op6, zend_uint op6_len, int self_var TSRMLS_DC);
void zephir_concat_vsvsvsvsvsv(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, const char *op6, zend_uint op6_len, zval *op7, const char *op8, zend_uint op8_len, zval *op9, const char *op10, zend_uint op10_len, zval *op11, int self_var TSRMLS_DC);
void zephir_concat_vsvsvv(zval **result, zval *op1, const char *op2, zend_uint op2_len, zval *op3, const char *op4, zend_uint op4_len, zval *op5, zval *op6, int self_var TSRMLS_DC);
void zephir_concat_vv(zval **result, zval *op1, zval *op2, int self_var TSRMLS_DC);
void zephir_concat_function(zval *result, zval *op1, zval *op2 TSRMLS_DC);