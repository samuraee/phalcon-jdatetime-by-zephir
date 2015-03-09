
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/hash.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


ZEPHIR_INIT_CLASS(Tartan_Shamsi) {

	ZEPHIR_REGISTER_CLASS_EX(Tartan, Shamsi, tartan, shamsi, zephir_get_internal_ce(SS("datetime") TSRMLS_CC), tartan_shamsi_method_entry, 0);

	/**
	 * @var string The current locale in use
	 */
	zend_declare_property_null(tartan_shamsi_ce, SL("locale"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string The current calendar in use
	 */
	zend_declare_property_null(tartan_shamsi_ce, SL("calendar"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * @var string The current locale in use
 */
PHP_METHOD(Tartan_Shamsi, setLocale) {

	zval *locale;

	zephir_fetch_params(0, 1, 0, &locale);



	zephir_update_property_this(this_ptr, SL("locale"), locale TSRMLS_CC);

}

/**
 * @var string The current locale in use
 */
PHP_METHOD(Tartan_Shamsi, getLocale) {


	RETURN_MEMBER(this_ptr, "locale");

}

/**
 * @var string The current calendar in use
 */
PHP_METHOD(Tartan_Shamsi, setCalendar) {

	zval *calendar;

	zephir_fetch_params(0, 1, 0, &calendar);



	zephir_update_property_this(this_ptr, SL("calendar"), calendar TSRMLS_CC);

}

/**
 * @var string The current calendar in use
 */
PHP_METHOD(Tartan_Shamsi, getCalendar) {


	RETURN_MEMBER(this_ptr, "calendar");

}

/**
 * Creates a new instance of IntlDateTime
 *
 * @param mixed $time Unix timestamp or strtotime() compatible string or another DateTime object
 * @param mixed $timezone DateTimeZone object or timezone identifier as full name (e.g. Asia/Tehran) or abbreviation (e.g. IRDT).
 * @param string $calendar any calendar supported by ICU (e.g. gregorian, persian, islamic, ...)
 * @param string $locale any locale supported by ICU
 * @param string $pattern the date pattern in which $time is formatted.
 * @return IntlDateTime
 */
PHP_METHOD(Tartan_Shamsi, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *calendar = NULL, *locale = NULL, *pattern = NULL;
	zval *time = NULL, *timezone = NULL, *calendar_param = NULL, *locale_param = NULL, *pattern_param = NULL, _0, *_1 = NULL, *_3 = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 5, &time, &timezone, &calendar_param, &locale_param, &pattern_param);

	if (!time) {
		time = ZEPHIR_GLOBAL(global_null);
	}
	if (!timezone) {
		ZEPHIR_CPY_WRT(timezone, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(timezone);
	}
	if (!calendar_param) {
		ZEPHIR_INIT_VAR(calendar);
		ZVAL_STRING(calendar, "gregorian", 1);
	} else {
		zephir_get_strval(calendar, calendar_param);
	}
	if (!locale_param) {
		ZEPHIR_INIT_VAR(locale);
		ZVAL_STRING(locale, "en_US", 1);
	} else {
		zephir_get_strval(locale, locale_param);
	}
	if (!pattern_param) {
		ZEPHIR_INIT_VAR(pattern);
		ZVAL_EMPTY_STRING(pattern);
	} else {
		zephir_get_strval(pattern, pattern_param);
	}


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "DateTimeZone", 0);
	ZEPHIR_CALL_FUNCTION(&_1, "is_a", &_2, timezone, &_0);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(timezone))) {
		ZEPHIR_INIT_NVAR(timezone);
		object_init_ex(timezone, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
		ZEPHIR_CALL_FUNCTION(&_3, "date_default_timezone_get", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, timezone, "__construct", NULL, _3);
		zephir_check_call_status();
	} else if (!zephir_is_true(_1)) {
		ZEPHIR_INIT_NVAR(timezone);
		object_init_ex(timezone, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, timezone, "__construct", NULL, timezone);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_4);
	ZVAL_NULL(_4);
	ZEPHIR_CALL_PARENT(NULL, tartan_shamsi_ce, this_ptr, "__construct", NULL, _4, timezone);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setlocale", NULL, locale);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcalendar", NULL, calendar);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(time))) {
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_NULL(_4);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, time, _4, pattern);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Alters object's internal timestamp with a string acceptable by strtotime() or a Unix timestamp or a DateTime object.
 *
 * @param mixed $time Unix timestamp or strtotime() compatible string or another DateTime object
 * @param mixed $timezone DateTimeZone object or timezone identifier as full name (e.g. Asia/Tehran) or abbreviation (e.g. IRDT).
 * @param string $pattern the date pattern in which $time is formatted.
 * @return IntlDateTime The modified DateTime.
 */
PHP_METHOD(Tartan_Shamsi, set) {

	zval *_10;
	zend_bool _3, _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_7 = NULL;
	zval *time = NULL, *timezone = NULL, *pattern = NULL, tempTimezone = zval_used_for_init, defaultTimezone = zval_used_for_init, _0 = zval_used_for_init, *_1 = NULL, *_4 = NULL, *_6 = NULL, *_8 = NULL, *_9 = NULL, *_11 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &time, &timezone, &pattern);

	ZEPHIR_SEPARATE_PARAM(time);
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}
	if (!pattern) {
		pattern = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "DateTime", 0);
	ZEPHIR_CALL_FUNCTION(&_1, "is_a", &_2, time, &_0);
	zephir_check_call_status();
	_3 = Z_TYPE_P(time) != IS_LONG;
	if (!(_3)) {
		_3 = !(ZEPHIR_IS_EMPTY(pattern));
	}
	if (zephir_is_true(_1)) {
		ZEPHIR_INIT_VAR(_4);
		ZVAL_STRING(_4, "U", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&time, time, "format", NULL, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
	} else if (_3) {
		if (!(ZEPHIR_IS_EMPTY(pattern))) {
			ZEPHIR_CALL_METHOD(&pattern, this_ptr, "guesspattern", NULL, time);
			zephir_check_call_status();
		}
		_5 = !(ZEPHIR_IS_EMPTY(pattern));
		if (_5) {
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "/((?:[+-]?\\d+)|next|last|previous)\\s*(year|month)s?/i", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_FUNCTION(&_6, "preg_match", &_7, _4, time);
			zephir_check_temp_parameter(_4);
			zephir_check_call_status();
			_5 = zephir_is_true(_6);
		}
		if (_5) {
			if (!(ZEPHIR_IS_EMPTY(timezone))) {
				ZEPHIR_CALL_METHOD(&tempTimezone, this_ptr, "gettimezone", NULL);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, timezone);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_FUNCTION(&_8, "time", NULL);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimestamp", NULL, _8);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "modify", NULL, time);
			zephir_check_call_status();
			if (!(ZEPHIR_IS_EMPTY(timezone))) {
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, tempTimezone);
				zephir_check_call_status();
			}
			RETURN_THIS();
		}
		ZEPHIR_INIT_VAR(_9);
		if (ZEPHIR_IS_EMPTY(timezone)) {
			ZEPHIR_CALL_METHOD(&_9, this_ptr, "gettimezone", NULL);
			zephir_check_call_status();
		} else {
			ZEPHIR_CPY_WRT(_9, timezone);
		}
		ZEPHIR_CPY_WRT(timezone, _9);
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_STRING(&_0, "DateTimeZone", 0);
		ZEPHIR_CALL_FUNCTION(&_8, "is_a", &_2, timezone, &_0);
		zephir_check_call_status();
		if (zephir_is_true(_8)) {
			ZEPHIR_CALL_METHOD(&timezone, timezone, "getname", NULL);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_FUNCTION(&defaultTimezone, "date_default_timezone_get", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "date_default_timezone_set", NULL, timezone);
		zephir_check_call_status();
		if (!(ZEPHIR_IS_EMPTY(pattern))) {
			ZEPHIR_INIT_VAR(_10);
			array_init_size(_10, 3);
			add_assoc_stringl_ex(_10, SS("timezone"), SL("GMT"), 1);
			zephir_array_update_string(&_10, SL("pattern"), &pattern, PH_COPY | PH_SEPARATE);
			ZEPHIR_CALL_METHOD(&_8, this_ptr, "getformatter", NULL, _10);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_11, _8, "parse", NULL, time);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(time, _11);
			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_STRING(&_0, "Z", 0);
			ZEPHIR_CALL_FUNCTION(&_11, "date", NULL, &_0, time);
			zephir_check_call_status();
			ZEPHIR_SUB_ASSIGN(time, _11);
		} else {
			ZEPHIR_CALL_FUNCTION(&_8, "strtotime", NULL, time);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(time, _8);
		}
		ZEPHIR_CALL_FUNCTION(NULL, "date_default_timezone_set", NULL, &defaultTimezone);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimestamp", NULL, time);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Tries to guess the date pattern in which $time is formatted.
 *
 * @param string $time The date string
 * @return string Detected ICU pattern on success, FALSE otherwise.
 */
PHP_METHOD(Tartan_Shamsi, guessPattern) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *pattern = NULL;
	zval *match;
	zval *time = NULL, *shortDateRegex, *longDateRegex, *timeRegex, *separator = NULL, *_0, *_1, *_2 = NULL, *_4, *_5 = NULL, *_6, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10, *_11, *_12 = NULL, *_13, *_14, *_15, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &time);

	ZEPHIR_SEPARATE_PARAM(time);


	ZEPHIR_INIT_VAR(match);
	array_init(match);
	ZEPHIR_INIT_VAR(pattern);
	ZVAL_EMPTY_STRING(pattern);
	ZEPHIR_INIT_VAR(_0);
	zephir_fast_trim(_0, time, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&time, this_ptr, "latinizedigits", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(shortDateRegex);
	ZVAL_STRING(shortDateRegex, "(\d{2,4})(-|\\\\|/)\d{1,2}\2\d{1,2}", 1);
	ZEPHIR_INIT_VAR(longDateRegex);
	ZVAL_STRING(longDateRegex, "([^\d]*\s)?\d{1,2}(-| )[^-\s\d]+\4(\d{2,4})", 1);
	ZEPHIR_INIT_VAR(timeRegex);
	ZVAL_STRING(timeRegex, "\d{1,2}:\d{1,2}(:\d{1,2})?(\s.*)?", 1);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SVSVSVS(_1, "@^(?:(?:", shortDateRegex, ")|(?:", longDateRegex, "))(\\s+", timeRegex, ")?$@");
	Z_SET_ISREF_P(match);
	ZEPHIR_CALL_FUNCTION(&_2, "preg_match", &_3, _1, time, match);
	Z_UNSET_ISREF_P(match);
	zephir_check_call_status();
	if (zephir_is_true(_2)) {
		ZEPHIR_OBS_VAR(_4);
		zephir_array_fetch_long(&_4, match, 1, PH_NOISY, "tartan/shamsi.zep", 112 TSRMLS_CC);
		if (!(ZEPHIR_IS_EMPTY(_4))) {
			ZEPHIR_OBS_VAR(separator);
			zephir_array_fetch_long(&separator, match, 2, PH_NOISY, "tartan/shamsi.zep", 113 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_5);
			zephir_array_fetch_long(&_6, match, 1, PH_NOISY | PH_READONLY, "tartan/shamsi.zep", 114 TSRMLS_CC);
			if (zephir_fast_strlen_ev(_6) == 2) {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_STRING(_5, "yy", 1);
			} else {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_STRING(_5, "yyyy", 1);
			}
			zephir_get_strval(pattern, _5);
			ZEPHIR_INIT_VAR(_7);
			ZEPHIR_CONCAT_VSVS(_7, separator, "MM", separator, "dd");
			zephir_concat_self(&pattern, _7 TSRMLS_CC);
		} else {
			ZEPHIR_OBS_NVAR(separator);
			zephir_array_fetch_long(&separator, match, 4, PH_NOISY, "tartan/shamsi.zep", 117 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_CONCAT_SVSV(_5, "dd", separator, "LLL", separator);
			zephir_get_strval(pattern, _5);
			ZEPHIR_INIT_LNVAR(_7);
			zephir_array_fetch_long(&_6, match, 5, PH_NOISY | PH_READONLY, "tartan/shamsi.zep", 119 TSRMLS_CC);
			if (zephir_fast_strlen_ev(_6) == 2) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_STRING(_7, "yy", 1);
			} else {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_STRING(_7, "yyyy", 1);
			}
			zephir_concat_self(&pattern, _7 TSRMLS_CC);
			ZEPHIR_OBS_VAR(_8);
			zephir_array_fetch_long(&_8, match, 3, PH_NOISY, "tartan/shamsi.zep", 120 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_8))) {
				ZEPHIR_INIT_VAR(_9);
				zephir_array_fetch_long(&_10, match, 3, PH_NOISY | PH_READONLY, "tartan/shamsi.zep", 121 TSRMLS_CC);
				ZEPHIR_INIT_VAR(_11);
				ZVAL_STRING(_11, "/,\\s+$/", ZEPHIR_TEMP_PARAM_COPY);
				ZEPHIR_CALL_FUNCTION(&_12, "preg_match", &_3, _11, _10);
				zephir_check_temp_parameter(_11);
				zephir_check_call_status();
				if (zephir_is_true(_12)) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "E, ", 1);
				} else {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "E ", 1);
				}
				ZEPHIR_INIT_VAR(_13);
				ZEPHIR_CONCAT_VV(_13, _9, pattern);
				zephir_get_strval(pattern, _13);
			}
		}
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_long(&_8, match, 6, PH_NOISY, "tartan/shamsi.zep", 124 TSRMLS_CC);
		if (!(ZEPHIR_IS_EMPTY(_8))) {
			ZEPHIR_INIT_LNVAR(_5);
			ZEPHIR_OBS_VAR(_14);
			zephir_array_fetch_long(&_14, match, 8, PH_NOISY, "tartan/shamsi.zep", 125 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_14))) {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_STRING(_5, " hh:mm", 1);
			} else {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_STRING(_5, " HH:mm", 1);
			}
			zephir_concat_self(&pattern, _5 TSRMLS_CC);
			ZEPHIR_OBS_VAR(_15);
			zephir_array_fetch_long(&_15, match, 7, PH_NOISY, "tartan/shamsi.zep", 126 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_15))) {
				zephir_concat_self_str(&pattern, ":ss", sizeof(":ss")-1 TSRMLS_CC);
			}
			ZEPHIR_OBS_VAR(_16);
			zephir_array_fetch_long(&_16, match, 8, PH_NOISY, "tartan/shamsi.zep", 127 TSRMLS_CC);
			if (!(ZEPHIR_IS_EMPTY(_16))) {
				zephir_concat_self_str(&pattern, " a", sizeof(" a")-1 TSRMLS_CC);
			}
		}
		RETURN_CTOR(pattern);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns an instance of IntlDateFormatter with specified options.
 *
 * @param array $options
 * @return IntlDateFormatter
 */
