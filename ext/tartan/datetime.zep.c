
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
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/hash.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Tartan_Datetime) {

	ZEPHIR_REGISTER_CLASS(Tartan, Datetime, tartan, datetime, tartan_datetime_method_entry, 0);

	zend_declare_property_null(tartan_datetime_ce, SL("jalali"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(tartan_datetime_ce, SL("convert"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(tartan_datetime_ce, SL("timezone"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(tartan_datetime_ce, SL("temp"), ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * jDateTime::Constructor
 *
 * Pass these parameteres when creating a new instance
 * of this Class, and they will be used as defaults.
 * e.g $obj = new Tartan\DateTime(false, true, 'Asia/Tehran');
 * To use system defaults pass null for each one or just
 * create the object without any parameters.
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param convert bool Converts numbers to Farsi
 * @param jalali bool Converts date to Jalali
 * @param timezone string Timezone string
 */
PHP_METHOD(Tartan_Datetime, __construct) {

	zval *timezone = NULL;
	zval *convert_param = NULL, *jalali_param = NULL, *timezone_param = NULL, *_0;
	zend_bool convert, jalali;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &convert_param, &jalali_param, &timezone_param);

	if (!convert_param) {
		convert = 1;
	} else {
		convert = zephir_get_boolval(convert_param);
	}
	if (!jalali_param) {
		jalali = 1;
	} else {
		jalali = zephir_get_boolval(jalali_param);
	}
	if (!timezone_param) {
		ZEPHIR_INIT_VAR(timezone);
		ZVAL_STRING(timezone, "", 1);
	} else {
		zephir_get_strval(timezone, timezone_param);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_BOOL(_0, jalali);
	zephir_update_static_property_ce(tartan_datetime_ce, SL("jalali"), &_0 TSRMLS_CC);
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_BOOL(_0, convert);
	zephir_update_static_property_ce(tartan_datetime_ce, SL("convert"), &_0 TSRMLS_CC);
	zephir_update_static_property_ce(tartan_datetime_ce, SL("timezone"), &timezone TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * jDateTime::Date
 *
 * Formats and returns given timestamp just like php's
 * built in date() function.
 * e.g:
 * $obj->date("Y-m-d H:i", time());
 * $obj->date("Y-m-d", time(), false, false, 'America/New_York');
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param $format string Acceps format string based on: php.net/date
 * @param $stamp int Unix Timestamp (Epoch Time)
 * @param $convert bool (Optional) forces convert action. pass null to use system default
 * @param $jalali bool (Optional) forces jalali conversion. pass null to use system default
 * @param $timezone string (Optional) forces a different timezone. pass null to use system default
 * @return string Formatted input
 */
PHP_METHOD(Tartan_Datetime, date) {

	HashTable *_15, *_29;
	HashPosition _14, _28;
	zephir_nts_static zephir_fcall_cache_entry *_11 = NULL, *_13 = NULL, *_33 = NULL, *_34 = NULL, *_39 = NULL, *_44 = NULL, *_49 = NULL, *_59 = NULL, *_60 = NULL, *_62 = NULL;
	zend_bool _6, _7, _45, _46, _47, _48, _61;
	int ZEPHIR_LAST_CALL_STATUS, year, month, day, jyear, jmonth, jday;
	zephir_fcall_cache_entry *_1 = NULL, *_18 = NULL, *_51 = NULL;
	zval *intact = NULL, *intactValues, *chars = NULL, *keys = NULL, *_27, *values = NULL;
	zval *format_param = NULL, *stamp = NULL, *convert = NULL, *jalali = NULL, *timezone = NULL, *_0 = NULL, *_2, *obj, *_3, *_4, *_5, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_12 = NULL, *k = NULL, *v = NULL, **_16, *_17 = NULL, *_19 = NULL, *_20 = NULL, *jParts = NULL, *_21 = NULL, *_22 = NULL, *_23, *_24, *_25, *_26 = NULL, *key = NULL, **_30, _31 = zval_used_for_init, _32 = zval_used_for_init, *_35 = NULL, *_36 = NULL, *_37, *_38, *_40, *_41, *_42, *_43, *tmpObj = NULL, *_50 = NULL, _52 = zval_used_for_init, *_53 = NULL, *_54 = NULL, *_55 = NULL, *_56 = NULL, *_57 = NULL, *_58 = NULL, *ret = NULL;
	zval *format = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &format_param, &stamp, &convert, &jalali, &timezone);

	if (unlikely(Z_TYPE_P(format_param) != IS_STRING && Z_TYPE_P(format_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'format' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(format_param) == IS_STRING)) {
		zephir_get_strval(format, format_param);
	} else {
		ZEPHIR_INIT_VAR(format);
		ZVAL_EMPTY_STRING(format);
	}
	if (!stamp) {
		ZEPHIR_CPY_WRT(stamp, ZEPHIR_GLOBAL(global_false));
	} else {
		ZEPHIR_SEPARATE_PARAM(stamp);
	}
	if (!convert) {
		convert = ZEPHIR_GLOBAL(global_null);
	}
	if (!jalali) {
		jalali = ZEPHIR_GLOBAL(global_null);
	}
	if (!timezone) {
		ZEPHIR_CPY_WRT(timezone, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(timezone);
	}


	ZEPHIR_INIT_VAR(_0);
	if (!ZEPHIR_IS_FALSE_IDENTICAL(stamp)) {
		ZEPHIR_CPY_WRT(_0, stamp);
	} else {
		ZEPHIR_CALL_FUNCTION(&_0, "time", &_1);
		zephir_check_call_status();
	}
	ZEPHIR_CPY_WRT(stamp, _0);
	ZEPHIR_INIT_LNVAR(_0);
	if (Z_TYPE_P(timezone) != IS_NULL) {
		ZEPHIR_CPY_WRT(_0, timezone);
	} else {
		_2 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("timezone") TSRMLS_CC);
		if (Z_TYPE_P(_2) != IS_NULL) {
			ZEPHIR_OBS_NVAR(_0);
			zephir_read_static_property_ce(&_0, tartan_datetime_ce, SL("timezone") TSRMLS_CC);
		} else {
			ZEPHIR_CALL_FUNCTION(&_0, "date_default_timezone_get", NULL);
			zephir_check_call_status();
		}
	}
	ZEPHIR_CPY_WRT(timezone, _0);
	ZEPHIR_INIT_VAR(obj);
	object_init_ex(obj, zephir_get_internal_ce(SS("datetime") TSRMLS_CC));
	ZEPHIR_INIT_LNVAR(_0);
	ZEPHIR_CONCAT_SV(_0, "@", stamp);
	ZEPHIR_INIT_VAR(_3);
	object_init_ex(_3, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _3, "__construct", NULL, timezone);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, obj, "__construct", NULL, _0, _3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_4);
	object_init_ex(_4, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
	ZEPHIR_CALL_METHOD(NULL, _4, "__construct", NULL, timezone);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, obj, "settimezone", NULL, _4);
	zephir_check_call_status();
	_5 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("jalali") TSRMLS_CC);
	_6 = ZEPHIR_IS_FALSE_IDENTICAL(_5);
	if (_6) {
		_6 = Z_TYPE_P(jalali) == IS_NULL;
	}
	_7 = _6;
	if (!(_7)) {
		_7 = ZEPHIR_IS_FALSE_IDENTICAL(jalali);
	}
	if (_7) {
		ZEPHIR_RETURN_CALL_METHOD(obj, "format", NULL, format);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_INIT_VAR(chars);
		array_init(chars);
		ZEPHIR_INIT_VAR(_8);
		ZEPHIR_INIT_VAR(_9);
		ZVAL_STRING(_9, "/([a-zA-Z]{1})/", ZEPHIR_TEMP_PARAM_COPY);
		Z_SET_ISREF_P(chars);
		ZEPHIR_CALL_FUNCTION(&_10, "preg_match_all", &_11, _9, format, chars);
		zephir_check_temp_parameter(_9);
		Z_UNSET_ISREF_P(chars);
		zephir_check_call_status();
		if (zephir_is_true(_10)) {
			ZEPHIR_OBS_NVAR(_8);
			zephir_array_fetch_long(&_8, chars, 0, PH_NOISY, "tartan/datetime.zep", 71 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(_8);
			array_init(_8);
		}
		ZEPHIR_CPY_WRT(chars, _8);
		ZEPHIR_INIT_VAR(intact);
		array_init_size(intact, 17);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "B", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "h", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "H", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "g", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "G", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "i", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "s", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "I", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "U", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "u", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "Z", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "O", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "P", 1);
		zephir_array_fast_append(intact, _9);
		ZEPHIR_CALL_SELF(&_12, "filterarray", &_13, chars, intact);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(intact, _12);
		ZEPHIR_INIT_VAR(intactValues);
		array_init(intactValues);
		zephir_is_iterable(intact, &_15, &_14, 0, 0, "tartan/datetime.zep", 83);
		for (
		  ; zephir_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
		  ; zephir_hash_move_forward_ex(_15, &_14)
		) {
			ZEPHIR_GET_HMKEY(k, _15, _14);
			ZEPHIR_GET_HVALUE(v, _16);
			ZEPHIR_CALL_METHOD(&_17, obj, "format", &_18, v);
			zephir_check_call_status();
			zephir_array_update_zval(&intactValues, k, &_17, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "Y", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_17, obj, "format", &_18, _9);
		zephir_check_temp_parameter(_9);
		zephir_check_call_status();
		year = zephir_get_intval(_17);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "n", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_19, obj, "format", &_18, _9);
		zephir_check_temp_parameter(_9);
		zephir_check_call_status();
		month = zephir_get_intval(_19);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "j", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_20, obj, "format", &_18, _9);
		zephir_check_temp_parameter(_9);
		zephir_check_call_status();
		day = zephir_get_intval(_20);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_LONG(_9, year);
		ZEPHIR_INIT_VAR(_21);
		ZVAL_LONG(_21, month);
		ZEPHIR_INIT_VAR(_22);
		ZVAL_LONG(_22, day);
		ZEPHIR_CALL_SELF(&jParts, "tojalali", NULL, _9, _21, _22);
		zephir_check_call_status();
		zephir_array_fetch_long(&_23, jParts, 0, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 92 TSRMLS_CC);
		jyear = zephir_get_intval(_23);
		zephir_array_fetch_long(&_24, jParts, 1, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 93 TSRMLS_CC);
		jmonth = zephir_get_intval(_24);
		zephir_array_fetch_long(&_25, jParts, 2, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 94 TSRMLS_CC);
		jday = zephir_get_intval(_25);
		ZEPHIR_INIT_VAR(keys);
		array_init_size(keys, 31);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "d", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "D", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "j", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "l", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "N", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "S", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "w", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "z", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "W", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "F", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "m", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "M", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "n", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "t", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "L", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "o", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "Y", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "y", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "a", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "A", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "c", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "r", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "e", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "T", 1);
		zephir_array_fast_append(keys, _9);
		ZEPHIR_INIT_VAR(_27);
		array_init_size(_27, 2);
		ZEPHIR_INIT_NVAR(_9);
		ZVAL_STRING(_9, "z", 1);
		zephir_array_fast_append(_27, _9);
		ZEPHIR_CALL_SELF(&_26, "filterarray", &_13, chars, keys, _27);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(keys, _26);
		ZEPHIR_INIT_VAR(values);
		array_init(values);
		zephir_is_iterable(keys, &_29, &_28, 0, 0, "tartan/datetime.zep", 206);
		for (
		  ; zephir_hash_get_current_data_ex(_29, (void**) &_30, &_28) == SUCCESS
		  ; zephir_hash_move_forward_ex(_29, &_28)
		) {
			ZEPHIR_GET_HMKEY(k, _29, _28);
			ZEPHIR_GET_HVALUE(key, _30);
			ZEPHIR_INIT_NVAR(v);
			ZVAL_STRING(v, "", 1);
			do {
				if (ZEPHIR_IS_STRING(key, "d")) {
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_STRING(&_31, "%02d", 0);
					ZEPHIR_SINIT_NVAR(_32);
					ZVAL_LONG(&_32, jday);
					ZEPHIR_CALL_FUNCTION(&v, "sprintf", &_33, &_31, &_32);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "D")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "D", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_35, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_BOOL(_9, 1);
					ZEPHIR_CALL_SELF(&v, "getdaynames", &_34, _35, _9);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "j")) {
					ZEPHIR_INIT_NVAR(v);
					ZVAL_LONG(v, jday);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "l")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "l", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_35, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_CALL_SELF(&v, "getdaynames", &_34, _35);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "N")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "l", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_35, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_BOOL(_9, 0);
					ZEPHIR_INIT_NVAR(_21);
					ZVAL_LONG(_21, 1);
					ZEPHIR_INIT_NVAR(_22);
					ZVAL_BOOL(_22, 1);
					ZEPHIR_CALL_SELF(&v, "getdaynames", &_34, _35, _9, _21, _22);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "S")) {
					ZEPHIR_INIT_NVAR(v);
					ZVAL_STRING(v, "ام", 1);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "w")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "l", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_36, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_BOOL(_9, 0);
					ZEPHIR_INIT_NVAR(_21);
					ZVAL_LONG(_21, 1);
					ZEPHIR_INIT_NVAR(_22);
					ZVAL_BOOL(_22, 1);
					ZEPHIR_CALL_SELF(&_35, "getdaynames", &_34, _36, _9, _21, _22);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(v);
					ZVAL_LONG(v, (zephir_get_numberval(_35) - 1));
					break;
				}
				if (ZEPHIR_IS_STRING(key, "z")) {
					ZEPHIR_INIT_NVAR(v);
					if (jmonth > 6) {
						ZVAL_LONG(v, ((186 + (((((jmonth - 6) - 1)) * 30))) + jday));
					} else {
						ZVAL_LONG(v, (((((jmonth - 1)) * 31)) + jday));
					}
					zephir_update_static_property_array_multi_ce(tartan_datetime_ce, SL("temp"), &v TSRMLS_CC, SL("s"), 2, SL("z"));
					break;
				}
				if (ZEPHIR_IS_STRING(key, "W")) {
					_37 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("temp") TSRMLS_CC);
					zephir_array_fetch_string(&_38, _37, SL("z"), PH_NOISY | PH_READONLY, "tartan/datetime.zep", 139 TSRMLS_CC);
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_DOUBLE(&_31, zephir_safe_div_zval_long(_38, 7 TSRMLS_CC));
					ZEPHIR_CALL_FUNCTION(&_35, "is_int", &_39, &_31);
					zephir_check_call_status();
					if (zephir_is_true(_35)) {
						_40 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("temp") TSRMLS_CC);
						zephir_array_fetch_string(&_41, _40, SL("z"), PH_NOISY | PH_READONLY, "tartan/datetime.zep", 139 TSRMLS_CC);
						ZEPHIR_INIT_NVAR(v);
						ZVAL_DOUBLE(v, zephir_safe_div_zval_long(_41, 7 TSRMLS_CC));
					} else {
						_42 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("temp") TSRMLS_CC);
						zephir_array_fetch_string(&_43, _42, SL("z"), PH_NOISY | PH_READONLY, "tartan/datetime.zep", 139 TSRMLS_CC);
						ZEPHIR_SINIT_NVAR(_31);
						ZVAL_DOUBLE(&_31, (zephir_safe_div_zval_long(_43, 7 TSRMLS_CC) + (double) (1)));
						ZEPHIR_INIT_NVAR(v);
						ZVAL_LONG(v, zephir_get_intval(&_31));
					}
					break;
				}
				if (ZEPHIR_IS_STRING(key, "F")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_LONG(_9, jmonth);
					ZEPHIR_CALL_SELF(&v, "getmonthnames", &_44, _9);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "m")) {
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_STRING(&_31, "%02d", 0);
					ZEPHIR_SINIT_NVAR(_32);
					ZVAL_LONG(&_32, jmonth);
					ZEPHIR_CALL_FUNCTION(&v, "sprintf", &_33, &_31, &_32);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "M")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_LONG(_9, jmonth);
					ZEPHIR_INIT_NVAR(_21);
					ZVAL_BOOL(_21, 1);
					ZEPHIR_CALL_SELF(&v, "getmonthnames", &_44, _9, _21);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "n")) {
					ZEPHIR_INIT_NVAR(v);
					ZVAL_LONG(v, jmonth);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "t")) {
					_45 = jmonth >= 1;
					if (_45) {
						_45 = jmonth <= 6;
					}
					_46 = jmonth >= 7;
					if (_46) {
						_46 = jmonth <= 11;
					}
					_47 = jmonth == 12;
					if (_47) {
						_47 = (jyear % 4) == 3;
					}
					_48 = jmonth == 12;
					if (_48) {
						_48 = (jyear % 4) != 3;
					}
					if (_45) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_LONG(v, 31);
					} else if (_46) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_LONG(v, 30);
					} else if (_47) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_LONG(v, 30);
					} else if (_48) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_LONG(v, 29);
					}
					break;
				}
				if (ZEPHIR_IS_STRING(key, "L")) {
					ZEPHIR_INIT_NVAR(tmpObj);
					object_init_ex(tmpObj, zephir_get_internal_ce(SS("datetime") TSRMLS_CC));
					ZEPHIR_CALL_FUNCTION(&_35, "time", &_1);
					zephir_check_call_status();
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_LONG(&_31, (zephir_get_numberval(_35) - 31536000));
					ZEPHIR_CALL_FUNCTION(&_36, "strval", &_49, &_31);
					zephir_check_call_status();
					ZEPHIR_INIT_LNVAR(_50);
					ZEPHIR_CONCAT_SV(_50, "@", _36);
					ZEPHIR_CALL_METHOD(NULL, tmpObj, "__construct", &_51, _50);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "L", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&v, tmpObj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "o") || ZEPHIR_IS_STRING(key, "Y")) {
					ZEPHIR_INIT_NVAR(v);
					ZVAL_LONG(v, jyear);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "y")) {
					ZEPHIR_INIT_NVAR(v);
					ZVAL_LONG(v, (jyear % 100));
					break;
				}
				if (ZEPHIR_IS_STRING(key, "a")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "a", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_35, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					if (ZEPHIR_IS_STRING(_35, "am")) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_STRING(v, "ق.ظ", 1);
					} else {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_STRING(v, "ب.ظ", 1);
					}
					break;
				}
				if (ZEPHIR_IS_STRING(key, "A")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "A", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_35, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					if (ZEPHIR_IS_STRING(_35, "AM")) {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_STRING(v, "قبل از ظهر", 1);
					} else {
						ZEPHIR_INIT_NVAR(v);
						ZVAL_STRING(v, "بعد از ظهر", 1);
					}
					break;
				}
				if (ZEPHIR_IS_STRING(key, "c")) {
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_LONG(&_31, jyear);
					ZEPHIR_SINIT_NVAR(_32);
					ZVAL_STRING(&_32, "%02d", 0);
					ZEPHIR_SINIT_NVAR(_52);
					ZVAL_LONG(&_52, jmonth);
					ZEPHIR_CALL_FUNCTION(&_35, "sprintf", &_33, &_32, &_52);
					zephir_check_call_status();
					ZEPHIR_SINIT_NVAR(_32);
					ZVAL_STRING(&_32, "%02d", 0);
					ZEPHIR_SINIT_NVAR(_52);
					ZVAL_LONG(&_52, jday);
					ZEPHIR_CALL_FUNCTION(&_36, "sprintf", &_33, &_32, &_52);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(v);
					ZEPHIR_CONCAT_VSVSVS(v, &_31, "-", _35, "-", _36, "T");
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "H", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_53, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "i", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_54, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "s", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_55, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "P", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_56, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_LNVAR(_50);
					ZEPHIR_CONCAT_VSVSVV(_50, _53, ":", _54, ":", _55, _56);
					zephir_concat_self(&v, _50 TSRMLS_CC);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "r")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "D", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_36, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_BOOL(_9, 1);
					ZEPHIR_CALL_SELF(&_35, "getdaynames", &_34, _36, _9);
					zephir_check_call_status();
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_STRING(&_31, "%02d", 0);
					ZEPHIR_SINIT_NVAR(_32);
					ZVAL_LONG(&_32, jday);
					ZEPHIR_CALL_FUNCTION(&_53, "sprintf", &_33, &_31, &_32);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_LONG(_9, jmonth);
					ZEPHIR_INIT_NVAR(_21);
					ZVAL_BOOL(_21, 1);
					ZEPHIR_CALL_SELF(&_54, "getmonthnames", &_44, _9, _21);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(v);
					ZEPHIR_CONCAT_VSVSV(v, _35, ", ", _53, " ", _54);
					ZEPHIR_SINIT_NVAR(_31);
					ZVAL_LONG(&_31, jyear);
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "H", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_55, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "i", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_56, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "s", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_57, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "P", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&_58, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					ZEPHIR_INIT_LNVAR(_50);
					ZEPHIR_CONCAT_SVSVSVSVSV(_50, " ", &_31, " ", _55, ":", _56, ":", _57, " ", _58);
					zephir_concat_self(&v, _50 TSRMLS_CC);
					break;
				}
				if (ZEPHIR_IS_STRING(key, "e")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "e", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&v, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					break;
				}
				if (ZEPHIR_IS_STRING(key, "T")) {
					ZEPHIR_INIT_NVAR(_9);
					ZVAL_STRING(_9, "T", ZEPHIR_TEMP_PARAM_COPY);
					ZEPHIR_CALL_METHOD(&v, obj, "format", &_18, _9);
					zephir_check_temp_parameter(_9);
					zephir_check_call_status();
					break;
				}
			} while(0);

			zephir_array_update_zval(&values, k, &v, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_9);
		zephir_fast_array_merge(_9, &(intact), &(keys) TSRMLS_CC);
		ZEPHIR_CPY_WRT(keys, _9);
		ZEPHIR_INIT_NVAR(_21);
		zephir_fast_array_merge(_21, &(intactValues), &(values) TSRMLS_CC);
		ZEPHIR_CPY_WRT(values, _21);
		ZEPHIR_CALL_FUNCTION(&_17, "array_combine", &_59, keys, values);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&ret, "strtr", &_60, format, _17);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_22);
		_45 = ZEPHIR_IS_FALSE_IDENTICAL(convert);
		if (!(_45)) {
			_46 = Z_TYPE_P(convert) == IS_NULL;
			if (_46) {
				_37 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("convert") TSRMLS_CC);
				_46 = ZEPHIR_IS_FALSE_IDENTICAL(_37);
			}
			_45 = _46;
		}
		_47 = _45;
		if (!(_47)) {
			_48 = ZEPHIR_IS_FALSE_IDENTICAL(jalali);
			if (!(_48)) {
				_61 = Z_TYPE_P(jalali) == IS_NULL;
				if (_61) {
					_40 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("jalali") TSRMLS_CC);
					_61 = ZEPHIR_IS_FALSE_IDENTICAL(_40);
				}
				_48 = _61;
			}
			_47 = _48;
		}
		if (_47) {
			ZEPHIR_CPY_WRT(_22, ret);
		} else {
			ZEPHIR_CALL_SELF(&_22, "convertnumbers", &_62, ret);
			zephir_check_call_status();
		}
		RETURN_CCTOR(_22);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Gregorian to Jalali Conversion
 * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param g_y integer Gregorian year
 * @param g_m integer Gregorian month
 * @param g_d integer Gregorian day
 */
