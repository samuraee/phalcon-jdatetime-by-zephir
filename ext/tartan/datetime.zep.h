
extern zend_class_entry *tartan_datetime_ce;

ZEPHIR_INIT_CLASS(Tartan_Datetime);

PHP_METHOD(Tartan_Datetime, __construct);
PHP_METHOD(Tartan_Datetime, date);
PHP_METHOD(Tartan_Datetime, toJalali);
PHP_METHOD(Tartan_Datetime, toGregorian);
PHP_METHOD(Tartan_Datetime, checkdate);
PHP_METHOD(Tartan_Datetime, mktime);
PHP_METHOD(Tartan_Datetime, strftime);
PHP_METHOD(Tartan_Datetime, div);
PHP_METHOD(Tartan_Datetime, substr);
PHP_METHOD(Tartan_Datetime, convertNumbers);
PHP_METHOD(Tartan_Datetime, getMonthNames);
PHP_METHOD(Tartan_Datetime, getDayNames);
PHP_METHOD(Tartan_Datetime, filterArray);
PHP_METHOD(Tartan_Datetime, gDate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, convert)
	ZEND_ARG_INFO(0, jalali)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_date, 0, 0, 1)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, stamp)
	ZEND_ARG_INFO(0, convert)
	ZEND_ARG_INFO(0, jalali)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_tojalali, 0, 0, 3)
	ZEND_ARG_INFO(0, g_y)
	ZEND_ARG_INFO(0, g_m)
	ZEND_ARG_INFO(0, g_d)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_togregorian, 0, 0, 3)
	ZEND_ARG_INFO(0, j_y)
	ZEND_ARG_INFO(0, j_m)
	ZEND_ARG_INFO(0, j_d)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_checkdate, 0, 0, 3)
	ZEND_ARG_INFO(0, month)
	ZEND_ARG_INFO(0, day)
	ZEND_ARG_INFO(0, year)
	ZEND_ARG_INFO(0, jalali)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_mktime, 0, 0, 6)
	ZEND_ARG_INFO(0, hour)
	ZEND_ARG_INFO(0, minute)
	ZEND_ARG_INFO(0, second)
	ZEND_ARG_INFO(0, month)
	ZEND_ARG_INFO(0, day)
	ZEND_ARG_INFO(0, year)
	ZEND_ARG_INFO(0, jalali)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_strftime, 0, 0, 1)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, stamp)
	ZEND_ARG_INFO(0, convert)
	ZEND_ARG_INFO(0, jalali)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_div, 0, 0, 2)
	ZEND_ARG_INFO(0, a)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_substr, 0, 0, 3)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, start)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_convertnumbers, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, matches, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_getmonthnames, 0, 0, 1)
	ZEND_ARG_INFO(0, month)
	ZEND_ARG_INFO(0, shorten)
	ZEND_ARG_INFO(0, len)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_getdaynames, 0, 0, 1)
	ZEND_ARG_INFO(0, day)
	ZEND_ARG_INFO(0, shorten)
	ZEND_ARG_INFO(0, len)
	ZEND_ARG_INFO(0, numeric)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_filterarray, 0, 0, 2)
	ZEND_ARG_ARRAY_INFO(0, needle, 0)
	ZEND_ARG_ARRAY_INFO(0, heystack, 0)
	ZEND_ARG_ARRAY_INFO(0, always, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_datetime_gdate, 0, 0, 1)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, stamp)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tartan_datetime_method_entry) {
	PHP_ME(Tartan_Datetime, __construct, arginfo_tartan_datetime___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Tartan_Datetime, date, arginfo_tartan_datetime_date, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, toJalali, arginfo_tartan_datetime_tojalali, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, toGregorian, arginfo_tartan_datetime_togregorian, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, checkdate, arginfo_tartan_datetime_checkdate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, mktime, arginfo_tartan_datetime_mktime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, strftime, arginfo_tartan_datetime_strftime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, div, arginfo_tartan_datetime_div, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, substr, arginfo_tartan_datetime_substr, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, convertNumbers, arginfo_tartan_datetime_convertnumbers, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, getMonthNames, arginfo_tartan_datetime_getmonthnames, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, getDayNames, arginfo_tartan_datetime_getdaynames, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, filterArray, arginfo_tartan_datetime_filterarray, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Datetime, gDate, arginfo_tartan_datetime_gdate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
  PHP_FE_END
};