PHP_METHOD(Tartan_Shamsi, getFormatter) {

	zephir_nts_static zephir_fcall_cache_entry *_7 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *calendar = NULL, *locale = NULL, *pattern = NULL, *_10;
	zval *options_param = NULL, *timezone = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3, *_4, _5, *_6 = NULL, *_8 = NULL, *_9, *_11 = NULL, *_12, *_13;
	zval *options = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	} else {
		zephir_get_arrval(options, options_param);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_OBS_VAR(_1);
	zephir_array_fetch_string(&_1, options, SL("locale"), PH_NOISY, "tartan/shamsi.zep", 144 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_1)) {
		ZEPHIR_OBS_NVAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("locale"), PH_NOISY_CC);
	} else {
		ZEPHIR_OBS_NVAR(_0);
		zephir_array_fetch_string(&_0, options, SL("locale"), PH_NOISY, "tartan/shamsi.zep", 144 TSRMLS_CC);
	}
	zephir_get_strval(locale, _0);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_OBS_VAR(_3);
	zephir_array_fetch_string(&_3, options, SL("calendar"), PH_NOISY, "tartan/shamsi.zep", 145 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_3)) {
		ZEPHIR_OBS_NVAR(_2);
		zephir_read_property_this(&_2, this_ptr, SL("calendar"), PH_NOISY_CC);
	} else {
		ZEPHIR_OBS_NVAR(_2);
		zephir_array_fetch_string(&_2, options, SL("calendar"), PH_NOISY, "tartan/shamsi.zep", 145 TSRMLS_CC);
	}
	zephir_get_strval(calendar, _2);
	ZEPHIR_OBS_VAR(_4);
	zephir_array_fetch_string(&_4, options, SL("timezone"), PH_NOISY, "tartan/shamsi.zep", 146 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_4)) {
		ZEPHIR_CALL_METHOD(&timezone, this_ptr, "gettimezone", NULL);
		zephir_check_call_status();
	} else {
		ZEPHIR_OBS_NVAR(timezone);
		zephir_array_fetch_string(&timezone, options, SL("timezone"), PH_NOISY, "tartan/shamsi.zep", 146 TSRMLS_CC);
	}
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_STRING(&_5, "DateTimeZone", 0);
	ZEPHIR_CALL_FUNCTION(&_6, "is_a", &_7, timezone, &_5);
	zephir_check_call_status();
	if (zephir_is_true(_6)) {
		ZEPHIR_CALL_METHOD(&timezone, timezone, "getname", NULL);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_8);
	ZEPHIR_OBS_VAR(_9);
	zephir_array_fetch_string(&_9, options, SL("pattern"), PH_NOISY, "tartan/shamsi.zep", 150 TSRMLS_CC);
	if (ZEPHIR_IS_EMPTY(_9)) {
		ZEPHIR_INIT_NVAR(_8);
		ZVAL_NULL(_8);
	} else {
		ZEPHIR_OBS_NVAR(_8);
		zephir_array_fetch_string(&_8, options, SL("pattern"), PH_NOISY, "tartan/shamsi.zep", 150 TSRMLS_CC);
	}
	zephir_get_strval(pattern, _8);
	object_init_ex(return_value, zephir_get_internal_ce(SS("intldateformatter") TSRMLS_CC));
	ZEPHIR_INIT_VAR(_10);
	ZEPHIR_CONCAT_VSV(_10, locale, "@calendar=", calendar);
	ZEPHIR_INIT_VAR(_11);
	if (ZEPHIR_IS_STRING(calendar, "gregorian")) {
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 1);
	} else {
		ZEPHIR_INIT_NVAR(_11);
		ZVAL_LONG(_11, 0);
	}
	ZEPHIR_INIT_VAR(_12);
	ZVAL_LONG(_12, 0);
	ZEPHIR_INIT_VAR(_13);
	ZVAL_LONG(_13, 0);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, _10, _12, _13, timezone, _11, pattern);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Replaces localized digits in $str with latin digits.
 *
 * @param string $str
 * @return string Latinized string
 */