PHP_METHOD(Tartan_Datetime, toJalali) {

	zend_bool _7, _8, _9, _12;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int gy, gm, gd, g_day_no, jy, jm, jd, j_day_no, i, ZEPHIR_LAST_CALL_STATUS;
	zval *g_days_in_month, *j_days_in_month;
	zval *g_y, *g_m, *g_d, *j_np = NULL, *_0 = NULL, *_1 = NULL, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6, *_10 = NULL, *_11 = NULL, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &g_y, &g_m, &g_d);



	ZEPHIR_INIT_VAR(g_days_in_month);
	array_init_size(g_days_in_month, 16);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 28);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_VAR(j_days_in_month);
	array_init_size(j_days_in_month, 16);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 29);
	zephir_array_fast_append(j_days_in_month, _0);
	gy = (zephir_get_numberval(g_y) - 1600);
	gm = (zephir_get_numberval(g_m) - 1);
	gd = (zephir_get_numberval(g_d) - 1);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, (gy + 3));
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 4);
	ZEPHIR_CALL_SELF(&_1, "div", &_2, _0, _3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, (gy + 99));
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 100);
	ZEPHIR_CALL_SELF(&_4, "div", &_2, _0, _3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, (gy + 399));
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 400);
	ZEPHIR_CALL_SELF(&_5, "div", &_2, _0, _3);
	zephir_check_call_status();
	g_day_no = ((((365 * gy) + zephir_get_numberval(_1)) - zephir_get_numberval(_4)) + zephir_get_numberval(_5));
	i = 0;
	while (1) {
		if (!(i < gm)) {
			break;
		}
		zephir_array_fetch_long(&_6, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 244 TSRMLS_CC);
		g_day_no += zephir_get_numberval(_6);
		i++;
	}
	_7 = gm > 1;
	if (_7) {
		_8 = (gy % 4) == 0;
		if (_8) {
			_8 = (gy % 100) != 0;
		}
		_9 = _8;
		if (!(_9)) {
			_9 = ((gy % 400) == 0);
		}
		_7 = _9;
	}
	if (_7) {
		g_day_no++;
	}
	g_day_no += gd;
	j_day_no = (g_day_no - 79);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, j_day_no);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 12053);
	ZEPHIR_CALL_SELF(&j_np, "div", &_2, _0, _3);
	zephir_check_call_status();
	j_day_no = (j_day_no % 12053);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, j_day_no);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 1461);
	ZEPHIR_CALL_SELF(&_10, "div", &_2, _0, _3);
	zephir_check_call_status();
	jy = ((979 + (33 * zephir_get_numberval(j_np))) + (4 * zephir_get_numberval(_10)));
	j_day_no %= 1461;
	if (j_day_no >= 366) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, (j_day_no - 1));
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 365);
		ZEPHIR_CALL_SELF(&_11, "div", &_2, _0, _3);
		zephir_check_call_status();
		jy += zephir_get_numberval(_11);
		j_day_no = (((j_day_no - 1)) % 365);
	}
	i = 0;
	while (1) {
		_12 = i < 11;
		if (_12) {
			zephir_array_fetch_long(&_6, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 268 TSRMLS_CC);
			_12 = ZEPHIR_LT_LONG(_6, j_day_no);
		}
		if (!(_12)) {
			break;
		}
		zephir_array_fetch_long(&_13, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 269 TSRMLS_CC);
		j_day_no -= zephir_get_numberval(_13);
		i++;
	}
	jm = (i + 1);
	jd = (j_day_no + 1);
	array_init_size(return_value, 4);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, jy);
	zephir_array_fast_append(return_value, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, jm);
	zephir_array_fast_append(return_value, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, jd);
	zephir_array_fast_append(return_value, _0);
	RETURN_MM();

}

