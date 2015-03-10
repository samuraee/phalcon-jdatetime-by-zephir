
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
#include "kernel/variables.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


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

PHP_METHOD(Tartan_Datetime, say) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL, *_1, *_2, *_3;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 2015);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 03);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, 10);
	ZEPHIR_CALL_SELF(&_0, "tojalali", NULL, _1, _2, _3);
	zephir_check_call_status();
	zephir_var_dump(&_0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gregorian to Jalali Conversion
 * Copyright (C) 2000  Roozbeh Pournader and Mohammad Toossi
 */
PHP_METHOD(Tartan_Datetime, toJalali) {

	zend_bool _8, _9, _10, _13;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	int gy, gm, gd, g_day_no, jy, jm, jd, j_day_no, i, ZEPHIR_LAST_CALL_STATUS;
	zval *g_days_in_month, *j_days_in_month;
	zval *g_y, *g_m, *g_d, *j_np = NULL, *_0 = NULL, *_1 = NULL, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6, *_7 = NULL, *_11 = NULL, *_12 = NULL, *_14;

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
		zephir_array_fetch_long(&_6, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 59 TSRMLS_CC);
		g_day_no += zephir_get_numberval(_6);
		i++;
	}
	ZEPHIR_INIT_VAR(_7);
	ZEPHIR_INIT_NVAR(_7);
	ZVAL_LONG(_7, g_day_no);
	zephir_var_dump(&_7 TSRMLS_CC);
	_8 = gm > 1;
	if (_8) {
		_9 = (gy % 4) == 0;
		if (_9) {
			_9 = (gy % 100) != 0;
		}
		_10 = _9;
		if (!(_10)) {
			_10 = ((gy % 400) == 0);
		}
		_8 = _10;
	}
	if (_8) {
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
	ZEPHIR_CALL_SELF(&_11, "div", &_2, _0, _3);
	zephir_check_call_status();
	jy = ((979 + (33 * zephir_get_numberval(j_np))) + (4 * zephir_get_numberval(_11)));
	j_day_no %= 1461;
	if (j_day_no >= 366) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, (j_day_no - 1));
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_LONG(_3, 365);
		ZEPHIR_CALL_SELF(&_12, "div", &_2, _0, _3);
		zephir_check_call_status();
		jy += zephir_get_numberval(_12);
		j_day_no = (((j_day_no - 1)) % 365);
	}
	i = 0;
	while (1) {
		_13 = i < 11;
		if (_13) {
			zephir_array_fetch_long(&_6, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 86 TSRMLS_CC);
			_13 = ZEPHIR_LT_LONG(_6, j_day_no);
		}
		if (!(_13)) {
			break;
		}
		zephir_array_fetch_long(&_14, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 87 TSRMLS_CC);
		j_day_no -= zephir_get_numberval(_14);
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
		zephir_array_fetch_long(&_5, j_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 127 TSRMLS_CC);
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
		zephir_array_fetch_long(&_5, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 170 TSRMLS_CC);
		if (g_day_no >= (zephir_get_numberval(_5) + a)) {
			zephir_array_fetch_long(&_10, g_days_in_month, i, PH_NOISY | PH_READONLY, "tartan/datetime.zep", 171 TSRMLS_CC);
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
 * Division
 */
PHP_METHOD(Tartan_Datetime, div) {

	zval *a, *b, _0;

	zephir_fetch_params(0, 2, 0, &a, &b);



	ZEPHIR_SINIT_VAR(_0);
	div_function(&_0, a, b TSRMLS_CC);
	RETURN_LONG(zephir_get_intval(&_0));

}