PHP_METHOD(Tartan_Shamsi, latinizeDigits) {

	zephir_fcall_cache_entry *_8 = NULL;
	HashTable *_5;
	HashPosition _4;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int pos, ZEPHIR_LAST_CALL_STATUS;
	zval *matches;
	zval *result;
	zval *str, *num, *charac = NULL, *parsedChar = NULL, *_0, *_1 = NULL, *_3, **_6, *_7 = NULL, *_9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &str);



	ZEPHIR_INIT_VAR(matches);
	array_init(matches);
	ZEPHIR_INIT_VAR(result);
	ZVAL_EMPTY_STRING(result);
	ZEPHIR_INIT_VAR(num);
	object_init_ex(num, zephir_get_internal_ce(SS("numberformatter") TSRMLS_CC));
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("locale"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 1);
	ZEPHIR_CALL_METHOD(NULL, num, "__construct", NULL, _0, _1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "/.[\\x80-\\xBF]*/", ZEPHIR_TEMP_PARAM_COPY);
	Z_SET_ISREF_P(matches);
	ZEPHIR_CALL_FUNCTION(NULL, "preg_match_all", &_2, _1, str, matches);
	zephir_check_temp_parameter(_1);
	Z_UNSET_ISREF_P(matches);
	zephir_check_call_status();
	zephir_array_fetch_long(&_3, matches, 0, PH_NOISY | PH_READONLY, "tartan/shamsi.zep", 170 TSRMLS_CC);
	zephir_is_iterable(_3, &_5, &_4, 0, 0, "tartan/shamsi.zep", 175);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HVALUE(charac, _6);
		pos = 0;
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 1);
		ZEPHIR_INIT_NVAR(_7);
		ZVAL_LONG(_7, pos);
		ZEPHIR_CALL_METHOD(&parsedChar, num, "parse", &_8, charac, _1, _7);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_9);
		if (pos) {
			ZEPHIR_CPY_WRT(_9, parsedChar);
		} else {
			ZEPHIR_CPY_WRT(_9, charac);
		}
		zephir_concat_self(&result, _9 TSRMLS_CC);
	}
	RETURN_CTOR(result);

}