/**
 * Jalali to Gregorian Conversion
 * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param j_y integer Jalali year
 * @param j_m integer Jalali month
 * @param j_d integer Jalali day
 */
PHP_METHOD(Tartan_Datetime, toGregorian) {

	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zend_bool leap, _9;
	zval *g_days_in_month, *j_days_in_month;
	zval *j_y_param = NULL, *j_m_param = NULL, *j_d_param = NULL, *_0 = NULL, *_1 = NULL, *_3 = NULL, *_4 = NULL, *_5, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_10;
	int j_y, j_m, j_d, jy, jm, jd, j_day_no, g_day_no, gy, gm, gd, i, j, a, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &j_y_param, &j_m_param, &j_d_param);

	if (unlikely(Z_TYPE_P(j_y_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'j_y' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	j_y = Z_LVAL_P(j_y_param);
	if (unlikely(Z_TYPE_P(j_m_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'j_m' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	j_m = Z_LVAL_P(j_m_param);
	if (unlikely(Z_TYPE_P(j_d_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'j_d' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	j_d = Z_LVAL_P(j_d_param);


	ZEPHIR_INIT_VAR(g_days_in_month);
	array_init_size(g_days_in_month, 16);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 28);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(g_days_in_month, _0);
	ZEPHIR_INIT_VAR(j_days_in_month);
	array_init_size(j_days_in_month, 16);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 31);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 30);
	zephir_array_fast_append(j_days_in_month, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 29);
	zephir_array_fast_append(j_days_in_month, _0);
	jy = (j_y - 979);
	jm = (j_m - 1);
	jd = (j_d - 1);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, jy);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 33);
	ZEPHIR_CALL_SELF(&_1, "div", &_2, _0, _3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, ((jy % 33) + 3));
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 4);
	ZEPHIR_CALL_SELF(&_4, "div", &_2, _0, _3);
	zephir_check_call_status();
	j_day_no = (((365 * jy) + (zephir_get_numberval(_1) * 8)) + zephir_get_numberval(_4));
	i = 0;
	while (1) {
		if (!(i < jm)) {
			break;
		}
		zephir_array_fetch_long(&_5, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 305 TSRMLS_CC);
		j_day_no += zephir_get_numberval(_5);
		i++;
	}
	j_day_no += jd;
	g_day_no = (j_day_no + 79);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, g_day_no);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 146097);
	ZEPHIR_CALL_SELF(&_6, "div", &_2, _0, _3);
	zephir_check_call_status();
	gy = (1600 + (400 * zephir_get_numberval(_6)));
	g_day_no = (g_day_no % 146097);
	leap = 1;
	if (g_day_no >= 36525) {
		g_day_no = (g_day_no - 1);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, g_day_no);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 36524);
		ZEPHIR_CALL_SELF(&_7, "div", &_2, _0, _3);
		zephir_check_call_status();
		gy += (100 * zephir_get_numberval(_7));
		g_day_no = (g_day_no % 36524);
		if (g_day_no >= 365) {
			g_day_no = (g_day_no + 1);
		} else {
			leap = 0;
		}
	}
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, g_day_no);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_LONG(_3, 1461);
	ZEPHIR_CALL_SELF(&_7, "div", &_2, _0, _3);
	zephir_check_call_status();
	gy += (4 * zephir_get_numberval(_7));
	g_day_no %= 1461;
	if (g_day_no >= 366) {
		leap = 0;
		g_day_no = (g_day_no - 1);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, g_day_no);
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 365);
		ZEPHIR_CALL_SELF(&_8, "div", &_2, _0, _3);
		zephir_check_call_status();
		gy += zephir_get_numberval(_8);
		g_day_no = (g_day_no % 365);
	}
	i = 0;
	j = (zephir_fast_count_int(g_days_in_month TSRMLS_CC) - 1);
	while (1) {
		if (!(i < j)) {
			break;
		}
		_9 = i == 1;
		if (_9) {
			_9 = leap;
		}
		if (_9) {
			a = 1;
		} else {
			a = 0;
		}
		zephir_array_fetch_long(&_5, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 348 TSRMLS_CC);
		if (g_day_no >= (zephir_get_numberval(_5) + a)) {
			zephir_array_fetch_long(&_10, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 349 TSRMLS_CC);
			g_day_no -= (zephir_get_numberval(_10) + a);
		} else {
			break;
		}
		i++;
	}
	gm = (i + 1);
	gd = (g_day_no + 1);
	array_init_size(return_value, 4);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, gy);
	zephir_array_fast_append(return_value, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, gm);
	zephir_array_fast_append(return_value, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, gd);
	zephir_array_fast_append(return_value, _0);
	RETURN_MM();

}

