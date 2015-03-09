
extern zend_class_entry *tartan_datetime_ce;

ZEPHIR_INIT_CLASS(Tartan_Datetime);

PHP_METHOD(Tartan_Datetime, __construct);
PHP_METHOD(Tartan_Datetime, say);
PHP_METHOD(Tartan_Datetime, toGregorian);
PHP_METHOD(Tartan_Datetime, div);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, convert)
	ZEND_ARG_INFO(0, jalali)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_togregorian, 0, 0, 3)
	ZEND_ARG_INFO(0, j_y)
	ZEND_ARG_INFO(0, j_m)
	ZEND_ARG_INFO(0, j_d)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_div, 0, 0, 2)
	ZEND_ARG_INFO(0, a)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tartan_datetime_method_entry) {
	PHP_ME(Tartan_Datetime, __construct, arginfo_tartan_datetime___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Tartan_Datetime, say, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, toGregorian, arginfo_tartan_datetime_togregorian, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, div, arginfo_tartan_datetime_div, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
  PHP_FE_END
};