/**
 * Alter the timestamp by incrementing or decrementing in a format accepted by strtotime().
 *
 * @param string $modify a string in a relative format accepted by strtotime().
 * @return IntlDateTime The modified DateTime.
 */
PHP_METHOD(Tartan_Shamsi, modify) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL;
	zval *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *modify_param = NULL, *tempModify = NULL, *_0, *_2 = NULL, *_3 = NULL;
	zval *modify = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &modify_param);

	zephir_get_strval(modify, modify_param);


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_trim(_0, modify, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&tempModify, this_ptr, "latinizedigits", NULL, _0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	array_init_size(_1, 3);
	zephir_array_fast_append(_1, this_ptr);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "modifyCallback", 1);
	zephir_array_fast_append(_1, _2);
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "/(.*?)((?:[+-]?\\d+)|next|last|previous)\\s*(year|month)s?/i", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_FUNCTION(&_3, "preg_replace_callback", &_4, _2, _1, tempModify);
	zephir_check_temp_parameter(_2);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(tempModify, _3);
	if (!(ZEPHIR_IS_EMPTY(tempModify))) {
		ZEPHIR_CALL_PARENT(NULL, tartan_shamsi_ce, this_ptr, "modify", NULL, tempModify);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * Overrides the getTimestamp method to support timestamps out of the integer range.
 *
 * @return float Unix timestamp representing the date.
 */
PHP_METHOD(Tartan_Shamsi, getTimestamp) {

	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "U", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_PARENT(&_0, tartan_shamsi_ce, this_ptr, "format", NULL, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("floatval", &_2, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Overrides the setTimestamp method to support timestamps out of the integer range.
 *
 * @param float $unixtimestamp Unix timestamp representing the date.
 * @return IntlDateTime the modified DateTime.
 */
PHP_METHOD(Tartan_Shamsi, setTimestamp) {

	zval *str = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL, *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *unixtimestamp_param = NULL, diff, *days = NULL, *seconds, *timezone = NULL, *_0 = NULL, _1, *_3, *_4 = NULL, *_6 = NULL, *_7;
	double unixtimestamp;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &unixtimestamp_param);

	unixtimestamp = zephir_get_doubleval(unixtimestamp_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "gettimestamp", NULL);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(diff);
	ZVAL_LONG(&diff, (unixtimestamp - zephir_get_numberval(_0)));
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_DOUBLE(&_1, zephir_safe_div_zval_long(&diff, 86400 TSRMLS_CC));
	ZEPHIR_CALL_FUNCTION(&days, "floor", &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(seconds);
	ZVAL_LONG(seconds, (zephir_get_numberval(&diff) - (zephir_get_numberval(days) * 86400)));
	ZEPHIR_CALL_METHOD(&timezone, this_ptr, "gettimezone", NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "UTC", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, _3);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_4, "strval", &_5, days);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_6, "strval", &_5, seconds);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_CONCAT_VSVS(_7, _4, " days ", _6, " seconds");
	zephir_get_strval(str, _7);
	ZEPHIR_CALL_PARENT(NULL, tartan_shamsi_ce, this_ptr, "modify", NULL, str);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, timezone);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Resets the current date of the object.
 *
 * @param integer $year
 * @param integer $month
 * @param integer $day
 * @return IntlDateTime The modified DateTime.
 */
PHP_METHOD(Tartan_Shamsi, setDate) {

	zval *year_param = NULL, *month_param = NULL, *day_param = NULL, _0, _1, _2, *_3 = NULL, *_4 = NULL, *_5, *_6;
	int year, month, day, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &year_param, &month_param, &day_param);

	year = zephir_get_intval(year_param);
	month = zephir_get_intval(month_param);
	day = zephir_get_intval(day_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, year);
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_LONG(&_1, month);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, day);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "HH:mm:ss", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "format", NULL, _4);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_CONCAT_VSVSVSV(_5, &_0, "/", &_1, "/", &_2, " ", _3);
	ZEPHIR_INIT_NVAR(_4);
	ZVAL_NULL(_4);
	ZEPHIR_INIT_VAR(_6);
	ZVAL_STRING(_6, "yyyy/MM/dd HH:mm:ss", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, _5, _4, _6);
	zephir_check_temp_parameter(_6);
	zephir_check_call_status();
	RETURN_THIS();

}