/**
 * jDateTime::Checkdate
 *
 * Checks the validity of the date formed by the arguments.
 * A date is considered valid if each parameter is properly defined.
 * works like php's built in checkdate() function.
 * Leap years are taken into consideration.
 * e.g:
 * $obj->checkdate(10, 21, 1390); // Return true
 * $obj->checkdate(9, 31, 1390);  // Return false
 *
 * You can force gregorian checkdate if system default is jalali and you
 * need to check based on gregorian date
 * $check = $obj->checkdate(12, 31, 2011, false);
 *
 * @author Omid Pilevar
 * @param $month int The month is between 1 and 12 inclusive.
 * @param $day int The day is within the allowed number of days for the given month.
 * @param $year int The year is between 1 and 32767 inclusive.
 * @param $jalali bool (Optional) pass false if you want to input gregorian time
 * @return bool
 */
PHP_METHOD(Tartan_Datetime, checkdate) {

	zval *_16;
	zend_bool _4, _5;
	zval *month_param = NULL, *day_param = NULL, *year_param = NULL, *jalali = NULL, *epoch = NULL, *ret = NULL, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_6, *_7 = NULL, *_8, *_9, *_10, *_11, *_12 = NULL, _13 = zval_used_for_init, _14 = zval_used_for_init, _15 = zval_used_for_init;
	int month, day, year, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &month_param, &day_param, &year_param, &jalali);

	if (unlikely(Z_TYPE_P(month_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'month' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	month = Z_LVAL_P(month_param);
	if (unlikely(Z_TYPE_P(day_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'day' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	day = Z_LVAL_P(day_param);
	if (unlikely(Z_TYPE_P(year_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'year' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	year = Z_LVAL_P(year_param);
	if (!jalali) {
		jalali = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	if (month == 0) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "n", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_0, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, month);
	}
	month = zephir_get_numberval(_0);
	ZEPHIR_INIT_VAR(_2);
	if (day == 0) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "j", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_2, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_LONG(_2, day);
	}
	day = zephir_get_numberval(_2);
	ZEPHIR_INIT_VAR(_3);
	if (year == 0) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Y", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_3, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, year);
	}
	year = zephir_get_numberval(_3);
	_4 = ZEPHIR_IS_TRUE_IDENTICAL(jalali);
	if (!(_4)) {
		_5 = Z_TYPE_P(jalali) == IS_NULL;
		if (_5) {
			_6 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("jalali") TSRMLS_CC);
			_5 = ZEPHIR_IS_TRUE_IDENTICAL(_6);
		}
		_4 = _5;
	}
	if (_4) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, 0);
		ZEPHIR_INIT_VAR(_7);
		ZVAL_LONG(_7, 0);
		ZEPHIR_INIT_VAR(_8);
		ZVAL_LONG(_8, 0);
		ZEPHIR_INIT_VAR(_9);
		ZVAL_LONG(_9, month);
		ZEPHIR_INIT_VAR(_10);
		ZVAL_LONG(_10, day);
		ZEPHIR_INIT_VAR(_11);
		ZVAL_LONG(_11, year);
		ZEPHIR_CALL_SELF(&epoch, "mktime", NULL, _1, _7, _8, _9, _10, _11);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Y-n-j", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_NVAR(_7);
		ZVAL_BOOL(_7, 0);
		ZEPHIR_CALL_SELF(&_12, "date", NULL, _1, epoch, _7);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_SINIT_VAR(_13);
		ZVAL_LONG(&_13, year);
		ZEPHIR_SINIT_VAR(_14);
		ZVAL_LONG(&_14, month);
		ZEPHIR_SINIT_VAR(_15);
		ZVAL_LONG(&_15, day);
		ZEPHIR_INIT_VAR(_16);
		ZEPHIR_CONCAT_VSVSV(_16, &_13, "-", &_14, "-", &_15);
		ZEPHIR_INIT_VAR(ret);
		if (ZEPHIR_IS_EQUAL(_12, _16)) {
			ZVAL_BOOL(ret, 1);
		} else {
			ZVAL_BOOL(ret, 0);
		}
	} else {
		ZEPHIR_SINIT_NVAR(_13);
		ZVAL_LONG(&_13, month);
		ZEPHIR_SINIT_NVAR(_14);
		ZVAL_LONG(&_14, day);
		ZEPHIR_SINIT_NVAR(_15);
		ZVAL_LONG(&_15, year);
		ZEPHIR_CALL_FUNCTION(&ret, "checkdate", NULL, &_13, &_14, &_15);
		zephir_check_call_status();
	}
	RETURN_CCTOR(ret);

}

/**
 * jDateTime::Mktime
 *
 * Creates a Unix Timestamp (Epoch Time) based on given parameters
 * works like php's built in mktime() function.
 * e.g:
 * $time = $obj->mktime(0,0,0,2,10,1368);
 * $obj->date("Y-m-d", $time); //Format and Display
 * $obj->date("Y-m-d", $time, false, false); //Display in Gregorian !
 *
 * You can force gregorian mktime if system default is jalali and you
 * need to create a timestamp based on gregorian date
 * $time2 = $obj->mktime(0,0,0,12,23,1989, false);
 *
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param $hour int Hour based on 24 hour system
 * @param $minute int Minutes
 * @param $second int Seconds
 * @param $month int Month Number
 * @param $day int Day Number
 * @param $year int Four-digit Year number eg. 1390
 * @param $jalali bool (Optional) pass false if you want to input gregorian time
 * @param $timezone string (Optional) acceps an optional timezone if you want one
 * @return int Unix Timestamp (Epoch Time)
 */
PHP_METHOD(Tartan_Datetime, mktime) {

	zephir_nts_static zephir_fcall_cache_entry *_16 = NULL;
	zend_bool _4, _5, _21;
	zval *date = NULL;
	zval *hour_param = NULL, *minute_param = NULL, *second_param = NULL, *month_param = NULL, *day_param = NULL, *year_param = NULL, *jalali = NULL, *timezone = NULL, *gParts = NULL, *obj, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_6, *_7 = NULL, *_8, *_9, *_10, *_11, _12, _13 = zval_used_for_init, _14 = zval_used_for_init, *_15 = NULL, *_17 = NULL, _18, *_19, *_20, *_22 = NULL;
	int hour, minute, second, month, day, year, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 6, 2, &hour_param, &minute_param, &second_param, &month_param, &day_param, &year_param, &jalali, &timezone);

	if (unlikely(Z_TYPE_P(hour_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'hour' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	hour = Z_LVAL_P(hour_param);
	if (unlikely(Z_TYPE_P(minute_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'minute' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	minute = Z_LVAL_P(minute_param);
	if (unlikely(Z_TYPE_P(second_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'second' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	second = Z_LVAL_P(second_param);
	if (unlikely(Z_TYPE_P(month_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'month' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	month = Z_LVAL_P(month_param);
	if (unlikely(Z_TYPE_P(day_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'day' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	day = Z_LVAL_P(day_param);
	if (unlikely(Z_TYPE_P(year_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'year' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	year = Z_LVAL_P(year_param);
	if (!jalali) {
		jalali = ZEPHIR_GLOBAL(global_null);
	}
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	if (month == 0) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "m", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_0, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, month);
	}
	month = zephir_get_numberval(_0);
	ZEPHIR_INIT_VAR(_2);
	if (day == 0) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "d", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_2, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_LONG(_2, day);
	}
	day = zephir_get_numberval(_2);
	ZEPHIR_INIT_VAR(_3);
	if (year == 0) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "Y", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_SELF(&_3, "date", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, year);
	}
	year = zephir_get_numberval(_3);
	_4 = ZEPHIR_IS_TRUE_IDENTICAL(jalali);
	if (!(_4)) {
		_5 = Z_TYPE_P(jalali) == IS_NULL;
		if (_5) {
			_6 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("jalali") TSRMLS_CC);
			_5 = ZEPHIR_IS_TRUE_IDENTICAL(_6);
		}
		_4 = _5;
	}
	if (_4) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, year);
		ZEPHIR_INIT_VAR(_7);
		ZVAL_LONG(_7, month);
		ZEPHIR_INIT_VAR(_8);
		ZVAL_LONG(_8, day);
		ZEPHIR_CALL_SELF(&gParts, "togregorian", NULL, _1, _7, _8);
		zephir_check_call_status();
		zephir_array_fetch_long(&_9, gParts, 0, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 449 TSRMLS_CC);
		year = zephir_get_intval(_9);
		zephir_array_fetch_long(&_10, gParts, 1, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 450 TSRMLS_CC);
		month = zephir_get_intval(_10);
		zephir_array_fetch_long(&_11, gParts, 2, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 451 TSRMLS_CC);
		day = zephir_get_intval(_11);
	}
	ZEPHIR_SINIT_VAR(_12);
	ZVAL_LONG(&_12, year);
	ZEPHIR_SINIT_VAR(_13);
	ZVAL_STRING(&_13, "%02d", 0);
	ZEPHIR_SINIT_VAR(_14);
	ZVAL_LONG(&_14, month);
	ZEPHIR_CALL_FUNCTION(&_15, "sprintf", &_16, &_13, &_14);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_STRING(&_13, "%02d", 0);
	ZEPHIR_SINIT_NVAR(_14);
	ZVAL_LONG(&_14, day);
	ZEPHIR_CALL_FUNCTION(&_17, "sprintf", &_16, &_13, &_14);
	zephir_check_call_status();
	ZEPHIR_SINIT_NVAR(_13);
	ZVAL_LONG(&_13, hour);
	ZEPHIR_SINIT_NVAR(_14);
	ZVAL_LONG(&_14, minute);
	ZEPHIR_SINIT_VAR(_18);
	ZVAL_LONG(&_18, second);
	ZEPHIR_INIT_VAR(_19);
	ZEPHIR_CONCAT_VSVSVSVSVSV(_19, &_12, "-", _15, "-", _17, " ", &_13, ":", &_14, ":", &_18);
	zephir_get_strval(date, _19);
	_20 = zephir_fetch_static_property_ce(tartan_datetime_ce, SL("timezone") TSRMLS_CC);
	_21 = Z_TYPE_P(_20) != IS_NULL;
	if (!(_21)) {
		_21 = Z_TYPE_P(timezone) != IS_NULL;
	}
	ZEPHIR_INIT_VAR(obj);
	if (_21) {
		object_init_ex(obj, zephir_get_internal_ce(SS("datetime") TSRMLS_CC));
		ZEPHIR_INIT_NVAR(_1);
		object_init_ex(_1, zephir_get_internal_ce(SS("datetimezone") TSRMLS_CC));
		ZEPHIR_INIT_VAR(_22);
		if (Z_TYPE_P(timezone) != IS_NULL) {
			ZEPHIR_CPY_WRT(_22, timezone);
		} else {
			ZEPHIR_OBS_NVAR(_22);
			zephir_read_static_property_ce(&_22, tartan_datetime_ce, SL("timezone") TSRMLS_CC);
		}
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _22);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, obj, "__construct", NULL, date, _1);
		zephir_check_call_status();
	} else {
		object_init_ex(obj, zephir_get_internal_ce(SS("datetime") TSRMLS_CC));
		ZEPHIR_CALL_METHOD(NULL, obj, "__construct", NULL, date);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(_7);
	ZVAL_STRING(_7, "U", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_METHOD(obj, "format", NULL, _7);
	zephir_check_temp_parameter(_7);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * jDateTime::Strftime
 *
 * Format a local time/date according to locale settings
 * built in strftime() function.
 * e.g:
 * $obj->strftime("%x %H", time());
 * $obj->strftime("%H", time(), false, false, 'America/New_York');
 *
 * @author Omid Pilevar
 * @param $format string Acceps format string based on: php.net/date
 * @param $stamp int Unix Timestamp (Epoch Time)
 * @param $convert bool (Optional) forces convert action. pass null to use system default
 * @param $jalali bool (Optional) forces jalali conversion. pass null to use system default
 * @param $timezone string (Optional) forces a different timezone. pass null to use system default
 * @return string Formatted input
 */
PHP_METHOD(Tartan_Datetime, strftime) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *str_format_code, *date_format_code;
	zval *format_param = NULL, *stamp = NULL, *convert = NULL, *jalali = NULL, *timezone = NULL, *_0 = NULL;
	zval *format = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &format_param, &stamp, &convert, &jalali, &timezone);

	if (unlikely(Z_TYPE_P(format_param) != IS_STRING && Z_TYPE_P(format_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'format' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(format_param) == IS_STRING)) {
		zephir_get_strval(format, format_param);
	} else {
		ZEPHIR_INIT_VAR(format);
		ZVAL_EMPTY_STRING(format);
	}
	if (!stamp) {
		stamp = ZEPHIR_GLOBAL(global_false);
	}
	if (!convert) {
		convert = ZEPHIR_GLOBAL(global_null);
	}
	if (!jalali) {
		jalali = ZEPHIR_GLOBAL(global_null);
	}
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(str_format_code);
	array_init_size(str_format_code, 51);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "%a", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%A", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%d", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%e", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%j", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%u", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%w", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%U", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%V", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%W", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%b", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%B", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%h", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%m", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%C", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%g", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%G", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%y", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%Y", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%H", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%I", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%l", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%M", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%p", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%P", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%r", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%R", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%S", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%T", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%X", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%z", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%Z", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%c", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%D", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%F", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%s", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%x", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%n", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%t", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%%", 1);
	zephir_array_fast_append(str_format_code, _0);
	ZEPHIR_INIT_VAR(date_format_code);
	array_init_size(date_format_code, 51);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "D", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "l", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "d", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "j", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "z", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "N", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "w", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "W", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "W", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "W", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "M", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "F", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "M", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "m", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "Y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "H", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "h", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "g", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "i", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "A", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "a", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "h:i:s A", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "H:i", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "s", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "H:i:s", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "h:i:s", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "H", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "H", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "D j M H:i:s", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "d/m/y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "Y-m-d", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "U", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "d/m/y", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "\n", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "\t", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "%", 1);
	zephir_array_fast_append(date_format_code, _0);
	ZEPHIR_INIT_NVAR(_0);
	zephir_fast_str_replace(_0, str_format_code, date_format_code, format TSRMLS_CC);
	zephir_get_strval(format, _0);
	ZEPHIR_RETURN_CALL_SELF("date", NULL, format, stamp, convert, jalali, timezone);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Division
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param a integer
 * @param b integer
 */
PHP_METHOD(Tartan_Datetime, div) {

	zval *a, *b, _0;

	zephir_fetch_params(0, 2, 0, &a, &b);



	ZEPHIR_SINIT_VAR(_0);
	div_function(&_0, a, b TSRMLS_CC);
	RETURN_LONG(zephir_get_intval(&_0));

}

/**
 * Substring helper
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param str string text
 * @param start integer start index
 * @param len integer length
 */
PHP_METHOD(Tartan_Datetime, substr) {

	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int start, len, ZEPHIR_LAST_CALL_STATUS;
	zval *str_param = NULL, *start_param = NULL, *len_param = NULL, _0 = zval_used_for_init, _1 = zval_used_for_init, _2;
	zval *str = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &str_param, &start_param, &len_param);

	zephir_get_strval(str, str_param);
	start = zephir_get_intval(start_param);
	len = zephir_get_intval(len_param);


	if ((zephir_function_exists_ex(SS("mb_substr") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_LONG(&_0, start);
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, len);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_STRING(&_2, "UTF-8", 0);
		ZEPHIR_RETURN_CALL_FUNCTION("mb_substr", NULL, str, &_0, &_1, &_2);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		ZEPHIR_SINIT_NVAR(_0);
		ZVAL_LONG(&_0, start);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_LONG(&_1, (len * 2));
		ZEPHIR_RETURN_CALL_FUNCTION("substr", &_3, str, &_0, &_1);
		zephir_check_call_status();
		RETURN_MM();
	}

}

/**
 * Converts latin numbers to farsi script
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param matches array array of digits for convertion
 */
PHP_METHOD(Tartan_Datetime, convertNumbers) {

	zval *matches_param = NULL, *_0 = NULL;
	zval *matches = NULL, *farsi_array, *english_array;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &matches_param);

	zephir_get_arrval(matches, matches_param);


	ZEPHIR_INIT_VAR(farsi_array);
	array_init_size(farsi_array, 13);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "۰", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۱", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۲", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۳", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۴", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۵", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۶", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۷", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۸", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "۹", 1);
	zephir_array_fast_append(farsi_array, _0);
	ZEPHIR_INIT_VAR(english_array);
	array_init_size(english_array, 13);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 0);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 1);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 2);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 3);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 4);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 5);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 6);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 7);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 8);
	zephir_array_fast_append(english_array, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_LONG(_0, 9);
	zephir_array_fast_append(english_array, _0);
	zephir_fast_str_replace(return_value, english_array, farsi_array, matches TSRMLS_CC);
	RETURN_MM();

}

/**
 * Returns correct names for months
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param month integer
 * @param shorten boolean
 * @param len integer
 */
PHP_METHOD(Tartan_Datetime, getMonthNames) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *months;
	zend_bool shorten;
	zval *month_param = NULL, *shorten_param = NULL, *len_param = NULL, *ret, *_0 = NULL, *_2, *_3;
	int month, len, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &month_param, &shorten_param, &len_param);

	if (unlikely(Z_TYPE_P(month_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'month' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	month = Z_LVAL_P(month_param);
	if (!shorten_param) {
		shorten = 0;
	} else {
		shorten = zephir_get_boolval(shorten_param);
	}
	if (!len_param) {
		len = 3;
	} else {
		len = zephir_get_intval(len_param);
	}


	ZEPHIR_INIT_VAR(months);
	array_init_size(months, 16);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "فروردین", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "اردیبهشت", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "خرداد", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "تیر", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "مرداد", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "شهریور", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "مهر", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "آبان", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "آذر", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "دی", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "بهمن", 1);
	zephir_array_fast_append(months, _0);
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "اسفند", 1);
	zephir_array_fast_append(months, _0);
	zephir_array_fetch_long(&ret, months, (month - 1), PH_NOISY | PH_READONLY, "tartan/datetime.zep", 571 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(_0);
	if (shorten == 1) {
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, len);
		ZEPHIR_CALL_SELF(&_0, "substr", &_1, ret, _2, _3);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(_0, ret);
	}
	RETURN_CCTOR(_0);

}

/**
 * Returns correct names for week days
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param day integer
 * @param shorten boolean
 * @param len integer
 * @param numeric boolean
 */
PHP_METHOD(Tartan_Datetime, getDayNames) {

	zephir_nts_static zephir_fcall_cache_entry *_4 = NULL, *_7 = NULL;
	zval *days, *_0 = NULL;
	int len, ZEPHIR_LAST_CALL_STATUS;
	zend_bool shorten, numeric;
	zval *day = NULL, *shorten_param = NULL, *len_param = NULL, *numeric_param = NULL, *_1 = NULL, _2, _3, *_5, *_6 = NULL, *_8, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &day, &shorten_param, &len_param, &numeric_param);

	ZEPHIR_SEPARATE_PARAM(day);
	if (!shorten_param) {
		shorten = 0;
	} else {
	if (unlikely(Z_TYPE_P(shorten_param) != IS_BOOL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'shorten' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	shorten = Z_BVAL_P(shorten_param);
	}
	if (!len_param) {
		len = 1;
	} else {
	if (unlikely(Z_TYPE_P(len_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'len' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	len = Z_LVAL_P(len_param);
	}
	if (!numeric_param) {
		numeric = 0;
	} else {
	if (unlikely(Z_TYPE_P(numeric_param) != IS_BOOL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'numeric' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	numeric = Z_BVAL_P(numeric_param);
	}


	ZEPHIR_INIT_VAR(days);
	array_init_size(days, 9);
	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 1);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "شنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("sat"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 2);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "یکشنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("sun"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 3);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "دوشنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("mon"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 4);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "سه شنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("tue"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 5);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "چهارشنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("wed"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 6);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "پنجشنبه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("thu"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_0);
	array_init_size(_0, 3);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_LONG(_1, 7);
	zephir_array_fast_append(_0, _1);
	ZEPHIR_INIT_NVAR(_1);
	ZVAL_STRING(_1, "جمعه", 1);
	zephir_array_fast_append(_0, _1);
	zephir_array_update_string(&days, SL("fri"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(_1);
	zephir_fast_strtolower(_1, day);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_LONG(&_2, 0);
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 3);
	ZEPHIR_CALL_FUNCTION(&day, "substr", &_4, _1, &_2, &_3);
	zephir_check_call_status();
	zephir_array_fetch(&_5, days, day, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 599 TSRMLS_CC);
	ZEPHIR_CPY_WRT(day, _5);
	ZEPHIR_INIT_VAR(_6);
	if (numeric == 1) {
		zephir_array_fetch_long(&_6, day, 0, PH_NOISY, "tartan/datetime.zep", 600 TSRMLS_CC);
	} else {
		if (shorten == 1) {
			zephir_array_fetch_long(&_5, day, 1, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 600 TSRMLS_CC);
			ZEPHIR_INIT_VAR(_8);
			ZVAL_LONG(_8, 0);
			ZEPHIR_INIT_VAR(_9);
			ZVAL_LONG(_9, len);
			ZEPHIR_CALL_SELF(&_6, "substr", &_7, _5, _8, _9);
			zephir_check_call_status();
		} else {
			ZEPHIR_OBS_NVAR(_6);
			zephir_array_fetch_long(&_6, day, 1, PH_NOISY, "tartan/datetime.zep", 600 TSRMLS_CC);
		}
	}
	RETURN_CCTOR(_6);

}

/**
 * Filters out an array
 *
 * @package Tartan
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param needle array
 * @param heystack array
 * @param always array
 */
PHP_METHOD(Tartan_Datetime, filterArray) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *needle_param = NULL, *heystack_param = NULL, *always_param = NULL, *_0;
	zval *needle = NULL, *heystack = NULL, *always = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &needle_param, &heystack_param, &always_param);

	zephir_get_arrval(needle, needle_param);
	zephir_get_arrval(heystack, heystack_param);
	if (!always_param) {
		ZEPHIR_INIT_VAR(always);
		array_init(always);
	} else {
		zephir_get_arrval(always, always_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_array_merge(_0, &(needle), &(always) TSRMLS_CC);
	ZEPHIR_RETURN_CALL_FUNCTION("array_intersect", &_1, _0, heystack);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * jDateTime::gDate
 *
 * Same as jDateTime::Date method
 * but this one works as a helper and returns Gregorian Date
 * in case someone doesn't like to pass all those false arguments
 * to Date method.
 *
 * e.g. $obj->gDate("Y-m-d") //Outputs: 2011-05-05
 *      $obj->date("Y-m-d", false, false, false); //Outputs: 2011-05-05
 *      Both return the exact same result.
 *
 * @author Aboozar Ghaffari <me@tartan.pro>
 * @param $format string Acceps format string based on: php.net/date
 * @param $stamp int Unix Timestamp (Epoch Time)
 * @param $timezone string (Optional) forces a different timezone. pass null to use system default
 * @return string Formatted input
 */
PHP_METHOD(Tartan_Datetime, gDate) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *format_param = NULL, *stamp = NULL, *timezone = NULL, *_0, *_1;
	zval *format = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &format_param, &stamp, &timezone);

	zephir_get_strval(format, format_param);
	if (!stamp) {
		stamp = ZEPHIR_GLOBAL(global_false);
	}
	if (!timezone) {
		timezone = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_BOOL(_0, 0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_BOOL(_1, 0);
	ZEPHIR_RETURN_CALL_SELF("date", NULL, format, stamp, _0, _1, timezone);
	zephir_check_call_status();
	RETURN_MM();

}

