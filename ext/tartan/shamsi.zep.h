
extern zend_class_entry *tartan_shamsi_ce;

ZEPHIR_INIT_CLASS(Tartan_Shamsi);

PHP_METHOD(Tartan_Shamsi, setLocale);
PHP_METHOD(Tartan_Shamsi, getLocale);
PHP_METHOD(Tartan_Shamsi, setCalendar);
PHP_METHOD(Tartan_Shamsi, getCalendar);
PHP_METHOD(Tartan_Shamsi, __construct);
PHP_METHOD(Tartan_Shamsi, set);
PHP_METHOD(Tartan_Shamsi, guessPattern);
PHP_METHOD(Tartan_Shamsi, getFormatter);
PHP_METHOD(Tartan_Shamsi, latinizeDigits);
PHP_METHOD(Tartan_Shamsi, modify);
PHP_METHOD(Tartan_Shamsi, getTimestamp);
PHP_METHOD(Tartan_Shamsi, setTimestamp);
PHP_METHOD(Tartan_Shamsi, setDate);
PHP_METHOD(Tartan_Shamsi, say);
PHP_METHOD(Tartan_Shamsi, setTimezone);
PHP_METHOD(Tartan_Shamsi, format);
PHP_METHOD(Tartan_Shamsi, classicFormat);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_setlocale, 0, 0, 1)
	ZEND_ARG_INFO(0, locale)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_setcalendar, 0, 0, 1)
	ZEND_ARG_INFO(0, calendar)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, time)
	ZEND_ARG_INFO(0, timezone)
	ZEND_ARG_INFO(0, calendar)
	ZEND_ARG_INFO(0, locale)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_set, 0, 0, 1)
	ZEND_ARG_INFO(0, time)
	ZEND_ARG_INFO(0, timezone)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_guesspattern, 0, 0, 1)
	ZEND_ARG_INFO(0, time)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_getformatter, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_latinizedigits, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_modify, 0, 0, 1)
	ZEND_ARG_INFO(0, modify)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_settimestamp, 0, 0, 1)
	ZEND_ARG_INFO(0, unixtimestamp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_setdate, 0, 0, 3)
	ZEND_ARG_INFO(0, year)
	ZEND_ARG_INFO(0, month)
	ZEND_ARG_INFO(0, day)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_settimezone, 0, 0, 1)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_format, 0, 0, 1)
	ZEND_ARG_INFO(0, pattern)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tartan_shamsi_classicformat, 0, 0, 1)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, timezone)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tartan_shamsi_method_entry) {
	PHP_ME(Tartan_Shamsi, setLocale, arginfo_tartan_shamsi_setlocale, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, getLocale, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, setCalendar, arginfo_tartan_shamsi_setcalendar, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, getCalendar, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, __construct, arginfo_tartan_shamsi___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Tartan_Shamsi, set, arginfo_tartan_shamsi_set, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, guessPattern, arginfo_tartan_shamsi_guesspattern, ZEND_ACC_PROTECTED)
	PHP_ME(Tartan_Shamsi, getFormatter, arginfo_tartan_shamsi_getformatter, ZEND_ACC_PROTECTED)
	PHP_ME(Tartan_Shamsi, latinizeDigits, arginfo_tartan_shamsi_latinizedigits, ZEND_ACC_PROTECTED)
	PHP_ME(Tartan_Shamsi, modify, arginfo_tartan_shamsi_modify, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, getTimestamp, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, setTimestamp, arginfo_tartan_shamsi_settimestamp, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, setDate, arginfo_tartan_shamsi_setdate, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, say, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tartan_Shamsi, setTimezone, arginfo_tartan_shamsi_settimezone, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, format, arginfo_tartan_shamsi_format, ZEND_ACC_PUBLIC)
	PHP_ME(Tartan_Shamsi, classicFormat, arginfo_tartan_shamsi_classicformat, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