PHP_METHOD(Tartan_Shamsi, say) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *zaman, *timez, *lang, *zab;
	zval *date, *_0, *_1, *_2, *_3, *_4, *_5 = NULL, *_6 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(zaman);
	ZVAL_STRING(zaman, "now", 1);
	ZEPHIR_INIT_VAR(timez);
	ZVAL_STRING(timez, "Asia/Tehran", 1);
	ZEPHIR_INIT_VAR(lang);
	ZVAL_STRING(lang, "persian", 1);
	ZEPHIR_INIT_VAR(zab);
	ZVAL_STRING(zab, "fa", 1);
	ZEPHIR_INIT_VAR(date);
	object_init_ex(date, zephir_get_internal_ce(SS("intldateformatter") TSRMLS_CC));
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "fa_IR@calendar=persian", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 0);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_STRING(_3, "Asia/Tehran", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 0);
	ZEPHIR_CALL_METHOD(NULL, date, "__construct", NULL, _0, _1, _2, _3, _4);
	zephir_check_temp_parameter(_0);
	zephir_check_temp_parameter(_3);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_6, "time", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, date, "format", NULL, _6);
	zephir_check_call_status();
	zend_print_zval(_5, 0);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the timezone for the object.
 *
 * @param mixed $timezone DateTimeZone object or timezone identifier as full name (e.g. Asia/Tehran) or abbreviation (e.g. IRDT).
 * @return IntlDateTime The modified DateTime.
 */
PHP_METHOD(Tartan_Shamsi, setTimezone) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *timezone = NULL, _0, *_1 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &timezone);

	ZEPHIR_SEPARATE_PARAM(timezone);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "DateTimeZone", 0);
	ZEPHIR_CALL_FUNCTION(&_1, "is_a", &_2, timezone, &_0);
	zephir_check_call_status();
	if (!zephir_is_true(_1)) {
		ZEPHIR_INIT_NVAR(timezone);
		object_init_ex(timezone, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, timezone, "__construct", NULL, timezone);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_PARENT(NULL, tartan_shamsi_ce, this_ptr, "settimezone", NULL, timezone);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Returns date formatted according to given pattern.
 *
 * @param string $pattern Date pattern in ICU syntax (@link http://userguide.icu-project.org/formatparse/datetime)
 * @param mixed $timezone DateTimeZone object or timezone identifier as full name (e.g. Asia/Tehran) or abbreviation (e.g. IRDT).
 * @return string Formatted date on success or FALSE on failure.
 */
PHP_METHOD(Tartan_Shamsi, format) {

	zval *_1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *pattern_param = NULL, *timezone = NULL, *tempTimezone = NULL, *result = NULL, *_0 = NULL, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_5, *_6 = NULL;
	zval *pattern = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &pattern_param, &timezone);

	if (unlikely(Z_TYPE_P(pattern_param) != IS_STRING && Z_TYPE_P(pattern_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'pattern' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(pattern_param) == IS_STRING)) {
		zephir_get_strval(pattern, pattern_param);
	} else {
		ZEPHIR_INIT_VAR(pattern);
		ZVAL_EMPTY_STRING(pattern);
	}
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}


	if (!(ZEPHIR_IS_EMPTY(timezone))) {
		ZEPHIR_CALL_METHOD(&tempTimezone, this_ptr, "gettimezone", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, timezone);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(_1);
	array_init_size(_1, 3);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "Z", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_PARENT(&_3, tartan_shamsi_ce, this_ptr, "format", NULL, _4);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "P", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_PARENT(&_2, tartan_shamsi_ce, this_ptr, "format", NULL, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "", 1);
	}
	ZEPHIR_INIT_VAR(_5);
	ZEPHIR_CONCAT_SV(_5, "GMT", _2);
	zephir_array_update_string(&_1, SL("timezone"), &_5, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("pattern"), &pattern, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getformatter", NULL, _1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "gettimestamp", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&result, _0, "format", NULL, _6);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(timezone))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, tempTimezone);
		zephir_check_call_status();
	}
	RETURN_CCTOR(result);

}

/**
 * Preserve original DateTime::format functionality
 *
 * @param string $format Format accepted by date().
 * @param mixed $timezone DateTimeZone object or timezone identifier as full name (e.g. Asia/Tehran) or abbreviation (e.g. IRDT).
 * @return string Formatted date on success or FALSE on failure.
 */
PHP_METHOD(Tartan_Shamsi, classicFormat) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *format_param = NULL, *timezone = NULL, *tempTimezone = NULL, *result = NULL;
	zval *format = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &format_param, &timezone);

	zephir_get_strval(format, format_param);
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}


	if (!(ZEPHIR_IS_EMPTY(timezone))) {
		ZEPHIR_CALL_METHOD(&tempTimezone, this_ptr, "gettimezone", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, timezone);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_PARENT(&result, tartan_shamsi_ce, this_ptr, "format", NULL, format);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(timezone))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "settimezone", NULL, tempTimezone);
		zephir_check_call_status();
	}
	RETURN_CCTOR(result);

}

